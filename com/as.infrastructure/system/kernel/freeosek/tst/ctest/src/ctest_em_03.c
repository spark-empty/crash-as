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

/** \brief Free OSEK Conformance Test for the Event Mechanism, Test Sequence 3
 **
 ** \file FreeOSEK/tst/ctest/src/ctest_em_03.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_CT_EM Event Mechanism
 ** @{ */
/** \addtogroup FreeOSEK_CT_EM_03 Test Sequence 3
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090417 v0.1.0 MaCe initial version based on old moduletest
 */

/*==================[inclusions]=============================================*/
#include "os.h"				/* include os header file */
#include "ctest_em_03.h"	/* include test header file */
#include "ctest.h"			/* include ctest header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
const uint32f SequenceCounterOk = MAX_SEQUENCE;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main
(
	void
)
{
	/* start OS in AppMode 1 */
	StartOS(AppMode1);

	/* shall never return */
	while(1);

	return 0;
}

TASK(Task1)
{
	StatusType ret;
	EventMaskType EventMask;
	TaskStateType TaskState;

	Sequence(1);
	ret = GetTaskState(Task2, &TaskState);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, TaskState != WAITING);

	Sequence(2);
	ret = GetEvent(Task2, &EventMask);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, EventMask != 0);

	Sequence(3);
	/* \treq EM_05 nm E1E2 se Call SetEvent() from non preemptive task
	 * on waiting extended task which is not waiting for any of the requested
	 * events
	 *
	 * \result Requested events are set. Running task is not preempted. Waiting
	 * task doesn't becomes ready. Service returns E_OK
	 */
	ret = SetEvent(Task2, Event2);
	ASSERT(EM_05, ret != E_OK);

	Sequence(4);
	ret = GetTaskState(Task2, &TaskState);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, TaskState != WAITING);

	Sequence(5);
	ret = GetEvent(Task2, &EventMask);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, EventMask != Event2);

	Sequence(6);
	/* \treq EM_04 nm E1E2 se Call SetEvent() from non preemptive task
	 * on waiting extended task which is waiting for at least one of the
	 * requested events
	 *
	 * \result Requested events are set. Running task is not preempted. Waiting
	 * task becomes ready. Service returns E_OK
	 */
	ret = SetEvent(Task2, Event1);
	ASSERT(EM_04, ret != E_OK);

	Sequence(7);
	ret = GetTaskState(Task2, &TaskState);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, TaskState != READY);

	Sequence(8);
	ret = GetEvent(Task2, &EventMask);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, EventMask != ( Event1 | Event2 ) );

	Sequence(9);
	/* \treq EM_09 nm E1E2 se Call SetEvent() from non preemptive task
	 * on waiting extended task
	 *
	 * \result Requested events are set. Running task is not preempted. Service
	 * returns E_OK
	 */
	ret = SetEvent(Task2, Event3);
	ASSERT(EM_09, ret != E_OK);

	Sequence(10);
	ret = GetEvent(Task2, &EventMask);
	ASSERT(OTHER, ret != E_OK);
	ASSERT(OTHER, EventMask != ( Event1 | Event2 | Event3 ) );

	Sequence(11);
	TerminateTask();
}

TASK(Task2)
{
	StatusType ret;

	Sequence(0);
	ret = WaitEvent(Event1);
	ASSERT(OTHER, ret != E_OK);

	Sequence(12);

	/* evaluate conformance tests */
	ConfTestEvaluation();

	/* finish the conformance test */
	ConfTestFinish();
}

/* This task is not used, only to change the scheduling police */
TASK(Task3)
{
	TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

