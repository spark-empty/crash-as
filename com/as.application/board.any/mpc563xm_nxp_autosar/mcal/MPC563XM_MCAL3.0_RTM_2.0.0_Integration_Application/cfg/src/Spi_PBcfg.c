/**
    @file    Spi_PBcfg.c
    @version 2.0.0

    @brief   AUTOSAR Spi - Post-Build(PB) configuration file.
    @details Generated Post-Build(PB) configuration file.

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

/**
@page misra_violations MISRA-C:2004 violations

@section Spi_Lcfg_c_REF_1
Violates MISRA 2004 Advisory Rule Rule 19.1, only preprocessor statements
and comments before '#include'. AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Spi_Lcfg_c_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include "Reg_eSys_DSPI.h"
#include "Mcal.h"
#if (SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@brief Parameters that shall be published within the configuration source file and also in the
       module's description file
@remarks Covers BSW00374, BSW00318
@{
*/
#define SPI_MODULE_ID_PBCFG_C         83
#define SPI_VENDOR_ID_PBCFG_C         43
#define SPI_AR_MAJOR_VERSION_PBCFG_C  3
#define SPI_AR_MINOR_VERSION_PBCFG_C  0
#define SPI_AR_PATCH_VERSION_PBCFG_C  0
#define SPI_SW_MAJOR_VERSION_PBCFG_C  2
#define SPI_SW_MINOR_VERSION_PBCFG_C  0
#define SPI_SW_PATCH_VERSION_PBCFG_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SPI header file are of the module ID */
#if (SPI_MODULE_ID_PBCFG_C != SPI_MODULE_ID_CFG)
    #error "Spi_PBcfg.c and Spi_Cfg.h have different module ids"
#endif

/* Check if source file and SPI header file are of the same vendor */
#if (SPI_VENDOR_ID_PBCFG_C != SPI_VENDOR_ID_CFG)
    #error "Spi_PBcfg.c and Spi_Cfg.h have different vendor ids"
#endif

/* Check if source file and SPI header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_PBCFG_C != SPI_AR_MAJOR_VERSION_CFG) || \
       (SPI_AR_MINOR_VERSION_PBCFG_C != SPI_AR_MINOR_VERSION_CFG) || \
       (SPI_AR_PATCH_VERSION_PBCFG_C != SPI_AR_PATCH_VERSION_CFG))
      #error "AutoSar Version Numbers of Spi_PBcfg.c and Spi_Cfg.h are different"
  #endif
#endif

/* Check if source file and SPI header file are of the same Software version */
#if ((SPI_SW_MAJOR_VERSION_PBCFG_C != SPI_SW_MAJOR_VERSION_CFG) || \
     (SPI_SW_MINOR_VERSION_PBCFG_C != SPI_SW_MINOR_VERSION_CFG))
    #error "Software Version Numbers of Spi_PBcfg.c and Spi_Cfg.h are different"
#endif

/* Check if source file and Dem header file are of the same version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_PBCFG_C != DEM_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_PBCFG_C != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Spi_PBcfg.c and Dem.h are different"
  #endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_CODE
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/* Job start Notifications */
/* Job End Notifications */
/* Sequence End Notifications */
extern void Spi_Seq0_EndNotification(void); /* End Notification for Sequence 'SpiSequence_0' */

#define SPI_STOP_SEC_CODE
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

#define SPI_START_SEC_VAR_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
/* Allocate Buffers for IB Channels (if any) */
static VAR(Spi_DataType, SPI_VAR) BufferTX_PBSpiChannel_0[8];
static VAR(Spi_DataType, SPI_VAR) BufferRX_PBSpiChannel_0[8];

#define SPI_STOP_SEC_VAR_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/* POSTBUILD FLASH from here onward! */

/*  Buffers Descriptors for IB Channels (if any) */
static CONST(Spi_BufferDescriptor, SPI_CONST) Buffer_PBSpiChannel_0 =
{
    BufferTX_PBSpiChannel_0,
    BufferRX_PBSpiChannel_0
};

/* SpiChannelConfig_PB0 Channel Configuration of SpiDriver_0*/
static CONST(Spi_ChannelConfig, SPI_CONST) SpiChannelConfig_PB0[1] =
{
    {
        /* SpiChannel_0*/
        IB,
        1U,
        8U,
        &Buffer_PBSpiChannel_0,
        &SpiChannelState[0]
    }

};

/* Channel to Job Assignment */

static CONST(Spi_ChannelType, SPI_CONST) SpiJob_0_ChannelAssignment_PB[1] = {SpiChannel_0};

/* SpiJobConfig_PB0 Job Configuration of SpiDriver_0*/
static CONST(Spi_JobConfig, SPI_CONST) SpiJobConfig_PB0[1] =
{
    {
        /* SpiJob_0 */
        (Spi_ChannelType)1u,
        SpiJob_0_ChannelAssignment_PB, /* List of Channels */
        NULL_PTR, /* End Notification */
        NULL_PTR, /* job start Notification */
        (sint8)0, /* Priority */
        &SpiJobState[0], /* JobState instance */
        CSIB0, /* HWUnit index */
        DSPI_1_OFFSET, /* DSPI device HW unit offset */
        /* External Device Settings */
        SpiExternalDevice_0, /* External Device */
        {
        (uint32)(DSPI_CTAR_CPOL_HIGH| /* Clock Polarity (Idle State) */
        DSPI_CTAR_CPHA_LEADING| /* Clock Phase */
        DSPI_CTAR_PCSCLK_1 | DSPI_CTAR_SCSCLK_64 | /* TimeCs2Clk: Should=1.0, Is=1, Error=6.67% */
        DSPI_CTAR_PASC_1 | DSPI_CTAR_SASC_64 | /* TimeClk2Cs: Should=1.0, Is=1, Error=6.67% */
        DSPI_CTAR_PDT_3 | DSPI_CTAR_SDT_128 | /* TimeCs2Cs: Should=6.4, Is=6, Error=0.0% */
        DSPI_CTAR_PBR_5 | DSPI_CTAR_SBR_128 | DSPI_CTAR_DBR_0), /* Baudrate: Should=100000.0, Is=93750, Error=-6.25% */
        (uint32)(DSPI_CMD_PCS0 | /* Chip Select Pin */
        DSPI_CMD_CONTINOUS_TRUE), /* Continous chip select */
        DSPI_PCS0_IDLEHIGH  /* Chip select polarity */
        }
    }

};

/* Job to Sequence Assignment */
static CONST(Spi_JobType, SPI_CONST) SpiSequence_0_JobAssignment_PB[1] = {SpiJob_0};

/* SpiSequenceConfig_PB0 Sequence Configuration of SpiDriver_0*/
static CONST(Spi_SequenceConfig, SPI_CONST) SpiSequenceConfig_PB0[1] =
{
    {  /* SpiSequence_0 */
        (Spi_JobType)1u,
        SpiSequence_0_JobAssignment_PB, /* List of Jobs */
        Spi_Seq0_EndNotification, /* End Notification */
        (uint8)FALSE/* Interruptible */
    }

};

/*---------------------------------------------------------------------------
             SPI Driver Implementation Specific Configuration
-----------------------------------------------------------------------------*/
/* DspiChannelAttributesConfig_PB0 Channel Attribute Configuration of SpiDriver_0*/
static CONST(Spi_LLD_ChannelAttributesConfig, SPI_CONST) DspiChannelAttributesConfig_PB0[1] =
{
    {(uint32)(DSPI_CMD_MSB | DSPI_CMD_WIDTH_8)}

};


/* DspiDeviceAttributesConfig_PB0 Device Attribute Configuration of SpiDriver_0*/
static CONST(Spi_LLD_DeviceAttributesConfig, SPI_CONST) DspiDeviceAttributesConfig_PB0[1] =
{
    {  /* SpiExternalDevice_0 */
        (uint32)(DSPI_CTAR_CPOL_HIGH| /* Clock Polarity (Idle State) */
        DSPI_CTAR_CPHA_LEADING| /* Clock Phase */
        DSPI_CTAR_PCSCLK_1 | DSPI_CTAR_SCSCLK_64 | /* TimeCs2Clk: Should=1.0, Is=1, Error=6.67% */
        DSPI_CTAR_PASC_1 | DSPI_CTAR_SASC_64 | /* TimeClk2Cs: Should=1.0, Is=1, Error=6.67% */
        DSPI_CTAR_PDT_3 | DSPI_CTAR_SDT_128 | /* TimeCs2Cs: Should=6.4, Is=6, Error=0.0% */
        DSPI_CTAR_PBR_5 | DSPI_CTAR_SBR_128 | DSPI_CTAR_DBR_0), /* Baudrate: Should=100000.0, Is=93750, Error=-6.25% */
        (uint32)(DSPI_CMD_PCS0 | /* Chip Select Pin */
        DSPI_CMD_CONTINOUS_TRUE), /* Continous chip select */
        DSPI_PCS0_IDLEHIGH  /* Chip select polarity */
    }
};


/* SpiAttributesConfig_PB0 Attribute Configuration of SpiDriver_0 */
static CONST(Spi_AttributesConfig, SPI_CONST) SpiAttributesConfig_PB0 = {
    DspiChannelAttributesConfig_PB0,
    DspiDeviceAttributesConfig_PB0
};

/* Array of DSPI Unit configurations */
static CONST(Spi_HWUnitConfig, SPI_CONST) HWUnitConfig_PB[SPI_MAX_HWUNIT] =
{
    { DSPI_1_OFFSET, SPI_PHYUNIT_ASYNC }
};

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/* SpiDriver_0 Configuration */
CONST(Spi_ConfigType, SPI_CONST) SpiDriver_0 =
{
    1u,
    1u,
    1u,
    1u,
    SpiChannelConfig_PB0,
    SpiJobConfig_PB0,
    SpiSequenceConfig_PB0,
    &SpiAttributesConfig_PB0,
    HWUnitConfig_PB
};


#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#endif /*(SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)*/

#ifdef __cplusplus
}
#endif

