/**
    @file    Spi.h
    @version 2.0.0

    @brief   AUTOSAR Spi - Spi driver header file.
    @details AUTOSAR specific Spi driver header file.

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

@section Spi_h_REF_1
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Spi_h_REF_2
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
and comments before "#include". AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.

*/
#ifndef SPI_H
#define SPI_H

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
/**
@note Violates MISRA 2004 Advisory Rules 19.15 - See @ref Spi_h_REF_1
*/
#include "Std_Types.h"
#include "Spi_Cfg.h"
#include "Dspi_LLD_CfgEx.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the Spi driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@remarks Implements DSPI02306
@{
*/
#define SPI_VENDOR_ID           43
#define SPI_MODULE_ID           83
#define SPI_AR_MAJOR_VERSION    2
#define SPI_AR_MINOR_VERSION    2
#define SPI_AR_PATCH_VERSION    1
#define SPI_SW_MAJOR_VERSION    2
#define SPI_SW_MINOR_VERSION    0
#define SPI_SW_PATCH_VERSION    0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SPI header file are of the same vendor */
#if (SPI_VENDOR_ID != SPI_VENDOR_ID_CFG)
    #error "Spi.h and Spi_Cfg.h have different vendor ids"
#endif

/* Check if source file and SPI header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION != SPI_AR_MAJOR_VERSION_CFG) || \
       (SPI_AR_MINOR_VERSION != SPI_AR_MINOR_VERSION_CFG) || \
       (SPI_AR_PATCH_VERSION != SPI_AR_PATCH_VERSION_CFG))
      #error "AutoSar Version Numbers of Spi.h and Spi_Cfg.h are different"
  #endif
#endif

/* Check if source file and SPI header file are of the same Software version */
#if ((SPI_SW_MAJOR_VERSION != SPI_SW_MAJOR_VERSION_CFG) || \
     (SPI_SW_MINOR_VERSION != SPI_SW_MINOR_VERSION_CFG))
    #error "Software Version Numbers of Spi.h and Spi_Cfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define SPI_PHYUNIT_SYNC        (uint32)1u
#define SPI_PHYUNIT_ASYNC       (uint32)0u

/* Error Values */
/**
@brief API service called with wrong parameter
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_CHANNEL       (uint8)0x0Au
/**
@brief API service called with wrong parameter
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_JOB           (uint8)0x0Bu
/**
@brief API service called with wrong parameter
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_SEQ           (uint8)0x0Cu
/**
@brief API service called with wrong parameter
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_LENGTH        (uint8)0x0Du
/**
@brief API service called with wrong parameter
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_UNIT          (uint8)0x0Eu
/**
@brief API service used without module initialization
@remarks Implements DSPI02130
*/
#define SPI_E_UNINIT              (uint8)0x1Au
/**
@brief Services called in a wrong sequence
@remarks Implements DSPI02130
*/
#define SPI_E_SEQ_PENDING         (uint8)0x2Au
/**
@brief Synchronous transmission service called at wrong time
@remarks Implements DSPI02130
*/
#define SPI_E_SEQ_IN_PROCESS      (uint8)0x3Au
/**
@brief API SPI_Init service called while the SPI driver has already been intialized
@remarks Implements DSPI02130
*/
#define SPI_E_ALREADY_INITIALIZED (uint8)0x4Au

/**
@brief The number of sequences, jobs or channels in the configuration
       exceeds precompile time related sizes:
       SPI_MAX_SEQUENCE, SPI_MAX_JOB or SPI_MAX_CHANNEL.
@remarks Implements DSPI02130
*/
#define SPI_E_CONFIG_OUT_OF_RANGE (uint8)0x5Au

/**
@brief   When a sequence contains uninitialized external buffers.
@remarks Implements DSPI02130
*/
#define SPI_E_PARAM_EB_UNIT       (uint8)0x5Bu

/**
@brief   No job in sequence.
*/
#define SPI_E_SEQ_EMPTY           (uint8)0x5Cu

/**
@brief   No channel in job
*/
#define SPI_E_JOB_EMPTY           (uint8)0x5Du
/**
@brief   If the parameter versioninfo is NULL_PTR
*/
#define SPI_E_VERSION           (uint8)0x5Eu

/**
@brief   API service called with wrong parameter
*/
#define SPI_E_TSBJOB              (uint8)0x5Eu


#define SPI_CHANNEL_FLAG_TX_DEFAULT (uint8) 0x01u
#define SPI_CHANNEL_FLAG_RX_DISCARD (uint8) 0x02u


    /* Service IDs */
/**
@brief API service ID for SPI Init function
@details Parameters used when raising an error/exception
*/
#define SPI_INIT_ID              (uint8) 0x00u
/**
@brief API service ID for SPI DeInit function
@details Parameters used when raising an error/exception
*/
#define SPI_DEINIT_ID            (uint8) 0x01u
/**
@brief API service ID for SPI write IB function
@details Parameters used when raising an error/exception
*/
#define SPI_WRITEIB_ID           (uint8) 0x02u
/**
@brief API service ID for SPI async transmit function
@details Parameters used when raising an error/exception
*/
#define SPI_ASYNCTRANSMIT_ID     (uint8) 0x03u
/**
@brief API service ID for SPI read IB function
@details Parameters used when raising an error/exception
*/
#define SPI_READIB_ID            (uint8) 0x04u
/**
@brief API service ID for SPI setup EB function
@details Parameters used when raising an error/exception
*/
#define SPI_SETUPEB_ID           (uint8) 0x05u
/**
@brief API service ID for SPI get status function
@details Parameters used when raising an error/exception
*/
#define SPI_GETSTATUS_ID         (uint8) 0x06u
/**
@brief API service ID for SPI get job result function
@details Parameters used when raising an error/exception
*/
#define SPI_GETJOBRESULT_ID      (uint8) 0x07u
/**
@brief API service ID for SPI get sequence result function
@details Parameters used when raising an error/exception
*/
#define SPI_GETSEQUENCERESULT_ID (uint8) 0x08u
/**
@brief API service ID for SPI get version info function
@details Parameters used when raising an error/exception
*/
#define SPI_GETVERSIONINFO_ID    (uint8) 0x09u
/**
@brief API service ID for SPI sync transmit function
@details Parameters used when raising an error/exception
*/
#define SPI_SYNCTRANSMIT_ID      (uint8) 0x0Au
/**
@brief API service ID for SPI get hwunit status function
@details Parameters used when raising an error/exception
*/
#define SPI_GETHWUNITSTATUS_ID   (uint8) 0x0Bu
/**
@brief API service ID for SPI cancel function
@details Parameters used when raising an error/exception
*/
#define SPI_CANCEL_ID            (uint8) 0x0Cu
/**
@brief API service ID for SPI set async mode function
@details Parameters used when raising an error/exception
*/
#define SPI_SETASYNCMODE_ID      (uint8) 0x0Du
/**
@brief API service ID for SPI main function
@details Parameters used when raising an error/exception
*/
#define SPI_MAINFUNCTION_DRIVING_ID  (uint8)0x11u
/**
@brief API service ID for SPI set HW Unit async mode
@details Parameters used when raising an error/exception
*/
#define SPI_SETHWUNITASYNCMODE_ID  (uint8)0x80u
/**
@brief API service ID for SPI Set Clock Mode
@details Parameters used when raising an error/exception
*/
#define SPI_SETCLOCKMODE_ID  (uint8)0x81u
/**
@brief API service ID for Timed Serial Bus Mode
@details Parameters used when raising an error/exception
*/
#define SPI_SETTSBMODE_ID  (uint8)0x82u

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/**
@brief   The number of allowed job priority levels (0..3)
         The Priority has to be sint8.
@remarks Implements DSPI05102
*/
#define SPI_JOB_PRIORITY_LEVELS_COUNT    (4)
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
typedef enum
{
    SPI_UNINIT = 0,
    SPI_IDLE,
    SPI_BUSY
} Spi_StatusType;

typedef enum
{
    SPI_JOB_OK = 0,
    SPI_JOB_PENDING,
    SPI_JOB_FAILED
} Spi_JobResultType;

/**
@remarks Implements DSPI02170
*/
typedef enum
{
    SPI_SEQ_OK = 0,
    SPI_SEQ_PENDING,
    SPI_SEQ_FAILED,
    SPI_SEQ_CANCELLED
} Spi_SeqResultType;

/**
@remarks Implements DSPI02130, DSPI02120
*/
typedef enum
{
    IB = 0,
    EB
} Spi_BufferType;

/* #if (LEVEL2 == SPI_LEVEL_DELIVERED) */
/* Specifies the asynchronous mechanism mode for SPI busses handled */
/* asynchronously in LEVEL 2. SPI150: This type is available or not */
/* according to the pre compile time parameter: */
/* SPI_LEVEL_DELIVERED. This is only relevant for LEVEL 2.  */
/** @remarks Implements DSPI02120 */
typedef enum
{
    /* The asynchronous mechanism is ensured by polling, so interrupts
       related to SPI busses handled asynchronously are disabled. */
    SPI_POLLING_MODE = 0,
    /* The asynchronous mechanism is ensured by interrupt, so interrupts
       related to SPI busses handled asynchronously are enabled. */
    SPI_INTERRUPT_MODE
} Spi_AsyncModeType;

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/**
@remarks Implements DSPI02190
*/
typedef enum
{
    SPI_NORMAL = 0,
    SPI_ALTERNATE
}Spi_DualClockMode;
#endif

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*---------------------------------------------------------------------------
                 SPI Driver AUTOSAR Related Type Definitions
-----------------------------------------------------------------------------*/
/** @remarks Implements DSPI02171 */
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    typedef uint8 Spi_DataType;
#else
    typedef uint16 Spi_DataType;
#endif


/** @remarks Implements DSPI02172 */
typedef uint16 Spi_NumberOfDataType;

#if (SPI_ALLOW_BIGSIZE_COLLECTIONS == STD_ON)
/** @remarks Violates SPI166 which requires uint8, for performance reasons */ /* SPI Ver2.1 */
typedef uint32 Spi_ChannelType;
/** @remarks Violates SPI167 which requires uint8, for performance reasons */
typedef uint32 Spi_JobType;
/** @remarks Violates SPI168 which requires uint8, for performance reasons */
typedef uint32 Spi_SequenceType;
#else
/** @remarks Implements DSPI02173 */
typedef uint8 Spi_ChannelType;
/** @remarks Implements DSPI02174 */
typedef uint8 Spi_JobType;
/** @remarks Implements DSPI02175 */
typedef uint8 Spi_SequenceType;
#endif

/** @remarks Implements DSPI02176 */
typedef uint8 Spi_HWUnitType;

typedef uint8 Spi_ExternalDeviceType;
typedef void (Spi_NotifyType) (void);

/** @brief The structure keeps a sequence configuration */
/** @remarks Implements DSPI02100 */
typedef struct
{
    /** @brief Number of jobs in the sequence */
    VAR(Spi_JobType, SPI_VAR) NumJobs;
    /** @brief Job index list */
    P2CONST(Spi_JobType, AUTOMATIC, SPI_VAR) JobIndexList;
    /** @brief Job notification handler */
    P2FUNC(Spi_NotifyType, SPI_VAR, EndNotification);
    /** @brief Boolean indicating if the Sequence is interruptible or not */
    VAR(uint8, SPI_VAR) Interruptible;
} Spi_SequenceConfig;

/** @brief Internal structure used to manage the sequence state */
typedef struct
{
    /** @brief Seq Result */
    VAR(Spi_SeqResultType, SPI_VAR) Result;
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
    /** @brief pointer to the configuration */
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) Sequence;

    /** @brief position in JobIndexList to the job in transmission of an async sequence
     */
    P2CONST(Spi_JobType, AUTOMATIC, SPI_VAR) CurrentJobIndexPointer;

    /** @brief Number of jobs in a pending async sequence, not yet transmitted */
    VAR(Spi_JobType, SPI_VAR) RemainingJobs;
#endif
} Spi_SequenceState;

/** @brief Internal structure used to manage the job state */
typedef struct
{
    /** @brief Job Result */
    VAR(Spi_JobResultType, SPI_VAR) Result;

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
    /** @brief Pointer to the state information of the async sequence
       linked to the job.
       This field is used also for locking jobs in pending async transmissions.
    */
    P2VAR(Spi_SequenceState, AUTOMATIC, SPI_VAR) AsyncCrtSequenceState;

    /** @brief pointer to the next async job planned for transmission */
    VAR(Spi_JobType, SPI_VAR) AsyncNextJob;
#endif
} Spi_JobState;

/** @brief The structure keeps a job configuration */
/** @remarks Implements DSPI02110, DSPI05200 */
typedef struct
{
    /** @brief Number of channels in the job */
    VAR(Spi_ChannelType, SPI_VAR) NumChannels;
    /** @brief Channel index list */
    P2CONST(Spi_ChannelType, AUTOMATIC, SPI_VAR) ChannelIndexList;
    /** @brief Job notification */
    P2FUNC(Spi_NotifyType, SPI_VAR, EndNotification);
    /** @brief Start Job notification */
    P2FUNC(Spi_NotifyType, SPI_VAR, StartNotification);
    /** @brief Priority */
    VAR(sint8, SPI_VAR) Priority;
    /** @brief Implementation specific field referencing the channel
        internal state */
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) JobState;
    /** @brief HWUnit */
    VAR(Spi_HWUnitType, SPI_VAR) HWUnit;
    /** @brief HW Unit offset */
    VAR(uint32, SPI_VAR) HWoffset;
    /** @brief ExternalDevice */
    VAR(Spi_ExternalDeviceType, SPI_VAR) ExternalDevice;
    /** @brief Implementation specific field: cached LLD device attributes */
    VAR(Spi_LLD_DeviceAttributesConfig, SPI_VAR) ExternalDeviceAttrs;
} Spi_JobConfig;

/** @brief RX/TX Spi buffer adresses structure */
typedef struct
{
    /** @brief Transmit buffer pointer */
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) BufferTX;
    /** @brief Receive buffer pointer */
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) BufferRX;
} Spi_BufferDescriptor;

/** @brief Internal structure used to manage the channel state */
typedef struct
{
    /** @brief Default Transmit Enabled */
    VAR(uint8, SPI_VAR) Flags;
    /** @brief Actual Transfer size for EB */
    VAR(Spi_NumberOfDataType, SPI_VAR) Length;
} Spi_ChannelState;

/** @brief The structure keeps a channel configuration */
typedef struct
{
    /** @brief Buffer Type IB/EB */
    VAR(Spi_BufferType, SPI_VAR) BufferType;
    /** @brief Default Transmit Value */
    VAR(Spi_DataType, SPI_VAR) DefaultTransmitValue;
    /** @brief Data length */
    VAR(Spi_NumberOfDataType, SPI_VAR) Length;
    /** @brief Buffer Descriptor */
    P2CONST(Spi_BufferDescriptor, AUTOMATIC, SPI_VAR) BufferDescriptor;
    /** @brief Implementation specific field referencing the channel
        internal state */
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) ChannelState;
} Spi_ChannelConfig;

/*---------------------------------------------------------------------------
             SPI Driver Low Level Implementation Specific Type Definitions
-----------------------------------------------------------------------------*/

/** @brief This structure holds the HWUnit configuration parameters */
typedef struct
{
    /** @brief DSPI HWunit physical offset on SOC */
    VAR(uint8, SPI_VAR) Offset;
    /** @brief indicates if the HW unit is configured as Sync or Async */
    VAR(uint32, SPI_VAR) IsSync;
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (SPI_DMA_USED == STD_ON)
    /** @brief boolean flag indicating if DMA will be used or not for this DSPI unit */
    VAR(uint16, SPI_VAR) UseDma;
    /** @brief Master TX DMA channel - enabled by the DSPI TX source */
    VAR(uint8, SPI_VAR) TxDmaChannel;
    /** @brief Auxiliary TX DMA channel - triggered by the master TX Dma */
    VAR(uint8, SPI_VAR) TxDmaChannelAux;
    /** @brief RX DMA channel - enabled by the DSPI RX source */
    VAR(uint8, SPI_VAR) RxDmaChannel;
#endif
#endif
} Spi_HWUnitConfig;

/*---------------------------------------------------------------------------
              SPI Driver Configuration Main Structure
-----------------------------------------------------------------------------*/
/** @brief The structure keeps an Spi configuration */
/** @remarks Implements DSPI05102 */
typedef struct
{
    /** @brief Number of external devices defined in the configuration */
    VAR(uint16, SPI_VAR) Spi_Max_ExternalDevice;
    /** @brief Number of channels defined in the configuration */
    VAR(Spi_ChannelType, SPI_VAR) Spi_Max_Channel;
    /** @brief Number of jobs defined in the configuration */
    VAR(Spi_JobType, SPI_VAR) Spi_Max_Job;
    /** @brief Number of sequences defined in the configuration */
    VAR(Spi_SequenceType, SPI_VAR) Spi_Max_Sequence;
    /** @brief Array of channels defined in the configuration */
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) ChannelConfig;
    /** @brief Array of jobs defined in the configuration */
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) JobConfig;
    /** @brief Array of sequences defined in the configuration */
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) SequenceConfig;
    /** @brief Channel & DSPI HW unit attributes */
    P2CONST(Spi_AttributesConfig, AUTOMATIC, SPI_CONST) AttributesConfig;
    /** @brief Array of LLD DSPI device instances */
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
} Spi_ConfigType;

#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
typedef struct
{
    /**@brief JobId of the configured TSB job*/
    VAR(Spi_JobType, SPI_VAR) Spi_TSB_Job;
    /** @brief This structure holds the TSB mode selection on HWUnits */
    VAR(Spi_LLD_TSBAttributesConfig, SPI_VAR) ExternalDeviceTSBAttrs;
} Spi_TSBConfig;
#endif
#endif
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define SPI_START_SEC_VAR_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

extern P2CONST(Spi_ConfigType, SPI_VAR, SPI_APPL_CONST) SpiConfigPtr;

/**
@brief Spi State
*/
extern VAR(Spi_JobState, AUTOMATIC) SpiJobState[SPI_MAX_JOB];
extern VAR(Spi_ChannelState, AUTOMATIC) SpiChannelState[SPI_MAX_CHANNEL];

#define SPI_STOP_SEC_VAR_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#define SPI_START_SEC_CONST_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
extern CONST(Spi_TSBConfig, SPI_CONST) SpiJobTSBConfig[];
#endif
#endif

#define SPI_STOP_SEC_CONST_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#if (SPI_CONFIG_VARIANT == SPI_VARIANT_PRECOMPILE)

#define SPI_START_SEC_CONST_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief Configuration structures
*/
SPI_CFG_EXTERN_DECLARATIONS

#define SPI_STOP_SEC_CONST_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#endif /*(SPI_CONFIG_VARIANT == SPI_VARIANT_PRECOMPILE)*/

#if (SPI_CONFIG_VARIANT == SPI_VARIANT_LINKTIME)

#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief Configuration structures
*/
SPI_CFG_EXTERN_DECLARATIONS

#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#endif /*(SPI_CONFIG_VARIANT == SPI_VARIANT_LINKTIME)*/

#if (SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)

#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief Configuration structures
*/
SPI_CFG_EXTERN_DECLARATIONS

#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#endif /*(SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)*/


#define SPI_START_SEC_CODE
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/**
@brief   This function returns the version information for the SPI driver.
@details This function returns the version information for the SPI driver.

@param[in,out]    VersionInfo      Specifies the pointer to the configuration

@remarks Implements DSPI02310, DSPI04091
*/
#if (SPI_VERSION_INFO_API == STD_ON)
FUNC (void, SPI_CODE) Spi_GetVersionInfo (
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_VAR) VersionInfo);
#endif

/**
@brief   This function initializes the SPI driver.
@details This function initializes the SPI driver using the
         pre-established configurations

@param[in]     ConfigPtr      Specifies the pointer to the configuration set

@remarks Implements DSPI02301, DSPI06000, DSPI04091, DSPI02130, DSPI04232
*/
FUNC (void, SPI_CODE) Spi_Init(
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_DATA) ConfigPtr);

/**
@brief   This function de-initializes the SPI driver.
@details This function de-initializes the SPI driver using the
         pre-established configurations

@return Std_ReturnType
        - E_OK - de-initialisation command has been accepted
        - E_NOT_OK - de-initialisation command has not been accepted



@remarks Implements DSPI02302, DSPI06000, DSPI04091, DSPI02180

*/
FUNC (Std_ReturnType, SPI_CODE) Spi_DeInit(void);

/**
@brief   This function writes the given data into the buffer of a specific channel.
@details This function writes the given data into the buffer of a specific channel.

@param[in]      Channel             Channel ID
@param[in]      DataBufferPtr       Pointer to source data buffer

@return Std_ReturnType
        - E_OK - Command has been accepted
        - E_NOT_OK - Command has not been accepted

@remarks Implements DSPI02303, DSPI06000, DSPI04091, DSPI02130, DSPI02120
*/
#if ((USAGE0 == SPI_CHANNEL_BUFFERS_ALLOWED) || (USAGE2 == SPI_CHANNEL_BUFFERS_ALLOWED ))
FUNC (Std_ReturnType, SPI_CODE) Spi_WriteIB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_CONST) DataBufferPtr);
/**
@brief   This function reads the data from the buffer of a specific channel
         and puts at the specified memory location.
@details This function reads the data from the buffer of a specific channel
         and puts at the specified memory location.

@param[in]      Channel             Channel ID
@param[in,out]  DataBufferPtr       Pointer to the memory location that will
                                    be written with the data in the internal
                                    buffer

@return Std_ReturnType
        - E_OK - read command has been accepted
        - E_NOT_OK - read command has not been accepted

@remarks Implements DSPI02305, DSPI06000, DSPI04091, DSPI02180, DSPI02130, DSPI02120
*/
FUNC (Std_ReturnType, SPI_CODE) Spi_ReadIB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DataBufferPtr);
#endif

/**
@brief   This function triggers the asynchronous transmission for the given sequence.
@details This function triggers the asynchronous transmission for the given sequence.

@param[in]      Sequence            Sequence ID

@return Std_ReturnType
        - E_OK - Transmission command has been accepted
        - E_NOT_OK - Transmission command has not been accepted

@remarks Implements DSPI02304, DSPI06000, DSPI04091, DSPI05100
@remarks Implements DSPI04096, DSPI02200, DSPI04332, DSPI04333
@remarks Implements DSPI04111, DSPI04125, DSPI04237, DSPI04094, DSPI04097
*/
#if ((LEVEL2 == SPI_LEVEL_DELIVERED) || (LEVEL1 == SPI_LEVEL_DELIVERED))
FUNC (Std_ReturnType, SPI_CODE) Spi_AsyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence);
#endif

/**
@brief   This function setup an external buffer to be used by a specific channel.
@details This function setup an external buffer to be used by a specific channel.

@param[in]      Channel             Channel ID
@param[in]      SrcDataBufferPtr    Pointer to the memory location that will hold
                                    the transmitted data
@param[in]      Length              Length of the data in the external buffer
@param[out]     DesDataBufferPtr    Pointer to the memory location that will hold
                                    the received data

@return Std_ReturnType
        - E_OK - Setup command has been accepted
        - E_NOT_OK - Setup command has not been accepted

@remarks Implements DSPI02306, DSPI06000, DSPI04091, DSPI02180, DSPI02130, DSPI02120
*/
#if ( ( USAGE1 == SPI_CHANNEL_BUFFERS_ALLOWED) || \
        ( USAGE2 == SPI_CHANNEL_BUFFERS_ALLOWED)  )
FUNC (Std_ReturnType, SPI_CODE) Spi_SetupEB(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_CONST) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) DesDataBufferPtr,
    VAR(Spi_NumberOfDataType, AUTOMATIC) Length);
#endif

/**
@brief   This function returns the status of the SPI driver.
@details This function returns the status of the SPI driver.

@return Spi_StatusType
        - SPI_UNINIT - The driver is un-initialized
        - SPI_IDLE - The driver has no pending transfers
        - SPI_BUSY - The driver is busy

@remarks Implements DSPI02307, DSPI06000, DSPI04091, DSPI04151, DSPI04152, DSPI04125, DSPI04237
*/
FUNC (Spi_StatusType, SPI_CODE) Spi_GetStatus(void);

/**
@brief   This function is used to request the status of a specific job.
@details This function is used to request the status of a specific job.

@param[in]      Job                 Job ID

@return Spi_JobResultType
        - SPI_JOB_OK - The job ended successfully
        - SPI_JOB_PENDING - The job is pending
        - SPI_JOB_FAILED - The job has failed

@pre If SPI Handler/Driver has not been initialized before this service
     is called, the return value is undefined.

@remarks Implements DSPI02308, DSPI06000, DSPI04091, DSPI04191, DSPI02160, DSPI04235, DSPI02180
*/
FUNC (Spi_JobResultType, SPI_CODE) Spi_GetJobResult(
    VAR(Spi_JobType, AUTOMATIC) Job);

/**
@brief   This function is used to request the status of a specific sequence.
@details This function is used to request the status of a specific sequence.

@param[in]      Sequence            Sequence ID

@return Spi_SeqResultType
        - SPI_SEQ_OK - The sequence ended successfully
        - SPI_SEQ_PENDING - The sequence is pending
        - SPI_SEQ_FAILED - The sequence has failed

@pre  If SPI Handler/Driver has not been initialized before this service
      is called, the return value is undefined.

@remarks Implements DSPI02309, DSPI06000, DSPI04091, DSPI05100, DSPI04212
*/
FUNC (Spi_SeqResultType, SPI_CODE) Spi_GetSequenceResult(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence);

/**
@brief   This function is used for synchronous transmission of a given sequence.
@details This function is used for synchronous transmission of a given sequence.

@param[in]      Sequence            Sequence ID

@return Std_ReturnType
        - E_OK - Transmission command has been completed successfully
        - E_NOT_OK - Transmission command has not been accepted

@remarks Implements DSPI02311, DSPI04236, DSPI06000, DSPI04091, DSPI05100
 @remarks Implements DSPI02180, DSPI04235, DSPI04234, DSPI04233, DSPI04232
 @remarks Implements DSPI02200, DSPI04125, DSPI04237, DSPI04231, DSPI02110
 @remarks Implements DSPI01451
*/
#if ((LEVEL2 == SPI_LEVEL_DELIVERED) || (LEVEL0 == SPI_LEVEL_DELIVERED))
FUNC (Std_ReturnType, SPI_CODE) Spi_SyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence);
#endif

/**
@brief   This function is used to request the status of a specific SPI peripheral unit.
@details This function is used to request the status of a specific SPI peripheral unit.

@param[in]      HWUnit              The HW peripheral for which we need the status

@return Spi_StatusType
        - SPI_UNINIT - The peripheral is un-initialized
        - SPI_IDLE - The peripheral is in idle state
        - SPI_BUSY - The peripheral is busy

@pre  If SPI Handler/Driver has not been initialized before this service
      is called, the return value is undefined

@remarks Implements DSPI02312, DSPI06000, DSPI04091, DSPI02150, DSPI04251
@remarks Implements DSPI02130, DSPI02180
*/
#if (SPI_HW_STATUS_API == STD_ON)
FUNC (Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit);
#endif

/**
@brief   This function is used to request the cancelation of the given sequence.
@details This function is used to request the cancelation of the given sequence.

@param[in]      Sequence            Sequence ID

@pre The SPI Handler/Driver is not responsible on external devices damages or
     undefined state due to cancelling a sequence transmission.

@remarks Implements DSPI02313, DSPI06000, DSPI04091, DSPI05100, DSPI04271, DSPI02180
*/
#if (SPI_CANCEL_API == STD_ON)
FUNC (void, SPI_CODE) Spi_Cancel(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence);
#endif

/**
@brief   This function specifies the asynchronous mode for all SPI busses
         handled asynchronously.
@details This function specifies the asynchronous mode for all SPI busses
         handled asynchronously. If a HWUnit operation mode was
         configured in a specific mode using Spi_SetHWUnitAsyncMode(), its
         operation mode will be reset to the new requested mode.

@param[in]      AsyncMode    This parameter specifies the asynchronous
                             operating mode (SPI_POLLING_MODE or
                             SPI_INTERRUPT_MODE)

@return Std_ReturnType
        - E_OK - The command ended successfully
        - E_NOT_OK - The command has failed

@remarks Implements DSPI02314, DSPI06000, DSPI04091, DSPI02180
@remarks Implements DSPI02120
*/
#if (SPI_LEVEL_DELIVERED == LEVEL2)
FUNC (Std_ReturnType, SPI_CODE) Spi_SetAsyncMode(
    VAR(Spi_AsyncModeType, AUTOMATIC) AsyncMode);
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
FUNC (Std_ReturnType, SPI_CODE) Spi_SetHWUnitAsyncMode(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
    VAR(Spi_AsyncModeType, AUTOMATIC) AsyncMode);
#endif /* (SPI_LEVEL_DELIVERED == LEVEL2) && (SPI_HWUNIT_ASYNC_MODE == STD_ON) */

/**
@brief   This function shall asynchronously poll SPI interrupts and call
         ISR if appropriate.
@details This function shall asynchronously poll SPI interrupts and call
         ISR if appropriate.
@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@remarks Implements DSPI02180
*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_MainFunction_Driving(void);
#endif

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/**
@brief   This function shall set different MCU clock configuration .
@details This function shall set different MCU clock configuration .

@param[in]    ClockMode   Clock mode to be set.

@return Std_ReturnType
        - E_OK - The driver is initialised and in an IDLE state. The clock
                mode can be changed.
        - E_NOT_OK - The driver is NOT initialised OR is NOT in an IDLE state.
                    The clock mode can NOT be changed.

@pre  Pre-compile parameter SPI_DUAL_CLOCK_MODE shall be STD_ON.

@remarks Implements DSPI04331, DSPI04332, DSPI04333, DSPI02335, DSPI06000, DSPI04091, DSPI04091
*/
FUNC (Std_ReturnType, SPI_CODE) Spi_SetClockMode(
    VAR(Spi_DualClockMode,AUTOMATIC) ClockMode);
#endif


#if ((LEVEL2 == SPI_LEVEL_DELIVERED) || (LEVEL1 == SPI_LEVEL_DELIVERED))
/**
@brief   End Job transmission notification handler declaration.
@details The function (global) is implemented in Spi.c (Autosar Driver Layer).

@param[in]    pJobConfig   The just transmited job pointer.
*/
extern FUNC (void, SPI_CODE) Spi_JobTransferFinished(
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig);
#endif


#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
/**
@brief   This function shall to enable user to access the Micro Second Bus functionality .
@details A non-Autosar API to support the configuartion of the TSB
to enable user to access the Micro Second Bus functionality

@param[in]    Spi_JobType   Specifies the job to be confgiured in TSB mode

@return Std_ReturnType
        - E_OK - The driver is initialised . The TSB  mode can be configured.
        - E_NOT_OK - The driver is NOT initialised

@pre  Pre-compile parameter SPI_TSB_MODE shall be STD_ON.

@remarks Implements DSPI08000
*/
FUNC (Std_ReturnType, SPI_CODE) Spi_TSBStart(
     VAR(Spi_JobType, AUTOMATIC) TSBJob);

 /**
@brief   This function shall to stop the transfer in TSB mode .
@details A non-Autosar API to support the configuartion of the TSB.
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
     VAR(Spi_JobType, AUTOMATIC) TSBJob);

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
     VAR(uint32, SPI_VAR) ASDR_Data);

#endif /*(SPI_TSB_MODE == STD_ON)*/
#endif /*TSB_MODE_SUPPORTED*/

#define SPI_STOP_SEC_CODE
/**
@file Spi.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_h_REF_2 & @ref Spi_h_REF_1
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

#endif /* SPI_H */

