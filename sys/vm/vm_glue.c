/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)vm_glue.c	8.6 (Berkeley) 1/5/94
 *
 *
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 *
 * $FreeBSD$
 */

#include "opt_vm.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/shm.h>
#include <sys/vmmeter.h>
#include <sys/sx.h>
#include <sys/sysctl.h>

#include <sys/kernel.h>
#include <sys/ktr.h>
#include <sys/unistd.h>

#include <machine/limits.h>

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/vm_object.h>
#include <vm/vm_kern.h>
#include <vm/vm_extern.h>
#include <vm/vm_pager.h>

#include <sys/user.h>

extern int maxslp;

/*
 * System initialization
 *
 * Note: proc0 from proc.h
 */
static void vm_init_limits(void *);
SYSINIT(vm_limits, SI_SUB_VM_CONF, SI_ORDER_FIRST, vm_init_limits, &proc0)

/*
 * THIS MUST BE THE LAST INITIALIZATION ITEM!!!
 *
 * Note: run scheduling should be divorced from the vm system.
 */
static void scheduler(void *);
SYSINIT(scheduler, SI_SUB_RUN_SCHEDULER, SI_ORDER_FIRST, scheduler, NULL)

#ifndef NO_SWAPPING
static void swapout(struct proc *);
static void vm_proc_swapin(struct proc *p);
static void vm_proc_swapout(struct proc *p);
#endif

/*
 * MPSAFE
 */
int
kernacc(addr, len, rw)
	caddr_t addr;
	int len, rw;
{
	boolean_t rv;
	vm_offset_t saddr, eaddr;
	vm_prot_t prot;

	KASSERT((rw & ~VM_PROT_ALL) == 0,
	    ("illegal ``rw'' argument to kernacc (%x)\n", rw));
	prot = rw;
	saddr = trunc_page((vm_offset_t)addr);
	eaddr = round_page((vm_offset_t)addr + len);
	rv = vm_map_check_protection(kernel_map, saddr, eaddr, prot);
	return (rv == TRUE);
}

/*
 * MPSAFE
 */
int
useracc(addr, len, rw)
	caddr_t addr;
	int len, rw;
{
	boolean_t rv;
	vm_prot_t prot;

	KASSERT((rw & ~VM_PROT_ALL) == 0,
	    ("illegal ``rw'' argument to useracc (%x)\n", rw));
	prot = rw;
	/*
	 * XXX - check separately to disallow access to user area and user
	 * page tables - they are in the map.
	 *
	 * XXX - VM_MAXUSER_ADDRESS is an end address, not a max.  It was once
	 * only used (as an end address) in trap.c.  Use it as an end address
	 * here too.  This bogusness has spread.  I just fixed where it was
	 * used as a max in vm_mmap.c.
	 */
	if ((vm_offset_t) addr + len > /* XXX */ VM_MAXUSER_ADDRESS
	    || (vm_offset_t) addr + len < (vm_offset_t) addr) {
		return (FALSE);
	}
	rv = vm_map_check_protection(&curproc->p_vmspace->vm_map,
	    trunc_page((vm_offset_t)addr), round_page((vm_offset_t)addr + len),
	    prot);
	return (rv == TRUE);
}

/*
 * MPSAFE
 */
void
vslock(addr, len)
	caddr_t addr;
	u_int len;
{

	vm_map_wire(&curproc->p_vmspace->vm_map, trunc_page((vm_offset_t)addr),
	    round_page((vm_offset_t)addr + len), FALSE);
}

/*
 * MPSAFE
 */
void
vsunlock(addr, len)
	caddr_t addr;
	u_int len;
{

	vm_map_unwire(&curproc->p_vmspace->vm_map,
	    trunc_page((vm_offset_t)addr),
	    round_page((vm_offset_t)addr + len), FALSE);
}

/*
 * Create the U area for a new process.
 * This routine directly affects the fork perf for a process.
 */
void
vm_proc_new(struct proc *p)
{
	vm_page_t ma[UAREA_PAGES];
	vm_object_t upobj;
	vm_offset_t up;
	vm_page_t m;
	u_int i;

	/*
	 * Allocate object for the upage.
	 */
	upobj = vm_object_allocate(OBJT_DEFAULT, UAREA_PAGES);
	p->p_upages_obj = upobj;

	/*
	 * Get a kernel virtual address for the U area for this process.
	 */
	up = kmem_alloc_nofault(kernel_map, UAREA_PAGES * PAGE_SIZE);
	if (up == 0)
		panic("vm_proc_new: upage allocation failed");
	p->p_uarea = (struct user *)up;

	for (i = 0; i < UAREA_PAGES; i++) {
		/*
		 * Get a uarea page.
		 */
		m = vm_page_grab(upobj, i, VM_ALLOC_NORMAL | VM_ALLOC_RETRY);
		ma[i] = m;

		/*
		 * Wire the page.
		 */
		m->wire_count++;
		cnt.v_wire_count++;

		vm_page_wakeup(m);
		vm_page_flag_clear(m, PG_ZERO);
		vm_page_flag_set(m, PG_MAPPED | PG_WRITEABLE);
		m->valid = VM_PAGE_BITS_ALL;
	}

	/*
	 * Enter the pages into the kernel address space.
	 */
	pmap_qenter(up, ma, UAREA_PAGES);
}

/*
 * Dispose the U area for a process that has exited.
 * This routine directly impacts the exit perf of a process.
 * XXX proc_zone is marked UMA_ZONE_NOFREE, so this should never be called.
 */
void
vm_proc_dispose(struct proc *p)
{
	vm_object_t upobj;
	vm_offset_t up;
	vm_page_t m;
	int i;

	upobj = p->p_upages_obj;
	up = (vm_offset_t)p->p_uarea;
	for (i = 0; i < UAREA_PAGES; i++) {
		m = vm_page_lookup(upobj, i);
		if (m == NULL)
			panic("vm_proc_dispose: upage already missing?");
		vm_page_busy(m);
		vm_page_unwire(m, 0);
		vm_page_free(m);
	}
	pmap_qremove(up, UAREA_PAGES);
	kmem_free(kernel_map, up, UAREA_PAGES * PAGE_SIZE);
	p->p_upages_obj = NULL;
	vm_object_deallocate(upobj);
}

#ifndef NO_SWAPPING
/*
 * Allow the U area for a process to be prejudicially paged out.
 */
void
vm_proc_swapout(struct proc *p)
{
	vm_object_t upobj;
	vm_offset_t up;
	vm_page_t m;
	int i;

	upobj = p->p_upages_obj;
	up = (vm_offset_t)p->p_uarea;
	for (i = 0; i < UAREA_PAGES; i++) {
		m = vm_page_lookup(upobj, i);
		if (m == NULL)
			panic("vm_proc_swapout: upage already missing?");
		vm_page_dirty(m);
		vm_page_unwire(m, 0);
	}
	pmap_qremove(up, UAREA_PAGES);
}

/*
 * Bring the U area for a specified process back in.
 */
void
vm_proc_swapin(struct proc *p)
{
	vm_page_t ma[UAREA_PAGES];
	vm_object_t upobj;
	vm_offset_t up;
	vm_page_t m;
	int rv;
	int i;

	upobj = p->p_upages_obj;
	up = (vm_offset_t)p->p_uarea;
	for (i = 0; i < UAREA_PAGES; i++) {
		m = vm_page_grab(upobj, i, VM_ALLOC_NORMAL | VM_ALLOC_RETRY);
		if (m->valid != VM_PAGE_BITS_ALL) {
			rv = vm_pager_get_pages(upobj, &m, 1, 0);
			if (rv != VM_PAGER_OK)
				panic("vm_proc_swapin: cannot get upage");
			m = vm_page_lookup(upobj, i);
			m->valid = VM_PAGE_BITS_ALL;
		}
		ma[i] = m;
		vm_page_wire(m);
		vm_page_wakeup(m);
		vm_page_flag_set(m, PG_MAPPED | PG_WRITEABLE);
	}
	pmap_qenter(up, ma, UAREA_PAGES);
}
#endif

/*
 * Implement fork's actions on an address space.
 * Here we arrange for the address space to be copied or referenced,
 * allocate a user struct (pcb and kernel stack), then call the
 * machine-dependent layer to fill those in and make the new process
 * ready to run.  The new process is set up so that it returns directly
 * to user mode to avoid stack copying and relocation problems.
 */
void
vm_forkproc(td, p2, td2, flags)
	struct thread *td;
	struct proc *p2;
	struct thread *td2;
	int flags;
{
	struct proc *p1 = td->td_proc;
	struct user *up;

	GIANT_REQUIRED;

	if ((flags & RFPROC) == 0) {
		/*
		 * Divorce the memory, if it is shared, essentially
		 * this changes shared memory amongst threads, into
		 * COW locally.
		 */
		if ((flags & RFMEM) == 0) {
			if (p1->p_vmspace->vm_refcnt > 1) {
				vmspace_unshare(p1);
			}
		}
		cpu_fork(td, p2, td2, flags);
		return;
	}

	if (flags & RFMEM) {
		p2->p_vmspace = p1->p_vmspace;
		p1->p_vmspace->vm_refcnt++;
	}

	while (vm_page_count_severe()) {
		VM_WAIT;
	}

	if ((flags & RFMEM) == 0) {
		p2->p_vmspace = vmspace_fork(p1->p_vmspace);

		pmap_pinit2(vmspace_pmap(p2->p_vmspace));

		if (p1->p_vmspace->vm_shm)
			shmfork(p1, p2);
	}

	/* XXXKSE this is unsatisfactory but should be adequate */
	up = p2->p_uarea;

	/*
	 * p_stats currently points at fields in the user struct
	 * but not at &u, instead at p_addr. Copy parts of
	 * p_stats; zero the rest of p_stats (statistics).
	 *
	 * If procsig->ps_refcnt is 1 and p2->p_sigacts is NULL we dont' need
	 * to share sigacts, so we use the up->u_sigacts.
	 */
	p2->p_stats = &up->u_stats;
	if (p2->p_sigacts == NULL) {
		if (p2->p_procsig->ps_refcnt != 1)
			printf ("PID:%d NULL sigacts with refcnt not 1!\n",p2->p_pid);
		p2->p_sigacts = &up->u_sigacts;
		up->u_sigacts = *p1->p_sigacts;
	}

	bzero(&up->u_stats.pstat_startzero,
	    (unsigned) ((caddr_t) &up->u_stats.pstat_endzero -
		(caddr_t) &up->u_stats.pstat_startzero));
	bcopy(&p1->p_stats->pstat_startcopy, &up->u_stats.pstat_startcopy,
	    ((caddr_t) &up->u_stats.pstat_endcopy -
		(caddr_t) &up->u_stats.pstat_startcopy));


	/*
	 * cpu_fork will copy and update the pcb, set up the kernel stack,
	 * and make the child ready to run.
	 */
	cpu_fork(td, p2, td2, flags);
}

/*
 * Called after process has been wait(2)'ed apon and is being reaped.
 * The idea is to reclaim resources that we could not reclaim while
 * the process was still executing.
 */
void
vm_waitproc(p)
	struct proc *p;
{
	struct thread *td;

	GIANT_REQUIRED;
	cpu_wait(p);
/* XXXKSE by here there should not be any threads left! */
	FOREACH_THREAD_IN_PROC(p, td) {
		panic("vm_waitproc: Survivor thread!");
	}
	vmspace_exitfree(p);		/* and clean-out the vmspace */
}

/*
 * Set default limits for VM system.
 * Called for proc 0, and then inherited by all others.
 *
 * XXX should probably act directly on proc0.
 */
static void
vm_init_limits(udata)
	void *udata;
{
	struct proc *p = udata;
	int rss_limit;

	/*
	 * Set up the initial limits on process VM. Set the maximum resident
	 * set size to be half of (reasonably) available memory.  Since this
	 * is a soft limit, it comes into effect only when the system is out
	 * of memory - half of main memory helps to favor smaller processes,
	 * and reduces thrashing of the object cache.
	 */
	p->p_rlimit[RLIMIT_STACK].rlim_cur = dflssiz;
	p->p_rlimit[RLIMIT_STACK].rlim_max = maxssiz;
	p->p_rlimit[RLIMIT_DATA].rlim_cur = dfldsiz;
	p->p_rlimit[RLIMIT_DATA].rlim_max = maxdsiz;
	/* limit the limit to no less than 2MB */
	rss_limit = max(cnt.v_free_count, 512);
	p->p_rlimit[RLIMIT_RSS].rlim_cur = ptoa(rss_limit);
	p->p_rlimit[RLIMIT_RSS].rlim_max = RLIM_INFINITY;
}

void
faultin(p)
	struct proc *p;
{

	GIANT_REQUIRED;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	mtx_lock_spin(&sched_lock);
#ifdef NO_SWAPPING
	if ((p->p_sflag & PS_INMEM) == 0)
		panic("faultin: proc swapped out with NO_SWAPPING!");
#else
	if ((p->p_sflag & PS_INMEM) == 0) {
		struct thread *td;

		++p->p_lock;
		mtx_unlock_spin(&sched_lock);
		PROC_UNLOCK(p);

		vm_proc_swapin(p);
		FOREACH_THREAD_IN_PROC (p, td)
			pmap_swapin_thread(td);

		PROC_LOCK(p);
		mtx_lock_spin(&sched_lock);
		FOREACH_THREAD_IN_PROC (p, td)
			if (td->td_state == TDS_RUNQ)	/* XXXKSE */
				setrunqueue(td);

		p->p_sflag |= PS_INMEM;

		/* undo the effect of setting SLOCK above */
		--p->p_lock;
	}
#endif
	mtx_unlock_spin(&sched_lock);
}

/*
 * This swapin algorithm attempts to swap-in processes only if there
 * is enough space for them.  Of course, if a process waits for a long
 * time, it will be swapped in anyway.
 *
 *  XXXKSE - process with the thread with highest priority counts..
 *
 * Giant is still held at this point, to be released in tsleep.
 */
/* ARGSUSED*/
static void
scheduler(dummy)
	void *dummy;
{
	struct proc *p;
	struct thread *td;
	int pri;
	struct proc *pp;
	int ppri;

	mtx_assert(&Giant, MA_OWNED | MA_NOTRECURSED);
	/* GIANT_REQUIRED */

loop:
	if (vm_page_count_min()) {
		VM_WAIT;
		goto loop;
	}

	pp = NULL;
	ppri = INT_MIN;
	sx_slock(&allproc_lock);
	FOREACH_PROC_IN_SYSTEM(p) {
		struct ksegrp *kg;
		if (p->p_sflag & (PS_INMEM | PS_SWAPPING)) {
			continue;
		}
		mtx_lock_spin(&sched_lock);
		FOREACH_THREAD_IN_PROC(p, td) {
			/* Only consider runnable threads */
			if (td->td_state == TDS_RUNQ) {
				kg = td->td_ksegrp;
				pri = p->p_swtime + kg->kg_slptime;
				if ((p->p_sflag & PS_SWAPINREQ) == 0) {
					pri -= kg->kg_nice * 8;
				}

				/*
				 * if this ksegrp is higher priority
				 * and there is enough space, then select
				 * this process instead of the previous
				 * selection.
				 */
				if (pri > ppri) {
					pp = p;
					ppri = pri;
				}
			}
		}
		mtx_unlock_spin(&sched_lock);
	}
	sx_sunlock(&allproc_lock);

	/*
	 * Nothing to do, back to sleep.
	 */
	if ((p = pp) == NULL) {
		tsleep(&proc0, PVM, "sched", maxslp * hz / 2);
		goto loop;
	}
	mtx_lock_spin(&sched_lock);
	p->p_sflag &= ~PS_SWAPINREQ;
	mtx_unlock_spin(&sched_lock);

	/*
	 * We would like to bring someone in. (only if there is space).
	 * [What checks the space? ]
	 */
	PROC_LOCK(p);
	faultin(p);
	PROC_UNLOCK(p);
	mtx_lock_spin(&sched_lock);
	p->p_swtime = 0;
	mtx_unlock_spin(&sched_lock);
	goto loop;
}

#ifndef NO_SWAPPING

/*
 * Swap_idle_threshold1 is the guaranteed swapped in time for a process
 */
static int swap_idle_threshold1 = 2;
SYSCTL_INT(_vm, OID_AUTO, swap_idle_threshold1,
	CTLFLAG_RW, &swap_idle_threshold1, 0, "");

/*
 * Swap_idle_threshold2 is the time that a process can be idle before
 * it will be swapped out, if idle swapping is enabled.
 */
static int swap_idle_threshold2 = 10;
SYSCTL_INT(_vm, OID_AUTO, swap_idle_threshold2,
	CTLFLAG_RW, &swap_idle_threshold2, 0, "");

/*
 * Swapout is driven by the pageout daemon.  Very simple, we find eligible
 * procs and unwire their u-areas.  We try to always "swap" at least one
 * process in case we need the room for a swapin.
 * If any procs have been sleeping/stopped for at least maxslp seconds,
 * they are swapped.  Else, we swap the longest-sleeping or stopped process,
 * if any, otherwise the longest-resident process.
 */
void
swapout_procs(action)
int action;
{
	struct proc *p;
	struct thread *td;
	struct ksegrp *kg;
	struct proc *outp, *outp2;
	int outpri, outpri2;
	int didswap = 0;

	GIANT_REQUIRED;

	outp = outp2 = NULL;
	outpri = outpri2 = INT_MIN;
retry:
	sx_slock(&allproc_lock);
	FOREACH_PROC_IN_SYSTEM(p) {
		struct vmspace *vm;
		int minslptime = 100000;
		
		PROC_LOCK(p);
		if (p->p_lock != 0 ||
		    (p->p_flag & (P_STOPPED_SNGL|P_TRACED|P_SYSTEM|P_WEXIT)) != 0) {
			PROC_UNLOCK(p);
			continue;
		}
		/*
		 * only aiod changes vmspace, however it will be
		 * skipped because of the if statement above checking 
		 * for P_SYSTEM
		 */
		vm = p->p_vmspace;
		mtx_lock_spin(&sched_lock);
		if ((p->p_sflag & (PS_INMEM|PS_SWAPPING)) != PS_INMEM) {
			mtx_unlock_spin(&sched_lock);
			PROC_UNLOCK(p);
			continue;
		}

		switch (p->p_state) {
		default:
			/* Don't swap out processes in any sort
			 * of 'special' state. */
			mtx_unlock_spin(&sched_lock);
			PROC_UNLOCK(p);
			continue;

		case PRS_NORMAL:
			/*
			 * do not swapout a realtime process
			 * Check all the thread groups..
			 */
			FOREACH_KSEGRP_IN_PROC(p, kg) {
				if (PRI_IS_REALTIME(kg->kg_pri_class)) {
					mtx_unlock_spin(&sched_lock);
					PROC_UNLOCK(p);
					goto nextproc;
				}

				/*
				 * Do not swapout a process waiting
				 * on a critical event of some kind. 
				 * Also guarantee swap_idle_threshold1
				 * time in memory.
				 */
				if (kg->kg_slptime < swap_idle_threshold1) {
					mtx_unlock_spin(&sched_lock);
					PROC_UNLOCK(p);
					goto nextproc;
				}
				FOREACH_THREAD_IN_PROC(p, td) {
					if ((td->td_priority) < PSOCK) {
						mtx_unlock_spin(&sched_lock);
						PROC_UNLOCK(p);
						goto nextproc;
					}
				}
				/*
				 * If the system is under memory stress,
				 * or if we are swapping
				 * idle processes >= swap_idle_threshold2,
				 * then swap the process out.
				 */
				if (((action & VM_SWAP_NORMAL) == 0) &&
				    (((action & VM_SWAP_IDLE) == 0) ||
				    (kg->kg_slptime < swap_idle_threshold2))) {
					mtx_unlock_spin(&sched_lock);
					PROC_UNLOCK(p);
					goto nextproc;
				}
				if (minslptime > kg->kg_slptime)
					minslptime = kg->kg_slptime;
			}

			mtx_unlock_spin(&sched_lock);
			++vm->vm_refcnt;
			/*
			 * do not swapout a process that
			 * is waiting for VM
			 * data structures there is a
			 * possible deadlock.
			 */
			if (!vm_map_trylock(&vm->vm_map)) {
				vmspace_free(vm);
				PROC_UNLOCK(p);
				goto nextproc;
			}
			vm_map_unlock(&vm->vm_map);
			/*
			 * If the process has been asleep for awhile and had
			 * most of its pages taken away already, swap it out.
			 */
			if ((action & VM_SWAP_NORMAL) ||
				((action & VM_SWAP_IDLE) &&
				 (minslptime > swap_idle_threshold2))) {
				sx_sunlock(&allproc_lock);
				swapout(p);
				vmspace_free(vm);
				didswap++;
				goto retry;
			}
			PROC_UNLOCK(p);
			vmspace_free(vm);
		}
nextproc:
		continue;
	}
	sx_sunlock(&allproc_lock);
	/*
	 * If we swapped something out, and another process needed memory,
	 * then wakeup the sched process.
	 */
	if (didswap)
		wakeup(&proc0);
}

static void
swapout(p)
	struct proc *p;
{
	struct thread *td;

	PROC_LOCK_ASSERT(p, MA_OWNED);
#if defined(SWAP_DEBUG)
	printf("swapping out %d\n", p->p_pid);
#endif
	++p->p_stats->p_ru.ru_nswap;
	/*
	 * remember the process resident count
	 */
	p->p_vmspace->vm_swrss = vmspace_resident_count(p->p_vmspace);

	mtx_lock_spin(&sched_lock);
	p->p_sflag &= ~PS_INMEM;
	p->p_sflag |= PS_SWAPPING;
	PROC_UNLOCK(p);
	FOREACH_THREAD_IN_PROC (p, td)
		if (td->td_state == TDS_RUNQ)	/* XXXKSE */
			remrunqueue(td);	/* XXXKSE */
	mtx_unlock_spin(&sched_lock);

	vm_proc_swapout(p);
	FOREACH_THREAD_IN_PROC(p, td)
		pmap_swapout_thread(td);
	mtx_lock_spin(&sched_lock);
	p->p_sflag &= ~PS_SWAPPING;
	p->p_swtime = 0;
	mtx_unlock_spin(&sched_lock);
}
#endif /* !NO_SWAPPING */
