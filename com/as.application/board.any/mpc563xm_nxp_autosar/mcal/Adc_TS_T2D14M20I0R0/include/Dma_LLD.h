/**
    @file        Dma_LLD.h
    @version     2.0.0
    @brief       AUTOSAR Adc - eDMA Low level header.
    @details     Low level header for eDMA IP module.

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

@section Dma_LLD_H_REF_1
 MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar

@section Dma_LLD_H_REF_2
MISRA-C:2004 19.7 VIOLATION: Use of function like macro.
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier: _DMA_LLD_H_. - See @ref Dma_LLD_H_REF_1
*/
#ifndef _DMA_LLD_H_
#define _DMA_LLD_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Reg_eSys_DMA.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define DMA_VENDOR_ID            43
#define DMA_AR_MAJOR_VERSION     3
#define DMA_AR_MINOR_VERSION     0
#define DMA_AR_PATCH_VERSION     0
#define DMA_SW_MAJOR_VERSION     2
#define DMA_SW_MINOR_VERSION     0
#define DMA_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Std_Types.h file and DMA header file are of the same Autosar version */
    #if ((DMA_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (DMA_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Dma_LLD.h and Std_Types.h are different"
    #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION                                                              
    /* Check if Std_Types.h file and DMA header file are of the same Autosar version */ 
    #if ((DMA_AR_MAJOR_VERSION != DMA_AR_MAJOR_VERSION_REG) || \
         (DMA_AR_MINOR_VERSION != DMA_AR_MINOR_VERSION_REG))
    #error "AutoSar Version Numbers of Dma_LLD.h and Reg_eSys_DMA.h are different"           
    #endif                                                                                
#endif                                                                                    

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/* Max numbers of CPRs groups used is DMA_NB_CHANNELS/4 */
#define MAX_NB_CPR_USED         (DMA_NB_CHANNELS>>2) 

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief Data transfer size 16 bits
*/
#define DMA_DATA_TRANSFER_16_BIT    ((uint8) 0x1)
/**
@brief Data transfer size 32 bits
*/
#define DMA_DATA_TRANSFER_32_BIT    ((uint8) 0x2)
/**
@brief Data transfer size 16 bits
*/
#define DMA_DATA_TRANSFER_64_BIT    ((uint8) 0x3)
/**
@brief Data transfer size 16 bytes
*/
#define DMA_DATA_TRANSFER_16_BYTE   ((uint8) 0x4)
/**
@brief Data transfer size 32 bytes
*/
#define DMA_DATA_TRANSFER_32_BYTE   ((uint8) 0x5)
/**
@brief Mode mask bit to check the channels which is requested for the mode change
*/
#define DMA_MODE_MASK               ((uint16)0x0001U)
/**
@brief Channel Active field bit to check whether channel is active or not
*/
#define DMA_IS_ACTIVE               ((uint32)0x00000040UL)
/**
@brief Channel Source specifies which DMA source is routed to DMA channel
*/
#define DMASOURCEMASK               ((uint16)0x003fU)
/**
@brief Macro used to wait for software eDMA Time out till zero
*/
#define DMA_ZERO_VALUE              ((uint32)0x0U)

/*================================================================================================*/
/** 
@brief   Acknowledge a DMA interrupt. 
@details Clears the interrupt request bit for a specific DMA channel
    
@param[in]     dma_channel      Dma channel for which to acknowledge the interrupt
   
@return N/A

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers 
@remarks Implements 
@remarks Test_case 
*/
/*================================================================================================*/
/**@note Violates MISRA 2004 Advisory Rule 19.7 - See @ref Dma_LLD_H_REF_2*/
#define Dma_ack_interrupt(dma_channel) \
    REG_WRITE8(DMA_CINT(DMA_MOD_IDX((uint8)(dma_channel))), \
        (((uint8)(dma_channel)) & DMA_CTRL_MAX_CHANNELS_MASK))

/*================================================================================================*/
/** 
@brief   Start the transfer on a specific DMA channel.
@details Start a DMA transfer
    
@param[in]     dma_channel      Dma channel for which to disable the interrupt
   
@return N/A

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers 
@remarks Implements 
@remarks Test_case 
*/
/*================================================================================================*/
/**@note Violates MISRA 2004 Advisory Rule 19.7 - See @ref Dma_LLD_H_REF_2*/
#define Dma_start_channel(dma_channel) \
    REG_WRITE8(DMA_SERQ(DMA_MOD_IDX((uint8)(dma_channel))), \
        ((uint8)(dma_channel)) & DMA_CTRL_MAX_CHANNELS_MASK)


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
 typedef struct {
       VAR(uint32, AUTOMATIC) edmaCr[DMA_NB_CONTROLLERS]; /** @brief eDMA MCR register. */
       VAR(uint8,  AUTOMATIC) edmaCpr[DMA_NB_CHANNELS];/** @brief eDMA channel priority registers */
       VAR(uint32, AUTOMATIC) edmaTimeout; /** @brief eDMA Timeout value used for the software
                         timeout */
} Dma_ConfigType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/**
@brief   This function initializes the DMA module.
@details This function initializes the DMA module.

@param[in]     ConfigLLDPtr Pointer to LLD configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements
*/
/*================================================================================================*/
extern void Dma_Init(P2CONST(Dma_ConfigType, AUTOMATIC, AUTOMATIC) ConfigLLDPtr);

/*================================================================================================*/
/**
@brief   This function disables the interrupt for a specific DMA channel.
@details Clears the interrupt enable bit for a specific DMA channel and also clears the itnerrupt
         request

@param[in]     dma_channel      Dma channel for which to disable the interrupt

@return N/A

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements
@remarks Test_case
*/
/*================================================================================================*/
extern void Dma_disable_interrupt( VAR(uint8, AUTOMATIC) dma_channel);

/**
@brief   Configure a DMA transfer.
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

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements
@remarks Test_case
*/
/*VAR(uint32, AUTOMATIC) descriptor,*/
/*================================================================================================*/
extern void Dma_setup_descriptor(VAR(DmaTcdPointerType, AUTOMATIC) descriptor,
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
                                );

/*================================================================================================*/
/**
@brief   Configure a DMA transfer.
@details Configures the DMA Tranfer Control Descriptor

@param[in]     dma_channel          Dma channel for which to disable the interrupt
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
@param[in]     tcd_flags            Mask to configure E_SG(bit4)/D_REQ(bit3)/
                                    INT_HALF(bit2)/INT_MAJ(bit1) bits of TCD

@return N/A

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements
@remarks Test_case
*/
/*================================================================================================*/
/**@note Violates MISRA 2004 Advisory Rule 19.7 - See @ref Dma_LLD_H_REF_2*/
#define Dma_configure_channel( dma_channel, \
                               src_addr, \
                               src_transfer_size, \
                               dest_transfer_size, \
                               src_next_offset, \
                               n_bytes_to_transfer, \
                               src_last_adj, \
                               dest_addr, \
                               crt_iter_cnt, \
                               dest_next_offset, \
                               dlast_sg_addr, \
                               begin_iter_cnt, \
                               tcd_flags ) \
        Dma_setup_descriptor( (VAR(DmaTcdPointerType, AUTOMATIC))(DMA_TCD(dma_channel)), \
                               (src_addr), \
                               (src_transfer_size), \
                               (dest_transfer_size), \
                               (src_next_offset), \
                               (n_bytes_to_transfer), \
                               (src_last_adj), \
                               (dest_addr), \
                               (crt_iter_cnt), \
                               (dest_next_offset), \
                               (dlast_sg_addr), \
                               (begin_iter_cnt), \
                                0u, \
                               (tcd_flags) )

#ifdef __cplusplus
}
#endif

#endif /*_DMA_LLD_H_*/
