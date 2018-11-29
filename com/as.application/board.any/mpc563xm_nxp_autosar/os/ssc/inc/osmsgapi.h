#ifndef OSMSGAPI_H
#define OSMSGAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osmsgapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS messages    
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if OSNMSGS > 0

/* consistency assurance */


#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT) || defined(OSSIGFLAG) || defined(OSSIGCALLBACK)
#define OSSIGNAL
#endif

#define OSMSGINVALID        0xFF


/**** COM standard macros ****/

#define COM_SHUTDOWN_IMMEDIATE  0

#if defined(OSCOMGETSERVICEID)

#if defined(OSCOMPARAMETERACCESS)
#define COMError_StartCOM_Mode()            (COMApplicationModeType)OsComObjId
#define COMError_StopCOM_Mode()             (COMShutdownModeType)OsComObjId
#define COMError_SendMessage_Message()      (MessageIdentifier)OsComObjId
#define COMError_ReceiveMessage_Message()   (MessageIdentifier)OsComObjId
#define COMError_GetMessageStatus_Message() (MessageIdentifier)OsComObjId
#define COMError_InitMessage_Message()      (MessageIdentifier)OsComObjId
#define COMError_ReadFlag_Flag()            (FlagType)OsComObjId
#define COMError_ResetFlag_Flag()           (FlagType)OsComObjId
#endif /* defined(OSCOMPARAMETERACCESS) */

#define COMErrorGetServiceId() OsComService

#endif /* defined(OSCOMGETSERVICEID)    */


/**** Configuration Data ****/
extern const OSMSGtype    OsMsg[OSNRCVMSGS];     /* receiving messages configuration */
#if defined(OSAPPLICATION)
extern const OSSNDMSGtype OsSndMsg[OSNSNDMSGS];  /* sending messages configuration */
#endif
extern const OSBYTE* const OsSndPtr[OSNSNDMSGS]; /* send messages pointers to arrays of receiving */

#define OSMSGOVERFLOW       0x80                        /* overflow detected            */


#if OSNFLAGS > 0

#define OSNOFLAG            0xFF

#if defined(OSORTICURRENTSERVICEID)

FlagValue   OSReadFlag( FlagType flag );
void        OSResetFlag( FlagType flag );

#else   /* defined(OSORTICURRENTSERVICEID) */

#define OSReadFlag(flag) ((flag == COM_TRUE) ? COM_TRUE : COM_FALSE )
#define OSResetFlag(flag) (flag = COM_FALSE, E_OK)

#endif   /* defined(OSORTICURRENTSERVICEID) */
#endif /* OSNFLAGS > 0 */

/**** COM OS internal functions ****/

StatusType OS_SendMessage( MessageIdentifier Message, ApplicationDataRef DataRef );
StatusType OS_ReceiveMessage( MessageIdentifier Message, ApplicationDataRef DataRef );
StatusType OS_GetMessageStatus( MessageIdentifier Message );
StatusType OS_InitMessage (MessageIdentifier Message, ApplicationDataRef DataRef);
StatusType OS_StartCOM( COMApplicationModeType Mode );
StatusType OS_StopCOM( COMShutdownModeType Mode);

/**** COM standard functions ****/
#if defined(OSMEMPROTECTION)

/* inline wrappers for OSServiceDispatcher callers */

OSINLINE StatusType SendMessage( MessageIdentifier Message, ApplicationDataRef DataRef )
{
    return OSServiceCall2(StatusType, Message, DataRef, SendMessage);
}

OSINLINE StatusType ReceiveMessage( MessageIdentifier Message, ApplicationDataRef DataRef )
{
    return OSServiceCall2( StatusType, Message, DataRef, ReceiveMessage);
}

OSINLINE StatusType GetMessageStatus( MessageIdentifier Message )
{
    return OSServiceCall1( StatusType, Message, GetMessageStatus);
}

OSINLINE StatusType InitMessage( MessageIdentifier Message, ApplicationDataRef DataRef )
{
    return OSServiceCall2( StatusType, Message, DataRef, InitMessage);
}

OSINLINE StatusType StartCOM( COMShutdownModeType Mode )
{
    return OSServiceCall1( StatusType, Mode, StartCOM);
}

OSINLINE StatusType StopCOM( COMShutdownModeType Mode )
{  
    return OSServiceCall1( StatusType, Mode, StopCOM);
}

#else  /* defined(OSMEMPROTECTION) */
#define SendMessage(Message,DataRef)     OS_SendMessage(Message, DataRef)
#define ReceiveMessage(Message,DataRef)  OS_ReceiveMessage(Message, DataRef)
#define GetMessageStatus(Message)        OS_GetMessageStatus(Message)
#define InitMessage(Message,DataRef )    OS_InitMessage(Message, DataRef)
#define StartCOM(Mode)                   OS_StartCOM(Mode)
#define StopCOM(Mode)                    OS_StopCOM(Mode)
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSCOMHOOKSTARTUP) 
StatusType StartCOMExtension(void);                 /* shall be provided by user */
#endif
#define GetCOMApplicationMode()   (OsCOMmode)

void   OSMsgInit( void );


#endif  /* OSNMSGS > 0 */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSMSGAPI_H */
