#ifndef OSBASAPI_H
#define OSBASAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osbasapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Basic API for OSEK OS (types, defines etc.)         
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* ram, rom definitions for Sysgen compatiblity */
#define __rom       const               /* ROM-based data */
#define __ram                           /* RAM-based data */

/* definitions for INLINE functions */	
#if defined(OSDIABPPC)	
#define OSASM                 __asm volatile
#define OSNEAR                __attribute__(( section(".ossdata") ))
#define OSINLINE              __inline__      /* This string should be decommented for the inline fuction using in ISR */
#define OSCNTLZW( x )         __ff1( x )
#endif /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
#define OSASM                 asm
#define OSNEAR                __declspec(section ".ossdata")
#define OSINLINE              inline
#define OSCNTLZW( x )         __cntlzw( x )
#endif /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSASM                 asm
#define OSNEAR
#ifdef __cplusplus
#define OSINLINE              inline
#else
#define OSINLINE              __inline
#endif
#define OSCNTLZW( x )         __CLZ32( x )
#define OSMTSPR( spr, value ) __MTSPR( spr, value )
#define OSMFSPR( spr )        __MFSPR( spr )
#endif /* defined(OSGHSPPC) */

/* definitions for assembler functions */	
#if defined(OSDIABPPC) || defined(OSGHSPPC)
#define OSSTRING(x) #x
#define OSASMF(x) OSASM (" "OSSTRING(x)" ")
#define OSASMF2(x,x1) OSASM (" "OSSTRING(x)","OSSTRING(x1)" ")
#define OSASMF3(x,x1,x2) OSASM (" "OSSTRING(x)","OSSTRING(x1)","OSSTRING(x2)" ")
#define OSASMF4(x,x1,x2,x3) OSASM (" "OSSTRING(x)","OSSTRING(x1)","OSSTRING(x2)","OSSTRING(x3)" ")
#define OSASMF5(x,x1,x2,x3,x4) OSASM (" "OSSTRING(x)","OSSTRING(x1)","OSSTRING(x2)","OSSTRING(x3)","OSSTRING(x4)" ")	
#endif /* defined(OSDIABPPC) || defined(OSGHSPPC) */

#if defined(OSCWPPC)
#define OSASMF(x)  x
#define OSASMF2(x,x1)  x,x1	
#define OSASMF3(x,x1,x2) x,x1,x2
#define OSASMF4(x,x1,x2,x3) x,x1,x2,x3
#define OSASMF5(x,x1,x2,x3,x4) x,x1,x2,x3,x4	
#endif /* defined(OSCWPPC) */	
	
#define OSDECLAREVAR(var_type, var) var_type var
#define OSUSEVAR(var) var
#define OSGETCOREID

/*  Data types */
#if !defined(STATUSTYPEDEFINED)                 /* presribed by OSEK/VDX */
#define STATUSTYPEDEFINED                       /* required by OSEK/VDX Binding Specification */
typedef unsigned char       StatusType;         /* OSEK: Status type             */
#define E_OK                0                   /* No error, successful completion  */
#endif  /* !defined(STATUSTYPEDEFINED) */

typedef unsigned char       OSBYTE;
typedef unsigned char      *OSBYTEPTR;
typedef unsigned short      OSWORD;
typedef signed short        OSSHORT;
typedef unsigned short      *OSWORDPTR;
typedef unsigned int        OSDWORD;
typedef unsigned long long  OSQWORD;
typedef unsigned int        OSCARDINAL;
typedef signed int          OSSIGNEDDWORD;
typedef signed long long    OSSIGNEDQWORD;

#define OSDWORDMSB          0x80000000ul

typedef void *TrustedFunctionParameterRefType;
typedef OSWORD  TrustedFunctionIndexType;
typedef void (*OS_TRUSTED_FUNCTION)(TrustedFunctionIndexType, TrustedFunctionParameterRefType); 

#define OSFALSE         (0u)
#define OSTRUE          (1u)

/* Private OS types */
typedef OSBYTE  OSServiceIdType;

typedef OSWORD OSObjectType;             /* bits [0..10] - obj Id, bits [11..13] - Obj Type */
#define OSOBJMASK   (OSWORD)0x07FF
#define OSTYPMASK   (OSWORD)0x3800
#define OSOBJSHIFT  0x0B                 /* shift to Type Mask */

#define OS_PID_APPSTK 1u    /* osstack area usage with application rights (RW only for runable stack) */
#define OS_PID_OSSTK  2u    /* osstack area usage with OS rights (RW for all osstack area) */

#define INVALID_OSAPPLICATION (ApplicationType) OSNAPPS

typedef enum { NO_RESTART, RESTART } RestartType; /* RestartOption for TerminateApplication */
typedef enum { OSNONTRUSTEDISR2, OSTRUSTEDISR2, OSISR1, OSSYSINTERRUPT, OSTPISR1 } OSISRTYPE;

#if defined(OSEXTSTATUS) || defined(OSCOMEXTSTATUS)
/* macro for SysGen, used in cfg files */
#define OS_MKOBJID(ObjTyp, ObjInd) (ObjTyp<<OSOBJSHIFT | ObjInd)
/* macro to get Object number (index), used in cfg.c */
#define OS_GETOBJIND(ObjId) (ObjId & OSOBJMASK)
/* macro to get Object Type, assuming bits[14,15] == 0 */
#define OS_GETOBJTYP(ObjId) (ObjId >> OSOBJSHIFT)
#else  /* defined(OSEXTSTATUS) || defined(OSCOMEXTSTATUS) */
#define OS_MKOBJID(ObjTyp, ObjInd) ObjInd
#define OS_GETOBJIND(ObjId) ObjId
#endif /* defined(OSEXTSTATUS) || defined(OSCOMEXTSTATUS) */

typedef OSDWORD             OSTASKTYPE;     /* for internal representation (then compiler don't recast register to TaskType */

#if defined(OSNOFASTTERMINATE)
typedef void                (*OSTASKENTRY)( void );
#else
typedef OSTASKTYPE  (*OSTASKENTRY)( void );
#endif

#if defined(OSMEMPROTECTION)
typedef  void          (*OSSRV)( void );
#endif

typedef OSDWORD             OSINTMASKTYPE;          /*  Interrupt mask                              */
typedef OSDWORD             OSISRLEVELTYPE;         /*  system level type, see osisrapi.h:OsIsrLevel for comments       */
typedef unsigned char       OSSUSPENDLEVELTYPE; 
typedef void                (*OSCALLBACK)( void );
typedef signed char         OSPRIOTYPE;
typedef void                (*OSHKSTARTUP)( void );
typedef void                (* OSHKERROR)(StatusType);
typedef void                (* OSHKSHUTDOWN)( StatusType );
typedef OSObjectType        TaskType;
typedef OSDWORD             PhysicalTimeType;


/* Public OSEK & AUTOSAR types */

typedef OSBYTE ApplicationType;
typedef OSBYTE ObjectTypeType;
typedef void* MemoryStartAddressType;
typedef OSDWORD MemorySizeType;

/* Counter ticks */     
typedef OSObjectType        CounterType;
typedef OSDWORD             TickType;           /* Type for timers ticks */
typedef TickType*           TickRefType;        /* OSEK: Reference to counter value */

/* Standard Constants of ObjectTypeType */
#define     OBJECT_TASK               ((ObjectTypeType)1)
#define     OBJECT_ISR                ((ObjectTypeType)2)
#define     OBJECT_ALARM              ((ObjectTypeType)3)
#define     OBJECT_RESOURCE           ((ObjectTypeType)4)
#define     OBJECT_COUNTER            ((ObjectTypeType)5)
#define     OBJECT_SCHEDULETABLE      ((ObjectTypeType)6)
#define     OBJECT_MESSAGE            ((ObjectTypeType)7)
#define     OBJECT_SPINLOCK           ((ObjectTypeType)8)
#define     OBJECT_CORE               ((ObjectTypeType)9)
/* Pseudo objects which used only with timing protection (only for AUTOSAR spec.2) */

typedef OSBYTE ObjectAccessType;
/* Standard Constants of ObjectAccessType */
#define     ACCESS                  ((ObjectAccessType)0)
#define     NO_ACCESS               ((ObjectAccessType)1)

/* AccessType holds information how a specific memory region can be accessed */
typedef OSBYTE AccessType;
#define OSMP_R ((AccessType)1)
#define OSMP_W ((AccessType)2)
#define OSMP_E ((AccessType)4)
#define OSMP_S ((AccessType)8)

/* These macros return a value not equal to zero if the memory is
   readable / writable / executable or stack space */
#define OSMEMORY_IS_READABLE(x)   ( ((x) & OSMP_R) != 0 )
#define OSMEMORY_IS_WRITEABLE(x)  ( ((x) & OSMP_W) != 0 )
#define OSMEMORY_IS_EXECUTABLE(x) ( ((x) & OSMP_E) != 0 )
#define OSMEMORY_IS_STACKSPACE(x) ( ((x) & OSMP_S) != 0 )

typedef unsigned char       AppModeType;        /* OSEK: Application mode type   */
typedef TaskType            *TaskRefType;
typedef unsigned char       TaskStateType;
typedef TaskStateType       *TaskStateRefType;
typedef OSObjectType        ISRType;
typedef OSDWORD             EventMaskType;
typedef EventMaskType       *EventMaskRefType;

#if defined(OSRESOURCE)
#define OSNALLRES (OSNRESS + OSNISRRESS)

typedef OSObjectType        ResourceType;
#endif

#if defined(OSDIABPPC)
#define OSWARNSUPPRESS
#endif /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
#define OSWARNSUPPRESS  OSASM volatile { .warn_def_reserved_reg off; }
#endif /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSWARNSUPPRESS
#endif /* defined(OSGHSPPC) */

#if defined(OSDIABPPC)
#define OSINTERRUPT         __interrupt__
#define OSINTERRUPTNEST     __interrupt__
#define OSSTACKTOP          __SP_INIT
#define OSSTACKBOTTOM       __SP_END
#endif /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
#define OSINTERRUPT         __declspec(interrupt)
#define OSINTERRUPTNEST     __declspec(interrupt SRR)
#define OSSTACKTOP          _stack_addr
#define OSSTACKBOTTOM       _stack_end
#endif /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSINTERRUPT         __interrupt
#define OSINTERRUPTNEST     __interrupt
#define OSSTACKTOP          _stack_addr
#define OSSTACKBOTTOM       _stack_end
#endif  /* defined(OSGHSPPC) */


/* ISR Management Mode Configuration */
#if defined(OSTIMINGPROTECTION)
#define OSHIGHINTPRIO OSHIGHTPISRPRIO
#else
#define OSHIGHINTPRIO OSHIGHISRPRIO
#endif /* defined(OSTIMINGPROTECTION) */

#if defined(OSISRENTRYEXIT) || defined(OSTIMINGPROTECTION)
/* defines the "save" local variables for current interrupts state saving */
/* `;' shall be in the definition to avoid it inside local variables declaration */
#define OSIMSAVE  OSINTMASKTYPE save;
#else
#define OSIMSAVE
#endif

/* Scheduler vector width */
#define OSSCHMAXBITNUM 32
#if defined(OSEXTPRIORS)
#define OSSCHWIDE       2           /* Number of scheduler registers/variables */
#else   /* defined(OSEXTPRIORS) */
#define OSSCHWIDE       1           /* Number of scheduler registers/variables */
#endif  /* defined(OSEXTPRIORS) */

#define OSSCHEDULERVECTORSIZE ( 32 * OSSCHWIDE )

#define OSSTKADDS 2                 /* additional stack space for compiler */

#if defined(OSUSETCB)

#define OSHASRUNNINGTASK        (OsRunning != &OsTaskTable[OSNULLTASK])
#define OSRUNNINGSTATUS         OsRunning->status
#define OSTASKCB(taskId)        OsTaskTable[taskId]
#define OSTASKSTATUS(taskId)    OsTaskTable[taskId].status
#define OSREMOVETASK(task)      OSTask2Suspend(task->taskId)
#define OSTSKPRIO(task)         task->taskId
#define OSTSKIND(task)          task->taskId
#define OS_TASK_ENTRY_PTR       OsRunning->entry
#define OSCallTask()            (*OsRunning->entry)()

#if defined(OSRESOURCE) || defined(OSINRES)
#define OSGETTASK(prio)         OsPrioLink[prio]
#define OSGETMAXPRIOTASK        OSGETTASK( OSGetReadyTask() )
#else   /* defined(OSRESOURCE) || defined(OSINRES) */
#define OSGETTASK(prio)         (&OsTaskTable[prio])
#define OSGETMAXPRIOTASK        OSGETTASK( OSPRIO2TASKID( OSGetReadyTask() ) )
#endif  /* defined(OSRESOURCE) */

#else   /* defined(OSUSETCB) */

#define OSHASRUNNINGTASK (OsRunning != OSNULLTASK)
#define OSRUNNINGSTATUS OsTaskStatus[OsRunning]
#define OSTASKSTATUS(taskId)    OsTaskStatus[taskId]   
#define OSREMOVETASK(taskId)    OSTask2Suspend(taskId)
#define OSTSKIND(task)          task
#define OSTSKPRIO(task)         task
#define OS_TASK_ENTRY_PTR       OsTaskEntry[OsRunning]
#define OSCallTask()            (*OsTaskEntry[OsRunning])()

#if defined(OSINRES)
#define OSGETTASK(prio)         OsPrio2Task[prio]
#else   /* defined(OSINRES) */
#define OSGETTASK(prio)         prio
#endif  /* defined(OSINRES) */

#define OSGETMAXPRIOTASK        OSGETTASK(OSGetReadyTask())
#endif  /* defined(OSUSETCB) */

#define OSAPPIDISINVALID(appId)   (OS_GETOBJIND(appId) >= (OSNAPPS))
#define OSTASKIDISINVALID(taskId) ((OS_GETOBJTYP(taskId) != OBJECT_TASK) || (taskId >= OS_MKOBJID(OBJECT_TASK,OSNTSKS)))
#define OSISRIDISINVALID(isrId)   ((OS_GETOBJTYP(isrId) != OBJECT_ISR) || (isrId >= OS_MKOBJID(OBJECT_ISR, OSNISR)))

#if defined(OSUSETCB) || defined(OSINRES)
#define OSISTASKNOSUSPEND(taskId)   (OSTASKSTATUS(taskId) & OSTCBNOSUSPENDED)
#else   
#define OSISTASKNOSUSPEND(taskId)   OSCHECKTASKSTATUS(taskId)
#endif  

#define OSTASKACTEXHAUSTED(taskId)   OSISTASKNOSUSPEND(taskId)


/* Internal Resources */
#if defined(OSINRES)

#if defined(OSUSETCB)
#define OSTASKRUNPRIO(task)     task->runprio
#define OSSETBITRUNPRIO()       OSSetPrioBit(OSTASKRUNPRIO(OsRunning)); \
                                OsPrioLink[OSTASKRUNPRIO(OsRunning)] = OsRunning
#define OSSETRUNPRIO()          OsRunning->prio2Task = OsPrioLink[OSTASKRUNPRIO(OsRunning)]; \
                                OSSETBITRUNPRIO()
#define OSRESETRUNPRIO()        (OsPrioLink[OSTASKRUNPRIO(OsRunning)] = OsRunning->prio2Task)

#else   /* defined(OSUSETCB) */
#define OSSETBITRUNPRIO()       OSSetPrioBit(OSTASKRUNPRIO(OsRunning)); \
                                OsPrio2Task[OSTASKRUNPRIO(OsRunning)] = OsRunning
#define OSTASKRUNPRIO(task)     OsTaskRunPrio[task]
#define OSSETRUNPRIO()          OSSETBITRUNPRIO();
#define OSRESETRUNPRIO()        (OsPrio2Task[OSTASKRUNPRIO(OsRunning)] = OSTASKRUNPRIO(OsRunning))
#endif  /* defined(OSUSETCB) */

#if defined(OSECC)
#define OSCLEARRUNPRIOBITISNECESSARY() \
    (( OSTASKRUNPRIO( OsRunning ) != OSTSKPRIO(OsRunning) ) && \
    ((OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO( OsRunning ) ) ) & (OSTCBNOSUSPENDED | \
    OSTCBWAIT)) != OSTCBNOSUSPENDED))
#else   /* defined(OSECC) */
#define OSCLEARRUNPRIOBITISNECESSARY() \
    (( OSTASKRUNPRIO( OsRunning ) != OSTSKPRIO(OsRunning) ) && \
    ((OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO( OsRunning ) ) ) & OSTCBNOSUSPENDED) != OSTCBNOSUSPENDED))
#endif  /* defined(OSECC) */

#else   /* defined(OSINRES) */

#define OSSETRUNPRIO()
#define OSSETBITRUNPRIO()

#endif  /* defined(OSINRES) */

#if defined(OSUSETCB) 
typedef struct  TagOSTSKCB  OSTSKCB;            /* Task control block */
typedef         OSTSKCB     *OSTSKCBPTR;        /* Pointer to the task control block */
#endif

#if defined(OSTIMINGPROTECTION) 

/* --- TP types --- */

typedef OSDWORD OSTPTICKTYPE;

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
typedef struct TagOSTPResLock   OSTPRESLOCK;
typedef OSTPRESLOCK OSTPLOCK;

/* TP configuration/control block of resource locking time */
struct TagOSTPResLock
{
    OSTPTICKTYPE lockTime;      /* resource locking time */
    OSWORD resId;               /* resource id */  
};
#endif

#define OSTP_MKOBJID(ObjTyp, ObjInd)    ( (ObjTyp<<OSOBJSHIFT) | ObjInd)
/* macro to get Object number (index) */
#define OSTP_GETOBJIND(ObjId)           ( ObjId & OSOBJMASK )
/* macro to get Object Type, assuming bits[14,15] == 0 */
#define OSTP_GETOBJTYP(ObjId)           ( ObjId >> OSOBJSHIFT )

#endif /* defined(OSTIMINGPROTECTION) */


/* Resources */
#if defined(OSRESOURCE)
typedef struct  TagOSRESCB  OSRESCB;
typedef OSRESCB             *OSResType;

struct TagOSRESCB
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;            /* Application identification mask value */
#endif
    OSPRIOTYPE      prio;               /* Resource priority for task resources */
    OSTSKCBPTR      prio2task;          /* to save the OsPrioLink[]/ISR rast resource previous value  */
#if defined(OSRESOURCEISR)
    OSINTMASKTYPE   savedIsrMask;       /* previous Interrupt mask */
#endif  /* defined(OSRESOURCEISR) */
#if defined(OSUSERESLINK)
    OSResType       nextRes;            /* Link to next item in the resource list */
#endif
#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
    OSTPTICKTYPE    tpRemained;         /* remained time on resource locking time */        
    OSResType       tpNextRes;          /* Link to next item in the list of resources with started TP */
#endif
#if (OSORTIDEBUGLEVEL > 0) || defined(OSEXTSTATUS)
    OSBYTE          isUsed;             /* Flag that the resource is used */
#endif  /*OSORTIDEBUGLEVEL > 0*/
#if (OSORTIDEBUGLEVEL > 0)
    OSPRIOTYPE      curPrio;            /* current task priority */
#endif  /* (OSORTIDEBUGLEVEL > 0) */
#if defined(OSAPPLICATION)
    ApplicationType appId;              /* application identification value */
#endif
};


#if defined(OSAPPLICATION)
struct TagOSRESCFG
{
    OSDWORD         appMask;            /* Application identification mask value */
    OSPRIOTYPE      prio;               /* Resource priority for task resources */
    ApplicationType appId;              /* application identification value */
};
typedef struct  TagOSRESCFG OSRESCFG;
#endif

#endif /* defined(OSRESOURCE) */


/* Tasks */

#if defined(OSUSETCB) 

#if defined(OSSC1)
#define OSJBLEN (21 + 1)                /* 21 GPRs + SPRG2 saved; (library _JBLEN is 26) */
#define OSSSP (OSJBLEN - 1)             /* Index for SingleStackPointer in the Task context */
#else
#define OSJBLEN (21)                    /* 21 registers saved */
#endif 

/*  Contexts of tasks */
/* OSJBLEN is defined in ostarget.h; OSNTSKS is defined in osprop.h */
typedef OSDWORD OSJMP_BUF[OSJBLEN];

/* Task configuration table */ 
struct TagOSTSK
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;            /* Application identification mask value */
#endif
    OSTASKENTRY     entry;              /* entry point of task */
#if (OSNAPPMODES > 1)            
    OSDWORD         autostart;
#endif  /* (OSNAPPMODES > 1) */
#if defined(OSUSETOS)
    OSDWORD*        tos;                /* top of task stack */
#if defined(OSUSEBOS)            
    OSDWORD*        bos;                /* bottom of task stack */
#endif  
#endif  /* defined(OSUSETOS)*/
#if defined(OSTIMINGPROTECTION)
#if  (OSNTPTSKBGTS > 0) 
    OSTPTICKTYPE    tpExecBudget;       /* execution budget for TASK */
#endif
#if  (OSNTPTSKARRIV > 0) 
    OSTPTICKTYPE    tpTimeFrame;        /* time frame for task */
#endif 
#if (OSNTPTSKINTLOCKTIME > 0)
    OSTPTICKTYPE    tpIntLockTime;      /* interrupt locking time */
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
    const OSTPRESLOCK    *tpResLock;    /* pointer to array with resource locking time configurations  */
    OSWORD          tpNumberResLock;    /* number of resource with locking time for this task */
#endif
#endif /* defined(OSTIMINGPROTECTION) */
#if defined(OSINRES)
    OSBYTE          runprio;            /* running prio (internal resource) */
#endif  /* defined(OSINRES) */
    OSBYTE          property;           /* properties of task OSTSKACTIVATE, OSTSKEXTENDED, OSTSKNONPREMPT */
    TaskType        taskId;             /* task id (task number in the task table) */

#if defined(OSAPPLICATION)
    ApplicationType appId;              /* application identification value */
#endif
};

typedef struct  TagOSTSK    OSTSK;              /* Task configuration table */
typedef         OSTSK       *OSTSKPTR;          /* Pointer to the task configuration table */
#define OSTSKPTR0           ( (OSTSKPTR)0 )     /* Null-pointer */

/* Task control block structure */
struct TagOSTSKCB
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;            /* Application identification mask value */
#endif
    OSTASKENTRY     entry;              /* entry point of task */
#if defined(OSUSETOS)
    OSDWORD*        tos;                /* top of task stack */
#if defined(OSUSEBOS)            
    OSDWORD*        bos;                /* bottom of task stack */
#endif
#endif  /* defined(OSUSETOS) */
#if (OSNXTSKS > 0)
    /*  Attributes of extended task */
    EventMaskType   wait_event;         /* mask of waited events */
    EventMaskType   set_event;          /* mask of set events    */
#endif  /* OSNXTSKS > 0 */
    OSJMP_BUF       context;            /* task context (stored by setjmp function) */
#if defined(OSUSERESLINK)
    OSResType       resources;          /* The head of the occupied resources list */
#endif
#if (OSORTIDEBUGLEVEL > 0) && defined(OSRESOURCE)
    OSPRIOTYPE      curPrio;            /* current task priority */
#endif 
#if defined(OSINRES)
    OSBYTE          runprio;            /* running prio (internal resource) */
    OSTSKCBPTR      prio2Task;          /* references from priority to task */ 
#endif  /* defined(OSINRES) */
    OSBYTE          status;             /* task status (initial equal propery ) */
    TaskType        taskId;             /* task id (task number in task table)  */
#if defined(OSAPPLICATION)
    ApplicationType appId;              /* application identification value */
#endif
#if defined(OSTIMINGPROTECTION)
#if  (OSNTPTSKBGTS > 0) 
    OSTPTICKTYPE    tpExecBudget;       /* the execution budget */
    OSTPTICKTYPE    tpRemained;         /* remained time on the budget */
#endif
#if  (OSNTPTSKARRIV > 0) 
    OSTPTICKTYPE    tpTimeFrame;        /* time frame */
    OSSIGNEDQWORD   tpLast;             /* 63-bit time of last successful transition to 'ready' state */   
#endif 
#if (OSNTPTSKINTLOCKTIME > 0)
    OSTPTICKTYPE    tpIntLockTime;      /* interrupt locking time */
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
    OSTPRESLOCK     *tpResLock;         /* pointer to array with resource locking time configurations  */
    OSResType       tpResources;        /* The head of the list of occupied resources with started TP */
    OSWORD          tpNumberResLock;    /* number of resource with locking time */
#endif
#endif /* defined(OSTIMINGPROTECTION) */
};

#else  /* if task CB is not used */
#define OSJBLEN (21)                /* 21 registers saved */
#endif /* defined(OSUSETCB) */



#if (OSNALMS > 0)
typedef struct TagOSREFALM* OSAlmType;          /* OS internal type - pointer to the alarm node    */
#endif

/* Counters */

/* Counter configuration table      */
struct TagOSCTR
{           /*  Configuration Data  */
#if defined(OSAPPLICATION)
    OSDWORD         appMask;                    /* Application identification mask value */
#endif
    TickType        maxallowedvalue;
    TickType        ticksperbase;               /* conversion constant  */
#if defined(OSEXTSTATUS)
    TickType        mincycle;                   /* minimum period value for alarm   */
#endif  /* defined(OSEXTSTATUS) */
#if defined(OSAPPLICATION)
    ApplicationType appId;                      /* application identification value */
#endif
};

typedef struct  TagOSCTR    OSCTR;              /* Counter configuration table  */

typedef         OSCTR       *OSCTRPTR;          /* Pointer to the counter configuration table   */

/* Counter control block            */
struct TagOSCTRCB                               /* counter control block (node)         */
{
#if (OSNALMS > 0)
    OSAlmType       alarm;                      /* pointer to assigned running alarms   */
#endif  
#if defined(OSAPPLICATION)
    OSDWORD         appMask;                    /* Application identification mask value */
#endif
    TickType        value;                      /* current value of counter             */
#if defined(OSAPPLICATION)
    ApplicationType appId;                      /* application identification value */
#endif
};

typedef struct  TagOSCTRCB  OSCTRCB;            /* Counter configuration table  */

typedef         OSCTRCB     *OSCTRCBPTR;        /* Pointer to the counter configuration table   */

#define OSCTRCBPTR0         ( (OSCTRPTR)0 )     /* Null-pointer */
#define OSCTR0              OSNCTRS             /* Id for unused counter */


/* Alarms */

#if (OSNALMS > 0)

struct TagOSALMACT                              /* Structure of the alarm action    */
{       /* used in Alarms and Schedule Tables for Task Activation and Events only   */
    OSWORD          taskIndex;                  /* Task to start or to set Event    */
#if  defined(OSALMSETEVENT) || defined(OSSCTSETEVENT)  
    EventMaskType   event;                      /* if event==0 alarm activates task */
                                                /* else it sets event for this task */
#endif  /* defined(OSALMSETEVENT) || defined(OSSCTSETEVENT) */
};

typedef struct TagOSALMACT  OSALMACT;           /* Alarm action */

#if defined(OSALMCALLBACK) 
typedef void          (*OSHOOKENTRY)( void );
#endif  /* defined(OSALMCALLBACK) */

#if (OSNUSERALMS > 0)
struct TagOSALM                                 /* Structure of the alarm cfg table */
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;                    /* Application access mask          */
#endif
    OSWORD          taskIndex;                  /* Task to start or to set Event    */
#if defined(OSECC) && defined(OSALMSETEVENT) && (OSNXTSKS > 0)
    EventMaskType   event;                      /* if event==0 alarm activates task */
                                                /* else it sets event for this task */
#endif  /*  defined(OSECC) && defined(OSALMSETEVENT) && (OSNXTSKS>0) */
    OSWORD          ctrIndex;                   /* attached Counter ID  */
#if defined(OSALMCALLBACK)
    OSHOOKENTRY     callBack;                   /* Alarms' hook entry  */
#endif  /* defined(OSALMCALLBACK) */
#if defined(OSALMINCCOUNTER) 
    OSWORD          ctrIndexInc;                /* Alarms' increment counter */
#endif  /* defined(OSALMCALLBACK) */
#if defined(OSAPPLICATION)
    ApplicationType appId;                      /* application identification value */
#endif
};

typedef struct TagOSALM     OSALM;              /* Alarm configuration table    */

/* Structure of the alarm control block  */
struct TagOSALMCB
{
        /* this field shall be first in the record because it is used in OsCheckAlarms */
    OSAlmType       next;                       /* next alarm in the list */
    OSAlmType       prev;                       /* previous alarm in the list   */
    TickType        value;                      /* Alarms' expiration value   */
    TickType        cycle;                      /* period value for cyclic alarm    */
/*  Copy of Configuration Data  */
    OSWORD          ctrIndex;                   /* attached Counter ID  */
#if defined(OSALMINCCOUNTER) 
    OSWORD          ctrIndexInc;                /* Alarms' increment counter */
#endif  /* defined(OSALMCALLBACK) */
#if defined(OSAPPLICATION) 
#if (OSNUSERALMS > 0)
    OSDWORD         appMask;                    /* Application access mask          */
#endif
#endif
#if (OSNUSERALMS > 0)
    OSALMACT        action;                     /* Alarm action */
#endif  /* (OSNUSERALMS > 0) */
#if defined(OSALMCALLBACK)
    OSHOOKENTRY     callBack;                   /* Alarms' hook entry  */
#endif  /* defined(OSALMCALLBACK) */
#if defined(OSAPPLICATION) 
#if (OSNUSERALMS > 0)
    ApplicationType appId;                      /* application identification value */
#endif
#endif
};

typedef struct TagOSALMCB   OSALMCB;            /* Alarm control block (node)   */
#endif /* (OSNUSERALMS > 0) */

/* Schedule tables  */
#if (OSNSCTS > 0)   
typedef struct TagOSSCTEP OSSCTEP;

struct TagOSSCTEP                               /* The expiry point structure */
{
    const OSSCTEP           *next;              /* the next expiry point */
    OSALMACT                action;
    TickType                delta;              /* the time space (in ticks) between the current expiry point 
                                                   and the next expiry point (or the end of the schedule if it's 
                                                   last expiry point) */
#if defined(OSSCTSYNCEXPLICIT)                  /* fields for syncronization with explicit strategy */
    TickType                maxRetard;          /* schedule table MAXRETARD values */  
    TickType                maxAdvance;         /* schedule table MAXADVANCE values */ 
#endif
};

struct TagOSSCT                                 /* Structure of the schedule table cfg  */
{
    OSWORD                  ctrIndex;           /* attached Counter ID  */
    TickType                length;             /* the length of the schedule table in ticks */
    TickType                initialOffset;      /* initial offset */
    const OSSCTEP           *firstEP;           /* the pointer to first expiry point in the schedule table */
#if defined(OSSCTSYNCEXPLICIT)
    TickType                precision;          /* schedule table EXPLICITPRECISION value */ 
#endif
#if defined(OSAPPLICATION)
    OSDWORD                 appMask;            /* Application identification mask value */
    ApplicationType         appId;              /* Application identification value */
#endif
    OSBYTE                  opts;               /* config byte of the schedule table */
};

typedef struct TagOSSCT     OSSCT;              /* Schedule table cfg */

struct TagOSSCTALM
{
        /* this field shall be first in the record because it is used in OsCheckAlarms */
    OSAlmType       next;                       /* next alarm in the list */
    OSAlmType       prev;                       /* previous alarm in the list   */
    TickType        value;                      /* Alarms' expiration value   */
    TickType        cycle;                      /* period value for cyclic alarm    */
    OSWORD          ctrIndex;                   /* attached Counter ID  */
};

typedef struct TagOSSCTALM  OSSCTALMCB;         /* Schedule table alarm control block (node) */


typedef struct TagOSSCTCB   OSSCTCB;            /* Schedule table control block */

struct TagOSSCTCB                               /* Structure of the schedule table control block  */
{
    /* Current Data */
    const OSSCTEP           *currentEP;         /* the current expiry point */
    OSSCTCB                 *nextId;            /* the next schedule table (for NextScheduleTable) */
    OSSCTALMCB              *almId;             /* the alarm for this SCT */ 
#if defined(OSSCTSYNCEXPLICIT)
    TickType                deviation;          /* deviation of ST local time and value of the synchronization count */
    TickType                precision;          /* schedule table sync.PRECISION value */ 
    TickType                syncOffset;         /* the next EP offset using for sync.correction */
#endif
    TickType                length;             /* the length of the schedule table in ticks */
    TickType                initialOffset;      /* initial offset */
    const OSSCTEP           *firstEP;           /* the pointer to first expiry point in the schedule table */
    OSWORD                  ctrIndex;           /* attached Counter ID  */
    OSWORD                  state;              /* the config(MS) and status(LS) of schedule table */
#if defined(OSAPPLICATION)
    OSDWORD                 appMask;            /* Application identification mask value */
    ApplicationType         appId;              /* Application identification value */
#endif
};

#endif

/* Common alarm structure. It is used only as a reference type (OsAlmType) during the processing alarm queue.
   NB! User and schedule table alarms must have the same items at the beginning */
struct TagOSREFALM
{
    OSAlmType       next;                       /* next alarm in the list */
    OSAlmType       prev;                       /* previous alarm in the list   */
    TickType        value;                      /* Alarms' expiration value   */
    TickType        cycle;                      /* period value for cyclic alarm    */
    OSWORD          ctrIndex;                   /* attached Counter ID  */
};

#define OSALMCBPTR0         ( (OSAlmType)0 )    /* Null-pointer */
#define OSALM0              OSALMCBPTR0
                                                /* AlarmId is address of the alarm control block    */
#endif  /* (OSNALMS >0) */




/* ISR */

typedef void (*OSVOIDFUNCVOID)( void ); 

struct tagISRCFGTYPE
{
#if defined(OSAPPLICATION)
    OSDWORD  appMask;           /* Application identification mask value */
#endif
#if defined(OSMEMPROTECTION)
    OSDWORD* stackPtr;          /* top of ISR stack     */
    OSDWORD* isrBos;            /* bottom of ISR stack (note that OSUSEBOS is defined always for SC3/4) */
#endif
    OSVOIDFUNCVOID userISR;     /* actual ISR function */
    OSISRTYPE type;             /* type of the ISR */
    OSWORD   index;             /* Index of interrupt in the external interrupts table */
    OSBYTE   prio;              /* Interrupt priority */
#if defined(OSTIMINGPROTECTION)
#if  (OSNTPISRBGTS > 0) 
    OSTPTICKTYPE tpExecBudget;  /* execution time for ISR */
#endif
#if (OSNTPISRARRIV > 0)
    OSTPTICKTYPE tpTimeFrame;   /* Time frame for inter-arrival rate protection */
#endif
#if (OSNTPISRINTLOCKTIME > 0)
    OSTPTICKTYPE tpIntLockTime; /* interrupt locking time */
#endif
#if (OSNTPISRRESLOCKTIME > 0) 
    const OSTPRESLOCK *tpResLock;  /* TP resource locking time configurations */
    OSWORD tpNumberResLock;     /* number of resource lock configurations for this ISR2 */ 
#endif
#endif /* defined(OSTIMINGPROTECTION) */
#if defined(OSAPPLICATION)
    ApplicationType   appId;    /* application identification value */
#endif
};

typedef struct tagISRCFGTYPE OSISRCFGTYPE;

struct tagISRTYPE
{
#if defined(OSAPPLICATION)
    OSDWORD  appMask;           /* application identification mask value */
#endif
#if defined(OSMEMPROTECTION)
    OSDWORD* stackPtr;          /* top of ISR stack     */
    OSDWORD* isrBos;            /* bottom of ISR stack  */
#endif
#if defined(OSTERMINATION)
    OSBYTE   isKilled;          /* set when the ISR is killed via ProtectionHook or via TerminateApplication() */  
#endif
#if defined(OSUSERESLINK)
    OSResType resources;        /* pointer to the resources */
#endif
    OSVOIDFUNCVOID userISR;     /* actual ISR function */
    OSISRTYPE type;             /* type of the ISR */
    OSWORD    index;            /* Index of interrupt in the external interrupts table */
    OSBYTE    prio;             /* Interrupt priority */
#if defined(OSTIMINGPROTECTION)
#if  (OSNTPISRBGTS > 0) 
    OSTPTICKTYPE tpExecBudget;  /* the execution budget */
    OSTPTICKTYPE tpRemained;    /* remained time on the budget */
#endif
#if  (OSNTPISRARRIV > 0) 
    OSTPTICKTYPE tpTimeFrame;   /* time frame */
    OSSIGNEDQWORD tpLast;       /* 63-bit time of last successful transition to 'ready' state */   
#endif 
#if (OSNTPISRINTLOCKTIME > 0)
    OSTPTICKTYPE tpIntLockTime; /* interrupt locking time */
#endif
#if (OSNTPISRRESLOCKTIME > 0)
    OSTPRESLOCK  *tpResLock;    /* pointer to array with resource locking time configurations  */
    OSResType    tpResources;   /* the head of the list of occupied resources with started TP */
    OSWORD       tpNumberResLock; /* number of resource with locking time */
#endif
#endif /* defined(OSTIMINGPROTECTION) */
#if defined(OSAPPLICATION)
    ApplicationType   appId;    /* application identification value */
#endif
};

typedef struct tagISRTYPE    OS_ISRTYPE;

/* Counter info */
#if defined(OSCOUNTER) 
typedef OSCTR               CtrInfoType;        /* OSEK: counter characteristics storage */
typedef CtrInfoType*        CtrInfoRefType;     /* OSEK: reference to counter characteristics */
#endif  /* defined(OSCOUNTER)  */

/* Alarms */
#if (OSNUSERALMS > 0) 
typedef OSObjectType        AlarmType;          /* OBJECT_ALARM | index in ALARMCB table  */
typedef OSCTR               AlarmBaseType;
typedef AlarmBaseType*      AlarmBaseRefType;

#define ALARMCALLBACK(funcName) void funcName( void )

#if defined(OSAUTOALARMS)
struct tagALMAUTOTYPE                           /* Structure of autostarted alarm   */
{
    OSALMCB    *almId;                          /* Reference to alarm               */
    TickType    time;                           /* Time to start (relative)         */
    TickType    cycle;                          /* Alarm cycle, 0 for non-cycled    */
#if (OSNAPPMODES > 1)            
    OSDWORD     autostart;                      /* bit mask of modes for start      */
#endif  /* (OSNAPPMODES > 1) */
    OSBYTE    type;                             /* type of autostart alarm */
};

typedef struct tagALMAUTOTYPE OSALMAUTOTYPE;
#endif  /* defined(OSAUTOALARMS) */

#endif  /* (OSNUSERALMS>0) */

/* Schedule table */
#if defined(OSSCHEDULETABLES) 

typedef OSObjectType       ScheduleTableType;          /* the index in 'the schedule table' array */
typedef unsigned char      ScheduleTableStatusType;    /* the status of a schedule table */
typedef ScheduleTableStatusType* ScheduleTableStatusRefType;  /* points to a variable of the data type ScheduleTableStatusType */
typedef TickType           GlobalTimeTickType;         /* the global time source type */ 

#define SCHEDULETABLE_NOT_STARTED   ((ScheduleTableStatusType)0)
#define SCHEDULETABLE_STOPPED       SCHEDULETABLE_NOT_STARTED
#define SCHEDULETABLE_NEXT          ((ScheduleTableStatusType)1)
#define SCHEDULETABLE_WAITING       ((ScheduleTableStatusType)2)
#define SCHEDULETABLE_RUNNING       ((ScheduleTableStatusType)3)
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS   ((ScheduleTableStatusType)4)

#define OSSCTABSOLUTE   ((OSWORD)1)
#define OSSCTRELATIVE   ((OSWORD)2)
#define OSSCTSYNCHRON   ((OSWORD)3)

#define OSSCT0             ( (OSSCTCB *) 0 )        /* idle schedule table */

#if defined(OSAUTOSCHEDULETABLES)
/* The schedule tables which are started on startup of the OS with a given offset. */
struct tagSCTAUTOTYPE
{
    OSWORD              sctIndex;
    TickType            offset;
#if (OSNAPPMODES > 1)
    OSDWORD             autostart;
#endif  /* (OSNAPPMODES > 1) */
    OSBYTE              type;
};

typedef struct tagSCTAUTOTYPE OSSCTAUTOTYPE;
#endif  /* defined(OSAUTOSCHEDULETABLES) */

#endif  /* defined(OSSCHEDULETABLES) */

#if (OSNSCTALMS > 0) && (OSNUSERALMS > 0)
/* OSALMUNION structure is intended to ensure that both OsAlarms and OsSCTAlarms arrays were located
   in the memory directly one after another.
   NB! The order of items is important because alarm processing code depends on this. */
typedef struct
{
    OSALMCB OsAlarms[OSNUSERALMS];
    OSSCTALMCB OsSCTAlarms[OSNSCTALMS];
} OSALLALARMS;
#endif

/* Start of hooks code section */
#define OSHOOK_START_SEC_CODE
#include "ossections.h"

#if defined(OSHOOKPROTECTION) && !defined(OSSC1)
typedef unsigned char ProtectionReturnType;

extern ProtectionReturnType ProtectionHook( StatusType FatalError );

#if defined(OSCHECKCONTEXT)
#define OSSETPROTCNXT() OsIsrLevel = (OsIsrLevel & OSISRLEVELTASKMASK) | OSISRLEVELHOOKPROTECTION
#define OSCLRPROTCNTX() OsIsrLevel = OsIsrLevel & OSISRLEVELTASKMASK
#else
#define OSSETPROTCNXT()
#define OSCLRPROTCNTX()
#endif

#define PRO_KILLTASKISR           ((ProtectionReturnType)1)
#define PRO_KILLAPPL              ((ProtectionReturnType)2) 
#define PRO_KILLAPPL_RESTART      ((ProtectionReturnType)3)
#define PRO_SHUTDOWN              ((ProtectionReturnType)4)
#define PRO_TERMINATETASKISR      PRO_KILLTASKISR
#define PRO_TERMINATEAPPL         PRO_KILLAPPL
#define PRO_TERMINATEAPPL_RESTART PRO_KILLAPPL_RESTART
#define PRO_IGNORE                ((ProtectionReturnType)5)
#endif /* defined(OSHOOKPROTECTION) && !defined(OSSC1) */

#if defined(OSHOOKSTARTUP)
void StartupHook( void );
#endif

#if defined(OSHOOKSHUTDOWN)
void ShutdownHook( StatusType error );
#endif

#if defined(OSHOOKPRETASK)
void PreTaskHook( void );

#if defined(OSISRENTRYEXIT) || defined(OSCHECKCONTEXT)
/******************************************************************************
 * Macro:       OSPreTaskHook
 * Description: call User hook, setting special level
 * Returns:
 * Notes:       OsSuspendLevel shall be equal to 0, interrupts disabled
 ******************************************************************************/
#define OSCallPreTaskHook( ) \
    OsIsrLevel |= OSISRLEVELHOOKPRETASK;                        \
    OSOrtiSetServiceWatch( OSServiceId_PreTaskHook );           \
    PreTaskHook();                                              \
    OSOrtiServiceWatchOnExit( OSServiceId_PreTaskHook );        \
    OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKPRETASK)      
#else  /* if defined(OSISRENTRYEXIT) || defined(OSCONTEXTCHECK) */
#define OSCallPreTaskHook( ) \
    OSOrtiSetServiceWatch( OSServiceId_PreTaskHook );           \
    PreTaskHook();                                              \
    OSOrtiServiceWatchOnExit( OSServiceId_PreTaskHook ) 
#endif /* if defined(OSISRENTRYEXIT) || defined(OSCONTEXTCHECK) */
#define OSPreTaskHook( ) \
    if( OSHASRUNNINGTASK )    \
    {                         \
        OSCallPreTaskHook( ); \
    }
#else  /* defined(OSHOOKPRETASK) */
#define OSCallPreTaskHook()
#define OSPreTaskHook()
#endif /* defined(OSHOOKPRETASK) */

#if defined(OSHOOKPOSTTASK)
void PostTaskHook( void );

#if defined(OSISRENTRYEXIT) || defined(OSCHECKCONTEXT)
/******************************************************************************
 * Macro:       OSPostTaskHook
 * Description:
 * Returns:
 * Notes:       OsSuspendLevel shall be equal to 0, interrupts disabled
 ******************************************************************************/
#define OSPostTaskHook( ) \
    OsIsrLevel |= OSISRLEVELHOOKPOSTTASK;                          /* set special ISR level                           */ \
    OSOrtiSetServiceWatch( OSServiceId_PostTaskHook );             /* set watch to this service                       */ \
    PostTaskHook(); \
    OSOrtiServiceWatchOnExit( OSServiceId_PostTaskHook );          /* clean service watch on hook leaving             */ \
    OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKPOSTTASK);       /* reset special ISR level                         */
#else  /* if defined(OSISRENTRYEXIT) || defined(OSCONTEXTCHECK) */
#define OSPostTaskHook() \
    OSOrtiSetServiceWatch( OSServiceId_PostTaskHook );             /* set watch to this service                       */ \
    PostTaskHook(); \
    OSOrtiServiceWatchOnExit( OSServiceId_PostTaskHook );          /* clean service watch on hook leaving             */
#endif /* if defined(OSISRENTRYEXIT) || defined(OSCONTEXTCHECK) */
#else  /* defined(OSHOOKPOSTTASK) */
#define OSPostTaskHook( )
#endif /* defined(OSHOOKPOSTTASK) */

/* End of hooks code section */
#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#if defined(OSORTICURRENTSERVICEID)
/* Declaration of service watch: */
/*   run-time variable containing the idenfifier of */
/*   currently running OSEK OS service */

/***  Macros to handle service watch  ***/
/* Set specified service identifier     */
#define OSOrtiSetServiceWatch( ServiceId )    (OsOrtiRunningServiceId = (ServiceId) | 1)

/* Set service watch on leaving service */
#define OSOrtiServiceWatchOnExit( ServiceId ) (OsOrtiRunningServiceId = ServiceId)
                                                
/* Remember current service ID          */
#define OSOrtiSetOldServiceID( ServiceId )    (OsOrtiOldServiceId = ServiceId)

/* Restore ID on exit (after dispatch)  */
#define OSOrtiResetIdOnExit()                           \
    if( OsOrtiOldServiceId )                            \
    {                                                   \
        OsOrtiRunningServiceId = OsOrtiOldServiceId;    \
        OsOrtiOldServiceId = 0;                         \
    }

#else   /* defined(OSORTICURRENTSERVICEID) */

#define OSOrtiSetServiceWatch( ServiceId )
#define OSOrtiServiceWatchOnExit( ServiceId )
#define OSOrtiSetOldServiceID( ServiceID )
#define OSOrtiResetIdOnExit()

#endif  /* defined(OSORTICURRENTSERVICEID) */

#if defined(OSAPPLICATION)
typedef struct 
{
#if defined(OSAPPHOOKSTARTUP)    
    OSHKSTARTUP startup;     
#endif   
#if defined(OSAPPHOOKSHUTDOWN)   
    OSHKSHUTDOWN shutdown;   
#endif   
#if defined(OSAPPHOOKERROR)      
    OSHKERROR error;     
#endif 
#if defined(OSAPPHOOKSTARTUP) || defined(OSAPPHOOKSHUTDOWN) || defined(OSAPPHOOKERROR)
    OSDWORD* hookStack;
#if defined(OSMEMPROTECTION)
    OSDWORD* hookStackBos;
#endif
#endif /* defined(OSAPPHOOKSTARTUP) || defined(OSAPPHOOKSHUTDOWN) || defined(OSAPPHOOKERROR) */
    OSDWORD tasks;       /* all tasks of the application, priority-wise */
#if defined(OSEXTPRIORS)
    OSDWORD tasks2;      /* tasks of the application, priority-wise, if the tasks are more than 32*/
#endif
#if defined(OSHAS_RESTARTTASK)
    OSWORD  restartTask; /* index in OsTaskTable */
#endif
} OS_AppType;

/* Get current application Id */
#define OSGetCurApp() OSGetSPRG4()
/* Set current application Id */
#define OSSetCurApp(appId) OSSetSPRG4(appId)

#define OSCURRENTAPPMASK (1 << (OSGetCurApp()))
#else
/* Set current application Id */
#define OSSetCurApp(arg)
#endif /* defined(OSAPPLICATION) */


#if defined(OSMEMPROTECTION)

#define OSMP_IS_TRUSTEDAPP(appIndex) ( (appIndex) >= (ApplicationType)OSNNOTTRUSTEDAPPS )
#define OSMP_IS_NONTRUSTEDAPP(appIndex) ( (appIndex) < (ApplicationType)OSNNOTTRUSTEDAPPS )

#define OSSRVENTRY( ServiceName ) OsId##ServiceName
typedef enum
{ 
#include <ossrvlist.h>
} ServiceIdType;
#undef OSSRVENTRY

extern OSDWORD OSSystemCall0( OSDWORD ServiceId );
extern OSDWORD OSSystemCall1( OSDWORD a, OSDWORD ServiceId );
extern OSDWORD OSSystemCall2( OSDWORD a, OSDWORD b, OSDWORD ServiceId );
extern OSDWORD OSSystemCall3( OSDWORD a, OSDWORD b, OSDWORD c, OSDWORD ServiceId );

#if OSNNOTTRUSTEDAPPS == 0 
#define OSServiceCall0(type, name) OS_##name()
#define OSServiceCall1(type, arg, name) OS_##name(arg)
#define OSServiceCall2(type, arg1, arg2, name) OS_##name(arg1, arg2)
#define OSServiceCall3(type, arg1, arg2, arg3, name) OS_##name(arg1, arg2, arg3)
#else
#define OSMP_SC_NEEDED() OSMP_IS_NONTRUSTEDAPP(OSGetCurApp())
#define OSServiceCall0(type, name) OSMP_SC_NEEDED() ? (type)OSSystemCall0(OsId##name) : OS_##name()
#define OSServiceCall1(type, arg, name) OSMP_SC_NEEDED() ? (type)OSSystemCall1((OSDWORD)arg, OsId##name) : OS_##name(arg)
#define OSServiceCall2(type, arg1, arg2, name) OSMP_SC_NEEDED() ? (type)OSSystemCall2((OSDWORD)arg1, (OSDWORD)arg2, OsId##name) : OS_##name(arg1, arg2)
#define OSServiceCall3(type, arg1, arg2, arg3, name) OSMP_SC_NEEDED() ? (type)OSSystemCall3((OSDWORD)arg1, (OSDWORD)arg2, (OSDWORD)arg3, OsId##name) : OS_##name(arg1, arg2, arg3)
#endif /* OSNNOTTRUSTEDAPPS == 0 */ 

/* Prepared MPU descriptor fields (except Word2) for each nontrusted application */
typedef struct {
    OSDWORD startaddr;          /* Word0 */
    OSDWORD endaddr;            /* Word1 */
    OSDWORD valid;              /* Word3 */
} OSMP_DSADDR;
#endif /* defined(OSMEMPROTECTION) */

#if OSNMSGS > 0

/**** COM standard types ****/

typedef OSObjectType        MessageIdentifier;
typedef void*               ApplicationDataRef;
typedef enum                { COM_FALSE, COM_TRUE }     FlagValue;
typedef OSBYTE              COMApplicationModeType;
typedef OSBYTE              COMShutdownModeType;

#if defined(OSORTICURRENTSERVICEID)
typedef unsigned char*      FlagType;
#else /* defined(OSORTICURRENTSERVICEID) */
typedef unsigned char       FlagType;
#endif /* defined(OSORTICURRENTSERVICEID) */


/**** OS internal COM types ****/

/* Message configuration table for receiving message */ 
struct TagOSMSG             /* OSMSGtype */
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;        /* Application identification mask value */
#endif
    void*           msgPtr;         /* pointers to messages bodies  */
    OSDWORD         msgSize;        /* size of messages in bytes    */
#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT)
    TaskType        msgSigTask;     /* Tasks to be signaled         */
#endif  /* defined(OSSIGACTIVTASK) || defined(OSSIGEVENT) */
#if defined(OSSIGEVENT)
    EventMaskType   msgSigEvent;    /* Events to be set             */
#endif  /* defined(OSSIGEVENT) */
#if defined(OSSIGCALLBACK)
    OSCALLBACK      msgSigCallBack; /* to be called in SendMessage  */
#endif  /* defined(OSSIGCALLBACK) */
#if defined(OSSIGFLAG)
    OSBYTE          msgSigFlag;     /* Flags to be set              */
#endif  /* defined(OSSIGFLAG) */
#if OSNQUEMSGS > 0
    const void*     fifoLast;       /* pointer to last element of queue for msg     */
                                    /* or pointer to initValue for unqueued message */
    OSBYTE          fifoLength;     /* number of elements in queue for msg          */
#else
    const void*     initValue;      /* pointer to initial message value or NULL     */
#endif  /* OSNQUEMSGS > 0 */
#if defined(OSAPPLICATION)
    ApplicationType appId;          /* application identification value */
#endif
};

typedef struct TagOSMSG      OSMSGtype;          /* receiving messages configuration */
typedef struct TagOSMSGCB    OSMSGCBtype;        /* The message control block        */

/* Message state table for receiving message */ 
struct TagOSMSGCB           /* OSMSGCBtype */
{
#if defined(OSAPPLICATION)
    OSDWORD         appMask;        /* Application identification mask value */
#endif
    OSMSGCBtype*    nextMsg;        /* next receiving message           */
/** Copy of configuration from ROM **/
    void*           msgPtr;         /* pointers to messages bodies  */
    OSDWORD         msgSize;        /* size of messages in bytes    */
#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT)
    TaskType        msgSigTask;     /* Tasks to be signaled         */
#endif  /* defined(OSSIGACTIVTASK) || defined(OSSIGEVENT) */
#if defined(OSSIGEVENT)
    EventMaskType   msgSigEvent;    /* Events to be set             */
#endif  /* defined(OSSIGEVENT) */
#if defined(OSSIGCALLBACK)
    OSCALLBACK      msgSigCallBack; /* to be called in SendMessage  */
#endif  /* defined(OSSIGCALLBACK) */
#if defined(OSSIGFLAG)
    OSBYTE          msgSigFlag;     /* Flags to be set              */
#endif  /* defined(OSSIGFLAG) */
#if OSNQUEMSGS > 0
    const void*     fifoLast;       /* pointer to last element of queue for msg     */
    OSBYTE          fifoLength;     /* number of elements in queue for message      */
#endif  /* OSNQUEMSGS > 0 */
/** end of copy **/
#if OSNQUEMSGS > 0
    OSBYTEPTR       fifoWrite;      /* element to be writed             */ 
    OSBYTEPTR       fifoRead;       /* element to read                  */
    OSBYTE          fifoCnt;        /* number of used elements in queue */
    OSBYTE          msgStatus;      /* messages status                  */
#endif  /* OSNQUEMSGS > 0 */
#if OSNFLAGS > 0
    OSBYTE          msgFlag;
#endif  /* OSNFLAGS > 0 */
#if defined(OSAPPLICATION)
    ApplicationType appId;          /* application identification value */
#endif    
};

#if defined(OSAPPLICATION)
/* Message configuration table for sending message */ 
struct TagOSSNDMSG             /* OSSNDMSGtype */
{
    OSDWORD         appMask;        /* Application identification mask value */
    ApplicationType appId;          /* application identification value */
};

typedef struct TagOSSNDMSG   OSSNDMSGtype;       /* receiving messages configuration */

/* Message state table for sending message */ 
struct TagOSSNDMSGCB           /* OSSNDMSGCBtype */
{
    OSDWORD         appMask;        /* Application identification mask value */
    ApplicationType appId;          /* application identification value */
};

typedef struct TagOSSNDMSGCB OSSNDMSGCBtype;     /* The message control block        */
#endif /* defined(OSAPPLICATION) */
#endif /* OSNMSGS > 0 */


#if defined(OSTERMINATION)
/* Flags in OsKilled */
#define OSRUNTSKKILLED  ((OSBYTE)0x1)
#endif
#if defined(OSTIMINGPROTECTION)
#define OSTPALMKILLED   ((OSBYTE)0x2)   /* flag that TP alarm queue interrupt handler is running */ 
#endif

/* Data section adresses for various compilers */
#if defined(OSCWPPC)
#define OS_BEGIN_DSADDR(DSNAME) _f_##DSNAME
#define OS_END_DSADDR(DSNAME)   _e_##DSNAME
#endif

#if defined(OSGHSPPC)
#define OS_BEGIN_DSADDR(DSNAME) __ghsbegin_##DSNAME
#define OS_END_DSADDR(DSNAME)   __ghsend_##DSNAME
#endif

#if defined(OSDIABPPC)
#define OS_BEGIN_DSADDR(DSNAME) _f_##DSNAME
#define OS_END_DSADDR(DSNAME)   _e_##DSNAME
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* OSBASAPI_H */
