/**
    @file    Dspi_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Spi - DSPI LLD header file.
    @details DSPI peripheral LLD header file.

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

@section Dspi_LLD_h_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
and comments before "#include". AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Dspi_LLD_h_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
@section Dspi_LLD_h_REF_3
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/

#ifndef DSPI_LLD_H
#define DSPI_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
/** @remarks Implements DSPI02180 */
#define SPI_AR_MAJOR_VERSION_LLD    3
#define SPI_AR_MINOR_VERSION_LLD    0
#define SPI_AR_PATCH_VERSION_LLD    0
#define SPI_SW_MAJOR_VERSION_LLD    2
#define SPI_SW_MINOR_VERSION_LLD    0
#define SPI_SW_PATCH_VERSION_LLD    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SPI configuration header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_LLD != SPI_AR_MAJOR_VERSION_CFG) || \
       (SPI_AR_MINOR_VERSION_LLD != SPI_AR_MINOR_VERSION_CFG) || \
       (SPI_AR_PATCH_VERSION_LLD != SPI_AR_PATCH_VERSION_CFG))
  #error "AutoSar Version Numbers of Dspi_LLD.h and Spi_Cfg.h are different"
  #endif
#endif

/* Check if source file and SPI configuration header file are of the same software version */
#if ((SPI_SW_MAJOR_VERSION_LLD != SPI_SW_MAJOR_VERSION_CFG) || \
     (SPI_SW_MINOR_VERSION_LLD != SPI_SW_MINOR_VERSION_CFG))
#error "Software Version Numbers of Dspi_LLD.h and Spi_Cfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/**
@brief  Map HWUnit to DSPI device structure.
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
- See @ref  Dspi_LLD_h_REF_3
*/
/*lint -save -e961 */
#define DSPI_HWUNIT2DSPI(HWUnit)    (&DspiDeviceState[(HWUnit)])
/*lint -restore */

#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/**
@brief   This Macro shall set different MCU clock mode .
@details This Macro shall set different MCU clock mode .

@param[in]    ClockMode   Clock mode to be set.

@pre  Pre-compile parameter SPI_DUAL_CLOCK_MODE shall be STD_ON.

@remarks Implements DSPI03510
*/
/*================================================================================================*/
#define DSPI_SET_CLOCK_MODE(ClockMode)  (Dspi_ClockMode = ClockMode)

#endif /* #if (SPI_DUAL_CLOCK_MODE == STD_ON) */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
/** @brief Internal structure keeping a set of cached channel attributes
           used by the optimized implementation of Spi_SyncTransmit() for
           the sequences having only one job. */
typedef struct
{
    /** @brief Cached value of the CTAR register */
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
    VAR(uint32, SPI_VAR) CTAR[2];
#else
    VAR(uint32, SPI_VAR) CTAR;
#endif
    /** @brief Cached pointer to the buffer descriptor */
    P2CONST(Spi_BufferDescriptor, AUTOMATIC, SPI_CONST) BufferDescriptor;
    /** @brief Cached pointer to the channel state */
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) State;
    /** @brief Cached default transmit value */
    VAR(Spi_DataType, AUTOMATIC) DefaultTransmitValue;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    /**< @brief Channel attributes for DataType width. */
    VAR(uint8, SPI_VAR) DataWidth;
#endif
} Spi_ChannelCacheAttrs;

/** @brief Internal structure keeping a set of cached sequences attributes
           used by the optimized implementation of Spi_SyncTransmit() for
           the sequences having only one job. */
typedef struct
{
    /** @brief Number of channels in sequence */
    VAR(Spi_ChannelType, AUTOMATIC) NumChannels;
    /** @brief Cached pointer to the sequence job state */
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) JobState;
    /** @brief Cached pointer to the sequence DSPI state */
    P2VAR(Spi_StatusType, AUTOMATIC, SPI_VAR) JobDspiStatus;
    /** @brief Table of channel cached attributes */
    P2VAR(Spi_ChannelCacheAttrs, AUTOMATIC, SPI_VAR) pChannels;
    /** @brief Cached value of the DSPI HW Unit offset */
    VAR(uint32, SPI_VAR) JobHWOffset;
    /** @brief Cached value of the DSPI HW Unit memory mapped
               registers base address */
    VAR(uint32, SPI_VAR) DspiBaseAddress;
    /** @brief Cached value of CMD field of the SPI dataframes */
    VAR(uint32, SPI_VAR) JobCMD;
} Spi_SequenceCacheAttrs;
#endif /* (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON) */

/** @brief This structure holds are runtime configuration parameters for Spi handler */
typedef struct
{
    /** @brief Reference to the corresponding HWUnit config instance */
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (SPI_DMA_USED == STD_ON)
    VAR(uint32, SPI_VAR) TxDmaBuffer;
    /** @brief internal buffer containing the command|data frame information
       for the last dtaframe in job. */
    VAR(uint32, SPI_VAR) TxDmaBufferLast;
    /** @brief address of the default master TX DMA descriptor stored in memory */
    P2VAR(uint32, AUTOMATIC, SPI_VAR) TxDmaTcdDefault;
    /** @brief address of the TX DMA descriptor to be used for transfering the last
       job dataframe. */
    P2VAR(uint32, AUTOMATIC, SPI_VAR) TxDmaTcdLast;
    /** @brief address of the master TX MMIO DMA descriptor */
    P2VAR(uint32, AUTOMATIC, SPI_VAR) TxDmaTcd;
    /** @brief address of the master RX MMIO DMA descriptor */
    P2VAR(uint32, AUTOMATIC, SPI_VAR) RxDmaTcd;
    /** @brief cache of the e_link configuration part into the iteration field. */
    VAR(uint16, SPI_VAR) MinorELink;
#endif
    VAR(uint32, SPI_VAR) ExternalDeviceCTAR;
    /** @brief pointer to the Tx buffer of the channel currently in transmission */
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) CurrentTxBuffer;
    /** @brief pointer to the Rx buffer of the channel currently in transmission */
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) CurrentRxBuffer;
    /** @brief the frame command value to be used for the channel in transmission */
    VAR(uint32, SPI_VAR) CurrentCmd;
    /** @brief position in ChannelIndexList to the channel in transmission */
    P2CONST(Spi_ChannelType, AUTOMATIC, SPI_VAR) CurrentChannelIndexPointer;
    /** @brief Number of channels in a pending async job, not yet transmitted */
    VAR(Spi_ChannelType, SPI_VAR) RemainingChannels;
    /** @brief Number of frames in a pending channel, not yet transmitted */
    VAR(Spi_NumberOfDataType, SPI_VAR) RemainingData;
    /** @brief Number of sent frames, which must be read back in the next ISR call */
    VAR(Spi_NumberOfDataType, SPI_VAR) SentFrames;
    /** @brief Reference to the current job */
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_VAR) CurrentJob;
    /** @brief indicates if this is the last chunk of data in the job */
    VAR(sint32, SPI_VAR) IsEndOfJob;
#endif
    /** @brief memory mapped registers base address */
    VAR(uint32, SPI_VAR) DspiBaseAddress;
    /** @brief DSPI PUSHR register address */
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiPUSHRAddress;
    /** @brief DSPI POPR register address */
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiPOPRAddress;
    /** @brief DSPI Status register address */
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiSRAddress;
    /** @brief DSPI CTAR register address */
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiCTARAddress;
    /** @brief Asynchronous operating mode of the DSPI unit */
    VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode;
    /** @brief Pointer to the Autosar HW unit SPI state */
    P2VAR(Spi_StatusType, AUTOMATIC, SPI_VAR) pStatus;
} Spi_LLD_DeviceState;


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_h_REF_1 & @ref Dspi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
/**
@brief Pointer table to the cached information structure, for one job sequences,
       or NULL, for unoptimized sequences.
*/
extern P2VAR(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR)
                DspiOneJobSeqsOptimized[SPI_MAX_SEQUENCE];
#endif


/** @brief Keep the HWUnit internal fields */
extern VAR(Spi_LLD_DeviceState, SPI_VAR) DspiDeviceState[SPI_MAX_HWUNIT];



#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/**
@brief Holds the mode of the Dual Clock.
*/
extern VAR(Spi_DualClockMode, AUTOMATIC) Dspi_ClockMode;
#endif

#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_h_REF_1 & @ref Dspi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#define SPI_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_h_REF_1 & @ref Dspi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

FUNC (void, SPI_CODE) Spi_LLD_Init(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
    VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode,
    P2VAR(Spi_StatusType, AUTOMATIC, SPI_VAR) pStatus);

FUNC (void, SPI_CODE) Spi_LLD_DeInit(VAR(Spi_HWUnitType, AUTOMATIC) HWUnit);

#if (((SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0)) && \
    (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON))
FUNC (void, SPI_CODE) Spi_LLD_PrepareCacheInformation(void);
#endif

#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
FUNC (Std_ReturnType, SPI_CODE) Spi_LLD_SyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence);
#endif

#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
FUNC (Std_ReturnType, SPI_CODE) Spi_LLD_SyncTransmit_Fast(
    P2CONST(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR) pSequence);
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_JobTransfer(
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_IrqConfig(
        VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
        VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_IrqPoll(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_IsrFifoRx(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
FUNC (void, SPI_CODE) Spi_LLD_IsrDmaRx(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif
#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
FUNC (void, SPI_CODE) Spi_LLD_SetTSBMode(
      VAR(Spi_JobType, AUTOMATIC) TSBJob);

FUNC (void, SPI_CODE) Spi_LLD_StopTSBMode(
      VAR(Spi_JobType, AUTOMATIC) TSBJob);

FUNC (void, SPI_CODE) Spi_LLD_TSB_ASDR_DataUpdate(
      VAR(Spi_JobType, AUTOMATIC) TSBJob,
      VAR(uint32, SPI_VAR) ASDR_Data);
#endif /*(SPI_TSB_MODE == STD_ON)*/
#endif /*TSB_MODE_SUPPORTED*/

#define SPI_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_h_REF_1 & @ref Dspi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

#endif /* DSPI_LLD_H */

