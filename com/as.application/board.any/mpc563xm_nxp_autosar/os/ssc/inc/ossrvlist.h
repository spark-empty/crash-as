/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*   BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*   Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ossrvlist.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for AUTOSAR services
*
* Notes:        this file is included twice in different contexts
*
******************************************************************************/

OSSRVENTRY( ShutdownOS )

#if defined(OSCHECKCONTEXT)
,
OSSRVENTRY( GetActiveApplicationMode )
#endif

#if (OSNCTRS > 0)
,
OSSRVENTRY( InitCounter ),
OSSRVENTRY( GetCounterValue ),
OSSRVENTRY( GetElapsedCounterValue ),
OSSRVENTRY( IncrementCounter ),
OSSRVENTRY( GetCounterInfo )
#endif

#if (OSNUSERALMS > 0)
,
OSSRVENTRY( GetAlarmBase ),
OSSRVENTRY( GetAlarm ),
OSSRVENTRY( SetRelAlarm ),
OSSRVENTRY( SetAbsAlarm ),
OSSRVENTRY( CancelAlarm )
#endif

#if defined(OSSCHEDULETABLES)
,
OSSRVENTRY( StartScheduleTableAbs ),
OSSRVENTRY( StartScheduleTableRel ),
OSSRVENTRY( StopScheduleTable ),
OSSRVENTRY( NextScheduleTable ),
OSSRVENTRY( SyncScheduleTable ),
OSSRVENTRY( StartScheduleTableSynchron ),
OSSRVENTRY( SetScheduleTableAsync ),
OSSRVENTRY( GetScheduleTableStatus )
#endif

#if (OSNXTSKS > 0)
,
OSSRVENTRY( SetEvent ),
OSSRVENTRY( ClearEvent ),
OSSRVENTRY( WaitEvent ),
OSSRVENTRY( GetEvent )
#endif

#if defined(OSRESOURCE)
,
OSSRVENTRY( GetResource ),
OSSRVENTRY( ReleaseResource )
#endif

#if (OSNMSGS > 0)
,
OSSRVENTRY( SendMessage ),
OSSRVENTRY( ReceiveMessage ),
OSSRVENTRY( GetMessageStatus ),
OSSRVENTRY( InitMessage ),
OSSRVENTRY( StartCOM ),
OSSRVENTRY( StopCOM )
#endif

#if defined(OSISRENTRYEXIT)
,
OSSRVENTRY( ResumeOSInterrupts ),
OSSRVENTRY( SuspendOSInterrupts ),
OSSRVENTRY( GetISRID )
#endif

#if OSNISR > 0
,
OSSRVENTRY( DisableInterruptSource ),
OSSRVENTRY( EnableInterruptSource )
#endif

#if OSNTRUSTEDFUNCTIONS > 0
,
OSSRVENTRY( CallTrustedFunction )
#endif

#if !defined(OSNOISR2)
,
OSSRVENTRY( CheckISRMemoryAccess )
#endif

#if (OSNNOTTRUSTEDAPPS > 0)
,
OSSRVENTRY( OS2SysMode )
#endif

,
OSSRVENTRY( ActivateTask ),
OSSRVENTRY( TerminateTask ),
OSSRVENTRY( ChainTask ),
OSSRVENTRY( GetTaskID ),
OSSRVENTRY( GetTaskState ),
OSSRVENTRY( CheckObjectAccess ),
OSSRVENTRY( Schedule ),
OSSRVENTRY( DisableAllInterrupts ),
OSSRVENTRY( EnableAllInterrupts ),
OSSRVENTRY( ResumeAllInterrupts ),
OSSRVENTRY( SuspendAllInterrupts ),
OSSRVENTRY( TerminateApplication ),
OSSRVENTRY( GetApplicationID ),
OSSRVENTRY( CheckTaskMemoryAccess ),
OSSRVENTRY( CheckObjectOwnership ),
OSSRVENTRY( ExceptionDispatch )
