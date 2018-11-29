#ifndef OSEVTAPI_H
#define OSEVTAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osevtapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS tasks' events   
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
#if defined(OSECC)

/*  Configuration Data  */

/*  Constants */

#define OSEVTWAIT   ((OSBYTE)0x00)
#define OSEVTREADY  ((OSBYTE)0x01)

#define OSNOEVENTS  ((EventMaskType) 0 )

/*  Global OS variables */

#if (OSNXTSKS > 0)

/*  Internal OS Services  */
void OSSetEvent(OSTSKCBPTR task, EventMaskType mask);
#if(OSNTPTSKARRIV > 0) && defined(OSHOOKPROTECTION)
void OSSetEventInAlm(OSTSKCBPTR task, EventMaskType mask);
#else
#define OSSetEventInAlm( task, mask)   OSSetEvent( task, mask ) 
#endif /* (OSNTPTSKARRIV > 0) && defined(OSHOOKPROTECTION) */

/*  External OS Services  */
StatusType OS_SetEvent( TaskType taskId, EventMaskType mask );
StatusType OS_ClearEvent( EventMaskType mask );
StatusType OS_WaitEvent( EventMaskType mask );
StatusType OS_GetEvent( TaskType taskId, EventMaskRefType maskRef );

/*  Public OS Services  */
#define DeclareEvent(Event)  extern OSBYTE osdummy

#if defined(OSMEMPROTECTION)
OSINLINE StatusType SetEvent( TaskType taskId, EventMaskType mask )
{
    return OSServiceCall2( StatusType, taskId, mask, SetEvent );
}
OSINLINE StatusType ClearEvent( EventMaskType mask ) 
{
    return OSServiceCall1( StatusType, mask, ClearEvent );
}
OSINLINE StatusType WaitEvent( EventMaskType mask )
{
    return OSServiceCall1( StatusType, mask, WaitEvent );
}
OSINLINE StatusType GetEvent( TaskType taskId, EventMaskRefType maskRef )
{
    return OSServiceCall2( StatusType, taskId, maskRef, GetEvent );
}
#else  /* defined(OSMEMPROTECTION) */
#define SetEvent(taskId, mask)    OS_SetEvent(taskId, mask)
#define ClearEvent(mask)          OS_ClearEvent(mask)
#define WaitEvent(mask)           OS_WaitEvent(mask)
#define GetEvent(taskId, maskRef) OS_GetEvent(taskId, maskRef)
#endif /* defined(OSMEMPROTECTION) */

#endif  /* (OSNXTSKS > 0) */

#endif  /* defined(OSECC)  */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSEVTAPI_H */
