/**
   @file    Lin_NonASR.h
   @version 2.0.0

   @brief   AUTOSAR Lin - Lin module NonAutosar API header.
   @details Lin NonAutosar APIs and defines

   Project AUTOSAR 3.0 MCAL
   Platform PA
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
 * @section LIN_NONASR_H_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 *
 * @section LIN_NONASR_H_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 */

#ifndef LIN_NONASR_H
#define LIN_NONASR_H

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
/** @remarks Covers LIN062 */
#define LIN_VENDOR_ID_NONASR_H            43
#define LIN_MODULE_ID_NONASR_H            82
#define LIN_AR_MAJOR_VERSION_NONASR_H     3
#define LIN_AR_MINOR_VERSION_NONASR_H     0
#define LIN_AR_PATCH_VERSION_NONASR_H     0
#define LIN_SW_MAJOR_VERSION_NONASR_H     2
#define LIN_SW_MINOR_VERSION_NONASR_H     0
#define LIN_SW_PATCH_VERSION_NONASR_H     0


/*=================================================================================================
                    FILE VERSION CHECKS
=================================================================================================*/

/** @remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and LIN configuration header file are of the same Autosar version */
  #if ((LIN_AR_MAJOR_VERSION_NONASR_H != LIN_AR_MAJOR_VERSION_CFG_H) || \
       (LIN_AR_MINOR_VERSION_NONASR_H != LIN_AR_MINOR_VERSION_CFG_H) || \
       (LIN_AR_PATCH_VERSION_NONASR_H != LIN_AR_PATCH_VERSION_CFG_H))
    #error "AutoSar Version Numbers of Lin_NonASR.h and Lin_Cfg.h are different"
  #endif
#endif

/* Check if source file and LIN configuration header file are of the same software version */
#if ((LIN_SW_MAJOR_VERSION_NONASR_H != LIN_SW_MAJOR_VERSION_CFG_H) || \
     (LIN_SW_MINOR_VERSION_NONASR_H != LIN_SW_MINOR_VERSION_CFG_H))
  #error "Software Version Numbers of Lin_NonASR.h and Lin_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_NONASR_H != COMSTACKTYPE_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_NONASR_H != COMSTACKTYPE_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_NONASR_H != COMSTACKTYPE_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Lin_NonASR.h and ComStack_Types.h are different"
  #endif
#endif

/*=================================================================================================
                       CONSTANTS
=================================================================================================*/

/*=================================================================================================
                     DEFINES AND MACROS
=================================================================================================*/

/*=================================================================================================
                       ENUMS
=================================================================================================*/
#if (LIN_DUAL_CLOCK_MODE == STD_ON)
/**
 * @brief Clock modes.
 */
typedef enum
    {
    LIN_NORMAL     =   (uint8)0x01U, /**< @brief
                                               LIN_NORMAL mode.*/
    LIN_ALTERNATE  =   (uint8)0x02U  /**< @brief
                                               LIN_ALTERNATE mode.*/
    } Lin_ClockModes;

#endif /* #if LIN_DUAL_CLOCK_MODE == STD_ON */

#ifdef LIN_USE_MSC

/*!
 * @brief MSC channel frame operation status, as returned by the
 *        API service Msc_GetStatus().
 */
typedef enum
    {
    MSC_IDLE = 0,      /**< @brief Receiver is disabled and no
                                   reception is running.*/
    MSC_READY,         /**< @brief Receiver is enabled and no
                                   reception is running.*/
    MSC_RUN,           /**< @brief Receiver is enabled and
                                   reception is running.*/
    MSC_WAKEUP,        /**< @brief Receiver is in wakeup mode.*/
    MSC_OVERRUN_ERROR, /**< @brief Erroneous reception due to
                                   an OR error.*/
    MSC_FRAMING_ERROR, /**< @brief Erroneous reception due to
                                   a FE error.*/
    MSC_PARITY_ERROR,  /**< @brief Erroneous reception due to
                                   a PE error.*/
    MSC_NOISE_ERROR    /**< @brief Erroneous reception due to
                                   an NF error.*/
    } Msc_StatusType;

/*!
 * @brief This type is used to provide Address, data, and any possible
 *        errors from the MSC driver to the application.
 */
typedef struct
    {
    uint8 Data;     /**< @brief Payload of the upstream MSC frame.*/
    uint8 Address;  /**< @brief address of the receive data buffer.*/
    uint8 Errors;   /**< @brief upstream MSC frame error type.*/
    Msc_StatusType  State;   /**< @brief upstream MSC channel state.*/
    } MSC_DataType;

#endif    /* #ifdef LIN_USE_MSC */

/*==================================================================================================
                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/
#if (LIN_DUAL_CLOCK_MODE == STD_ON)
    extern VAR(Lin_ClockModes,LIN_VAR)LinClock;
#endif    /* #if LIN_DUAL_CLOCK_MODE == STD_ON */
#ifdef LIN_USE_MSC
  #ifdef LIN_USE_DMA
    volatile extern VAR(MSC_DataType, LIN_VAR) MscBuffer[LIN_NUM_BYTES];
  #else
    volatile extern VAR(MSC_DataType, LIN_VAR) MscBuffer[LIN_HW_MAX_MODULES];
  #endif

    extern VAR(sint8,LIN_VAR)Lin_ChannelHardwareMap[];
#endif    /* #ifdef LIN_USE_MSC */
/*=================================================================================================
                                     FUNCTION PROTOTYPES
=================================================================================================*/

#define LIN_START_SEC_CODE
#include "MemMap.h"


/** @remarks Covers PR-MCAL-3201 */
#if LIN_DUAL_CLOCK_MODE == STD_ON

  /**
  @brief   Lin_SetClockMode
  @details Switch the clock mode

  @param[in] ClockMode - New clock mode

  @remarks Covers       PR-MCAL-3201
  */

 extern FUNC (Std_ReturnType, LIN_CODE) Lin_SetClockMode(VAR(Lin_ClockModes, AUTOMATIC) ClockMode);

#endif

/** @remarks Covers PR-MCAL-3220 */
#ifdef LIN_USE_MSC

  /**
  @brief   Msc_InitChannel
  @details Initialize Channel with MSC functionality.

  @param[in] Channel - MSC to be initialized.
  @param[in] Config  - Pointer to LIN channel configuration set.

  @remarks Covers       PR-MCAL-3220
  */

 extern FUNC(void, LIN_CODE) Msc_InitChannel(CONST(uint8, LIN_CONST)Channel,\
                  P2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_CONST)Config);

  /**
  @brief   Msc_DeInitChannel
  @details De-Inits a channel with MSC functionality.

  @param[in] Channel - MSC to be de-initialized.

  @remarks Covers       PR-MCAL-3220
  */

 extern FUNC (void, LIN_CODE) Msc_DeInitChannel(CONST(uint8, LIN_CONST)Channel);

  /**
  @brief   Msc_GetStatus
  @details Gets the status of the Channel with MSC functionality.

  @param[in] Channel - MSC to be initialized.

  @param[out] Lin_SduPtr   Pointer to pointer to a shadow
                           buffer or memory mapped eSCI Hardware
                           receive buffer where the current data is
                           stored.
  @return Msc_StatusType   The MSC channel status.
  - MSC_IDLE            Receiver is disabled and no
                        reception is running.
  - MSC_READY           Receiver is enabled and no
                        reception is running.
  - MSC_RUN             Receiver is enabled and
                        reception is running.
  - MSC_WAKEUP          Receiver is in wakeup mode.
  - MSC_OVERRUN_ERROR   Erroneous reception due to
                        an OR error.
  - MSC_FRAMING_ERROR   Erroneous reception due to
                        a FE error.
  - MSC_PARITY_ERROR    Erroneous reception due to
                        a PE error.
  - MSC_NOISE_ERROR     Erroneous reception due to
                        an NF error.

  @remarks Covers       PR-MCAL-3220
  */

 extern FUNC(Msc_StatusType, LIN_CODE) Msc_GetStatus(CONST(uint8, LIN_CONST) Channel);

  /**
  @brief   Msc_Polling
  @details Tests the RDRF flag to know if something was received by
           the channel with MSC functionality and in that case fill the
           buffer with the received data.

  @param[in] Channel - MSC to be initialized.

  @param[out] Lin_SduPtr   Pointer to pointer to a shadow
                           buffer or memory mapped eSCI Hardware
                           receive buffer where the current data is
                           stored.

  @remarks Covers       PR-MCAL-3220
  */

 extern FUNC (void, LIN_CODE) Msc_Polling(CONST(uint8, LIN_CONST) Channel);

#endif


#define LIN_STOP_SEC_CODE
/**
 * @file Lin_NonASR.h
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_NONASR_H_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_NONASR_H_REF_2
 */
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* LIN_NONASR_H */

/* End of File */

/** @}*/
