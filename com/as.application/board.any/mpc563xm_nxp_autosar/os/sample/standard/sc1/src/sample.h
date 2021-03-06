#ifndef SAMPLE_H
#define SAMPLE_H
/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2009
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*  Description:  AUTOSAR OS sample application
*
**************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned short ind, taskRcv1, taskRcv2, taskStop, taskSnd1, taskSnd2, taskCnt;

extern volatile int hookNmb;

typedef struct TagMYMsgA    MSGATYPE;           /* User defined type for a message */
struct TagMYMsgA
{
    unsigned short value;
};

typedef struct TagMYMsgB    MSGBTYPE;           /* User-defined type for a message */
struct  TagMYMsgB
{
    TickType    ts;                             /* user's defined time-stamp */
    unsigned short msg;                         /* message body */
};

#ifdef __cplusplus
}
#endif

#endif  /* SAMPLE_H */
