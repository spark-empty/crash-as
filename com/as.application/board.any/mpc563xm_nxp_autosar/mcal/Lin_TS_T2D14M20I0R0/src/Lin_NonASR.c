/**
    @file     Lin_NonASR.c
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Lin NonAutosar high level interface implementation.
    @details  Lin NonAutosar high level interface implementation.
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 * 
 * @section LIN_NONASR_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 * 
 * @section LIN_NONASR_C_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
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


#include "Lin.h"
#include "Lin_NonASR.h"
#include "Lin_LLD.h"
#include "ESCI_LLD.h"
#ifdef LIN_USE_DMA
  #include "Dma_LLD.h"
#endif
#include "Reg_Macros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   Parameters that shall be published within the Lin driver header file and also in the
         module's description file
@remarks Covers LIN062
*/
#define LIN_VENDOR_ID_NONASR_C            43
#define LIN_AR_MAJOR_VERSION_NONASR_C     3
#define LIN_AR_MINOR_VERSION_NONASR_C     0
#define LIN_AR_PATCH_VERSION_NONASR_C     0
#define LIN_SW_MAJOR_VERSION_NONASR_C     2
#define LIN_SW_MINOR_VERSION_NONASR_C     0
#define LIN_SW_PATCH_VERSION_NONASR_C     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/** @remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != LIN_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_NONASR_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin_NonASR.c and Lin.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != LIN_AR_MAJOR_VERSION_LLD) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != LIN_AR_MINOR_VERSION_LLD) || \
       (LIN_AR_PATCH_VERSION_NONASR_C != LIN_AR_PATCH_VERSION_LLD))
      #error "AutoSar Version Numbers of Lin_NonASR.c and Lin_LLD.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION_LLD) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION_LLD))
    #error "Software Version Numbers of Lin_NonASR.c and Lin_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != STD_TYPES_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != STD_TYPES_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and Std_Types.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != LIN_IF_AR_MAJOR_VERSION_CBK) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != LIN_IF_AR_MINOR_VERSION_CBK))
      #error "AutoSar Version Numbers of Lin_NonASR.c and LinIf_Cbk.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != ECUM_CBK_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != ECUM_CBK_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and EcuM_CBK.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != ECUM_CFG_AR_MINOR_VERSION))
      #error "Software Version Numbers of Lin_NonASR.c and EcuM_Cfg.h are different"
  #endif

  /* Check if the source file and Dem header file are of the same version */
  #if ((LIN_AR_MAJOR_VERSION_NONASR_C != DEM_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_C != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and Dem.h are different"
  #endif
#endif

#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* Check if the source file and Det header file are of the same version */
  #ifdef CHECK_AUTOSAR_VERSION
    #if ((LIN_AR_MAJOR_VERSION_NONASR_C != DET_AR_MAJOR_VERSION) || \
         (LIN_AR_MINOR_VERSION_NONASR_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Lin_NonASR.c and Det.h are different"
    #endif
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

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

#define LIN_START_SEC_VAR_UNSPECIFIED
/**
 * @file Lin_NonASR.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_NONASR_C_REF_2
 */
#include "MemMap.h"

/**
 * @brief Global variable to allow the appication
 *        to switch to the alternate clock mode.
 */
#if LIN_DUAL_CLOCK_MODE == STD_ON
    VAR(Lin_ClockModes,LIN_VAR)LinClock = LIN_NORMAL;
#endif
#ifdef LIN_USE_MSC
  #ifdef LIN_USE_DMA
    volatile VAR(MSC_DataType, LIN_VAR) MscBuffer[LIN_NUM_BYTES];
  #else
    volatile VAR(MSC_DataType, LIN_VAR) MscBuffer[LIN_HW_MAX_MODULES];
  #endif
#endif

#define LIN_STOP_SEC_VAR_UNSPECIFIED
/**
 * @file Lin_NonASR.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_NONASR_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_NONASR_C_REF_2
 */
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#define LIN_START_SEC_CODE
/**
 * @file Lin_NonASR.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_NONASR_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_NONASR_C_REF_2
 */
#include "MemMap.h"

#if (LIN_DUAL_CLOCK_MODE == STD_ON)

/**
 * @brief   Lin_SetClockMode
 * @details Switch the clock mode to the alternate clock mode on all the Lin channels
 * 
 * @param[in] ClockMode - New clock mode
 * 
 * @remarks Covers       PR-MCAL-3201
 */
FUNC (Std_ReturnType, LIN_CODE) Lin_SetClockMode(VAR(Lin_ClockModes, AUTOMATIC) ClockMode)
{
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (uint8)E_OK;
    VAR(uint8,AUTOMATIC) chLoop;
    VAR(uint8,AUTOMATIC) Lin_ESCI;
    VAR(Lin_StatusType,AUTOMATIC) LinStatus = LIN_NOT_OK;
    VAR(uint8,AUTOMATIC) *linSduPtr[1];
    VAR(uint8,AUTOMATIC) linSdu[8] = {(uint8)0, (uint8)0, (uint8)0, (uint8)0, (uint8)0, \
                                      (uint8)0, (uint8)0, (uint8)0};
    linSduPtr[0] = linSdu;

    for(chLoop=(uint8)0U; chLoop < LIN_HW_MAX_MODULES; chLoop++)
    {
        /* Get the hardware Lin channel from logical channel */
        Lin_ESCI = Lin_Channel_Cfg_Ptr[chLoop]->LinChannelID;

        LinStatus = Lin_GetStatus(chLoop, linSduPtr);

        switch (LinStatus)
        {
            case LIN_NOT_OK :
            case LIN_CH_UNINIT :

                /* If the LIN driver or some channels are not initialized it's not possible to
                change the baudrate */
                TempReturn = (uint8)E_NOT_OK;

                break;

            default :
                /* Disable Transmitter*/
                ESCI_LLM_CR1_TE_Disable(Lin_ESCI);

                /* Disable Receiver*/
                ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

                #ifdef LIN_USE_DMA
                    /* Transmit DMA disabled */
                    ESCI_LLM_CR2_TXDMA_Disable(Lin_ESCI);

                    /* Receive DMA disabled */
                    ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);
                #endif

                if (ClockMode == LIN_NORMAL)
                {
                    /* set baud rate value for normal running mode */
                    ESCI_LLM_BRR_Config(Lin_ESCI, \
                                        Lin_Cfg_Ptr->Lin_Channel[chLoop]->Lin_BaudRate_RegValue);
                }
                else
                {
                    /* set baud rate value for low power mode */
                    ESCI_LLM_BRR_Config(Lin_ESCI, \
                    Lin_Cfg_Ptr->Lin_Channel[chLoop]->Lin_BaudRate_RegValue_Alternate);
                }

                /* Enable Receiver */
                ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

                /* Enable Transmitter */
                ESCI_LLM_CR1_TE_Enable(Lin_ESCI);

                #ifdef LIN_USE_DMA
                    /* Transmit DMA enabled */
                    ESCI_LLM_CR2_TXDMA_Enable(Lin_ESCI);

                    /* Receive DMA enabled */
                    ESCI_LLM_CR2_RXDMA_Enable(Lin_ESCI);
                #endif

                break;
        }
    }
    return TempReturn;
}
#endif /* DUAL CLOCK MODE */

#ifdef LIN_USE_MSC

/**
 * @brief   Msc_InitChannel
 * @details Initialize Channel with MSC functionality.
 * 
 * @param[in] Channel - MSC to be initialized.
 * @param[in] Config  - Pointer to LIN channel configuration set.
 * 
 * @remarks Covers       LIN_CUSTOM002
 */
FUNC(void,LIN_CODE) Msc_InitChannel(CONST(uint8, LIN_CONST)Channel,P2CONST(Lin_ChannelConfigType,\
                                    AUTOMATIC, LIN_CONST)Config)
{
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Check for invalid channel */
    if (Channel >= LIN_HW_MAX_MODULES)
    {
        /* Invalid channel */
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_INITCHANNEL_ID,\
                            (uint8)LIN_E_INVALID_CHANNEL);
        #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        /* Check Config for not being a null pointer */
        if (Config == NULL_PTR)
        {
            /* Invalid pointer */
            #if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_INITCHANNEL_ID,\
                                (uint8)LIN_E_INVALID_POINTER);
            #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            Lin_Channel_Cfg_Ptr[Channel] = Config;

            if(Lin_Channel_Cfg_Ptr[Channel]->MscEnabled == (uint8)STD_ON)
            {
                /* Initialize MSC buffer */
                MscBuffer[Channel].Data = 0U;
                MscBuffer[Channel].Errors = 0U;
                MscBuffer[Channel].Address = 0U;

                /* Update MSC channel frame operation status to MSC_IDLE */
                MscBuffer[Channel].State = MSC_IDLE;

                /* Get the hardware Lin channel from logical channel */
                Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

                /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                /* Enable eSCI module */
                ESCI_LLM_ENABLE_ESCI_MODULE(Lin_ESCI);

                /* Set MSC frame format */
                if (Lin_Channel_Cfg_Ptr[Channel]->Msc_FrameFormat == MSC_16_BITS)
                {
                    /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains 4-bit address field and 8 data bits. */
                    /* LSB is received first. */
                    ESCI_LLM_CR1_M_Enable(Lin_ESCI);
                }
                else
                {
                    /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains only 8 data bits. */
                    /* LSB is received first. */
                    ESCI_LLM_CR1_M_Disable(Lin_ESCI);
                }

                /* Set Frame Format Mode 2 value */
                ESCI_LLM_M2_Enable(Lin_ESCI);

                /* Set Parity Enable value */
                ESCI_LLM_CR1_PE_Enable(Lin_ESCI);

                /* check the parity type for even or odd */
                if (Lin_Channel_Cfg_Ptr[Channel]->MscParity == MSC_EVEN)
                {
                    /* Even parity */
                    ESCI_LLM_CR1_PT_Disable(Lin_ESCI);
                }
                else
                {
                    /* Odd parity.*/
                    ESCI_LLM_CR1_PT_Enable(Lin_ESCI);
                }

                /* Set baud rate value */
                ESCI_LLM_BRR_Config(Lin_ESCI, Lin_Channel_Cfg_Ptr[Channel]->Msc_BaudRate_RegValue);

                if (Lin_Channel_Cfg_Ptr[Channel]->MscPolarity == MSC_NORMAL)
                {
                    /* A RX low level bit at SI is stored in the upstream channel as logic 0. */
                    /* A RX high level bit at SI is stored in the upstream channel as logic 1.*/
                    ESCI_LLM_CR2_RXPOL_Disable(Lin_ESCI);
                }
                else
                {
                    /* A RX low level bit at SI is stored in the upstream channel as logic 1. */
                    /* A RX high level bit at SI is stored in the upstream channel as logic 0.*/
                    ESCI_LLM_CR2_RXPOL_Enable(Lin_ESCI);
                }

                /* Enable Receiver*/
                ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

                if (Lin_Channel_Cfg_Ptr[Channel]->MscPollingMode == (uint8)STD_OFF)
                {
                    /* Enable Frame Error Interrupt */
                    ESCI_LLM_CR2_FEIE_Enable(Lin_ESCI);

                    /* Enable Parity Flag Interrupt */
                    ESCI_LLM_CR2_PFIE_Enable(Lin_ESCI);

                    /* Enable Noise Flag Interrupt */
                    ESCI_LLM_CR2_NFIE_Enable(Lin_ESCI);

                    /* Enable Overrun Flag Interrupt */
                    ESCI_LLM_CR2_ORIE_Enable(Lin_ESCI);

                    /* Enable Receiver full Interrupt request */
                    if (Lin_Channel_Cfg_Ptr[Channel]->RieEnabled == STD_ON)
                    {
                        ESCI_LLM_CR1_RIE_Enable(Lin_ESCI);                        
                    }
                }
                else
                {
                    /* Enable Overrun Flag Interrupt */
                    ESCI_LLM_ERROR_FLAG_OVERRUN_Enable(Lin_ESCI);

                    /* Enable Frame Error Interrupt */
                    ESCI_LLM_ERROR_FLAG_FRAME_ERROR_Enable(Lin_ESCI);

                    /* Enable Parity Flag Interrupt */
                    ESCI_LLM_ERROR_FLAG_PARITY_ERROR_Enable(Lin_ESCI);
                }

                #ifdef LIN_USE_DMA
                    /* DMA_RX  */
                    Dma_configure_channel( Lin_Channel_Cfg_Ptr[Channel]->LinRxDMAChannel,
                        ESCI_SDR(Lin_ESCI),
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAtransferSize,  /* ssize */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAtransferSize,  /* dsize */
                        0U,    /* soff */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAnbytesToTransfer, /*nbytes to transfer*/
                        0U,    /* slast */
                        (uint32)&(MscBuffer[0].Data),
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAiterationCnt,      /* citer */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAdestinationOffset, /* doff */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAaddressAdjustment, /* dlast_sg_addr */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAiterationCnt,      /* biter */
                        Lin_Channel_Cfg_Ptr[Channel]->LinDMAInterruptFlags);   /* int_half int_maj*/

                        /* Transmit DMA enabled */
                        ESCI_LLM_CR2_TXDMA_Enable(Lin_ESCI);

                        /* Receive DMA enabled */
                        ESCI_LLM_CR2_RXDMA_Enable(Lin_ESCI);

                        /* Start a DMA transfer */
                        Dma_start_channel(Lin_Channel_Cfg_Ptr[Channel]->LinRxDMAChannel);
                #endif

                /* Update MSC channel frame operation status to MSC_READY */
                MscBuffer[Channel].State = MSC_READY;

                /* Map configured hardware channel to logical channel */
                Lin_ChannelHardwareMap[Lin_Channel_Cfg_Ptr[Channel]->LinChannelID] = (sint8)Channel;

            }

        }

    }
    return;
}

/**
 * @brief   Msc_DeInitChannel
 * @details De-Inits a channel with MSC functionality.
 * 
 * @param[in] Channel - MSC to be de-initialized.
 * 
 * @remarks Covers       LIN_CUSTOM002
 */
FUNC(void, LIN_CODE) Msc_DeInitChannel(CONST(uint8, LIN_CONST)Channel)
{
    VAR(uint8, LIN_VAR) Lin_ESCI;

    /* Check for invalid channel */
    if (Channel >= LIN_HW_MAX_MODULES) /* Invalid channel */
    {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_DEINITCHANNEL_ID,\
                            (uint8)LIN_E_INVALID_CHANNEL);
        #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Lin_Channel_Cfg_Ptr[Channel]->MscEnabled == (uint8)STD_ON)
        {
            /* Clear MSC buffer */
            MscBuffer[Channel].Data = 0U;
            MscBuffer[Channel].Errors = 0U;
            MscBuffer[Channel].Address = 0U;

            /* Get the hardware Lin channel from logical channel */
            Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

            /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
            /* Disable eSCI module */
            ESCI_LLM_DISABLE_ESCI_MODULE(Lin_ESCI);

            /* Write the reset value of Control Register 1 (eSCI_CR1)*/
            ESCI_LLM_CR1_Reset(Lin_ESCI);

            /* Disable Parity Enable value */
            ESCI_LLM_CR1_PE_Disable(Lin_ESCI);

            /* set default parity type */
            ESCI_LLM_CR1_PT_Disable(Lin_ESCI);

            /* Write the reset value of Baud Rate Register (eSCI_BRR)*/
            ESCI_LLM_BRR_Reset(Lin_ESCI);

            if (Lin_Channel_Cfg_Ptr[Channel]->MscPollingMode == (uint8)STD_OFF)
            {
                /* Disable the Receive Interrupt Enable */
                ESCI_LLM_CR1_RIE_Disable(Lin_ESCI);

                /* Disable Frame Error Interrupt */
                ESCI_LLM_CR2_FEIE_Disable(Lin_ESCI);

                /* Disable Parity Flag Interrupt */
                ESCI_LLM_CR2_PFIE_Disable(Lin_ESCI);

                /* Disable Noise Flag Interrupt */
                ESCI_LLM_CR2_NFIE_Disable(Lin_ESCI);

                /* Disable Overrun Flag Interrupt */
                ESCI_LLM_CR2_ORIE_Disable(Lin_ESCI);
            }
            else
            {
                /* Disable Overrun Flag Interrupt */
                ESCI_LLM_ERROR_FLAG_OVERRUN_Disable(Lin_ESCI);

                /* Disable Frame Error Interrupt */
                ESCI_LLM_ERROR_FLAG_FRAME_ERROR_Disable(Lin_ESCI);

                /* Disable Parity Flag Interrupt */
                ESCI_LLM_ERROR_FLAG_PARITY_ERROR_Disable(Lin_ESCI);
            }

            #ifdef LIN_USE_DMA
                if(Lin_Channel_Cfg_Ptr[Channel]->LinDMAEnabled == (uint8)STD_ON)
                {
                    /* DMA is used */

                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                    /* Receive DMA disabled */
                    ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);

                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: end violation */

                    /* Disable the interrupt for RX DMA channel */
                    Dma_disable_interrupt(Lin_Channel_Cfg_Ptr[Channel]->LinRxDMAChannel);
                }
            #endif

            /* Disable Receiver*/
            ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

            /* Update MSC channel frame operation status to MSC_IDLE */
            MscBuffer[Channel].State = MSC_IDLE;

            /* Remove channel from hardware map */
            Lin_ChannelHardwareMap[Lin_Channel_Cfg_Ptr[Channel]->LinChannelID] = -1;
        }
    }
    return;
}

/**
 * @brief   Msc_GetStatus
 * @details Gets the status of the Channel with MSC functionality.
 *
 * @param[in] Channel - MSC to be initialized.
 *
 * @param[out] Lin_SduPtr   Pointer to pointer to a shadow
 *                          buffer or memory mapped eSCI Hardware
 *                          receive buffer where the current data is
 *                          stored.
 * @return Msc_StatusType   The MSC channel status.
 *  - MSC_IDLE              Receiver is disabled and no
 *                          reception is running.
 *  - MSC_READY             Receiver is enabled and no
 *                          reception is running.
 *  - MSC_RUN               Receiver is enabled and
 *                          reception is running.
 *  - MSC_WAKEUP            Receiver is in wakeup mode.
 *  - MSC_OVERRUN_ERROR     Erroneous reception due to
 *                          an OR error.
 *  - MSC_FRAMING_ERROR     Erroneous reception due to
 *                          a FE error.
 *  - MSC_PARITY_ERROR      Erroneous reception due to
 *                          a PE error.
 *  - MSC_NOISE_ERROR       Erroneous reception due to
 *                          an NF error.
 * 
 * @remarks Covers       LIN_CUSTOM002
 */
FUNC(Msc_StatusType, LIN_CODE) Msc_GetStatus(CONST(uint8, LIN_CONST) Channel)
{
    VAR(uint8, LIN_VAR) Lin_ESCI;

    VAR(Msc_StatusType, LIN_VAR) MSC_State = MSC_IDLE;

    /* Check for invalid channel */
    if (Channel >= LIN_HW_MAX_MODULES) /* Invalid channel */
    {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_GETSTATUS_ID,\
                            (uint8)LIN_E_INVALID_CHANNEL);
        #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Lin_Channel_Cfg_Ptr[Channel]->MscEnabled == (uint8)STD_ON)
        {
            /* Get the hardware Lin channel from logical channel */
            Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

            switch (MscBuffer[Channel].State)
            {
                case MSC_IDLE :
                    /* Check if RE Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                       (!ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&&(!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_READY;
                    }
                    break;
                    
                case MSC_READY :
                    /* Check if RACT Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                       (ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_RUN;
                    }

                    /* Check if RWU Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && (ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_WAKEUP;
                    }

                    /* Check if RE Flag is reset */
                    if (!ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                      (!ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_IDLE;
                    }

                    break;
                    
                case MSC_RUN :
                    /* Check if RE Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                      (!ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_READY;
                    }

                    /* Check if RWU Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && (ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_WAKEUP;
                    }

                    /* Check if RE Flag is reset */
                    if (!ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                      (!ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_IDLE;
                    }

                    /* Check if OR Flag is set */
                    if (ESCI_LLM_IFSR1_OVERRUN_FLAG_READ(Lin_ESCI) && \
                       (ESCI_LLM_SDR_ERROR_FLAG_READ(Lin_ESCI)))
                    {
                        /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                        /* Overrun Error flag */
                        ESCI_LLM_IFSR1_OVERRUN_FLAG_Clear(Lin_ESCI);

                        MscBuffer[Channel].State = MSC_OVERRUN_ERROR;
                    }

                    /* Check if FE Flag is set */
                    if (ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(Lin_ESCI) && \
                       (ESCI_LLM_SDR_ERROR_FLAG_READ(Lin_ESCI)))
                    {
                        /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                        /* Framing Error flag */
                        ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

                        MscBuffer[Channel].State = MSC_FRAMING_ERROR;
                    }

                    /* Check if NF Flag is set */
                    if (ESCI_LLM_IFSR1_NOISE_FLAG_READ(Lin_ESCI) && \
                       (ESCI_LLM_SDR_ERROR_FLAG_READ(Lin_ESCI)))
                    {
                        /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                        /* Noise Error flag */
                        ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

                        MscBuffer[Channel].State = MSC_NOISE_ERROR;
                    }

                    /* Check if PF Flag is set */
                    if (ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_READ(Lin_ESCI) && \
                       (ESCI_LLM_SDR_ERROR_FLAG_READ(Lin_ESCI)))
                    {
                        /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                        /* Parity Error flag */
                        ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_Clear(Lin_ESCI);

                        MscBuffer[Channel].State = MSC_PARITY_ERROR;
                    }

                    break;
                    
                case MSC_WAKEUP :
                    /* Check if RE Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                      (!ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_READY;
                    }

                    /* Check if RACT Flag is set */
                    if (ESCI_LLM_CR1_RE_Read(Lin_ESCI) && \
                       (ESCI_LLM_IFSR1_IS_RX_ACTIVE(Lin_ESCI))&& (!ESCI_LLM_CR1_RWU_Read(Lin_ESCI)))
                    {
                        MscBuffer[Channel].State = MSC_RUN;
                    }
                    break;
                    
                case MSC_OVERRUN_ERROR :
                case MSC_FRAMING_ERROR :
                case MSC_PARITY_ERROR :
                case MSC_NOISE_ERROR :
                default :
                    /* Disable Receiver*/
                    ESCI_LLM_CR1_RE_Disable(Lin_ESCI);

                    #ifdef LIN_USE_DMA
                        /* Receive DMA disabled */
                        ESCI_LLM_CR2_RXDMA_Disable(Lin_ESCI);
                    #endif

                    /* Enable Receiver */
                    ESCI_LLM_CR1_RE_Enable(Lin_ESCI);

                    #ifdef LIN_USE_DMA
                    /* Receive DMA enabled */
                    ESCI_LLM_CR2_RXDMA_Enable(Lin_ESCI);
                    #endif

                    MscBuffer[Channel].Errors = 0U;

                    MscBuffer[Channel].State = MSC_READY;

                    break;
            }

            /* Get the MSC channel state */
            MSC_State = MscBuffer[Channel].State;
        }
    }
    return MSC_State;
}

#ifdef MSC_RX_POLLING_MODE
/**
 * @brief   Msc_Polling
 * @details Tests the RDRF flag to know if something was received by 
 *          the channel with MSC functionality and in that case fill the 
 *          buffer with the received data.
 * 
 * @param[in]  Channel - MSC to be initialized.
 * 
 * @param[out] Lin_SduPtr   Pointer to pointer to a shadow
 *             buffer or memory mapped eSCI Hardware
 *             receive buffer where the current data is
 *             stored.
 *
 * @remarks Covers       LIN_CUSTOM002
 */
FUNC(void, LIN_CODE) Msc_Polling(CONST(uint8, LIN_CONST) Channel)
{
    VAR(uint8, AUTOMATIC) Lin_ESCI;

    /* Check for invalid channel */
    if (Channel >= LIN_HW_MAX_MODULES) /* Invalid channel */
    {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_POLLING_ID,\
                            (uint8)LIN_E_INVALID_CHANNEL);
        #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if ((Lin_Channel_Cfg_Ptr[Channel]->MscPollingMode == (uint8)STD_ON) && \
            (Lin_Channel_Cfg_Ptr[Channel]->MscEnabled == (uint8)STD_ON))
        {

            /* Get the hardware Lin channel from logical channel */
            Lin_ESCI = Lin_Channel_Cfg_Ptr[Channel]->LinChannelID;

            /* If something was received and there are no errors */
            if((ESCI_LLM_IFSR1_IS_RX_DATA_REG_FULL(Lin_ESCI)) && \
                !(ESCI_LLM_SDR_ERROR_FLAG_READ(Lin_ESCI)))
            {
                /* Update MSC channel frame operation status to MSC_RUN */
                MscBuffer[Channel].State = MSC_RUN;

                /* No errors occurred on RX. */
                MscBuffer[Channel].Errors = 0U;

                /* Read data from Data Register and store into the addressed channel's MscBuffer */
                MscBuffer[Channel].Data = (uint8)ESCI_LLM_SDR_DATA_READ(Lin_ESCI);

                /* Which is the MSC frame format ? */
                if (Lin_Channel_Cfg_Ptr[Channel]->Msc_FrameFormat == MSC_16_BITS)
                {
                    /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains 4-bit address field and 8 data bits. */
                    /* LSB is received first. */
                    MscBuffer[Channel].Address = (uint8)ESCI_LLM_SDR_ADDRESS_READ(Lin_ESCI);
                }
                else
                {
                    /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains only 8 data bits. */
                    /* LSB is received first. */
                    MscBuffer[Channel].Address = 0U;
                }

                /* Clear Receive Data Register Full Interrupt Flag */
                ESCI_LLM_IFSR1_RX_DATA_REG_FULL_Clear(Lin_ESCI);
            }

            /* there is an error set the corresponding flag in the MSC buffer */
            else
            {
                /* An error occurred on RX: it can be an Overrun, Framing, Noise or Parity error. */
                MscBuffer[Channel].Errors = 1U;

                /* Check if OR Flag is set */
                if (ESCI_LLM_IFSR1_OVERRUN_FLAG_READ(Lin_ESCI))
                {
                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                    /* Overrun Error flag */
                    ESCI_LLM_IFSR1_OVERRUN_FLAG_Clear(Lin_ESCI);

                    MscBuffer[Channel].State = MSC_OVERRUN_ERROR;
                }

                /* Check if FE Flag is set */
                if (ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_READ(Lin_ESCI))
                {
                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                    /* Framing Error flag */
                    ESCI_LLM_IFSR1_FRAMING_ERROR_FLAG_Clear(Lin_ESCI);

                    MscBuffer[Channel].State = MSC_FRAMING_ERROR;
                }

                /* Check if NF Flag is set */
                if (ESCI_LLM_IFSR1_NOISE_FLAG_READ(Lin_ESCI))
                {
                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                    /* Noise Error flag */
                    ESCI_LLM_IFSR1_NOISE_FLAG_Clear(Lin_ESCI);

                    MscBuffer[Channel].State = MSC_NOISE_ERROR;
                }

                /* Check if PF Flag is set */
                if (ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_READ(Lin_ESCI))
                {
                    /* MISRA-C:2004 11.1, 11.3 VIOLATION: cast from unsigned long to pointer */
                    /* Parity Error flag */
                    ESCI_LLM_IFSR1_PARITY_ERROR_FLAG_Clear(Lin_ESCI);

                    MscBuffer[Channel].State = MSC_PARITY_ERROR;

                }

            }

        }

    }
    return;
}
#endif /* MSC_RX_POLLING_MODE */

#endif /* LIN_USE_MSC */

#define LIN_STOP_SEC_CODE
/**
 * @file Lin_NonASR.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_NONASR_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_NONASR_C_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
