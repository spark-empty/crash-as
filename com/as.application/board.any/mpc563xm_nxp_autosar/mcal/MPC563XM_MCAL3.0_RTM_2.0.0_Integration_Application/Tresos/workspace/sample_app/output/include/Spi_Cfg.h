/**
    @file    Spi_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Spi - Spi configuration header file.
    @details This file is the header containing all the necessary information for SPI
             module configuration(s).

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

@section Spi_Cfg_h_REF_1
Violates MISRA 2004 Advisory Rule Rule 19.1, only preprocessor statements
and comments before '#include'. AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Spi_Cfg_h_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*/

#ifndef SPI_CFG_H
#define SPI_CFG_H

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
/**
@brief Parameters that shall be published within the configuration header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define SPI_MODULE_ID_CFG           83
#define SPI_VENDOR_ID_CFG           43
#define SPI_AR_MAJOR_VERSION_CFG    3
#define SPI_AR_MINOR_VERSION_CFG    0
#define SPI_AR_PATCH_VERSION_CFG    0
#define SPI_SW_MAJOR_VERSION_CFG    2
#define SPI_SW_MINOR_VERSION_CFG    0
#define SPI_SW_PATCH_VERSION_CFG    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/



/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/



/**
@brief Switches the Development Error functionality STD_ON or STD_OFF.
@remarks Implements DSPI01431, DSPI01430
*/
#define SPI_DEV_ERROR_DETECT           (STD_ON)

/**
@brief Switches the Version Information API functionality STD_ON or STD_OFF.
@remarks Implements DSPI01413
*/
#define SPI_VERSION_INFO_API           (STD_ON)

/**
@brief Switches the Interruptible Sequences handling functionality STD_ON or
   STD_OFF. (see chapter 7.2.4) - Note: This parameter depends on
   SPI_LEVEL_DELIVERED value. It is only used for SPI_LEVEL_DELIVERED
   configured to 1 or 2.

@remarks Implements DSPI01421
*/
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED  (STD_OFF)

/**
@brief Switches the Spi_GetHWUnitStatus function STD_ON or STD_OFF.
   (see chapters 8.2.10 and 8.3.12).
@remarks Implements DSPI01412
*/
#define SPI_HW_STATUS_API          (STD_ON)

/**
@brief Switches the Spi_Cancel function STD_ON or STD_OFF. (see chapter 8.3.13)

@remarks Implements DSPI01420
*/
#define SPI_CANCEL_API             (STD_ON)

/**
@brief Only Internal Buffers are allowed in Handler/Driver.
*/
#define USAGE0                          0x00u

/**
@brief Only External Buffers are allowed in Handler/Driver.
*/
#define USAGE1                          0x01u

/**
@brief Both Buffer types are allowd in Handler/Driver.
*/
#define USAGE2                          0x02u
/* Derive the CTAR used */
#define SPI_CTAR_USED                   3u

/**
@brief Selects the SPI Handler/Driver Channel Buffers usage allowed and
   delivered. (see chapter 7.2.1)

@remarks Implements DSPI01411
*/
#define SPI_CHANNEL_BUFFERS_ALLOWED    (USAGE0)

/**
@brief The LEVEL 0 Simple Synchronous SPI Handler/Driver functionalities are selected.
*/
#define LEVEL0                          0x00u

/**
@brief The LEVEL 1 Basic Asynchronous SPI Handler/Driver functionalities are selected.
*/
#define LEVEL1                          0x01u

/**
@brief  The LEVEL 2 Enhanced SPI Handler/Driver functionalities are selected.
*/
#define LEVEL2                          0x02u

/**
@brief Selects the SPI Handler/Driver level of scalable functionality that is
   available and delivered. (see chapter 7.1)

@remarks Implements DSPI01410
*/
#define SPI_LEVEL_DELIVERED            (LEVEL2)

/**
@brief Defines the maximum number of supported channels for all the driver configurations

@remarks Implements DSPI01910
*/
#define SpiChannel_0    ((Spi_ChannelType)0)
#define SPI_MAX_CHANNEL  ((Spi_ChannelType)1)

/**
@brief Defines the maximum number of supported jobs for all the driver configurations

@remarks Implements DSPI01920
*/
#define SpiJob_0   ((Spi_JobType)0)
#define SPI_MAX_JOB     ((Spi_JobType)1)

/**
@brief Defines the maximum number of supported sequences for all the driver configurations

@remarks Implements DSPI01930
*/
#define SpiSequence_0   ((Spi_SequenceType)0)
#define SPI_MAX_SEQUENCE  ((Spi_SequenceType)1)


/**
@brief Defines the peripherals used throughout the configuration(s)
@remarks Implements DSPI01480, DSPI01100
*/
#define CSIB0  (uint8)0u
#define SPI_MAX_HWUNIT   1u

/**
@brief Physical HWUnits definition - as from resource manager
*/
#define DSPI_1_HWUNIT   CSIB0

/**
@brief Physical HWUnits enabled/disabled
*/
#define DSPI_0_ENABLED  (STD_OFF)
#define DSPI_1_ENABLED  (STD_ON)
#define DSPI_2_ENABLED  (STD_OFF)
/**
@brief DSPI offset
*/

#define DSPI_1_OFFSET  1u

/**
@brief SPI FIFO size
*/
#define SPI_FIFO_SIZE   (uint8)4u

/**
@brief Defines the external devices the driver will use

@remarks Implements DSPI01760
*/
#define SpiExternalDevice_0  (Spi_ExternalDeviceType)0u

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief Define values for Autosar configuration variants
*/
#define SPI_VARIANT_PRECOMPILE  (0)
#define SPI_VARIANT_POSTBUILD   (1)
#define SPI_VARIANT_LINKTIME    (2)




/**
@brief Defines the use of Post-Build(PB) support
@remarks Implements DSPI01000, DSPI01200
*/
#define SPI_CONFIG_VARIANT      SPI_VARIANT_POSTBUILD
#define SPI_CFG_EXTERN_DECLARATIONS \
extern CONST(Spi_ConfigType, SPI_CONST) SpiDriver_0;


/**
@brief Defines if transfers are made using DMA or FIFO.
*/
#define SPI_DMA_USED    (STD_OFF)

/**
@brief Defines if Spi driver optimization for sequences having only one job is activated or not.
@remarks If activated, additional RAM memory is required for internal data caching.
*/
#define SPI_OPTIMIZE_ONE_JOB_SEQUENCES (STD_OFF)

/**
@brief Number of CPU clock cycles consumed by Spi_SyncTransmit() during the wait on TX/RX transmission
@remarks This value is set to the minimum measure retrieved for GHS, DIAB and CW compilers,
         with all optimizations activated
*/
#define SPI_WAIT_LOOP_TICKS       23u

/**
@brief Defines the "Number of Loops" timeout used by Spi_SyncTransmit function during the wait on TX/RX transmission
*/
#define SPI_TIMEOUT_COUNTER       (uint32)((3000000u) / SPI_WAIT_LOOP_TICKS)



/*==================================================================================================
                                             Non AUTOSAR DEFINES
==================================================================================================*/
/**
@brief Allow simultaneous calls to Spi_SyncTransmit() for different threads.
       Two concurrent calls to Spi_SyncTransmit() will be allowed only if the related sequences
       do not share HW units.
*/
#define SPI_ENABLE_MULTI_SYNC_TRANSMIT             (STD_OFF)

/**
@brief If enabled, allows to configure more than 256 sequences, jobs and channels.
*/
#define SPI_ALLOW_BIGSIZE_COLLECTIONS (STD_OFF)
/**
@brief If enabled, the asyncronous operation mode (POLLING or INTERRUPT) can
       be defined independently for each HWUnit using Spi_SetHWUnitAsyncMode().
*/
#define SPI_HWUNIT_ASYNC_MODE (STD_OFF)

/**
@brief If enabled, allows dual MCU clock configuration settings.
*/
#define SPI_DUAL_CLOCK_MODE (STD_OFF)

/**
@brief   Specifies if TSB implementation is supported
*/
#define TSB_MODE_SUPPORTED

/**
@brief   Specifies if TSB feature/mode is available
*/
#define SPI_TSB_MODE (STD_OFF)

/**
@brief If enabled, SpiDataType is declared as uint8 instead of uint16.
@remarks Implements DSPI05210
*/
#define SPI_DATA_WIDTH_8  0u
#define SPI_DATA_WIDTH_16 1u
#define SPI_FORCE_DATA_TYPE (STD_OFF)

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE)
#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif /* (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE) */

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define SPI_START_SEC_CODE
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define SPI_STOP_SEC_CODE
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*SPI_CFG_H*/

