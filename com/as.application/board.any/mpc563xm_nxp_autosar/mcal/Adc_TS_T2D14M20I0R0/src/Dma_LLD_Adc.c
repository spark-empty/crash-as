/**
    @file        Dma_LLD.c
    @version     2.0.0

    @brief       AUTOSAR Adc - eDMA low level driver.
    @details     eDMA low level driver functions used by MCAL drivers.

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : ADC_10B
    Dependencies : none

    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section DMA_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
MemMap.h included after each section define in order to set the current memory section
@section DMA_LLD_C_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a 
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003
@section DMA_LLD_C_REF_3
Violates MISRA 2004 Rule 11.1, Conversions shall not be performed between a pointer to a
function and any type other than an integral type.This violation is due to cast from unsigned long to pointer
@section DMA_LLD_C_REF_4
Violates MISRA 2004 Advisory Rule 11.4, a cast should not be performed between a pointer to object 
type and a different pointer to object type. Cast from (uint8*) to (uint32*) used for optimizing 
the memory accesses
@section DMA_LLD_C_REF_5
Violates MISRA 2004 Advisory Rule 17.4, Array indexing shall be the only allowed form of pointer
arithmetic. This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed
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
#include "Dma_LLD.h"
#include "modules.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/* this define value is 101 for MCU, 123 for ADC, 82 for LIN and 83 for SPI */
#define DMA_COMMON_MODULE_ID                123

/** @remarks Covers BSW00374, BSW00318 */
#define DMA_AR_VENDOR_ID_LLD_C          43
#define DMA_AR_MAJOR_VERSION_LLD_C      3
#define DMA_AR_MINOR_VERSION_LLD_C      0
#define DMA_AR_PATCH_VERSION_LLD_C      0
#define DMA_SW_MAJOR_VERSION_LLD_C      2
#define DMA_SW_MINOR_VERSION_LLD_C      0
#define DMA_SW_PATCH_VERSION_LLD_C      0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and DMA header file are from the same vendor */
#if (DMA_AR_VENDOR_ID_LLD_C != DMA_VENDOR_ID)
#error "Dma_LLD.c and Dma_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
        /* Check if source file and DMA header file are of the same Autosar version */
    #if ((DMA_AR_MAJOR_VERSION_LLD_C != DMA_AR_MAJOR_VERSION) || \
         (DMA_AR_MINOR_VERSION_LLD_C != DMA_AR_MINOR_VERSION) || \
         (DMA_AR_PATCH_VERSION_LLD_C != DMA_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Dma_LLD.c and Dma_LLD.h are different"
    #endif
#endif
    /* Check if source file and DMA header file are of the same Software version */
#if ((DMA_SW_MAJOR_VERSION_LLD_C != DMA_SW_MAJOR_VERSION) || \
     (DMA_SW_MINOR_VERSION_LLD_C != DMA_SW_MINOR_VERSION) || \
     (DMA_SW_PATCH_VERSION_LLD_C != DMA_SW_PATCH_VERSION))
#error "Software Version Numbers of Dma_LLD.c and Dma_LLD.h are different"
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


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*lint -save -e961 -e537 -e451 */
#if ((USE_ADC_MODULE==STD_ON) && (DMA_COMMON_MODULE_ID==123) && (ADC_USE_DMA_LLD==STD_ON))
#define DMA_CODE ADC_CODE
/** @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
  '#include': See @ref DMA_LLD_C_REF_1 */
#define ADC_START_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && (USE_SPI_MODULE==STD_ON) && \
     (DMA_COMMON_MODULE_ID==83) && (SPI_USE_DMA_LLD==STD_ON))
#define DMA_CODE SPI_CODE
/** @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
  '#include': See @ref DMA_LLD_C_REF_1 */
#define SPI_START_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && (USE_LIN_MODULE==STD_ON) && \
      (DMA_COMMON_MODULE_ID==82) && (LIN_USE_DMA_LLD==STD_ON))
#define DMA_CODE LIN_CODE
/** @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
  '#include': See @ref DMA_LLD_C_REF_1 */
#define LIN_START_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && ((USE_LIN_MODULE==STD_OFF) || (LIN_USE_DMA_LLD==STD_OFF )) && \
      (USE_MCU_MODULE==STD_ON) && (DMA_COMMON_MODULE_ID==101) && (MCU_USE_DMA_LLD==STD_ON))
#define DMA_CODE MCU_CODE
/** @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
  '#include': See @ref DMA_LLD_C_REF_1 */
#define MCU_START_SEC_CODE
#include "MemMap.h"
#endif
/*lint -restore */ 

#if ( ((USE_ADC_MODULE==STD_ON)  && (DMA_COMMON_MODULE_ID==123) && (ADC_USE_DMA_LLD==STD_ON)) || \
      (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && (USE_SPI_MODULE==STD_ON) && \
      (DMA_COMMON_MODULE_ID==83) && (SPI_USE_DMA_LLD==STD_ON)) || \
      (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && (USE_LIN_MODULE==STD_ON) && \
      (DMA_COMMON_MODULE_ID==82) && (LIN_USE_DMA_LLD==STD_ON)) || \
      (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && ((USE_LIN_MODULE==STD_OFF) || (LIN_USE_DMA_LLD==STD_OFF )) && \
      (USE_MCU_MODULE==STD_ON) && (DMA_COMMON_MODULE_ID==101) && (MCU_USE_DMA_LLD==STD_ON)) )

/*================================================================================================*/
/**
@brief   This function initializes the DMA module by MCU driver.
@details This function initializes the DMA module by MCU driver.

@param[in]     ConfigLLDPtr Pointer to LLD configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements
*/
/*================================================================================================*/
FUNC(void, DMA_CODE) Dma_Init
    (P2CONST(Dma_ConfigType, AUTOMATIC, AUTOMATIC) ConfigLLDPtr)
{
    volatile VAR(uint8, AUTOMATIC) i=0U;
    VAR(uint8, AUTOMATIC) j=0U;
    
#if (DMA_NB_CONTROLLERS==2U)
    for(i=0U; i<DMA_NB_CONTROLLERS; i++)
    {
#endif         
        /** 
        @note Violates MISRA 2004 Advisory Rules 11.1
        - See @ref DMA_LLD_C_REF_3
        */
        /*lint -save -e923*/
        /* Initialise the EDMA.MCR register with confgured val */
        REG_WRITE32(DMA_CR(i), (uint32) ConfigLLDPtr->edmaCr[i]);
        
        /* Init eDMA channel priority registers */
        for (j=0U; j<DMA_NB_CHANNELS; j++)
        {
            /* update the CPRs registers */
            REG_WRITE8(DMA_CPR(j), ConfigLLDPtr->edmaCpr[j]); 
        }
        /*lint -restore*/
#if (DMA_NB_CONTROLLERS==2U)        
    }
#endif    
}

/*================================================================================================*/
/** 
@brief   This function disables the interrupt for a specific DMA channel.
@details Clears the interrupt enable bit for a specific DMA channel and also 
         clears the interrupt request
    
@param[in]     dma_channel      Dma channel for which to disable the interrupt
   
@return N/A

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers 
@remarks Implements 
@remarks Test_case 
*/
/*================================================================================================*/
FUNC(void, DMA_CODE) Dma_disable_interrupt( VAR(uint8, AUTOMATIC) dma_channel)
{
    /* DMA module index */
    volatile VAR(uint8, AUTOMATIC) mIdx = DMA_MOD_IDX(dma_channel);
   
    /** 
    @note Violates MISRA 2004 Advisory Rules 11.1 
    - See @ref DMA_LLD_C_REF_3
    */
    /*lint -save -e923*/
    /* clear enable interrupt request for dma_channel */
    REG_WRITE8(DMA_CERQ(mIdx), dma_channel & DMA_CTRL_MAX_CHANNELS_MASK );
    /* clear interrupt request for dma_channel */
    REG_WRITE8(DMA_CINT(mIdx), dma_channel & DMA_CTRL_MAX_CHANNELS_MASK);
    /*lint -restore*/
}

/*================================================================================================*/
/** 
@brief   Setup a DMA Transfer Control Descritor (TCD).
@details Configures the DMA Tranfer Control Descriptor
    
@param[out]    descriptor           Dma descriptor address to be configured
@param[in]     src_addr             Source address for DMA transfer
@param[in]     src_transfer_size    Source access transfer size
@param[in]     dest_transfer_size   Destination access transfer size
@param[in]     src_next_offset      Offset to be applied to compute next src addr
@param[in]     n_bytes_to_transfer  Number of bytes to transfer
@param[in]     src_last_adj         Adjustment to be applied to src addr at the
                                    completion of the outer major iteration count.
@param[in]     dest_addr            Destination address for DMA transfer
@param[in]     crt_iter_cnt         Current major iteration count
@param[in]     dest_next_offset     Offset to be applied to compute next 
                                    destination address.
@param[in]     dlast_sg_addr        Adjustment to be applied to destination 
                                    address at the completion of the outer major
                                    iteration count (if E_SG bit is 0), or 
                                    scatter/gather address (if E_SG bit is 1).
@param[in]     begin_iter_cnt       Beginning major iteration count
@param[in]     major_linkch         Major link channel number
@param[in]     tcd_flags            Mask to configure E_SG(bit4)/D_REQ(bit3)/
                                    INT_HALF(bit2)/INT_MAJ(bit1) bits of TCD
   
@return N/A

@pre The TCD descriptor must be 32 bytes aligned
@post Postconditions of this function

@remarks Covers 
@remarks Implements 
@remarks Test_case 
*/
/*================================================================================================*/
FUNC(void, DMA_CODE) Dma_setup_descriptor( 
    VAR(DmaTcdPointerType, AUTOMATIC) descriptor,
    VAR(uint32, AUTOMATIC) src_addr,
    VAR(uint8, AUTOMATIC) src_transfer_size,
    VAR(uint8, AUTOMATIC) dest_transfer_size,
    VAR(uint16, AUTOMATIC) src_next_offset,
    VAR(uint16, AUTOMATIC) n_bytes_to_transfer,
    VAR(uint32, AUTOMATIC) src_last_adj,
    VAR(uint32, AUTOMATIC) dest_addr,
    VAR(uint16, AUTOMATIC) crt_iter_cnt,
    VAR(uint16, AUTOMATIC) dest_next_offset,
    VAR(uint32, AUTOMATIC) dlast_sg_addr,
    VAR(uint16, AUTOMATIC) begin_iter_cnt,
    VAR(uint8, AUTOMATIC)  major_linkch,
    VAR(uint8, AUTOMATIC)  tcd_flags
    )
{
    VAR(uint32, AUTOMATIC)reg_value;
    /** 
    @note Violates MISRA 2004 Advisory Rules 11.4 
    - See @ref DMA_LLD_C_REF_4
    */
    /*lint -save -e927*/
    volatile P2VAR(uint32, AUTOMATIC, AUTOMATIC) descriptor32 = 
        (volatile P2VAR(uint32, AUTOMATIC, AUTOMATIC))descriptor;
    /*lint -restore*/

    /** 
    @note Violates MISRA 2004 Advisory Rules 17.4 
    - See @ref DMA_LLD_C_REF_5
    */
    /* Source address */
    descriptor32[0/*DMA_TCD_SADDR_OFFSET>>2 - avoid MISRA Warn*/] = src_addr;

    /* Transfer attributes, source offset */
    reg_value= (uint32)(((uint32)(src_transfer_size)<<24) | 
                        (((uint32)dest_transfer_size)<<16) | 
                        ((uint32)src_next_offset) 
                       );
    /** 
    @note Violates MISRA 2004 Advisory Rules 17.4 - See @ref DMA_LLD_C_REF_5 */
    descriptor32[DMA_TCD_TA_SOFF_OFFSET>>2] = reg_value;
    
    /* Signed minor loop OFFSET], Number of bytes to transfer 
       with each service request 
     */
    reg_value=  (uint32) ( (uint32)(n_bytes_to_transfer));
    /** 
    @note Violates MISRA 2004 Advisory Rules 17.4 
    - See @ref DMA_LLD_C_REF_5
    */
    descriptor32[DMA_TCD_SMLO_NBTYES_OFFSET>>2] = reg_value;
    
    /* Source address last adjustment */
    descriptor32[DMA_TCD_SLAST_OFFSET>>2] = src_last_adj;
    
    /* Destination address */
    descriptor32[DMA_TCD_DADDR_OFFSET>>2] = dest_addr;

    /* Current major iteration count, destination offset */
    reg_value= (uint32)((((uint32)crt_iter_cnt)<<16) | 
                        ((uint32)(dest_next_offset)) );
    /** 
    @note Violates MISRA 2004 Advisory Rules 17.4 
    - See @ref DMA_LLD_C_REF_5
    */
    descriptor32[DMA_TCD_CITER_DOFF_OFFSET>>2] = reg_value;

    /* Destination address last adjustment / scatter gather address */
    descriptor32[DMA_TCD_DLAST_SGA_OFFSET>>2] = dlast_sg_addr;

    /* Beginning iteration count, scatter/gather, interrupt flags */
    reg_value= (uint32)(
                    (((uint32)begin_iter_cnt)<<16) | 
                    (((uint32)major_linkch)<<8) | 
                    tcd_flags);
    /** 
    @note Violates MISRA 2004 Advisory Rules 17.4 
    - See @ref DMA_LLD_C_REF_5
    */
    /* DONE flag must be reset prior to set E_SG & E_LINK bits */
    descriptor32[DMA_TCD_BITER_CCS_OFFSET>>2] = 0u;
    /* effective set of last TCD entry */
    descriptor32[DMA_TCD_BITER_CCS_OFFSET>>2] = reg_value;
}
#endif /* module check */

/*lint -save -e961 -e537 -e451 */
#if ((USE_ADC_MODULE==STD_ON) && (DMA_COMMON_MODULE_ID==123) && (ADC_USE_DMA_LLD==STD_ON))
/** @note Violates MISRA 2004 Advisory Rule 19.1 and Rule 19.15  See @ref DMA_LLD_C_REF_1 &
  @ref DMA_LLD_C_REF_2 */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && (USE_SPI_MODULE==STD_ON) && \
     (DMA_COMMON_MODULE_ID==83) && (SPI_USE_DMA_LLD==STD_ON))
/** @note Violates MISRA 2004 Advisory Rule 19.1 and Rule 19.15  See @ref DMA_LLD_C_REF_1 &
  @ref DMA_LLD_C_REF_2 */
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && (USE_LIN_MODULE==STD_ON) && \
      (DMA_COMMON_MODULE_ID==82) && (LIN_USE_DMA_LLD==STD_ON))
/** @note Violates MISRA 2004 Advisory Rule 19.1 and Rule 19.15  See @ref DMA_LLD_C_REF_1 &
  @ref DMA_LLD_C_REF_2 */
#define LIN_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (((USE_ADC_MODULE==STD_OFF) || (ADC_USE_DMA_LLD==STD_OFF)) && ((USE_SPI_MODULE==STD_OFF) || \
      (SPI_USE_DMA_LLD==STD_OFF)) && ((USE_LIN_MODULE==STD_OFF) ||(LIN_USE_DMA_LLD==STD_OFF )) && \
      (USE_MCU_MODULE==STD_ON) && (DMA_COMMON_MODULE_ID==101) && (MCU_USE_DMA_LLD==STD_ON))
/** @note Violates MISRA 2004 Advisory Rule 19.1 and Rule 19.15  See @ref DMA_LLD_C_REF_1 &
  @ref DMA_LLD_C_REF_2 */
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*lint -restore */ 

#ifdef __cplusplus
}
#endif
