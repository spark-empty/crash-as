/**
    @file    sample_app_mcal_data_definition.h
    @version 2.0.0

    @brief   AUTOSAR Sample_app - header file for the initialization task for platform reg file.
    @details .

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : 
    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

    ARVersion     : 1.9.0
    ARRevision    : ASR_REL_1_9_REV_0003
    ARConfVariant :
    SWVersion     : 2.0.0
    BuildVersion  : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.

    You can use this example for any purpose on any computer system with the following restrictions:
    1. This example is provided "as is", without warranty.
    2. You do not remove this copyright notice from this example or any direct derivation thereof.

*/
/*==================================================================================================
==================================================================================================*/

#ifndef SAMPLE_APP_MCAL_DATA_DEFINITION_H
#define SAMPLE_APP_MCAL_DATA_DEFINITION_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        modules.h
@brief Include Standard types & defines
*/

#include "typedefs.h"
#include "Std_Types.h"
#include "modules.h"
#include "sample_app_mcal_uart_console.h"

#if (USE_ADC_MODULE==STD_ON)
    #include "Adc.h"
#endif

#if (USE_CAN_MODULE==STD_ON)
    #include "Can.h"
    #include "CanIf.h"
    #include "CanIf_Cbk.h"
#endif
#include "Det.h"
#include "Dem.h"
#if (USE_DIO_MODULE==STD_ON)
    #include "Dio.h"
#endif
#include "EcuM.h"
#if (USE_FEE_MODULE==STD_ON)
    #include "Fee.h"
#endif
#if (USE_FLS_MODULE==STD_ON)
    #include "Fls.h"
#endif

#if (USE_FR_MODULE==STD_ON)
    #include "Fr.h"
#endif

#if (USE_GPT_MODULE==STD_ON)
    #include "Gpt.h"
#endif
#if (USE_ICU_MODULE==STD_ON)
    #include "Icu.h"
#endif
#if (USE_LIN_MODULE==STD_ON)
    #include "Lin.h"
    #include "LinIf_Cbk.h"
#endif
#if (USE_MCU_MODULE==STD_ON)
    #include "Mcu.h"
#endif
#include "SchM_Adc.h"
#include "SchM_Can.h"
#include "SchM_Dio.h"
#include "SchM_Fls.h"
#include "SchM_Gpt.h"
#include "SchM_Icu.h"
#include "SchM_Mcu.h"
#include "SchM_Port.h"
#include "SchM_RamTst.h"
#include "SchM_Spi.h"
#include "SchM_Wdg.h"
#if (USE_PORT_MODULE==STD_ON)
    #include "Port.h"
#endif
#if (USE_PWM_MODULE==STD_ON)
    #include "Pwm.h"
#endif
#if (USE_SPI_MODULE==STD_ON)
    #include "Spi.h"
#endif
#if (USE_WDG_MODULE==STD_ON)
    #include "Wdg.h"
    #include "WdgIf_Types.h"
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/**
@{
@brief Parameters that shall be published within the modules header file.
       The integration of incompatible files shall be avoided.
@remarks Covers
@remarks Implements
*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* State machine constants*/
/* CAN state machine */
#define CAN_INITIAL_STATE               10
#define CAN_ERROR_STATE                 20
#define CAN_INITIALIZED_STATE           30
#define CAN_TRANSMIT_STATE              40
#define CAN_RECEIVE_STATE               50
#define CAN_FINAL_STATE                 60
#define CAN_STALLED_STATE               70

/* FLEXRAY state machine */
#define FLEXRAY_INITIAL_STATE           10
#define FLEXRAY_ERROR_STATE             20
#define FLEXRAY_INITIALIZED_STATE       30
#define FLEXRAY_POCCONFIG_STATE         40
#define FLEXRAY_CONTROLLER_INIT_STATE   50
#define FLEXRAY_POCREADY_STATE          60
#define FLEXRAY_COLDSTART_INIT_STATE    70
#define FLEXRAY_POCSTARTUP_STATE        80
#define FLEXRAY_FINAL_STATE             90

/* LIN state machine */
#define LIN_INITIAL_STATE               10
#define LIN_ERROR_STATE                 20
#define LIN_OPERATIONAL_STATE           30
#define LIN_TRANSMIT_STATE              40
#define LIN_TX_PENDING_STATE            50
#define LIN_FINAL_STATE                 60
#define LIN_STALLED_STATE               70
#define LIN_SLEEP_STATE                 80
#define LIN_WAKEUP_STATE                90

/* SPI state machine */
#define SPI_INITIAL_STATE               10
#define SPI_ERROR_STATE                 20
#define SPI_INITIALIZED_STATE           30
#define SPI_TRANSMIT_STATE              40
#define SPI_TX_PENDING_STATE            50
#define SPI_FINAL_STATE                 60
#define SPI_STALLED_STATE               70

/* ADC state machine*/
#define ADC_INITIAL_STATE               0x10U
#define ADC_ERROR_STATE                 0x20U
#define ADC_INITIALIZED_STATE           0x30U
#define ADC_CONVERT_PENDING_STATE       0x40U
#define ADC_FINISH_CONVERT_STATE        0x50U
#define ADC_COMPLETE_STATE              0x60U


/* PWM state machine*/
#define PWM_INITIAL_STATE               0x11U
#define PWM_ERROR_STATE                 0x21U
#define PWM_INITIALIZED_STATE           0x31U
#define PWM_RUNNING_STATE               0x41U
#define PWM_COMPLETE_STATE              0x51U

/* ICU state machine*/

#define ICU_INITIAL_STATE               0x12U
#define ICU_ERROR_STATE                 0x22U
#define ICU_RUNNING_STATE               0x32U
#define ICU_FINISHED_MEASUREMENT_STATE  0x42U
#define ICU_COMPLETE_STATE              0x52U


/* FEE state machine */
#define FEE_INITIAL_STATE               10
#define FEE_ERROR_STATE                 20
#define FEE_ERASE_STATE                 30
#define FEE_ERASE_BUSY_STATE            40
#define FEE_WRITE_STATE                 50
#define FEE_WRITE_BUSY_STATE            60
#define FEE_READ_STATE                  70
#define FEE_READ_BUSY_STATE             80
#define FEE_READ_ERROR_STATE            90
#define FEE_VALIDATE_STATE              100
#define FEE_FINAL_STATE                 110
/* Other constants*/

#define GPT_TIMER_LED_TICKS             40000000UL

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

#if (USE_SPI_MODULE==STD_ON)
/* Spi specific structures */
typedef struct
{
    uint8 ucState; /*State machine state */
    uint8 bFlags; /* various application specific flags */
    uint32 ulTimeout;
    Spi_ConfigType * pSpiDriverConfig; /* pointer to the PB configuration structure */
} SpiSpecificData_T;
#endif

#if (USE_CAN_MODULE==STD_ON)
/* Can specific structures */
typedef struct
{
    uint8 ucState; /* State machine state */
    uint8 bFlags; /* various application specific flags */
    VAR(uint8, CAN_VAR)  controller;
    uint8 Can_Tx_flag;
    uint8 Can_Rx_flag;
    PduIdType Can_TxConfirmation_CanTxPduId;
    uint8 Can_TxConfirmation;
    uint8 Can_RxIndication;
    VAR(uint8, CAN_VAR)   Can_RxData[8U];
    uint8 Can_RxHandle;
    Can_IdType Can_RxId;
    uint8 Can_RxDlc;
    uint32 ulTimeout;
    Can_PduType CanMessage;
    Can_ConfigType * pCanDriverConfig; /* pointer to the PB configuration structure */
} CanSpecificData_T;
#endif

#if (USE_FR_MODULE==STD_ON)
/* FlexRay specific structures*/
typedef struct
{
    uint8 ucState; /* State machine state */
    uint8 bFlags; /* various application specific flags */
    Fr_ConfigurationType *pFlexRay_Config;
    uint32 ulTimeout;
    Fr_POCStatusType POCStatus;/* POC state */
} FlexRaySpecificData_T;
#endif

#if (USE_LIN_MODULE==STD_ON)
/* Lin specific structures */
typedef struct
{
    uint8 ucState; /* State machine state */
    uint8 bFlags; /* various application specific flags */
    Lin_ConfigType *pLinDriverConfig;
    Lin_PduType tosend_header;
    uint32 ulSleepTimeout;
    uint32 ulGetStatusTimeout;
} LinSpecificData_T;
#endif

#if (USE_ADC_MODULE==STD_ON)
/* ADC specific structures */
typedef struct
{
    uint8 ucState;                      /* State machine state */
    uint16 usValueConverted;            /* Value read by adc */
    uint32 ulTimeout;                   /* Value of timeout*/
    uint16 usAdcMaxValueRes;             /* Adc resolution*/
    Adc_ConfigType  *pAdcDriverConfig;  /* Pointer to the PB configuration structure */
} AdcSpecificData_T;
#endif

#if (USE_PWM_MODULE==STD_ON)
/* PWM specific structures */
typedef struct
{
    uint8  ucState;                     /* State machine state */
    uint8  ucNoOfSamples;               /* Number of samples measured**/
    uint16 usDutyCycle;                 /* The duty cycle set up depending on Adc conversion*/
    Pwm_ConfigType  *pPwmDriverConfig;  /* Pointer to the PB configuration structure */
} PwmSpecificData_T;
#endif

#if (USE_ICU_MODULE==STD_ON)
/* ICU specific structures */
typedef struct
{
    uint8 ucState;                      /* State machine state */
    Icu_DutyCycleType IcuDuty;          /* sampled duty of the pwm signal */
    Icu_ConfigType  *pIcuDriverConfig;  /* Pointer to the PB configuration structure */
} IcuSpecificData_T;
#endif

#if (USE_FEE_MODULE==STD_ON)
/* Fee specific structures */
typedef struct
{
    uint8 ucState; /* State machine state */
    uint8 bFlags; /* various application specific flags */
    Fls_ConfigType * pFlsDriverConfig; /* pointer to the PB configuration structure of the Fee driver*/
} FeeSpecificData_T;
#endif

/* Sample app specific structures */
typedef struct
{
#if (USE_CAN_MODULE==STD_ON)
    CanSpecificData_T stCanData;
#endif
#if (USE_FR_MODULE==STD_ON)
    FlexRaySpecificData_T stFlexRayData;
#endif
#if (USE_LIN_MODULE==STD_ON)
    LinSpecificData_T stLinData;
#endif
#if (USE_SPI_MODULE==STD_ON)
    SpiSpecificData_T stSpiData;
#endif
#if (USE_FEE_MODULE==STD_ON)
    FeeSpecificData_T stFeeData;
#endif
#if (USE_ADC_MODULE==STD_ON)
    AdcSpecificData_T stAdcData;
#endif
#if (USE_PWM_MODULE==STD_ON)
    PwmSpecificData_T stPwmData;
#endif
#if (USE_ICU_MODULE==STD_ON)
    IcuSpecificData_T stIcuData;
#endif
}SampleAppData_T;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

extern volatile VAR(SampleAppData_T, AUTOMATIC) stSampleAppData;
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*********************************************************************
 *
 * Copyright:
 *  Freescale Semiconductor, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Freescale
 *  Semiconductor, Inc. This software is provided on an "AS IS"
 *  basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, Freescale
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH
 *  REGARD TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF)
 *  AND ANY ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Freescale Semiconductor assumes no responsibility for the
 *  maintenance and support of this software
 *
 ********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SAMPLE_APP_MCAL_DATA_DEFINITION_H */

