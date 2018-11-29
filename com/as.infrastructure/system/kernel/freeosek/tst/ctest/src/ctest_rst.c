/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief Free OSEK Conformance Test Result
 **
 ** \file FreeOSEK/tst/ctest/src/ctest_rst_tm_01.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_CT Conformance Test
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090406 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "ctest.h"		/* include ctest header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8 TestResults[35];


const uint8 TestResultsOk[35] =
	{
#if (defined ctest_tm_01)
	  ( OK << 0 )			/* TM_01 index 00 */
#else
	  ( INIT << 0 )		/* TM_01 index 00 */
#endif
#if (defined ctest_tm_02)
	| ( OK << 2 )			/* TM_02 index 01*/
#else
	| ( INIT << 2 )		/* TM_02 index 01*/
#endif
#if (defined ctest_tm_03)
	| ( OK << 4 )			/* TM_03 index 02*/
#else
	| ( INIT << 4 )		/* TM_03 index 02*/
#endif
#if (defined ctest_tm_03)
	| ( OK << 6 ),			/* TM_04 index 03 */
#else
	| ( INIT << 6 ),		/* TM_04 index 03*/
#endif
#if (defined ctest_tm_08)
	  ( OK << 0 )			/* TM_05 index 04 */
#else
	  ( INIT << 0 )		/* TM_05 index 04*/
#endif
#if (defined ctest_tm_04)
	| ( OK << 2 )			/* TM_06 index 05 */
#else
	| ( INIT << 2 )		/* TM_06 index 05*/
#endif
#if (defined ctest_tm_05)
	| ( OK << 4 )			/* TM_07 index 06 */
#else
	| ( INIT << 4 )		/* TM_07 index 06 */
#endif
#if (defined ctest_tm_05)
	| ( OK << 6 ),			/* TM_08 index 07 */
#else
	| ( INIT << 6 ),		/* TM_08 index 07 */
#endif
#if (defined ctest_tm_10)
	  ( OK << 0 )			/* TM_09 index 08 */
#else
	  ( INIT << 0 )		/* TM_09 index 08 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 2 )			/* TM_10 index 09 */
#else
	| ( INIT << 2 )		/* TM_10 index 09 */
#endif
#if (defined ctest_tm_06)
	| ( OK << 4 )			/* TM_11 index 10 */
#else
	| ( INIT << 4 )		/* TM_11 index 10 */
#endif
#if (defined ctest_tm_07)
	| ( OK << 6 ),			/* TM_12 index 11 */
#else
	| ( INIT << 6 ),		/* TM_12 index 11 */
#endif
#if (defined ctest_tm_08)
	  ( OK << 0 )			/* TM_13 index 12 */
#else
	  ( INIT << 0 )		/* TM_13 index 12 */
#endif
#if (defined ctest_tm_08)
	| ( OK << 2 )			/* TM_14 index 13 */
#else
	| ( INIT << 2 )		/* TM_14 index 13 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 4 )			/* TM_15 index 14 */
#else
	| ( INIT << 4 )		/* TM_15 index 14 */
#endif
#if (defined ctest_tm_06)
	| ( OK << 6 ),			/* TM_16 index 15 */
#else
	| ( INIT << 6 ),		/* TM_16 index 15 */
#endif
#if (defined ctest_tm_07)
	  ( OK << 0 )			/* TM_17 index 16 */
#else
	  ( INIT << 0 )		/* TM_17 index 16 */
#endif
#if (defined ctest_tm_08)
	| ( OK << 2 )			/* TM_18 index 17 */
#else
	| ( INIT << 2 )		/* TM_18 index 17 */
#endif
#if (defined ctest_tm_06)
	| ( OK << 4 )			/* TM_19 index 18 */
#else
	| ( INIT << 4 )		/* TM_19 index 18 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 6 ),			/* TM_20 index 19 */
#else
	| ( INIT << 6 ),		/* TM_20 index 19 */
#endif
#if ( (defined ctest_tm_01) && (ISR_CATEGORY_3 == ENABLE) )
	  ( OK << 0 )			/* TM_21 index 20 */
#else
	  ( INIT << 0 )		/* TM_21 index 20 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 2 )			/* TM_22 index 21 */
#else
	| ( INIT << 2 )		/* TM_22 index 21 */
#endif
#if (defined ctest_tm_09)
	| ( OK << 4 )			/* TM_23 index 22 */
#else
	| ( INIT << 4 )		/* TM_23 index 22 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 6 ),			/* TM_24 index 23 */
#else
	| ( INIT << 6 ),		/* TM_24 index 23 */
#endif
#if (defined ctest_tm_01)
	  ( OK << 0 )			/* TM_25 index 24 */
#else
	  ( INIT << 0 )		/* TM_25 index 24 */
#endif
#if ( (defined ctest_tm_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 2 )			/* TM_26 index 25 */
#else
	| ( INIT << 2 )		/* TM_26 index 25 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 4 )			/* TM_27 index 26 */
#else
	| ( INIT << 4 )		/* TM_27 index 26 */
#endif
#if (defined ctest_tm_09)
	| ( OK << 6 ),			/* TM_28 index 27 */
#else
	| ( INIT << 6 ),		/* TM_28 index 27 */
#endif
#if (defined ctest_tm_09)
	  ( OK << 0 )			/* TM_29 index 28 */
#else
	  ( INIT << 0 )		/* TM_29 index 28 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 2 )			/* TM_30 index 29 */
#else
	| ( INIT << 2 )		/* TM_30 index 29 */
#endif
#if (defined ctest_tm_06)
	| ( OK << 4 )			/* TM_31 index 30 */
#else
	| ( INIT << 4 )		/* TM_31 index 30 */
#endif
#if (defined ctest_tm_07)
	| ( OK << 6 ),			/* TM_32 index 31 */
#else
	| ( INIT << 6 ),		/* TM_32 index 31 */
#endif
#if (defined ctest_tm_06)
	  ( OK << 0 )			/* TM_33 index 32 */
#else
	  ( INIT << 0 )		/* TM_33 index 32 */
#endif
#if (defined ctest_tm_02)
	| ( OK << 2 )			/* TM_34 index 33 */
#else
	| ( INIT << 2 )		/* TM_34 index 33 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 4 )			/* TM_35 index 34 */
#else
	| ( INIT << 4 )		/* TM_35 index 34 */
#endif
#if ( (defined ctest_tm_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 6 ),			/* TM_36 index 35 */
#else
	| ( INIT << 6 ),		/* TM_36 index 35 */
#endif
#if (defined ctest_tm_01)
	  ( OK << 0 )			/* TM_37 index 36 */
#else
	  ( INIT << 0 )		/* TM_37 index 36 */
#endif
#if ( (defined ctest_tm_01) && (ISR_CATEGORY_3 == ENABLE) )
	| ( OK << 2 )			/* TM_38 index 37 */
#else
	| ( INIT << 2 )		/* TM_38 index 37 */
#endif
#if (defined ctest_tm_09)
	| ( OK << 4 )			/* TM_39 index 38 */
#else
	| ( INIT << 4 )		/* TM_39 index 38 */
#endif
#if (defined ctest_tm_01)
	| ( OK << 6 ),			/* TM_40 index 39 */
#else
	| ( INIT << 6 ),		/* TM_40 index 39 */
#endif
#if (defined ctest_tm_09)
	  ( OK << 0 )			/* TM_41 index 40 */
#else
	  ( INIT << 0 )		/* TM_41 index 40 */
#endif
	| ( INIT << 2 )		/* IP_01 index 41 */
	| ( INIT << 4 )		/* IP_02 index 42 */
	| ( INIT << 6 ),		/* IP_03 index 43 */
	  ( INIT << 0 )		/* IP_04 index 44 */
	| ( INIT << 2 )		/* IP_05 index 45 */
	| ( INIT << 4 )		/* IP_06 index 46 */
	| ( INIT << 6 ),		/* IP_07 index 47 */
	  ( INIT << 0 )		/* IP_08 index 48 */
	| ( INIT << 2 )		/* IP_09 index 49 */
	| ( INIT << 4 )		/* IP_10 index 50 */
	| ( INIT << 6 ),		/* IP_11 index 51 */
	  ( INIT << 0 )		/* IP_12 index 52 */
#if (defined ctest_em_01)
	| ( OK << 2 )			/* EM_01 index 53 */
#else
	| ( INIT << 2 )		/* EM_01 index 53 */
#endif
#if (defined ctest_em_01)
	| ( OK << 4 )			/* EM_02 index 54 */
#else
	| ( INIT << 4 )		/* EM_02 index 54 */
#endif
#if (defined ctest_em_01)
	| ( OK << 6 ),			/* EM_03 index 55 */
#else
	| ( INIT << 6 ),		/* EM_03 index 55 */
#endif
#if (defined ctest_em_03)
	  ( OK << 0 )			/* EM_04 index 56 */
#else
	  ( INIT << 0 )		/* EM_04 index 56 */
#endif
#if (defined ctest_em_03)
	| ( OK << 2 )			/* EM_05 index 57 */
#else
	| ( INIT << 2 )		/* EM_05 index 57 */
#endif
#if (defined ctest_em_04)
	| ( OK << 4 )			/* EM_06 index 58 */
#else
	| ( INIT << 4 )		/* EM_06 index 58 */
#endif
#if (defined ctest_em_04)
	| ( OK << 6 ),			/* EM_07 index 59 */
#else
	| ( INIT << 6 ),		/* EM_07 index 59 */
#endif
#if (defined ctest_em_04)
	  ( OK << 0 )			/* EM_08 index 60 */
#else
	  ( INIT << 0 )		/* EM_08 index 60 */
#endif
#if (defined ctest_em_03)
	| ( OK << 2 )			/* EM_09 index 61 */
#else
	| ( INIT << 2 )		/* EM_09 index 61 */
#endif
#if (defined ctest_em_04)
	| ( OK << 4 )			/* EM_10 index 62 */
#else
	| ( INIT << 4 )		/* EM_10 index 62 */
#endif
#if (defined ctest_em_01)
	| ( OK << 6 ),			/* EM_11 index 63 */
#else
	| ( INIT << 6 ),		/* EM_11 index 63 */
#endif
#if (defined ctest_em_01)
	  ( OK << 0 )			/* EM_12 index 64 */
#else
	  ( INIT << 0 )		/* EM_12 index 64 */
#endif
	| ( INIT << 2 )		/* EM_13 index 65 */
#if (defined ctest_em_02)
	| ( OK << 4 )			/* EM_14 index 66 */
#else
	| ( INIT << 4 )		/* EM_14 index 66 */
#endif
#if (defined ctest_em_01)
	| ( OK << 6 ),			/* EM_15 index 67 */
#else
	| ( INIT << 6 ),		/* EM_15 index 67 */
#endif
#if (defined ctest_em_01)
	  ( OK << 0 )			/* EM_16 index 68 */
#else
	  ( INIT << 0 )		/* EM_16 index 68 */
#endif
#if (defined ctest_em_01)
	| ( OK << 2 )			/* EM_17 index 69 */
#else
	| ( INIT << 2 )		/* EM_17 index 69 */
#endif
#if (defined ctest_em_02)
	| ( OK << 4 )			/* EM_18 index 70 */
#else
	| ( INIT << 4 )		/* EM_18 index 70 */
#endif
#if (defined ctest_em_02)
	| ( OK << 6 ),			/* EM_19 index 71 */
#else
	| ( INIT << 6 ),		/* EM_19 index 71 */
#endif
#if (defined ctest_em_02)
	  ( OK << 0 )			/* EM_20 index 72 */
#else
	  ( INIT << 0 )		/* EM_20 index 72 */
#endif
#if (defined ctest_em_01)
	| ( OK << 2 )			/* EM_21 index 73 */
#else
	| ( INIT << 2 )		/* EM_21 index 73 */
#endif
#if (defined ctest_em_01)
	| ( OK << 4 )			/* EM_22 index 74 */
#else
	| ( INIT << 4 )		/* EM_22 index 74 */
#endif
#if (defined ctest_em_01)
	| ( OK << 6 ),			/* EM_23 index 75 */
#else
	| ( INIT << 6 ),		/* EM_23 index 75 */
#endif
	  ( INIT << 0 )		/* EM_24 index 76 */
#if (defined ctest_em_02)
	| ( OK << 2 )			/* EM_25 index 77 */
#else
	| ( INIT << 2 )		/* EM_25 index 77 */
#endif
#if (defined ctest_em_02)
	| ( OK << 4 )			/* EM_26 index 78 */
#else
	| ( INIT << 4 )		/* EM_26 index 78 */
#endif
#if (defined ctest_rm_01)
	| ( OK << 6 ),			/* RM_01 index 79 */
#else
	| ( INIT << 6 ),		/* RM_01 index 79 */
#endif
#if ( (defined ctest_rm_01) || (defined ctest_rm_05) )
	  ( OK << 0 )			/* RM_02 index 80 */
#else
	  ( INIT << 0 )		/* RM_02 index 80 */
#endif
#if ( (defined ctest_rm_01) || (defined ctest_rm_05) )
	| ( OK << 2 )			/* RM_03 index 81 */
#else
	| ( INIT << 2 )		/* RM_03 index 81 */
#endif
	| ( INIT << 4 )		/* RM_04 index 82 */
#if (defined ctest_rm_01)
	| ( OK << 6 ),			/* RM_05 index 83 */
#else
	| ( INIT << 6 ),		/* RM_05 index 83 */
#endif
#if (defined ctest_rm_02)
	  ( OK << 0 )			/* RM_06 index 84 */
#else
	  ( INIT << 0 )		/* RM_06 index 84 */
#endif
#if (defined ctest_rm_03)
	| ( OK << 2 )			/* RM_07 index 85 */
#else
	| ( INIT << 2 )		/* RM_07 index 85 */
#endif
#if (defined ctest_rm_04)
	| ( OK << 4 )			/* RM_08 index 86 */
#else
	| ( INIT << 4 )		/* RM_08 index 86 */
#endif
#if ( (defined ctest_rm_01) || (defined ctest_rm_05) )
	| ( OK << 6 ),			/* RM_09 index 87 */
#else
	| ( INIT << 6 ),		/* RM_09 index 87 */
#endif
#if ( (defined ctest_rm_01) || (defined ctest_rm_05) )
	  ( OK << 0 )			/* RM_10 index 88 */
#else
	  ( INIT << 0 )		/* RM_10 index 88 */
#endif
	| ( INIT << 2 )		/* RM_11 index 89 */
#if ( (defined ctest_rm_01) || (defined ctest_rm_05) )
	| ( OK << 4 )			/* RM_12 index 90 */
#else
	| ( INIT << 4 )		/* RM_12 index 90 */
#endif
#if (defined ctest_rm_02)
	| ( OK << 6 ),			/* RM_13 index 91 */
#else
	| ( INIT << 6 ),		/* RM_13 index 91 */
#endif
#if (defined ctest_rm_03)
	  ( OK << 0 )			/* RM_14 index 92 */
#else
	  ( INIT << 0 )		/* RM_14 index 92 */
#endif
#if (defined ctest_rm_04)
	| ( OK << 2 )			/* RM_15 index 93 */
#else
	| ( INIT << 2 )		/* RM_15 index 93 */
#endif
#if (defined ctest_rm_04)
	| ( OK << 4 )			/* RM_16 index 94 */
#else
	| ( INIT << 4 )		/* RM_16 index 94 */
#endif
#if (defined ctest_al_01)
	| ( OK << 6 ),			/* AL_01 index 95 */
#else
	| ( INIT << 6 ),		/* AL_01 index 95 */
#endif
#if (defined ctest_al_02)
	  ( OK << 0 )			/* AL_02 index 96 */
#else
	  ( INIT << 0 )		/* AL_02 index 96 */
#endif
#if (defined ctest_al_01)
	| ( OK << 2 )			/* AL_03 index 97 */
#else
	| ( INIT << 2 )		/* AL_03 index 97 */
#endif
#if (defined ctest_al_02)
	| ( OK << 4 )			/* AL_04 index 98 */
#else
	| ( INIT << 4 )		/* AL_04 index 98 */
#endif
#if (defined ctest_al_02)
	| ( OK << 6 ),			/* AL_05 index 99 */
#else
	| ( INIT << 6 ),		/* AL_05 index 99 */
#endif
#if (defined ctest_al_03)
	  ( OK << 0 )			/* AL_06 index 100 */
#else
	  ( INIT << 0 )		/* AL_06 index 100 */
#endif
#if (defined ctest_al_01)
	| ( OK << 2 )			/* AL_07 index 101 */
#else
	| ( INIT << 2 )		/* AL_07 index 101 */
#endif
#if (defined ctest_al_02)
	| ( OK << 4 )			/* AL_08 index 102 */
#else
	| ( INIT << 4 )		/* AL_08 index 102 */
#endif
#if (defined ctest_al_03)
	| ( OK << 6 ),			/* AL_09 index 103 */
#else
	| ( INIT << 6 ),		/* AL_09 index 103 */
#endif
#if (defined ctest_al_01)
	  ( OK <<  0 )			/* AL_10 index 104 */
#else
	  ( INIT << 0 )		/* AL_10 index 104 */
#endif
#if (defined ctest_al_01)
	| ( OK << 2 )			/* AL_11 index 105 */
#else
	| ( INIT << 2 )		/* AL_11 index 105 */
#endif
#if (defined ctest_al_01)
	| ( OK << 4 )			/* AL_12 index 106 */
#else
	| ( INIT << 4 )		/* AL_12 index 106 */
#endif
#if (defined ctest_al_01)
	| ( OK << 6 ),			/* AL_13 index 107 */
#else
	| ( INIT << 6 ),		/* AL_13 index 107 */
#endif
#if (defined ctest_al_02)
	  ( OK << 0 )			/* AL_14 index 108 */
#else
	  ( INIT << 0 )		/* AL_14 index 108 */
#endif
#if (defined ctest_al_03)
	| ( OK << 2 )			/* AL_15 index 109 */
#else
	| ( INIT << 2 )		/* AL_15 index 109 */
#endif
#if (defined ctest_al_01)
	| ( OK << 4 )			/* AL_16 index 110 */
#else
	| ( INIT << 4 )		/* AL_16 index 110 */
#endif
#if (defined ctest_al_02)
	| ( OK << 6 ),			/* AL_17 index 111 */
#else
	| ( INIT << 6 ),		/* AL_17 index 111 */
#endif
#if (defined ctest_al_03)
	  ( OK <<  0 )			/* AL_18 index 112 */
#else
	  ( INIT << 0 )		/* AL_18 index 112 */
#endif
#if (defined ctest_al_01)
	| ( OK << 2 )			/* AL_19 index 113 */
#else
	| ( INIT << 2 )		/* AL_19 index 113 */
#endif
#if (defined ctest_al_01)
	| ( OK << 4 )			/* AL_20 index 114 */
#else
	| ( INIT << 4 )		/* AL_20 index 114 */
#endif
#if (defined ctest_al_01)
	| ( OK << 6 ),			/* AL_21 index 115 */
#else
	| ( INIT << 6 ),		/* AL_21 index 115 */
#endif
#if (defined ctest_al_01)
	  ( OK <<  0 )			/* AL_22 index 116 */
#else
	  ( INIT << 0 )		/* AL_22 index 116 */
#endif
#if (defined ctest_al_02)
	| ( OK << 2 )			/* AL_23 index 117 */
#else
	| ( INIT << 2 )		/* AL_23 index 117 */
#endif
#if (defined ctest_al_03)
	| ( OK <<  4 )			/* AL_24 index 118 */
#else
	| ( INIT << 4 )		/* AL_24 index 118 */
#endif
#if (defined ctest_al_01)
	| ( OK << 6 ),			/* AL_25 index 119 */
#else
	| ( INIT << 6 ),		/* AL_25 index 119 */
#endif
#if (defined ctest_al_02)
	  ( OK << 0 )			/* AL_26 index 120 */
#else
	  ( INIT << 0 )		/* AL_26 index 120 */
#endif
#if (defined ctest_al_02)
	| ( OK << 2 )			/* AL_27 index 121 */
#else
	| ( INIT << 2 )		/* AL_27 index 121 */
#endif
#if (defined ctest_al_03)
	| ( OK <<  4 )			/* AL_28 index 122 */
#else
	| ( INIT << 4 )		/* AL_28 index 122 */
#endif
	| ( INIT << 6 ),		/* AL_29 index 123 */
#if (defined ctest_al_04)
	  ( OK <<  0 )			/* AL_30 index 124 */
#else
	  ( INIT << 0 )		/* AL_30 index 124 */
#endif
#if (defined ctest_al_05)
	| ( OK <<  2 )			/* AL_31 index 125 */
#else
	| ( INIT << 2 )		/* AL_31 index 125 */
#endif
#if (defined ctest_al_05)
	| ( OK <<  4 )			/* AL_32 index 126 */
#else
	| ( INIT << 4 )		/* AL_32 index 126 */
#endif
#if (defined ctest_al_06)
	| ( OK <<  6 ),		/* AL_33 index 127 */
#else
	| ( INIT << 6 ),		/* AL_33 index 127 */
#endif
#if ( ( (defined ctest_al_03) && (CT_SCHEDULING_Task1 == CT_NON_PREEMPTIVE) ) || \
		(defined ctest_al_06) )
	  ( OK <<  0 )			/* AL_34 index 128 */
#else
	  ( INIT << 0 )		/* AL_34 index 128 */
#endif
#if (defined ctest_al_07)
	| ( OK <<  2 )			/* AL_35 index 129 */
#else
	| ( INIT << 2 )		/* AL_35 index 129 */
#endif
#if (defined ctest_al_07)
	| ( OK <<  4 )			/* AL_36 index 130 */
#else
	| ( INIT << 4 )		/* AL_36 index 130 */
#endif
#if (defined ctest_eh_02)
	| ( OK << 6 ),			/* EH_01 index 131 */
#else
	| ( INIT << 6 ),		/* EH_01 index 131 */
#endif
	  ( INIT << 0 )		/* EH_02 index 132 */
#if (defined ctest_eh_02)
	| ( OK << 2 )			/* EH_03 index 133 */
#else
	| ( INIT << 2 )		/* EH_03 index 133 */
#endif
#if (defined ctest_eh_01)
	| ( OK << 4 )			/* EH_04 index 134 */
#else
	| ( INIT << 4 )		/* EH_04 index 134 */
#endif
#if (defined ctest_eh_01)
	| ( OK << 6 ),			/* EH_05 index 135 */
#else
	| ( INIT << 6 ),		/* EH_05 index 135 */
#endif
#if (defined ctest_eh_01)
	  ( OK << 0 )			/* EH_06 index 136 */
#else
	  ( INIT << 0 )		/* EH_06 index 136 */
#endif
#if (defined ctest_eh_02)
	| ( OK << 2 )			/* EH_07 index 137 */
#else
	| ( INIT << 2 )		/* EH_07 index 137 */
#endif
	| ( INIT << 4 )		/* EH_08 index 138 */
	| ( OK << 6 )			/* OTHER index 139 */
	};

uint8 ConfTestResult;

uint32f SequenceCounter;

/*==================[internal functions definition]==========================*/
#ifdef __CTEST_WITH_PRINTF__
extern int printf(const char* fmt, ...);
#else
int printf(const char* fmt, ...) { return 0; }
#endif
/*==================[external functions definition]==========================*/
void ASSERT
(
	uint8f tc,
	boolean cond
)
{
   if (cond)
   {
		TestResults[(tc)>>2] |=	FAILED << ( ( tc & 3 ) * 2 );
		printf("\t\t\tTestCase %03d FAIL\n", tc);
		while(1);
   }
	else
	{
		if ( ( TestResults[(tc)>>2] >> ( (tc & 3 ) * 2 ) ) != FAILED )
		{
			TestResults[(tc)>>2] |=	OK << ( ( tc & 3 ) * 2 );
		}
		printf("\t\t\tTestCase %03d PASS\n", tc);
	}
}

void ConfTestEvaluation
(
	void
)
{
	uint32f loopi;
	boolean testok = TRUE;

	for( loopi = 0; loopi < 35; loopi++)
	{
		if ( TestResultsOk[loopi] != TestResults[loopi] )
		{
			testok = FALSE;
		}
	}

	if ( ( testok == TRUE ) && ( SequenceCounter == SequenceCounterOk ) )
	{
		ConfTestResult = 255;
	}
	else
	{
		ConfTestResult = 128;
	}

}

void Sequence
(
	uint32f seq
)
{
   if ( (seq) == 0 )
   {
      SequenceCounter = 0;
      printf("Sequence %03d PASS\n", seq);
   }
   else if ( (SequenceCounter+1) == (seq) )
   {
      SequenceCounter++;
      printf("Sequence %03d PASS\n", seq);
   }
   else
   {
		SequenceCounter |= SEQUENCE_INVALID;
		printf("Sequence %03d FAIL\n", seq);
		while(1);
   }
}

void ConfTestFinish
(
	void
)
{
	printf(" >> END << \n");
	while(1);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

