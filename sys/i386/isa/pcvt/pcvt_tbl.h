/*
 * Copyright (c) 1992, 1995 Hellmuth Michaelis.
 *
 * All rights reserved.
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
 *	This product includes software developed by Hellmuth Michaelis
 * 4. The name authors may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @(#)pcvt_tbl.h, 3.20, Last Edit-Date: [Sun Apr  2 18:59:19 1995]
 *
 */

/*---------------------------------------------------------------------------*
 *
 *	pcvt_tbl.h	VT220 Driver Character Set Conversion Tables
 *	------------------------------------------------------------
 *	-hm	splitting off pccons_out.c
 *	-hm	default tables for pure mda/hcg/cga
 *
 *	in pcvt_out.c, hooks are provided for the following charactersets:
 *
 *		HAVECS_BRITISH
 *		HAVECS_ASCII
 *		HAVECS_FINNISH
 *		HAVECS_NORWEGIANDANISH
 *		HAVECS_SWEDISH
 *		HAVECS_GERMAN
 *		HAVECS_FRENCHCANADA
 *		HAVECS_FRENCH
 *		HAVECS_ITALIAN
 *		HAVECS_SPANISH
 *		HAVECS_SPECIAL
 *		HAVECS_ALTERNATEROM1
 *		HAVECS_ALTERNATEROM2
 *		HAVECS_ROMAN8
 *		HAVECS_DUTCH
 *		HAVECS_SUPPLEMENTAL
 *		HAVECS_SWISS
 *		HAVECS_TECHNICAL
 *		HAVECS_ISOLATIN
 *
 *	to add support for a new charcterset, you have to provide the
 *	table named "cs_<charset>",define the according "HAVECS_<CHARSET>"
 *	and recompile everything. ref: pcvt_out.c, vt_designate()
 *
 *---------------------------------------------------------------------------*/

/*===========================================================================*
 *	DEFAULT TABLES FOR MDA/HCG/CGA
 *===========================================================================*/

/*---------------------------------------------------------------------------*
 *	ASCII Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSD_ASCII
u_short csd_ascii[CSSIZE] = {
/* 20 */	0x20 | CSL, 0x21 | CSL, 0x22 | CSL, 0x23 | CSL,
/* 24 */	0x24 | CSL, 0x25 | CSL, 0x26 | CSL, 0x27 | CSL,
/* 28 */	0x28 | CSL, 0x29 | CSL, 0x2A | CSL, 0x2B | CSL,
/* 2C */	0x2C | CSL, 0x2D | CSL, 0x2E | CSL, 0x2F | CSL,

/* 30 */	0x30 | CSL, 0x31 | CSL, 0x32 | CSL, 0x33 | CSL,
/* 34 */	0x34 | CSL, 0x35 | CSL, 0x36 | CSL, 0x37 | CSL,
/* 38 */	0x38 | CSL, 0x39 | CSL, 0x3A | CSL, 0x3B | CSL,
/* 3C */	0x3C | CSL, 0x3D | CSL, 0x3E | CSL, 0x3F | CSL,

/* 40 */	0x40 | CSL, 0x41 | CSL, 0x42 | CSL, 0x43 | CSL,
/* 44 */	0x44 | CSL, 0x45 | CSL, 0x46 | CSL, 0x47 | CSL,
/* 48 */	0x48 | CSL, 0x49 | CSL, 0x4A | CSL, 0x4B | CSL,
/* 4C */	0x4C | CSL, 0x4D | CSL, 0x4E | CSL, 0x4F | CSL,

/* 50 */	0x50 | CSL, 0x51 | CSL, 0x52 | CSL, 0x53 | CSL,
/* 54 */	0x54 | CSL, 0x55 | CSL, 0x56 | CSL, 0x57 | CSL,
/* 58 */	0x58 | CSL, 0x59 | CSL, 0x5A | CSL, 0x5B | CSL,
/* 5C */	0x5C | CSL, 0x5D | CSL, 0x5E | CSL, 0x5F | CSL,

/* 60 */	0x60 | CSL, 0x61 | CSL, 0x62 | CSL, 0x63 | CSL,
/* 64 */	0x64 | CSL, 0x65 | CSL, 0x66 | CSL, 0x67 | CSL,
/* 68 */	0x68 | CSL, 0x69 | CSL, 0x6A | CSL, 0x6B | CSL,
/* 6C */	0x6C | CSL, 0x6D | CSL, 0x6E | CSL, 0x6F | CSL,

/* 70 */	0x70 | CSL, 0x71 | CSL, 0x72 | CSL, 0x73 | CSL,
/* 74 */	0x74 | CSL, 0x75 | CSL, 0x76 | CSL, 0x77 | CSL,
/* 78 */	0x78 | CSL, 0x79 | CSL, 0x7A | CSL, 0x7B | CSL,
/* 7C */	0x7C | CSL, 0x7D | CSL, 0x7E | CSL, 0x7F | CSL,
};

/*---------------------------------------------------------------------------*
 *	DEC Supplemental Graphic Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSD_SUPPLEMENTAL
u_short csd_supplemental[CSSIZE] = {
/* 20 */	0x20 | CSL, 0xAD | CSL, 0x9B | CSL, 0x9C | CSL,
/* 24 */	0x20 | CSL, 0x9D | CSL, 0x20 | CSL, 0x20 | CSL,
/* 28 */	0x20 | CSL, 0x20 | CSL, 0xA6 | CSL, 0xAE | CSL,
/* 2C */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,

/* 30 */	0xF8 | CSL, 0xF1 | CSL, 0xFD | CSL, 0x20 | CSL,
/* 34 */	0x20 | CSL, 0xE6 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 38 */	0x20 | CSL, 0x20 | CSL, 0xA7 | CSL, 0xAF | CSL,
/* 3C */	0xAC | CSL, 0xAB | CSL, 0x20 | CSL, 0xA8 | CSL,

/* 40 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 44 */	0x8E | CSL, 0x8F | CSL, 0x92 | CSL, 0x80 | CSL,
/* 48 */	0x20 | CSL, 0x90 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 4C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 50 */	0x20 | CSL, 0xA5 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 54 */	0x20 | CSL, 0x20 | CSL, 0x99 | CSL, 0x20 | CSL,
/* 58 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 5C */	0x9A | CSL, 0x20 | CSL, 0x20 | CSL, 0xE1 | CSL,

/* 60 */	0x85 | CSL, 0xA0 | CSL, 0x83 | CSL, 0x20 | CSL,
/* 64 */	0x84 | CSL, 0x86 | CSL, 0x91 | CSL, 0x87 | CSL,
/* 68 */	0x8A | CSL, 0x82 | CSL, 0x88 | CSL, 0x89 | CSL,
/* 6C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 70 */	0x20 | CSL, 0xA4 | CSL, 0x95 | CSL, 0xA2 | CSL,
/* 74 */	0x93 | CSL, 0x20 | CSL, 0x94 | CSL, 0x20 | CSL,
/* 78 */	0x20 | CSL, 0x97 | CSL, 0xA3 | CSL, 0x96 | CSL,
/* 7C */	0x81 | CSL, 0x98 | CSL, 0x20 | CSL, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	DEC Special Graphic Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSD_SPECIAL
u_short csd_special[CSSIZE] = {
/* 20 */	0x20 | CSL, 0x21 | CSL, 0x22 | CSL, 0x23 | CSL,
/* 24 */	0x24 | CSL, 0x25 | CSL, 0x26 | CSL, 0x27 | CSL,
/* 28 */	0x28 | CSL, 0x29 | CSL, 0x2A | CSL, 0x2B | CSL,
/* 2C */	0x2C | CSL, 0x2D | CSL, 0x2E | CSL, 0x2F | CSL,

/* 30 */	0x30 | CSL, 0x31 | CSL, 0x32 | CSL, 0x33 | CSL,
/* 34 */	0x34 | CSL, 0x35 | CSL, 0x36 | CSL, 0x37 | CSL,
/* 38 */	0x38 | CSL, 0x39 | CSL, 0x3A | CSL, 0x3B | CSL,
/* 3C */	0x3C | CSL, 0x3D | CSL, 0x3E | CSL, 0x3F | CSL,

/* 40 */	0x40 | CSL, 0x41 | CSL, 0x42 | CSL, 0x43 | CSL,
/* 44 */	0x44 | CSL, 0x45 | CSL, 0x46 | CSL, 0x47 | CSL,
/* 48 */	0x48 | CSL, 0x49 | CSL, 0x4A | CSL, 0x4B | CSL,
/* 4C */	0x4C | CSL, 0x4D | CSL, 0x4E | CSL, 0x4F | CSL,

/* 50 */	0x50 | CSL, 0x51 | CSL, 0x52 | CSL, 0x53 | CSL,
/* 54 */	0x54 | CSL, 0x55 | CSL, 0x56 | CSL, 0x57 | CSL,
/* 58 */	0x58 | CSL, 0x59 | CSL, 0x5A | CSL, 0x5B | CSL,
/* 5C */	0x5C | CSL, 0x5D | CSL, 0x5E | CSL, 0x20 | CSL,

/* 60 */	0x20 | CSL, 0xB0 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 64 */	0x20 | CSL, 0x20 | CSL, 0xF8 | CSL, 0xF1 | CSL,
/* 68 */	0x20 | CSL, 0x20 | CSL, 0xD9 | CSL, 0xBF | CSL,
/* 6C */	0xDA | CSL, 0xC0 | CSL, 0xC5 | CSL, 0x20 | CSL,

/* 70 */	0x20 | CSL, 0xC4 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 74 */	0xC3 | CSL, 0xB4 | CSL, 0xC1 | CSL, 0xC2 | CSL,
/* 78 */	0xB3 | CSL, 0xF3 | CSL, 0xF2 | CSL, 0xE3 | CSL,
/* 7C */	0x20 | CSL, 0x9C | CSL, 0x20 | CSL, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	DEC Technical Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSD_TECHNICAL
u_short csd_technical[CSSIZE] = {
/* 20 */	0xFE | CSH, 0xFB | CSL, 0xDA | CSL, 0xC4 | CSL,
/* 24 */	0xF4 | CSL, 0xF5 | CSL, 0xB3 | CSL, 0xDA | CSL,
/* 28 */	0xC0 | CSL, 0xBF | CSL, 0xD9 | CSL, 0x20 | CSL,
/* 2C */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,

/* 30 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 34 */	0x20 | CSL, 0xAA | CSL, 0xA9 | CSL, 0x3E | CSL,
/* 38 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 3C */	0xF3 | CSL, 0x20 | CSL, 0xF2 | CSL, 0x20 | CSL,

/* 40 */	0x20 | CSL, 0x20 | CSL, 0xEC | CSL, 0xF6 | CSL,
/* 44 */	0x20 | CSL, 0x20 | CSL, 0xE8 | CSL, 0xE2 | CSL,
/* 48 */	0x20 | CSL, 0xF7 | CSL, 0xE9 | CSL, 0x78 | CSL,
/* 4C */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0xF0 | CSL,

/* 50 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0xE4 | CSL,
/* 54 */	0x20 | CSL, 0x20 | CSL, 0xFB | CSL, 0xEA | CSL,
/* 58 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 5C */	0xEF | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,

/* 60 */	0xAA | CSL, 0xE0 | CSL, 0xE1 | CSL, 0x20 | CSL,
/* 64 */	0xEB | CSL, 0x20 | CSL, 0xED | CSL, 0x59 | CSL,
/* 68 */	0x20 | CSL, 0x20 | CSL, 0xE9 | CSL, 0x20 | CSL,
/* 6C */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,

/* 70 */	0xE3 | CSL, 0x20 | CSL, 0x20 | CSL, 0xE5 | CSL,
/* 74 */	0xE7 | CSL, 0x20 | CSL, 0x9F | CSL, 0x20 | CSL,
/* 78 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 7C */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	ISO Latin-1 Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSD_ISOLATIN
u_short csd_isolatin[CSSIZE] = {
/* 20 */	0x20 | CSL, 0xAD | CSL, 0x9B | CSL, 0x9C | CSL,
/* 24 */	0x20 | CSL, 0x9D | CSL, 0x7C | CSL, 0x20 | CSL,
/* 28 */	0x22 | CSL, 0x20 | CSL, 0xA6 | CSL, 0xAE | CSL,
/* 2C */	0xAA | CSL, 0x2D | CSL, 0x20 | CSL, 0x2D | CSL,

/* 30 */	0xF8 | CSL, 0xF1 | CSL, 0xFD | CSL, 0x20 | CSL,
/* 34 */	0x27 | CSL, 0xE6 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 38 */	0x20 | CSL, 0x20 | CSL, 0xA7 | CSL, 0xAF | CSL,
/* 3C */	0xAC | CSL, 0xAB | CSL, 0x20 | CSL, 0xA8 | CSL,

/* 40 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 44 */	0x8E | CSL, 0x8F | CSL, 0x92 | CSL, 0x80 | CSL,
/* 48 */	0x20 | CSL, 0x90 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 4C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 50 */	0x20 | CSL, 0xA5 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 54 */	0x20 | CSL, 0x20 | CSL, 0x99 | CSL, 0x78 | CSL,
/* 58 */	0x20 | CSL, 0x20 | CSL, 0x20 | CSL, 0x20 | CSL,
/* 5C */	0x9A | CSL, 0x20 | CSL, 0x20 | CSL, 0xE1 | CSL,

/* 60 */	0x85 | CSL, 0xA0 | CSL, 0x83 | CSL, 0x20 | CSL,
/* 64 */	0x84 | CSL, 0x86 | CSL, 0x91 | CSL, 0x87 | CSL,
/* 68 */	0x8A | CSL, 0x82 | CSL, 0x88 | CSL, 0x89 | CSL,
/* 6C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 70 */	0x20 | CSL, 0xA4 | CSL, 0x95 | CSL, 0xA2 | CSL,
/* 74 */	0x93 | CSL, 0x20 | CSL, 0x94 | CSL, 0xF6 | CSL,
/* 78 */	0x20 | CSL, 0x97 | CSL, 0xA3 | CSL, 0x96 | CSL,
/* 7C */	0x81 | CSL, 0x20 | CSL, 0x20 | CSL, 0x98 | CSL
};

/*===========================================================================*
 *	EXTENDED TABLES FOR EGA/VGA
 *===========================================================================*/

/*---------------------------------------------------------------------------*
 *	ASCII Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_ASCII
u_short cse_ascii[CSSIZE] = {
/* 20 */	0x20 | CSL, 0x21 | CSL, 0x22 | CSL, 0x23 | CSL,
/* 24 */	0x24 | CSL, 0x25 | CSL, 0x26 | CSL, 0x27 | CSL,
/* 28 */	0x28 | CSL, 0x29 | CSL, 0x2A | CSL, 0x2B | CSL,
/* 2C */	0x2C | CSL, 0x2D | CSL, 0x2E | CSL, 0x2F | CSL,

/* 30 */	0x30 | CSL, 0x31 | CSL, 0x32 | CSL, 0x33 | CSL,
/* 34 */	0x34 | CSL, 0x35 | CSL, 0x36 | CSL, 0x37 | CSL,
/* 38 */	0x38 | CSL, 0x39 | CSL, 0x3A | CSL, 0x3B | CSL,
/* 3C */	0x3C | CSL, 0x3D | CSL, 0x3E | CSL, 0x3F | CSL,

/* 40 */	0x40 | CSL, 0x41 | CSL, 0x42 | CSL, 0x43 | CSL,
/* 44 */	0x44 | CSL, 0x45 | CSL, 0x46 | CSL, 0x47 | CSL,
/* 48 */	0x48 | CSL, 0x49 | CSL, 0x4A | CSL, 0x4B | CSL,
/* 4C */	0x4C | CSL, 0x4D | CSL, 0x4E | CSL, 0x4F | CSL,

/* 50 */	0x50 | CSL, 0x51 | CSL, 0x52 | CSL, 0x53 | CSL,
/* 54 */	0x54 | CSL, 0x55 | CSL, 0x56 | CSL, 0x57 | CSL,
/* 58 */	0x58 | CSL, 0x59 | CSL, 0x5A | CSL, 0x5B | CSL,
/* 5C */	0x5C | CSL, 0x5D | CSL, 0x5E | CSL, 0x5F | CSL,

/* 60 */	0x60 | CSL, 0x61 | CSL, 0x62 | CSL, 0x63 | CSL,
/* 64 */	0x64 | CSL, 0x65 | CSL, 0x66 | CSL, 0x67 | CSL,
/* 68 */	0x68 | CSL, 0x69 | CSL, 0x6A | CSL, 0x6B | CSL,
/* 6C */	0x6C | CSL, 0x6D | CSL, 0x6E | CSL, 0x6F | CSL,

/* 70 */	0x70 | CSL, 0x71 | CSL, 0x72 | CSL, 0x73 | CSL,
/* 74 */	0x74 | CSL, 0x75 | CSL, 0x76 | CSL, 0x77 | CSL,
/* 78 */	0x78 | CSL, 0x79 | CSL, 0x7A | CSL, 0x7B | CSL,
/* 7C */	0x7C | CSL, 0x7D | CSL, 0x7E | CSL, 0xB0 | CSL,
};

/*---------------------------------------------------------------------------*
 *	DEC Supplemental Graphic Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_SUPPLEMENTAL
u_short cse_supplemental[CSSIZE] = {
/* 20 */	0x20 | CSL, 0xAD | CSL, 0x9B | CSL, 0x9C | CSL,
/* 24 */	0x9F | CSH, 0x67 | CSH, 0x9F | CSH, 0x15 | CSL,
/* 28 */	0x9D | CSH, 0x9C | CSH, 0xA6 | CSL, 0xAE | CSL,
/* 2C */	0x9F | CSH, 0x9F | CSH, 0x9F | CSH, 0x9F | CSH,

/* 30 */	0xF8 | CSL, 0xF1 | CSL, 0xFD | CSL, 0x9B | CSH,
/* 34 */	0x9F | CSH, 0xE6 | CSL, 0x14 | CSL, 0x99 | CSH,
/* 38 */	0x9F | CSH, 0x98 | CSH, 0xA7 | CSL, 0xAF | CSL,
/* 3C */	0xAC | CSL, 0xAB | CSL, 0x9F | CSH, 0xA8 | CSL,

/* 40 */	0x97 | CSH, 0x96 | CSH, 0x95 | CSH, 0x94 | CSH,
/* 44 */	0x8E | CSL, 0x8F | CSL, 0x92 | CSL, 0x80 | CSL,
/* 48 */	0x93 | CSH, 0x90 | CSL, 0x92 | CSH, 0x91 | CSH,
/* 4C */	0x90 | CSH, 0x8F | CSH, 0x8E | CSH, 0x8D | CSH,

/* 50 */	0x9F | CSH, 0xA5 | CSL, 0x8C | CSH, 0x8B | CSH,
/* 54 */	0x8A | CSH, 0x89 | CSH, 0x99 | CSL, 0x88 | CSH,
/* 58 */	0x87 | CSH, 0x86 | CSH, 0x85 | CSH, 0x84 | CSH,
/* 5C */	0x9A | CSL, 0x83 | CSH, 0x9F | CSH, 0xE1 | CSL,

/* 60 */	0x85 | CSL, 0xA0 | CSL, 0x83 | CSL, 0x82 | CSH,
/* 64 */	0x84 | CSL, 0x86 | CSL, 0x91 | CSL, 0x87 | CSL,
/* 68 */	0x8A | CSL, 0x82 | CSL, 0x88 | CSL, 0x89 | CSL,
/* 6C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 70 */	0x9F | CSH, 0xA4 | CSL, 0x95 | CSL, 0xA2 | CSL,
/* 74 */	0x93 | CSL, 0x81 | CSH, 0x94 | CSL, 0x80 | CSH,
/* 78 */	0x7F | CSH, 0x97 | CSL, 0xA3 | CSL, 0x96 | CSL,
/* 7C */	0x81 | CSL, 0x98 | CSL, 0x9F | CSH, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	DEC Special Graphic Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_SPECIAL
u_short cse_special[CSSIZE] = {
/* 20 */	0x20 | CSL, 0x21 | CSL, 0x22 | CSL, 0x23 | CSL,
/* 24 */	0x24 | CSL, 0x25 | CSL, 0x26 | CSL, 0x27 | CSL,
/* 28 */	0x28 | CSL, 0x29 | CSL, 0x2A | CSL, 0x2B | CSL,
/* 2C */	0x2C | CSL, 0x2D | CSL, 0x2E | CSL, 0x2F | CSL,

/* 30 */	0x30 | CSL, 0x31 | CSL, 0x32 | CSL, 0x33 | CSL,
/* 34 */	0x34 | CSL, 0x35 | CSL, 0x36 | CSL, 0x37 | CSL,
/* 38 */	0x38 | CSL, 0x39 | CSL, 0x3A | CSL, 0x3B | CSL,
/* 3C */	0x3C | CSL, 0x3D | CSL, 0x3E | CSL, 0x3F | CSL,

/* 40 */	0x40 | CSL, 0x41 | CSL, 0x42 | CSL, 0x43 | CSL,
/* 44 */	0x44 | CSL, 0x45 | CSL, 0x46 | CSL, 0x47 | CSL,
/* 48 */	0x48 | CSL, 0x49 | CSL, 0x4A | CSL, 0x4B | CSL,
/* 4C */	0x4C | CSL, 0x4D | CSL, 0x4E | CSL, 0x4F | CSL,

/* 50 */	0x50 | CSL, 0x51 | CSL, 0x52 | CSL, 0x53 | CSL,
/* 54 */	0x54 | CSL, 0x55 | CSL, 0x56 | CSL, 0x57 | CSL,
/* 58 */	0x58 | CSL, 0x59 | CSL, 0x5A | CSL, 0x5B | CSL,
/* 5C */	0x5C | CSL, 0x5D | CSL, 0x5E | CSL, 0x20 | CSL,

/* 60 */	0x04 | CSL, 0xB0 | CSL, 0x09 | CSH, 0x0C | CSH,
/* 64 */	0x0D | CSH, 0x0A | CSH, 0xF8 | CSL, 0xF1 | CSL,
/* 68 */	0x00 | CSH, 0x0B | CSH, 0xD9 | CSL, 0xBF | CSL,
/* 6C */	0xDA | CSL, 0xC0 | CSL, 0xC5 | CSL, 0x7D | CSH,

/* 70 */	0x7C | CSH, 0x7B | CSH, 0x7A | CSH, 0x79 | CSH,
/* 74 */	0xC3 | CSL, 0xB4 | CSL, 0xC1 | CSL, 0xC2 | CSL,
/* 78 */	0xB3 | CSL, 0xF3 | CSL, 0xF2 | CSL, 0xE3 | CSL,
/* 7C */	0x78 | CSH, 0x9C | CSL, 0x99 | CSH, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	DEC Technical Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_TECHNICAL
u_short cse_technical[CSSIZE] = {
/* 20 */	0x20 | CSL, 0x65 | CSH, 0xDA | CSL, 0xC4 | CSL,
/* 24 */	0xF4 | CSL, 0xF5 | CSL, 0xB3 | CSL, 0xDA | CSL,
/* 28 */	0xC0 | CSL, 0xBF | CSL, 0xD9 | CSL, 0x61 | CSH,
/* 2C */	0x62 | CSH, 0x63 | CSH, 0x64 | CSH, 0x5F | CSH,

/* 30 */	0x60 | CSH, 0x5E | CSH, 0x5D | CSH, 0x5C | CSH,
/* 34 */	0x5B | CSH, 0xAA | CSL, 0xA9 | CSL, 0x3E | CSL,
/* 38 */	0x9F | CSH, 0x9F | CSH, 0x9F | CSH, 0x9F | CSH,
/* 3C */	0xF3 | CSL, 0x78 | CSH, 0xF2 | CSL, 0x5A | CSH,

/* 40 */	0x59 | CSH, 0x58 | CSH, 0xEC | CSL, 0xF6 | CSL,
/* 44 */	0x57 | CSH, 0x56 | CSH, 0xE8 | CSL, 0xE2 | CSL,
/* 48 */	0x77 | CSH, 0x55 | CSH, 0x54 | CSH, 0x6E | CSH,
/* 4C */	0x53 | CSH, 0x52 | CSH, 0x51 | CSH, 0xF0 | CSL,

/* 50 */	0x50 | CSH, 0x4F | CSH, 0x9F | CSH, 0xE4 | CSL,
/* 54 */	0x9F | CSH, 0x9F | CSH, 0xFB | CSL, 0xEA | CSL,
/* 58 */	0x4E | CSH, 0x4D | CSH, 0x4C | CSH, 0x4B | CSH,
/* 5C */	0xEF | CSL, 0x4A | CSH, 0x49 | CSH, 0x48 | CSH,

/* 60 */	0xAA | CSL, 0xE0 | CSL, 0xE1 | CSL, 0x47 | CSH,
/* 64 */	0xEB | CSL, 0x46 | CSH, 0xED | CSL, 0x59 | CSL,
/* 68 */	0x45 | CSH, 0x44 | CSH, 0xE9 | CSL, 0x9E | CSH,
/* 6C */	0x43 | CSH, 0x9F | CSH, 0x76 | CSL, 0x42 | CSH,

/* 70 */	0xE3 | CSL, 0x41 | CSH, 0x40 | CSH, 0xE5 | CSL,
/* 74 */	0xE7 | CSL, 0x9F | CSH, 0x9F | CSL, 0x66 | CSH,
/* 78 */	0x68 | CSH, 0x7E | CSH, 0x9A | CSH, 0x1B | CSL,
/* 7C */	0x18 | CSL, 0x1A | CSL, 0x19 | CSL, 0x20 | CSL
};

/*---------------------------------------------------------------------------*
 *	ISO Latin-1 Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_ISOLATIN
u_short cse_isolatin[CSSIZE] = {
/* 20 */	0x20 | CSL, 0xAD | CSL, 0x9B | CSL, 0x9C | CSL,
/* 24 */	0x9D | CSH, 0x9D | CSL, 0x7C | CSL, 0x15 | CSL,
/* 28 */	0x77 | CSH, 0x9C | CSH, 0xA6 | CSL, 0xAE | CSL,
/* 2C */	0x76 | CSH, 0x75 | CSH, 0x74 | CSH, 0x73 | CSH,

/* 30 */	0xF8 | CSL, 0xF1 | CSL, 0xFD | CSL, 0x9B | CSH,
/* 34 */	0x72 | CSH, 0xE6 | CSL, 0x14 | CSL, 0x99 | CSH,
/* 38 */	0x71 | CSH, 0x98 | CSH, 0xA7 | CSL, 0xAF | CSL,
/* 3C */	0xAC | CSL, 0xAB | CSL, 0x70 | CSH, 0xA8 | CSL,

/* 40 */	0x97 | CSH, 0x96 | CSH, 0x95 | CSH, 0x94 | CSH,
/* 44 */	0x8E | CSL, 0x8F | CSL, 0x92 | CSL, 0x80 | CSL,
/* 48 */	0x93 | CSH, 0x90 | CSL, 0x92 | CSH, 0x91 | CSH,
/* 4C */	0x90 | CSH, 0x8F | CSH, 0x8E | CSH, 0x8D | CSH,

/* 50 */	0x6F | CSH, 0xA5 | CSL, 0x8C | CSH, 0x8B | CSH,
/* 54 */	0x8A | CSH, 0x89 | CSH, 0x99 | CSL, 0x6E | CSH,
/* 58 */	0x87 | CSH, 0x86 | CSH, 0x85 | CSH, 0x84 | CSH,
/* 5C */	0x9A | CSL, 0x6D | CSH, 0x6C | CSH, 0xE1 | CSL,

/* 60 */	0x85 | CSL, 0xA0 | CSL, 0x83 | CSL, 0x82 | CSH,
/* 64 */	0x84 | CSL, 0x86 | CSL, 0x91 | CSL, 0x87 | CSL,
/* 68 */	0x8A | CSL, 0x82 | CSL, 0x88 | CSL, 0x89 | CSL,
/* 6C */	0x8D | CSL, 0xA1 | CSL, 0x8C | CSL, 0x8B | CSL,

/* 70 */	0x6B | CSH, 0xA4 | CSL, 0x95 | CSL, 0xA2 | CSL,
/* 74 */	0x93 | CSL, 0x81 | CSH, 0x94 | CSL, 0xF6 | CSL,
/* 78 */	0x7F | CSH, 0x97 | CSL, 0xA3 | CSL, 0x96 | CSL,
/* 7C */	0x81 | CSL, 0x69 | CSH, 0x6A | CSH, 0x98 | CSL
};

/*---------------------------------------------------------------------------*
 *	Downloadable Characterset
 *---------------------------------------------------------------------------*/
#define HAVECSE_DOWNLOADABLE
u_short cse_downloadable[CSSIZE] = {
/* 20 */	0xA0 | CSH, 0xA1 | CSH, 0xA2 | CSH, 0xA3 | CSH,
/* 24 */	0xA4 | CSH, 0xA5 | CSH, 0xA6 | CSH, 0xA7 | CSH,
/* 28 */	0xA8 | CSH, 0xA9 | CSH, 0xAA | CSH, 0xAB | CSH,
/* 2C */	0xAC | CSH, 0xAD | CSH, 0xAE | CSH, 0xAF | CSH,

/* 30 */	0xB0 | CSH, 0xB1 | CSH, 0xB2 | CSH, 0xB3 | CSH,
/* 34 */	0xB4 | CSH, 0xB5 | CSH, 0xB6 | CSH, 0xB7 | CSH,
/* 38 */	0xB8 | CSH, 0xB9 | CSH, 0xBA | CSH, 0xBB | CSH,
/* 3C */	0xBC | CSH, 0xBD | CSH, 0xBE | CSH, 0xBF | CSH,

/* 40 */	0xC0 | CSH, 0xC1 | CSH, 0xC2 | CSH, 0xC3 | CSH,
/* 44 */	0xC4 | CSH, 0xC5 | CSH, 0xC6 | CSH, 0xC7 | CSH,
/* 48 */	0xC8 | CSH, 0xC9 | CSH, 0xCA | CSH, 0xCB | CSH,
/* 4C */	0xCC | CSH, 0xCD | CSH, 0xCE | CSH, 0xCF | CSH,

/* 50 */	0xD0 | CSH, 0xD1 | CSH, 0xD2 | CSH, 0xD3 | CSH,
/* 54 */	0xD4 | CSH, 0xD5 | CSH, 0xD6 | CSH, 0xD7 | CSH,
/* 58 */	0xD8 | CSH, 0xD9 | CSH, 0xDA | CSH, 0xDB | CSH,
/* 5C */	0xDC | CSH, 0xDD | CSH, 0xDE | CSH, 0xDF | CSH,

/* 60 */	0xE0 | CSH, 0xE1 | CSH, 0xE2 | CSH, 0xE3 | CSH,
/* 64 */	0xE4 | CSH, 0xE5 | CSH, 0xE6 | CSH, 0xE7 | CSH,
/* 68 */	0xE8 | CSH, 0xE9 | CSH, 0xEA | CSH, 0xEB | CSH,
/* 6C */	0xEC | CSH, 0xED | CSH, 0xEE | CSH, 0xEF | CSH,

/* 70 */	0xF0 | CSH, 0xF1 | CSH, 0xF2 | CSH, 0xF3 | CSH,
/* 74 */	0xF4 | CSH, 0xF5 | CSH, 0xF6 | CSH, 0xF7 | CSH,
/* 78 */	0xF8 | CSH, 0xF9 | CSH, 0xFA | CSH, 0xFB | CSH,
/* 7C */	0xFC | CSH, 0xFD | CSH, 0xFE | CSH, 0xFF | CSH,
};

/* ------------------------- E O F ------------------------------------------*/
