/**
   @file    ESCI_LLD.c
   @version 2.0.0

   @brief   AUTOSAR Lin - Low level functions implementations
   @details low level functions

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
 * @section ESCI_LLD_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 *
 * @section ESCI_LLD_C_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 *
 * @section ESCI_LLD_C_REF_3
 * Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer 
 * to a function and any type other than an integral type. This violation is due to the pointer 
 * arithematic used to write/read the data to/from the registers.
 *
 * @section ESCI_LLD_C_REF_4
 * Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator.
 * Expression is a macro which returns a boolean value always.
 *
 * @section ESCI_LLD_C_REF_5
 * Violates MISRA 2004 Required Rule 12.4, side effects on right hand of logical operator.
 * This violation is not fixed as the right hand operator of the logical operator
 * does not contain any side effects.
 *
 * @section ESCI_LLD_C_REF_6
 * Violates MISRA 2004 Required Rule 17.4 , Array indexing shall be the only allowed form of 
 * pointer arithmetic. This violation is due to the use of pointer arithematic, to access the 
 * channel parameters, the indexing of the pointer is taken care and hence the unintended memory 
 * location will not be accessed.
 *
 * @section ESCI_LLD_C_REF_7
 * Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or 
 * functions at file scope shall have internal linkage unless external linkage is required. 
 * The respective code could not be made static because of layers architecture design of 
 * the driver.
 */

#ifdef __cplusplus
extern "C" {
#endif
/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Lin.h"
#include "ESCI_LLD.h"
#ifdef LIN_USE_DMA
#include "Dma_LLD.h"
#endif
#include "Reg_Macros.h"
#include "Reg_eSys.h"

#include "Reg_eSys_ESCI.h"
#include "Lin_NonASR.h"



/*=================================================================================================
                                        LOCAL MACROS
=================================================================================================*/
#define LIN_AR_MAJOR_VERSION_ESCI_C  1
#define LIN_AR_MINOR_VERSION_ESCI_C  2
#define LIN_AR_PATCH_VERSION_ESCI_C  1

#define LIN_SW_MAJOR_VERSION_ESCI_C  2
#define LIN_SW_MINOR_VERSION_ESCI_C  0
#define LIN_SW_PATCH_VERSION_ESCI_C  0

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/* ESCI_LLD.c vs Lin.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if (((LIN_AR_MAJOR_VERSION_ESCI_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != LIN_AR_MINOR_VERSION)) || \
       (LIN_AR_PATCH_VERSION_ESCI_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of ESCI_LLD.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of ESCI_LLD.c and Lin.h are different"
#endif

/* ESCI_LLD.c vs ESCI_LLD.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if (((LIN_AR_MAJOR_VERSION_ESCI_C != LIN_AR_MAJOR_VERSION_ESCI) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != LIN_AR_MINOR_VERSION_ESCI)) || \
       (LIN_AR_PATCH_VERSION_ESCI_C != LIN_AR_PATCH_VERSION_ESCI))
      #error "AutoSar Version Numbers of ESCI_LLD.c and ESCI_LLD.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION_ESCI) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION_ESCI))
    #error "Software Version Numbers of ESCI_LLD.c and ESCI_LLD.h are different"
#endif

/* ESCI_LLD.c vs Reg_eSys_ESCI.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if (((LIN_AR_MAJOR_VERSION_ESCI_C != LIN_AR_MAJOR_VERSION_REGESCI) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != LIN_AR_MINOR_VERSION_REGESCI)) || \
       (LIN_AR_PATCH_VERSION_ESCI_C != LIN_AR_PATCH_VERSION_REGESCI))
      #error "AutoSar Version Numbers of ESCI_LLD.c and Reg_eSys_ESCI.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION_REGESCI) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION_REGESCI))
    #error "Software Version Numbers of Lin_LLD.c and Reg_eSys_ESCI.h are different"
#endif


/* ESCI_LLD.c vs LinIf_Cbk.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_ESCI_C != LIN_IF_AR_MAJOR_VERSION_CBK) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != LIN_IF_AR_MINOR_VERSION_CBK))
      #error "AutoSar Version Numbers of ESCI_LLD.c and LinIf_Cbk.h are different"
  #endif
#endif

/* ESCI_LLD.c vs EcuM_Cbk.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_ESCI_C != ECUM_CBK_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != ECUM_CBK_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin.c and EcuM_CBK.h are different"
  #endif
#endif

  /* ESCI_LLD.c vs EcuM_Cfg.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_ESCI_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_ESCI_C != ECUM_CFG_AR_MINOR_VERSION))
      #error "Software Version Numbers of Lin.c and EcuM_Cfg.h are different"
  #endif
#endif

/*=================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
                                       LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       LOCAL VARIABLES
=================================================================================================*/
#define LIN_START_SEC_VAR_UNSPECIFIED
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"

/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref ESCI_LLD_C_REF_7
 */
 
/* LIN channel buffer counter */
 VAR(uint8,LIN_VAR)Lin_BufferCounter[LIN_HW_MAX_AVAILABLE_MODULES];
 VAR(uint8,LIN_VAR)Lin_BufferCounterMax[LIN_HW_MAX_AVAILABLE_MODULES];

  #ifdef  ESCIA_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffA;
  #endif /* ESCIA_BASEADDR */
  #ifdef  ESCIB_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffB;
  #endif /* ESCIB_BASEADDR */
  #ifdef  ESCIC_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffC;
  #endif /* ESCIC_BASEADDR */
  #ifdef  ESCID_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffD;
  #endif /* ESCID_BASEADDR */
  #ifdef  ESCIE_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffE;
  #endif  /* ESCIE_BASEADDR */
  #ifdef  ESCIF_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffF;
  #endif /* ESCIF_BASEADDR */
  #ifdef  ESCIG_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffG;
  #endif /* ESCIG_BASEADDR */
  #ifdef  ESCIH_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffH;
  #endif /* ESCIH_BASEADDR */
  #ifdef  ESCIJ_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffJ;
  #endif /* ESCIJ_BASEADDR */
  #ifdef  ESCIK_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffK;
  #endif /* ESCIK_BASEADDR */
  #ifdef  ESCIL_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffL;
  #endif /* ESCIL_BASEADDR */
  #ifdef  ESCIM_BASEADDR
  VAR(Lin_BuffType,LIN_VAR)Lin_ChShadowBuffM;
  #endif /* ESCIM_BASEADDR */

#define LIN_STOP_SEC_VAR_UNSPECIFIED
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref ESCI_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"


/*=================================================================================================
                                       GLOBAL CONSTANTS
=================================================================================================*/
#define LIN_START_SEC_CONST_UNSPECIFIED
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref ESCI_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"

/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref ESCI_LLD_C_REF_7
 */
 CONST(uint32, LIN_CONST) LIN_BASE_ADDRESS[] =
 {
    #ifdef  ESCIA_BASEADDR
        ESCIA_BASEADDR,
    #endif /* ESCIA_BASEADDR */
    #ifdef  ESCIB_BASEADDR
        ESCIB_BASEADDR,
    #endif /* ESCIB_BASEADDR */
    #ifdef  ESCIC_BASEADDR
        ESCIC_BASEADDR,
    #endif /* ESCIC_BASEADDR */
    #ifdef  ESCID_BASEADDR
        ESCID_BASEADDR,
    #endif /* ESCID_BASEADDR */
    #ifdef  ESCIE_BASEADDR
        ESCIE_BASEADDR,
    #endif /* ESCIE_BASEADDR */
    #ifdef  ESCIF_BASEADDR
        ESCIF_BASEADDR,
    #endif /* ESCIF_BASEADDR */
    #ifdef  ESCIG_BASEADDR
        ESCIG_BASEADDR,
    #endif /* ESCIG_BASEADDR */
    #ifdef  ESCIH_BASEADDR
        ESCIH_BASEADDR,
    #endif /* ESCIH_BASEADDR */
    #ifdef  ESCIJ_BASEADDR
        ESCIJ_BASEADDR,
    #endif /* ESCIJ_BASEADDR */
    #ifdef  ESCIK_BASEADDR
        ESCIK_BASEADDR,
    #endif /* ESCIK_BASEADDR */
    #ifdef  ESCIL_BASEADDR
        ESCIL_BASEADDR,
    #endif /* ESCIL_BASEADDR */
    #ifdef  ESCIM_BASEADDR
        ESCIM_BASEADDR
    #endif /* ESCIM_BASEADDR */
};


/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref ESCI_LLD_C_REF_7
 */
CONSTP2VAR(Lin_BuffType,LIN_APPL_CONST,LIN_VAR) Lin_ChShadowBuffPtr[]=
{
    #ifdef  ESCIA_BASEADDR
        &Lin_ChShadowBuffA,
    #endif /* ESCIA_BASEADDR */
    #ifdef  ESCIB_BASEADDR
        &Lin_ChShadowBuffB,
    #endif /* ESCIB_BASEADDR */
    #ifdef  ESCIC_BASEADDR
        &Lin_ChShadowBuffC,
    #endif /* ESCIC_BASEADDR */
    #ifdef  ESCID_BASEADDR
        &Lin_ChShadowBuffD,
    #endif /* ESCID_BASEADDR */
    #ifdef  ESCIE_BASEADDR
      &Lin_ChShadowBuffE,
    #endif /* ESCIE_BASEADDR */
    #ifdef  ESCIF_BASEADDR
        &Lin_ChShadowBuffF,
    #endif /* ESCIF_BASEADDR */
    #ifdef  ESCIG_BASEADDR
        &Lin_ChShadowBuffG,
    #endif /* ESCIG_BASEADDR */
    #ifdef  ESCIH_BASEADDR
        &Lin_ChShadowBuffH,
    #endif /* ESCIH_BASEADDR */
    #ifdef ESCIJ_BASEADDR
        &Lin_ChShadowBuffJ,
    #endif /* ESCIJ_BASEADDR */
    #ifdef  ESCIK_BASEADDR
        &Lin_ChShadowBuffK,
    #endif /* ESCIK_BASEADDR */
    #ifdef  ESCIL_BASEADDR
        &Lin_ChShadowBuffL,
    #endif /* ESCIL_BASEADDR */
    #ifdef ESCIM_BASEADDR
        &Lin_ChShadowBuffM
    #endif /* ESCIM_BASEADDR */
};

/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref ESCI_LLD_C_REF_7
 */
CONST (uint8,LIN_APPL_CONST) Lin_TimeoutValue [(LIN_MAX_DATA_LENGTH + 1U)]=
{
  LIN_TIMEOUT_DATABYTE_ZERO,        /*= (10*0+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_ONE,         /*= (10*1+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_TWO,         /*= (10*2+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_THREE,       /*= (10*3+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_FOUR,        /*= (10*4+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_FIVE,        /*= (10*5+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_SIX,         /*= (10*6+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_SEVEN,       /*= (10*7+45)*1.4 */
  LIN_TIMEOUT_DATABYTE_EIGHT        /*= (10*8+45)*1.4 */
};

#define LIN_STOP_SEC_CONST_UNSPECIFIED
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref ESCI_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/
/*=================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/

/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/

#define LIN_START_SEC_CODE
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref ESCI_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"

/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer: 
 *       See @ref ESCI_LLD_C_REF_3
 *       Violation for below block of code
 */
 
/*===============================================================================================*/
/*!
 * @brief Check if a LIN channel (eSCI_A or eSCI_B or eSCI_C) has been waked-up.
 * @param[in] Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be waked-up.
 * @return TRUE if Channel has the wake up flag set and the wake up ISR disabled
 *         FALSE otherwise.
 * @remarks implements DLIN30011
 */
/*===============================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_WakeUpValidation(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)FALSE;
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /* Check whether wake up flag has been set and wake up ISR is disabled */
    /**
     * @file ESCI_LLD.c
     * @note Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: 
     *       See @ref ESCI_LLD_C_REF_4
     */    
    if ((ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_READ(Lin_ESCI)) && (!ESCI_LLM_LCR1_WUIE_Read(Lin_ESCI)))
        {
        /* LIN channel with wake up support disabled has been woken up */
        /* Clear Wake-Up flag */
        /* Note: all flags have to be cleared by writing a 1 to the flags -> writing 0 has no
           effect */
        ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(Lin_ESCI);

        /* Set the returned value to TRUE */
        tempReturn = (uint8)TRUE;
        }
    return tempReturn;
    }
/*===============================================================================================*/
/**
 * @brief         Initialize a LIN channel (eSCI_A or eSCI_B or eSCI_C).
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be initialized.
 * @remarks     implements DLIN30004
 */
/*===============================================================================================*/
FUNC(void, LIN_CODE) ESCI_LLD_InitChannel(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(uint8, LIN_VAR) Lin_ESCI;
    VAR(uint8,AUTOMATIC)BuffLoop;
    VAR(uint8,AUTOMATIC)Lin_ChLoopCount;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;


    /* Enable eSCI module */
    ESCI_LLM_ENABLE_ESCI_MODULE(Lin_ESCI);

    /* Enable LIN mode */
    ESCI_LLM_LCR1_LIN_Enable(Lin_ESCI);

    /* Set LRES bit of LCR1 register to reset the LIN state machine */
    ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

    /* set baud rate value for low power mode */
    ESCI_LLM_BRR_Config(Lin_ESCI, Lin_Channel_Cfg_Ptr[Channel]->Lin_BaudRate_RegValue);

    /* Enable Transmitter*/
    ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

    /* Enable Receiver*/
    ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

#ifdef LIN_USE_DMA
    /* Enable DMA Stop on Bit Error or Physical Bus Error*/
    ESCI_LLM_CR2_BSTP_Enable(Lin_ESCI);
#endif
    /* Enable Bit Error Interrupt */
    ESCI_LLM_CR2_BERRIE_Enable(Lin_ESCI);

    /* Select break character length of 13 bit as required by LIN 2.0 */
    ESCI_LLM_CR2_BRCL_Enable(Lin_ESCI);

    /* Enable Fast Bit Error Detection Sample Mode */
    ESCI_LLM_CR2_BESM_Enable(Lin_ESCI);

    /* Enable Transmit Stop on Bit Error */
    ESCI_LLM_CR2_BESTP_Enable(Lin_ESCI);

    /* Enable Frame Error Interrupt */
    ESCI_LLM_CR2_FEIE_Enable(Lin_ESCI);

    /* Clear LRES bit of LCR1 register to reset the LIN state machine */
    ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

    /* Enable Parity Flag Interrupt */
    ESCI_LLM_LCR1_PRTY_Enable(Lin_ESCI);

    /* Enable Slave Timeout Flag Interrupt */
    ESCI_LLM_LCR1_STIE_Enable(Lin_ESCI);

    /* Enable Physical Bus Error Interrupt */
    ESCI_LLM_LCR1_PBIE_Enable(Lin_ESCI);

    /* Enable Checksum Error Interrupt */
    ESCI_LLM_LCR1_CKIE_Enable(Lin_ESCI);

    /* Enable CRC Error Interrupt */
    ESCI_LLM_LCR1_CIE_Enable(Lin_ESCI);

    /* Enable Overflow Flag Interrupt */
    ESCI_LLM_LCR2_OFIE_Enable(Lin_ESCI);

    /* Disable wake up interrupt */
    ESCI_LLM_LCR1_WUIE_Disable(Lin_ESCI);

    /* Clear the contents of shadow buffer*/
    for(Lin_ChLoopCount=(uint8)ESCI_ZERO;Lin_ChLoopCount<LIN_HW_MAX_MODULES;Lin_ChLoopCount++)
        {
        for(BuffLoop=ESCI_ZERO;BuffLoop < LIN_MAX_DATA_LENGTH;BuffLoop++)
            {
            Lin_ChShadowBuffPtr[Lin_ChLoopCount]->DATA[BuffLoop] = ESCI_ZERO;
            }
        }
    }
/*===============================================================================================*/
/**
 * @brief Deinitialize and disable a LIN channel (eSCI_A or eSCI_B or eSCI_C).
 * @param[in] Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be de-initialized.
 * @remarks implements DLIN30000
 */
/*===============================================================================================*/
FUNC (void, LIN_CODE) ESCI_LLD_DeInitChannel(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /* Disable eSCI module */
    ESCI_LLM_DISABLE_ESCI_MODULE(Lin_ESCI);

    /* Write the reset value of Control Register 1 (eSCI_CR1)*/
    ESCI_LLM_CR1_Reset(Lin_ESCI);

    /* Write the reset value of Baud Rate Register (eSCI_BRR)*/
    ESCI_LLM_BRR_Reset(Lin_ESCI);

    /* Disable Receive Data Ready Interrupt */
    ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

    /* Disable Transmit Data Ready Interrupt */
    ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);

    /* Disable Bit Error Interrupt */
    ESCI_LLM_CR2_BERRIE_Disable(Lin_ESCI);

    /* Disable Slave Timeout Flag Interrupt */
    ESCI_LLM_LCR1_STIE_Disable(Lin_ESCI);

    /* Disable Physical Bus Error Interrupt */
    ESCI_LLM_LCR1_PBIE_Disable(Lin_ESCI);

    /* Disable Checksum Error Interrupt */
    ESCI_LLM_LCR1_CKIE_Disable(Lin_ESCI);

    /* Disable CRC Error Interrupt */
    ESCI_LLM_LCR1_CIE_Disable(Lin_ESCI);

    /* Disable Slave Timeout Flag Interrupt */
    ESCI_LLM_LCR2_OFIE_Disable(Lin_ESCI);
#ifdef LIN_USE_DMA
    if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
        {
        /* DMA is used */

        /* disable DMA request from eSCI */
        /* Transmit DMA disabled */
        ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

        /* Receive DMA disabled */
        ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);

        /* Disable the interrupt for TX DMA channel */
        Dma_disable_interrupt(Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel);

        /* Disable the interrupt for RX DMA channel */
        Dma_disable_interrupt(Lin_Channel_Cfg_Ptr[Channel]->LinRxDMAChannel);

        }
#endif

    }
/*===============================================================================================*/
/*!
 * @brief         Initiates the transmission of the header
 *                part of the LIN frame on Channel (eSCI_A or eSCI_B or eSCI_C)
 *                using information stored on PduInfoPtr pointer.
 *                If response type is MASTER_RESPONSE then nothing is sent over the bus
 *                the entire frame (including header) is sent with the ESCI_LLD_SendReponse
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @param[in]     PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *                Response type, Dl and SDU data pointer
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @remarks implements DLIN30008
 */
/*===============================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_SendHeader(CONST(uint8, LIN_CONST) Channel,
                          CONST(Lin_PduType*, LIN_CONST) PduInfoPtr)
    {
    VAR(uint8,AUTOMATIC)Lin_Temp;
    VAR(uint8, LIN_VAR) Lin_ESCI;
    VAR(uint32, AUTOMATIC) counter = ESCI_ZERO;
    VAR(uint8, AUTOMATIC) tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /** Stop any ongoing transmission */
    /** @remarks implements DLIN15003 */

    /* Disable Transmitter*/
    ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

    /* Disable Receiver*/
    ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

    /* Disable Receive Data Ready Interrupt */
    ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

    /* Disable Transmit Data Ready Interrupt */
    ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);

#ifdef LIN_USE_DMA
    /* Transmit DMA disabled */
    ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

    /* Receive DMA disabled */
    ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);
#endif
    /* Disable Frame Control Interrupt */
    ESCI_LLM_LCR1_FCIE_Disable(Lin_ESCI);

    /* wait till Cancellation of current frame */
    while(counter < LIN_TIMEOUT_LOOPS)
        {
#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

          if((ESCI_LLM_IFSR1_IS_TX_ACTIVE(Lin_ESCI) == FALSE))
#endif
#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

#ifdef LIN_USE_DMA
          /* Is there a a transmit or receive DMA request pending ? */
          if((ESCI_LLM_IFSR1_IS_DMA_ACTIVE(Lin_ESCI) == FALSE))
#else
          /* Is there a a transmit or receive interrupt request pending ? */
          if((ESCI_LLM_IFSR1_IS_LIN_ACTIVE(Lin_ESCI) == FALSE))
#endif
#endif
            {
            tmpReturn = (uint8)E_OK;
            break;
            }

        counter++;

        }

    if(tmpReturn == (uint8)E_OK)
        {
        /* Set LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* These redundant line are required since LIN state machine gets RESET correctly after
           setting LRES bit three times and then clear it*/
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* Clear the Noise Flag of Interrupt Flag and Status Register 1 (eSCI_IFSR1) */
        ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

        /* Copy the Identifier into a local variable */
        Lin_Temp = (PduInfoPtr->Pid & ESCI_LTR_ID_MASK);

        if (ESCI_LLM_LCR1_PRTY_Read(Lin_ESCI) == FALSE)
            {
            /* recalculate the parity */
            Lin_Temp  = ((Lin_Temp) & (uint8)(~((ESCI_ID_BIT_SIX_MASK)|(ESCI_ID_BIT_SEVEN_MASK))))^
                        (((uint8)(Lin_Temp  << ESCI_ID_BIT_SHIFT_BY_TWO) ^
                        ((uint8)(Lin_Temp << ESCI_ID_BIT_SHIFT_BY_THREE) & ESCI_ID_BIT_SEVEN_MASK)^
                        (uint8)(Lin_Temp << ESCI_ID_BIT_SHIFT_BY_FOUR) ^
                        ((uint8)(Lin_Temp << ESCI_ID_BIT_SHIFT_BY_FIVE) & ESCI_ID_BIT_SIX_MASK) ^
                        (uint8)(Lin_Temp << ESCI_ID_BIT_SHIFT_BY_SIX)) &
                        ESCI_ID_BIT_SIX_SEVEN_MASK);
            }
        else
            {
            /* Hardware parity is enabled, just assign the PID value to go to next ELSE statement*/
            Lin_Temp = PduInfoPtr->Pid;
            }
        /* prepare header */
        /* First step is to configure ID */
        Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ZERO] = Lin_Temp ;


        /* Second step data length */
        Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE] = PduInfoPtr->Dl;

        /* third step is to configure Checksum, CRC and Transfer direction*/
        if(PduInfoPtr->Drc == LIN_MASTER_RESPONSE)
            {
            /* Tx */
            if(PduInfoPtr->Cs == LIN_ENHANCED_CS)
                {
                /* Use enhanced checksum and set Transfer direction bit as Transmit */
                Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_TWO] = ( ESCI_LTR_CSM_MASK |
                                                ESCI_LTR_TD_MASK  |
                                                 ESCI_LTR_CSE_MASK);
                }

            else
                {
                /* Use Classic checksum and set Transfer direction bit as Transmit */
                Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_TWO] = ( ESCI_LTR_TD_MASK |
                                                ESCI_LTR_CSE_MASK);
                }

            /* set master response msg type */
            Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE = (uint8)LIN_MASTER_RESPONSE;
            }
        else
            {

            /* Rx */
            if(PduInfoPtr->Cs == LIN_ENHANCED_CS)
                {

                /* use enhanced checksum */
                /* third step */
                /* HDCHK|CSUM|RX */
                Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_TWO] = (ESCI_LTR_CSM_MASK |
                                               ESCI_LTR_CSE_MASK);
                }
            else
                {
                /* use classic checksum */
                /* third step */
                /* CSUM|RX */
                Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_TWO] = (ESCI_LTR_CSE_MASK);
                }

            /* fourth step timeout */
            Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_THREE] =
                                      Lin_TimeoutValue[PduInfoPtr->Dl];

            /* set slave response msg type */
            Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE = (uint8)LIN_SLAVE_RESPONSE;
            }


        /* Clear Receive Data Register Full Interrupt Flag */
        ESCI_LLM_IFSR1_RX_DATA_REG_FULL_Clear(Lin_ESCI);

        /* Enable Receiver Full Interrupt */
        ESCI_LLM_CR1_RIE_Enable(Lin_ESCI);

        /* Clear LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

        /* Enable Receiver */
        ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

        /* Enable Transmitter */
        ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

        /* initiate transmission of the header depending on DMA or interrupt driven */
#ifdef LIN_USE_DMA
      if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
            {

            if(PduInfoPtr->Drc == LIN_SLAVE_RESPONSE)
                {
                /* Configure TX DMA channel*/
                Dma_configure_channel( Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel,
                            (uint32)&Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER,
                             0U,
                             0U,
                             1U,
                             1U,
                             0U,
                             ESCI_LTR(Lin_ESCI),
                             4U,
                             0U,
                             0U,
                             4U,
                             DMA_INT_MAJ_MASK);

                /* Clear Receive Data Ready Interrupt Flag */
                ESCI_LLM_RX_READY_Clear(Lin_ESCI);

                /* Enable Receive Data Ready Interrupt */
                ESCI_LLM_LCR1_RXIE_Enable(Lin_ESCI);

                /* Transmit DMA enabled */
                ESCI_LLM_CR2_TXDMA_Enable(Lin_ESCI);

                /* Start a DMA transfer */
                Dma_start_channel(Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel);
                }
            }
        else
            {
#endif
            /* ISR driven */

            if(Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE != (uint8)LIN_MASTER_RESPONSE)
                {
                /* Clear Receive Data Ready Interrupt Flag */
                ESCI_LLM_RX_READY_Clear(Lin_ESCI);

                /* Enable Receive Data Ready Interrupt */
                ESCI_LLM_LCR1_RXIE_Enable(Lin_ESCI);
                }

            if(PduInfoPtr->Drc == LIN_SLAVE_RESPONSE)
                {
                /* Reset buffer counter */
                Lin_BufferCounter[Lin_ESCI] = ESCI_ZERO;

                /* Rx requires 4 steps to initiate the header transmission */
                Lin_BufferCounterMax[Lin_ESCI] = SLAVE_RESPONSE_HEADER_WRITE_COUNT;

                /* Enable Transmit Data Ready Interrupt */
                ESCI_LLM_LCR1_TXIE_Enable(Lin_ESCI);
                }
#ifdef LIN_USE_DMA
            }
#endif

        /* Clear the Noise Interrupt Flag */
        ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

        /* Framing Error flag */
        ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

        /* Clear Bit Error Interrupt Flag */
        ESCI_LLM_IFSR1_BIT_ERROR_FLAG_Clear(Lin_ESCI);

        /* Clear Slave Timeout Interrupt Flag */
        ESCI_LLM_SLAVE_TIMEOUT_FLAG_Clear(Lin_ESCI);

        /* Clear Physical Bus Error Interrupt Flag */
        ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_Clear(Lin_ESCI);

        /* Clear CRC Error Interrupt Flag */
        ESCI_LLM_CRC_ERROR_FLAG_Clear(Lin_ESCI);

        /* Clear Checksum Error Interrupt Flag */
        ESCI_LLM_CHECKSUM_ERROR_FLAG_Clear(Lin_ESCI);

        /* Clear Overflow Interrupt Flag */
        ESCI_LLM_OVERFLOW_FLAG_Clear(Lin_ESCI);

        /* Clear Unrequested Data Received Interrupt Flag */
        ESCI_LLM_UNREQUESTED_DATA_FLAG_Clear(Lin_ESCI);

        /* Clear Frame Complete Interrupt Flag */
        ESCI_LLM_FRAME_COMPLETE_FLAG_Clear(Lin_ESCI);

        /* enable end of frame interrupt */
        ESCI_LLM_LCR1_FCIE_Enable(Lin_ESCI);
        }


    return tmpReturn;
    }
/*===============================================================================================*/
/*!
 * @brief         Initiates the transmission of the data
 *                part of the LIN frame on Channel (eSCI_A or eSCI_B or eSCI_C)
 *                using information stored on PduInfoPtr pointer.
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @param[in]     PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *                Response type, Dl and SDU data pointer
 * @remarks implements DLIN30007
 */
/*===============================================================================================*/
FUNC (void, LIN_CODE) ESCI_LLD_SendResponse(CONST(uint8, LIN_CONST) Channel,
                      CONST(Lin_PduType*, LIN_CONST) PduInfoPtr)
    {

    VAR(uint8, AUTOMATIC) Lin_Temp;

    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /* Check that no error is occurred during sending the header */
    if (Lin_LinChFrameStatus[Channel] == LIN_CH_SEND_HEADER_ERROR)
        {
        /* there was an error during header transmission */

        /* update LIN channel frame operation status to LIN_CH_SEND_DATA_ERROR */

        Lin_LinChFrameStatus[Channel] = LIN_CH_SEND_DATA_ERROR;
        }
    else
        {
        /* Check whether data length is valid or not */
        if(PduInfoPtr->Dl != ESCI_ZERO)
            {

            /* send data */
            /* copy 1 to 8 data bytes from Pdu to shadow buffer */
#ifdef LIN_USE_DMA
        if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
                {

                /* HEADER[3] will be used as first data byte */
                Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[3] = PduInfoPtr->SduPtr[ESCI_ZERO];

                for(Lin_Temp=ESCI_ZERO;
                    Lin_Temp<Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE] - ESCI_ONE;
                      Lin_Temp++)
                    {
                    /* Since first datbyte [0] is updated in HEADER[3], now update remaining
                       databytes [1..7] */
                    Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Lin_Temp] =
                                      PduInfoPtr->SduPtr[Lin_Temp + ESCI_ONE];

                    }
                }
            else
                {
#endif
                for(Lin_Temp=ESCI_ZERO;
                    Lin_Temp<Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE];
                      Lin_Temp++)
                    {
                    /**
                     * @file ESCI_LLD.c
                     * @note Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than 
                     *       array indexing used: See @ref ESCI_LLD_C_REF_6
                     */                    
                    Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Lin_Temp] = PduInfoPtr->SduPtr[Lin_Temp];

                    }
#ifdef LIN_USE_DMA
                }
#endif

            /* initiate transmission of the response depending on DMA or interrupt driven */
#ifdef LIN_USE_DMA
        if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
                {
                /* Configure TX DMA channel*/
                Dma_configure_channel( Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel,
                            (uint32)&Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER,
                            0U,
                            0U,
                            1U,
                            1U,
                            0U,
                            ESCI_LTR(Lin_ESCI),
                            Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[1] + 3U,
                            0U,
                            0U,
                            Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[1] + 3U,
                            DMA_INT_MAJ_MASK);

                /* Transmit DMA enabled */
                ESCI_LLM_CR2_TXDMA_Enable(Lin_ESCI);

                /* Start a DMA transfer */
                Dma_start_channel(Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel);
                }
            else
                {
#endif
                /* ISR driven */
                /* Reset buffer counter */
                Lin_BufferCounter[Lin_ESCI] = ESCI_ZERO;

                /* Max ISR count */
                Lin_BufferCounterMax[Lin_ESCI] =
                            Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE] +
                              MASTER_RESPONSE_HEADER_WRITE_COUNT;

                /* Enable Transmit Data Ready Interrupt */
                ESCI_LLM_LCR1_TXIE_Enable(Lin_ESCI);
#ifdef LIN_USE_DMA
                }
#endif
            }
        }
    }
/*===============================================================================================*/
/*!
 * @brief       Prepares and send a go-to-sleep-command
 *              frame on Channel (eSCI_A or eSCI_B or eSCI_C).
 * @param[in]   Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and initiates
 *              the transmission of the sleep command (master command frame with
 *              ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF).
 *              LIN 2.0 protocol specifications
 * @remarks implements DLIN30001
 */
/*===============================================================================================*/
FUNC(Std_ReturnType, LIN_CODE) ESCI_LLD_GoToSleep(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(uint8, LIN_VAR) Lin_ESCI;
    VAR(uint8, AUTOMATIC) Lin_Temp;
    VAR(uint32, AUTOMATIC) counter = ESCI_ZERO;
    VAR(uint8, AUTOMATIC) tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /** Stop any ongoing transmission */
    /** @remarks implements DLIN15003 */

    /* Disable Transmitter*/
    ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

    /* Disable Receiver*/
    ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

    /* Disable Receive Data Ready Interrupt */
    ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

    /* Disable Transmit Data Ready Interrupt */
    ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);

#ifdef LIN_USE_DMA
    /* Transmit DMA disabled */
    ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

    /* Receive DMA disabled */
    ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);
#endif
    /* Disable Frame Control Interrupt */
    ESCI_LLM_LCR1_FCIE_Disable(Lin_ESCI);

    /* wait till Cancellation of current frame */
    while(counter < LIN_TIMEOUT_LOOPS)
        {

#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

          if((ESCI_LLM_IFSR1_IS_TX_ACTIVE(Lin_ESCI) == FALSE))
#endif
#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

#ifdef LIN_USE_DMA
          /* Is there a a transmit or receive DMA request pending ? */
          if((ESCI_LLM_IFSR1_IS_DMA_ACTIVE(Lin_ESCI) == FALSE))
#else
          /* Is there a a transmit or receive interrupt request pending ? */
          if((ESCI_LLM_IFSR1_IS_LIN_ACTIVE(Lin_ESCI) == FALSE))
#endif
#endif
            {
            tmpReturn = (uint8)E_OK;
            break;
            }

          counter++;

        }

    if(tmpReturn == (uint8)E_OK)
        {

        /* Set LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* These redundant line are required since LIN state machine gets RESET correctly after
           setting LRES bit three times and then clear it*/
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* Clear LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

        /* Enable Transmitter*/
        ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

        /* Enable Receiver*/
        ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

        /* prepare buffer for sleep mode command */
        /* prepare header */
        /* first step ID */
        /* includes the parity */
        Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ZERO] = SLEEP_IDENTIFIER_VALUE ;

        /* second step data length */
        /* standard length for master request command */
        Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE] = ESCI_MAX_DATA_LENGTH;

        /* third step use classic checksum */
        /* CSUM|TX */
        Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_TWO] = (ESCI_LTR_CSE_MASK |
                                      ESCI_LTR_TD_MASK);

#ifdef LIN_USE_DMA
      if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_OFF)
            {
#endif
            /* prepare data */
            /* the data of the shadow buffer to 0 -> Byte0=0 is sleep command */
            Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[ESCI_ZERO] = SLEEP_DATABYTE_ONE_VALUE;

            /* just 1-7 bytes of the DATA will be send since HEADER[3] is the first data byte */
            for(Lin_Temp=ESCI_ONE;
                Lin_Temp<Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE];
                  Lin_Temp++)
                {
                Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Lin_Temp] = SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE;
                }
#ifdef LIN_USE_DMA
            }
        else
            {
            /* fourth step use sleep mode command -> will be used as first data byte */
            Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_THREE] = ESCI_ZERO;

            /* just 1-7 bytes of the DATA will be send since HEADER[3] is the first data byte */
            for(Lin_Temp=ESCI_ZERO;
                Lin_Temp<Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE];
                  Lin_Temp++)
                {
                Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Lin_Temp] = SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE;
                }
            }
#endif
        /* set sleep cmd msg type */
        Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE = SLEEP_CMD_TYPE;

        /* initiate transmission of the header depending on DMA or interrupt driven */
#ifdef LIN_USE_DMA
      if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
            {
            /* Configure TX DMA channel*/
            Dma_configure_channel( Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel,
                         (uint32)&Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER,
                         0U,
                         0U,
                         1U,
                         1U,
                         0U,
                         ESCI_LTR(Lin_ESCI),
                         11U,
                         0U,
                         0U,
                         11U,
                         DMA_INT_MAJ_MASK);

            /* Transmit DMA enabled */
            ESCI_LLM_CR2_TXDMA_Enable(Lin_ESCI);

            /* Start a DMA transfer */
            Dma_start_channel(Lin_Channel_Cfg_Ptr[Channel]->LinTxDMAChannel);
            }
        else
            {
#endif
            /* ISR driven */
            /* Reset buffer counter */
            Lin_BufferCounter[Lin_ESCI] = ESCI_ZERO;

            /* Max ISR count */
            Lin_BufferCounterMax[Lin_ESCI] = LIN_HEADER_DATA_WRITE_COUNT;

            /* Enable Transmit Data Ready Interrupt */
            ESCI_LLM_LCR1_TXIE_Enable(Lin_ESCI);
#ifdef LIN_USE_DMA
            }
#endif

        /* Clear Frame Complete Interrupt Flag */
        ESCI_LLM_FRAME_COMPLETE_FLAG_Clear(Lin_ESCI);

        /* enable end of frame interrupt */
        ESCI_LLM_LCR1_FCIE_Enable(Lin_ESCI);


        }
    return tmpReturn;
    }
/*===============================================================================================*/
/*!
 * @brief       Same function as ESCI_LLD_GoToSleep but
 *              without sending a go-to-sleep-command on the bus.
 * @param[in]   Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and put the
 *              Channel in sleep mode (then LIN hardware enters a
 *              reduced power operation mode).
 * @remarks     Implements DLIN30002
 */
/*===============================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(uint8, LIN_VAR) Lin_ESCI;
    VAR(uint32, AUTOMATIC) counter = ESCI_ZERO;
    VAR(uint8, AUTOMATIC) tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /** Stop any ongoing transmission */
    /** @remarks implements DLIN15003 */

    /* Disable Transmitter*/
    ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

    /* Disable Receiver*/
    ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

    /* Disable Receive Data Ready Interrupt */
    ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

    /* Disable Transmit Data Ready Interrupt */
    ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);
#ifdef LIN_USE_DMA
    /* Transmit DMA disabled */
    ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

    /* Receive DMA disabled */
    ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);
#endif
    /* Disable Frame Control Interrupt */
    ESCI_LLM_LCR1_FCIE_Disable(Lin_ESCI);


    /* wait till Cancellation of current frame */
    while(counter < LIN_TIMEOUT_LOOPS)
        {
#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

        if((ESCI_LLM_IFSR1_IS_TX_ACTIVE(Lin_ESCI) == FALSE))
#endif
#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

#ifdef LIN_USE_DMA
          /* Is there a a transmit or receive DMA request pending ? */
          if((ESCI_LLM_IFSR1_IS_DMA_ACTIVE(Lin_ESCI) == FALSE))
#else
          /* Is there a a transmit or receive interrupt request pending ? */
          if((ESCI_LLM_IFSR1_IS_LIN_ACTIVE(Lin_ESCI) == FALSE))
#endif
#endif
            {
            tmpReturn = (uint8)E_OK;
            break;
            }

          counter++;

        }
    /* Enable Transmitter*/
    ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

    /* Enable Receiver*/
    ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

    if(tmpReturn == (uint8)E_OK)
        {
        /* Set LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* These redundant line are required since LIN state machine gets RESET correctly after
           setting LRES bit three times and then clear it*/
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
        ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

        /* Clear LRES bit of LCR1 register to reset the LIN state machine */
        ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

        /* Check whether wake up detection is enabled */
        if (Lin_Channel_Cfg_Ptr[Lin_ESCI]->LinChannelWakeUpSupport == (uint8) STD_ON)
            {
            /* Wake up detection is enabled */
            /* Clear Wake-Up flag */
            ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(Lin_ESCI);

            /* Enable wake up interrupt */
            ESCI_LLM_LCR1_WUIE_Enable(Lin_ESCI);
            }
        }
    return tmpReturn;
    }
/*===============================================================================================*/
/*!
 * @brief         Send a wake up signal to the LIN bus.
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @remarks implements DLIN30010
 */
/*===============================================================================================*/
FUNC (void, LIN_CODE) ESCI_LLD_WakeUp(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    /* Send Wake up request */
    ESCI_LLM_LCR1_WU_Enable(Lin_ESCI);
    }
/*===============================================================================================*/
/*!
 * @brief         Gets the status of the LIN driver when Channel is operating.
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @param[out]     LinSduPtr pointer to pointer to a shadow buffer or memory
 *                 mapped LIN Hardware receive buffer where the current SDU is
 *                 stored
 * @return LIN_NOT_OK if the LIN driver is not in LIN_INIT state or
 *                    LIN Channel is not valid or
 *                    LIN Channel is not activated or
 *                    LIN Channel is not initialized or
 *                    LIN Channel is in sleep state
 *         LIN_TX_OK - Successful transmission
 *         LIN_TX_BUSY - Ongoing transmission of header or response
 *         LIN_TX_HEADER_ERROR - Error occurred during header
 *                               transmission
 *         LIN_TX_ERROR - Error occurred during response transmission
 *         LIN_RX_OK - Reception of correct response
 *         LIN_RX_BUSY - Ongoing reception where at least one
 *                       byte has been received
 *         LIN_RX_ERROR - Error occurred during reception
 *         LIN_RX_NO_REPONSE - No data byte has been received yet
 *         LIN_CH_UNINIT - Channel is not initialized
 *         LIN_CH_OPERATIONAL - Channel is ready for next header
 *                              transmission and no data are available
 *         LIN_CH_SLEEP - Channel is sleep mode
 *         LIN_NOT_OK otherwise.
 * @note This function returns the state of the current transmission,
 *       reception or operation status, only if Channel is in the
 *       LIN_CH_OPERATIONAL_STATE If the reception of a Slave response
 *       was successful then it provides a pointer to buffer where the data is stored.
 * @remarks implements DLIN30003
 * @remarks
 */
/*===============================================================================================*/
FUNC (Lin_StatusType, LIN_CODE) ESCI_LLD_HardwareGetStatus(CONST(uint8, LIN_CONST) Channel,
                             P2VAR(uint8, AUTOMATIC, LIN_VAR) LinSduPtr)
    {
    VAR(Lin_StatusType,AUTOMATIC) TempReturn = LIN_NOT_OK;

  /* Check error status */
  switch(Lin_LinChFrameErrorStatus[Channel])
    {

    /* Tx data error conditions */
    case LIN_BIT_ERROR:
      /**
       * @file ESCI_LLD.c
       * @note Violates MISRA 2004 Required Rule 12.4, side effects on right hand of 
       *       logical operator: See @ref ESCI_LLD_C_REF_5
       */   
      if ((TransmitHeaderCommand[Channel] == LIN_TX_MASTER_RES_COMMAND)||
          (TransmitHeaderCommand[Channel] == LIN_TX_SLEEP_COMMAND) ||
            (Lin_LinChFrameStatus[Channel] ==LIN_CH_SEND_DATA_ERROR))
        {
        TempReturn = LIN_TX_ERROR;
        }
      /**
       * @file ESCI_LLD.c
       * @note Violates MISRA 2004 Required Rule 12.4, side effects on right hand of 
       *       logical operator: See @ref ESCI_LLD_C_REF_5
       */       
      else if ((TransmitHeaderCommand[Channel] == LIN_TX_SLAVE_RES_COMMAND)||
            (Lin_LinChFrameStatus[Channel] ==LIN_CH_SEND_HEADER_ERROR))
        {
        TempReturn = LIN_TX_HEADER_ERROR;
        }
      else
        {
        TempReturn = LIN_NOT_OK;
        }
      break;

    /* Rx error conditions */
    case LIN_NOISE_ERROR:
    case LIN_CHECKSUM_ERROR:
    case CRC_ERROR:
    case LIN_FRAMING_ERROR:
    case OVERFLOW_ERROR:
    case SLAVE_TIMEOUT_ERROR:
    case UNREQUESTED_DATA_ERROR:
    case PHYSICAL_BUS_ERROR:
      TempReturn = LIN_RX_ERROR;
      break;

    case LIN_NO_ERROR :
      /* Check Lin frame status variable */
      switch(Lin_LinChFrameStatus[Channel])
        {

        case LIN_CH_SEND_HEADER:
        case LIN_CH_SEND_DATA:
          TempReturn =  LIN_TX_BUSY;
          break;

        case LIN_CH_RECEIVE_DATA:
          TempReturn =  LIN_RX_BUSY;
          break;

        /* Tx completed - Status Updated in ISR */
        case LIN_TX_COMPLETE_STATE:
          TempReturn = LIN_TX_OK;
          break;

        /* Rx completed - Status Updated in ISR */
        case LIN_RX_COMPLETE_STATE:
          /* Copy the data from hardware buffer */
          ESCI_LLD_CopyData(Channel, LinSduPtr);
          TempReturn =  LIN_RX_OK;
          break;

        /* Tx completed - But master not received any data */
        case LIN_CH_RECEIVE_NOTHING_STATE:
          TempReturn = LIN_RX_NO_RESPONSE;
          break;

        /* Channel Initialized or wakenup or all activity completed and ready to
           send next header */
        case LIN_CH_READY_STATE:
          TempReturn = LIN_CH_OPERATIONAL;
          break;

        /* Channel not ready */
        case LIN_CH_NOT_READY_STATE:
          TempReturn = LIN_NOT_OK;
          break;

        default :
            Cer_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)ESCI_LLD_HWGETSTATUS_ID,(uint8)LIN_CER_UNEXPECTED_FRAME_STATUS_INTERRUPT);
            /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                  Cer_ReportError() function implementation */
            break;
        }
      break;
    default:
      Cer_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)ESCI_LLD_HWGETSTATUS_ID,(uint8)LIN_CER_UNEXPECTED_FRAME_ERROR_STATUS_INTERRUPT);
      /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                            Cer_ReportError() function implementation */
      break;
    }
    return TempReturn;
    }
/*===============================================================================================*/
/*!
 * @brief         Copy the data received from the ESCI data registers to "LinSduPtr".
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @param[out]     LinSduPtr pointer to pointer to a shadow buffer or memory
 *                 mapped LIN Hardware receive buffer where the current SDU is stored
 * @note         Internal driver function.
 * @remarks        implements DLIN30012
 * @remarks
 */
/*===============================================================================================*/
FUNC (void, LIN_CODE) ESCI_LLD_CopyData(CONST(uint8, LIN_CONST) Channel,
                    VAR(uint8, AUTOMATIC) * LinSduPtr)
    {
    VAR(uint8, AUTOMATIC) Loop;
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
    Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

    for (Loop=ESCI_ZERO;Loop<LIN_MAX_DATA_LENGTH;Loop++)
        {
        /* Copy LSB data received in LinSduPtr[] buffer */
        /**
         * @file ESCI_LLD.c
         * @note Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than 
         *       array indexing used: See @ref ESCI_LLD_C_REF_6
         */         
        LinSduPtr[Loop]  = (Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Loop]);
        }
    }
/*===============================================================================================*/
/*!
 * @brief         Interrupt handler for TX and RX on ESCI.
 * @param[in]     Channel LIN channel (eSCI_A or eSCI_B or eSCI_C) to be addressed
 * @note         Internal driver function.
 * @remarks        implements DLIN30005
 * @remarks
 */
/*===============================================================================================*/
FUNC (void, LIN_CODE) ESCI_LLD_InterruptHandler(CONST(uint8, LIN_CONST) Channel)
    {

        VAR(uint8, LIN_VAR) Lin_ESCI;
        VAR(sint8, AUTOMATIC) LogicalChannel;
        VAR(boolean, AUTOMATIC) IsTxErrorOnSleepCmd = (boolean)FALSE;

    if (Lin_ChannelHardwareMap[Channel] != ESCI_NONMAPPED_CHANNEL_VALUE)
        {

             /* Get the logical channel index from physical channel */
             LogicalChannel = Lin_ChannelHardwareMap[Channel];

             /* Get base address of ESCI module which is used by LIN channel */
             Lin_ESCI = (uint8)Channel;

#ifdef LIN_USE_MSC

            if (Lin_Channel_Cfg_Ptr[LogicalChannel]->MscEnabled == (uint8)STD_ON)
            {

                /* If something was received and there are no errors */
                if(ESCI_LLM_IFSR1_IS_RX_DATA_REG_FULL(Lin_ESCI) && \
                 !(ESCI_LLM_IFSR1_OVERRUN_FLAG_READ(Lin_ESCI) || \
                   ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(Lin_ESCI) || \
                   ESCI_LLM_IFSR1_NOISE_FLAG_READ(Lin_ESCI)|| \
                   ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_READ(Lin_ESCI)))
                {
                            /* Update MSC channel frame operation status to MSC_RUN */
                            MscBuffer[LogicalChannel].State = MSC_RUN;

                            /* No errors occurred on RX. */
                            MscBuffer[LogicalChannel].Errors = 0U;

                            /* Read the data from Data Register and store into the addressed channel's MscBuffer */
                            MscBuffer[LogicalChannel].Data = (uint8)ESCI_LLM_SDR_DATA_READ(Lin_ESCI);

                            /* Which is the MSC frame format ? */
                            if (Lin_Channel_Cfg_Ptr[LogicalChannel]->Msc_FrameFormat == MSC_16_BITS)
                            {
                                /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                                /* The frame contains 4-bit address field and 8 data bits. */
                                /* LSB is received first. */
                                MscBuffer[LogicalChannel].Address = (uint8)ESCI_LLM_SDR_ADDRESS_READ(Lin_ESCI);
                            }
                            else
                            {
                                /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                                /* The frame contains only 8 data bits. */
                                /* LSB is received first. */
                                MscBuffer[LogicalChannel].Address = 0U;
                            }

                }

                /* If there is an error set the corresponding flag in the MSC buffer */
                else
                {

                    /* An error occurred on RX: it can be an Overrun, Framing, Noise or Parity error. */
                    MscBuffer[LogicalChannel].Errors = 1U;

                    /* Check if OR Flag is set */
                    if (ESCI_LLM_IFSR1_OVERRUN_FLAG_READ(Lin_ESCI))
                    {
                        /* Overrun Error flag */
                        ESCI_LLM_IFSR1_OVERRUN_FLAG_Clear(Lin_ESCI);

                        MscBuffer[LogicalChannel].State = MSC_OVERRUN_ERROR;
                    }

                    /* Check if FE Flag is set */
                    if (ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(Lin_ESCI))
                    {
                        /* Framing Error flag */
                        ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

                        MscBuffer[LogicalChannel].State = MSC_FRAMING_ERROR;
                    }

                    /* Check if NF Flag is set */
                    if (ESCI_LLM_IFSR1_NOISE_FLAG_READ(Lin_ESCI))
                    {
                        /* Noise Error flag */
                        ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

                        MscBuffer[LogicalChannel].State = MSC_NOISE_ERROR;

                    }

                    /* Check if PF Flag is set */
                    if (ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_READ(Lin_ESCI))
                    {
                        /* Parity Error flag */
                        ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_Clear(Lin_ESCI);

                        MscBuffer[LogicalChannel].State = MSC_PARITY_ERROR;

                    }

                }

                 /* Clear Receive Data Register Full Interrupt Flag as error occured */
                 ESCI_LLM_IFSR1_RX_DATA_REG_FULL_Clear(Lin_ESCI);

            }

    else
    {

#endif /* LIN_USE_MSC */

    /* Check if Noise Interrupt Flag is set */
    if (ESCI_LLM_IFSR1_NOISE_FLAG_READ(Lin_ESCI))
      {
      /* Clear the Noise Interrupt Flag */
      ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);
      /* Set LIN channel frame error status to LIN_NOISE_ERROR */
      Lin_LinChFrameErrorStatus[LogicalChannel] = LIN_NOISE_ERROR;
      if (Lin_LinChFrameStatus[LogicalChannel] == LIN_CH_SEND_HEADER)
          {
                /* LIN_CH_SEND_HEADER */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
          }
      else
          {
                /* LIN_CH_SEND_DATA */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_DATA_ERROR;

          }
            /* Set LRES bit of LCR1 register to reset the LIN state machine */
            ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

            /* These redundant line are required since LIN state machine gets RESET correctly */
            /* after setting LRES bit three times and then clear it */
            ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
            ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

            /* Disable Transmitter*/
            ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

            /* Disable Receiver*/
            ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

            /* Clear LRES bit of LCR1 register to reset the LIN state machine */
            ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

            /* Enable Transmitter*/
            ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

            /* Enable Receiver*/
            ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

      }
    /* Check if Frame error Interrupt Flag is set */
    /**
     * @file ESCI_LLD.c
     * @note Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: 
     *       See @ref ESCI_LLD_C_REF_4
     */    
     else if (ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(Lin_ESCI) && ESCI_LLM_CR2_FEIE_Read(Lin_ESCI))
     {
      /* Framing Error flag */
      ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

      /* Set LIN channel frame error status to LIN_FRAMING_ERROR */
      Lin_LinChFrameErrorStatus[LogicalChannel] = LIN_FRAMING_ERROR;

      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and  then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
       /* Check if Bit Error Interrupt Flag is set */
        else if (ESCI_LLM_IFSR1_BIT_ERROR_FLAG_READ(Lin_ESCI))
            {
            /* Clear Bit Error Interrupt Flag */
            ESCI_LLM_IFSR1_BIT_ERROR_FLAG_Clear(Lin_ESCI);
            /* Set LIN channel frame error status to LIN_BIT_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = LIN_BIT_ERROR;
            /* Check if error was on sleep frame transmitting */
            if (TransmitHeaderCommand[LogicalChannel] == LIN_TX_SLEEP_COMMAND)
                {
                IsTxErrorOnSleepCmd = (boolean)TRUE;
                }
      if (Lin_LinChFrameStatus[LogicalChannel] == LIN_CH_SEND_HEADER)
          {
                /* LIN_CH_SEND_HEADER */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
          }
      else
          {
                /* LIN_CH_SEND_DATA */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_DATA_ERROR;

          }
      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
      setting LRES bit three times and then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if Slave Timeout Interrupt Flag is set */
         else if (ESCI_LLM_SLAVE_TIMEOUT_FLAG_READ(Lin_ESCI))
            {
            /* Clear Slave Timeout Interrupt Flag */
            ESCI_LLM_SLAVE_TIMEOUT_FLAG_Clear(Lin_ESCI);

            /* Set LIN channel frame error status to LIN_FRAMING_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = SLAVE_TIMEOUT_ERROR;

      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and  then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if Physical Bus Error Interrupt Flag is set */
         else if (ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_READ(Lin_ESCI))
            {
            /* Clear Physical Bus Error Interrupt Flag */
            ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_Clear(Lin_ESCI);
            /* Set LIN channel frame error status to LIN_FRAMING_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = PHYSICAL_BUS_ERROR;
      if (Lin_LinChFrameStatus[LogicalChannel] == LIN_CH_SEND_HEADER)
          {
                /* LIN_CH_SEND_HEADER */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
          }
      else
          {
                /* LIN_CH_SEND_DATA */
                /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_DATA_ERROR;

          }
      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if CRC Error Interrupt Flag is set */
         else if (ESCI_LLM_CRC_ERROR_FLAG_READ(Lin_ESCI))
            {
            /* Clear CRC Error Interrupt Flag */
            ESCI_LLM_CRC_ERROR_FLAG_Clear(Lin_ESCI);

            /* Set LIN channel frame error status to LIN_FRAMING_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = CRC_ERROR;

      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and  then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if Checksum Error Interrupt Flag is set */
        else if (ESCI_LLM_CHECKSUM_ERROR_FLAG_READ(Lin_ESCI))
            {
            /* Clear Checksum Error Interrupt Flag */
            ESCI_LLM_CHECKSUM_ERROR_FLAG_Clear(Lin_ESCI);

            /* Set LIN channel frame error status to LIN_CHECKSUM_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = LIN_CHECKSUM_ERROR;

      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and  then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if Overflow Interrupt Flag is set */
        else if (ESCI_LLM_OVERFLOW_FLAG_READ(Lin_ESCI))
            {
            /* Clear Overflow Interrupt Flag */
            ESCI_LLM_OVERFLOW_FLAG_Clear(Lin_ESCI);

            /* Set LIN channel frame error status to LIN_BUFFER_OVER_RUN_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = OVERFLOW_ERROR;

      /* Set LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* These redundant line are required since LIN state machine gets RESET correctly after
         setting LRES bit three times and  then clear it*/
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
      ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

      /* Disable Transmitter*/
      ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

      /* Disable Receiver*/
      ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

      /* Clear LRES bit of LCR1 register to reset the LIN state machine */
      ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

      /* Enable Transmitter*/
      ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

      /* Enable Receiver*/
      ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

            }
    /* Check if Unrequested Data Received Interrupt Flag is set */
        else if (ESCI_LLM_UNREQUESTED_DATA_FLAG_READ(Lin_ESCI))
            {
            /* Clear Unrequested Data Received Interrupt Flag */
            ESCI_LLM_UNREQUESTED_DATA_FLAG_Clear(Lin_ESCI);
            /* Set LIN channel frame error status to LIN_BUFFER_OVER_RUN_ERROR */
            Lin_LinChFrameErrorStatus[LogicalChannel] = UNREQUESTED_DATA_ERROR;
            }
        /* Check if Frame Complete Interrupt Flag is set */
    else if (ESCI_LLM_FRAME_COMPLETE_FLAG_READ(Lin_ESCI))
      {
            /* Clear Frame Complete Interrupt Flag */
            ESCI_LLM_FRAME_COMPLETE_FLAG_Clear(Lin_ESCI);
            /* Check if error was on sleep frame transmitting */
            if (TransmitHeaderCommand[LogicalChannel] == LIN_TX_SLEEP_COMMAND)
                {
                if (Lin_Channel_Cfg_Ptr[LogicalChannel]->LinChannelWakeUpSupport == (uint8) STD_ON)
                    {
                    /* Clear Wake-Up flag */
                    ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(Lin_ESCI);

                    /* Enable wake up interrupt */
                    ESCI_LLM_LCR1_WUIE_Enable(Lin_ESCI);

                    /* Disable TX interrupt */
                    ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);

                    /* Disable Frame Error Interrupt */
                    ESCI_LLM_CR2_FEIE_Disable(Lin_ESCI);

                    }
                /* Set Channel state to SLEEP state */
                Lin_LinChStatus[LogicalChannel] = LIN_CH_SLEEP_STATE;

                /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_NOT_READY_STATE;

                }
            else
                {
                /* Check the Type of Response */
                if(Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == (uint8)LIN_MASTER_RESPONSE)
                    {
                    /* Master response */
                    /* Update LIN channel frame operation status to LIN_RX_COMPLETE_STATE */
                    Lin_LinChFrameStatus[LogicalChannel] = LIN_TX_COMPLETE_STATE;

                    }
                else
                    {
                    /* Slave response */
                    /* Update LIN channel frame operation status to LIN_TX_COMPLETE_STATE */
                    Lin_LinChFrameStatus[LogicalChannel] = LIN_RX_COMPLETE_STATE;
                    }

                }

            /* Disable Frame Complete Interrupt */
            ESCI_LLM_LCR1_FCIE_Disable(Lin_ESCI);
      }

    /* Check if Receive Data Ready Interrupt Flag is set */
    /**
     * @file ESCI_LLD.c
     * @note Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: 
     *       See @ref ESCI_LLD_C_REF_4
     */        
    else if (ESCI_LLM_IS_RX_READY(Lin_ESCI) && ESCI_LLM_LCR1_RXIE_Read(Lin_ESCI))
      {

            /* first byte received ? */
            if( Lin_BufferCounter[Lin_ESCI] == ESCI_ZERO)
                {
                /* first byte received */

                /* update LIN channel frame operation status to LIN_CH_RECEIVE_DATA */

                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_RECEIVE_DATA;

                }
            /* Store data in buffer */
            Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[Lin_BufferCounter[Lin_ESCI]] =
                                        ESCI_LLM_LRR_Read(Lin_ESCI);


            /* Increment counter by 1 */
            Lin_BufferCounter[Lin_ESCI]++;


            /* Is this the last byte ? */
            if(Lin_BufferCounter[Lin_ESCI] >= Lin_BufferCounterMax[Lin_ESCI])
                {
                /* Last byte has been received */

                /* Disable Receive Data Ready Interrupt */
                ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

                /* Clear Receive Data Ready Interrupt flag */
                ESCI_LLM_RX_READY_Clear(Lin_ESCI);

                }
            else
                {
#ifdef LIN_USE_DMA
                /* Is DMA enabled in the configuration for this Lin channel */
          if(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinDMAEnabled == (uint8)STD_ON)
                    {

                    /* Disable Receive Data Ready Interrupt */
                    ESCI_LLM_LCR1_RXIE_Disable(Lin_ESCI);

                    /* Clear Receive Data Ready Interrupt Flag */
                    ESCI_LLM_RX_READY_Clear(Lin_ESCI);

                    /* Receive DMA enabled */
                    ESCI_LLM_CR2_RXDMA_Enable(Lin_ESCI);

                    /* Start a DMA transfer */
                    Dma_start_channel(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinRxDMAChannel);
                    }
                else
                    {
#endif
                    /* ISR driven */
                    /* Clear Receive Data Ready Interrupt flag */
                    ESCI_LLM_RX_READY_Clear(Lin_ESCI);
#ifdef LIN_USE_DMA
                    }
#endif
                }
      }

    /* Check if Transmit Data Ready Interrupt Flag is set */
    /**
     * @file ESCI_LLD.c
     * @note Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: 
     *       See @ref ESCI_LLD_C_REF_4
     */
    else if (ESCI_LLM_IS_TX_READY(Lin_ESCI) && ESCI_LLM_LCR1_TXIE_Read(Lin_ESCI))
      {
            /* Clear Transmit Data Ready Interrupt Flag */
            ESCI_LLM_TX_READY_Clear(Lin_ESCI);


            if(((Lin_BufferCounter[Lin_ESCI] < MASTER_RESPONSE_HEADER_WRITE_COUNT) &&
              ((Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == (uint8)LIN_MASTER_RESPONSE)||
              (Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == SLEEP_CMD_TYPE)))
                ||  ((Lin_BufferCounter[Lin_ESCI] < SLAVE_RESPONSE_HEADER_WRITE_COUNT)
                && (Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == (uint8)LIN_SLAVE_RESPONSE)))
                {
                /* Send header */
                ESCI_LLM_LTR_Conf(Lin_ESCI,
                      Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[Lin_BufferCounter[Lin_ESCI]]);

                /* Update LIN channel frame status to LIN_CH_SEND_HEADER */
                Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_HEADER;
                }
            else
                {
                if((Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == (uint8)LIN_MASTER_RESPONSE)||
                  (Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == SLEEP_CMD_TYPE))
                    {
                    /* Send data */
                    ESCI_LLM_LTR_Conf(Lin_ESCI,
                        Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[(Lin_BufferCounter[Lin_ESCI]) -
                          MASTER_RESPONSE_HEADER_WRITE_COUNT]);

                    if(Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE == (uint8)LIN_MASTER_RESPONSE)
                        {
                        /* Update LIN channel frame operation status to LIN_CH_SEND_DATA */
                        Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_SEND_DATA;
                        }
                    }
                }


            /* Increment counter by 1 */
            Lin_BufferCounter[Lin_ESCI]++;

            /* Is this the last byte ? */
            if(Lin_BufferCounter[Lin_ESCI] >= Lin_BufferCounterMax[Lin_ESCI])
                {
                /* Last byte has been transmitted */
                if((Lin_LinChFrameStatus[LogicalChannel] == LIN_CH_SEND_HEADER) &&
                   (Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE != (uint8)LIN_MASTER_RESPONSE))
                    {
                    /* Set max count */
                    Lin_BufferCounterMax[Lin_ESCI] =
                              Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[ESCI_HEADER_ONE];

                    /* reset counter */
                    Lin_BufferCounter[Lin_ESCI] = ESCI_ZERO;
                    }

                /* Last write of the header, clear all error flags and RXRDY */
                /* Clear the Noise Interrupt Flag */
                ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

                /* Framing Error flag */
                ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

                /* Clear Bit Error Interrupt Flag */
                ESCI_LLM_IFSR1_BIT_ERROR_FLAG_Clear(Lin_ESCI);

                /* Clear Slave Timeout Interrupt Flag */
                ESCI_LLM_SLAVE_TIMEOUT_FLAG_Clear(Lin_ESCI);

                /* Clear Physical Bus Error Interrupt Flag */
                ESCI_LLM_PHYSICAL_BUS_ERROR_FLAG_Clear(Lin_ESCI);

                /* Clear CRC Error Interrupt Flag */
                ESCI_LLM_CRC_ERROR_FLAG_Clear(Lin_ESCI);

                /* Clear Checksum Error Interrupt Flag */
                ESCI_LLM_CHECKSUM_ERROR_FLAG_Clear(Lin_ESCI);

                /* Clear Overflow Interrupt Flag */
                ESCI_LLM_OVERFLOW_FLAG_Clear(Lin_ESCI);

                /* Clear Unrequested Data Received Interrupt Flag */
                ESCI_LLM_UNREQUESTED_DATA_FLAG_Clear(Lin_ESCI);

                /* Disable Transmit Data Ready Interrupt */
                ESCI_LLM_LCR1_TXIE_Disable(Lin_ESCI);

                }
      }

    /* Wake up interrupt */
    /* Wake up flag set */
    /**
     * @file ESCI_LLD.c
     * @note Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: 
     *       See @ref ESCI_LLD_C_REF_4
     */    
    else if (ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_READ(Lin_ESCI) &&
             ESCI_LLM_LCR1_WUIE_Read(Lin_ESCI))
        {
#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

      /* In case of wakeup interrupt the LIN Wake-Up active status bit is also set */
      if (ESCI_LLM_IFSR1_IS_WAKEUP_ACTIVE(Lin_ESCI) || \
          TransmitHeaderCommand[LogicalChannel] == LIN_TX_SLEEP_COMMAND)
      {
#endif
          /* Disable wake up interrupt */
          ESCI_LLM_LCR1_WUIE_Disable(Lin_ESCI);
          /* Clear Wake-Up flag */
          ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(Lin_ESCI);

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/
          /* Clear Framing Error flag */
          ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

          /* Set LRES bit of LCR1 register to reset the LIN state machine */
          ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

          /* These redundant line are required since LIN state machine gets RESET correctly after
             setting LRES bit three times and  then clear it*/
          ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);
          ESCI_LLM_LCR1_LRES_Enable(Lin_ESCI);

          /* Disable Transmitter*/
          ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

          /* Disable Receiver*/
          ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

          /* Clear LRES bit of LCR1 register to reset the LIN state machine */
          ESCI_LLM_LCR1_LRES_Disable(Lin_ESCI);

          /* Enable Transmitter */
          ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

          /* Enable Receiver*/
          ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

          /* Enable Frame Error Interrupt */
          ESCI_LLM_CR2_FEIE_Enable(Lin_ESCI);
#endif
          /* Check whether the Lin channel status is in LIN_CH_SLEEP_STATE */
          if (Lin_LinChStatus[LogicalChannel] == LIN_CH_SLEEP_STATE)
            {
#ifdef LIN_GLOBAL_WAKEUP_SUPPORT
                    /* Check whether wake up detection is enabled */
              if (Lin_Channel_Cfg_Ptr[LogicalChannel]->LinChannelWakeUpSupport == (uint8) STD_ON)
                {
                /* Indicates a valid timer wakeup event to ECU State Manager */
                EcuM_CheckWakeup(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinChannelEcuMWakeUpSource);
                }
#endif
            /* Set Channel state Operational */
            Lin_LinChStatus[LogicalChannel] = LIN_CH_OPERATIONAL_STATE;
            /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
            Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_READY_STATE;
            }
#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
          }
#endif
      }

    else
        {
            /* Do nothing*/
        }
        /* Check if error was on sleep frame transmitting */
        if (IsTxErrorOnSleepCmd == (boolean)TRUE) /* Error was on sleep frame transmitting */
            {
            /* Check whether wake up detection is enabled */
            if (Lin_Channel_Cfg_Ptr[LogicalChannel]->LinChannelWakeUpSupport == (uint8) STD_ON)
                {
                /* Wake up detection enabled */
                /* Clear Wake-Up flag */
                ESCI_LLM_LIN_WAKEUP_RECEIVED_FLAG_Clear(Lin_ESCI);
                /* Enable wake up interrupt */
                ESCI_LLM_LCR1_WUIE_Enable(Lin_ESCI);
                }
            /* Set Channel state Sleep */
            Lin_LinChStatus[LogicalChannel] = LIN_CH_SLEEP_STATE;
            /* Update TransmitHeaderCommand value to LIN_TX_NO_COMMAND */
            TransmitHeaderCommand[LogicalChannel] = LIN_TX_NO_COMMAND;
            /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
            Lin_LinChFrameStatus[LogicalChannel] = LIN_CH_NOT_READY_STATE;
            /* Reset IsTxErrorOnSleepCmd flag */
            IsTxErrorOnSleepCmd = (boolean)FALSE;
            }

#ifdef LIN_USE_MSC
        }
#endif

    }

    return; /* exit function with no return */
}


#ifdef LIN_USE_DMA
/*===============================================================================================*/
/*!
 * @brief          ESCI_LLD_InterruptHandler_eDma.
 * @param[in]      Channel to be addressed.
 * @note           Internal driver function for DMA functionality.
 * @remarks implements DLIN30009
 */
/*===============================================================================================*/
FUNC(void, LIN_CODE) ESCI_LLD_Tx_InterruptHandler_eDma(CONST(uint8,LIN_CONST) Channel)
    {
    VAR(sint8, AUTOMATIC) LogicalChannel;
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the logical channel index from physical channel */
    LogicalChannel = Lin_ChannelHardwareMap[Channel];

    if (Lin_ChannelHardwareMap[Channel] != ESCI_NONMAPPED_CHANNEL_VALUE)
        {
        /* Get base address of ESCI module which is used by LIN channel */
        Lin_ESCI = (uint8)Channel;

        Dma_ack_interrupt(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinTxDMAChannel);

        /* Transmit DMA disabled */
        ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

        /* Sent Header && SLAVE_RESPONSE ? */
        if(Lin_ChShadowBuffPtr[Lin_ESCI]->TYPE != LIN_MASTER_RESPONSE)
            {

            /* Destination address -> address of channel shadow buffer second byte ->
               first byte will be received with ISR */
            /* DMA_RX  */
            Dma_configure_channel( Lin_Channel_Cfg_Ptr[LogicalChannel]->LinRxDMAChannel,
                         ESCI_LRR(Lin_ESCI),
                         0U,
                         0U,
                         0U,
                         1U,
                         0U,
                         (uint32)&Lin_ChShadowBuffPtr[Lin_ESCI]->DATA[1],
                         Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[1] - 1U,
                         1U,
                         0U,
                         Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[1] - 1U,
                         DMA_INT_MAJ_MASK);

            Lin_BufferCounterMax[Lin_ESCI] = Lin_ChShadowBuffPtr[Lin_ESCI]->HEADER[1];

            /* reset counter */
            Lin_BufferCounter[Lin_ESCI] = 0U;

            }

        /* clear DMA interrupt request */
        /* Disable the interrupt for RX DMA channel */
        Dma_disable_interrupt(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinTxDMAChannel);
        }
    }

/*===============================================================================================*/
/*!
 * @brief          ESCI_LLD_InterruptHandler_eDma.
 * @param[in]      Channel to be addressed.
 * @note           Internal driver function for DMA functionality.
 * @remarks implements DLIN30006
 */
/*===============================================================================================*/
FUNC(void, LIN_CODE) ESCI_LLD_Rx_InterruptHandler_eDma(CONST(uint8,LIN_CONST) Channel)
    {
    VAR(sint8, AUTOMATIC) LogicalChannel;
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Get the logical channel index from physical channel */
    LogicalChannel = Lin_ChannelHardwareMap[Channel];

    if (Lin_ChannelHardwareMap[Channel] != ESCI_NONMAPPED_CHANNEL_VALUE)
        {
        /* Get base address of ESCI module which is used by LIN channel */
        Lin_ESCI = (uint8)Channel;

        Dma_ack_interrupt(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinRxDMAChannel);

        /* Transmit DMA disabled */
        ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);

        /* clear DMA interrupt request */
        /* Disable the interrupt for RX DMA channel */
        Dma_disable_interrupt(Lin_Channel_Cfg_Ptr[LogicalChannel]->LinRxDMAChannel);
        }
    }
#endif

/**
 * MISRA 2004 Required Rule 11.1  -  end violation
 */

#define LIN_STOP_SEC_CODE
/**
 * @file ESCI_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref ESCI_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref ESCI_LLD_C_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/* End of File */
