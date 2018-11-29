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
        (OSTASKENTRY)FuncTASK3, 
        OSTASK3STKTOS, /* tos */
        OSTASK3STKBOS, /* bos */
        0 | OSTSKEXTENDED | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TASK3), /* id */
    }, /* TASK3 */
    {
        (OSTASKENTRY)FuncTASK2, 
        OSTASK2STKTOS, /* tos */
        OSTASK2STKBOS, /* bos */
        0 | OSTSKEXTENDED | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TASK2), /* id */
    }, /* TASK2 */
    {
        (OSTASKENTRY)FuncTASK1, 
        OSTASK1STKTOS, /* tos */
        OSTASK1STKBOS, /* bos */
        0 | OSTSKEXTENDED | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(TASK1), /* id */
    }, /* TASK1 */
    {
        (OSTASKENTRY)FuncLoopTask, 
        0, 
        0, 
        0 | OSTSKACTIVATE, /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
        OS_GETOBJIND(LoopTask), /* id */
    }, /* LoopTask */
};
const    OSISRCFGTYPE   OsIsrCfg[OSNISR + 1] =  /*Interrupts config table*/
{
    {
        OSISRSystemTimer, 
        OSSYSINTERRUPT, 
        200, /* index in OsIsr */
        1, 
    }, /* SysTimer */
    {
        OS_isr_ESCI_SCI_Isr_UART_TX, /* ISR function */
        OSISR1, /* ISR category */
        146,  
        5, /* ISR PRIORITY */
    }, /* ESCI_SCI_Isr_UART_TX */
    {
        OS_isr_Wdg_Isr, /* ISR function */
        OSISR1, /* ISR category */
        8,  
        15, /* ISR PRIORITY */
    }, /* Wdg_Isr */
    {
        OS_isr_Gpt_PITRTI_TIMER_0_ISR, /* ISR function */
        OSISR1, /* ISR category */
        301,  
        3, /* ISR PRIORITY */
    }, /* Gpt_PITRTI_TIMER_0_ISR */
    {
        OS_isr_Lin_LLD_InterruptHandler_ESCI_1, /* ISR function */
        OSISR1, /* ISR category */
        149,  
        5, /* ISR PRIORITY */
    }, /* Lin_LLD_InterruptHandler_ESCI_1 */
    {
        OS_isr_Spi_LLD_IsrEOQ_DSPI_1, /* ISR function */
        OSISR1, /* ISR category */
        132,  
        3, /* ISR PRIORITY */
    }, /* Spi_LLD_IsrEOQ_DSPI_1 */
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
        OS_isr_EMIOS_0_CH_8_ISR, /* ISR function */
        OSISR1, /* ISR category */
        59,  
        5, /* ISR PRIORITY */
    }, /* EMIOS_0_CH_8_ISR */
    {
        OS_isr_EMIOS_0_CH_9_ISR, /* ISR function */
        OSISR1, /* ISR category */
        60,  
        11, /* ISR PRIORITY */
    }, /* EMIOS_0_CH_9_ISR */
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
        OS_GETOBJIND(TASK1), /* task to notify */
        OsEvent_Task1, /* if event==0 then alarm activates task else it set event for this task */
        OS_GETOBJIND(SYSTEMTIMER), /* attached Counter ID */
    }, /* OsAlarm_Task1 */
    {
        OS_GETOBJIND(TASK2), /* task to notify */
        OsEvent_Task2, /* if event==0 then alarm activates task else it set event for this task */
        OS_GETOBJIND(SYSTEMTIMER), /* attached Counter ID */
    }, /* OsAlarm_Task2 */
    {
        OS_GETOBJIND(TASK3), /* task to notify */
        OsEvent_Task3, /* if event==0 then alarm activates task else it set event for this task */
        OS_GETOBJIND(SYSTEMTIMER), /* attached Counter ID */
    }, /* OsAlarm_Task3 */
};

/* Auto started Alarms */
const    OSALMAUTOTYPE   OsAutoAlarms[OSNAUTOALMS] = 
{
    {
        &OsAllAlarms.OsAlarms[0], 
        (TickType)5000, 
        (TickType)5000, 
        OSALMRELATIVE, 
    }, /* OsAlarm_Task1 */
    {
        &OsAllAlarms.OsAlarms[1], 
        (TickType)10000, 
        (TickType)10000, 
        OSALMRELATIVE, 
    }, /* OsAlarm_Task2 */
    {
        &OsAllAlarms.OsAlarms[2], 
        (TickType)15000, 
        (TickType)15000, 
        OSALMRELATIVE, 
    }, /* OsAlarm_Task3 */
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
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 2, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 8, 
    9, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, 6, 7, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, 5, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 1, OSNISR, OSNISR, 4, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    0, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, 3, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, OSNISR, 
    OSNISR, OSNISR, OSNISR, OSNISR, 
};
static const    OSSCTEP   OSSCHEDTAB_actions[] = 
{
    { &OSSCHEDTAB_actions[0], { OS_GETOBJIND(TASK1), 0,  }, 30000,  }, /* TASK1 activation */
};
const    OSSCT   OsScheduleTablesCfg[OSNSCTS] = 
{
    { OS_GETOBJIND(SYSTEMTIMER), 30000, 0, &OSSCHEDTAB_actions[0], OSSCTCFGPERIODIC,  }, /* OSSCHEDTAB */
};
#define OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED        
#include    "ossections.h"

#define OS_STOP_SEC_CONST_UNSPECIFIED      
#include    "ossections.h"

