/**
    @file    Dspi_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Spi - DSPI low-level driver implementations.
    @details DSPI low-level driver implementations.

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

@section Dspi_LLD_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
and comments before "#include". AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Dspi_LLD_c_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
@section Dspi_LLD_c_REF_3
Violates MISRA 2004 Rule 11.1, Conversions shall not be performed between a pointer to a
function and any type other than an integral type.
@section Dspi_LLD_c_REF_4
Violates MISRA 2004 Advisory Rule 11.4, a cast should not be performed between a pointer to object
type and a different pointer to object type. Casts between (uint8*) and (uint32*) are used for
optimizing the memory accesses.
@section Dspi_LLD_c_REF_5
Violates MISRA 2004 Required Rule 8.10,Objects shall be defined at block scope if they are only accessed
from within a single function
@section Dspi_LLD_c_REF_6
Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer arithmetic.

 @section Dspi_LLD_c_REF_7
Violates MISRA 2004 Advisory Rule  12.6, The operands of logical operators (&&, || and !) should be
effectively Boolean. Expressions that are effectively Boolean should not be used as operands to operators other
than (&&, || and !).
@section Dspi_LLD_c_REF_8
Violates MISRA 2004 Advisory Rule  10.5,If the bitwise operators ~ and << are applied to an operand of
underlying type unsigned char or unsigned short, the result shall
be immediately cast to the underlying type of the operand.
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
#include "Mcal.h"
#include "Spi.h"
#include "Dspi_LLD.h"
#include "Dem.h"
#include "Reg_eSys_DSPI.h"
#if (SPI_DMA_USED == STD_ON)
#include "Dma_LLD.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SPI_AR_MAJOR_VERSION_LLD_C      3
#define SPI_AR_MINOR_VERSION_LLD_C      0
#define SPI_AR_PATCH_VERSION_LLD_C      0
#define SPI_SW_MAJOR_VERSION_LLD_C      2
#define SPI_SW_MINOR_VERSION_LLD_C      0
#define SPI_SW_PATCH_VERSION_LLD_C      0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_LLD_C != SPI_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_LLD_C != SPI_AR_MINOR_VERSION) || \
       (SPI_AR_PATCH_VERSION_LLD_C != SPI_AR_PATCH_VERSION))
  #error "AutoSar Version Numbers of SPI_LLD.c and SPI.h are different"
  #endif
#endif

#if ((SPI_SW_MAJOR_VERSION_LLD_C != SPI_SW_MAJOR_VERSION) || \
     (SPI_SW_MINOR_VERSION_LLD_C != SPI_SW_MINOR_VERSION))
#error "Software Version Numbers of SPI_LLD.c and SPI_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_LLD_C != DEM_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_LLD_C != DEM_AR_MINOR_VERSION))
  #error "AutoSar Version Numbers of Spi_LLD.c and Dem.h are different"
  #endif

  #if ((SPI_AR_MAJOR_VERSION_LLD_C != SCHM_SPI_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_LLD_C != SCHM_SPI_AR_MINOR_VERSION))
  #error "AutoSar Version Numbers of Spi_LLD.c and SchM_Spi.h are different"
  #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define SPI_START_SEC_VAR_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
/**
@brief Pool of cached information for sequences having only one job.
*/
STATIC VAR(Spi_SequenceCacheAttrs, AUTOMATIC)
    DspiSeqsAttributes[SPI_OPTIMIZED_SEQ_BUFFER_SIZE];

/**
@brief Pool of cached information for sequences having only one job.
*/
STATIC VAR(Spi_ChannelCacheAttrs, AUTOMATIC)
    DspiChannelsAttributes[SPI_OPTIMIZED_CHANNEL_BUFFER_SIZE];
#endif

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
STATIC VAR(volatile uint32, SPI_VAR) DspiReadDiscard;

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
/**
@brief Holds the mode of the Dual Clock.
@remarks Covers PR-MCAL-3198
*/
VAR(Spi_DualClockMode, AUTOMATIC) Dspi_ClockMode;
#endif

#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
/**
@brief Pointer table to the cached information structure, for one job
       sequences, or NULL, for unoptimized sequences.
*/
P2VAR(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR)
    DspiOneJobSeqsOptimized[SPI_MAX_SEQUENCE];
#endif

/** @brief Keep the HWUnit internal fields */
VAR(Spi_LLD_DeviceState, SPI_VAR) DspiDeviceState[SPI_MAX_HWUNIT];

#define SPI_STOP_SEC_VAR_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))

/**
@brief DMA TCD descriptors for scatter / gather DMA transmissions
@remarks This buffers must be alligned at 32bytes
*/
/**
@note lint tool detection failed due to macro usage.
      Conform with MISRA 2004 Required Rules 8.10 (local variable must be
      defined as static)
*/
/*lint -save -e765*/
ALIGNED_VARS_START(ex_var, 32)
VAR_ALIGN(STATIC VAR(DmaTcdType, AUTOMATIC) Dspi_DmaTcdTxArray[SPI_MAX_HWUNIT], 32)
VAR_ALIGN(STATIC VAR(DmaTcdType, AUTOMATIC) Dspi_DmaTcdTxLastArray[SPI_MAX_HWUNIT], 32)
ALIGNED_VARS_STOP()
/*lint -restore*/
#endif  /* SPI_DMA_USED == STD_ON */

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
#define SPI_START_SEC_CONST_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief DSPI base address array
*/
/**
@note Violates MISRA 2004 Required Rule 8.10 (local variable must be
      defined as static) @ref Dspi_LLD_c_REF_5
      Structure shall be public as it is used by Reg_eSys_DSPI.h which may be
      used outside DSPI module.
*/
/*lint -save -e765*/
CONST(uint32, SPI_CONST) DSPI_BASE_ADDRS[] =
{
    #ifdef  DSPI0_BASEADDR
           DSPI0_BASEADDR,
    #endif
    #ifdef  DSPI1_BASEADDR
           DSPI1_BASEADDR,
    #endif
    #ifdef  DSPI2_BASEADDR
           DSPI2_BASEADDR,
    #endif
    #ifdef  DSPI3_BASEADDR
           DSPI3_BASEADDR,
    #endif
    #ifdef  DSPI4_BASEADDR
           DSPI4_BASEADDR,
    #endif
    #ifdef  DSPI5_BASEADDR
           DSPI5_BASEADDR,
    #endif
    #ifdef  DSPI6_BASEADDR
           DSPI6_BASEADDR,
    #endif
    #ifdef  DSPI7_BASEADDR
           DSPI7_BASEADDR
    #endif
};
/*lint -restore*/
#define SPI_STOP_SEC_CONST_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define SPI_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_InitDma(
        VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
        P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_DmaIrqConfig(
        P2CONST(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
        VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_ChannelTransferFifoInit(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
    VAR(Spi_ChannelType, AUTOMATIC) Channel);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferFifoDrain(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferFifoFill(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_ChannelTransferDmaInit(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
    VAR(Spi_ChannelType, AUTOMATIC) Channel);
#endif

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferDmaContinue(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev);
#endif

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/*================================================================================================*/
/**
@brief   Initialize DMA related fields for a DSPI unit.
@details Initialize DMA TCD descriptors static fields

@param[in]     HWUnit      Specifies which DSPI peripheral is used
@param[in]     DspiDev     LLD instance of the given DSPI peripheral

*/
/*================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_InitDma(
        VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
        P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;

    /**
    @note Violates MISRA 2004 Advisory Rules 11.4
    - See @ref Dspi_LLD_c_REF_4
    */
    /*lint -save -e926 -e927 -e928 -e929*/
    /* initialize cache values */
    DspiDev->TxDmaTcdDefault =
        (P2VAR(uint32, AUTOMATIC, AUTOMATIC))Dspi_DmaTcdTxArray[HWUnit];
    DspiDev->TxDmaTcdLast =
        (P2VAR(uint32, AUTOMATIC, AUTOMATIC))Dspi_DmaTcdTxLastArray[HWUnit];
    /*lint -restore*/
    /**
    @note Violates MISRA 2004 Advisory Rule 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    HWUnitConfig = DspiDev->HWUnitConfig;
    DspiDev->TxDmaTcd =
        (P2VAR(uint32, AUTOMATIC, AUTOMATIC))DMA_TCD(HWUnitConfig->TxDmaChannel);
    DspiDev->RxDmaTcd =
        (P2VAR(uint32, AUTOMATIC, AUTOMATIC))DMA_TCD(HWUnitConfig->RxDmaChannel);
    /*lint -restore*/

    /* store DMA Minor ELink configuration for future usage */
    DspiDev->MinorELink =
       (((uint16)((uint16)1u << 15)) |
        ((uint16)(((uint16)HWUnitConfig->TxDmaChannelAux & DMA_CTRL_MAX_CHANNELS_MASK) << 9))
       );

    /**
    @note Violates MISRA 2004 Advisory Rules 11.1 & 11.4
    - See @ref Dspi_LLD_c_REF_3 & Dspi_LLD_c_REF_4
    */
    /*lint -save -e923 -e926 -e927 -e928 -e929*/
    /* configure TX Channel 1 to write data frames (16bits) to TxDmaBuffer */
    Dma_setup_descriptor((DmaTcdPointerType)DspiDev->TxDmaTcd,
        (uint32) 0u, /* src address read => will be updated later */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            (uint8)  0x0, /* 1bytes src transfer size */
            (uint8)  0x0, /* 1bytes dest transfer size */
            (uint16) 1u, /* src offset */
            (uint16) 1u, /* bytes to transfer */
        #else
        (uint8)  DMA_DATA_TRANSFER_16_BIT, /* 2bytes src transfer size */
        (uint8)  DMA_DATA_TRANSFER_16_BIT, /* 2bytes dest transfer size */
        (uint16) 2u, /* src offset */
        (uint16) 2u, /* bytes to transfer */
        #endif
        (uint32) 0u, /* no src adjustment */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
           (uint32) (&DspiDev->TxDmaBuffer)+3u, /* dest address */
        #else
           (uint32) (&DspiDev->TxDmaBuffer)+2u, /* dest address */
        #endif
        (uint16) DspiDev->MinorELink, /* major iter will be updated later */
        (uint16) 0u, /* no dest offset */
        (uint32) DspiDev->TxDmaTcdDefault, /* S/G to itself */
        (uint16) DspiDev->MinorELink, /* major iter will be updated later */
        (uint8)  HWUnitConfig->TxDmaChannelAux, /* major e_link */
        (uint8)  (DMA_TCD_MAJOR_E_LINK | DMA_TCD_SGA));

    /* duplicate in memory TX Channel 1 TCD, for final restore */
    /**     @note Violates MISRA 2004 Advisory 11.1, 11.4 -
            See @ref Dspi_LLD_c_REF_3 & Dspi_LLD_c_REF_4
    */
    Dma_setup_descriptor((DmaTcdPointerType)DspiDev->TxDmaTcdDefault,
        (uint32) 0u, /* src address read => will be updated later */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            (uint8)  0x0, /* 1bytes src transfer size */
            (uint8)  0x0, /* 1bytes dest transfer size */
            (uint16) 1u, /* src offset */
            (uint16) 1u, /* bytes to transfer */
        #else
            (uint8)  DMA_DATA_TRANSFER_16_BIT, /* 2bytes src transfer size */
            (uint8)  DMA_DATA_TRANSFER_16_BIT, /* 2bytes dest transfer size */
            (uint16) 2u, /* src offset */
            (uint16) 2u, /* bytes to transfer */
        #endif
        (uint32) 0u, /* no src adjustment */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
           (uint32) (&DspiDev->TxDmaBuffer)+3u, /* dest address */
        #else
           (uint32) (&DspiDev->TxDmaBuffer)+2u, /* dest address */
        #endif
        (uint16) DspiDev->MinorELink, /* major iter will be updated later */
        (uint16) 0u, /* no dest offset */
        (uint32) DspiDev->TxDmaTcdDefault, /* S/G to itself */
        (uint16) DspiDev->MinorELink, /* major iter will be updated later */
        (uint8)  HWUnitConfig->TxDmaChannelAux, /* major e_link */
        (uint8)  (DMA_TCD_MAJOR_E_LINK | DMA_TCD_SGA));

    /* configure TX Channel 2 to write TxDmaBuffer (32bits) to DSPI PUSHR */
    /**
    @note Violates MISRA 2004 Advisory Rule 11.1
    - See @ref Dspi_LLD_c_REF_3
   */
    Dma_setup_descriptor((DmaTcdPointerType)(DMA_TCD(HWUnitConfig->TxDmaChannelAux)),
        (uint32) (&DspiDev->TxDmaBuffer), /* src address read */
        (uint8)  DMA_DATA_TRANSFER_32_BIT, /* 4bytes src transfer size */
        (uint8)  DMA_DATA_TRANSFER_32_BIT, /* 4bytes dest transfer size */
        (uint16) 0u, /* no src offset */
        (uint16) 4u, /* bytes to transfer */
        (uint32) 0u, /* no src adjustment */
        (uint32) (DspiDev->pDspiPUSHRAddress), /* dest address */
        (uint16) 1, /* crt maj iter cnt */
        (uint16) 0u, /* no dest offset */
        (uint32) 0u, /* no dest adjustment */
        (uint16) 1, /* beg maj iter cnt */
        (uint8)  0u, /* no major linked channel */
        (uint8)  DMA_TCD_DISABLE_REQ);

    /* setup scatter/gather TCD */
    /* S/G to the original DMA TCD => reload the initial values */
    /**
    @note Violates MISRA 2004 Advisory Rule 11.1
    - See @ref Dspi_LLD_c_REF_3
       */
    Dma_setup_descriptor((DmaTcdPointerType)DspiDev->TxDmaTcdLast,
        (uint32) (&DspiDev->TxDmaBufferLast), /* src address read */
        (uint8)  DMA_DATA_TRANSFER_32_BIT, /* 4bytes src transfer size */
        (uint8)  DMA_DATA_TRANSFER_32_BIT, /* 4bytes dest transfer size */
        (uint16) 0u, /* no src offset */
        (uint16) 4u, /* bytes to transfer */
        (uint32) 0u, /* no src adjustment */
        (uint32) (&DspiDev->TxDmaBuffer), /* dest address */
        (uint16) 1u, /* crt maj iter cnt */
        (uint16) 0u, /* no dest offset */
        (uint32) DspiDev->TxDmaTcdDefault, /* S/G to the initial TX DMA TCD */
        (uint16) 1u, /* beg maj iter cnt */
        (uint8)  HWUnitConfig->TxDmaChannelAux, /* major e_link */
        (uint8)  (DMA_TCD_MAJOR_E_LINK | DMA_TCD_DISABLE_REQ | DMA_TCD_SGA));

    /* setup RX DMA channel */
    /**
    @note Violates MISRA 2004 Advisory Rules 11.1 & 11.4
    - See @ref Dspi_LLD_c_REF_3 & Dspi_LLD_c_REF_4
    */
    Dma_setup_descriptor((DmaTcdPointerType)DspiDev->RxDmaTcd,
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            (uint32)(DspiDev->pDspiPOPRAddress)+3u, /* data only read */
            (uint8) 0x0, /* 1bytes src transfer size */
            (uint8) 0x0, /* 1bytes dest transfer size */
        #else
            (uint32)(DspiDev->pDspiPOPRAddress)+2u, /* data only read */
            (uint8) DMA_DATA_TRANSFER_16_BIT, /* 2bytes src transfer size */
            (uint8) DMA_DATA_TRANSFER_16_BIT, /* 2bytes dest transfer size */
        #endif
        (uint16) 0u, /* no src offset */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            (uint16) 1u, /* bytes to transfer */
        #else
            (uint16) 2u, /* bytes to transfer */
        #endif
        (uint32) 0u, /* no src adjustment */
        (uint32) 0u, /* dest address => will be updated later */
        (uint16) 0u, /* crt maj iter cnt => will be updated later */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            (uint16) 1u, /* bytes to transfer */
        #else
            (uint16) 2u, /* dest offset */
        #endif
        (uint32) 0u, /* no dest adjustment */
        (uint16) 0u, /* beg maj iter cnt => will be updated later */
        (uint8)  0u, /* no major linked channel */
        (uint8)  DMA_TCD_DISABLE_REQ);
    /*lint -restore*/

}
#endif /* (SPI_DMA_USED == STD_ON) */

/*================================================================================================*/
/**
@brief   Configures DMA interrupts for the Rx channel.
@details Activate RX channel interrupt in interrupt mode or disable then
         in polling mode.

@param[in]     DspiDev     LLD instance of the given DSPI peripheral
@param[in]     AsyncMode   operation mode
                           (SPI_INTERRUPT_MODE | SPI_POLLING_MODE)

*/
/*================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_DmaIrqConfig(
        P2CONST(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
        VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode)
{
    /**
    @note Violates MISRA 2004 Advisory Rule 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    if (SPI_INTERRUPT_MODE == AsyncMode)
    {
        LLM_Set_DMA_TCDADDR_INT(DspiDev->RxDmaTcd);
    }
    else
    {
        LLM_Clear_DMA_TCDADDR_INT(DspiDev->RxDmaTcd);
    }
    /*lint -restore*/
}
#endif /* (SPI_DMA_USED == STD_ON) */

/*================================================================================================*/
/**
@brief   This function initializes channel related informations in DSPI HW Unit
         structure.
@details The function must be called before starting the async transfer of a
         channel

    Configuration caracteristics:
    - TxDma1 fills the Data part (16bits) of a TxBuffer (32 bits), with the
      command field set by this function
    - TxDma1 is daisy chained with TxDma2 which transfers the TxBuffer content
      to the DSPI PUSHR register.
    - At the end of TxDma1 transmission, one of the following may happend:
        -> a dedicated descriptor is loaded through scatter/gather into the
           channel TCD, in order to transfer the last dataframe which will
           deassert the CS signal (for end of job channels - see picture below)
        -> the default Tx descriptor is reloaded through scatter/gather into
           the channel TCD, in order to facilitate the next transmission
           configuration; transmission session not started for this descriptor
           (for not end of job channels, or for channels having the size of 1.)
        -> the scatter/gather link is disabled, and the DMA transmission ends,
           conserving the actual Spi Tx/Rx Buffer pointers (for long channels,
           which need to be transfered in manny datachunck of
           DMA_MAX_LINKED_ITER_CNT)

1) DMA configuration for the transmission of the last channel in job
   - for this situation, the last frame will be sent using a distinct DMA
     descriptor, as it should manage the CS deassertion into the command field.

    SpiTxBuffer
         |
         V
    ,---------,     DMA.E_LINK
    | TX DMA1 |.......................
    |         |>-------,             :
    '---------'        |             :
     :DMA.S_G          |16bits       :
     :                 |             :
     : TxDmaBufferLast |             :
     :     |           |             :
     V     V           |             :
    ,---------,        |  DMA.E_LINK V
    | TX DMA  |.......................
    |  Last   |>--,    |             :
    '---------'   |    |             :
                  |    |             :
            32bits|    V             :
                  V /----\           :
               /---------\           V
  TxDmaBuffer: |Cmd |Data|      ,---------,
               \---------/      | TX DMA2 |
                    '---------->|         |---->DSPI.PUSHR
                        32bits  '---------'
                                                            ,---------,
                                                DSPI.POPR-->| RX DMA  |
                                                            |         |
                                                            '---------'
                                                                 |
                                                                 V
                                                            SpiRxBuffer

2) DMA configuration for the transmission of a not final job channel, or
   for channels having only one dataframe.
   - all transmission is managed through the DMA TX descriptor in place;
     reload only the default DMA descriptor

    SpiTxBuffer
         |
         V
    ,---------,     DMA.E_LINK
    | TX DMA1 |.......................
    |         |>-------,             :
    '---------'        |             :
         :DMA.S_G      |16bits       :
         :             |             :
         :             |             :
         :             |             :
         V             |             :
    ,---------,        |             :
    | TX DMA  |        |             :
    | Default |        |             :
    '---------'        |             :
                       |             :
                       |             :
                       V             :
                    /----\           V
  TxDmaBuffer: |Cmd |Data|      ,---------,
               \---------/      | TX DMA2 |
                    '---------->|         |---->DSPI.PUSHR
                        32bits  '---------'
                                                            ,---------,
                                                DSPI.POPR-->| RX DMA  |
                                                            |         |
                                                            '---------'
                                                                 |
                                                                 V
                                                            SpiRxBuffer

3) DMA configuration for the transmission of long jobs
   - same picture as (2) but without any scatter/gather chaining;
   - then the transmission is finished, the Tx channel descriptor
     will conserve the Rx/Tx Spi buffer pointers

As the Tx / Rx channel descriptors are already preset with some values, this
function updates only:
- Tx descriptor: - source address (Spi Tx Buffer)
                 - DMA major iteration count (derived from channel size)
                 - scattered/gathered DMA descriptor address
                   (TxDmaLast or TxDmaDefault)
                 - flags (S/G & DREQ activation)
- Rx descriptor: - destination address (Spi Rx Buffer)
                 - DMA major iteration count (channel size)

@param[in]     DspiDev     Specifies device involved in transmission
@param[in]     Channel     ID of the channel to be transmited.

@remarks Implements DSPI03510
*/
/*================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_ChannelTransferDmaInit(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
    VAR(Spi_ChannelType, AUTOMATIC) Channel)
{
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig;
   /**
    @note Violates MISRA 2004 Advisory Rule 17.4
    - See @ref Dspi_LLD_c_REF_6
   */
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig =
        &SpiConfigPtr->ChannelConfig[Channel];
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) pChannelState =
        pChannelConfig->ChannelState;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) BufferRX;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) BufferTX;
    VAR(Spi_NumberOfDataType, SPI_VAR) FramesCount;
    VAR(sint32, SPI_VAR) CsClearNeeded = FALSE;

    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) TxTcdAddr = DspiDev->TxDmaTcd;
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) RxTcdAddr = DspiDev->RxDmaTcd;
    VAR(uint8, AUTOMATIC) SgaFlag = DMA_TCD_SGA;

    /* Set the CTAR parameters for this channel */
    DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;

    /**
      @note False detection of MISRA 2004 Rule 11.4, 17.4 violation
      - See @ref Dspi_LLD_c_REF_4,
      - See @ref Dspi_LLD_c_REF_6
    */
    /*lint -save -e929 -e960*/
    /* set CTAR register */
    /**@remarks The call is blocking till the HWUnit exits the running state.*/
    REG_WRITE32(DspiDev->pDspiCTARAddress,
                (DspiDev->ExternalDeviceCTAR |
                 DspiChannelAttributesConfig[Channel].CMD));
    /*lint -restore*/

    /**
    @note Violates MISRA 2004 Advisory Rules 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/

    FramesCount = pChannelState->Length;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
    {
        /* When Spi_DataWidth is 16 bits number of frames is half of TX buffer */
        FramesCount /= 2u;
    }
#endif
    /**
    @note All calls to LLM_Wr_DMA_TCDADDR_...() violate
    MISRA 2004 Advisory Rule 11.1,11.4
    - See @ref Dspi_LLD_c_REF_3, Dspi_LLD_c_REF_4
    */
    /*lint -save -e926 -e927 -e928 -e929*/
    /* identify the TX/RX buffers and update them into the DMA TCDs */
    if (0u != (pChannelState->Flags & ((uint8)SPI_CHANNEL_FLAG_TX_DEFAULT)))
    {
        /* update source address into the DMA TCD */
        LLM_Wr_DMA_TCDADDR_SADDR(TxTcdAddr, (uint32)(&pChannelConfig->DefaultTransmitValue));
        /* overwrite the default src next offset */
        LLM_Wr_DMA_TCDADDR_SOFF(TxTcdAddr, (uint16)0u /* no src offset */);

        DspiDev->TxDmaBufferLast = ((DspiDev->CurrentCmd & ~DSPI_CONT_MASK) |
                pChannelConfig->DefaultTransmitValue);
    }
    else
    {
        BufferTX = pChannelConfig->BufferDescriptor->BufferTX;

        /* configure TX Channel 1 to write data frames (16bits) to TxDmaBuffer */
        LLM_Wr_DMA_TCDADDR_SADDR(TxTcdAddr, (uint32)BufferTX);
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
          if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
          {
                /* overwrite the default src next offset */
                /* 2 bytes src transfer size, 2 bytes dest transfer size */
                /* 2 bytes src offset */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_TA_SOFF_OFFSET, (uint32)(0x01010002u));
                /* dest address */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_DADDR_OFFSET,
                            (uint32)(&DspiDev->TxDmaBuffer)+2u);
                /* 2 bytes to transfer */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_SMLO_NBTYES_OFFSET, (uint32)(0x02u));
          }
          else
          {
                /* overwrite the default src next offset */
                /* 1 bytes src transfer size, 1 bytes dest transfer size */
                /* 1 bytes src offset */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_TA_SOFF_OFFSET, (uint32)(0x00000001u));
                /* dest address */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_DADDR_OFFSET,
                            (uint32)(&DspiDev->TxDmaBuffer)+3u);
                /* 1 bytes to transfer */
                REG_WRITE32((uint32)(TxTcdAddr) + DMA_TCD_SMLO_NBTYES_OFFSET, (uint32)(0x01u));
          }
        #endif
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     - See @ref Dspi_LLD_c_REF_6
    */
    /*lint -save -e960*/
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
        if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth )
        {
            DspiDev->TxDmaBufferLast = ((DspiDev->CurrentCmd & ~DSPI_CONT_MASK) |
                        ((uint8) (BufferTX[pChannelState->Length -2u])<<8) |
                          BufferTX[pChannelState->Length - 1u] );
        }
        else
        {
            DspiDev->TxDmaBufferLast = ((DspiDev->CurrentCmd & ~DSPI_CONT_MASK) |
                    BufferTX[FramesCount-1u]);
        }
        #else
            DspiDev->TxDmaBufferLast = ((DspiDev->CurrentCmd & ~DSPI_CONT_MASK) |
                        BufferTX[FramesCount-1u]);
        #endif
    /*lint -restore*/
    }

    /* prepare the command in the intermediate buffer */
    DspiDev->TxDmaBuffer = DspiDev->CurrentCmd;

    /* get the number of frames to be sent through DMA */
    if ( DMA_MAX_LINKED_ITER_CNT < FramesCount)
    {
        /* DMA iteration count is on 9 bits, if e_link field is used */
        DspiDev->RemainingData = FramesCount - DMA_MAX_LINKED_ITER_CNT;
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
            {
                DspiDev->RemainingData *= 2u;
            }
        #endif
        FramesCount = DMA_MAX_LINKED_ITER_CNT;

        /* S/G linking must be disabled in this case;
           The actual TCD must be in place till the last DMA chunk will
           be finished */
        SgaFlag = 0u;
        /* reset dest address adjustement */
    /**     @note Violates MISRA 2004 Advisory Rules 11.1     - See @ref Dspi_LLD_c_REF_3     */
        LLM_Wr_DMA_TCDADDR_DLAST_SGA(TxTcdAddr, 0u);
    }
    else
    {
        DspiDev->RemainingData = 0u;

        /* identify if CS clearing will be needed at the channel end */
        if (0u == DspiDev->RemainingChannels)
        {
            if (1u == FramesCount)
            {   /* clear the CS assertion directly into the next TX frame */
                DspiDev->TxDmaBuffer &= ~DSPI_CONT_MASK;
            }
            else
            {   /* the last dataframe must be sent in a distinct TCD */
                CsClearNeeded = TRUE;
            }
        }
    }

    /* Configure RX DMA descriptor */
    /* Rx buffer will be NULL if discarding read values */
    BufferRX = pChannelConfig->BufferDescriptor->BufferRX;
    if (NULL_PTR == BufferRX)
    {
        /* dest address - discard read */
        LLM_Wr_DMA_TCDADDR_DADDR(RxTcdAddr, (uint32) &DspiReadDiscard);
        /* update RX transfer size; no offset for destination address */
        LLM_Wr_DMA_TCDADDR_CITER_DOFF(RxTcdAddr, ((uint32)(FramesCount)<<16) | 0u );
        LLM_Wr_DMA_TCDADDR_BITER(RxTcdAddr, (uint16)FramesCount);
    }
    else
    {
        /* dest address - RX buffer */
        LLM_Wr_DMA_TCDADDR_DADDR(RxTcdAddr, (uint32) BufferRX);
        /* update RX transfer size; 2bytes offset for destination address */
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
          if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
          {
                /* update RX transfer size; 2bytes offset for destination address */
                LLM_Wr_DMA_TCDADDR_CITER_DOFF(RxTcdAddr, ((uint32)(FramesCount)<<16) | 2u );
                LLM_Wr_DMA_TCDADDR_SADDR(RxTcdAddr, (uint32)(DspiDev->pDspiPOPRAddress)+2u);
                /* overwrite the default src next offset */
                /* 2 bytes src transfer size, 2 bytes dest transfer size */
                /* no src offset */
                 REG_WRITE32((uint32)(RxTcdAddr) + DMA_TCD_TA_SOFF_OFFSET, (uint32)(0x01010000u));
                 /* 2 bytes to transfer */
                 REG_WRITE32((uint32)(RxTcdAddr) + DMA_TCD_SMLO_NBTYES_OFFSET, (uint32)(0x02u));
          }
          else
          {
                /* update RX transfer size; 1bytes offset for destination address */
                LLM_Wr_DMA_TCDADDR_CITER_DOFF(RxTcdAddr, ((uint32)(FramesCount)<<16) | 1u );
                LLM_Wr_DMA_TCDADDR_SADDR(RxTcdAddr, (uint32)(DspiDev->pDspiPOPRAddress)+3u);
                /* overwrite the default src next offset */
                /* 1 bytes src transfer size, 1 bytes dest transfer size */
                /* no src offset */
                REG_WRITE32((uint32)(RxTcdAddr) + DMA_TCD_TA_SOFF_OFFSET, (uint32)(0x00000000u));
                /* 1 bytes to transfer */
                REG_WRITE32((uint32)(RxTcdAddr) + DMA_TCD_SMLO_NBTYES_OFFSET, (uint32)(0x01u));
          }
        #else
          /* update RX transfer size; 2bytes offset for destination address */
          LLM_Wr_DMA_TCDADDR_CITER_DOFF(RxTcdAddr, ((uint32)(FramesCount)<<16) | 2u );
        #endif
        LLM_Wr_DMA_TCDADDR_BITER(RxTcdAddr, (uint16)FramesCount);
    }

    /* configure or not scatter/gather related informations */
    if (CsClearNeeded)
    {
        /* if Cs clearing is needed, last dataframe will be transmited using
           a distinct TCD.
         */

        /* update transfer size, preserving linked channel information */
        FramesCount = (DspiDev->MinorELink | ((uint16)(FramesCount-1u)));
        LLM_Wr_DMA_TCDADDR_CITER(TxTcdAddr, (uint16)FramesCount);
        LLM_Wr_DMA_TCDADDR_BITER(TxTcdAddr, (uint16)FramesCount);

        /* flags are set by default to DMA_TCD_MAJOR_E_LINK | DMA_TCD_SGA */
        /* update S/G address with the address of the CS clearing TCD */
        LLM_Wr_DMA_TCDADDR_DLAST_SGA(TxTcdAddr, (uint32)DspiDev->TxDmaTcdLast);
    }
    else
    {
        /* update transfer size, preserving linked channel information */
        FramesCount = (DspiDev->MinorELink | ((uint16)FramesCount));
        LLM_Wr_DMA_TCDADDR_CITER(TxTcdAddr, (uint16)FramesCount);
        LLM_Wr_DMA_TCDADDR_BITER(TxTcdAddr, (uint16)FramesCount);

        /* S/G address set by default to reload the default TX1 TCD */
        /* setup flags */
        /* reset DONE flag (quicker than LLM_Wr_DMA_CDNE()) */
        LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr, 0u);
        LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr,
            (uint8)(DMA_TCD_DONE | DMA_TCD_MAJOR_E_LINK | DMA_TCD_DISABLE_REQ | SgaFlag));
    }
    /*lint -restore*/ /* end of Rule 11.4 violations */

    /* start RX before TX! */
    HWUnitConfig = DspiDev->HWUnitConfig;
    /**
     @note Violates MISRA 2004 Advisory Rule 11.1
     - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    Dma_start_channel(HWUnitConfig->RxDmaChannel);
    Dma_start_channel(HWUnitConfig->TxDmaChannel);
    /*lint -restore*/
}
#endif /* SPI_DMA_USED == STD_ON */

/*================================================================================================*/
/**
@brief   Restart the DMA transmission, refreshing the size.
@details Source and destination addresses are already set into the active TCDs

@param[in]     DspiDev      Specifies which DSPI module is used

@pre The function can be called only if Spi_LLD_JobTransferDmaStart() was
     previously called to initialize the DMA configuration.
@remarks Implements DSPI03508
*/
/*================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferDmaContinue(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
    VAR(Spi_NumberOfDataType, SPI_VAR) FramesCount;
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) TxTcdAddr = DspiDev->TxDmaTcd;
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) RxTcdAddr = DspiDev->RxDmaTcd;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;

    if(SPI_DATA_WIDTH_16 ==
       DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
    {
        FramesCount = DspiDev->RemainingData / 2u;
    }
    else
    {
        FramesCount = DspiDev->RemainingData;
    }
#else
    FramesCount = DspiDev->RemainingData;
#endif
    /**
    @note All calls to LLM_Wr_DMA_TCDADDR_...() violate
    MISRA 2004 Advisory Rules 11.4,11.1
    - See @ref Dspi_LLD_c_REF_4,Dspi_LLD_c_REF_3
    */
    /*lint -save -e926 -e927 -e928 -e929*/

    /* get the number of frames to be sent through DMA */
    if ( DMA_MAX_LINKED_ITER_CNT < FramesCount)
    {
        /* DMA iteration count is on 9 bits, if e_link field is used */
        DspiDev->RemainingData = FramesCount - DMA_MAX_LINKED_ITER_CNT;
         #if (SPI_FORCE_DATA_TYPE == STD_ON)
            if(SPI_DATA_WIDTH_16 ==
               DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
            {
                DspiDev->RemainingData *= 2u;
            }
        #endif
        FramesCount = DMA_MAX_LINKED_ITER_CNT;

/**     @note Violates MISRA 2004 Advisory Rules 11.1     - See @ref Dspi_LLD_c_REF_3     */
        /* update RX transfer size */
        LLM_Wr_DMA_TCDADDR_CITER(RxTcdAddr, (uint16)FramesCount);
        LLM_Wr_DMA_TCDADDR_BITER(RxTcdAddr, (uint16)FramesCount);
    }
    else
    {
        /* update RX transfer size */
        LLM_Wr_DMA_TCDADDR_CITER(RxTcdAddr, (uint16)FramesCount);
        LLM_Wr_DMA_TCDADDR_BITER(RxTcdAddr, (uint16)FramesCount);

        DspiDev->RemainingData = 0u;

        /* identify if CS clearing will be needed at the channel end */
        if ( 0u == DspiDev->RemainingChannels )
        {
            if (1u == FramesCount)
            {   /* clear the CS assertion directly into the next TX frame */
                DspiDev->TxDmaBuffer &= ~DSPI_CONT_MASK;
                /* set S/G address to reload the default TX1 descriptor,
                   at the end
                   */
                LLM_Wr_DMA_TCDADDR_DLAST_SGA(TxTcdAddr,
                        (uint32)DspiDev->TxDmaTcdDefault);
                /* reset DONE flag (quicker than LLM_Wr_DMA_CDNE()) */
                LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr, 0u);
                /* enable scatter/gather link and conserve the E_LINK setting;
                   - DMA REQ must be disabled at the end of the current
                   transfer, in order to stop the transfer before the reload of
                   the default TCD
                 */
                LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr,
                    DMA_TCD_MAJOR_E_LINK | DMA_TCD_SGA | DMA_TCD_DISABLE_REQ);
            }
            else
            {   /* last dataframe will be transmited using a distinct TCD. */
                LLM_Wr_DMA_TCDADDR_DLAST_SGA(TxTcdAddr,
                    (uint32)DspiDev->TxDmaTcdLast);
                /* reset DONE flag (quicker than LLM_Wr_DMA_CDNE()) */
                LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr, 0u);
                /* enable scatter/gather link and conserve the E_LINK setting;
                   - DMA REQ must not be disabled at the end of the current
                   transfer, in order to allow the execution of the linked SG
                 */
                LLM_Wr_DMA_TCDADDR_FLAGS(TxTcdAddr,
                        DMA_TCD_MAJOR_E_LINK | DMA_TCD_SGA);
                FramesCount--;
            }
        }
    }

    /* update transfer size, preserving linked channel information */
    FramesCount = (DspiDev->MinorELink | ((uint16)FramesCount));
    LLM_Wr_DMA_TCDADDR_CITER(TxTcdAddr, (uint16)FramesCount);
    LLM_Wr_DMA_TCDADDR_BITER(TxTcdAddr, (uint16)FramesCount);

    /*lint -restore*//* end of Rule 11.4 violations */

    /* start RX before TX! */
    HWUnitConfig = DspiDev->HWUnitConfig;
    /**
     @note Violates MISRA 2004 Advisory Rule 11.1
     - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    Dma_start_channel(HWUnitConfig->RxDmaChannel);
    Dma_start_channel(HWUnitConfig->TxDmaChannel);
    /*lint -restore*/
}
#endif

/*================================================================================================*/
/**
@brief   This function initializes channel related informations in DSPI HW Unit
         structure.
@details The function must be called before starting the async transfer of a
         channel

@param[in]     DspiDev     Specifies device involved in transmission
@param[in]     Channel     ID of the channel to be transmited.

@remarks Implements DSPI03510
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_ChannelTransferFifoInit(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev,
    VAR(Spi_ChannelType, AUTOMATIC) Channel)
{
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) pChannelState;

/**
 @note Violates MISRA 2004 Advisory Rule 17.4
 - See @ref Dspi_LLD_c_REF_6
*/
    pChannelConfig = &SpiConfigPtr->ChannelConfig[Channel];
    pChannelState = pChannelConfig->ChannelState;
    DspiDev->RemainingData = pChannelState->Length;

    /* identify the TX/RX buffers */
    if (0u != (pChannelState->Flags & ((uint8)SPI_CHANNEL_FLAG_TX_DEFAULT)))
    {
        DspiDev->CurrentTxBuffer = NULL_PTR;

        /* integrate default transmit value in the command */
        DspiDev->CurrentCmd |= pChannelConfig->DefaultTransmitValue;
    }
    else
    {
        DspiDev->CurrentTxBuffer = pChannelConfig->BufferDescriptor->
                    BufferTX;

        /* remove default transmit value from the command, if previously set */

        DspiDev->CurrentCmd &= DSPI_TX_CMD_MASK;
    }

    /* Rx buffer will be NULL if discarding read values */
    DspiDev->CurrentRxBuffer = pChannelConfig->BufferDescriptor->BufferRX;

    /* Set the CTAR parameters for this channel */
    DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;

    /**
      @note False detection of MISRA 2004 Rule 11.4,17.4 violation
      - See @ref Dspi_LLD_c_REF_4,
      - See @ref Dspi_LLD_c_REF_6
    */
    /*lint -save -e929 -e960*/
    /* set CTAR register */
    /**@remarks The call is blocking till the HWUnit exits the running state.*/
    REG_WRITE32(DspiDev->pDspiCTARAddress,
                (DspiDev->ExternalDeviceCTAR |
                 DspiChannelAttributesConfig[Channel].CMD));
    /*lint -restore*/
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function fills the DSPI FIFO.
@details This function fills DSPI FIFO Transmit buffer with the
         predefined data assigned or transmit the default
         buffer values in case of the lack of transmit
         data buffer.

@param[in]     DspiDev     Specifies which DSPI module is used

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2

@remarks Implements DSPI03510
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferFifoFill(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    VAR(uint32, SPI_VAR) Cmd;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferTX;
    VAR(Spi_NumberOfDataType, SPI_VAR) nFramesCount;
    VAR(sint32, SPI_VAR) bEndOfJob; /* end of job */
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullTX;
#endif
    /* Get physical device handler */
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiPUSHRAddress =
        DspiDev->pDspiPUSHRAddress;

    /* Get Channel Attributes */
    Cmd = DspiDev->CurrentCmd;

    /* calculate the number of frames to be sent and the 'end of job' state */
    nFramesCount = DspiDev->RemainingData;
    #if (SPI_FORCE_DATA_TYPE == STD_ON)
        if(SPI_DATA_WIDTH_16 ==
           DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
        {
            nFramesCount/=2u;
        }
    #endif
    /* TX_FIFO_SIZE =4 */
    if (nFramesCount > SPI_FIFO_SIZE)
    {
        nFramesCount = SPI_FIFO_SIZE;
        bEndOfJob = FALSE; /* end of job not reached */
    }
    else
    {
        /* end of job reached if this is the last channel in the job */
        bEndOfJob = (sint32)(0u == DspiDev->RemainingChannels);
    }

    pBufferTX = DspiDev->CurrentTxBuffer;
    DspiDev->RemainingData -= nFramesCount;
    #if (SPI_FORCE_DATA_TYPE == STD_ON)
    if(SPI_DATA_WIDTH_16 ==
       DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
    {
        DspiDev->RemainingData -= nFramesCount;
    }
    #endif
    DspiDev->SentFrames = nFramesCount;

    if (NULL_PTR != pBufferTX)
    {
        /* set the new TX buffer pointer */
        /**
         @note Violates MISRA 2004 Advisory Rule 17.4
         - See @ref Dspi_LLD_c_REF_6
        */
        /*lint -save -e960*/
        DspiDev->CurrentTxBuffer += nFramesCount;
        /*lint -restore*/
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
        if(SPI_DATA_WIDTH_16 ==
           DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
        {
            DspiDev->CurrentTxBuffer += nFramesCount;
        }
        #endif
        /* write the information from the buffer */
        while (nFramesCount > 0u)
        {
            nFramesCount--;

            if (0u == nFramesCount)
            {
                Cmd |= DSPI_EOQ_MASK;    /* EOQ bit in PUSHR */
                /* Force the CS disabling if last data unit
                   for the last channel of the Job */
                if (bEndOfJob)
                {
                    /* signal the end of job for the current DSPI Unit */
                    DspiDev->IsEndOfJob = TRUE;
                    Cmd = Cmd & ~DSPI_CONT_MASK; /* clear the continous CS assertion */
                }
            }

            /*lint -save -e960 -e929*/
            #if (SPI_FORCE_DATA_TYPE == STD_ON)
                if( SPI_DATA_WIDTH_16 ==
                    DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
                {
                    pBufferFullTX = (uint16 *) pBufferTX;

                    /**
                    @note False detection of MISRA 2004 Rule 11.4 violation
                    (cast from pointer to pointer)
                    */
                    REG_WRITE32(pDspiPUSHRAddress, (Cmd | *pBufferFullTX));

                    /**
                    @note Violates MISRA 2004 Required Rule 17.4
                    (pointer arithmetic by increment or decrement used)
                    - See @ref Dspi_LLD_c_REF_6
                    */
                    pBufferTX++;
                }
                else
                {
                    /**
                    @note False detection of MISRA 2004 Rule 11.4 violation
                    (cast from pointer to pointer)
                    */
                    REG_WRITE32(pDspiPUSHRAddress, (Cmd | *pBufferTX));
                }
            #else
                /**
                   @note False detection of MISRA 2004 Rule 11.4 violation
                   (cast from pointer to pointer)
                */
                REG_WRITE32(pDspiPUSHRAddress, (Cmd | *pBufferTX));
            #endif
            /**
              @note Violates MISRA 2004 Required Rule 17.4
                    (pointer arithmetic by increment or decrement used)
              - See @ref Dspi_LLD_c_REF_6
            */
            pBufferTX++;
            /*lint -restore*/
        }
        /* update current TX buffer pointer */
        DspiDev->CurrentTxBuffer = pBufferTX;
    }
    else
    {   /* write the default value */
        while (nFramesCount > 0u)
        {
            nFramesCount--;

            if (0u == nFramesCount)
            {
                Cmd |= DSPI_EOQ_MASK;    /* EOQ bit in PUSHR */
                /* Force the CS disabling if last data unit
                   for the last channel of the Job */
                if (bEndOfJob)
                {
                    /* signal the end of job for the current DSPI Unit */
                    DspiDev->IsEndOfJob = TRUE;
                    Cmd = Cmd & ~DSPI_CONT_MASK; /* clear the continous CS assertion */
                }
            }

            /**
              @note False detection of MISRA 2004 Rule 11.4 violation
                   (cast from pointer to pointer)
            */
            /*lint -save -e929*/
            /* default transmit value already integrated in DspiDev->CurrentCmd */
            REG_WRITE32(pDspiPUSHRAddress, Cmd);
            /*lint -restore*/
        }
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function drains the DSPI FIFO.
@details This function retrieves the received data from DSPI FIFO

@param[in]     DspiDev     Specifies which DSPI module is used
@remarks Implements DSPI03511
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
STATIC INLINE FUNC (void, SPI_CODE) Spi_LLD_JobTransferFifoDrain(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferRx;

    VAR(Spi_NumberOfDataType, AUTOMATIC) nFramesCount;
    volatile P2VAR(uint32, AUTOMATIC, SPI_VAR) pDspiPOPRAddress =
        DspiDev->pDspiPOPRAddress;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullRX;
#endif

    nFramesCount = DspiDev->SentFrames;

    pBufferRx = DspiDev->CurrentRxBuffer;

    if (NULL_PTR != pBufferRx)
    {
        /* set the new RX buffer pointer */
        /**
         @note Violates MISRA 2004 Advisory Rule 17.4
         - See @ref Dspi_LLD_c_REF_6
        */
        /*lint -save -e960*/
        DspiDev->CurrentRxBuffer += nFramesCount;
        /*lint -restore*/
        #if (SPI_FORCE_DATA_TYPE == STD_ON)
            if(SPI_DATA_WIDTH_16 ==
               DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
            {
                DspiDev->CurrentRxBuffer += nFramesCount;
            }
        #endif
        /* read the deserialized information */
        do
        {
            /*lint -save -e960 -e929*/
            #if (SPI_FORCE_DATA_TYPE == STD_ON)
                if(SPI_DATA_WIDTH_16 ==
                   DspiChannelAttributesConfig[*(DspiDev->CurrentChannelIndexPointer)].DataWidth)
                {
                    pBufferFullRX = (uint16 *) pBufferRx;
                    /**
                    @note False detection of MISRA 2004 Rule 11.4 violation
                    (cast from pointer to pointer)
                    */
                    *pBufferFullRX = (uint16)REG_READ32(pDspiPOPRAddress);

                    /**
                    @note Violates MISRA 2004 Advisory Rule 17.4
                        (pointer arithmetic by increment or decrement used)
                    - See @ref Dspi_LLD_c_REF_6
                    */
                    pBufferRx += 2u;
                }
                else
                {
                    /**
                    @note False detection of MISRA 2004 Rule 11.4 violation
                    (cast from pointer to pointer)
                    */
                    *pBufferRx = (Spi_DataType)REG_READ32(pDspiPOPRAddress);
                    /**
                    @note Violates MISRA 2004 Advisory Rule 17.4
                    (pointer arithmetic by increment or decrement used)
                    - See @ref Dspi_LLD_c_REF_6
                    */
                    pBufferRx++;
                }
            #else
                /**
                @note False detection of MISRA 2004 Rule 11.4 violation
                (cast from pointer to pointer)
                */
                *pBufferRx = (Spi_DataType)REG_READ32(pDspiPOPRAddress);
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4
                (pointer arithmetic by increment or decrement used)
                - See @ref Dspi_LLD_c_REF_6
                */
                pBufferRx++;
            #endif
            /*lint -restore*/
            nFramesCount--;
        } while ( 0u != nFramesCount);  /* TX_FIFO_SIZE = x */
        /* update current RX buffer pointer */
        DspiDev->CurrentRxBuffer = pBufferRx;
    }
    else
    {   /* discard the information read */
        do
        {
            /**
            @note False detection of MISRA 2004 Rule 11.4 violation
                  (cast from pointer to pointer)
            */
            /*lint -save -e929*/
            DspiReadDiscard = REG_READ32(pDspiPOPRAddress);
            /*lint -restore*/
            nFramesCount--;
        } while ( 0u != nFramesCount);
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if ((SPI_LEVEL_DELIVERED != LEVEL1) && (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON))
/**
@brief   Low-level initialize function.
@details Computes sequence / job configuration parameters like
         parameters like Baud Rate, CS, Clock polarity, etc.
         This cached values will be used in sync transmissions in
         order to optimize the time

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall not be LEVEL1
@pre  Pre-compile parameter SPI_OPTIMIZE_ONE_JOB_SEQUENCES shall be STD_ON.

@remarks Implements DSPI05101
*/
/*================================================================================================*/
FUNC (void, SPI_CODE) Spi_LLD_PrepareCacheInformation(void)
{
    VAR(Spi_ChannelType, AUTOMATIC) Channel, ChannelId;
    VAR(Spi_JobType, AUTOMATIC) Job;
    VAR(Spi_SequenceType, AUTOMATIC) Sequence;
    P2VAR(Spi_ChannelCacheAttrs, AUTOMATIC, SPI_VAR) pChannelAttrs;
    P2VAR(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR) pSeqAttrs;
    P2CONST(Spi_LLD_DeviceAttributesConfig, AUTOMATIC, SPI_VAR)
        pDeviceAttributesConfig;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequenceConfig;

    /* index to the first free entry in 'DspiSeqsAttributes' table. */
    VAR(Spi_SequenceType, AUTOMATIC) SeqsAttrCurrentIndex = 0u;

    /* index to the first free entry in 'DspiChannelsAttributes' table. */
    VAR(Spi_ChannelType, AUTOMATIC) ChannelsAttrCurrentIndex = 0u;


    /* reset all sequences as not optimized */
    for (Sequence = 0u;
         Sequence < SpiConfigPtr->Spi_Max_Sequence;
         Sequence++)
    {
        DspiOneJobSeqsOptimized[Sequence] = NULL_PTR;
    }

    for (Sequence = 0u;
         Sequence < SpiConfigPtr->Spi_Max_Sequence;
         Sequence++)
    {
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
     */
        pSequenceConfig = &SpiConfigPtr->SequenceConfig[Sequence];
        /* only one job sequences can be optimized */
        if (1u == pSequenceConfig->NumJobs)
        {
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
     */
      /*lint -save -e960*/
            Job = pSequenceConfig->JobIndexList[0];
            pJobConfig = &SpiConfigPtr->JobConfig[Job];
      /*lint -restore*/
            /* check if enough place in the cached data channel pool */
            if (pJobConfig->NumChannels <=
                (SPI_OPTIMIZED_CHANNEL_BUFFER_SIZE-ChannelsAttrCurrentIndex) )
            {
                /* get the first empty entry in the sequence pool and
                   link it to the sequence */
                pSeqAttrs = &DspiSeqsAttributes[SeqsAttrCurrentIndex];
                DspiOneJobSeqsOptimized[Sequence] = pSeqAttrs;

                /* retrieve the device configuration for the sequence */
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
     */
                pDeviceAttributesConfig =
                    &SpiConfigPtr->AttributesConfig->DeviceAttributesConfig
                        [SpiConfigPtr->JobConfig[Job].ExternalDevice];

                /* prepare sequence cache information */
                pSeqAttrs->NumChannels = pJobConfig->NumChannels;
                pSeqAttrs->JobState = &SpiJobState[Job];
                pSeqAttrs->DspiBaseAddress =
                    DspiDeviceState[pJobConfig->HWUnit].DspiBaseAddress;
                pSeqAttrs->JobDspiStatus =
                    DspiDeviceState[pJobConfig->HWUnit].pStatus;
     /**
      @note Violates MISRA 2004 Advisory Rule 10.5
      (Operators '~' and '<<' require recasting to underlying type for sub-integers)
      - See @ref Dspi_LLD_c_REF_8
     */
                pSeqAttrs->JobCMD =
                    pDeviceAttributesConfig->CMD | DSPI_CMD_CTAR_SEL;

                /* set the link to the first cached channel entry */
                pSeqAttrs->pChannels =
                    &DspiChannelsAttributes[ChannelsAttrCurrentIndex];

                /* prepare channel cache information */
                for (Channel = 0u;
                     Channel < pJobConfig->NumChannels;
                     Channel++)
                {
                    /**
                       @note Violates MISRA 2004 Advisory Rule 17.4
                       pointer arithmetic other than array indexing used)
                       - See @ref Dspi_LLD_c_REF_6
                    */
              /*lint -save -e960*/
                    ChannelId = pJobConfig->ChannelIndexList[Channel];
                    pChannelConfig = &SpiConfigPtr->ChannelConfig[ChannelId];
                    pChannelAttrs = &pSeqAttrs->pChannels[Channel];
              /*lint -restore*/
                    pChannelAttrs->DefaultTransmitValue =
                        pChannelConfig->DefaultTransmitValue;
                    pChannelAttrs->State = pChannelConfig->ChannelState;
                    pChannelAttrs->BufferDescriptor =
                        pChannelConfig->BufferDescriptor;
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
                    pChannelAttrs->CTAR[0] =
                        SpiConfigPtr->AttributesConfig->DeviceAttributesConfig
                            [pJobConfig->ExternalDevice].CTAR[0]
                        |
                        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig
                            [ChannelId].CMD;
                    pChannelAttrs->CTAR[1] =
                        SpiConfigPtr->AttributesConfig->DeviceAttributesConfig
                            [pJobConfig->ExternalDevice].CTAR[1]
                        |
                        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig
                            [ChannelId].CMD;
#else
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
    /*lint -save -e960*/
                    pChannelAttrs->CTAR =
                        SpiConfigPtr->AttributesConfig->DeviceAttributesConfig
                            [pJobConfig->ExternalDevice].CTAR
                        |
                        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig
                            [ChannelId].CMD;
     /*lint -restore*/
#endif
#if (SPI_FORCE_DATA_TYPE == STD_ON)
                    pChannelAttrs->DataWidth =
                            SpiConfigPtr->AttributesConfig->ChannelAttributesConfig
                                [ChannelId].DataWidth;
#endif
                } /* for (channels) */

                /* set the pool indexes to the new empty entries */
                SeqsAttrCurrentIndex++;
                ChannelsAttrCurrentIndex += pJobConfig->NumChannels;

                /* end the loop if caches are full */
                if ((SeqsAttrCurrentIndex >=
                        SPI_OPTIMIZED_SEQ_BUFFER_SIZE)
                    ||
                    (ChannelsAttrCurrentIndex >=
                        SPI_OPTIMIZED_CHANNEL_BUFFER_SIZE)
                   )
                {
                    break;
                }
            }
        }
    } /* for (sequences) */
}
#endif /* (SPI_LEVEL_DELIVERED != LEVEL1) && (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON) */

/**
@brief   Low-level initialize function.
@details Initialize the specific Spi unit with all configuration
         parameters like Baud Rate, CS, Clock polarity, etc.
         Also this function initializes all structure parameters
         from the specific DSPI unit.

@param[in]      HWUnit      Specifies which DSPI peripheral is used
@param[in]      AsyncMode   operation mode
                            (SPI_INTERRUPT_MODE | SPI_POLLING_MODE)
@param[in]      pStatus     pointer to the Autosar SPI HWUnit State

@remarks Implements DSPI03502
*/
/*================================================================================================*/
FUNC (void, SPI_CODE) Spi_LLD_Init(
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
    VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode,
    P2VAR(Spi_StatusType, AUTOMATIC, SPI_VAR) pStatus)
{
    P2CONST(Spi_LLD_DeviceAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiDeviceAttributesConfig;
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev;
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
    VAR(Spi_JobType, AUTOMATIC) Job;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) JobConfig;
    VAR(uint32, AUTOMATIC) MCR1;

    VAR(uint8, AUTOMATIC) HWoffset;

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
    /* Clock mode */
    Dspi_ClockMode = SPI_NORMAL;
#endif

    /* External device attributes */
    DspiDeviceAttributesConfig =
        SpiConfigPtr->AttributesConfig->DeviceAttributesConfig;

    /* Get physical device instances and link them */
    DspiDev = &DspiDeviceState[HWUnit];
   /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
   */
    HWUnitConfig = &SpiConfigPtr->HWUnitConfig[HWUnit];
    DspiDev->HWUnitConfig = HWUnitConfig;
    DspiDev->pStatus = pStatus;

    /* Peripheral Registers */
    HWoffset = HWUnitConfig->Offset;
    /**
    @note Violates MISRA 2004 Advisory Rules 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    /* cache frequently used DSPI adresses in order to have a quicker access */
    DspiDev->DspiBaseAddress = DSPI_GET_BASE_ADDRESS(HWoffset);
    DspiDev->pDspiPUSHRAddress =
        (P2VAR(uint32, AUTOMATIC, SPI_VAR))(DSPI_PUSHR(HWoffset));
    DspiDev->pDspiPOPRAddress =
        (P2VAR(uint32, AUTOMATIC, SPI_VAR))(DSPI_POPR(HWoffset));
    DspiDev->pDspiSRAddress =
        (P2VAR(uint32, AUTOMATIC, SPI_VAR))(DSPI_SR(HWoffset));
    DspiDev->pDspiCTARAddress =
        (P2VAR(uint32, AUTOMATIC, SPI_VAR))(DSPI_CTAR(HWoffset));
    /*lint -restore*/

    /* Determine chip select inactive states for each PCS */
    MCR1 = (DSPI_MCR_MSTR | DSPI_MCR_PCSIS_ALL);   /* high by default */
    for (Job = (Spi_JobType) 0;
        Job < (Spi_JobType) SpiConfigPtr->Spi_Max_Job; Job++)
    {
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
     */
        JobConfig = &SpiConfigPtr->JobConfig[Job];
        if (JobConfig->HWUnit == HWUnit)
        {
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
     */
            MCR1 = (uint32)(MCR1 & (
                    ~DspiDeviceAttributesConfig[JobConfig->ExternalDevice].MCR)
                   );
        }
    }

    /* SPI works as a Master and CS configured with inactive
       state as appropriate */
    /**
    @note Violates MISRA 2004 Advisory Rules 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    DSPI_LLM_MCR_CONFIG(HWoffset, MCR1);
    /*lint -restore*/

#if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) )
#if (SPI_DMA_USED == STD_ON)
    if (HWUnitConfig->UseDma)
    {
        /**
        @note Violates MISRA 2004 Advisory Rules 11.1
        - See @ref Dspi_LLD_c_REF_3
        */
        /*lint -save -e923*/
        DSPI_LLM_WRITE_RSER_REG(HWoffset,
            (DSPI_TFFF_RE_MASK | DSPI_TFFF_DIRS_MASK |
             DSPI_RFDF_RE_MASK | DSPI_RFDF_DIRS_MASK));
        /*lint -restore*/

        /* initialize DMA TCDs */
        Spi_LLD_InitDma(HWUnit, DspiDev);
    }
#endif /* (SPI_DMA_USED == STD_ON) */

        /* activate/deactivate EOQ interrupts for Async HWUnits */
        Spi_LLD_IrqConfig(HWUnit, AsyncMode);
#endif

}

/*================================================================================================*/
/**
@brief   IRQ configure functions.
@details Activate/deactivate EOQ interrupts for async HWUnit according to
         the driver operation mode (polling or interrupt)

@param[in]     HWUnit      Specifies which DSPI peripheral is used
@param[in]     AsyncMode   Specifies the operation mode
                            (SPI_INTERRUPT_MODE | SPI_POLLING_MODE)
*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
/*================================================================================================*/
FUNC (void, SPI_CODE) Spi_LLD_IrqConfig(
        VAR(Spi_HWUnitType, AUTOMATIC) HWUnit,
        VAR(Spi_AsyncModeType, SPI_VAR) AsyncMode)
{
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev =
        &DspiDeviceState[HWUnit];
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig =
        DspiDev->HWUnitConfig;
    VAR(uint8, AUTOMATIC) HWoffset = HWUnitConfig->Offset;

    /* set the async mode for the HWUnit */
    DspiDev-> AsyncMode = AsyncMode;

    /* activate/deactivate EOQ interrupts for Async HWUnits */
    if (SPI_PHYUNIT_ASYNC == HWUnitConfig->IsSync)
    {
#if (SPI_DMA_USED == STD_ON)
        if (HWUnitConfig->UseDma)
        {
            Spi_LLD_DmaIrqConfig(DspiDev, AsyncMode);
        }
        else
#endif /* SPI_DMA_USED == STD_ON */

        if (SPI_INTERRUPT_MODE == AsyncMode)
        {
            /**
            @note Violates MISRA 2004 Advisory Rules 11.1
            - See @ref Dspi_LLD_c_REF_3
            */
            /*lint -save -e923*/
            DSPI_LLM_ENABLE_EOQF(HWoffset);
            /*lint -restore*/
        }
        else
        {
            /**
            @note Violates MISRA 2004 Advisory Rules 11.1
            - See @ref Dspi_LLD_c_REF_3
            */
            /*lint -save -e923*/
            DSPI_LLM_DISABLE_EOQF(HWoffset);
            /*lint -restore*/
        }
    }
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2) ) */

/*================================================================================================*/
/**
@brief   IRQ polling functions.
@details Configures DMA unit to detect received data via
         interrupt or by polling a bit in the RSER register.

@param[in]     DspiDev     Specifies which DSPI peripheral is used

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2

@remarks Implements DSPI02330
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_IrqPoll(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
#if (SPI_DMA_USED == STD_ON)
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig =
        DspiDev->HWUnitConfig;
#endif

#if (SPI_DMA_USED == STD_ON)
    if (HWUnitConfig->UseDma)
    {
        /* Get status from TCD[7] register */
        /* Emulate IRQ */
        /**
        @note Violates MISRA 2004 Advisory Rules 11.1 & 11.4
        - See @ref Dspi_LLD_c_REF_3 & Dspi_LLD_c_REF_4
        */
        /*lint -save -e923 -e926 -e927 -e928 -e929*/
        if (0u != (LLM_Rd_DMA_TCDADDR_FLAGS(DspiDev->RxDmaTcd) & DMA_TCD_DONE))
        {
            LLM_Wr_DMA_CDNE(HWUnitConfig->RxDmaChannel);
            /*lint -restore*/
            Spi_LLD_IsrDmaRx(DspiDev);
        }
    }
    else
#endif /* (SPI_DMA_USED == STD_ON) */
    {
        /**
        @note False detection of MISRA 2004 Rule 11.4 violation
              (cast from pointer to pointer)
        */
        /*lint -save -e929*/
        if (0u != (REG_READ32(DspiDev->pDspiSRAddress) & DSPI_EOQF_STS_MASK))
        /*lint -restore*/
        {
            /* Emulate IRQ in PIO_FIFO mode */
            Spi_LLD_IsrFifoRx(DspiDev);
        }
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function performs the de-initialization of a specific
         peripheral unit
@details This function de-initializes all configured values
         in the MCR register and CTAR registers.

@param[in]     HWUnit      Specifies which DSPI peripheral is used

@remarks Implements DSPI03501
*/
/*================================================================================================*/
FUNC (void, SPI_CODE) Spi_LLD_DeInit(VAR(Spi_HWUnitType, AUTOMATIC) HWUnit)
{
    P2CONST(Spi_LLD_DeviceState, AUTOMATIC, SPI_CONST) DspiDev;
    VAR(uint8, AUTOMATIC) HWoffset;

    /* Get physical device handler */
    DspiDev = &DspiDeviceState[HWUnit];

    /* Pointer to peripheral registers */
    HWoffset = DspiDev->HWUnitConfig->Offset;

    /* Reset the DSPI Regs */
    /**
    @note Violates MISRA 2004 Advisory Rules 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    DSPI_LLM_MCR_RESET(HWoffset);
    DSPI_LLM_RESET_RSER_REG(HWoffset);
    DSPI_LLM_RESET_CTAR_REG(HWoffset);

    DSPI_LLM_RESET_FIFO_TX_REG(HWoffset);
    DSPI_LLM_RESET_TCR(HWoffset);
    DSPI_LLM_RESET_STATUS_REG(HWoffset);
    /*lint -restore*/
}

/*================================================================================================*/
/**
@brief   This function is called by EOQ ISRs for the DSPI units working
         in PIO_FIFO mode.
@details Non-AutoSar support function used by interrupt service
         routine. The function is used as a pseudo ISR for all the DSPI
         peripherals

@param[in]     DspiDev     Specifies which DSPI peripheral is used

@remarks Implements DSPI03512
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_IsrFifoRx(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    /* clear EOQ Flag, in order to unlock next TX transmission */
    /**
      @note False detection of MISRA 2004 Rule 11.4 violation
           (cast from pointer to pointer)
    */
    /*lint -save -e929*/
    REG_WRITE32(DspiDev->pDspiSRAddress, DSPI_EOQF_STS_MASK);
    /*lint -restore*/

    /* Copy data from DSPI FIFOD to channels */
    Spi_LLD_JobTransferFifoDrain(DspiDev);
    /**
     @note Violates MISRA 2004 Advisory Rule 12.6
     (boolean expression required for operator: '!'; the -strong(B,...) option
      can help provide Boolean-by-enforcement)
     - See @ref Dspi_LLD_c_REF_7
    */
    if (!DspiDev->IsEndOfJob)
    {
        /* check for the channel switch */
        if ( 0u == DspiDev->RemainingData )
        {
            /* reached the end of channel => move to the next channel */
            /* Increase Channel indexes */
            DspiDev->RemainingChannels--;
   /**
    @note Violates MISRA 2004 Advisory Rule 17.4
    (pointer arithmetic by increment or decrement used)
    - See @ref Dspi_LLD_c_REF_6
    */
            DspiDev->CurrentChannelIndexPointer++;

            /* prepare next channel transmission */
            Spi_LLD_ChannelTransferFifoInit(DspiDev,
                *(DspiDev->CurrentChannelIndexPointer));
        }

        /* perform the next chunk transmission */
        Spi_LLD_JobTransferFifoFill(DspiDev);
    }
    else
    {
        /* finish job transfer */
        Spi_JobTransferFinished(DspiDev->CurrentJob);
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function is called by DMA ISR for Rx DMA channels.
@details Non-AutoSar support function used by interrupt service
         routine. The function is used as a pseudo ISR for all the DSPI
         peripherals

@param[in]     DspiDev     Specifies which DSPI peripheral is used

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2
      and SPI_DMA_USED must be STD_ON

@remarks Implements DSPI03509
*/
/*================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)))
FUNC (void, SPI_CODE) Spi_LLD_IsrDmaRx(
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev)
{
    /**
    @note Violates MISRA 2004 Advisory Rules 11.1
    - See @ref Dspi_LLD_c_REF_3
    */
    /*lint -save -e923*/
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(DspiDev->HWUnitConfig->RxDmaChannel);
    /*lint -restore*/

    if ( 0u != DspiDev->RemainingData )
    {
        /* Channel not finished => update RX/TX pointers */
        Spi_LLD_JobTransferDmaContinue(DspiDev);
    }
    else
    {
        /* reached the end of channel => move to the next channel */
        if (0u != DspiDev->RemainingChannels)
        {
            /* Increase Channel indexes */
            DspiDev->RemainingChannels--;
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic by increment or decrement used)

     - See @ref Dspi_LLD_c_REF_6
    */
            DspiDev->CurrentChannelIndexPointer++;

            /* prepare next channel transmission */
            Spi_LLD_ChannelTransferDmaInit(DspiDev,
                *(DspiDev->CurrentChannelIndexPointer));
        }
        else
        {
            /* finish job transfer */
            Spi_JobTransferFinished(DspiDev->CurrentJob);
        }
    }
}
#endif /* ((SPI_DMA_USED == STD_ON) && ((SPI_LEVEL_DELIVERED == LEVEL1) ||
           (SPI_LEVEL_DELIVERED == LEVEL2))) */

/*================================================================================================*/
/**
@brief   This function sets the Job's attributes and send all the data
         through the SPI bus.
@details This function is in charge to setup the Job attribute,
         and to send all data though the SPI Bus.

@param[in]     pJobConfig    Specifies the Job for which we will set the
                           register values

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2

@remarks Implements DSPI03503
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
FUNC (void, SPI_CODE) Spi_LLD_JobTransfer(
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig)
{
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) pDspiDev =
        &DspiDeviceState[pJobConfig->HWUnit];
    P2CONST(Spi_ChannelType, AUTOMATIC, SPI_VAR) pChannelList =
            pJobConfig->ChannelIndexList;

#if (SPI_DUAL_CLOCK_MODE == STD_ON)
    pDspiDev->ExternalDeviceCTAR = pJobConfig->ExternalDeviceAttrs.CTAR[Dspi_ClockMode];
#else
    pDspiDev->ExternalDeviceCTAR = pJobConfig->ExternalDeviceAttrs.CTAR;
#endif

    /* setup job specific ctar and cmd */
    /**
     @note Violates MISRA 2004 Advisory Rule 10.5
     (Operators '~' and '<<' require recasting to underlying type for sub-integers)
     - See @ref Dspi_LLD_c_REF_8
    */
    pDspiDev->CurrentCmd = (pJobConfig->ExternalDeviceAttrs.CMD | DSPI_CMD_CTAR_SEL);

    /* initialize starting channel index */
    pDspiDev->CurrentChannelIndexPointer = pChannelList;
    pDspiDev->RemainingChannels = pJobConfig->NumChannels - (Spi_ChannelType) 1u;

    /* memorize the current job */
    pDspiDev->CurrentJob = pJobConfig;

#if (SPI_DMA_USED == STD_ON)
    if (pDspiDev->HWUnitConfig->UseDma)
    {
        /* initialize the transfer parameters for the first channel */
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
        Spi_LLD_ChannelTransferDmaInit(pDspiDev, pChannelList[0]);
    }
    else
#endif /* (SPI_DMA_USED == STD_ON) */
    {
        pDspiDev->IsEndOfJob = FALSE;

        /* initialize the transfer parameters for the first channel */
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
        Spi_LLD_ChannelTransferFifoInit(pDspiDev, pChannelList[0]);
        Spi_LLD_JobTransferFifoFill(pDspiDev);
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2)) */

/*================================================================================================*/
/**
@brief   This function starts the synchronous transmission for optimized
         sequences having only one job
@details This function is pre compile time selectable by the
         configuration parameter: SPI_LEVEL_DELIVERED. This function is only
         relevant for LEVEL 0 and LEVEL 2.
         Same behavior as Spi_SyncTransmit(), but the initialization time and
         data preparation time are optimized.

@param[in]     pSequence     Keep the cached information for "one job sequence"

@return Std_ReturnType
        - E_OK            Transmission command has been completed
        - E_NOT_OK        Transmission command has not been accepted

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL0 or LEVEL2
@pre  Pre-compile parameter SPI_OPTIMIZE_ONE_JOB_SEQUENCES shall be STD_ON

@remarks Implements DSPI03500, DSPI02311
*/
/*================================================================================================*/
#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
#if (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON)
FUNC (Std_ReturnType, SPI_CODE) Spi_LLD_SyncTransmit_Fast(
    P2CONST(Spi_SequenceCacheAttrs, AUTOMATIC, SPI_VAR) pSequence)
{
    P2VAR(Spi_ChannelCacheAttrs, AUTOMATIC, SPI_VAR) pChannel;
    VAR(Spi_ChannelType, AUTOMATIC) ChannelsCount;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferTX;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferRX;
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) pJobState = pSequence->JobState;
    VAR(uint32, AUTOMATIC) Timeout = SPI_TIMEOUT_COUNTER;
    VAR(uint32, AUTOMATIC) tempXferData;
    VAR(Std_ReturnType, AUTOMATIC) Status;
    VAR(uint32, SPI_VAR) DspiBaseAddress;
    VAR(Spi_NumberOfDataType, AUTOMATIC) LengthTX;
    VAR(Spi_NumberOfDataType, AUTOMATIC) LengthRX;
    VAR(uint32, AUTOMATIC) nEmptyPlaces;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullTX;
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullRX;
#endif

    /* retrieve the DSPI offset */
    DspiBaseAddress = pSequence->DspiBaseAddress;

    /* set the CMD part of the word to be transmitted */
    /**
     @note Violates MISRA 2004 Advisory Rule 10.5
     (Operators '~' and '<<' require recasting to underlying type for sub-integers)
     - See @ref Dspi_LLD_c_REF_8
     */
    tempXferData = pSequence->JobCMD;

    /* Set the job status as pending and mark HW Unit as busy */
    pJobState->Result = SPI_JOB_PENDING;
    *(pSequence->JobDspiStatus) = SPI_BUSY;

    /* iterate on all channels in job */
    pChannel = pSequence->pChannels;
    ChannelsCount = pSequence->NumChannels;
    while (ChannelsCount > (Spi_ChannelType)0)
    {
        ChannelsCount--;

        /**
        @note Violates MISRA 2004 Advisory Rules 11.1
        - See @ref Dspi_LLD_c_REF_3
        */
        /*lint -save -e923*/
        /* set CTAR register */
        /**
            @remarks The call is blocking till the HWUnit exits
                     the running state.
        */
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
        REG_WRITE32(DSPI_BASEADDR2CTAR(DspiBaseAddress), pChannel->CTAR[Dspi_ClockMode]);
#else
        REG_WRITE32(DSPI_BASEADDR2CTAR(DspiBaseAddress), pChannel->CTAR);
#endif
        /*lint -restore*/

        /* retrieve RX/TX buffers and the transmitted/received lengths */
        if (pChannel->State->Flags & ((uint8)SPI_CHANNEL_FLAG_TX_DEFAULT))
        {
            pBufferTX = NULL_PTR;
        }
        else
        {
            pBufferTX = pChannel->BufferDescriptor->BufferTX;
        }
        pBufferRX = pChannel->BufferDescriptor->BufferRX;

        LengthTX = pChannel->State->Length;
    #if (SPI_FORCE_DATA_TYPE == STD_ON)
        if (SPI_DATA_WIDTH_16 == pChannel->DataWidth)
        {
            LengthTX = LengthTX/2u;
        }
    #endif
        LengthRX = LengthTX;

        Timeout = SPI_TIMEOUT_COUNTER;
        nEmptyPlaces = SPI_FIFO_SIZE;

        /* while there is still something to read or to write */
        /* a kind of: while ((LengthTX > 0) || (LengthRX > 0)) */
        while ((LengthTX | LengthRX) > 0u)
        {
            VAR(uint32, AUTOMATIC) StatusReset = 0u;

            /* --------- Transmit ---------- */
            /* there is something to write and Transmit FIFO not full */
            if ((LengthTX > 0u) && (nEmptyPlaces > 0u))
            {
                LengthTX--;
                nEmptyPlaces--;

                /* reset the timeout */
                Timeout = SPI_TIMEOUT_COUNTER;

                /* prepare the data to be transmitted */
                /**
                 @note Violates MISRA 2004 Advisory Rule 12.6
                 (boolean expression required for operator: '!'; the -strong(B,...) option can
                 help provide Boolean-by-enforcement)
                 - See @ref Dspi_LLD_c_REF_7
                */
                if (!pBufferTX)
                {
                    /** @remarks Implements DSPI02306 */
                    /* Get default data if TX buffer is NULL_PTR */

                    tempXferData =
                        (tempXferData & DSPI_TX_CMD_MASK) |
                        pChannel->DefaultTransmitValue;
                }
                else
                {
                    /* Read transmit data */
                    /**
                    @note Violates MISRA 2004 Advisory Rules 11.1
                    - See @ref Dspi_LLD_c_REF_3
                    */
                    /*lint -save -e923 -e960*/
                    #if (SPI_FORCE_DATA_TYPE == STD_ON)
                        if (SPI_DATA_WIDTH_16 == pChannel->DataWidth)
                        {
                            /**
                            @note Violates MISRA 2004 Advisory Rules 11.1
                            - See @ref Dspi_LLD_c_REF_3
                            */
                            pBufferFullTX = (uint16 *) pBufferTX;
                            tempXferData =
                                (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferFullTX);

                            /**
                            @note Violates MISRA 2004 Advisory Rule 17.4
                            (pointer arithmetic by increment or decrement used)
                               - See @ref Dspi_LLD_c_REF_6
                            */
                            pBufferTX++;
                        }
                        else
                        {
                            /**
                            @note Violates MISRA 2004 Advisory Rules 11.1
                            - See @ref Dspi_LLD_c_REF_3
                            */
                            tempXferData =
                                (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferTX);
                        }
                    #else
                        /**
                          @note Violates MISRA 2004 Advisory Rules 11.1
                          - See @ref Dspi_LLD_c_REF_3
                        */
                        tempXferData =
                        (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferTX);
                    #endif
                    /**
                   @note Violates MISRA 2004 Advisory Rule 17.4
                   (pointer arithmetic by increment or decrement used)
                    - See @ref Dspi_LLD_c_REF_6
                    */
                    pBufferTX++;
                    /*lint -restore*/
                }

                /* For the last frame, clear the continous CS assertion */
                /* a kind of: if ((0u == LengthTX) && (0u == ChannelsCount) )*/
                if (0u == (LengthTX | ChannelsCount))
                {
                    tempXferData = tempXferData & ~DSPI_CONT_MASK;
                }

                /* Transmit the data */
                /**
                @note Violates MISRA 2004 Advisory Rules 11.1
                - See @ref Dspi_LLD_c_REF_3
                */
                /*lint -save -e923*/
                REG_WRITE32(DSPI_BASEADDR2PUSHR(DspiBaseAddress), tempXferData);
                /*lint -restore*/

                /* Transmit FIFO Fill Flag must be reset */
                StatusReset |= DSPI_TFFF_STS_MASK;
            }

            /* --------- Receive ---------- */
            /* there is still something to read and Receive FIFO has data */
            if (LengthRX > 0u)
            {
            /**
                @note Violates MISRA 2004 Advisory Rules 11.1
                - See @ref Dspi_LLD_c_REF_3
                */
                /*lint -save -e923*/
                 if (0u != ((REG_READ32(
                     DSPI_BASEADDR2SR(DspiBaseAddress))) & DSPI_RFDF_STS_MASK)
                    )
                /*lint -restore*/
                {
                    LengthRX--;
                    nEmptyPlaces++;

                    /* reset the timeout */
                    Timeout = SPI_TIMEOUT_COUNTER;

                    /* Read Data from RX FIFO */
                    /**
                       @note Violates MISRA 2004 Advisory Rule 12.6
                       (boolean expression required for operator: '!'; the -strong(B,...)
                       option can help provide Boolean-by-enforcement)
                       - See @ref Dspi_LLD_c_REF_7
                    */
                    if (!pBufferRX)
                    {
                        /** @remarks Implements DSPI02306 */
                        /* discard data if RX buffer is NULL_PTR */
                        /**
                        @note Violates MISRA 2004 Advisory Rules 11.1
                        - See @ref Dspi_LLD_c_REF_3
                        */
                        /*lint -save -e923*/
                        DspiReadDiscard = REG_READ32(
                                        DSPI_BASEADDR2POPR(DspiBaseAddress));
                        /*lint -restore*/
                    }
                    else
                    {
                        /*lint -save -e923 -e960*/
                        #if (SPI_FORCE_DATA_TYPE == STD_ON)
                            if (SPI_DATA_WIDTH_16 == pChannel->DataWidth)
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rules 11.1
                                - See @ref Dspi_LLD_c_REF_3
                               */
                                pBufferFullRX = (uint16 *) pBufferRX;
                                *pBufferFullRX = (uint16)REG_READ32(
                                    DSPI_BASEADDR2POPR(DspiBaseAddress));

                                /**
                                @note Violates MISRA 2004 Advisory Rule 17.4
                                    (pointer arithmetic by increment or decrement used)
                                - See @ref Dspi_LLD_c_REF_6
                                */
                                pBufferRX += 2u;
                            }
                            else
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rules 11.1
                                - See @ref Dspi_LLD_c_REF_3
                                */
                                *pBufferRX = (Spi_DataType)REG_READ32(
                                            DSPI_BASEADDR2POPR(DspiBaseAddress));

                                /**
                                @note Violates MISRA 2004 Advisory Rule 17.4
                                (pointer arithmetic by increment or decrement used)
                                    - See @ref Dspi_LLD_c_REF_6
                            */
                                pBufferRX++;
                            }
                        #else
                            /**
                            @note Violates MISRA 2004 Advisory Rules 11.1
                            - See @ref Dspi_LLD_c_REF_3
                            */
                            *pBufferRX = (Spi_DataType)REG_READ32(
                                DSPI_BASEADDR2POPR(DspiBaseAddress));
                            /**
                            @note Violates MISRA 2004 Advisory Rule 17.4
                            (pointer arithmetic by increment or decrement used)
                            - See @ref Dspi_LLD_c_REF_6
                            */
                             pBufferRX++;
                        #endif
                        /*lint -restore*/
                    }
                    /* Receive FIFO Drain Flag must be reset */
                    StatusReset |= DSPI_RFDF_STS_MASK;
                }
            }

            /**
            @note Violates MISRA 2004 Advisory Rules 11.1
            - See @ref Dspi_LLD_c_REF_3
            */
            /*lint -save -e923*/
            REG_WRITE32(DSPI_BASEADDR2SR(DspiBaseAddress), StatusReset);
            /*lint -restore*/

            Timeout--;
            /* end the loop if timeout expired */
            if (0u == Timeout)
            {
                /* force the end of the outer loop too */
                ChannelsCount = 0U;
                break;
            }
        } /* while ((LengthTX > 0) || (LengthRX > 0)) */
        /**
           @note Violates MISRA 2004 Advisory Rule 17.4
              (pointer arithmetic by increment or decrement used)

       - See @ref Dspi_LLD_c_REF_6
        */
        pChannel++;
    } /* while (ChannelsCount) */

    /* release the HW Unit */
    *(pSequence->JobDspiStatus) = SPI_IDLE;

    if (Timeout > 0u)
    {
        /* Job is done set the status as OK */
        pJobState->Result = SPI_JOB_OK;
        Status = (Std_ReturnType)E_OK;
    }
    else
    {
        /* Timeout expired => transmission failed */
        /* set the Job status as FAILED */
        pJobState->Result = SPI_JOB_FAILED;
        Status = (Std_ReturnType)E_NOT_OK;
        /* Call Dem_ReportErrorStatus. */
        Dem_ReportErrorStatus((Dem_EventIdType) SPI_E_TIMEOUT,
            DEM_EVENT_STATUS_FAILED);
    }

    return Status;
}
#endif /* (SPI_OPTIMIZE_ONE_JOB_SEQUENCES == STD_ON) */
#endif /* ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) ) */

/*================================================================================================*/
/**
@brief   This function performs the synchronous transmission for a sequence
@details This function is pre compile time selectable by the
         configuration parameter: SPI_LEVEL_DELIVERED. This function is only
         relevant for LEVEL 0 and LEVEL 2.

@param[in]     Sequence      Specifies the sequence for which we will have
                             the synchronous transmission

@return Std_ReturnType
        - E_OK            Transmission command has been completed
        - E_NOT_OK        Transmission command has not been accepted

@pre  Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL0 or LEVEL2

@remarks Implements DSPI03500, DSPI02311
*/
/*================================================================================================*/
#if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) )
FUNC (Std_ReturnType, SPI_CODE) Spi_LLD_SyncTransmit(
    VAR(Spi_SequenceType, AUTOMATIC) Sequence)
{
    P2CONST(Spi_SequenceConfig, AUTOMATIC, SPI_CONST) pSequenceConfig;
    P2CONST(Spi_ChannelConfig, AUTOMATIC, SPI_CONST) pChannelConfig;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2VAR(Spi_LLD_DeviceState, AUTOMATIC, SPI_VAR) DspiDev;
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
        DspiChannelAttributesConfig;
    VAR(Spi_JobType, AUTOMATIC) JobsCount;
    VAR(Spi_JobType, AUTOMATIC) Job;
    P2CONST(Spi_JobType, AUTOMATIC, SPI_VAR) pJobIndexList;
    P2CONST(Spi_ChannelType, AUTOMATIC, SPI_VAR) pChannelIndexList;
    VAR(Spi_ChannelType, AUTOMATIC) ChannelsCount;
    VAR(uint32, AUTOMATIC) Timeout = SPI_TIMEOUT_COUNTER;
    VAR(uint32, AUTOMATIC) tempXferData;
    VAR(Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType)E_OK;
    P2VAR(Spi_JobState, AUTOMATIC, SPI_VAR) pJobState;
    P2VAR(Spi_ChannelState, AUTOMATIC, SPI_VAR) pChannelState;
    VAR(Spi_ChannelType, AUTOMATIC) Channel;
    VAR(uint32, SPI_VAR) DspiBaseAddress;
    VAR(Spi_NumberOfDataType, AUTOMATIC) LengthTX;
    VAR(Spi_NumberOfDataType, AUTOMATIC) LengthRX;
    VAR(uint32, AUTOMATIC) Ctar;
    VAR(uint32, AUTOMATIC) nEmptyPlaces;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferTX;
    P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR) pBufferRX;
#if (SPI_FORCE_DATA_TYPE == STD_ON)
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullTX;
    P2VAR(uint16, AUTOMATIC, SPI_VAR) pBufferFullRX;
#endif
    /* Get sequence configuration */
    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
    pSequenceConfig = &SpiConfigPtr->SequenceConfig[Sequence];

    /* Get Channel Attributes */
    DspiChannelAttributesConfig =
        SpiConfigPtr->AttributesConfig->ChannelAttributesConfig;

    /* Get the number of jobs in the sequence */
    JobsCount = pSequenceConfig->NumJobs;

    pJobIndexList = pSequenceConfig->JobIndexList;
    while (JobsCount > 0u)
    {
        /* Get the job id */
        Job = *pJobIndexList;

        /* Set the job status as pending */
        pJobState = &SpiJobState[Job];
        pJobState->Result = SPI_JOB_PENDING;

    /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
        pJobConfig = &SpiConfigPtr->JobConfig[Job];
        DspiDev = &DspiDeviceState[pJobConfig->HWUnit];

        /* mark HW unit as busy */
        *(DspiDev->pStatus) = SPI_BUSY;

        /* retrieve the DSPI offset */
        DspiBaseAddress = DspiDev->DspiBaseAddress;

        /* retrieve the CTAR setting for the corresponding external device */
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
        Ctar = pJobConfig->ExternalDeviceAttrs.CTAR[Dspi_ClockMode];
#else
        Ctar = pJobConfig->ExternalDeviceAttrs.CTAR;
#endif

        /* set the CMD part of the word to be transmitted */
        /**
             @note Violates MISRA 2004 Advisory Rule 10.5
            (Operators '~' and '<<' require recasting to underlying type for sub-integers)
             - See @ref Dspi_LLD_c_REF_8
             */
        tempXferData = (pJobConfig->ExternalDeviceAttrs.CMD | DSPI_CMD_CTAR_SEL);

        /* iterate on all channels in job */
        ChannelsCount = pJobConfig->NumChannels;
        pChannelIndexList = pJobConfig->ChannelIndexList;
        while (ChannelsCount > (Spi_ChannelType)0)
        {
            ChannelsCount--;

            /* Get the channel ID & configuration */
            Channel = *pChannelIndexList;
     /**
     @note Violates MISRA 2004 Advisory Rule 17.4
     (pointer arithmetic other than array indexing used)
     - See @ref Dspi_LLD_c_REF_6
    */
            pChannelConfig = &SpiConfigPtr->ChannelConfig[Channel];
            pChannelState = pChannelConfig->ChannelState;

            /**
            @note Violates MISRA 2004 Advisory Rules 11.1,17.4
            - See @ref Dspi_LLD_c_REF_3,
            - See @ref Dspi_LLD_c_REF_6
            */
            /*lint -save -e923 -e960*/
            /* set CTAR register */
            /**
                @remarks The call is blocking till the HWUnit exits
                         the running state.
            */
            REG_WRITE32(DSPI_BASEADDR2CTAR(DspiBaseAddress),
                (Ctar | DspiChannelAttributesConfig[Channel].CMD));
            /*lint -restore*/

            /* retrieve RX/TX buffers and the transmitted/received lengths */
            if (pChannelState->Flags & ((uint8)SPI_CHANNEL_FLAG_TX_DEFAULT))
            {
                pBufferTX = NULL_PTR;
            }
            else
            {
                pBufferTX = pChannelConfig->BufferDescriptor->BufferTX;
            }
            pBufferRX = pChannelConfig->BufferDescriptor->BufferRX;

            LengthTX = pChannelState->Length;
            #if (SPI_FORCE_DATA_TYPE == STD_ON)
                if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
                {
                    LengthTX = LengthTX/2u;
                }
            #endif
            LengthRX = LengthTX;

            Timeout = SPI_TIMEOUT_COUNTER;
            nEmptyPlaces = SPI_FIFO_SIZE;

            /* while there is still something to read or to write */
            /* a kind of: while ((LengthTX > 0) || (LengthRX > 0)) */
            while ((LengthTX | LengthRX) > 0u)
            {
                VAR(uint32, AUTOMATIC) StatusReset = 0u;

                /* --------- Transmit ---------- */
                /* there is something to write and Transmit FIFO not full */
                if ((LengthTX > 0u) && (nEmptyPlaces > 0u))
                {
                    LengthTX--;
                    nEmptyPlaces--;

                    /* reset the timeout */
                    Timeout = SPI_TIMEOUT_COUNTER;

                    /* prepare the data to be transmitted */
                    /**
                       @note Violates MISRA 2004 Advisory Rule 12.6
                       (boolean expression required for operator: '!'; the -strong(B,...) option can
                       help provide Boolean-by-enforcement)
                       - See @ref Dspi_LLD_c_REF_7
                    */
                    if (!pBufferTX)
                    {
                        /** @remarks Implements DSPI02306 */
                        /* Get default data if TX buffer is NULL_PTR */

                        tempXferData =
                            (tempXferData & DSPI_TX_CMD_MASK) |
                            pChannelConfig->DefaultTransmitValue;
                    }
                    else
                    {
                        /* Read transmit data */
                        /**
                        @note Violates MISRA 2004 Advisory Rules 11.1
                        - See @ref Dspi_LLD_c_REF_3
                        */
                        /*lint -save -e923 -e960*/
                        #if (SPI_FORCE_DATA_TYPE == STD_ON)
                            if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rules 11.1
                                - See @ref Dspi_LLD_c_REF_3
                                */
                                pBufferFullTX = (uint16 *) pBufferTX;
                                tempXferData =
                                (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferFullTX);
                            }
                            else
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rules 11.1
                                - See @ref Dspi_LLD_c_REF_3
                                */
                                tempXferData =
                                    (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferTX);
                            }
                        #else
                            /**
                            @note Violates MISRA 2004 Advisory Rules 11.1
                            - See @ref Dspi_LLD_c_REF_3
                            */
                            tempXferData =
                            (tempXferData & DSPI_TX_CMD_MASK) | (*pBufferTX);
                        #endif

                        /**
                         @note Violates MISRA 2004 Advisory Rule 17.4
                               (pointer arithmetic by increment or decrement used)

                         - See @ref Dspi_LLD_c_REF_6
                        */
                        pBufferTX++;
                    #if (SPI_FORCE_DATA_TYPE == STD_ON)
                        if (SPI_DATA_WIDTH_16 == DspiChannelAttributesConfig[Channel].DataWidth)
                        {
                            pBufferTX++;
                        }
                    #endif
                        /*lint -restore*/
                    }

                    /* For the last frame, clear the continous CS assertion */
                    /* a kind of: ((0u == LengthTX) && (0u == ChannelsCount))*/
                    if (0u == (LengthTX | ChannelsCount))
                    {
                        /* clear the continuous CS assertion */
                        tempXferData = tempXferData & ~DSPI_CONT_MASK;
                    }

                   /* Transmit the data */
                    /**
                    @note Violates MISRA 2004 Advisory Rules 11.1
                    - See @ref Dspi_LLD_c_REF_3
                    */
                    /*lint -save -e923*/
                    REG_WRITE32(DSPI_BASEADDR2PUSHR(DspiBaseAddress),
                                tempXferData);
                    /*lint -restore*/

                    /* Transmit FIFO Fill Flag must be reset */
                    StatusReset |= DSPI_TFFF_STS_MASK;
                }

                /* --------- Receive ---------- */
                /* there is still something to read and Receive FIFO has data */
                if (LengthRX > 0u)
                {
                    /**
                    @note Violates MISRA 2004 Advisory Rules 11.1
                    - See @ref Dspi_LLD_c_REF_3
                    */
                    /*lint -save -e923*/
                    if (0u !=
                        ((REG_READ32(DSPI_BASEADDR2SR(DspiBaseAddress))) &
                            DSPI_RFDF_STS_MASK)
                       )
                    /*lint -restore*/
                    {
                        LengthRX--;
                        nEmptyPlaces++;

                        /* reset the timeout */
                        Timeout = SPI_TIMEOUT_COUNTER;

                        /* Read Data from RX FIFO */
                        /**
                            @note Violates MISRA 2004 Advisory Rule 12.6
                        (boolean expression required for operator: '!'; the -strong(B,...) option
                         can help provide Boolean-by-enforcement)
                        - See @ref Dspi_LLD_c_REF_7
                        */
                        if (!pBufferRX)
                        {
                            /** @remarks Implements DSPI02306 */
                            /* discard data if RX buffer is NULL_PTR */
                            /**
                            @note Violates MISRA 2004 Advisory Rules 11.1
                            - See @ref Dspi_LLD_c_REF_3
                            */
                            /*lint -save -e923*/
                            DspiReadDiscard = REG_READ32(
                                    DSPI_BASEADDR2POPR(DspiBaseAddress));
                            /*lint -restore*/
                        }
                        else
                        {
                            /*lint -save -e923 -e960*/
                            #if (SPI_FORCE_DATA_TYPE == STD_ON)
                                if (SPI_DATA_WIDTH_16 ==
                                    DspiChannelAttributesConfig[Channel].DataWidth)
                                {
                                    /**
                                    @note Violates MISRA 2004 Advisory Rules 11.1
                                    - See @ref Dspi_LLD_c_REF_3
                                    */
                                    pBufferFullRX = (uint16 *) pBufferRX;
                                    *pBufferFullRX = (uint16)REG_READ32(
                                            DSPI_BASEADDR2POPR(DspiBaseAddress));

                                    /**
                                    @note Violates MISRA 2004 Advisory Rule 17.4
                                    (pointer arithmetic by increment or decrement used)
                                    - See @ref Dspi_LLD_c_REF_6
                                    */
                                    pBufferRX += 2u;
                                }
                                else
                                {
                                    /**
                                    @note Violates MISRA 2004 Advisory Rules 11.1
                                    - See @ref Dspi_LLD_c_REF_3
                                    */
                                    *pBufferRX = (Spi_DataType)REG_READ32(
                                            DSPI_BASEADDR2POPR(DspiBaseAddress));
                                    /**
                                    @note Violates MISRA 2004 Advisory Rule 17.4
                                    (pointer arithmetic by increment or decrement used)
                                    - See @ref Dspi_LLD_c_REF_6
                                    */
                                    pBufferRX++;
                                }
                            #else
                                /**
                                @note Violates MISRA 2004 Advisory Rules 11.1
                                - See @ref Dspi_LLD_c_REF_3
                                */
                                *pBufferRX = (Spi_DataType)REG_READ32(
                                        DSPI_BASEADDR2POPR(DspiBaseAddress));
                                /**
                                @note Violates MISRA 2004 Advisory Rule 17.4
                                (pointer arithmetic by increment or decrement used)
                                - See @ref Dspi_LLD_c_REF_6
                                */

                                pBufferRX++;
                            #endif
                            /*lint -restore*/
                        }

                        /* Receive FIFO Drain Flag must be reset */
                        StatusReset |= DSPI_RFDF_STS_MASK;
                    }
                }

                /**
                @note Violates MISRA 2004 Advisory Rules 11.1
                - See @ref Dspi_LLD_c_REF_3
                */
                /*lint -save -e923*/
                REG_WRITE32(DSPI_BASEADDR2SR(DspiBaseAddress), StatusReset);
                /*lint -restore*/

                Timeout--;
                /* end the loop if timeout expired */
                if (0u == Timeout)
                {
                    /* force the end of the outer loop too */
                    ChannelsCount = 0U;
                    break;
                }
            } /* while ((LengthTX > 0) || (LengthRX > 0)) */

            /**
             @note Violates MISRA 2004 Advisory Rule 17.4
             (pointer arithmetic by increment or decrement used)

             - See @ref Dspi_LLD_c_REF_6
            */
            pChannelIndexList++;
        } /* while (ChannelsCount) */

        /* release the HW unit */
        *(DspiDev->pStatus) = SPI_IDLE;

        if (Timeout > 0U)
        {
            /* Job is done set the status as OK */
            pJobState->Result = SPI_JOB_OK;
        }
        else
        {
            /* Timeout expired => transmission failed */
            /* set the remaining job status (including the current one) as FAILED */
            do
            {
                /* Set the job status as FAILED */
                SpiJobState[*pJobIndexList].Result = SPI_JOB_FAILED;
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4
                (pointer arithmetic by increment or decrement used)
                - See @ref Dspi_LLD_c_REF_6
                */
                pJobIndexList++;
                JobsCount--;
            } while (JobsCount > 0u);
            JobsCount = 1u;  /* needed to end correctly the outer loop */
            Status = (Std_ReturnType)E_NOT_OK;
        }

        /* iterate to next job in sequence */
        /**
         @note Violates MISRA 2004 Advisory Rule 17.4
         (pointer arithmetic by increment or decrement used)
         - See @ref Dspi_LLD_c_REF_6
         */
        pJobIndexList++;
        JobsCount--;
    } /* while (JobsCount > 0u) */

    if ((Std_ReturnType)E_OK != Status)
    {
        /* Call Dem_ReportErrorStatus. */
        Dem_ReportErrorStatus((Dem_EventIdType) SPI_E_TIMEOUT,
                              DEM_EVENT_STATUS_FAILED);
    }
    return Status;
}
#endif /* #if ( (SPI_LEVEL_DELIVERED == LEVEL2) || (SPI_LEVEL_DELIVERED == LEVEL0) ) */

#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
/**
@brief   Low-level timed serial bus mode setting function.
@details Initialize all the Spi units with CSI configuration.
         Also configure the master configuration register for
         parameters like DSPI configuration, continuos clock enable,
         master mode selection etc.

@param[in]  Spi_JobType  Job to be configured in TSB mode

@remarks Implements DSPI08000
*/
FUNC (void, SPI_CODE) Spi_LLD_SetTSBMode(
       VAR(Spi_JobType, AUTOMATIC) TSBJob)
{

    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    VAR(uint8, AUTOMATIC) HWoffset;
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2CONST(Spi_TSBConfig, AUTOMATIC, SPI_CONST) pJobTSBConfig;
    VAR(uint32, AUTOMATIC) SpiNormalJob;
    VAR(uint32, AUTOMATIC) MCR;
    VAR(uint32, AUTOMATIC) DSICR;
    VAR(uint32, AUTOMATIC) DSICR1;
    VAR(uint32, AUTOMATIC) CTAR;

    pJobTSBConfig = &SpiJobTSBConfig[TSBJob];
    SpiNormalJob = pJobTSBConfig->Spi_TSB_Job;

    pJobConfig = &SpiConfigPtr->JobConfig[SpiNormalJob];


    /* Logical Spi HWUnit */
    HWUnit = pJobConfig->HWUnit;
    HWUnitConfig = &SpiConfigPtr->HWUnitConfig[HWUnit];
    /* Peripheral Registers */
    HWoffset = HWUnitConfig->Offset;

    MCR = REG_READ32(DSPI_MCR(HWoffset));
    /*2) configuration of DSPI_MCR*/
    /* Master mode selection*/
    /* Determine chip select inactive states for each PCS */  /* high by default */
    /* CSI configuration of the DSPI*/
    /* Enable Transmit FIFO*/
    /* Disable Transmit FIFO.*/
    /* Continuous SCK Enable*/
    /* HALT = 1; stop transfers*/
    MCR = ((MCR & DSPI_MCR_PCSIS_ALL) | DSPI_MCR_MSTR | DSPI_MCR_DCONF_CSI
            | DSPI_MCR_RX_FIFO | DSPI_MCR_CONT_SCKE | DSPI_MCR_HALT);


    DSPI_LLM_MCR_CONFIG(HWoffset, MCR);

    /*2) configuration of DSPI_DSICR*/
    /*Timed Serial Bus Configuration enabled*/
    /*ctar3 selection*/

    /*3)Set DSPI_DSICR attributes Transmit Data Source(TXSS), Change in data transfer(CID),
        DSI peripheral Chip Select(DPCSx)*/
    DSICR = pJobTSBConfig->ExternalDeviceTSBAttrs.DSICR;
    DSPI_LLM_DSICR_CONFIG(HWoffset, (DSICR|DSPI_DSICR_TSBC|DSPI_DSICR_DSICTAS_CTAR3));

    /*4)Set DSPI_DSICR1 attributes Timed Serial Bus Operation Count(TSBCNT),
        Peripheral chip select for the seocnd part of the frame with dual receiver */
    DSICR1 = pJobTSBConfig->ExternalDeviceTSBAttrs.DSICR1;
    DSPI_LLM_DSICR1_CONFIG(HWoffset, DSICR1);

     /*5)Set ctar3 attributes*/

    /*Update the ctar3 based on clock mode selected*/
    #if (SPI_DUAL_CLOCK_MODE == STD_ON)
    CTAR = pJobTSBConfig->ExternalDeviceTSBAttrs.CTAR[Dspi_ClockMode];
    #else
    CTAR = pJobTSBConfig->ExternalDeviceTSBAttrs.CTAR;
    #endif
    DSPI_LLM_WR_CTAR3_CONFIG(HWoffset, CTAR);
    /*LSB first, when operating in TSB configuration, this bit
    should be set to be compliant to MSC specification*/
    DSPI_LLM_CTAR3_WR_LSBFE(HWoffset);

    /*6) Start transfer*/
    DSPI_LLM_MCR_HALT_CLEAR(HWoffset);
}

/**
@brief   Low-level timed serial bus mode deinitialisation function.
@details DSPI hardware is deinitialised to master and SPI mode

@param[in]     Spi_JobType Job configured in TSB mode

@remarks Implements DSPI08000
*/
FUNC (void, SPI_CODE) Spi_LLD_StopTSBMode(
       VAR(Spi_JobType, AUTOMATIC) TSBJob)
{
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2CONST(Spi_TSBConfig, AUTOMATIC, SPI_CONST) pJobTSBConfig;
    VAR(uint32, AUTOMATIC) SpiNormalJob;

    pJobTSBConfig = &SpiJobTSBConfig[TSBJob];
    SpiNormalJob = pJobTSBConfig->Spi_TSB_Job;

    pJobConfig = &SpiConfigPtr->JobConfig[SpiNormalJob];

    /* Logical Spi HWUnit */
    HWUnit = pJobConfig->HWUnit;

    /* De- initialize the DSPI driver */
    Spi_LLD_DeInit(HWUnit);

    /* Reset configuration pointer */
    SpiConfigPtr = NULL_PTR;
}
/**
@brief   Low-level ASDR write register while in  timed serial bus mode
@details Low-level ASDR write register while in  timed serial bus mode

@param[in]     Spi_JobType Job configured in TSB mode

@remarks Implements DSPI08000
*/
FUNC (void, SPI_CODE) Spi_LLD_TSB_ASDR_DataUpdate(
       VAR(Spi_JobType, AUTOMATIC) TSBJob,
       VAR(uint32, SPI_VAR) ASDR_Data)
{
    VAR(Spi_HWUnitType, AUTOMATIC) HWUnit;
    VAR(uint8, AUTOMATIC) HWoffset;
    P2CONST(Spi_HWUnitConfig, AUTOMATIC, SPI_CONST) HWUnitConfig;
    P2CONST(Spi_JobConfig, AUTOMATIC, SPI_CONST) pJobConfig;
    P2CONST(Spi_TSBConfig, AUTOMATIC, SPI_CONST) pJobTSBConfig;
    VAR(uint32, AUTOMATIC) SpiNormalJob;

    pJobTSBConfig = &SpiJobTSBConfig[TSBJob];
    SpiNormalJob = pJobTSBConfig->Spi_TSB_Job;

    pJobConfig = &SpiConfigPtr->JobConfig[SpiNormalJob];

    /* Logical Spi HWUnit */
    HWUnit = pJobConfig->HWUnit;
    HWUnitConfig = &SpiConfigPtr->HWUnitConfig[HWUnit];
    /* Peripheral Registers */
    HWoffset = HWUnitConfig->Offset;

    /*Update data on ASDR register*/
    DSPI_LLM_ASDR_CONFIG(HWoffset, ASDR_Data);

}
#endif /*(SPI_TSB_MODE == STD_ON)*/
#endif /*TSB_MODE_SUPPORTED*/
/*================================================================================================*/
#define SPI_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Dspi_LLD_c_REF_1 & @ref Dspi_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
