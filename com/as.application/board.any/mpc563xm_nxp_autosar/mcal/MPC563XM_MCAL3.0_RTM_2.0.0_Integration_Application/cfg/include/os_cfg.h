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
* Description: Configuration Header file
*
* Note: The implementation was used: AUTOSAR_MPC56xxAM
*       System Generator for AUTOSAR OS/MPC56xxAM - Version: 3.0 Build 3.0.35
*
********************************************************************************/

#ifndef OSCFG_H
#define OSCFG_H                            
#define APP_START_SEC_CODE                 
#include    "ossections.h"

#define OS_START_SEC_CONST_UNSPECIFIED     
#include    "ossections.h"

#define OS_START_SEC_VAR_UNSPECIFIED       
#include    "ossections.h"

#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"


/* Applications */

/* Application modes */
#define Mode01 ((AppModeType)0)            /* AppMode ID */

/* Common stack */
#define OSTASK3STKSIZE 2080                /* stack size of TASK3 */
#define OSTASK3STKBOS OSRUNNABLESTKBEG     /* TASK3 bos */
#define OSTASK3STKTOS OSTASK3STKBOS + OSTASK3STKSIZE/4 /* TASK3 tos */
#define OSTASK2STKSIZE 2080                /* stack size of TASK2 */
#define OSTASK2STKBOS OSTASK3STKTOS        /* TASK2 bos */
#define OSTASK2STKTOS OSTASK2STKBOS + OSTASK2STKSIZE/4 /* TASK2 tos */
#define OSTASK1STKSIZE 2080                /* stack size of TASK1 */
#define OSTASK1STKBOS OSTASK2STKTOS        /* TASK1 bos */
#define OSTASK1STKTOS OSTASK1STKBOS + OSTASK1STKSIZE/4 /* TASK1 tos */

/* Task definitions */
#define TASK3 ((TaskType)OS_MKOBJID(OBJECT_TASK, 0)) /* Task ID */
extern void FuncTASK3(void); /* Task entry point */
#define TASK2 ((TaskType)OS_MKOBJID(OBJECT_TASK, 1)) /* Task ID */
extern void FuncTASK2(void); /* Task entry point */
#define TASK1 ((TaskType)OS_MKOBJID(OBJECT_TASK, 2)) /* Task ID */
extern void FuncTASK1(void); /* Task entry point */
#define LoopTask ((TaskType)OS_MKOBJID(OBJECT_TASK, 3)) /* Task ID */
extern void FuncLoopTask(void); /* Task entry point */

/* ISR functions */

/* ISRs definition */
#define OSISRESCI_SCI_Isr_UART_TX() OSISR1DISP(ESCI_SCI_Isr_UART_TX) /* IrqChannel is EXTERNAL */
extern void OS_isr_ESCI_SCI_Isr_UART_TX(void); /* irq: ESCI_SCI_Isr_UART_TX; channel: EXTERNAL; category: 1 */
#define ESCI_SCI_Isr_UART_TXLEVEL 5        /* interrupt level of ESCI_SCI_Isr_UART_TX */
#define ESCI_SCI_Isr_UART_TXPRIORITY 5     /* priority of ESCI_SCI_Isr_UART_TX */
#define OSISRWdg_Isr() OSISR1DISP(Wdg_Isr) /* IrqChannel is EXTERNAL */
extern void OS_isr_Wdg_Isr(void); /* irq: Wdg_Isr; channel: EXTERNAL; category: 1 */
#define Wdg_IsrLEVEL 15                    /* interrupt level of Wdg_Isr */
#define Wdg_IsrPRIORITY 15                 /* priority of Wdg_Isr */
#define OSISRGpt_PITRTI_TIMER_0_ISR() OSISR1DISP(Gpt_PITRTI_TIMER_0_ISR) /* IrqChannel is EXTERNAL */
extern void OS_isr_Gpt_PITRTI_TIMER_0_ISR(void); /* irq: Gpt_PITRTI_TIMER_0_ISR; channel: EXTERNAL; category: 1 */
#define Gpt_PITRTI_TIMER_0_ISRLEVEL 3      /* interrupt level of Gpt_PITRTI_TIMER_0_ISR */
#define Gpt_PITRTI_TIMER_0_ISRPRIORITY 3   /* priority of Gpt_PITRTI_TIMER_0_ISR */
#define OSISRLin_LLD_InterruptHandler_ESCI_1() OSISR1DISP(Lin_LLD_InterruptHandler_ESCI_1) /* IrqChannel is EXTERNAL */
extern void OS_isr_Lin_LLD_InterruptHandler_ESCI_1(void); /* irq: Lin_LLD_InterruptHandler_ESCI_1; channel: EXTERNAL; category: 1 */
#define Lin_LLD_InterruptHandler_ESCI_1LEVEL 5 /* interrupt level of Lin_LLD_InterruptHandler_ESCI_1 */
#define Lin_LLD_InterruptHandler_ESCI_1PRIORITY 5 /* priority of Lin_LLD_InterruptHandler_ESCI_1 */
#define OSISRSpi_LLD_IsrEOQ_DSPI_1() OSISR1DISP(Spi_LLD_IsrEOQ_DSPI_1) /* IrqChannel is EXTERNAL */
extern void OS_isr_Spi_LLD_IsrEOQ_DSPI_1(void); /* irq: Spi_LLD_IsrEOQ_DSPI_1; channel: EXTERNAL; category: 1 */
#define Spi_LLD_IsrEOQ_DSPI_1LEVEL 3       /* interrupt level of Spi_LLD_IsrEOQ_DSPI_1 */
#define Spi_LLD_IsrEOQ_DSPI_1PRIORITY 3    /* priority of Spi_LLD_IsrEOQ_DSPI_1 */
#define OSISRAdc_Irq_eQADCA_CFIFO0_Empty() OSISR1DISP(Adc_Irq_eQADCA_CFIFO0_Empty) /* IrqChannel is EXTERNAL */
extern void OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty(void); /* irq: Adc_Irq_eQADCA_CFIFO0_Empty; channel: EXTERNAL; category: 1 */
#define Adc_Irq_eQADCA_CFIFO0_EmptyLEVEL 5 /* interrupt level of Adc_Irq_eQADCA_CFIFO0_Empty */
#define Adc_Irq_eQADCA_CFIFO0_EmptyPRIORITY 5 /* priority of Adc_Irq_eQADCA_CFIFO0_Empty */
#define OSISRAdc_Irq_eQADCA_RFIFO0_Full() OSISR1DISP(Adc_Irq_eQADCA_RFIFO0_Full) /* IrqChannel is EXTERNAL */
extern void OS_isr_Adc_Irq_eQADCA_RFIFO0_Full(void); /* irq: Adc_Irq_eQADCA_RFIFO0_Full; channel: EXTERNAL; category: 1 */
#define Adc_Irq_eQADCA_RFIFO0_FullLEVEL 5  /* interrupt level of Adc_Irq_eQADCA_RFIFO0_Full */
#define Adc_Irq_eQADCA_RFIFO0_FullPRIORITY 5 /* priority of Adc_Irq_eQADCA_RFIFO0_Full */
#define OSISREMIOS_0_CH_8_ISR() OSISR1DISP(EMIOS_0_CH_8_ISR) /* IrqChannel is EXTERNAL */
extern void OS_isr_EMIOS_0_CH_8_ISR(void); /* irq: EMIOS_0_CH_8_ISR; channel: EXTERNAL; category: 1 */
#define EMIOS_0_CH_8_ISRLEVEL 5            /* interrupt level of EMIOS_0_CH_8_ISR */
#define EMIOS_0_CH_8_ISRPRIORITY 5         /* priority of EMIOS_0_CH_8_ISR */
#define OSISREMIOS_0_CH_9_ISR() OSISR1DISP(EMIOS_0_CH_9_ISR) /* IrqChannel is EXTERNAL */
extern void OS_isr_EMIOS_0_CH_9_ISR(void); /* irq: EMIOS_0_CH_9_ISR; channel: EXTERNAL; category: 1 */
#define EMIOS_0_CH_9_ISRLEVEL 11           /* interrupt level of EMIOS_0_CH_9_ISR */
#define EMIOS_0_CH_9_ISRPRIORITY 11        /* priority of EMIOS_0_CH_9_ISR */

/* ISR1 id */
#define ESCI_SCI_Isr_UART_TX ((ISRType)OS_MKOBJID(OBJECT_ISR, 1)) /* ISR ID */
#define Wdg_Isr ((ISRType)OS_MKOBJID(OBJECT_ISR, 2)) /* ISR ID */
#define Gpt_PITRTI_TIMER_0_ISR ((ISRType)OS_MKOBJID(OBJECT_ISR, 3)) /* ISR ID */
#define Lin_LLD_InterruptHandler_ESCI_1 ((ISRType)OS_MKOBJID(OBJECT_ISR, 4)) /* ISR ID */
#define Spi_LLD_IsrEOQ_DSPI_1 ((ISRType)OS_MKOBJID(OBJECT_ISR, 5)) /* ISR ID */
#define Adc_Irq_eQADCA_CFIFO0_Empty ((ISRType)OS_MKOBJID(OBJECT_ISR, 6)) /* ISR ID */
#define Adc_Irq_eQADCA_RFIFO0_Full ((ISRType)OS_MKOBJID(OBJECT_ISR, 7)) /* ISR ID */
#define EMIOS_0_CH_8_ISR ((ISRType)OS_MKOBJID(OBJECT_ISR, 8)) /* ISR ID */
#define EMIOS_0_CH_9_ISR ((ISRType)OS_MKOBJID(OBJECT_ISR, 9)) /* ISR ID */

/* Resources definitions */
#define RES_SCHEDULER ((ResourceType)OS_MKOBJID(OBJECT_RESOURCE, 0)) /* Resource ID */

/* Events definition */
#define OsEvent_Task1 ((EventMaskType)0x1) /* Event mask */
#define OsEvent_Task2 ((EventMaskType)0x1) /* Event mask */
#define OsEvent_Task3 ((EventMaskType)0x1) /* Event mask */

/* Alarms identification */
#define OsAlarm_Task1 ((AlarmType)OS_MKOBJID(OBJECT_ALARM, 0)) /* Alarm ID */
#define OsAlarm_Task2 ((AlarmType)OS_MKOBJID(OBJECT_ALARM, 1)) /* Alarm ID */
#define OsAlarm_Task3 ((AlarmType)OS_MKOBJID(OBJECT_ALARM, 2)) /* Alarm ID */

/* Counters identification */
#define SYSTEMTIMER ((CounterType)OS_MKOBJID(OBJECT_COUNTER, 0)) /* Counter ID */
#define OSMINCYCLE_SYSTEMTIMER ((TickType)0x0) /* SYSTEMTIMER */
#define OSMAXALLOWEDVALUE_SYSTEMTIMER ((TickType)0xffffffff) /* SYSTEMTIMER */
#define OSTICKSPERBASE_SYSTEMTIMER 10UL    /* SYSTEMTIMER */
#define OS_TICKS2NS_SYSTEMTIMER(ticks) (PhysicalTimeType)((OSQWORD)(ticks)*7500ULL/1UL) /*  */
#define OS_TICKS2US_SYSTEMTIMER(ticks) (PhysicalTimeType)((OSQWORD)(ticks)*7500ULL/1000UL) /*  */
#define OS_TICKS2MS_SYSTEMTIMER(ticks) (PhysicalTimeType)((OSQWORD)(ticks)*7500ULL/1000000UL) /*  */
#define OS_TICKS2SEC_SYSTEMTIMER(ticks) (PhysicalTimeType)((OSQWORD)(ticks)*7500ULL/1000000000UL) /*  */
#define OSMINCYCLE ((TickType)0x0)         /* SysTimer */
#define OSMAXALLOWEDVALUE ((TickType)0xffffffff) /* SysTimer */
#define OSTICKSPERBASE 10UL                /* SysTimer */
#define OSTICKDURATION 7500UL              /* SysTimer */

/* Messages identification */

/* Flags identification */

/* Message callback prototypes */

/* scheduletable */
#define SCHEDTAB ((ScheduleTableType)OS_MKOBJID(OBJECT_SCHEDULETABLE, 0)) /* ScheduleTable ID */
#define OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED        
#include    "ossections.h"

#define OS_STOP_SEC_CONST_UNSPECIFIED      
#include    "ossections.h"

#define APP_STOP_SEC_CODE                  
#include    "ossections.h"

#endif /* OSCFG_H */

