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
* Description: OS property file
*
* Note: The implementation was used: AUTOSAR_MPC56xxAM
*       System Generator for AUTOSAR OS/MPC56xxAM - Version: 3.0 Build 3.0.35
*
********************************************************************************/

/* OSPROP configuration file */

#ifndef OSPROP_H
#define OSPROP_H                           

/* Timing protection */
#define OSNTPTSKARRIV 0                    /* The number of tasks with TIMEFRAME > 0  */
#define OSNTPTSKRESLOCKS 0                 /* number of all resource locking time configurations for TASKs */
#define OSNTPISRRESLOCKS 0                 /*  number of all resource locking time configurations for ISRs cat.2 */
#define OSNTPISRARRIV 0                    /* The number of ISR2 with TIMEFRAME > 0  */
#define OSNTPTSKBGTS 0                     /* The number of task with Execution Budget > 0 */
#define OSNTPISRBGTS 0                     /* The number of ISR2 with Execution Time > 0 */
#define OSNTPBGTS 0                        /* The number of task with execution budget  and ISR2 with execution time (OSNTPBGTS=OSNTPTSKBGTS+OSNTPISRBGTS) */
#define OSNTPTSKINTLOCKTIME 0              /* The number of task with OS Interrupt Lock Time */
#define OSNTPISRINTLOCKTIME 0              /* The number of ISR2 with OS Interrupt Lock Time */
#define OSNTPTSKRESLOCKTIME 0              /* The number of task with at least one Resource Lock Time */
#define OSNTPISRRESLOCKTIME 0              /* The number of ISR2 with at least one Resource Lock Time */

/* Implementation */

#define OSMPC56xxAM                        

/* Target MCU */

#ifndef OSMPC5634M
#define OSMPC5634M                         /* Target MCU */

#endif
#define OSSTKSIZE 2080                     /* Common stack size */

/* Applications */

#define OSNAPPS 0                          /* number of OS-applications */
#define OSNTRUSTEDFUNCTIONS 0              /* number of trusted functions */
#define OSNNOTTRUSTEDAPPS 0                /* number of not trusted applications */
#define OSNMEMDATA0 0                      /* number of nontrusted application with data in region #0 */
#define OSNMEMDATA1 0                      /* number of nontrusted application with data in region #1 */
#define OSNMEMDATA2 0                      /* number of nontrusted application with data in region #2 */

/* Scalability Class */

#define OSSC1                              /* Scalability Class */

/* Conformance Class */

#define OSECC1                             /* Conformance Class */

/* Scheduler Policy */

#define OSFULLPREEMPT                      /* preemptive schedule pollicy is set */
#define OSNOFASTTERMINATE                  /* FastTerminate attribute is set to FALSE */
#define OSRES_SCHEDULER                    /* USERESSCHEDULER attribute has TRUE value */
#define OSEXTSTATUS                        /* STATUS attribute has the EXTENDED value */
#define OSORTIDEBUGLEVEL 2                 /* value of DEBUG_LEVEL attribute */
#define OSSTKCHECK                         /* attribute StackOverflowCheck is set to TRUE */
#define OSSTKCHECKPATTERN 3735901610       /* equal to StackOverflowCheck/Pattern */
#define OSSTKCHECKPATTERNSIZE 4            /* equal to StackOverflowCheck/PatternSize */

/* Hook routines */

#define OSHOOKSTARTUP                      /* STARTUPHOOK is set to TRUE */

/* ISRs categories support */

#define OSISRSTACKSIZE 204U                /*  */

/* Interrupt management */

#define OSISRENTRYEXIT                     /* ISR entry/exit frames must be implemented */

/* Timing protection */


/* Communication mechanism */


/* Counters and Alarms mechanisms */

#define OSNHWCTRS 1                        /* equal to number of system timers of type HWCOUNTER (0, 1 or 2) */
#define OSHWCOUNTER                        /*  */
#define OSSYSTIMER                         /* SysTimer has the HWCOUNTER or SWCOUNTER value */
#define OSNSYSTMRS 1                       /*  */
#define OSTIMSTM                           /* Hardware for System/Second timer */
#define OSTIMCHAN 0                        /* Hardware channel for System timer */
#define OSSYSTIMFREEZE                     /* Freeze in SysTimer is set to TRUE */
#define OS_TIMER_STKSIZE 128               /* system/second timer stack size in dwords */
#define OSTIMPRESCALER 59                  /* SysTimer has the HWCOUNTER or SWCOUNTER value and Prescaler is set to OS and Prescaler/Value is applicable for corresponding timer hardware */
#define OSTIMPRIO 1                        /*  */
#define OSALMACTIVTASK                     /* at least one alarm has the ACTION = ACTIVATETASK */
#define OSNAPPMODES 1                      /*  */
#define OSNTSKS 6                          /* equal to  number of TASK objects  */
#define OSNXTSKS 1                         /* equal to  number of extended TASK objects */
#define OSNMAXREADYTSKS 10                 /*  */
#define OSNISRRESS 0                       /* number of RESOURCEs which are used by ISRs */
#define OSNRESS 1                          /* The number of RESOURCEs with task priority, STANDARD or LINKED plus resscheduler */
#define OSRESOURCE                         /* at least one resource with task priority and RESOURCEPROPERTY = STANDARD (including RES_SCHEDULER) is defined */
#define OSNCTRS 1                          /* equal to number of COUNTER objects */
#define OSCOUNTER                          /* defined if at least one COUNTER object defined  */
#define OSNUSERALMS 2                      /*  */
#define OSNSCTALMS 0                       /*  */
#define OSNALMS (OSNUSERALMS + OSNSCTALMS) /* equal to number of ALARM objects */
#define OSALARM                            /* at least one ALARM object defined */
#define OSNAUTOALMS 2                      /* equal to number of auto-start alarms */
#define OSNMSGS 0                          /* equal to the number of MESSAGE objects */
#define OSNNONTRUSTEDTSKS 0                /* Number of tasks which belongs to nontrusted applications  */
#define OSNNONTRUSTEDISR 0                 /* Number of user's ISR2 which belongs to nontrusted applications  */
#define OSNUSERISR 1                       /*  */
#define OSNISR 4                           /* equal to summ of number ISR, system timers and TPTimer */
#define OSHIGHISRPRIO 1                    /* equal to the highest ISR(category 2)/SysTimer/SecondTimer (ISR)PRIORITY */
#define OSNIPLS 1                          /*  */

/* Schedule table */

#define OSNSCTS 0                          /*  */
#define OSNAUTOSCTS 0                      /*  */
#endif /* OSPROP_H */

