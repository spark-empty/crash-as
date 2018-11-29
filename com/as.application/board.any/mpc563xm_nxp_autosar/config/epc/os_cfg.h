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
#define OSTaskShellSTKSIZE 2080            /* stack size of TaskShell */
#define OSTaskShellSTKBOS OSRUNNABLESTKBEG /* TaskShell bos */
#define OSTaskShellSTKTOS OSTaskShellSTKBOS + OSTaskShellSTKSIZE/4 /* TaskShell tos */

/* Task definitions */
#define TaskCanIf ((TaskType)OS_MKOBJID(OBJECT_TASK, 0)) /* Task ID */
extern void FuncTaskCanIf(void); /* Task entry point */
#define SchM_BswService ((TaskType)OS_MKOBJID(OBJECT_TASK, 1)) /* Task ID */
extern void FuncSchM_BswService(void); /* Task entry point */
#define SchM_Startup ((TaskType)OS_MKOBJID(OBJECT_TASK, 2)) /* Task ID */
extern void FuncSchM_Startup(void); /* Task entry point */
#define TaskApp ((TaskType)OS_MKOBJID(OBJECT_TASK, 3)) /* Task ID */
extern void FuncTaskApp(void); /* Task entry point */
#define TaskShell ((TaskType)OS_MKOBJID(OBJECT_TASK, 4)) /* Task ID */
extern void FuncTaskShell(void); /* Task entry point */
#define TaskIdle ((TaskType)OS_MKOBJID(OBJECT_TASK, 5)) /* Task ID */
extern void FuncTaskIdle(void); /* Task entry point */

/* ISR functions */

/* ISRs definition */
#define OSISRAdc_Irq_eQADCA_CFIFO0_Empty() OSISR1DISP(Adc_Irq_eQADCA_CFIFO0_Empty) /* IrqChannel is EXTERNAL */
extern void OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty(void); /* irq: Adc_Irq_eQADCA_CFIFO0_Empty; channel: EXTERNAL; category: 1 */
#define Adc_Irq_eQADCA_CFIFO0_EmptyLEVEL 5 /* interrupt level of Adc_Irq_eQADCA_CFIFO0_Empty */
#define Adc_Irq_eQADCA_CFIFO0_EmptyPRIORITY 5 /* priority of Adc_Irq_eQADCA_CFIFO0_Empty */
#define OSISRAdc_Irq_eQADCA_RFIFO0_Full() OSISR1DISP(Adc_Irq_eQADCA_RFIFO0_Full) /* IrqChannel is EXTERNAL */
extern void OS_isr_Adc_Irq_eQADCA_RFIFO0_Full(void); /* irq: Adc_Irq_eQADCA_RFIFO0_Full; channel: EXTERNAL; category: 1 */
#define Adc_Irq_eQADCA_RFIFO0_FullLEVEL 5  /* interrupt level of Adc_Irq_eQADCA_RFIFO0_Full */
#define Adc_Irq_eQADCA_RFIFO0_FullPRIORITY 5 /* priority of Adc_Irq_eQADCA_RFIFO0_Full */
#define OSISRRTI_TickHandler() OSISR2DISP(RTI_TickHandler) /* IrqChannel is EXTERNAL */
extern void OS_isr_RTI_TickHandler(void); /* irq: RTI_TickHandler; channel: EXTERNAL; category: 2 */
#define RTI_TickHandlerLEVEL 1             /* interrupt level of RTI_TickHandler */
#define RTI_TickHandlerPRIORITY 1          /* priority of RTI_TickHandler */
#define RTI_TickHandler ((ISRType)OS_MKOBJID(OBJECT_ISR, 0)) /* ISR ID */

/* ISR1 id */
#define Adc_Irq_eQADCA_CFIFO0_Empty ((ISRType)OS_MKOBJID(OBJECT_ISR, 2)) /* ISR ID */
#define Adc_Irq_eQADCA_RFIFO0_Full ((ISRType)OS_MKOBJID(OBJECT_ISR, 3)) /* ISR ID */

/* Resources definitions */
#define RES_SCHEDULER ((ResourceType)OS_MKOBJID(OBJECT_RESOURCE, 0)) /* Resource ID */

/* Events definition */
#define EventShellInput ((EventMaskType)1) /* Event mask */

/* Alarms identification */
#define AlarmApp ((AlarmType)OS_MKOBJID(OBJECT_ALARM, 0)) /* Alarm ID */
#define Alarm_BswService ((AlarmType)OS_MKOBJID(OBJECT_ALARM, 1)) /* Alarm ID */

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
#define OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED 
#include    "ossections.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED        
#include    "ossections.h"

#define OS_STOP_SEC_CONST_UNSPECIFIED      
#include    "ossections.h"

#define APP_STOP_SEC_CODE                  
#include    "ossections.h"

#endif /* OSCFG_H */

