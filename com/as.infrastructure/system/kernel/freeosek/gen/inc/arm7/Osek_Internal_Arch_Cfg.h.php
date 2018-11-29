/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

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

#ifndef _OSEK_INTERNAL_ARCH_CFG_H_
#define _OSEK_INTERNAL_ARCH_CFG_H_
/** \brief FreeOSEK Generated Internal Architecture Configuration Header File
 **
 ** This file content the internal generated architecture dependent
 ** configuration of FreeOSEK.
 **
 ** \file Osek_Internal_Arch_Cfg.h
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.0 20081116 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
/** TODO */
#define INTERUPTS_COUNT		32

/*==================[typedef]================================================*/
/** \brief Task Context Type */
typedef struct {
	uint32 reg_r0;
	uint32 reg_r1;
	uint32 reg_r2;
	uint32 reg_r3;
	uint32 reg_r4;
	uint32 reg_r5;
	uint32 reg_r6;
	uint32 reg_r7;
	uint32 reg_r8;
	uint32 reg_r9;
	uint32 reg_r10;
	uint32 reg_r11;
	uint32 reg_r12;
	uint32 reg_r13; /* stack pointer */
	uint32 reg_r14; /* link register */
	uint32 reg_r15; /* program counter */
	uint32 reg_cpsr; /* current program status register */
} TaskContextType;

/** \brief Task Context Type */
typedef TaskContextType* TaskContextRefType;

/** \brief InterruptType Type definition */
typedef void (*InterruptType)(void);

/*==================[external data declaration]==============================*/
extern InterruptType InterruptTable[INTERUPTS_COUNT];

/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OSEK_INTERNAL_ARCH_CFG_H_ */
