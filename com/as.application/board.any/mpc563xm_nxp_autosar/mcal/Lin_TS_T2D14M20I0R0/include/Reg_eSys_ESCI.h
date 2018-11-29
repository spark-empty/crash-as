/**
   @file    Reg_eSys_ESCI.h
   @version 2.0.0

   @brief   ESCI Registers and Macros Definitions.
   @details Header file for ESCI Registers and Macros Definitions.

   Project AUTOSAR 3.0 MCAL
   Patform PA
   Peripheral ESCI
   Dependencies 

   ARVersion 3.0.0
   ARRevision ASR_REL_3_0_REV_0003
   ARConfVariant
   SWVersion 2.0.0
   BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

   (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
   All Rights Reserved.
*/
/*=================================================================================================
=================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section REG_ESYS_ESCI_H_REF_1
 * Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
 * Function like macros are used to reduce code complexity.
 *
 * @section REG_ESYS_ESCI_H_REF_2
 * Violates MISRA 2004 Required Rule 1.4, Identifier clash (one symbol with another symbol)
 * MISRA tool considers only first 32 characters of an identifier and if it is repeating for some 
 * other identifier, this violation is generated (even though identifier names are different, only 
 * some part of them is same).
 */

#ifndef REG_ESYS_ESCI_H
#define REG_ESYS_ESCI_H

#ifdef __cplusplus
extern "C" {
#endif


/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/


/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define LIN_AR_MAJOR_VERSION_REGESCI        1
#define LIN_AR_MINOR_VERSION_REGESCI        2
#define LIN_AR_PATCH_VERSION_REGESCI        1

#define LIN_SW_MAJOR_VERSION_REGESCI        2
#define LIN_SW_MINOR_VERSION_REGESCI        0
#define LIN_SW_PATCH_VERSION_REGESCI        0

/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/
/* ========================IPV_ESCI macro definition========================================*/
#define IPV_ESCI_07_00_00_00  0x07000000UL   /* Generic define for IPV_ESCI V.7*/
#define IPV_ESCI_08_00_00_00  0x08000000UL   /* Generic define for IPV_ESCI V.8 */

/* IPV_ESCI shall be defined in Soc_Ips.h file with the appropriate value                     */
/* because this convention started with Leopard and in order to keep the backward compatibility  */
/* the following 3 lines defines the default value for IPV_ESCI                                */
/* the only rule you need to follow is to include Soc_Ips.h before Reg_eSys_ESCI.h in any     */
/* c source file                                                                                 */
#ifndef IPV_ESCI
    #error "IPV_ESCI not defined"
#endif
/* ========================IPV_ESCI macro definition========================================*/
/*lint -save -e765*/
extern CONST(uint32, LIN_CONST) LIN_BASE_ADDRESS[];
/*lint -restore*/

/**
 * @file Reg_eSys_ESCI.h
 * @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined: 
 *       See @ref REG_ESYS_ESCI_H_REF_1
 *       Violation for below block of code
 */
#define LIN_GET_BASE_ADDRESS(offset) (uint32)( LIN_BASE_ADDRESS[offset] )

/* ESCI REGISTERS */
/* eSCI Baud Rate Register (eSCI_BRR) */
#define ESCI_BRR(offset)      ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x00uL ) )

/* eSCI Control Register 1 (LINCR1) */
 #define ESCI_CR1(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x02uL ) )

/* eSCI Control Register 2 (eSCI_CR2) */
 #define ESCI_CR2(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x04uL ) )

/* eSCI SCI Data Register (eSCI_SDR) */
 #define ESCI_SDR(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x06uL ) )

/* eSCI Interrupt Flag and Status Register 1 (eSCI_IFSR1) */
#define ESCI_IFSR1(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x08uL ) )

/* eSCI Interrupt Flag and Status Register 2 (eSCI_IFSR2) */
#define ESCI_IFSR2(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x0AuL ) )

/* eSCI LIN Control Register 1 (eSCI_LCR1) */
#define ESCI_LCR1(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x0CuL ) )

/* eSCI LIN Control Register 2 (eSCI_LCR2) */
#define ESCI_LCR2(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x0EuL ) )

/* eSCI LIN Transmit Register (eSCI_LTR) */
#define ESCI_LTR(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x10uL ) )

/* eSCI LIN Receive Register (eSCI_LRR) */
#define ESCI_LRR(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x14uL ) )

/* eSCI LIN CRC Polynomial Register (eSCI_LPR) */
#define ESCI_LPR(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x18uL ) )

/* eSCI Control Register 3 (eSCI_CR3) */
#define ESCI_CR3(offset)    ( (uint32)( LIN_GET_BASE_ADDRESS(offset) + 0x1AuL ) )

/**
 * MISRA 2004 Advisory Rule 19.7  -  end violation
 */
 
/* eSCI REGISTERS BITS */


/*-----------------------------------------------------------------------------------------------*/
/*                                Baud Rate Register (eSCI_BRR) bits                             */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     Reserved    |                         SBR                                                */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Baud Rate Register (eSCI_BRR) bit masks */

/* Baud Rate Register bit masks */
#define ESCI_BRR_SBR_MASK                (uint16)0x1FFFU

/* Baud Rate Register Resetbit masks */
#define ESCI_BRR_RESET_MASK              (uint16)0x0004U






/*-----------------------------------------------------------------------------------------------*/
/*                                    Control Register 1 (eSCI_CR1) bits                         */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|LOOPS|SDZR |RSRC | M   |WAKE | ILT | PE  | PT  | TIE |TCIE | RIE |ILIE | TE  | RE  | RWU | SBK*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Control Register 1 bit masks */
/* Send Break Character bit mask */
#define ESCI_CR1_SBK_MASK                (uint16)0x0001U

/* Receiver Wake-Up Mode bit mask */
#define ESCI_CR1_RWU_MASK                (uint16)0x0002U

/* Receiver Enable bit mask */
#define ESCI_CR1_RE_MASK                 (uint16)0x0004U

/* Transmitter Enable bit mask */
#define ESCI_CR1_TE_MASK                 (uint16)0x0008U

/* Idle Line Interrupt Enable bit mask */
#define ESCI_CR1_ILIE_MASK               (uint16)0x0010U

/* Receiver Full Interrupt Enable bit mask */
#define ESCI_CR1_RIE_MASK                (uint16)0x0020U

/* Transmission Complete Interrupt Enable bit mask */
#define ESCI_CR1_TCIE_MASK               (uint16)0x0040U

/* Transmitter Interrupt Enable bit mask */
#define ESCI_CR1_TIE_MASK                (uint16)0x0080U

/* Parity Type bit mask */
#define ESCI_CR1_PT_MASK                 (uint16)0x0100U

/* Parity Enable bit mask */
#define ESCI_CR1_PE_MASK                 (uint16)0x0200U

#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

/* Idle Line Type bit mask */
#define ESCI_CR1_ILT_MASK        (uint16)0x0400U

#endif
/* Receiver Wake-up Condition bit mask */
#define ESCI_CR1_WAKE_MASK               (uint16)0x0800U

/* Frame Format Mode bit mask */
#define ESCI_CR1_M_MASK                  (uint16)0x1000U

/* Receiver Source Control bit mask */
#define ESCI_CR1_RSRC_MASK               (uint16)0x2000U

/* Loop Mode Select bit mask */
#define ESCI_CR1_LOOPS_MASK              (uint16)0x8000U

/* Control Register 1 Reset bit masks */
#define ESCI_CR1_RESET_MASK              (uint16)0x0000U






/*-----------------------------------------------------------------------------------------------*/
/*                                   Control Register 2 (eSCI_CR2) bits                          */
/*-----------------------------------------------------------------------------------------------*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*BIT 0|BIT 1|BIT 2|BIT 3 |BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*MDIS | FBR |BSTP |BERRIE|RXDMA|TXDMA|BRCL |TXDIR|BESM |BESTP|RXPOL|PMSK |ORIE |NFIE |FFIE |PFIE*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Control Register 2 bit masks */

/* Parity Error Interrupt Enable bit mask */
#define ESCI_CR2_PFIE_MASK               (uint16)0x0001U

/* Frame Error Interrupt Enable bit mask */
#define ESCI_CR2_FEIE_MASK               (uint16)0x0002U

/* Noise Interrupt Enable bit mask */
#define ESCI_CR2_NFIE_MASK               (uint16)0x0004U

/* Overrun Interrupt Enable bit mask */
#define ESCI_CR2_ORIE_MASK               (uint16)0x0008U

/* Parity Bit Masking bit mask */
#define ESCI_CR2_PMSK_MASK               (uint16)0x0010U

/* RXD Pin polarity bit mask */
#define ESCI_CR2_RXPOL_MASK              (uint16)0x0020U

/* Transmit Stop on Bit Error bit mask */
#define ESCI_CR2_BESTP_MASK              (uint16)0x0040U

/* Fast Bit Error Detection Sample Mode bit mask */
#define ESCI_CR2_BESM_MASK               (uint16)0x0080U

/* TXD pin output enable bit mask */
#define ESCI_CR2_TXDIR_MASK              (uint16)0x0100U

/* Break Character Length bit mask */
#define ESCI_CR2_BRCL_MASK               (uint16)0x0200U

/* Transmit DMA Control bit mask */
#define ESCI_CR2_TXDMA_MASK              (uint16)0x0400U

/* Receive DMA Control bit mask */
#define ESCI_CR2_RXDMA_MASK              (uint16)0x0800U

/* Bit Error Interrupt Enable bit mask */
#define ESCI_CR2_BERRIE_MASK             (uint16)0x1000U

/* DMA Stop on Bit Error or Physical Bus Error bit mask */
#define ESCI_CR2_BSTP_MASK               (uint16)0x2000U

/* Fast Bit Error Detection bit mask */
#define ESCI_CR2_FBR_MASK                (uint16)0x4000U

/* Module Disabled Mode bit mask */
#define ESCI_CR2_MDIS_MASK               (uint16)0x8000U

/* Control Register 2 Reset bit masks */
#define ESCI_CR2_RESET_MASK              (uint16)0x2000U






/*-----------------------------------------------------------------------------------------------*/
/*                            SCI Data Register (eSCI_SDR) bits                                  */
/*-----------------------------------------------------------------------------------------------*/
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/*BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/* RN  |     |ERR  | 0   |     RD [11:8]        |RD[7]|            RD [6:0]                      */
/*-----| TN  |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/*     |     |     |     |     |    |      |     |TD[7]|            TD [6:0]                     */
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/

/* SCI Data Register bit masks */
/* Received / Transmit bits 6 to 0 bit mask */
#define ESCI_SDR_RD_TD_6_0_MASK          (uint16)0x007FU

/* Received / Transmit Bit 7 bit mask */
#define ESCI_SDR_RD_TD_7_MASK            (uint16)0x0080U

/* Received / Transmit bits 7 to 0 bit mask */
#define ESCI_SDR_RD_TD_7_0_MASK          (uint16)0x00FFU

/* Received Data [11:8] bit mask */
#define ESCI_SDR_RD_11_8_MASK            (uint16)0x0F00U

/* Receive Error Bit mask */
#define ESCI_SDR_ERR_MASK                (uint16)0x2000U

/* Transmit Most Significant Bit mask */
#define ESCI_SDR_TN_MASK                 (uint16)0x4000U

/* Received Most Significant Bit mask */
#define ESCI_SDR_RN_MASK                 (uint16)0x8000U

/* SCI Data Register Reset bit masks */
#define ESCI_SDR_RESET_MASK              (uint16)0x0000U






/*-----------------------------------------------------------------------------------------------*/
/*      Interrupt Flag and Status Register 1 (eSCI_IFSR1) bits                                   */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|TDRE | TC  |RDRF |IDLE | OR  | NF  | FE  | PF  |     |     |DACT |BERR |WACT |LACT |TACT |RACT*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Interrupt Flag and Status Register 1 bit masks */

/* Receiver Active bit mask */
#define ESCI_IFSR1_RACT_MASK             (uint16)0x0001U

/* Transmitter Active bit mask */
#define ESCI_IFSR1_TACT_MASK             (uint16)0x0002U

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

/* LIN Active Flag bit mask */
#define ESCI_IFSR1_LACT_MASK             (uint16)0x0004U

/* LIN WAke-Up Active Flag bit mask */
#define ESCI_IFSR1_WACT_MASK             (uint16)0x0008U

#endif
/* Bit Error Interrupt Flag bit mask */
#define ESCI_IFSR1_BERR_MASK             (uint16)0x0010U

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/
/* DMA Active Flag bit mask */
#define ESCI_IFSR1_DACT_MASK             (uint16)0x0020U
#endif
/* Parity Error Interrupt Flag bit mask */
#define ESCI_IFSR1_PF_MASK               (uint16)0x0100U

/* Framing Error Interrupt Flag bit mask */
#define ESCI_IFSR1_FE_MASK               (uint16)0x0200U

/* Noise Interrupt Flag bit mask */
#define ESCI_IFSR1_NF_MASK               (uint16)0x0400U

/* Overrun Interrupt Flag bit mask */
#define ESCI_IFSR1_OR_MASK               (uint16)0x0800U

/* Idle Line Interrupt Flag bit mask */
#define ESCI_IFSR1_IDLE_MASK             (uint16)0x1000U

/* Receive Data Register Full Interrupt Flag bit mask */
#define ESCI_IFSR1_RDRF_MASK             (uint16)0x2000U

/* Transmit Complete Interrupt Flag bit mask */
#define ESCI_IFSR1_TC_MASK               (uint16)0x4000U

/* Transmit Data Register Empty Interrupt Flag bit mask */
#define ESCI_IFSR1_TDRE_MASK             (uint16)0x8000U

/* Interrupt Flag and Status Register 1 Reset bit masks */
#define ESCI_IFSR1_RESET_MASK            (uint16)0xFF13U






/*-----------------------------------------------------------------------------------------------*/
/*        Interrupt Flag and Status Register 2 (eSCI_IFSR2) bits                                 */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|RXRDY|TXRDY|LWAKE| STO |PBERR|CERR |CKERR| FRC |     |     |     |     |     |     |UREQ |OVFL*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Interrupt Flag and Status Register 2 bit masks */

/* Overflow Interrupt Flag bit mask */
#define ESCI_IFSR2_OVFL_MASK             (uint16)0x0001U

/* Unrequested Data Received Interrupt Flag bit mask */
#define ESCI_IFSR2_UREQ_MASK             (uint16)0x0002U

/* Frame Complete Interrupt Flag bit mask */
#define ESCI_IFSR2_FRC_MASK              (uint16)0x0100U

/* Checksum Error Interrupt Flag bit mask */
#define ESCI_IFSR2_CKERR_MASK            (uint16)0x0200U

/* CRC Error Interrupt Flag bit mask */
#define ESCI_IFSR2_CERR_MASK             (uint16)0x0400U

/* Physical Bus Error Interrupt Flag bit mask */
#define ESCI_IFSR2_PBERR_MASK            (uint16)0x0800U

/* Slave Timeout Interrupt Flag bit mask */
#define ESCI_IFSR2_STO_MASK              (uint16)0x1000U

/* LIN Wakeup Received Interrupt Flag Flag bit mask */
#define ESCI_IFSR2_LWAKE_MASK            (uint16)0x2000U

/* Transmit Data Ready Interrupt Flag bit mask */
#define ESCI_IFSR2_TXRDY_MASK            (uint16)0x4000U

/* Receive Data Ready Interrupt Flag bit mask */
#define ESCI_IFSR2_RXRDY_MASK            (uint16)0x8000U

/* Interrupt Flag and Status Register 2 Reset bit masks */
#define ESCI_IFSR2_RESET_MASK            (uint16)0xFF03U






/*-----------------------------------------------------------------------------------------------*/
/*            LIN Control Register 1 (eSCI_LCR1) bits                                            */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|LRES | WU  |    WUD    |     |     |PRTY | LIN |RXIE |TXIE |WUIE |STIE |PBIE | CIE |CKIE |FCIE*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* LIN Control Register 1 bit masks */

/* Frame Complete Interrupt Enable bit mask */
#define ESCI_LCR1_FCIE_MASK              (uint16)0x0001U

/* Checksum Error Interrupt Enable bit mask */
#define ESCI_LCR1_CKIE_MASK              (uint16)0x0002U

/* CRC Error Interrupt Enable bit mask */
#define ESCI_LCR1_CIE_MASK               (uint16)0x0004U

/* Physical Bus Error Interrupt Enable bit mask */
#define ESCI_LCR1_PBIE_MASK              (uint16)0x0008U

/* Slave Timeout Flag Interrupt Enable bit mask */
#define ESCI_LCR1_STIE_MASK              (uint16)0x0010U

/* LIN Wakeup Received Interrupt Enable bit mask */
#define ESCI_LCR1_WUIE_MASK              (uint16)0x0020U

/* Transmit Data Ready Interrupt Enable bit mask */
#define ESCI_LCR1_TXIE_MASK              (uint16)0x0040U

/* Receive Data Ready Interrupt Enable bit mask */
#define ESCI_LCR1_RXIE_MASK              (uint16)0x0080U

/* LIN Mode Control bit mask */
#define ESCI_LCR1_LIN_MASK               (uint16)0x0100U

/* Parity Generation Control bit mask */
#define ESCI_LCR1_PRTY_MASK              (uint16)0x0200U

/* LIN Bus Wake-Up Delimiter Time 4 bit mask */
#define ESCI_LCR1_WUD_FOUR_BIT_MASK      (uint16)0x0000U

/* LIN Bus Wake-Up Delimiter Time 8 bit mask */
#define ESCI_LCR1_WUD_EIGHT_BIT_MASK     (uint16)0x1000U

/* LIN Bus Wake-Up Delimiter Time 32 bit mask */
#define ESCI_LCR1_WUD_THIRTY_TWO_BIT_MASK       (uint16)0x2000U

/* LIN Bus Wake-Up Delimiter Time 64 bit mask */
#define ESCI_LCR1_WUD_SIXTY_FOUR_BIT_MASK       (uint16)0x3000U

/* LIN Bus Wake-Up Trigger bit mask */
#define ESCI_LCR1_WU_MASK                (uint16)0x4000U

/* LIN Protocol Engine Reset Enable bit mask */
#define ESCI_LCR1_LRES_MASK              (uint16)0x8000U

/* LIN Control Register 1 Reset bit masks */
#define ESCI_LCR1_RESET_MASK             (uint16)0x0000U






/*-----------------------------------------------------------------------------------------------*/
/*        LIN Control Register 2 (eSCI_LCR2) bits                                                */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     |     |     |     |     |     |UQIE |OFIE |     |     |     |     |     |     |     |    */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* LIN Control Register 2 bits masks */

/* Unrequested Data Received Interrupt Enable bit mask */
#define ESCI_LCR2_OFIE_MASK              (uint16)0x0100U

/* Overflow Interrupt Enable bit mask */
#define ESCI_LCR2_UQIE_MASK              (uint16)0x0200U

/* LIN Control Register 2 Reset bit masks */
#define ESCI_LCR2_RESET_MASK             (uint16)0x0000U






/*----------------------------------------------------------*/
/* LIN Transmit Register(eSCI_LTR)- LIN TX frame generation */
/*----------------------------------------------------------*/
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |WRITE||BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |1st W||   P [1:0] |    ID [5:0]                       | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |2nd W||        LEN                                    | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |3rd W|| CSM | CSE | CRC |TD(1)|  TO (ignored)         | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |4th  W||        D                                     | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */



/*----------------------------------------------------------*/
/* LIN Transmit Register(eSCI_LTR)- LIN RX frame generation */
/*----------------------------------------------------------*/
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |WRITE||BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |1st W||   P [1:0] |    ID [5:0]                       | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |2nd W||        LEN                                    | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |3rd W|| CSM | CSE | CRC |TD(0)|  TO [11:8]            | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |4th  W||        TO [7:0]                              | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */



/* LIN Transmit Register bit masks */

/* Identifier bit mask */
#define ESCI_LTR_ID_MASK                 (uint8)0x3FU

/* Identifier Parity bit mask */
#define ESCI_LTR_P_MASK                  (uint8)0xC0U

/* Frame Length bit mask */
#define ESCI_LTR_LEN_MASK                (uint8)0xFFU

/* Timeout Value bit mask */
#define ESCI_LTR_TO_11_8_MASK            (uint8)0x0FU

/* Transfer Direction bit mask */
#define ESCI_LTR_TD_MASK                 (uint8)0x10U

/* CRC Enable bit mask */
#define ESCI_LTR_CRC_MASK                (uint8)0x20U

/* Checksum Enable bit mask */
#define ESCI_LTR_CSE_MASK                (uint8)0x40U

/* Checksum Model bit mask */
#define ESCI_LTR_CSM_MASK                (uint8)0x80U

/* Transmit Data bit mask */
#define ESCI_LTR_TO_7_0_MASK             (uint8)0xFFU

/* LIN Transmit Register Reset bit masks */
#define ESCI_LTR_RESET_MASK              (uint8)0x00U






/*---------------------------------------------------*/
/*   LIN Receive Register (eSCI_LRR) bits            */
/*---------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----|-----|-----|-----|-----|-----|-----|-----| */
/* |           D [7:0]                             | */
/* |-----|-----|-----|-----|-----|-----|-----|-----| */

/* LIN Receive Register bit masks */

/* Receive Data bit mask */
#define ESCI_LRR_D_MASK                  (uint8)0xFFU

/* LIN Receive Register Reset bit masks */
#define ESCI_LRR_RESET_MASK              (uint8)0x00U






/*-----------------------------------------------------------------------------------------------*/
/*          LIN CRC Polynomial Register (eSCI_LPR) bits                                          */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|                                         P [15:0]                                             */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* LIN CRC Polynomial Register bit masks */

/* Polynomial bit mask */
#define ESCI_LPR_P_MASK                  (uint16)0x00FFU

/* LIN CRC Polynomial Register Reset bit masks */
#define ESCI_LPR_RESET_MASK              (uint16)0xC599U






/*-----------------------------------------------------------------------------------------------*/
/*              Control Register 3 (eSCI_CR3) bits                                               */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     |     |     |SYNM |EROE |ERFE |ERPE | M2  |     |     |     |     |     |     |     |    */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/* Control Register 3 bit masks */

/* Frame Format Mode 2 bit mask */
#define ESCI_CR3_M2_MASK                 (uint16)0x0100U

/* ERR flag parity error enable bit mask */
#define ESCI_CR3_ERPE_MASK               (uint16)0x0200U

/* ERR flag frame error enable bit mask */
#define ESCI_CR3_ERFE_MASK               (uint16)0x0400U

/* ERR flag overrun enable bit mask */
#define ESCI_CR3_EROE_MASK               (uint16)0x0800U

/* Synchronization Mode bit mask */
#define ESCI_CR3_SYNM_MASK               (uint16)0x1000U

/* Control Register 3 Reset bit masks */
#define ESCI_CR3_RESET_MASK              (uint16)0x0000U






/*-----------------------------------------------------------------------------------------------*/
/*               Baud Rate Register (eSCI_BRR) Configuration                                     */
/*-----------------------------------------------------------------------------------------------*/

/**
 * @file Reg_eSys_ESCI.h
 * @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined: 
 *       See @ref REG_ESYS_ESCI_H_REF_1
 *       Violation for below block of code
 */

/* Reset eSCI_BRR register */
#define ESCI_LLM_BRR_Reset(offset)       ( REG_WRITE16(ESCI_BRR(offset), ESCI_BRR_RESET_MASK) )

/* Read eSCI_BRR register */
#define ESCI_LLM_BRR_Read(offset)       ( REG_READ16(ESCI_BRR(offset)) )

/* Configure eSCI_BRR register */
#define ESCI_LLM_BRR_Config(offset, value)   ( REG_WRITE16(ESCI_BRR(offset),\
                             (value & ESCI_BRR_SBR_MASK)) )

/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*               Control Register 1 (eSCI_CR1) Configuration                                     */
/*-----------------------------------------------------------------------------------------------*/


/* Reset eSCI_CR1 register */
#define ESCI_LLM_CR1_Reset(offset)       ( REG_WRITE16(ESCI_CR1(offset), ESCI_CR1_RESET_MASK) )

/* Read eSCI_CR1 register */
#define ESCI_LLM_CR1_Read(offset)       ( REG_READ16(ESCI_CR1(offset)) )


/* Send Break Character. */
/* This bit controls the transmission of break characters. */
/* - 0 No break characters will be transmitted. */
/* - 1 Break characters will be transmitted. */
/* Note: This bit should be set in SCI mode only. */

#define ESCI_LLM_CR1_SBK_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_SBK_MASK) )
#define ESCI_LLM_CR1_SBK_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_SBK_MASK) )
#define ESCI_LLM_CR1_SBK_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) & \
                      ESCI_CR1_SBK_MASK) == ESCI_CR1_SBK_MASK)? TRUE : FALSE )



/* Receiver Wake-Up Mode. This bit controls and indicates the receiver wake-up mode */
/* - 0 Normal receiver operation. */
/* - 1 Receiver is in wake-up mode. */
/* Note: This bit should be set in SCI mode only. */

#define ESCI_LLM_CR1_RWU_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_RWU_MASK) )
#define ESCI_LLM_CR1_RWU_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_RWU_MASK) )
#define ESCI_LLM_CR1_RWU_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_RWU_MASK) == ESCI_CR1_RWU_MASK)? TRUE : FALSE )



/* RE - Receiver Enable. */
/* This control bit enables and disables the receiver. */
/* - 0 Receiver disabled. */
/* - 1 Receiver enabled. */

#define ESCI_LLM_CR1_RE_Enable(offset)     ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_RE_MASK) )
#define ESCI_LLM_CR1_RE_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_RE_MASK) )
#define ESCI_LLM_CR1_RE_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_RE_MASK) == ESCI_CR1_RE_MASK) ? TRUE : FALSE )



/* TE - Transmitter Enable. */
/* This control bit enables and disables the transmitter. */
/* - 0 Transmitter disabled. */
/* - 1 Transmitter enabled. */

#define ESCI_LLM_CR1_TE_Enable(offset)     ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_TE_MASK) )
#define ESCI_LLM_CR1_TE_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_TE_MASK) )
#define ESCI_LLM_CR1_TE_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_TE_MASK) == ESCI_CR1_TE_MASK) ? TRUE : FALSE )



/* ILIE - Idle Line Interrupt Enable. */
/* This bit controls theeSCI_IFSR1[IDLE] interrupt request generation. */
/* - 0 IDLE interrupt request generation disabled. */
/* - 1 IDLE interrupt request generation enabled. */

#define ESCI_LLM_CR1_ILIE_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_ILIE_MASK) )
#define ESCI_LLM_CR1_ILIE_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_ILIE_MASK))
#define ESCI_LLM_CR1_ILIE_Read(offset)    (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_ILIE_MASK) == ESCI_CR1_ILIE_MASK)? TRUE : FALSE)



/* RIE - Receiver Full Interrupt Enable. */
/* This bit controls the eSCI_IFSR1[RDRF] interrupt request generation. */
/* - 0 RDRF interrupt request generation disabled. */
/* - 1 RDRF interrupt request generation enabled. */

#define ESCI_LLM_CR1_RIE_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_RIE_MASK) )
#define ESCI_LLM_CR1_RIE_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_RIE_MASK) )
#define ESCI_LLM_CR1_RIE_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_RIE_MASK) == ESCI_CR1_RIE_MASK) ? TRUE : FALSE)



/* TCIE - Transmission Complete Interrupt Enable. */
/* This bit controls the eSCI_IFSR1[TC] interrupt request generation. */
/* - 0 TC interrupt request generation disabled. */
/* - 1 TC interrupt request generation enabled. */

#define ESCI_LLM_CR1_TCIE_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_TCIE_MASK) )
#define ESCI_LLM_CR1_TCIE_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_TCIE_MASK))
#define ESCI_LLM_CR1_TCIE_Read(offset)    (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_TCIE_MASK) == ESCI_CR1_TCIE_MASK) ? TRUE : FALSE)



/* TIE - Transmitter Interrupt Enable. */
/* This bit controls the eSCI_IFSR1[TRDE] interrupt request generation. */
/* - 0 TDRE interrupt request generation disabled. */
/* - 1 TDRE interrupt request generation enabled. */

#define ESCI_LLM_CR1_TIE_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_TIE_MASK) )
#define ESCI_LLM_CR1_TIE_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_TIE_MASK) )
#define ESCI_LLM_CR1_TIE_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_TIE_MASK) == ESCI_CR1_TIE_MASK) ? TRUE : FALSE)



/* PT - Parity Type.  */
/* This control bit defines whether even or odd parity has to be used. */
/* - 0 Even parity (even number of ones in character clears the parity bit). */
/* - 1 Odd parity (odd number of ones in character clears the parity bit). */

#define ESCI_LLM_CR1_PT_Enable(offset)     ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_PT_MASK) )
#define ESCI_LLM_CR1_PT_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_PT_MASK) )
#define ESCI_LLM_CR1_PT_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_PT_MASK) == ESCI_CR1_PT_MASK) ? TRUE : FALSE )



/* PE - Parity Enable.  */
/* This control bit enables the parity bit generation and checking. */
/* - 0 Parity bit generation and checking disabled. */
/* - 1 Parity bit generation and checking enabled. */

#define ESCI_LLM_CR1_PE_Enable(offset)     ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_PE_MASK) )
#define ESCI_LLM_CR1_PE_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_PE_MASK) )
#define ESCI_LLM_CR1_PE_Read(offset)      (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_PE_MASK) == ESCI_CR1_PE_MASK) ? TRUE : FALSE )


#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

/* ILT - Idle Line Type.  */
/* This control bit defines the type of idle line detection for the receiver wake-up. */
/* - 0 Idle line detection starts after reception of a low bit. */
/* - 1 Idle line detection starts after reception of the last stop bit. */

#define ESCI_LLM_CR1_ILT_Enable(offset)  ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_ILT_MASK) )
#define ESCI_LLM_CR1_ILT_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_ILT_MASK) )
#define ESCI_LLM_CR1_ILT_Read(offset)     (((REG_READ16(ESCI_CR1(offset)) &  \
           ESCI_CR1_ILT_MASK) == ESCI_CR1_ILT_MASK) ? TRUE : FALSE)


#endif
/* WAKE - Receiver Wake-up Condition.  */
/* This control bit defines the wake-up condition for the receiver. */
/* - 0 Idle line wake-up. */
/* - 1 Address mark wake-up */

#define ESCI_LLM_CR1_WAKE_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_WAKE_MASK) )
#define ESCI_LLM_CR1_WAKE_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_WAKE_MASK))
#define ESCI_LLM_CR1_WAKE_Read(offset)    (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_WAKE_MASK) == ESCI_CR1_WAKE_MASK)? TRUE : FALSE)



/* M - Frame Format Mode.*/
/* This control bit together with the M2 bit of the Control Register 3 (eSCI_CR3) controls the */
/* frame format used.  */

#define ESCI_LLM_CR1_M_Enable(offset)     ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_M_MASK) )
#define ESCI_LLM_CR1_M_Disable(offset)     ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_M_MASK) )
#define ESCI_LLM_CR1_M_Read(offset)        (((REG_READ16(ESCI_CR1(offset)) &  \
                      ESCI_CR1_M_MASK) == ESCI_CR1_M_MASK) ? TRUE : FALSE )


/* Loop Mode Select (LOOPS) and Receiver Source Control (RSRC) bits together defines the receiver *
 * source mode.                                           */

/* Receive Source Mode Selection */

/* |-----|-------|--------------------------| */
/* |LOOPS|  RSCR |  Receiver Input Mode     | */
/* |-----|-------|--------------------------| */
/* |  0   |   0  |  Dual Wire Mode          | */
/* |-----|-------|--------------------------| */
/* |  0  |   1   |  Reserved                | */
/* |-----|-------|--------------------------| */
/* |  1  |   0   |  Loop Mode               | */
/* |-----|-------|--------------------------| */
/* |  1  |   1   |  Single Wire Mode        | */
/* |-----|-------|--------------------------| */

/* LOOPS - Loop Mode Select. */
/* This control bit together with the RSRC control bit defines the receiver source mode. */

#define ESCI_LLM_CR1_LOOPS_Enable(offset)  ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_LOOPS_MASK) )
#define ESCI_LLM_CR1_LOOPS_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_LOOPS_MASK))
#define ESCI_LLM_CR1_LOOPS_Read(offset)  (((REG_READ16(ESCI_CR1(offset)) &  \
                     ESCI_CR1_LOOPS_MASK) == ESCI_CR1_LOOPS_MASK)? TRUE : FALSE)


/* RSRC - Receiver Source Control. */
/* This control bit together with the LOOPS control bit defines the receiver source mode. */

#define ESCI_LLM_CR1_RSRC_Enable(offset)   ( REG_BIT_SET16(ESCI_CR1(offset), ESCI_CR1_RSRC_MASK) )
#define ESCI_LLM_CR1_RSRC_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR1(offset), ESCI_CR1_RSRC_MASK))
#define ESCI_LLM_CR1_RSRC_Read(offset)   (((REG_READ16(ESCI_CR1(offset)) &  \
                     ESCI_CR1_RSRC_MASK) == ESCI_CR1_RSRC_MASK) ? TRUE : FALSE )


/* Configure ESCI_CR1 register */
#define ESCI_LLM_CR1_DUAL_WIRE_MODE_Config(offset)     ( REG_WRITE16(ESCI_CR1(offset),\
                              REG_READ16(ESCI_CR1(offset)) & \
                                ((~(ESCI_CR1_LOOPS_MASK)) & \
                                  (~(ESCI_CR1_RSRC_MASK))) ) )
#define ESCI_LLM_CR1_LOOP_MODE_Config(offset)       ( REG_WRITE16(ESCI_CR1(offset),\
                              REG_READ16(ESCI_CR1(offset)) | \
                                (ESCI_CR1_LOOPS_MASK & \
                                  (~(ESCI_CR1_RSRC_MASK)))) )
#define ESCI_LLM_CR1_SINGLE_WIRE_MODE_Config(offset)   ( REG_WRITE16(ESCI_CR1(offset),\
                              REG_READ16(ESCI_CR1(offset)) | \
                                ESCI_CR1_LOOPS_MASK | \
                                  ESCI_CR1_RSRC_MASK) )



/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*               Control Register 2 (eSCI_CR2) Configuration                                     */
/*-----------------------------------------------------------------------------------------------*/

/* Reset eSCI_CR2 register */
#define ESCI_LLM_CR2_Reset(offset)       ( REG_WRITE16(ESCI_CR2(offset), ESCI_CR2_RESET_MASK) )


/* Read eSCI_CR2 register */
#define ESCI_LLM_CR2_Read(offset)       ( REG_READ16(ESCI_CR2(offset)) )


/* MDIS - Module Disabled Mode. This bit controls the Module Mode of Operation */
/* - 0 Module is not in Disabled Mode. */
/* - 1 Module is in Disabled Mode. */

#define ESCI_LLM_DISABLE_ESCI_MODULE(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_MDIS_MASK))
#define ESCI_LLM_ENABLE_ESCI_MODULE(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_MDIS_MASK))
#define ESCI_LLM_CR2_MDIS_Read(offset)    (((REG_READ16(ESCI_CR2(offset)) &  \
                      ESCI_CR2_MDIS_MASK) == ESCI_CR2_MDIS_MASK)? TRUE : FALSE)



/* FBR - Fast Bit Error Detection. This bit controls the Bit Error Detection mode */
/* - 0 Standard Bit error detection performed. */
/* - 1 Fast Bit error detection performed. */
/* Note: This bit is used in LIN mode only. */

#define ESCI_LLM_CR2_FBR_Enable(offset)   ( REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_FBR_MASK) )
#define ESCI_LLM_CR2_FBR_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_FBR_MASK) )
#define ESCI_LLM_CR2_FBR_Read(offset)      (((REG_READ16(ESCI_CR2(offset)) &  \
                      ESCI_CR2_FBR_MASK) == ESCI_CR2_FBR_MASK) ? TRUE : FALSE)



/* BSTP - DMA Stop on Bit Error or Physical Bus Error.This bit controls the transmit DMA requests*/
/* generation in case of bit errors or physical bus errors. Bit errors are indicated by the BERR */
/* flag in the Interrupt Flag and Status Register 1 (eSCI_IFSR1) and physical bus errors are     */
/* indicated by the PBERR flag in the Interrupt Flag and Status Register 2 (eSCI_IFSR2).       */
/* - 0 Transmit DMA requests generated regardless of bit errors or physical bus errors.       */
/* - 1 Transmit DMA requests are not generated if eSCI_IFSR1[BERR] flag or eSCI_IFSR2[PBERR]     */
/* flags are set.                                           */
/* Note: This bit is used in LIN mode only.                             */

#define ESCI_LLM_CR2_BSTP_Enable(offset)   ( REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_BSTP_MASK) )
#define ESCI_LLM_CR2_BSTP_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_BSTP_MASK))
#define ESCI_LLM_CR2_BSTP_Read(offset)  (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_BSTP_MASK) == ESCI_CR2_BSTP_MASK) ? TRUE : FALSE )



/* BERRIE - Bit Error Interrupt Enable. This bit controls the BERR interrupt request generation. */
/* - 0 BERR interrupt request generation disabled. */
/* - 1 BERR interrupt request generation enabled. */

#define ESCI_LLM_CR2_BERRIE_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_BERRIE_MASK) )
#define ESCI_LLM_CR2_BERRIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset),ESCI_CR2_BERRIE_MASK))
#define ESCI_LLM_CR2_BERRIE_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                  ESCI_CR2_BERRIE_MASK) == ESCI_CR2_BERRIE_MASK)? TRUE : FALSE)



/* RXDMA - Receive DMA Control. This bit enables the receive DMA feature. */
/* - 0 Receive DMA disabled. */
/* - 1 Receive DMA enabled. */

#define ESCI_LLM_CR2_RXDMA_Enable(offset)   (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_RXDMA_MASK))
#define ESCI_LLM_CR2_RXDMA_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_RXDMA_MASK))
#define ESCI_LLM_CR2_RXDMA_Read(offset)  (((REG_READ16(ESCI_CR2(offset)) &  \
                     ESCI_CR2_RXDMA_MASK) == ESCI_CR2_RXDMA_MASK) ? TRUE : FALSE)



/* TXDMA - Transmit DMA Control. This bit enables the transmit DMA feature. */
/* - 0 Transmit DMA disabled. */
/* - 1 Transmit DMA enabled. */

#define ESCI_LLM_CR2_TXDMA_Enable(offset)   (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_TXDMA_MASK) )
#define ESCI_LLM_CR2_TXDMA_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_TXDMA_MASK))
#define ESCI_LLM_CR2_TXDMA_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_TXDMA_MASK) == ESCI_CR2_TXDMA_MASK) ? TRUE : FALSE)



/* BRCL - Break Character Length. This bit is used to define the length of the break character to *
 * be transmitted.                                           */

#define ESCI_LLM_CR2_BRCL_Enable(offset)   ( REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_BRCL_MASK) )
#define ESCI_LLM_CR2_BRCL_Disable(offset)  ( REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_BRCL_MASK))
#define ESCI_LLM_CR2_BRCL_Read(offset)   (((REG_READ16(ESCI_CR2(offset)) &  \
                     ESCI_CR2_BRCL_MASK) == ESCI_CR2_BRCL_MASK) ? TRUE : FALSE )



/* TXDIR - TXD pin output enable. This bit determines whether the TXD pin is used as an output. */
/* - 0 TXD pin is not used as output. */
/* - 1 TXD pin is used as output. */
/* Note: This bit is used in Single Wire Mode only. */

#define ESCI_LLM_CR2_TXDIR_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_TXDIR_MASK) )
#define ESCI_LLM_CR2_TXDIR_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_TXDIR_MASK))
#define ESCI_LLM_CR2_TXDIR_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_TXDIR_MASK) == ESCI_CR2_TXDIR_MASK) ? TRUE : FALSE)



/* BESM - Fast Bit Error Detection Sample Mode. This bit defines the sample point for the Fast */
/* Bit Error Detection Mode. */
/* - 0 Sample point is RS9. */
/* - 1 Sample point is RS13. */
/* Note: This bit is used in LIN mode only. */

#define ESCI_LLM_CR2_BESM_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_BESM_MASK) )
#define ESCI_LLM_CR2_BESM_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_BESM_MASK) )
#define ESCI_LLM_CR2_BESM_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                     ESCI_CR2_BESM_MASK) == ESCI_CR2_BESM_MASK) ? TRUE : FALSE )



/* BESTP - Transmit Stop on Bit Error. If this control bit is set, the eSCI stops driving the */
/* LIN bus immediately when a Bit */
/* Error has been detected, i.e. eSCI_IFSR1[BERR]=1. Additionally, the eSCI will not start a */
/* new byte transmission */
/* as long the BERR interrupt flag is set. */
/* - 0 Transmission is not stopped on bit error. */
/* - 1 Transmission is stopped on bit error. */
/* Note: This bit is used in LIN mode only. */

#define ESCI_LLM_CR2_BESTP_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_BESTP_MASK) )
#define ESCI_LLM_CR2_BESTP_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_BESTP_MASK))
#define ESCI_LLM_CR2_BESTP_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_BESTP_MASK) == ESCI_CR2_BESTP_MASK) ? TRUE : FALSE)



/* RXPOL - RXD Pin polarity. This bit controls the polarity of the RXD pin.  */
/* - 0 Normal Polarity. */
/* - 1 Inverted Polarity. */

#define ESCI_LLM_CR2_RXPOL_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_RXPOL_MASK) )
#define ESCI_LLM_CR2_RXPOL_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_RXPOL_MASK))
#define ESCI_LLM_CR2_RXPOL_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_RXPOL_MASK) == ESCI_CR2_RXPOL_MASK) ? TRUE : FALSE)



/* PMSK - Parity Bit Masking. This bit defines whether the received parity bit is presented in */
/* the related bit position in the SCI Data Register (eSCI_SDR). */
/* - 0 The received parity bit is presented in the bit position related to the parity bit. */
/* - 1 The value 0 is presented in the bit position related to the parity bit. */

#define ESCI_LLM_CR2_PMSK_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_PMSK_MASK) )
#define ESCI_LLM_CR2_PMSK_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_PMSK_MASK) )
#define ESCI_LLM_CR2_PMSK_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                     ESCI_CR2_PMSK_MASK) == ESCI_CR2_PMSK_MASK) ? TRUE : FALSE )



/* ORIE - Overrun Interrupt Enable. This bit controls the eSCI_IFSR1[OR] interrupt request */
/* generation. */
/* - 0 OR interrupt request generation disabled. */
/* - 1 OR interrupt request generation enabled. */

#define ESCI_LLM_CR2_ORIE_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_ORIE_MASK) )
#define ESCI_LLM_CR2_ORIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_ORIE_MASK) )
#define ESCI_LLM_CR2_ORIE_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_ORIE_MASK) == ESCI_CR2_ORIE_MASK) ? TRUE : FALSE )



/* NFIE - Noise Interrupt Enable. This bit controls the eSCI_IFSR1[NF] interrupt request */
/* generation */
/* - 0 NF interrupt request generation disabled. */
/* - 1 NF interrupt request generation enabled. */


#define ESCI_LLM_CR2_NFIE_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_NFIE_MASK) )
#define ESCI_LLM_CR2_NFIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_NFIE_MASK) )
#define ESCI_LLM_CR2_NFIE_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_NFIE_MASK) == ESCI_CR2_NFIE_MASK) ? TRUE : FALSE )



/* FEIE - Frame Error Interrupt Enable. This bit controls the eSCI_IFSR1[FE] interrupt */
/* request generation. */
/* - 0 FE interrupt request generation disabled. */
/* - 1 FE interrupt request generation enabled. */

#define ESCI_LLM_CR2_FEIE_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_FEIE_MASK) )
#define ESCI_LLM_CR2_FEIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_FEIE_MASK) )
#define ESCI_LLM_CR2_FEIE_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_FEIE_MASK) == ESCI_CR2_FEIE_MASK) ? TRUE : FALSE )



/* PFIE - Parity Error Interrupt Enable. This bit controls the eSCI_IFSR1[PF] interrupt request */
/* generation. */
/* - 0 PF interrupt request generation disabled. */
/* - 1 PF interrupt request generation enabled. */


#define ESCI_LLM_CR2_PFIE_Enable(offset) (REG_BIT_SET16(ESCI_CR2(offset), ESCI_CR2_PFIE_MASK) )
#define ESCI_LLM_CR2_PFIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR2(offset), ESCI_CR2_PFIE_MASK) )
#define ESCI_LLM_CR2_PFIE_Read(offset) (((REG_READ16(ESCI_CR2(offset)) &  \
                    ESCI_CR2_PFIE_MASK) == ESCI_CR2_PFIE_MASK) ? TRUE : FALSE )



/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*               SCI Data Register (eSCI_SDR) Configuration                                      */
/*-----------------------------------------------------------------------------------------------*/

/* Reset eSCI_SDR register */
#define ESCI_LLM_SDR_Reset(offset)     (REG_WRITE16(ESCI_SDR(offset), ESCI_SDR_RESET_MASK) )

/* Read eSCI_SDR register */
#define ESCI_LLM_SDR_Read(offset)     (REG_READ16(ESCI_SDR(offset)) )

/* Read data [0..7] from eSCI_SDR register */
#define ESCI_LLM_SDR_DATA_READ(offset) (REG_READ16(ESCI_SDR(offset)) & ESCI_SDR_RD_TD_7_0_MASK )

/* Read address [8..11] from eSCI_SDR register */
#define ESCI_LLM_SDR_ADDRESS_READ(offset) (REG_READ16(ESCI_SDR(offset)) & ESCI_SDR_RD_11_8_MASK )

/* ERR - Receive Error Bit. This bit indicates the occurrence of the errors selected by the */
/* Control Register 3 (eSCI_CR3) during the reception of the frame presented in SCI Data */
/* Register (eSCI_SDR). In case of an overrun error for subsequent frames this bit is set too. */
/* - 0 None of the selected errors occured. */
/* - 1 At least one of the selected errors occured. */

#define ESCI_LLM_SDR_ERROR_FLAG_READ(offset) (((REG_READ16(ESCI_SDR(offset)) &  \
                  ESCI_SDR_ERR_MASK) == ESCI_SDR_ERR_MASK) ? TRUE : FALSE)


/*************************************************************************************************/



/**
 * @file Reg_eSys_ESCI.h
 * @note Violates MISRA 2004 Required Rule 1.4, Identifier clash: 
 *       See @ref REG_ESYS_ESCI_H_REF_2
 *       Violation for below block of code
 */


/*-----------------------------------------------------------------------------------------------*/
/*       Interrupt Flag and Status Register 1 (eSCI_IFSR1) Configuration                         */
/*-----------------------------------------------------------------------------------------------*/


/* Read eSCI_IFSR1 register */
#define ESCI_LLM_IFSR1_Read(offset)     (REG_READ16(ESCI_IFSR1(offset)) )


/* TDRE - Transmit Data Register Empty Interrupt Flag. This interrupt flag is set when the */
/* content of the SCI Data Register (eSCI_SDR) was transferred into internal shift register. */
/* Note: This flag is set in SCI mode only. */

#define ESCI_LLM_IFSR1_IS_TX_DATA_REG_EMPTY(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_TDRE_MASK) == ESCI_IFSR1_TDRE_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_TX_DATA_REG_EMPTY_Clear(offset)   ( REG_WRITE16(ESCI_IFSR1(offset),\
                              (ESCI_IFSR1_TDRE_MASK)) )



/* TC - Transmit Complete Interrupt Flag. This interrupt flag is set when a frame, break or */
/* idle character transmission has been completed and no data were written into SCI Data Register*/
/* (eSCI_SDR) after the last setting of the TDRE flag and the SBK bit in Control Register 1 */
/* (eSCI_CR1) is 0. */
/* This flag is set in LIN mode, if the preamble was transmitted after the enabling of the */
/* transmitter. */

#define ESCI_LLM_IFSR1_TX_COMPLETE_READ(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                    ESCI_IFSR1_TC_MASK) == ESCI_IFSR1_TC_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_TX_COMPLETE_Clear(offset)   (REG_WRITE16(ESCI_IFSR1(offset), \
                           ESCI_IFSR1_TC_MASK))



/* RDRF - Receive Data Register Full Interrupt Flag. This interrupt flag is set when */
/* the payload data of a received frame was transferred into the SCI Data Register (eSCI_SDR). */
/* Note: This flag is set in SCI mode only. */

#define ESCI_LLM_IFSR1_IS_RX_DATA_REG_FULL(offset) (((REG_READ16(ESCI_IFSR1(offset)) & \
                  ESCI_IFSR1_RDRF_MASK) == ESCI_IFSR1_RDRF_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_RX_DATA_REG_FULL_Clear(offset)   ( REG_WRITE16(ESCI_IFSR1(offset), \
                              ESCI_IFSR1_RDRF_MASK) )



/* IDLE - Idle Line Interrupt Flag. This interrupt flag is set when an idle character was */
/* detected and the receiver is not in the wakeup state. */
/* Note: This flag is set in SCI mode only. */

#define ESCI_LLM_IFSR1_ILDE_LINE_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_IDLE_MASK) == ESCI_IFSR1_IDLE_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_ILDE_LINE_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR1(offset), \
                              ESCI_IFSR1_IDLE_MASK) )



/* OR - Overrun Interrupt Flag. This interrupt flag is set when an overrun was detected  */
/* Note: This flag is set in SCI mode only. */

#define ESCI_LLM_IFSR1_OVERRUN_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                    ESCI_IFSR1_OR_MASK) == ESCI_IFSR1_OR_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_OVERRUN_FLAG_Clear(offset) (REG_WRITE16(ESCI_IFSR1(offset), \
                           ESCI_IFSR1_OR_MASK) )



/* NF - Noise Interrupt Flag. This interrupt flag is set when the payload data of a received */
/* frame was transferred into the SCI Data Register (eSCI_SDR) or LIN Receive Register (eSCI_LRR)*/
/* and the receiver has detected noise during the reception of that frame. */

#define ESCI_LLM_IFSR1_NOISE_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                    ESCI_IFSR1_NF_MASK) == ESCI_IFSR1_NF_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_NOISE_FLAG_Clear(offset)(REG_WRITE16(ESCI_IFSR1(offset),ESCI_IFSR1_NF_MASK))



/* FE - Framing Error Interrupt Flag. This interrupt flag is set when the payload data of a */
/* received frame was transferred into the SCI Data Register (eSCI_SDR) or LIN Receive Register */
/* (eSCI_LRR) and the receiver has detected a framing error during the reception of that frame. */

#define ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(offset)    ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                    ESCI_IFSR1_FE_MASK) == ESCI_IFSR1_FE_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(offset) ( REG_WRITE16(ESCI_IFSR1(offset), \
                              ESCI_IFSR1_FE_MASK) )



/* PF - Parity Error Interrupt Flag. This interrupt flag is set when the payload data of a */
/* received frame was transferred into the SCI Data Register (eSCI_SDR) and the receiver has */
/* detected a parity error for the character */
/* Note: This flag is set in SCI mode only. */

#define ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_READ(offset) ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                    ESCI_IFSR1_PF_MASK) == ESCI_IFSR1_PF_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR1(offset), \
                              ESCI_IFSR1_PF_MASK) )


#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

/* DACT - DMA Active. The status bit is set when a transmit or receive DMA request is pending. */
/* - 0 No DMA request pending. */
/* - 1 DMA request pending. */

#define ESCI_LLM_IFSR1_IS_DMA_ACTIVE(offset)   ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_DACT_MASK) == ESCI_IFSR1_DACT_MASK) ? TRUE : FALSE )

#endif
/* BERR - Bit Error Interrupt Flag. This flag is set when a bit error was detected. */
/* Note: This flag is set in LIN mode only. */

#define ESCI_LLM_IFSR1_BIT_ERROR_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_BERR_MASK) == ESCI_IFSR1_BERR_MASK) ? TRUE : FALSE )

#define ESCI_LLM_IFSR1_BIT_ERROR_FLAG_Clear(offset) ( REG_WRITE16(ESCI_IFSR1(offset), \
                            ESCI_IFSR1_BERR_MASK) )

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

/* WACT - LIN Wake-Up Active. The status bit is set as long as the LIN wakeup engine */
/* receives a LIN wake-up signal. */
/* This bit will be cleared, when an idle character was detected. */
/* - 0 No LIN wakeup signal reception in progress. */
/* - 1 LIN wakeup signal reception in progress. */

#define ESCI_LLM_IFSR1_IS_WAKEUP_ACTIVE(offset) ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_WACT_MASK) == ESCI_IFSR1_WACT_MASK) ? TRUE : FALSE )



/* LACT - LIN Active. This status bit is set as long as the LIN protocol engine */
/* is about to transmit or receive LIN frames. */
/* - 0 No LIN frame transmission or reception in progress. */
/* - 1 LIN frame transmission or reception in progress. */

#define ESCI_LLM_IFSR1_IS_LIN_ACTIVE(offset)   ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_LACT_MASK) == ESCI_IFSR1_LACT_MASK) ? TRUE : FALSE )

#endif


/* TACT - Transmitter Active. The status bit is set as long as the transmission of a frame or */
/* special character is ongoing. */
/* - 0 No transmission in progress. */
/* - 1 Transmission in progress. */

#define ESCI_LLM_IFSR1_IS_TX_ACTIVE(offset)   ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_TACT_MASK) == ESCI_IFSR1_TACT_MASK) ? TRUE : FALSE )



/* RACT - Receiver Active. The bit will be set 3 receiver clock (RCLK) cycles after the */
/* successful qualification of a start bit. */
/* This bit will be cleared, when an idle character was detected. */
/* - 0 No reception in progress. */
/* - 1 Reception in progress. */

#define ESCI_LLM_IFSR1_IS_RX_ACTIVE(offset) ( ( ( REG_READ16(ESCI_IFSR1(offset)) &  \
                  ESCI_IFSR1_RACT_MASK) == ESCI_IFSR1_RACT_MASK) ? TRUE : FALSE )


/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*       Interrupt Flag and Status Register 2 (eSCI_IFSR2) Configuration                         */
/*-----------------------------------------------------------------------------------------------*/

/* Read eSCI_IFSR2 register */
#define ESCI_LLM_IFSR2_Read(offset) ( REG_READ16(ESCI_IFSR2(offset)) )


/* RXRDY - Receive Data Ready Interrupt Flag. This interrupt flag is set when the payload data of*/
/* a received frame was transferred into the LIN Receive Register (eSCI_LRR). */

#define ESCI_LLM_IS_RX_READY(offset)    ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_RXRDY_MASK) == ESCI_IFSR2_RXRDY_MASK) ? TRUE : FALSE)

#define ESCI_LLM_RX_READY_Clear(offset)   (REG_WRITE16(ESCI_IFSR2(offset), ESCI_IFSR2_RXRDY_MASK))



/* TXRDY - Transmit Data Ready Interrupt Flag. This interrupt flag is set when the content of the*/
/* LIN Transmit Register (eSCI_LTR) was process by the LIN PE either to generate a frame header */
/* or to transmit frame data. */

#define ESCI_LLM_IS_TX_READY(offset)      ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_TXRDY_MASK) == ESCI_IFSR2_TXRDY_MASK) ? TRUE : FALSE)

#define ESCI_LLM_TX_READY_Clear(offset)   (REG_WRITE16(ESCI_IFSR2(offset), ESCI_IFSR2_TXRDY_MASK))



/* LWAKE - LIN Wakeup Received Interrupt Flag. This interrupt flag is set when a LIN Wakeup */
/* character was received */

#define ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_READ(offset)    ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_LWAKE_MASK) == ESCI_IFSR2_LWAKE_MASK) ? TRUE : FALSE)

#define ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR2(offset), \
                                ESCI_IFSR2_LWAKE_MASK) )



/* STO - Slave Timeout Interrupt Flag. This interrupt flag is set when a Slave-Not-Responding */
/* -Error is detected.  */

#define ESCI_LLM_SLAVE_TIMEOUT_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR2(offset)) &  \
                    ESCI_IFSR2_STO_MASK) == ESCI_IFSR2_STO_MASK) ? TRUE : FALSE)

#define ESCI_LLM_SLAVE_TIMEOUT_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR2(offset), \
                            ESCI_IFSR2_STO_MASK) )



/* PBERR - Physical Bus Error Interrupt Flag. This interrupt flag is set when the receiver input */
/* remains unchanged for at least 31 RCLK clock cycles after the start of a byte transmission */

#define ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_READ(offset)    ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_PBERR_MASK) == ESCI_IFSR2_PBERR_MASK) ? TRUE : FALSE)

#define ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR2(offset), \
                              ESCI_IFSR2_PBERR_MASK) )



/* CERR - CRC Error Interrupt Flag. This interrupt flag is set when an incorrect CRC pattern was */
/* detected for a received LIN frame. */

#define ESCI_LLM_CRC_ERROR_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_CERR_MASK) == ESCI_IFSR2_CERR_MASK) ? TRUE : FALSE )

#define ESCI_LLM_CRC_ERROR_FLAG_Clear(offset) (REG_WRITE16(ESCI_IFSR2(offset), \
                         ESCI_IFSR2_CERR_MASK) )



/* CKERR - Checksum Error Interrupt Flag. This interrupt flag is set when a checksum error was */
/* detected for a received LIN frame. */

#define ESCI_LLM_CHECKSUM_ERROR_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_CKERR_MASK) == ESCI_IFSR2_CKERR_MASK) ? TRUE : FALSE)

#define ESCI_LLM_CHECKSUM_ERROR_FLAG_Clear(offset)     ( REG_WRITE16(ESCI_IFSR2(offset), \
                              ESCI_IFSR2_CKERR_MASK) )



/* FRC - Frame Complete Interrupt Flag. This interrupt flag is set when a LIN TX frame has been */
/* completely transmitted or a LIN RX frame has been completely received. */

#define ESCI_LLM_FRAME_COMPLETE_FLAG_READ(offset) (((REG_READ16(ESCI_IFSR2(offset)) &  \
                    ESCI_IFSR2_FRC_MASK) == ESCI_IFSR2_FRC_MASK) ? TRUE : FALSE)

#define ESCI_LLM_FRAME_COMPLETE_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR2(offset), \
                            ESCI_IFSR2_FRC_MASK) )



/* UREQ - Unrequested Data Received Interrupt Flag. This interrupt flag is set when unrequested */
/* activity has been detected on the LIN bus. */

#define ESCI_LLM_UNREQUESTED_DATA_FLAG_READ(offset)      ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_UREQ_MASK) == ESCI_IFSR2_UREQ_MASK) ? TRUE : FALSE )

#define ESCI_LLM_UNREQUESTED_DATA_FLAG_Clear(offset)   ( REG_WRITE16(ESCI_IFSR2(offset), \
                              ESCI_IFSR2_UREQ_MASK) )



/* OVFL - Overflow Interrupt Flag. This interrupt flag is set when an overflow */

#define ESCI_LLM_OVERFLOW_FLAG_READ(offset)      ( ( ( REG_READ16(ESCI_IFSR2(offset)) &  \
                  ESCI_IFSR2_OVFL_MASK) == ESCI_IFSR2_OVFL_MASK) ? TRUE : FALSE )

#define ESCI_LLM_OVERFLOW_FLAG_Clear(offset)   (REG_WRITE16(ESCI_IFSR2(offset), \
                         ESCI_IFSR2_OVFL_MASK) )



/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*             LIN Control Register 1 (eSCI_LCR1) Configuration                                  */
/*-----------------------------------------------------------------------------------------------*/

/* Read eSCI_LCR1 register */
#define ESCI_LLM_LCR1_Read(offset)     (REG_READ16(ESCI_LCR1(offset)) )


/* Reset eSCI_LCR1 register */
#define ESCI_LLM_LCR1_Reset(offset)   (REG_WRITE16(ESCI_LCR1(offset), ESCI_LCR1_RESET_MASK) )


/* LRES - LIN Protocol Engine Reset. This bit controls the mode of the LIN protocol engine. */
/* - 0 LIN protocol engine in operational mode. */
/* - 1 LIN protocol engine forced into idle state. */

#define ESCI_LLM_LCR1_LRES_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_LRES_MASK) )
#define ESCI_LLM_LCR1_LRES_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_LRES_MASK))
#define ESCI_LLM_LCR1_LRES_Read(offset) (((REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_LRES_MASK) == ESCI_LCR1_LRES_MASK) ? TRUE : FALSE)



/* WU - LIN Bus Wake-Up Trigger. This bit is used to trigger the generation of a wake-up signal */
/* on the LIN bus */
/* - 0 Write has no effect. */
/* - 1 Write triggers the generation of a wakeup signal. */

#define ESCI_LLM_LCR1_WU_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_WU_MASK) )
#define ESCI_LLM_LCR1_WU_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset), ESCI_LCR1_WU_MASK) )
#define ESCI_LLM_LCR1_WU_Read(offset) (((REG_READ16(ESCI_LCR1(offset)) &  \
                      ESCI_LCR1_WU_MASK) == ESCI_LCR1_WU_MASK) ? TRUE : FALSE)



/* WUD - LIN Bus Wake-Up Delimiter Time. This field determines how long the LIN protocol engine */
/* waits after the end of the transmitted wakeup signal, before starting the next LIN frame */
/* transmission. */

/* |------|-------|--------------------------| */
/* |WUD[1]|WUD[0] |  Wake-Up Delimiter       | */
/* |------|-------|--------------------------| */
/* |  0    |   0   |  4 bit                  | */
/* |------|-------|--------------------------| */
/* |  0   |   1   |  8 bit                   | */
/* |----- |-------|--------------------------| */
/* |  1   |   0   |  16 bit                  | */
/* |----- |-------|--------------------------| */
/* |  1   |   1   |  32 bit                  | */
/* |----- |-------|--------------------------| */

#define ESCI_LLM_LCR1_WUD_FOUR_BIT_Enable(offset)   (REG_WRITE16(ESCI_LCR1(offset),\
                            REG_READ16(ESCI_LCR1(offset)) | \
                              ESCI_LCR1_WUD_FOUR_BIT_MASK) )

#define ESCI_LLM_LCR1_WUD_EIGHT_BIT_Enable(offset)   (REG_WRITE16(ESCI_LCR1(offset), \
                            REG_READ16(ESCI_LCR1(offset)) | \
                            ESCI_LCR1_WUD_EIGHT_BIT_MASK) )

#define ESCI_LLM_LCR1_WUD_THIRTY_TWO_BIT_Enable(offset) ( REG_WRITE16(ESCI_LCR1(offset),\
                              REG_READ16(ESCI_LCR1(offset)) | \
                                ESCI_LCR1_WUD_THIRTY_TWO_BIT_MASK) )

#define ESCI_LLM_LCR1_WUD_SIXTY_FOUR_BIT_Enable(offset) ( REG_WRITE16(ESCI_LCR1(offset), \
                              REG_READ16(ESCI_LCR1(offset)) | \
                              ESCI_LCR1_WUD_SIXTY_FOUR_BIT_MASK) )

#define ESCI_LLM_LCR1_WUD_Read(offset)         (REG_READ16(ESCI_LCR1(offset)) &  \
                           ESCI_LCR1_WUD_SIXTY_FOUR_BIT_MASK)



/* PRTY - Parity Generation Control. This bit controls the generation of the two parity bits */
/* in the LIN header. */
/* - 0 Parity bits generation disabled. */
/* - 1 Parity bits generation enabled. */

#define ESCI_LLM_LCR1_PRTY_Enable(offset)   (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_PRTY_MASK))
#define ESCI_LLM_LCR1_PRTY_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_PRTY_MASK))
#define ESCI_LLM_LCR1_PRTY_Read(offset)      ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_PRTY_MASK) == ESCI_LCR1_PRTY_MASK) ? TRUE : FALSE)



/* LIN - LIN Mode Control. This bit controls whether the device is in SCI or LIN Mode. */
/* - 0 SCI Mode. */
/* - 1 LIN Mode. */

#define ESCI_LLM_LCR1_LIN_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_LIN_MASK) )
#define ESCI_LLM_LCR1_LIN_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset), ESCI_LCR1_LIN_MASK) )
#define ESCI_LLM_LCR1_LIN_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_LIN_MASK) == ESCI_LCR1_LIN_MASK) ? TRUE : FALSE )



/* RXIE - Receive Data Ready Interrupt Enable. This bit controls the eSCI_IFSR2[RXRDY] interrupt */
/* request generation. */
/* - 0 RXRDY interrupt request generation disabled. */
/* - 1 RXRDY interrupt request generation enabled. */

#define ESCI_LLM_LCR1_RXIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_RXIE_MASK) )
#define ESCI_LLM_LCR1_RXIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_RXIE_MASK))
#define ESCI_LLM_LCR1_RXIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_RXIE_MASK) == ESCI_LCR1_RXIE_MASK) ? TRUE : FALSE)



/* TXIE - Transmit Data Ready Interrupt Enable. This bit controls the eSCI_IFSR2[TXRDY] interrupt*/
/* request generation. */
/* - 0 TXRDY interrupt request generation disabled. */
/* - 1 TXRDY interrupt request generation enabled. */

#define ESCI_LLM_LCR1_TXIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_TXIE_MASK) )
#define ESCI_LLM_LCR1_TXIE_Disable(offset)(REG_BIT_CLEAR16(ESCI_LCR1(offset), ESCI_LCR1_TXIE_MASK))
#define ESCI_LLM_LCR1_TXIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_TXIE_MASK) == ESCI_LCR1_TXIE_MASK) ? TRUE : FALSE)



/* WUIE - LIN Wakeup Received Interrupt Enable. This bit controls the eSCI_IFSR2[LWAKE] interrupt*/
/* request generation. */
/* - 0 LWAKE interrupt request generation disabled. */
/* - 1 LWAKE interrupt request generation enabled. */

#define ESCI_LLM_LCR1_WUIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_WUIE_MASK) )
#define ESCI_LLM_LCR1_WUIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_WUIE_MASK))
#define ESCI_LLM_LCR1_WUIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_WUIE_MASK) == ESCI_LCR1_WUIE_MASK) ? TRUE : FALSE)



/* STIE - Slave Timeout Flag Interrupt Enable. This bit controls the eSCI_IFSR2[STO] interrupt */
/* request generation. */
/* - 0 STO interrupt request generation disabled. */
/* - 1 STO interrupt request generation enabled. */

#define ESCI_LLM_LCR1_STIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_STIE_MASK) )
#define ESCI_LLM_LCR1_STIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_STIE_MASK))
#define ESCI_LLM_LCR1_STIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_STIE_MASK) == ESCI_LCR1_STIE_MASK) ? TRUE : FALSE)



/* PBIE - Physical Bus Error Interrupt Enable. This bit controls the eSCI_IFSR2[PBERR] interrupt */
/* request generation. */
/* - 0 PBERR interrupt request generation disabled. */
/* - 1 PBERR interrupt request generation enabled. */

#define ESCI_LLM_LCR1_PBIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_PBIE_MASK) )
#define ESCI_LLM_LCR1_PBIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_PBIE_MASK))
#define ESCI_LLM_LCR1_PBIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_PBIE_MASK) == ESCI_LCR1_PBIE_MASK) ? TRUE : FALSE)



/* CIE - CRC Error Interrupt Enable. This bit controls the eSCI_IFSR2[CERR] interrupt request */
/* generation. */
/* - 0 CERR interrupt request generation disabled. */
/* - 1 CERR interrupt request generation enabled. */

#define ESCI_LLM_LCR1_CIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_CIE_MASK) )
#define ESCI_LLM_LCR1_CIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset), ESCI_LCR1_CIE_MASK) )
#define ESCI_LLM_LCR1_CIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_CIE_MASK) == ESCI_LCR1_CIE_MASK) ? TRUE : FALSE )



/* CKIE - Checksum Error Interrupt Enable. This bit controls the eSCI_IFSR2[CKERR] interrupt */
/* request generation. */
/* - 0 CKERR interrupt request generation disabled. */
/* - 1 CKERR interrupt request generation enabled. */

#define ESCI_LLM_LCR1_CKIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_CKIE_MASK) )
#define ESCI_LLM_LCR1_CKIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_CKIE_MASK))
#define ESCI_LLM_LCR1_CKIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_CKIE_MASK) == ESCI_LCR1_CKIE_MASK) ? TRUE : FALSE)



/* FCIE - Frame Complete Interrupt Enable.This bit controls the eSCI_IFSR2[FRC] interrupt request*/
/* generation. */
/* - 0 FRC interrupt request generation disabled. */
/* - 1 FRC interrupt request generation enabled. */

#define ESCI_LLM_LCR1_FCIE_Enable(offset) (REG_BIT_SET16(ESCI_LCR1(offset), ESCI_LCR1_FCIE_MASK) )
#define ESCI_LLM_LCR1_FCIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR1(offset),ESCI_LCR1_FCIE_MASK))
#define ESCI_LLM_LCR1_FCIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR1(offset)) &  \
                    ESCI_LCR1_FCIE_MASK) == ESCI_LCR1_FCIE_MASK) ? TRUE : FALSE)


/*************************************************************************************************/





/*-----------------------------------------------------------------------------------------------*/
/*             LIN Control Register 2 (eSCI_LCR2) Configuration                                  */
/*-----------------------------------------------------------------------------------------------*/


/* Read eSCI_LCR2 register */
#define ESCI_LLM_LCR2_Read(offset)       (REG_READ16(ESCI_LCR2(offset)) )


/* Reset eSCI_LCR2 register */
#define ESCI_LLM_LCR2_Reset(offset)     (REG_WRITE16(ESCI_LCR2(offset), ESCI_LCR2_RESET_MASK) )


/* UQIE - Unrequested Data Received Interrupt Enable. This bit controls the eSCI_IFSR2[UREQ] */
/* interrupt request generation. */
/* - 0 UREQ interrupt request generation disabled. */
/* - 1 UREQ interrupt request generation enabled. */

#define ESCI_LLM_LCR2_UQIE_Enable(offset)   (REG_BIT_SET16(ESCI_LCR2(offset), ESCI_LCR2_UQIE_MASK))
#define ESCI_LLM_LCR2_UQIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR2(offset),ESCI_LCR2_UQIE_MASK))
#define ESCI_LLM_LCR2_UQIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR2(offset)) &  \
                    ESCI_LCR2_UQIE_MASK) == ESCI_LCR2_UQIE_MASK) ? TRUE : FALSE)



/* OFIE - Overflow Interrupt Enable. This bit controls the eSCI_IFSR2[OVFL] interrupt request */
/* generation. */
/* - 0 OVFL interrupt request generation disabled. */
/* - 1 OVFL interrupt request generation enabled. */

#define ESCI_LLM_LCR2_OFIE_Enable(offset)   (REG_BIT_SET16(ESCI_LCR2(offset), ESCI_LCR2_OFIE_MASK))
#define ESCI_LLM_LCR2_OFIE_Disable(offset) (REG_BIT_CLEAR16(ESCI_LCR2(offset),ESCI_LCR2_OFIE_MASK))
#define ESCI_LLM_LCR2_OFIE_Read(offset) ( ( ( REG_READ16(ESCI_LCR2(offset)) &  \
                    ESCI_LCR2_OFIE_MASK) == ESCI_LCR2_OFIE_MASK) ? TRUE : FALSE)


/*************************************************************************************************/






/*-----------------------------------------------------------------------------------------------*/
/*             LIN Transmit Register (eSCI_LTR) Configuration                                    */
/*-----------------------------------------------------------------------------------------------*/

/* Configure the ESCI_LTR register */
#define ESCI_LLM_LTR_Conf(offset, value)          (  REG_WRITE8(ESCI_LTR(offset), (value)) )

/* Read eSCI_LTR register */
#define ESCI_LLM_LTR_Read(offset)       (REG_READ8(ESCI_LTR(offset)) )


/* Reset eSCI_LTR register */
#define ESCI_LLM_LTR_Reset(offset)       (REG_WRITE8(ESCI_LTR(offset), ESCI_LTR_RESET_MASK) )


/* P - Identifier Parity. This field provides the identifier parity which is used to create the */
/* protected identifier if the automatic identifier parity generation is disabled, i.e the PRTY */
/* bit in LIN Control Register 1 (eSCI_LCR1) is 0. */

#define ESCI_LLM_LTR_IDENTIFIER_PARITY_Enable(offset) ( REG_BIT_SET8(ESCI_LTR(offset), \
                                   ESCI_LTR_P_MASK) )

#define ESCI_LLM_LTR_IDENTIFIER_PARITY_Disable(offset)   ( REG_BIT_CLEAR8(ESCI_LTR(offset), \
                                     ESCI_LTR_P_MASK) )
#define ESCI_LLM_LTR_IDENTIFIER_PARITY_Read(offset)      ( ( ( REG_READ8(ESCI_LTR(offset)) &  \
                        ESCI_LTR_P_MASK) == ESCI_LTR_P_MASK) ? TRUE : FALSE)



/* ID - Identifier. This field is used for the identifier field in the protected identifier. */

#define ESCI_LLM_LTR_INDENTIFIER_Clear(offset) (REG_WRITE8(ESCI_LTR(offset), \
                        REG_READ16(ESCI_LTR(offset)) & (~ESCI_LTR_ID_MASK)))
#define ESCI_LLM_LTR_INDENTIFIER_Config(offset, value)   ( REG_WRITE8(ESCI_LTR(offset), \
                              REG_READ16(ESCI_LTR(offset)) | \
                              (value & ESCI_LTR_ID_MASK)) )

#define ESCI_LLM_LTR_INDENTIFIER_Read(offset) (REG_READ18(ESCI_LTR(offset)) & ESCI_LTR_ID_MASK)


/* LEN Frame Length. This field defines the number of data bytes to be transmitted or received. */

#define ESCI_LLM_LTR_FRAME_LENGTH_Clear(offset) (REG_WRITE8(ESCI_LTR(offset), \
                         REG_READ16(ESCI_LTR(offset)) & \
                         (~ ESCI_LTR_LEN_MASK)) )

#define ESCI_LLM_LTR_FRAME_LENGTH_Config(offset, value)   ( REG_WRITE8(ESCI_LTR(offset), \
                                REG_READ16(ESCI_LTR(offset)) | \
                                (value & ESCI_LTR_LEN_MASK)) )
#define ESCI_LLM_LTR_FRAME_LENGTH_Read(offset)   (REG_READ8(ESCI_LTR(offset)) & ESCI_LTR_LEN_MASK)



/* CSM - Checksum Model. This bit controls the checksum calculation model used. */
/* - 0 Classic Checksum Model (LIN 1.3). */
/* - 1 Enhanced Checksum Model (LIN 2.0). */

#define ESCI_LLM_LTR_CHECKSUM_ENHANCED_Enable(offset) ( REG_BIT_SET8(ESCI_LTR(offset), \
                                   ESCI_LTR_CSM_MASK) )

#define ESCI_LLM_LTR_CHECKSUM_CLASSIC_Enable(offset) ( REG_BIT_CLEAR8(ESCI_LTR(offset), \
                                    ESCI_LTR_CSM_MASK) )

#define ESCI_LLM_LTR_IS_CHECKSUM_ENHANCED(offset)      ( ( ( REG_READ8(ESCI_LTR(offset)) &  \
                      ESCI_LTR_CSM_MASK) == ESCI_LTR_CSM_MASK) ? TRUE : FALSE)



/* CSE - Checksum Enable. This bit control the generation and checking of the checksum byte. */
/* - 0 No generation and checking of checksum byte. */
/* - 1 Generation and checking of checksum byte. */

#define ESCI_LLM_LTR_CHECKSUM_Enable(offset) (REG_BIT_SET8(ESCI_LTR(offset), ESCI_LTR_CSE_MASK) )
#define ESCI_LLM_LTR_CHECKSUM_Disable(offset) (REG_BIT_CLEAR8(ESCI_LTR(offset), ESCI_LTR_CSE_MASK))
#define ESCI_LLM_LTR_IS_CHECKSUM_ENABLED(offset)      ( ( ( REG_READ8(ESCI_LTR(offset)) &  \
                      ESCI_LTR_CSE_MASK) == ESCI_LTR_CSE_MASK) ? TRUE : FALSE)



/* CRC - CRC Enable. This bit controls the generation of checking standard or enhanced LIN frames*/
/* - 0 Standard LIN frame generation and checking. */
/* - 1 Enhanced LIN frame generation and checking. */

#define ESCI_LLM_CRC_ENHANCED_LIN_FRMAE_Enable(offset) (REG_BIT_SET8(ESCI_LTR(offset), \
                                   ESCI_LTR_CRC_MASK) )

#define ESCI_LLM_CRC_ENHANCED_LIN_FRMAE_Disable(offset)     ( REG_BIT_CLEAR8(ESCI_LTR(offset), \
                                        ESCI_LTR_CRC_MASK) )
#define ESCI_LLM_IS_CRC_ENHANCED_LIN_FRMAE_ENABLED(offset)     ( ( (REG_READ8(ESCI_LTR(offset)) & \
                      ESCI_LTR_CRC_MASK) == ESCI_LTR_CRC_MASK) ? TRUE : FALSE)



/* TD - Transfer Direction. This bit control the transfer direction of the data, crc,and checksum*/
/* byte fields. */
/* - 0 Data, CRC, and Checksum byte fields received. */
/* - 1 Data, CRC, and Checksum byte fields transmitted. */

#define ESCI_LLM_LTR_TD_TRANSMIT_Enable(offset) (REG_BIT_SET8(ESCI_LTR(offset), ESCI_LTR_TD_MASK) )
#define ESCI_LLM_LTR_TD_RECEIVE_Enable(offset) (REG_BIT_CLEAR8(ESCI_LTR(offset), ESCI_LTR_TD_MASK))
#define ESCI_LLM_LTR_TD_Read(offset) ( ( ( REG_READ8(ESCI_LTR(offset)) &  \
                      ESCI_LTR_TD_MASK) == ESCI_LTR_TD_MASK) ? TRUE : FALSE )



/* TO - Timeout Value. The content of the field depends on the transfer direction. */
/* RX frame: Defines the time available for a complete RX frame transfer  */
/* TX frame: Must be set to 0. */


#define ESCI_LLM_LTR_TIMEOUT_11_8_Config(offset, value)   ( REG_WRITE8(ESCI_LTR(offset), \
                                REG_READ16(ESCI_LTR(offset)) | \
                                (value & ESCI_LTR_TO_11_8_MASK)) )

#define ESCI_LLM_LTR_TIMEOUT_7_0_Config(offset, value)     ( REG_WRITE8(ESCI_LTR(offset), \
                                REG_READ16(ESCI_LTR(offset)) | \
                                (value & ESCI_LTR_TO_7_0_MASK)) )



/* D Transmit Data. Data bits for transmission. */

#define ESCI_LLM_LTR_TRANSMIT_DATA_Config(offset, value)   ( REG_WRITE8(ESCI_LTR(offset), \
                                REG_READ16(ESCI_LTR(offset)) | \
                                (value & ESCI_LTR_TO_11_8_MASK)) )

#define ESCI_LLM_LTR_TRANSMIT_DATA_Read(offset) (REG_READ8(ESCI_LTR(offset)) & \
                               ESCI_LTR_TO_11_8_MASK )


/*************************************************************************************************/






/*-----------------------------------------------------------------------------------------------*/
/*             LIN Receive Register (eSCI_LRR) Configuration                                     */
/*-----------------------------------------------------------------------------------------------*/

/* Read eSCI_LRR register */
#define ESCI_LLM_LRR_Read(offset) (REG_READ8(ESCI_LRR(offset)) & ESCI_LRR_D_MASK )


/*************************************************************************************************/






/*-----------------------------------------------------------------------------------------------*/
/*             LIN CRC Polynomial Register (eSCI_LPR) Configuration                              */
/*-----------------------------------------------------------------------------------------------*/

/* Reset eSCI_LRR register */
#define ESCI_LLM_LPR_Reset(offset)       (REG_WRITE16(ESCI_LPR(offset), ESCI_LPR_RESET_MASK) )

/* Read eSCI_LPR register */
#define ESCI_LLM_LPR_Read(offset)       (REG_READ16(ESCI_LPR(offset)) & ESCI_LPR_P_MASK )

/* Configure eSCI_LPR register */
#define ESCI_LLM_LPR_Config(offset, value)   (REG_WRITE16(ESCI_LPR(offset), \
                       REG_READ16(ESCI_LPR(offset)) | \
                       (value & ESCI_LPR_P_MASK)) )


/*************************************************************************************************/






/*-----------------------------------------------------------------------------------------------*/
/*             Control Register 3 (eSCI_CR3) Configuration                                       */
/*-----------------------------------------------------------------------------------------------*/

/* Read eSCI_CR3 register */
#define ESCI_LLM_CR3_Read(offset)       (REG_READ16(ESCI_CR3(offset)) )

/* Reset eSCI_CR3 register */
#define ESCI_LLM_CR3_Reset(offset)       (REG_WRITE16(ESCI_CR3(offset), ESCI_CR3_RESET_MASK) )

#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

/* SYNM */
/* Synchronization Mode. This bit controls the synchronization mode of the receiver. */
/* - 0 Synchronization performed at falling start and data bit edge. */
/* - 1 Synchronization performed at falling start bit edge only. */

#define ESCI_LLM_SYNC_MODE_Enable(offset) (REG_BIT_SET16(ESCI_CR3(offset), ESCI_CR3_SYNM_MASK) )
#define ESCI_LLM_SYNC_MODE_Disable(offset) (REG_BIT_CLEAR16(ESCI_CR3(offset), ESCI_CR3_SYNM_MASK) )
#define ESCI_LLM_SYNC_MODE_Read(offset) (((REG_READ16(ESCI_CR3(offset)) &  \
           ESCI_CR3_SYNM_MASK) == ESCI_CR3_SYNM_MASK) ? TRUE : FALSE )

#endif


/* EROE */
/* ERR flag overrun enable. */
/* - 0 eSCI_SDR[ERR] flag not affected by overrun detection. */
/* - 1 eSCI_SDR[ERR] flag is set on overrun detection during frame reception. */

#define ESCI_LLM_ERROR_FLAG_OVERRUN_Enable(offset) (REG_BIT_SET16(ESCI_CR3(offset), \
                                  ESCI_CR3_EROE_MASK) )

#define ESCI_LLM_ERROR_FLAG_OVERRUN_Disable(offset) ( REG_BIT_CLEAR16(ESCI_CR3(offset), \
                                    ESCI_CR3_EROE_MASK) )

#define ESCI_LLM_ERROR_FLAG_OVERRUN_Read(offset) (((REG_READ16(ESCI_CR3(offset)) &  \
                    ESCI_CR3_EROE_MASK) == ESCI_CR3_EROE_MASK) ? TRUE : FALSE )



/* ERFE */
/* ERR flag frame error enable. */
/* - 0 eSCI_SDR[ERR] flag not affected by frame error detection. */
/* - 1 eSCI_SDR[ERR] flag is set on frame error detection for the data provided in eSCI_SDR. */

#define ESCI_LLM_ERROR_FLAG_FRAME_ERROR_Enable(offset)     ( REG_BIT_SET16(ESCI_CR3(offset), \
                                      ESCI_CR3_ERFE_MASK) )

#define ESCI_LLM_ERROR_FLAG_FRAME_ERROR_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR3(offset), \
                                        ESCI_CR3_ERFE_MASK) )
#define ESCI_LLM_ERROR_FLAG_FRAME_ERROR_Read(offset) (((REG_READ16(ESCI_CR3(offset)) &  \
                    ESCI_CR3_ERFE_MASK) == ESCI_CR3_ERFE_MASK) ? TRUE : FALSE )



/* ERPE */
/* ERR flag parity error enable. */
/* - 0 eSCI_SDR[ERR] flag not affected by parity error detection. */
/* - 1 eSCI_SDR[ERR] flag is set on parity error detection for the data provided in eSCI_SDR. */

#define ESCI_LLM_ERROR_FLAG_PARITY_ERROR_Enable(offset)   ( REG_BIT_SET16(ESCI_CR3(offset), \
                                      ESCI_CR3_ERPE_MASK) )

#define ESCI_LLM_ERROR_FLAG_PARITY_ERROR_Disable(offset)   ( REG_BIT_CLEAR16(ESCI_CR3(offset), \
                                        ESCI_CR3_ERPE_MASK) )

#define ESCI_LLM_ERROR_FLAG_PARITY_ERROR_Read(offset) (((REG_READ16(ESCI_CR3(offset)) &  \
                    ESCI_CR3_ERPE_MASK) == ESCI_CR3_ERPE_MASK) ? TRUE : FALSE )



/* M2 */
/* Frame Format Mode 2. This control bit together with the M bit of the Control Register 1 */
/* (eSCI_CR1) controls the frame format used.  */

#define ESCI_LLM_M2_Enable(offset)          (REG_BIT_SET16(ESCI_CR3(offset),ESCI_CR3_M2_MASK))
#define ESCI_LLM_M2_Disable(offset)       (REG_BIT_CLEAR16(ESCI_CR3(offset),ESCI_CR3_M2_MASK))
#define ESCI_LLM_M2_Read(offset)          ( ( ( REG_READ16(ESCI_CR3(offset)) &  \
                      ESCI_CR3_M2_MASK) == ESCI_CR3_M2_MASK) ? TRUE : FALSE )


/*************************************************************************************************/

/**
 * MISRA 2004 Advisory Rule 19.7  -  end violation
 * MISRA 2004 Required Rule 1.4   -  end violation
 */

#ifdef __cplusplus
}
#endif

#endif /* REG_ESYS_ESCI_H */
