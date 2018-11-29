/******************************************************************************
*
*       Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc.
*       All other product or service names are the property of their respective owners.
*       (C) Freescale Semiconductor, Inc. 2010
*
*       THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*       BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*       Freescale Semiconductor, Inc.
*
* Description: Configuration Data file
*
* Note: The implementation was used: AUTOSAR_MPC56xxAM
*       System Generator for AUTOSAR OS/MPC56xxAM - Version: 3.0 Build 3.0.35
*
********************************************************************************/

#include    <os.h>

#define OS_START_SEC_CONST_UNSPECIFIED     
#include    "ossections.h"

#define OS_START_SEC_VAR_UNSPECIFIED       
#include    "ossections.h"

#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"


/* Task Configuration table */
const    OSTSK   OsTaskCfgTable[OSNTSKS] = 
{
    {
        (OSTASKENTRY)FuncTaskCanIf, 
        0, 
        0, 
        0 | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TaskCanIf), /* id */
    }, /* TaskCanIf */
    {
        (OSTASKENTRY)FuncSchM_BswService, 
        0, 
        0, 
        0, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(SchM_BswService), /* id */
    }, /* SchM_BswService */
    {
        (OSTASKENTRY)FuncSchM_Startup, 
        0, 
        0, 
        0 | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(SchM_Startup), /* id */
    }, /* SchM_Startup */
    {
        (OSTASKENTRY)FuncTaskApp, 
        0, 
        0, 
        0 | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TaskApp), /* id */
    }, /* TaskApp */
    {
        (OSTASKENTRY)FuncTaskShell, 
        OSTaskShellSTKTOS, /* tos */
        OSTaskShellSTKBOS, /* bos */
        0 | OSTSKEXTENDED | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TaskShell), /* id */
    }, /* TaskShell */
    {
        (OSTASKENTRY)FuncTaskIdle, 
        0, 
        0, 
        0 | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TaskIdle), /* id */
    }, /* TaskIdle */
};
const    OSISRCFGTYPE   OsIsrCfg[OSNISR + 1] =  /*Interrupts config table*/
{
    {
        OS_isr_RTI_TickHandler, /* ISR function */
        OSTRUSTEDISR2, /* ISR category */
        305,  
        1, /* ISR PRIORITY */
    }, /* RTI_TickHandler */
    {
        OSISRSystemTimer, 
        OSSYSINTERRUPT, 
        200, /* index in OsIsr */
        1, 
    }, /* SysTimer */
    {
        OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty, /* ISR function */
        OSISR1, /* ISR category */
        104,  
        5, /* ISR PRIORITY */
    }, /* Adc_Irq_eQADCA_CFIFO0_Empty */
    {
        OS_isr_Adc_Irq_eQADCA_RFIFO0_Full, /* ISR function */
        OSISR1, /* ISR category */
        105,  
        5, /* ISR PRIORITY */
    }, /* Adc_Irq_eQADCA_RFIFO0_Full */
    {
        OSISRException, 
        OSSYSINTERRUPT, 
        OSISREXCEPTIONIDX, 
        OSISREXCEPTIONPRIO, 
    }, /* Exception */
};
const    OSPRIOTYPE   OsResPrioTbl[OSNRESS + OSNISRRESS] = 
{
    0, /* RES_SCHEDULER */
};

/* Alarms table */
const    OSALM   OsAlarmsCfg[OSNUSERALMS] = 
{
    {
        OS_GETOBJIND(TaskApp), /* task to notify */
        OS_GETOBJIND(SYSTEMTIMER), /* attached Counter ID */
    }, /* AlarmApp */
    {
        OS_GETOBJIND(SchM_BswService), /* task to notify */
        OS_GETOBJIND(SYSTEMTIMER), /* attached Counter ID */
    }, /* Alarm_BswService */
};

/* Auto started Alarms */
const    OSALMAUTOTYPE   OsAutoAlarms[OSNAUTOALMS] = 
{
    {
        &OsAlarms[0], 
        (TickType)5000, 
        (TickType)5000, 
        OSALMRELATIVE, 
    }, /* AlarmApp */
    {
        &OsAlarms[1], 
        (TickType)10000, 
        (TickType)10000, 
        OSALMRELATIVE, 
    }, /* Alarm_BswService */
};

/* Counter table */
const    OSCTR   OsCountersCfg[OSNCTRS] = 
{
    {
        0xffffffff, /* maximum allowed counter value */
        10, /* conversion constant */
        0x0, /* minimum period value for alarm */
    }, /* SYSTEMTIMER */
};
const    OSSHORT   OsIsr[OSNINTC] =  /* OSNINTERRUPTS external interrupt handlers table */
{
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, 2, 3, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    1, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 0, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, 
};
#define OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED        
#include    "ossections.h"

#define OS_STOP_SEC_CONST_UNSPECIFIED      
#include    "ossections.h"

