/**
    @file    Spi.c
    @version 2.0.0

    @brief   AUTOSAR Spi - Implements the AUTOSAR SPI driver functionality.
    @details Implements the AUTOSAR SPI driver. All the API functions are described by AUTOSAR

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral DSPI
    Dependencies 

    ARVersion 3.0.0
    ARRevision ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion 2.0.0
    BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Spi_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
and comments before "#include". AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.

@section Spi_c_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent
the content of a header file to be included twice. The inclusion of MemMap.h
is as per Autosar requirement MEMMAP003.

@section Spi_c_REF_3
Violates MISRA 2004 Advisory Rule 11.4, a cast should not be performed between
a pointer to object type and a different pointer to object type.
'Spi_ChannelConfig.BufferDescriptor' field is defined as P2CONST(), while the
referenced Spi_BufferDescriptor instance may be a variable, in the case of
external buffers.
@section Spi_c_REF_4
Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer arithmetic.
@section Spi_c_REF_5


Violates MISRA 2004 Required Rule 11.5 A cast shall not be performed that removes any const or volatile
qualification from the type addressed by a pointer.
@section Spi_c_REF_6
Violates MISRA 2004 Required Rule 12.13, The increment (++) and decrement (--) operators should
not be mixed with other operators in an expression.
*/
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include "Spi_LLD.h"
#include "Dem.h"
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif
#include "SchM_Spi.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@brief Parameters that shall be published within the driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define SPI_AR_MAJOR_VERSION_C  3
#define SPI_AR_MINOR_VERSION_C  0
#define SPI_AR_PATCH_VERSION_C  0
#define SPI_SW_MAJOR_VERSION_C  2
#define SPI_SW_MINOR_VERSION_C  0
#define SPI_SW_PATCH_VERSION_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_C != SPI_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_C != SPI_AR_MINOR_VERSION) || \
       (SPI_AR_PATCH_VERSION_C != SPI_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Spi.c and Spi.h are different"
  #endif
#endif

#if ((SPI_SW_MAJOR_VERSION_C != SPI_SW_MAJOR_VERSION) || \
     (SPI_SW_MINOR_VERSION_C != SPI_SW_MINOR_VERSION))
#error "Software Version Numbers of Spi.c and Spi.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  #if ((SPI_AR_MAJOR_VERSION != DET_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION != DET_AR_MINOR_VERSION))
  #error "AutoSar Version Numbers of SPI.h and Det.h are different"
  #endif
  #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION != DEM_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION != DEM_AR_MINOR_VERSION))
  #error "AutoSar Version Numbers of Spi.h and Dem.h are different"
  #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_C != SCHM_SPI_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_C != SCHM_SPI_AR_MINOR_VERSION))
  #error "AutoSar Version Numbers of Spi.c and SchM_Spi.h are different"
  #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/** @brief For async transmissions, this structure holds the HWUnit scheduling queue
           For sync transmissions, only HWUnit Status is managed
  */
typedef struct
{
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
    /** @brief array of the IDs of jobs to be scheduled, for each priority level */
    VAR(Spi_JobType, SPI_VAR) ScheduledJobsListHead[SPI_JOB_PRIORITY_LEVELS_COUNT];
    /** @brief array of the IDs of last jobs in queues, for each priority level */
    VAR(Spi_JobType, SPI_VAR) ScheduledJobsListTail[SPI_JOB_PRIORITY_LEVELS_COUNT];
    /** @brief array of the IDs of last jobs in queues, for each priority level */
    VAR(sint8, SPI_VAR) MaxScheduledPriority;
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */
    /** @brief DSPI state */
    VAR(Spi_StatusType, SPI_VAR) Status;
} Spi_HWUnitQueue;

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/**
@brief  Values used to denote NULL indexes.
*/
#define SPI_JOB_NULL            ((Spi_JobType)(-1))
#define SPI_SEQUENCE_NULL       ((Spi_SequenceType)(-1))
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define   SPI_START_SEC_VAR_UNSPECIFIED
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_c_REF_1 & @ref Spi_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/** @brief Array of HW units queues */
STATIC VAR(Spi_HWUnitQueue, SPI_VAR) SpiHWUnitQueueArray[SPI_MAX_HWUNIT];


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/



/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/**
@brief Pointer initialized during init with the address of the received configuration structure.
@details Will be used by all functions to access the configuration data.
*/
P2CONST(Spi_ConfigType, SPI_VAR, SPI_APPL_CONST) SpiConfigPtr = NULL_PTR;

/**
@brief Spi State
*/
/**
@note Violates MISRA 2004 Required Rule 8.10 (local variable must be
      defined as static)
      State variables may be used by LLD layer.
*/
/*lint -save -e765*/
VAR(Spi_SequenceState, AUTOMATIC) SpiSequenceState[SPI_MAX_SEQUENCE];
VAR(Spi_JobState, AUTOMATIC) SpiJobState[SPI_MAX_JOB];
VAR(Spi_ChannelState, AUTOMATIC) SpiChannelState[SPI_MAX_CHANNEL];
/*lint -restore*/

#if (SPI_MAX_HWUNIT > 32u)
    #error "Too many HW Units in configuration (max 32 units allowed)"
#endif
/** Array of used HW units per sequence:
    The element corresponding to a given sequence will have asserted the bits
    corresponding to the used HW units.
*/
#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
STATIC VAR(uint32, SPI_VAR) SpiSeqUsedHWUnits[SPI_MAX_SEQUENCE];
#endif

/**
@brief Spi Sync Transmit Running HWUnits Status
*/
STATIC volatile VAR(uint32, SPI_VAR) SpiBusySyncHWUnitsStatus = 0u;

/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Spi_c_REF_1
*/
#define SPI_STOP_SEC_VAR_UNSPECIFIED
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_c_REF_1 & @ref Spi_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Spi_c_REF_1
*/
#define SPI_START_SEC_CODE
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_c_REF_1 & @ref Spi_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_ScheduleJob(
    P2VAR(Spi_HWUnitQueue, AUTOMATIC, SPI_VAR) pHWUnitQueue,
    VAR(Spi_JobType, AUTOMATIC) Job,
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig);
#endif

#if (SPI_LEVEL_DELIVERED == LEVEL2)
STATIC INLINE FUNC (Spi_StatusType, SPI_CODE) Spi_GetAsyncStatus(void);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (Std_ReturnType, SPI_CODE) Spi_LockJobs(
    VAR(Spi_SequenceType, SPI_VAR) Sequence,
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequence);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (SPI_CANCEL_API == STD_ON)
STATIC INLINE FUNC (void, SPI_CODE) Spi_UnlockRemainingJobs(
    VAR(Spi_JobType, AUTOMATIC) RemainingJobs,
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequence);
#endif
#endif
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC FUNC (void, SPI_CODE) Spi_ScheduleNextJob(
    P2VAR(Spi_HWUnitQueue, AUTOMATIC, SPI_VAR) pHWUnitQueue);
#endif


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
@brief   This function returns the status of the SPI driver related to async HW Units.
@details Return SPI_BUSY if at least one async HW unit is busy.

@return  Spi_StatusType
        - SPI_UNINIT - The driver is un-initialized
        - SPI_IDLE - The driver has no pending transfers
        - SPI_BUSY - The driver is busy

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL2.

@remarks Implements DSPI02314
*/
/*================================================================================================*/

#if (SPI_LEVEL_DELIVERED == LEVEL2)
STATIC INLINE FUNC (Spi_StatusType, SPI_CODE) Spi_GetAsyncStatus(void)
{
    VAR(Spi_StatusType, AUTOMATIC) Spi_StatusFlag = SPI_IDLE;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;

    for (HWUnit = 0u; HWUnit < (Spi_HWUnitType)SPI_MAX_HWUNIT; HWUnit++)
    {
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 17.4
- See @ref Spi_c_REF_4
*/
        if ((SPI_BUSY == SpiHWUnitQueueArray[HWUnit].Status) &&
            (SPI_PHYUNIT_ASYNC == SpiConfigPtr->HWUnitConfig[HWUnit].IsSync))
        {
            Spi_StatusFlag = SPI_BUSY;
            break;
        }
    }
    return Spi_StatusFlag;
}
#endif /* (SPI_LEVEL_DELIVERED == LEVEL2) */

/*================================================================================================*/
/**
@brief   This function is called in order to mark the jobs of a sequence as
         ready to be transmitted.
@details For each job in sequence, the function checks if it is already
         linked to another pending sequence.
         If at least one job is already linked, the function returns E_NOT_OK.
         Elsewhere, all jobs in sequence are locked (linked to the current
         sequence)

@param[in]      Sequence        The sequence ID.
@param[in]      pSequence       The sequence configuration.

@return Std_ReturnType
        - E_OK - The given sequence does not share its jobs with some
                   other sequences, and all its jobs were successfully
                   locked.
        - E_NOT_OK - The given sequence shares its jobs with some other
                   sequences. No lock performed for its jobs.

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.

@remarks Implements DSPI02304, DSPI04096, DSPI02200
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (Std_ReturnType, SPI_CODE) Spi_LockJobs(
    VAR(Spi_SequenceType, SPI_VAR) Sequence,
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequence)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    VAR(Spi_JobType, AUTOMATIC) JobCount = pSequence->NumJobs;
    P2CONST(Spi_JobType, AUTOMATIC, SPI_VAR) pJobs = pSequence->JobIndexList;
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) pJobState;
    P2VAR(Spi_SequenceState, AUTOMATIC, SPI_VAR) pSequenceState;

    SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_05);

    /* use an optimized implementation for one job sequences */
    if (1u == JobCount)
    {
        pJobState = &SpiJobState[*pJobs];
        if (NULL_PTR == pJobState->AsyncCrtSequenceState)
        {
            /* job not yet linked => link it to the current sequence */
            pJobState->AsyncCrtSequenceState = &SpiSequenceState[Sequence];
        }
        else
        {
            /* the job is already locked by a pending sequence */
            Status = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        pSequenceState = &SpiSequenceState[Sequence];
        while (JobCount > 0u)
        {
            pJobState = &SpiJobState[*pJobs];
            if (NULL_PTR == pJobState->AsyncCrtSequenceState)
            {
                /* job not yet linked => link it to the current sequence */
                pJobState->AsyncCrtSequenceState = pSequenceState;
            }
            else
            {
                /* the job is already locked by a pending sequence =>
                   rollback all the previous locks */
                if (JobCount < pSequence->NumJobs)
                {
                    do
                    {
                        JobCount++;
                 /**
                  @file Spi.c
                  @note Violates MISRA 2004 Advisory Rules 17.4
                  -See  @ref Spi_c_REF_4
                 */
                        pJobs--;
                        SpiJobState[*pJobs].AsyncCrtSequenceState = NULL_PTR;
                    }
                    while (JobCount < pSequence->NumJobs);
                }
                Status = (Std_ReturnType)E_NOT_OK;
                break;
            }

            /* next job */
            JobCount--;
             /**
              @file Spi.c
              @note Violates MISRA 2004 Advisory Rules 17.4
              -See  @ref Spi_c_REF_4
             */
            pJobs++;
        }

    }
    SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_05);
    return Status;
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function is called in order release the jobs at the
         end of an async sequence transmission
@details Mark the linked sequence for all jobs as NULL_PTR.

@param[in]      RemainingJobs    The starting job
@param[in]      pSequence        The sequence configuration

@pre  Pre-compile parameter SPI_CANCEL_API shall be STD_ON.

@remarks Implements DSPI02332, DSPI04112
*/
/*================================================================================================*/

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (SPI_CANCEL_API == STD_ON)
STATIC INLINE FUNC (void, SPI_CODE) Spi_UnlockRemainingJobs(
    VAR(Spi_JobType, AUTOMATIC) RemainingJobs,
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequence)
{
    VAR(Spi_JobType, AUTOMATIC) NumJobsInSeq = pSequence->NumJobs;
    VAR(Spi_JobType, AUTOMATIC) JobIdx;

    SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_06);
    for (JobIdx = NumJobsInSeq-RemainingJobs; JobIdx < NumJobsInSeq; JobIdx++)
    {
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 17.4
-see  @ref Spi_c_REF_4
*/
        SpiJobState[pSequence->JobIndexList[JobIdx]].AsyncCrtSequenceState =
                NULL_PTR;
    }
    SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_06);
}
#endif /* (SPI_CANCEL_API == STD_ON) */
#endif /* (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) */

/*================================================================================================*/
/**
@brief   This function will schedule a job for a given HW unit
@details If the HWUnit is not busy, the transfer is started and the HW unit is
         marked as busy.
         If the HWUnit is not busy (another job is in progress), the new job is
         scheduled in a waiting job list, according to its priority.

@param[in]      pHWUnitQueue     HW Unit to be used by the job
@param[in]      Job             ID of the scheduled job
@param[in]      pJobConfig      Configuration of the scheduled job

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.

@remarks Implements DSPI02300, DSPI04335
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_ScheduleJob(
    P2VAR(Spi_HWUnitQueue, AUTOMATIC, SPI_VAR) pHWUnitQueue,
    VAR(Spi_JobType, AUTOMATIC) Job,
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig)
{
    VAR(sint8, AUTOMATIC) Priority;
    P2VAR(Spi_JobType, AUTOMATIC, SPI_VAR) pJobListTail;

    SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_03);
    if (SPI_IDLE == pHWUnitQueue->Status)
    {
        /* idle unit => the job can be started */
        pHWUnitQueue->Status = SPI_BUSY;
        SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_03);

        /* mark the job as pending */
        SpiJobState[Job].Result = SPI_JOB_PENDING;
        Spi_LLD_JobTransfer(pJobConfig);
    }
    else
    {
        /* add the job to the scheduling corresponding queue */

        /* retrieve the tail of the scheduling queue for the job priority */
        Priority = pJobConfig->Priority;
        pJobListTail = &pHWUnitQueue->ScheduledJobsListTail[Priority];

        if (SPI_JOB_NULL == *pJobListTail)
        {
            /* the list is empty => set also the head of the list */
            pHWUnitQueue->ScheduledJobsListHead[Priority] = Job;
        }
        else
        {
            /* add the item at the end of the list */
            SpiJobState[*pJobListTail].AsyncNextJob = Job;
        }

        /* set the new tail of the list */
        *pJobListTail = Job;

        /* the new item will be the last element in the list */
        SpiJobState[Job].AsyncNextJob = SPI_JOB_NULL;

        if (pHWUnitQueue->MaxScheduledPriority < Priority)
        {
            pHWUnitQueue->MaxScheduledPriority = Priority;
        }
        SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_03);
    }
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) ) */

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (SPI_VERSION_INFO_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function returns the version information for the SPI driver.
@details This function returns the version information for the SPI driver.
         - Service ID:       0x09
         - Sync/Async:       Synchronous
         - Reentrancy:       Non-Reentrant

@param[in,out]    VersionInfo      Pointer to where to store the version
                                   information of this module

@pre  Pre-compile parameter SPI_VERSION_INFO_API shall be STD_ON.

@remarks Implements DSPI02310, DSPI04091
*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (void, SPI_CODE) Spi_GetVersionInfo (
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_VAR) VersionInfo)
{
#if( SPI_DEV_ERROR_DETECT == STD_ON )
    if(NULL_PTR == VersionInfo)
    {
        Det_ReportError((uint16)SPI_MODULE_ID,
                        (uint8)0,
                        SPI_GETVERSIONINFO_ID,
                        SPI_E_VERSION);
    }
    else
    {
#endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    VersionInfo->vendorID = (uint16)SPI_VENDOR_ID;
    VersionInfo->moduleID = (uint8)SPI_MODULE_ID;
    VersionInfo->sw_major_version = (uint8)SPI_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = (uint8)SPI_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = (uint8)SPI_SW_PATCH_VERSION;
#if(SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* SPI_DEV_ERROR_DETECT == STD_ON */
}
#endif /* (SPI_VERSION_INFO_API == STD_ON) */
/*================================================================================================*/
/**
@brief   This function initializes the SPI driver.
@details This function initializes the SPI driver using the
         pre-established configurations
         - Service ID:       0x00
         - Sync/Async:       Synchronous
         - Reentrancy:       Non-Reentrant


@param[in]     ConfigPtr      Specifies the pointer to the configuration set

@remarks Implements DSPI02301, DSPI06000, DSPI04091, DSPI02130, DSPI04232
*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (void, SPI_CODE) Spi_Init(
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_DATA) ConfigPtr)
{
    VAR(Spi_ChannelType, AUTOMATIC) Channel;
    VAR(Spi_JobType, AUTOMATIC) Job;
    VAR(Spi_SequenceType, AUTOMATIC) Sequence;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
    VAR(sint8, AUTOMATIC) Priority;
#endif

#if (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE)
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if ConfigPtr */
    /* is passed as a NULL Pointer */
    if (NULL_PTR != SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_INIT_ID,
                        SPI_E_ALREADY_INITIALIZED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_INIT_ID,
                        SPI_E_UNINIT);
    }
    else
#endif
    if ((ConfigPtr->Spi_Max_Channel > SPI_MAX_CHANNEL) ||
             (ConfigPtr->Spi_Max_Job > SPI_MAX_JOB) ||
             (ConfigPtr->Spi_Max_Sequence > SPI_MAX_SEQUENCE))
    {
        /* configuration sizes must be checked for
           Post Build & Link Time configurations */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_INIT_ID,
                        SPI_E_CONFIG_OUT_OF_RANGE);
#endif
    }
    else
    {
#else /* (SPI_CONFIG_VARIANT == SPI_VARIANT_PRECOMPILE) */
        if (NULL_PTR != SpiConfigPtr)
        {

#if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_INIT_ID,
                            SPI_E_ALREADY_INITIALIZED);
#endif
        }
        else if (NULL_PTR == ConfigPtr)
        {
            SpiConfigPtr = &SpiDriverConfig_PC;
        }
        else
#endif
        {
            SpiConfigPtr = ConfigPtr;
        }
        /* initialize buffer pointers to zero */
        for (Channel = (Spi_ChannelType) 0;
            Channel < (SpiConfigPtr->Spi_Max_Channel);
            Channel++)
        {
            /* Check if configured buffers are External (EB) */
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
            if (EB == SpiConfigPtr->ChannelConfig[Channel].BufferType)
            {
                /* Initialize all buffers */
                /**
                @note Violates MISRA 2004 Advisory Rules 11.4,11.5,17.4
                - See @ref Spi_c_REF_3, Spi_c_REF_5,Spi_c_REF_4
                */
                /*lint -save -e929 -e960*/
                ((P2VAR(Spi_BufferDescriptor, AUTOMATIC, SPI_VAR))
                    SpiConfigPtr->ChannelConfig[Channel].BufferDescriptor)
                        ->BufferTX = NULL_PTR;
                ((P2VAR(Spi_BufferDescriptor, AUTOMATIC, SPI_VAR))
                    SpiConfigPtr->ChannelConfig[Channel].BufferDescriptor)
                        ->BufferRX = NULL_PTR;
                /*lint -restore*/

                /* Channel length is zero for unconfigured external buffers */

                SpiChannelState[Channel].Length = (Spi_NumberOfDataType) 0;
            }
            else
            {
                /* Setup channel length according to configuration */
                SpiChannelState[Channel].Length =
                    SpiConfigPtr->ChannelConfig[Channel].Length;
            }
            SpiChannelState[Channel].Flags =
                (VAR(uint8, SPI_VAR)) SPI_CHANNEL_FLAG_TX_DEFAULT;
        }

        /* initialize job results */
        /** @remarks Implements DSPI02301 */
        for (Job = (VAR(Spi_JobType, AUTOMATIC)) 0;
            Job < ( SpiConfigPtr->Spi_Max_Job);
            Job++)
        {
            SpiJobState[Job].Result = SPI_JOB_OK;

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
            /* mark the job as unlocked / not linked to a pending async sequence */
            SpiJobState[Job].AsyncCrtSequenceState = NULL_PTR;
#endif
        }

        for (Sequence = (VAR(Spi_SequenceType, AUTOMATIC)) 0;
            Sequence < (SpiConfigPtr->Spi_Max_Sequence); Sequence++)
        {
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/**
 @file Spi.c
 @note Violates MISRA 2004 Advisory Rules 17.4
 -see  @ref Spi_c_REF_4
*/
            SpiSequenceState[Sequence].Sequence =
                &SpiConfigPtr->SequenceConfig[Sequence];
#endif

            /* initialize sequence results */
            /** @remarks Implements DSPI02301 */
            SpiSequenceState[Sequence].Result = SPI_SEQ_OK;

#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
#if (SPI_ENABLE_MULTI_SYNC_TRANSMIT == STD_ON)
            /* initialize the map of used HWUnits per sequence */
            SpiSeqUsedHWUnits[Sequence] = 0;
            for (Job = 0u;
                Job < SpiConfigPtr->SequenceConfig[Sequence].NumJobs;
                Job++)
            {
                HWUnit = SpiConfigPtr->JobConfig[
                            SpiConfigPtr->SequenceConfig[Sequence].
                                JobIndexList[Job]
                        ].HWUnit;
                SpiSeqUsedHWUnits[Sequence] |=
                    (1 << (SpiConfigPtr->HWUnitConfig[HWUnit].Offset));
            }
#else /* (SPI_ENABLE_MULTI_SYNC_TRANSMIT == STD_OFF) */
            /* SPI135: Spi_SyncTransmit() must fail if an other sync transmission
                   is ongoing.*/
            /* mark all HW units as used by the sync transmission, in order to
                force the mutual exclusion of Spi_SyncTransmit() calls */
            SpiSeqUsedHWUnits[Sequence] = 0xFFFFFFFFU;
#endif /* (SPI_ENABLE_MULTI_SYNC_TRANSMIT == STD_OFF) */
#endif /* ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) ) */

        }

        /* initialize all physical HWUnits */
        for (HWUnit = (VAR(Spi_HWUnitType, AUTOMATIC)) 0;
            HWUnit < (VAR(Spi_HWUnitType, AUTOMATIC)) SPI_MAX_HWUNIT;
            HWUnit++)
        {
#if (SPI_LEVEL_DELIVERED == LEVEL2)
            /* handler uses polling mode only if LEVEL 2 is selected */
            Spi_LLD_Init(HWUnit, SPI_POLLING_MODE,
                        &SpiHWUnitQueueArray[HWUnit].Status);
#else
            Spi_LLD_Init(HWUnit, SPI_INTERRUPT_MODE,
                        &SpiHWUnitQueueArray[HWUnit].Status);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
            /* initialize the Job lists => no scheduled job for the unit */
            for (Priority = 0; Priority < SPI_JOB_PRIORITY_LEVELS_COUNT; Priority++)
            {
                SpiHWUnitQueueArray[HWUnit].ScheduledJobsListHead[Priority] =
                    SPI_JOB_NULL;
                SpiHWUnitQueueArray[HWUnit].ScheduledJobsListTail[Priority] =
                    SPI_JOB_NULL;
            }

            /* no scheduled job => MaxScheduledPriority is -1 */
            SpiHWUnitQueueArray[HWUnit].MaxScheduledPriority = -1;
#endif
            SpiHWUnitQueueArray[HWUnit].Status = SPI_IDLE;
        }

#if ((SPI_LEVEL_DELIVERED != LEVEL1) && (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON))
        /* cache information for sequences having only one job */
        Spi_LLD_PrepareCacheInformation();
#endif

#if (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE)
    }
#endif
}
/*================================================================================================*/
/**
@brief   This function de-initializes the SPI driver.
@details This function de-initializes the SPI driver using the
         pre-established configurations
         - Service ID:       0x01
         - Sync/Async:       Synchronous
         - Reentrancy:       Non-Reentrant

@return Std_ReturnType
        - E_OK - de-initialisation command has been accepted
        - E_NOT_OK - de-initialisation command has not been accepted

@pre  The driver needs to be initialized before calling Spi_DeInit()
      otherwise, the function Spi_DeInit() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.

@remarks Implements DSPI02302, DSPI06000, DSPI04091, DSPI02180

*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_DeInit(void)
{
    VAR(Std_ReturnType, AUTOMATIC) tempExit = (Std_ReturnType)E_OK;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_DEINIT_ID,
                        SPI_E_UNINIT);
        tempExit = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif


        /* Check if Spi Status is Busy */
        if (SPI_BUSY == Spi_GetStatus())
        {
            /* SPI0121 */
            tempExit = (VAR(Std_ReturnType, AUTOMATIC)) E_NOT_OK;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_DEINIT_ID,
                            SPI_E_SEQ_PENDING);
#endif
        }
        else
        {
            /* de-initialize all physical HWUnits */
            for (HWUnit = (VAR(Spi_HWUnitType, AUTOMATIC)) 0;
                 HWUnit < (VAR(Spi_HWUnitType, AUTOMATIC)) SPI_MAX_HWUNIT;
                 HWUnit++)
            {
                Spi_LLD_DeInit(HWUnit);

                SpiHWUnitQueueArray[HWUnit].Status = SPI_UNINIT;
            }
            /* reset configuration pointer */
            SpiConfigPtr = NULL_PTR;
        }

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return tempExit;
}

/*================================================================================================*/
/**
@brief   This function writes the given data into the buffer of a specific channel.
@details This function writes the given data into the buffer of a specific channel.
         - Service ID:       0x02
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      Channel             Channel ID
@param[in]      DataBufferPtr       Pointer to source data buffer

@return Std_ReturnType
        - E_OK - Command has been accepted
        - E_NOT_OK - Command has not been accepted

@pre  The driver needs to be initialized before calling Spi_WriteIB()
      otherwise, the function Spi_WriteIB() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_CHANNEL_BUFFERS_ALLOWED shall be USAGE0 or USAGE2.

@remarks Implements DSPI02303, DSPI06000, DSPI04091, DSPI02130, DSPI02120

*/
/*================================================================================================*/
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE0) || \
      (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_WriteIB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_CONST) DataBufferPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    VAR(uint16, AUTOMATIC) Index;
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) pChannelState;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DataBufferDes;
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferSrc;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_WRITEIB_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }

    /* If Development Error Detection is enabled,
       report error if invalid channel */
    else if (Channel >= (SpiConfigPtr->Spi_Max_Channel))
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_WRITEIB_ID,
                        SPI_E_PARAM_CHANNEL);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
        pChannelState = &SpiChannelState[Channel];
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        pChannelConfig = &SpiConfigPtr->ChannelConfig[Channel];

        /* exit early if this is the wrong buffer type */
        if (EB == pChannelConfig->BufferType)
        {
            Status = (Std_ReturnType)E_NOT_OK;
            /* Call Det_ReportError */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_WRITEIB_ID,
                            SPI_E_PARAM_CHANNEL);
#endif
        }
        else
        {
            /* if DataBufferPtr is zero, then transmit default value */
            if (NULL_PTR == DataBufferPtr)
            {

                pChannelState->Flags |= SPI_CHANNEL_FLAG_TX_DEFAULT;
            }

            /* otherwise, copy data from DataBufferPtr to IB */
            else
            {
                DataBufferDes = pChannelConfig->BufferDescriptor->BufferTX;
                DataBufferSrc = DataBufferPtr;
                for (Index = 0u;
                     Index < pChannelConfig->Length;
                     Index++)
                {
    /**
     @file Spi.c
     @note Violates MISRA 2004 Advisory Rules 17.4,12.13
     -see  @ref Spi_c_REF_4,Spi_c_REF_6
    */
                    *DataBufferDes++ = *DataBufferSrc++;
                }
                pChannelState->Flags =
                    (uint8)(pChannelState->Flags &
                            ((uint8) (~SPI_CHANNEL_FLAG_TX_DEFAULT)));
            }
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    /* Return status */
    return Status;
}
#endif
/*================================================================================================*/
/**
@brief   This function triggers the asynchronous transmission for the given sequence.
@details This function triggers the asynchronous transmission for the given sequence.
         - Service ID:       0x03
         - Sync/Async:       Asynchronous
         - Reentrancy:       Reentrant

@param[in]      Sequence            Sequence ID

@return Std_ReturnType
        - E_OK - Transmission command has been accepted
        - E_NOT_OK - Transmission command has not been accepted

@pre  The driver needs to be initialized before calling Spi_AsyncTransmit()
      otherwise, the function Spi_AsyncTransmit()  raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.

@remarks Implements DSPI02304, DSPI06000, DSPI04091, DSPI05100
@remarks Implements DSPI04096, DSPI02200, DSPI04332, DSPI04333
@remarks Implements DSPI04111, DSPI04125, DSPI04237, DSPI04094, DSPI04097, DSPI05200

*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static)  */
FUNC (Std_ReturnType, SPI_CODE) Spi_AsyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequenceConfig;
    P2VAR(Spi_SequenceState, AUTOMATIC, SPI_VAR) pSequenceState;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2CONST(Spi_JobType, AUTOMATIC, SPI_CONST) pJob;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    VAR(Spi_JobType, AUTOMATIC) NumJobsInSequence;
    VAR(Spi_JobType, AUTOMATIC) JobIndex;
    VAR(Spi_JobType, AUTOMATIC) Job;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
    VAR(Spi_ChannelType, AUTOMATIC) ChannelID;
    VAR(Spi_ChannelType, AUTOMATIC) NumChannelsInJob;
    VAR(Spi_ChannelType, AUTOMATIC) ChannelIndex;
#endif
#endif

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_ASYNCTRANSMIT_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    /* Sequence Valid Range */
    else if (Sequence >= (SpiConfigPtr->Spi_Max_Sequence))
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_ASYNCTRANSMIT_ID,
                        SPI_E_PARAM_SEQ);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        pSequenceConfig = &SpiConfigPtr->SequenceConfig[Sequence];
        /* Get the number of jobs in the sequence */
        NumJobsInSequence = pSequenceConfig->NumJobs;

        /* check for empty sequence */
        if (0u == NumJobsInSequence)
        {
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_ASYNCTRANSMIT_ID,
                            SPI_E_SEQ_EMPTY);
            Status = (Std_ReturnType)E_NOT_OK;
        }

        JobIndex = 0u;
        while(JobIndex < NumJobsInSequence)
        {
           /* Get the job id */
     /**
     @file Spi.c
     @note Violates MISRA 2004 Advisory Rules 17.4
     -see  @ref Spi_c_REF_4
     */
     /*lint -save -e960*/
            Job = pSequenceConfig->JobIndexList[JobIndex];

            pJobConfig = &SpiConfigPtr->JobConfig[Job];
            /*lint -restore*/

            /* start job notification to assert the non-cs pin,
                when non-cs pin is used as chipselect*/
            if (NULL_PTR != pJobConfig->StartNotification)
            {
                pJobConfig->StartNotification();
            }
            /* check for empty jobs */
            if (0u == pJobConfig->NumChannels)
            {
                /* Call Det_ReportError */
                Det_ReportError((uint16) SPI_MODULE_ID,
                                (uint8) 0,
                                SPI_ASYNCTRANSMIT_ID,
                                SPI_E_JOB_EMPTY);
                Status = (Std_ReturnType)E_NOT_OK;
            }

            /* Logical Spi HWUnit */
            HWUnit = pJobConfig->HWUnit;

            /* SPI128,SPI129,SPI130,SPI131 */
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
      -see@ref Spi_c_REF_4
    */
            if (SPI_PHYUNIT_ASYNC !=
                SpiConfigPtr->HWUnitConfig[HWUnit].IsSync)
            {
                /* HwUnit is not prearranged for dedicated Asynchronous
                   transmission */
                /* Call Det_ReportError */
                Det_ReportError((uint16) SPI_MODULE_ID,
                                (uint8) 0,
                                SPI_ASYNCTRANSMIT_ID,
                                SPI_E_PARAM_UNIT);
                Status = (Std_ReturnType)E_NOT_OK;
            }
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
            if ((Std_ReturnType)E_OK == Status)
            {
                /* Check if all EBs have been setup */
                NumChannelsInJob = pJobConfig->NumChannels;
                for (ChannelIndex =(Spi_ChannelType) 0;
                     ChannelIndex <  NumChannelsInJob;
                     ChannelIndex++)
                {
     /**
      @file Spi.c
      @note Violates MISRA 2004 Advisory Rules 17.4
      -see @ref Spi_c_REF_4
     */
                    ChannelID = pJobConfig->ChannelIndexList[ChannelIndex];
                    if (EB ==
                        SpiConfigPtr->ChannelConfig[ChannelID].BufferType)
                    {
                        /* Length is 0 for unconfigured ext. buffers */
                        if (0U == SpiChannelState[ChannelID].Length)
                        {
                            /* An used EB not initialized  */
                            Det_ReportError((uint16) SPI_MODULE_ID,
                                            (uint8) 0,
                                            SPI_ASYNCTRANSMIT_ID,
                                            SPI_E_PARAM_EB_UNIT);
                            Status = (Std_ReturnType)E_NOT_OK;
                            break;
                        }
                    }
                }
            }
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) ) */
            if ((Std_ReturnType)E_OK != Status)
            {
                /* break */
                break;
            }
            JobIndex++;
        }

        if ((Std_ReturnType)E_OK == Status)
        {
#else /* (SPI_DEV_ERROR_DETECT == STD_OFF) */
            pSequenceConfig = &SpiConfigPtr->SequenceConfig[Sequence];
#endif /* (SPI_DEV_ERROR_DETECT == STD_OFF) */

            Status = Spi_LockJobs(Sequence, pSequenceConfig);
            if ((Std_ReturnType)E_OK == Status)
            {
                pSequenceState = &SpiSequenceState[Sequence];
                /* Mark sequence pending */
                pSequenceState->Result = SPI_SEQ_PENDING;

                /* Initialize job related information */
                pSequenceState->RemainingJobs = pSequenceConfig->NumJobs - (Spi_JobType) 1u;
                /**
                      @file Spi.c
                      @note Violates MISRA 2004 Advisory Rules 17.4
                      -see @ref Spi_c_REF_4
                */
                pJob = &pSequenceConfig->JobIndexList[0];
                pSequenceState->CurrentJobIndexPointer = pJob;

                /* Schedule transmission of the first job */
                /**
                 @file Spi.c
                 @note Violates MISRA 2004 Advisory Rules 17.4
                 -see @ref Spi_c_REF_4
                */
                pJobConfig = &SpiConfigPtr->JobConfig[*pJob];
                Spi_ScheduleJob(&SpiHWUnitQueueArray[pJobConfig->HWUnit],
                                *pJob, pJobConfig);
            }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            else
            {
                /* Call Det_ReportError */
                Det_ReportError((uint16) SPI_MODULE_ID,
                                (uint8) 0,
                                SPI_ASYNCTRANSMIT_ID,
                                SPI_E_SEQ_PENDING);
            }
#endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */

    return Status;
}

#endif
/*================================================================================================*/
/**
@brief   This function reads the data from the buffer of a specific channel
         and puts at the specified memory location.
@details This function reads the data from the buffer of a specific channel
         and puts at the specified memory location.
         - Service ID:       0x04
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant


@param[in]      Channel             Channel ID
@param[in,out]  DataBufferPtr       Pointer to the memory location that will
                                    be written with the data in the internal
                                    buffer

@return Std_ReturnType
        - E_OK - read command has been accepted
        - E_NOT_OK - read command has not been accepted

@pre  The driver needs to be initialized before calling Spi_ReadIB()
      otherwise, the function Spi_ReadIB() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_CHANNEL_BUFFERS_ALLOWED shall be USAGE0 or USAGE2.

@remarks Implements DSPI02305, DSPI06000, DSPI04091, DSPI02180, DSPI02130, DSPI02120

*/
/*================================================================================================*/
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE0) || \
      (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_ReadIB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DataBufferPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    VAR(Spi_NumberOfDataType, AUTOMATIC) Index;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DataBufferSrc;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DataBufferDes;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_READIB_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    /* Channel valid range - Channels range is from 0 to (Spi_Max_Channel-1) */
    else if (Channel >= SpiConfigPtr->Spi_Max_Channel)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_READIB_ID,
                        SPI_E_PARAM_CHANNEL);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        pChannelConfig = &SpiConfigPtr->ChannelConfig[Channel];

        /* exit early if this is the wrong buffer type or destination
           is invalid */
        if (EB == pChannelConfig->BufferType)
        {
            /* Call Det_ReportError */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_READIB_ID,
                            SPI_E_PARAM_CHANNEL);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else if (NULL_PTR == DataBufferPtr)
        {
            /* Call Det_ReportError */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_READIB_ID,
                            SPI_E_PARAM_CHANNEL);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Copy Rx buffer to IB buffer */
            DataBufferSrc = pChannelConfig->BufferDescriptor->BufferRX;
            DataBufferDes = DataBufferPtr;
            for (Index = 0u; Index < pChannelConfig->Length; Index++)
            {
                /**
                 @file Spi.c
                 @note Violates MISRA 2004 Advisory Rules 17.4,12.13
                 -see  @ref Spi_c_REF_4,Spi_c_REF_6
                */

                *DataBufferDes++ = *DataBufferSrc++;
            }
        }

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return Status;
}
#endif
/*================================================================================================*/
/**
@brief   This function setup an external buffer to be used by a specific channel.
@details This function setup an external buffer to be used by a specific channel.
         - Service ID:       0x05
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      Channel             Channel ID
@param[in]      SrcDataBufferPtr    Pointer to the memory location that will hold
                                    the transmitted data
@param[in]      Length              Length of the data in the external buffer
@param[out]     DesDataBufferPtr    Pointer to the memory location that will hold
                                    the received data

@return Std_ReturnType
        - E_OK - Setup command has been accepted
        - E_NOT_OK - Setup command has not been accepted

@pre  The driver needs to be initialized before calling Spi_SetupEB()
      otherwise, the function Spi_SetupEB() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_CHANNEL_BUFFERS_ALLOWED shall be USAGE1 or USAGE2.

@remarks Implements DSPI02306, DSPI06000, DSPI04091, DSPI02180, DSPI02130, DSPI02120
*/
/*================================================================================================*/
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || \
      (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_SetupEB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_CONST) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DesDataBufferPtr,
    VAR(Spi_NumberOfDataType, AUTOMATIC) Length)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) pChannelState;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETUPEB_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    /* Channel ID - Valid channels range is from 0 to (Spi_Max_Channel-1)*/
    else if (Channel >= SpiConfigPtr->Spi_Max_Channel)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETUPEB_ID,
                        SPI_E_PARAM_CHANNEL);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    /* Length - Valid range */
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
    else if ((Length > SpiConfigPtr->ChannelConfig[Channel].Length) || (0u == Length))
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETUPEB_ID,
                        SPI_E_PARAM_LENGTH);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
        pChannelState = &SpiChannelState[Channel];
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        pChannelConfig = &SpiConfigPtr->ChannelConfig[Channel];
        /* exit early if this is the wrong buffer type */
        if (IB == pChannelConfig->BufferType)
        {
            /* Call Det_ReportError */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_SETUPEB_ID,
                            SPI_E_PARAM_CHANNEL);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* save the new parameters */
            /**
            @note Violates MISRA 2004 Advisory Rules 11.4,11.5
                    - See @ref Spi_c_REF_3,Spi_c_REF_5
            */
            /*lint -save -e929*/
            ((P2VAR(Spi_BufferDescriptor, AUTOMATIC, SPI_VAR))
                pChannelConfig->BufferDescriptor)->BufferTX =
                (P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR)) SrcDataBufferPtr;
            ((P2VAR(Spi_BufferDescriptor, AUTOMATIC, SPI_VAR))
                pChannelConfig->BufferDescriptor)->BufferRX = DesDataBufferPtr;
            /*lint -restore*/
            pChannelState->Length = Length;

            /* if source data pointer is zero, transmit default value */
            if (NULL_PTR == SrcDataBufferPtr)
            {
                pChannelState->Flags |= SPI_CHANNEL_FLAG_TX_DEFAULT;
            }
            else
            {
                pChannelState->Flags &= (uint8) (~SPI_CHANNEL_FLAG_TX_DEFAULT);
            }

            /* if destination data pointer is zero, discard receiving data */
            if (NULL_PTR == DesDataBufferPtr)
            {
                pChannelState->Flags |= SPI_CHANNEL_FLAG_RX_DISCARD;
            }
            else
            {
                pChannelState->Flags &= (uint8) (~SPI_CHANNEL_FLAG_RX_DISCARD);
            }
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return Status;
}
#endif
/*================================================================================================*/
/**
@brief   This function returns the status of the SPI driver.
@details This function returns the status of the SPI driver.
         - Service ID:       0x06
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@return Spi_StatusType
        - SPI_UNINIT - The driver is un-initialized
        - SPI_IDLE - The driver has no pending transfers
        - SPI_BUSY - The driver is busy

@pre  The driver needs to be initialized before calling Spi_GetStatus()
      otherwise, the function Spi_GetStatus() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.

@remarks Implements DSPI02307, DSPI06000, DSPI04091, DSPI04151, DSPI04152, DSPI04125, DSPI04237

*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Spi_StatusType, SPI_CODE) Spi_GetStatus(void)
{
    VAR(Spi_StatusType, AUTOMATIC) Spi_StatusFlag = SPI_IDLE;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;

    if (NULL_PTR == SpiConfigPtr)
    {
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* If Development Error Detection is enabled, report error if not */
        /* initialized */
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETSTATUS_ID,
                        SPI_E_UNINIT);
#endif
        Spi_StatusFlag = SPI_UNINIT;
    }
    else
    {
        /* The SPI Handler/Driver software module shall be busy when any
           HWUnit is busy */
        if (0u != SpiBusySyncHWUnitsStatus)
        {
            /* a Spi_SyncTransmit() is pending */
            Spi_StatusFlag = SPI_BUSY;
        }
        else
        {
            /* check for busy HWUnit in async transmissions*/
            /* Note: Checking for IsSync attribute for HWUnit is not really needed
                 It is preferable to skip this check in order to have a more compact code
            */
            for (HWUnit = 0u; HWUnit < (Spi_HWUnitType)SPI_MAX_HWUNIT; HWUnit++)
            {
                if (SPI_BUSY == SpiHWUnitQueueArray[HWUnit].Status)
                {
                    Spi_StatusFlag = SPI_BUSY;
                    break;
                }
            }
        }
    }
    return Spi_StatusFlag;
}
/*================================================================================================*/
/**
@brief   This function is used to request the status of a specific job.
@details This function is used to request the status of a specific job.
         - Service ID:       0x07
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      Job                 Job ID

@return Spi_JobResultType
        - SPI_JOB_OK - The job ended successfully
        - SPI_JOB_PENDING - The job is pending
        - SPI_JOB_FAILED - The job has failed

@pre  The driver needs to be initialized before calling Spi_GetJobResult()
      otherwise, the function Spi_GetJobResult() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.

@remarks Implements DSPI02308, DSPI06000, DSPI04091, DSPI04191, DSPI02160, DSPI04235, DSPI02180

*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Spi_JobResultType, SPI_CODE) Spi_GetJobResult(
    VAR(Spi_JobType, AUTOMATIC) Job)
{
    VAR(Spi_JobResultType, AUTOMATIC) JobResult;

#if (SPI_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        JobResult = SPI_JOB_FAILED;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETJOBRESULT_ID,
                        SPI_E_UNINIT);
    }
    /* Job Valid Range - from 0 to (Spi_Max_Job-1)*/
    else if (Job >= SpiConfigPtr->Spi_Max_Job)
    {
        JobResult = SPI_JOB_FAILED;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETJOBRESULT_ID,
                        SPI_E_PARAM_JOB);
    }
    else
    {
#endif
        JobResult = SpiJobState[Job].Result;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return JobResult;
}
/*================================================================================================*/
/**
@brief   This function is used to request the status of a specific sequence.
@details This function is used to request the status of a specific sequence.
         - Service ID:       0x08
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      Sequence            Sequence ID

@return Spi_SeqResultType
        - SPI_SEQ_OK - The sequence ended successfully
        - SPI_SEQ_PENDING - The sequence is pending
        - SPI_SEQ_FAILED - The sequence has failed

@pre  The driver needs to be initialized before calling Spi_GetSequenceResult()
      otherwise, the function Spi_GetSequenceResult() raises the development
      error if SPI_DEV_ERROR_DETECT is STD_ON.

@remarks Implements DSPI02309, DSPI06000, DSPI04091, DSPI05100, DSPI04212

*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Spi_SeqResultType, SPI_CODE) Spi_GetSequenceResult(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence)
{
    VAR(Spi_SeqResultType, AUTOMATIC) SequenceResult;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        SequenceResult = SPI_SEQ_FAILED;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETSEQUENCERESULT_ID,
                        SPI_E_UNINIT);
    }
    /* Sequence Valid Range from 0 to (Spi_Max_Sequence-1)*/
    else if (Sequence >= SpiConfigPtr->Spi_Max_Sequence)
    {
        SequenceResult = SPI_SEQ_FAILED;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETSEQUENCERESULT_ID,
                        SPI_E_PARAM_SEQ);
    }
    else
    {
#endif
        SequenceResult = SpiSequenceState[Sequence].Result;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return SequenceResult;
}

#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
/*================================================================================================*/
/**
@brief   This function is used for synchronous transmission of a given sequence.
@details This function is used for synchronous transmission of a given sequence.
         - Service ID:       0x0a
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      Sequence            Sequence ID

@return Std_ReturnType
        - E_OK - Transmission command has been completed successfully
        - E_NOT_OK - Transmission command has not been accepted

@pre  The driver needs to be initialized before calling Spi_SyncTransmit().
      otherwise, the function Spi_SyncTransmit() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL0 or LEVEL2

@remarks Implements DSPI02311, DSPI04236, DSPI06000, DSPI04091, DSPI05100
 @remarks Implements DSPI02180, DSPI04235, DSPI04234, DSPI04233, DSPI04232
 @remarks Implements DSPI02200, DSPI04125, DSPI04237, DSPI04231, DSPI02110
 @remarks Implements DSPI01451
*/
/*================================================================================================*/
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_SyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence)
{
    P2VAR(Spi_SequenceState, AUTOMATIC, SPI_VAR) pSequenceState;
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    VAR(uint32, AUTOMATIC) SpiSequenceUsedHWUnits;

#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
    P2VAR(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR) pSequenceCache;
#endif

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequenceConfig;
    VAR(Spi_JobType, AUTOMATIC) Job;
    VAR(Spi_JobType, AUTOMATIC) JobIndex;
    VAR(Spi_JobType, AUTOMATIC) NumJobsInSequence;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    VAR(uint32, AUTOMATIC) UnitIsSync;
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
    VAR(Spi_ChannelType, AUTOMATIC)ChannelID;
    VAR(Spi_ChannelType, AUTOMATIC) NumChannelsInJob;
    VAR(Spi_ChannelType, AUTOMATIC)ChannelIndex;
#endif
#endif

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SYNCTRANSMIT_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    /* Sequence Valid Range */
    else if (Sequence >= SpiConfigPtr->Spi_Max_Sequence)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SYNCTRANSMIT_ID,
                        SPI_E_PARAM_SEQ);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        pSequenceConfig = &SpiConfigPtr->SequenceConfig[Sequence];

        /* Get the number of jobs in the sequence */
        NumJobsInSequence = pSequenceConfig->NumJobs;

        for (JobIndex = 0u; JobIndex < NumJobsInSequence; JobIndex++)
        {
            /* Get the job id */
            /**
             @file Spi.c
             @note Violates MISRA 2004 Advisory Rules 17.4
             -see  @ref Spi_c_REF_4
             */
            Job = pSequenceConfig->JobIndexList[JobIndex];

            pJobConfig = &SpiConfigPtr->JobConfig[Job];

            /* Logical Spi HWUnit */
            HWUnit = pJobConfig->HWUnit;

            /**
             @file Spi.c
             @note Violates MISRA 2004 Advisory Rules 17.4
             -see  @ref Spi_c_REF_4
             */
            UnitIsSync = SpiConfigPtr->HWUnitConfig[HWUnit].IsSync;
            /* SPI128,SPI129,SPI130,SPI131 */
            if ((uint32)(SPI_PHYUNIT_ASYNC) == (UnitIsSync))
            {
                /* HwUnit is not prearranged for dedicated Synchronous
                   transmission */
                Det_ReportError((uint16) SPI_MODULE_ID,
                                (uint8) 0,
                                SPI_SYNCTRANSMIT_ID,
                                SPI_E_PARAM_UNIT);
                Status = (Std_ReturnType)E_NOT_OK;
            }
#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) )
            if ((Std_ReturnType)E_OK == Status)
            {
                /* Check if all EBs have been setup */
                NumChannelsInJob = pJobConfig->NumChannels;
                for (ChannelIndex =(Spi_ChannelType) 0;
                     ChannelIndex <  NumChannelsInJob;
                     ChannelIndex++)
                {
               /**
                @file Spi.c
                @note Violates MISRA 2004 Advisory Rules 17.4
                -see  @ref Spi_c_REF_4
               */
               /*lint -save -e960*/
                    ChannelID = pJobConfig->ChannelIndexList[ChannelIndex];
                    if (EB ==
                        SpiConfigPtr->ChannelConfig[ChannelID].BufferType)
               /*lint -restore*/
                    {
                        /* Channel length is 0 for unconfigured ext. buffers */
                        if (0U == SpiChannelState[ChannelID].Length)
                        {
                            /* An used EB not initialized  */
                            Det_ReportError((uint16) SPI_MODULE_ID, (uint8) 0,
                                            SPI_SYNCTRANSMIT_ID,
                                            SPI_E_PARAM_EB_UNIT);
                            Status = (Std_ReturnType)E_NOT_OK;
                            break;
                        }
                    }
                }
            }
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == USAGE2) ) */
            if ((Std_ReturnType)E_NOT_OK == Status)
            {
                /* break */
                break;
            }
        }

        if ((Std_ReturnType)E_NOT_OK != Status)
        {
#endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
            SpiSequenceUsedHWUnits = SpiSeqUsedHWUnits[Sequence];

            SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_01);

            /* check if there are HW units already running */
            if ( 0u != (SpiBusySyncHWUnitsStatus & SpiSequenceUsedHWUnits) )
            {
                Status = (Std_ReturnType)E_NOT_OK;

                SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_01);

#if (SPI_DEV_ERROR_DETECT == STD_ON)

                /* Call Det_ReportError */
                Det_ReportError((uint16) SPI_MODULE_ID,
                                (uint8) 0,
                                SPI_SYNCTRANSMIT_ID,
                                SPI_E_SEQ_IN_PROCESS);

#endif
            }
            else
            {
                /* Set the sequence as pending */
                pSequenceState = &SpiSequenceState[Sequence];
                pSequenceState->Result = (Spi_SeqResultType) SPI_SEQ_PENDING;

                /* set used HW units as busy */
                SpiBusySyncHWUnitsStatus |= SpiSequenceUsedHWUnits;

                SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_01);

#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
                pSequenceCache = DspiOneJobSeqsOptimized[Sequence];
                if (NULL_PTR != pSequenceCache)
                {
                    Status = Spi_LLD_SyncTransmit_Fast(pSequenceCache);
                }
                else
                {
                    Status = Spi_LLD_SyncTransmit( Sequence);
                }
#else /* (SPI_OPTIMIZE_ONE_JOB_SEQUENCES != STD_ON) */
                Status = Spi_LLD_SyncTransmit( Sequence);
#endif

                SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_02);

                if ((Std_ReturnType)E_OK == Status)
                {
                    /* Set the sequence as OK */
                    pSequenceState->Result = SPI_SEQ_OK;
                }
                else
                {
                    /* Set the sequence as FAILED */
                    pSequenceState->Result = SPI_SEQ_FAILED;
                }

                /* set used HW units as idle */
                SpiBusySyncHWUnitsStatus &= (~SpiSequenceUsedHWUnits);

                SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_02);

            }

#if (SPI_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif

    return Status;
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) ) */

/*================================================================================================*/
/**
@brief   This function is used to request the status of a specific SPI peripheral unit.
@details This function is used to request the status of a specific SPI peripheral unit.
         - Service ID:       0x0b
         - Sync/Async:       Synchronous
         - Reentrancy:       Reentrant

@param[in]      HWUnit              The HW peripheral for which we need the status

@return Spi_StatusType
        - SPI_UNINIT - The peripheral is un-initialized
        - SPI_IDLE - The peripheral is in idle state
        - SPI_BUSY - The peripheral is busy

@pre  The driver needs to be initialized before calling Spi_GetHWUnitStatus()
      otherwise, the function Spi_GetHWUnitStatus() raises the development
      error if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  SPI_HW_STATUS_API == STD_ON

@remarks Implements DSPI02312, DSPI06000, DSPI04091, DSPI02150, DSPI04251
@remarks Implements DSPI02130, DSPI02180

*/
/*================================================================================================*/
#if (SPI_HW_STATUS_API == STD_ON)
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit)
{
    VAR(Spi_StatusType, AUTOMATIC) Status = SPI_UNINIT;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (SpiConfigPtr == NULL_PTR)
    {
        Status = SPI_UNINIT;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETHWUNITSTATUS_ID,
                        SPI_E_UNINIT);

    }
    else if (HWUnit >= SPI_MAX_HWUNIT)
    {
        Status = SPI_UNINIT;
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_GETHWUNITSTATUS_ID,
                        SPI_E_PARAM_UNIT);
    }
    else
    {
#endif
        Status = SpiHWUnitQueueArray[HWUnit].Status;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif
    return Status;
}
#endif
/*================================================================================================*/
/**
@brief   This function is used to request the cancelation of the given sequence.
@details This function is used to request the cancelation of the given sequence.
         - Service ID:       0x0c
         - Sync/Async:       Asynchronous
         - Reentrancy:       Reentrant

@param[in]      Sequence            Sequence ID

@pre  The driver needs to be initialized before calling Spi_Cancel()
      otherwise, the function Spi_Cancel() raises the development error
      if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_CANCEL_API shall be STD_ON
@post  The SPI Handler/Driver is not responsible on external devices damages or
      undefined state due to cancelling a sequence transmission.

@remarks Implements DSPI02313, DSPI06000, DSPI04091, DSPI05100, DSPI04271, DSPI02180

*/
/*================================================================================================*/
#if (SPI_CANCEL_API == STD_ON)
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (void, SPI_CODE) Spi_Cancel(VAR(Spi_SequenceType, AUTOMATIC) Sequence)
{
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (SpiConfigPtr == NULL_PTR)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_CANCEL_ID,
                        SPI_E_UNINIT);
    }
    /* Sequence Valid Range  from 0 to (Spi_Max_Sequence-1)*/
    else if (Sequence >= SpiConfigPtr->Spi_Max_Sequence)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_CANCEL_ID,
                        SPI_E_PARAM_SEQ);
    }
    else
    {
#endif
        /* Set sequence state to Cancel */
        SpiSequenceState[Sequence].Result = SPI_SEQ_CANCELLED;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif
/*================================================================================================*/
/**
@brief   This function specifies the asynchronous mode for the SPI busses
         handled asynchronously.
@details This function specifies the asynchronous mode for the SPI busses
         handled asynchronously.
         - Service ID:       0x0d
         - Sync/Async:       Synchronous
         - Reentrancy:       Non-Reentrant

@param[in]      AsyncMode    This parameter specifies the asynchronous
                             operating mode (SPI_POLLING_MODE or
                             SPI_INTERRUPT_MODE)

@return Std_ReturnType
        - E_OK - The command ended successfully
        - E_NOT_OK - The command has failed

@pre  The driver needs to be initialized before calling Spi_SetAsyncMode()
      otherwise, the function Spi_SetAsyncMode() raises the development
      error if SPI_DEV_ERROR_DETECT is STD_ON.
@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL2

@remarks Implements DSPI02314, DSPI06000, DSPI04091, DSPI02180
@remarks Implements DSPI02120

*/
/*================================================================================================*/
#if (SPI_LEVEL_DELIVERED == LEVEL2)
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_SetAsyncMode(
    VAR(Spi_AsyncModeType, AUTOMATIC) AsyncMode)
{
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (SpiConfigPtr == NULL_PTR)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETASYNCMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
        if (SPI_BUSY == Spi_GetAsyncStatus())
        {
            /* Call Det_ReportError */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_SETASYNCMODE_ID,
                            SPI_E_SEQ_PENDING);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* set the async mode for each HW Unit;
               activate/deactivate EOQ interrupts for Async HWUnits */
            for (HWUnit = 0u;
                 HWUnit < (Spi_HWUnitType) SPI_MAX_HWUNIT;
                 HWUnit++)
            {
                Spi_LLD_IrqConfig(HWUnit, AsyncMode);
            }
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return Status;
}
#endif

/**
@brief   This function specifies the asynchronous mode for a given HWUnit.
@details This function specifies the asynchronous mode for the SPI busses
         handled asynchronously.
         For synchronous HW units, the function has no impact.
         The function will fail in two cases:
         - driver not initialised (SPI_E_UNINIT reported by DET)
         - a sequence transmission is pending the the asynchronous HW unit
           (SPI_E_SEQ_PENDING reported by DET)

@param[in]      HWUnit       The ID of the HWUnit to be configured
@param[in]      AsyncMode    This parameter specifies the asynchronous
                             operating mode (SPI_POLLING_MODE or
                             SPI_INTERRUPT_MODE)

@return Std_ReturnType
        - E_OK - The command ended successfully
        - E_NOT_OK - The command has failed

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL2 and
      SPI_HWUNIT_ASYNC_MODE should be on STD_ON

@remarks Implements DSPI01320, DSPI06000, DSPI04091, DSPI02314, DSPI01310
*/
#if ((SPI_LEVEL_DELIVERED == LEVEL2) && (SPI_HWUNIT_ASYNC_MODE == STD_ON))
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (Std_ReturnType, SPI_CODE) Spi_SetHWUnitAsyncMode(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
    VAR(Spi_AsyncModeType, AUTOMATIC) AsyncMode)
{
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (SpiConfigPtr == NULL_PTR)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETHWUNITASYNCMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
    /**
     @file Spi.c
     @note Violates MISRA 2004 Advisory Rules 17.4
     -see  @ref Spi_c_REF_4
    */
        if (SPI_PHYUNIT_ASYNC != SpiConfigPtr->HWUnitConfig[HWUnit].IsSync)
        {
            /* return E_NOT_OK if HWUnit is Sync */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_SETHWUNITASYNCMODE_ID,
                            SPI_E_PARAM_UNIT);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else if (SPI_BUSY == SpiHWUnitQueueArray[HWUnit].Status)
        {
        /* return E_NOT_OK if HWUnit is Async and Busy */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_SETHWUNITASYNCMODE_ID,
                            SPI_E_SEQ_PENDING);
#endif
            Status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* set the async mode & activate/deactivate the interrupts
               for the HW Unit
             */
            Spi_LLD_IrqConfig(HWUnit, AsyncMode);
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    }
#endif

    return Status;
}
#endif /* (SPI_LEVEL_DELIVERED == LEVEL2) && (SPI_HWUNIT_ASYNC_MODE == STD_ON) */

/*================================================================================================*/
/**
@brief   This function shall asynchronously poll SPI interrupts and call
         ISR if appropriate.
@details This function shall asynchronously poll SPI interrupts and call
         ISR if appropriate.
         - Service ID:       0x11

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@remarks Implements DSPI02180
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (void, SPI_CODE) Spi_MainFunction_Driving(void)
{
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev;

    if (NULL_PTR != SpiConfigPtr)
    {
        for (HWUnit = 0u;
             HWUnit < (Spi_HWUnitType) SPI_MAX_HWUNIT;
             HWUnit++)
        {
            DspiDev = DSPI_HWUNIT2DSPI(HWUnit);
            if ((SPI_POLLING_MODE == DspiDev->AsyncMode) &&
                (SPI_BUSY == SpiHWUnitQueueArray[HWUnit].Status) &&
                (SPI_PHYUNIT_ASYNC == DspiDev->HWUnitConfig->IsSync))
            {
                Spi_LLD_IrqPoll(DspiDev);
            }
        }
    }
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) ) */

/*================================================================================================*/
/**
@brief   This function starts the transfer of the first scheduled job for a
         given HW unit
@details If the list of scheduled jobs is not empty, pop the first job and
         start the transfer. Elsewhere, mark the HW unit as IDLE.

@param[in]      pHWUnitQueue     The HW Unit used for scheduling

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.

@remarks Implements DSPI04122

*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC FUNC (void, SPI_CODE) Spi_ScheduleNextJob(
    P2VAR(Spi_HWUnitQueue, AUTOMATIC, SPI_VAR) pHWUnitQueue)
{
    VAR(Spi_JobType, AUTOMATIC) Job;
    P2VAR(Spi_JobType, AUTOMATIC, SPI_VAR) pJobListHead;
    VAR(sint8, AUTOMATIC) Priority;
    VAR(sint8, AUTOMATIC) MaxScheduledPriority =
        pHWUnitQueue->MaxScheduledPriority;

    SchM_Enter_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_04);
    if (MaxScheduledPriority < 0)
    {
        /* no job waiting => mark the HWUnit as IDLE */
        pHWUnitQueue->Status = SPI_IDLE;
        SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_04);
    }
    else
    {
        /* a job is waiting => get the job ID from the highest priority queue */
        pJobListHead =
            &pHWUnitQueue->ScheduledJobsListHead[MaxScheduledPriority];
        Job = *pJobListHead;

        /* set the new head of the list */
        *pJobListHead = SpiJobState[Job].AsyncNextJob;

        /* if the list is empty, set the tail accordingly and adjust the
           scheduled priority level */
        if (SPI_JOB_NULL == *pJobListHead)
        {
            /* reset the tail */
            pHWUnitQueue->ScheduledJobsListTail[MaxScheduledPriority] =
                SPI_JOB_NULL;

            /* find the first non empty scheduling queue */
            for (Priority = MaxScheduledPriority - 1;
                 Priority >= 0;
                 Priority--)
            {
                if (SPI_JOB_NULL !=
                    pHWUnitQueue->ScheduledJobsListHead[Priority])
                {
                    /* there is a scheduled Job for this priority level */
                    break;
                }
            }

            /* Priority is set on the highest priority queue having
               scheduled jobs, or -1 if no other jobs scheduled */
            pHWUnitQueue->MaxScheduledPriority = Priority;
        }
        SchM_Exit_Spi(SCHM_SPI_INSTANCE_0, SPI_EXCLUSIVE_AREA_04);

        /* mark the job as pending */
        SpiJobState[Job].Result = SPI_JOB_PENDING;
    /**
    @file Spi.c
    @note Violates MISRA 2004 Advisory Rules 17.4
    -see  @ref Spi_c_REF_4
    */
        Spi_LLD_JobTransfer(&SpiConfigPtr->JobConfig[Job]);
    }
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) ) */

/*================================================================================================*/
/**
@brief   This function is called after a Job has been executed.
@details The function calls Job and Sequence end notifications and schedules
         the next job of the sequence or on the liberated HW Unit.

@param[in]    pJobConfig   The just transmited job pointer.

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.

@remarks Implements DSPI02332, DSPI04333, DSPI04113, DSPI04116, DSPI04271, DSPI04333
@remarks Implements DSPI04114, DSPI04112, DSPI04123
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/** @note Violates MISRA 2004 Required Rule 8.10 (local variable must be defined as static) */
FUNC (void, SPI_CODE) Spi_JobTransferFinished(
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig)
{
    VAR(Spi_HWUnitType, SPI_VAR) HWUnit = pJobConfig->HWUnit;
    P2VAR(Spi_HWUnitQueue, AUTOMATIC, SPI_VAR) pHWUnitQueue =
        &SpiHWUnitQueueArray[HWUnit];
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) pJobState =
        pJobConfig->JobState;
    P2VAR(Spi_SequenceState, AUTOMATIC, SPI_VAR) pSequenceState =
        pJobState->AsyncCrtSequenceState;
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequenceConfig =
        pSequenceState->Sequence;
    P2CONST(Spi_JobType, AUTOMATIC, SPI_CONST) pJob;
    VAR(Spi_JobType, SPI_VAR) Job;

    pJobState->Result = SPI_JOB_OK;

    /* unlink the job from its sequence */
    pJobState->AsyncCrtSequenceState = NULL_PTR;

    /* Perform job EndNotification (if there is one) */
    if (NULL_PTR != pJobConfig->EndNotification)
    {
        pJobConfig->EndNotification();
    }

#if (SPI_CANCEL_API == STD_ON)
    /* Check if current sequence has been cancelled */
    if (SPI_SEQ_CANCELLED == pSequenceState->Result)
    {

        /* unlock jobs */
        Spi_UnlockRemainingJobs(pSequenceState->RemainingJobs, pSequenceConfig);

        if (NULL_PTR != pSequenceConfig->EndNotification)
        {
            pSequenceConfig->EndNotification();
        }
        Spi_ScheduleNextJob(pHWUnitQueue);
    }
    else
    {
#endif
        /* Check if this job is the last one */
        if (0u == pSequenceState->RemainingJobs)
        {
            /* Reset sequence state */
            pSequenceState->Result = SPI_SEQ_OK;

            /* SeqEndNotification */
            if (NULL_PTR != pSequenceConfig->EndNotification)
            {
                pSequenceConfig->EndNotification();
            }

            Spi_ScheduleNextJob(pHWUnitQueue);

        }
        else
        {
            /* advance to the next job */
    /**
             @file Spi.c
             @note Violates MISRA 2004 Advisory Rules 17.4
             -see  @ref Spi_c_REF_4
            */

            pSequenceState->CurrentJobIndexPointer++;
            pJob = pSequenceState->CurrentJobIndexPointer;
            Job = *pJob;
            pSequenceState->RemainingJobs--;

          /**
           @file Spi.c
           @note Violates MISRA 2004 Advisory Rules 17.4
           -see  @ref Spi_c_REF_4
          */
            pJobConfig = &SpiConfigPtr->JobConfig[Job];
            if (HWUnit != pJobConfig->HWUnit)
            {
                /* schedule the next job on the new DSPI unit */
                Spi_ScheduleJob(&SpiHWUnitQueueArray[pJobConfig->HWUnit],
                                Job, pJobConfig);

                /* transmit the next scheduled job on the current DSPI unit */
                Spi_ScheduleNextJob(pHWUnitQueue);
            }
            else
            {
                /* the next job uses the same DSPI unit */

#if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
                if (pSequenceConfig->Interruptible)
                {
                    /* if the sequence is interruptible,
                       then schedule the next job */
                    /* DSPI is marked as BUSY => the new job is scheduled only */
                    Spi_ScheduleJob(pHWUnitQueue, Job, pJobConfig);

                    /* run the first eligible job */
                    Spi_ScheduleNextJob(pHWUnitQueue);
                }
                else
#endif
                {
                    /* non-interruptible sequence =>
                       start transmission without scheduling */
                    /* mark the job as pending */
                    SpiJobState[Job].Result = SPI_JOB_PENDING;

                    Spi_LLD_JobTransfer(pJobConfig);
                }
            }
        }
#if (SPI_CANCEL_API == STD_ON)
    }
#endif
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) ) */

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/*================================================================================================*/
/**
@brief   This function shall set different MCU clock configuration .
@details This function shall set different MCU clock configuration .

@param[in]    ClockMode   Clock mode to be set (SPI_NORMAL | SPI_ALTERNATE).

@return Std_ReturnType
        - E_OK - The driver is initialised and in an IDLE state. The clock
                mode can be changed.
        - E_NOT_OK - The driver is NOT initialised OR is NOT in an IDLE state.
                    The clock mode can NOT be changed.

@pre  Pre-compile parameter SPI_DUAL_CLOCK_MODE shall be STD_ON.

@remarks Implements DSPI04331, DSPI04332, DSPI04333, DSPI02335, DSPI06000, DSPI04091, DSPI04091
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SPI_CODE) Spi_SetClockMode(
    VAR(Spi_DualClockMode,AUTOMATIC) ClockMode)
{
   VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error if not */
    /* initialized */
    if (NULL_PTR == SpiConfigPtr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETCLOCKMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
        /* Check if Spi Status is Busy */
        if (SPI_BUSY == Spi_GetStatus())
        {
            /* SPI0121 */
            Status = (VAR(Std_ReturnType, AUTOMATIC)) E_NOT_OK;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Call Det_ReportError */
            Det_ReportError((uint16) SPI_MODULE_ID,
                            (uint8) 0,
                            SPI_SETCLOCKMODE_ID,
                            SPI_E_SEQ_PENDING);
#endif
        }
        else
        {
            DSPI_SET_CLOCK_MODE(ClockMode);
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
}
#endif
        return Status;
}
#endif /* #if (SPI_DUAL_CLOCK_MODE == STD_ON) */

#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
/*================================================================================================*/
/**
@brief   This function shall to enable user to access the Micro Second Bus functionality .
@details A non-Autosar API to support the configuartion of the TSB
to enable user to access the Micro Second Bus functionality

@param[in]    Spi_JobType   Specifies the job confgiured in TSB mode

@return Std_ReturnType
        - E_OK - The driver is initialised . The TSB  mode can be configured.
        - E_NOT_OK - The driver is NOT initialised

@pre  Pre-compile parameter SPI_TSB_MODE shall be STD_ON.

@remarks Implements DSPI08000
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SPI_CODE) Spi_TSBStart(
     VAR(Spi_JobType, AUTOMATIC) TSBJob)
{

    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == SpiConfigPtr)
    {
          /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else if (TSBJob > SPI_MAX_TSBJOBS)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_TSBJOB);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
       {
         Spi_LLD_SetTSBMode(TSBJob);
       }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
}
#endif
        return Status;
}
/*================================================================================================*/
/**
@brief   This function shall to stop teh transfer in TSB mode .
@details A non-Autosar API to support the configuartion of the TSB
         Hardware is deinitialized to master and SPI mode.

@param[in]    Spi_JobType   Job configured in TSB mode

@return Std_ReturnType
        - E_OK - The driver is initialised . The TSB  mode can be configured.
        - E_NOT_OK - The driver is NOT initialised

@pre  Pre-compile parameter SPI_TSB_MODE shall be STD_ON.

@remarks Implements DSPI08000
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SPI_CODE) Spi_TSBStop(
     VAR(Spi_JobType, AUTOMATIC) TSBJob)
{

    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == SpiConfigPtr)
    {
          /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else if (TSBJob > SPI_MAX_TSBJOBS)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_TSBJOB);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
       {
         Spi_LLD_StopTSBMode(TSBJob);
       }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
}
#endif
        return Status;
}

/*================================================================================================*/
/**
@brief   This function shall to enable user to write data in ASDR (alternate serialisation register)
        while using Micro Second Bus functionality .
@details A non-Autosar API to support the configuartion of the TSB
to enable user to access the Micro Second Bus functionality

@param[in]    Spi_JobType   Specifies the job confgiured in TSB mode

@return Std_ReturnType
        - E_OK - The driver is initialised . The TSB  mode can be configured.
        - E_NOT_OK - The driver is NOT initialised

@pre  Pre-compile parameter SPI_TSB_MODE shall be STD_ON.

@remarks Implements DSPI08000
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SPI_CODE) Spi_TSB_ASDR_DataUpdate(
     VAR(Spi_JobType, AUTOMATIC) TSBJob,
     VAR(uint32, SPI_VAR) ASDR_Data)
{

    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == SpiConfigPtr)
    {
          /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_UNINIT);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else if (TSBJob > SPI_MAX_TSBJOBS)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16) SPI_MODULE_ID,
                        (uint8) 0,
                        SPI_SETTSBMODE_ID,
                        SPI_E_TSBJOB);
        Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif
       {
         Spi_LLD_TSB_ASDR_DataUpdate(TSBJob, ASDR_Data);
       }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
}
#endif
        return Status;
}
#endif /*SPI_TSB_MODE == STD_ON*/
#endif /*TSB_MODE_SUPPORTED*/
/*================================================================================================*/
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Spi_c_REF_1
*/
#define SPI_STOP_SEC_CODE
/**
@file Spi.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_c_REF_1 & @ref Spi_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif


