/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    EQADC_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Adc - low level driver source file.
    @details This is the low level driver source file, mainly implemented for the EQADC hardware IP.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral ADC_10B
    Dependencies none

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

@section EQADC_LLD_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'.
The usage of the MemMap.h file violates this rule, but this mechanism is used to properly place into
their sections the code and variables.

@section EQADC_LLD_c_REF_2
Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are different kinds
of execution code section.

@section EQADC_LLD_c_REF_3
Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer. This macro compute the
address of any register by using the hardware ofsset of the controller. The address calculated as an
unsigned int is passed to a amcro for initializing the pointer with that address.

@section EQADC_LLD_c_REF_4
Violates MISRA 2004 Advisory Rule 14.7, return statement before end of function. The return
statement are used to simplify the code structure and easier readability.

@section EQADC_LLD_c_REF_5
Violates MISRA 2004 Advisory Rule 11.4, cast from pointer to pointer. This is used for the Speed
optimization of the memory access.

@section EQADC_LLD_c_REF_6
Violates MISRA 2004 Advisory Rule 14.2, expected void type, assignment, increment or decrement.
This is used to read an unused value from an ADC register.

@section EQADC_LLD_c_REF_7
Violates MISRA 2004 Advisory Rule 17.4, expected another indexing, but used due to the code
complexity.

@section EQADC_LLD_c_REF_8
Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable, but is necessary to
to calculate the result with a function in order to reduce code complexity and readability.

@section EQADC_LLD_c_REF_9
Violates MISRA 2004 Advisory Rule 10.3, cast of complex expression changes signedness, because the
value of a complex expression of integer type shall only be cast to a type of the same sighedness
that is no wider than the underlying type of the expression.
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
#include "Adc.h"
#include "SchM_Adc.h"
#include "EQADC_LLD.h"
#include "Dma_LLD.h"
#include "Siu_Adc_LLD.h"
#include "Dem.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00318
*/
#define EQADC_AR_VENDOR_ID_LLD_C      43
#define EQADC_AR_MAJOR_VERSION_LLD_C  3
#define EQADC_AR_MINOR_VERSION_LLD_C  0
#define EQADC_AR_PATCH_VERSION_LLD_C  0
#define EQADC_SW_MAJOR_VERSION_LLD_C  2
#define EQADC_SW_MINOR_VERSION_LLD_C  0
#define EQADC_SW_PATCH_VERSION_LLD_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Adc header file are from the same vendor */
#if (EQADC_AR_VENDOR_ID_LLD_C != ADC_VENDOR_ID)
    #error "EQADC_LLD.c and Adc.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Adc header file are of the same Autosar version */
    #if ((EQADC_AR_MAJOR_VERSION_LLD_C != ADC_AR_MAJOR_VERSION) || \
         (EQADC_AR_MINOR_VERSION_LLD_C != ADC_AR_MINOR_VERSION) || \
         (EQADC_AR_PATCH_VERSION_LLD_C != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of EQADC_LLD.c and Adc.h are different"
    #endif
#endif
/* Check if source file and Adc header file are of the same Software version */
#if ((EQADC_SW_MAJOR_VERSION_LLD_C != ADC_SW_MAJOR_VERSION) || \
     (EQADC_SW_MINOR_VERSION_LLD_C != ADC_SW_MINOR_VERSION) || \
     (EQADC_SW_PATCH_VERSION_LLD_C != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of EQADC_LLD.c and Adc.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((EQADC_AR_MAJOR_VERSION_LLD_C != SCHM_ADC_AR_MAJOR_VERSION) || \
         (EQADC_AR_MINOR_VERSION_LLD_C != SCHM_ADC_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of EQADC_LLD.c and SchM_Adc.h are different"
    #endif
#endif

/* Check if source file and EQADC_LLD header file are from the same vendor */
#if (EQADC_AR_VENDOR_ID_LLD_C != EQADC_VENDOR_ID_LLD)
    #error "EQADC_LLD.c and EQADC_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and EQADC_LLD header file are of the same Autosar version */
    #if ((EQADC_AR_MAJOR_VERSION_LLD_C != EQADC_AR_MAJOR_VERSION_LLD) || \
         (EQADC_AR_MINOR_VERSION_LLD_C != EQADC_AR_MINOR_VERSION_LLD) || \
         (EQADC_AR_PATCH_VERSION_LLD_C != EQADC_AR_PATCH_VERSION_LLD))
        #error "AutoSar Version Numbers of EQADC_LLD.c and EQADC_LLD.h are different"
    #endif
#endif
/* Check if source file and EQADC_LLD header file are of the same Software version */
#if ((EQADC_SW_MAJOR_VERSION_LLD_C != EQADC_SW_MAJOR_VERSION_LLD) || \
     (EQADC_SW_MINOR_VERSION_LLD_C != EQADC_SW_MINOR_VERSION_LLD) || \
     (EQADC_SW_PATCH_VERSION_LLD_C != EQADC_SW_PATCH_VERSION_LLD))
    #error "Software Version Numbers of EQADC_LLD.c and EQADC_LLD.h are different"
#endif

/* Check if source file and DMA header file are from the same vendor */
#if (EQADC_AR_VENDOR_ID_LLD_C != DMA_VENDOR_ID)
    #error "EQADC_LLD.c and Dma_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DMA header file are of the same Autosar version */
    #if ((EQADC_AR_MAJOR_VERSION_LLD_C != DMA_AR_MAJOR_VERSION) || \
         (EQADC_AR_MINOR_VERSION_LLD_C != DMA_AR_MINOR_VERSION) || \
         (EQADC_AR_PATCH_VERSION_LLD_C != DMA_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of EQADC_LLD.c and Dma_LLD.h are different"
    #endif
#endif
/* Check if source file and DMA header file are of the same Software version */
#if ((EQADC_SW_MAJOR_VERSION_LLD_C != DMA_SW_MAJOR_VERSION) || \
     (EQADC_SW_MINOR_VERSION_LLD_C != DMA_SW_MINOR_VERSION) || \
     (EQADC_SW_PATCH_VERSION_LLD_C != DMA_SW_PATCH_VERSION))
    #error "Software Version Numbers of EQADC_LLD.c and Dma_LLD.h are different"
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

#ifdef ADC_DMA_SUPPORTED
STATIC FUNC (void, ADC_CODE) Adc_CopyQueueData2DMACommmandBuffer(VAR(Adc_HwUnitType, AUTOMATIC) unit);
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref EQADC_LLD_c_REF_1
*/
#define ADC_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

VAR(uint32,ADC_VAR) EQADC_DMACommandQueue[ADC_HW_MAX][ADC_MAX_GROUP_CHANNELS];
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref EQADC_LLD_c_REF_1
*/
#define ADC_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref EQADC_LLD_c_REF_1
*/
#define ADC_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

VAR(uint8,ADC_VAR) EQADC_CFIFOChannelCount[EQADC_MAX_UNITS][ADC_MAX_FIFO];
VAR(uint8,ADC_VAR) EQADC_RFIFOChannelCount[EQADC_MAX_UNITS][ADC_MAX_FIFO];
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref EQADC_LLD_c_REF_1
*/
#define ADC_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

STATIC CONST(uint8, ADC_CODE) EQADCA_Fifo_array[ADC_MAX_FIFO] =
{
    (uint8)ADC_EQADC_A_FIFO0_ENABLED, (uint8)ADC_EQADC_A_FIFO1_ENABLED, (uint8)ADC_EQADC_A_FIFO2_ENABLED, (uint8)ADC_EQADC_A_FIFO3_ENABLED, (uint8)ADC_EQADC_A_FIFO4_ENABLED, (uint8)ADC_EQADC_A_FIFO5_ENABLED
};

/* if Andorra2M and Andorra4M or Monaco 1.5M*/
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
#else
STATIC CONST(uint8, ADC_CODE) EQADCB_Fifo_array[ADC_MAX_FIFO] =
{
    (uint8)ADC_EQADC_B_FIFO0_ENABLED, (uint8)ADC_EQADC_B_FIFO1_ENABLED, (uint8)ADC_EQADC_B_FIFO2_ENABLED, (uint8)ADC_EQADC_B_FIFO3_ENABLED, (uint8)ADC_EQADC_B_FIFO4_ENABLED, (uint8)ADC_EQADC_B_FIFO5_ENABLED
};
#endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#if (STD_ON == ADC_CALIBRATION) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief  Adc_CalculateCalConst()  This routine calculates the EQADC gain and offset calibration constants
 *         (GCC and OCC) from the conversion results of 25%Vref and 75%Vref.
 *         The calibration constants are returned in a format defined by the ADC0/1
 *         Gain and Offset Calibration Constant Registers (ADC0/1_GCCR and
 *         ADC0/1_OCCR).
 *
 * @param[in] raw_result_25  - conversion result for 25%Vref.
 * @param[in] raw_result_75  - conversion result for 75%Vref.
 * @param[out] p_gcc - pointer to variable where the gain calibration.
 * param[out] p_occ - pointer to variable where offset calibration constant is returned.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC (void, ADC_CODE) Adc_CalculateCalConst(VAR(uint16, AUTOMATIC) raw_result_25,
            VAR(uint16, AUTOMATIC) raw_result_75, P2VAR(uint16, AUTOMATIC, ADC_APPL_DATA) p_gcc,
            P2VAR(sint16, AUTOMATIC, ADC_APPL_DATA) p_occ);
#endif /* ADC_CALIBRATION */

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/* put all ADC code into defined section */
#define ADC_START_SEC_CODE
/**
@file  EQADC_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref EQADC_LLD_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref EQADC_LLD_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#if (STD_ON == ADC_CALIBRATION) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief  Adc_CalculateCalConst()  This routine calculates the EQADC gain and offset calibration constants
 *         (GCC and OCC) from the conversion results of 25%Vref and 75%Vref.
 *         The calibration constants are returned in a format defined by the ADC0/1
 *         Gain and Offset Calibration Constant Registers (ADC0/1_GCCR and
 *         ADC0/1_OCCR).
 *
 * @param[in] raw_result_25  - conversion result for 25%Vref.
 * @param[in] raw_result_75  - conversion result for 75%Vref.
 * @param[out] p_gcc - pointer to variable where the gain calibration.
 * @param[out] p_occ - pointer to variable where offset calibration constant is returned.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC (void, ADC_CODE) Adc_CalculateCalConst(VAR(uint16, AUTOMATIC) raw_result_25,
            VAR(uint16, AUTOMATIC) raw_result_75, P2VAR(uint16, AUTOMATIC, ADC_APPL_DATA) p_gcc,
            P2VAR(sint16, AUTOMATIC, ADC_APPL_DATA) p_occ)
{
    VAR(uint32, AUTOMATIC) cal_gcc;
    cal_gcc = (uint32)((uint32)ADC_CAL_GCC / (uint32)((uint32)raw_result_75 - (uint32)raw_result_25));
    *p_gcc = (uint16) cal_gcc;
    /**
@note Violates MISRA 2004 Advisory Rule 10.3, cast of complex expression changes signedness
- See @ref EQADC_LLD_c_REF_9
    */
    /*lint -save -e961 */
    *p_occ = (sint16) (ADC_IDEAL_RES75 - ((cal_gcc * (uint32)raw_result_75) >> 14U));
    /*lint -restore */
}
#endif /* ADC_CALIBRATION */


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
 * @brief   This function initializes the ADC hardware module, and the ADC driver.
 *
 * @details This function initializes the ADC hardware module, and the ADC driver.
 *
 * @param[in]  CfgPtr - configuration data pointer.
 *
 * @remarks    Covers: ADC056, ADC077 and ADC307.
 * @remarks    Implements: DADC10000.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_Init
(
  P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) CfgPtr
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) unit=(Adc_HwUnitType)0U; /* HW unit index */
    #if (IPV_EQADC == IPV_EQADC_01_00_07_00)
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex=(Adc_HwUnitType)0; /* HW index in the hardware configuration structure */
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_07_00) */
    VAR(uint8, AUTOMATIC) eQADC_AorB=(uint8)0U; /* eQADC_AorB */
    VAR(uint8, AUTOMATIC) fifoindex=(uint8)0U; /* fifoindex */
    VAR(uint16, AUTOMATIC)q_index = (uint16)0U; /* Queue index */
    VAR(Adc_GroupType,AUTOMATIC)Group = (Adc_GroupType)0U; /* Group Index */
    VAR(uint32, AUTOMATIC) c_buffer;
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(uint8, AUTOMATIC) Temp;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    #if (STD_ON == ADC_CALIBRATION)
    VAR(uint16, AUTOMATIC) res25;
    VAR(uint16, AUTOMATIC) res75;
    VAR(uint16, AUTOMATIC) cal_gcc;
    VAR(sint16, AUTOMATIC) occ;
    #endif /* ADC_CALIBRATION */
    /* ADC056*/

    /* Initialize Group Status structures to beginning values */
    for(Group=0U; Group<CfgPtr->GroupCount; Group++)  /* GroupCount =  total number of groups  */
    {
        /* ADC307*/
        ADC_GroupStatus[Group].Conversion     = ADC_IDLE;
        ADC_GroupStatus[Group].AlreadyConverted = ADC_NOT_YET_CONVERTED; /* this group was not converted yet */
        ADC_GroupStatus[Group].ResultIndex    = 0U;
        #if (STD_ON == ADC_HW_TRIGGER_API)
        ADC_GroupStatus[Group].HwTriggering   = ADC_HWTRIGGER_DISABLED;
        #endif
        /* ADC077*/
        #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
        #endif
    }
    for(eQADC_AorB =0U; eQADC_AorB < EQADC_MAX; eQADC_AorB++)
    {
    for(fifoindex=0U; fifoindex < ADC_MAX_FIFO; fifoindex++)
    {
        if (eQADC_AorB == (uint8)ADC_EQADC_A)
        {
            if(EQADCA_Fifo_array[fifoindex] == (uint8)STD_ON)
            {
                EQADC_Disable_FIFO(eQADC_AorB, fifoindex);
                /* To clear RFDF flag */
                for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
                {
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                    /*lint -save -e961 */
                    if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                    {
                        break;
                    }
                    /*lint -restore */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                    /*lint -save -e961 */
                    tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
                    /*lint -restore */
                }
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                /*lint -save -e961 */
                REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
                /*lint -restore */
            }
        }
        /* if Andorra2M and Andorra4M or Monaco 1.5M */
        #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
        #else
        if (eQADC_AorB == (uint8)ADC_EQADC_B)
        {
            if(EQADCB_Fifo_array[fifoindex] == (uint8)STD_ON)
            {
                EQADC_Disable_FIFO(eQADC_AorB, fifoindex);
                /* To clear RFDF flag */
                for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
                {
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                    /*lint -save -e961 */
                    if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                    {
                        break;
                    }
                    /*lint -restore */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                    /*lint -save -e961 */
                    tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
                    /*lint -restore */
                }
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
                /*lint -save -e961 */
                REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
                /*lint -restore */
            }
        }
        #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
    }
    #if (STD_ON == ADC_HW_TRIGGER_API)
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
        /*lint -save -e961 */
        /* init EQADC_ETDFR - can only be written when the MODEn of all CFIFOs are configured to disabled */
        REG_WRITE32(EQADC_ETDFR(eQADC_AorB), Adc_Cfg_Ptr->EtriggerDigitalFilter);
        /*lint -restore */
    #endif
    }
    /* Initialize Unit Status structures */
    #if (ADC_MAX_HW_UNITS > 1U)
    for(unit = (Adc_HwUnitType)0; unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; unit++)
    #endif
    {
        /* Mark the HW unit as IDLE */
        ADC_UnitStatus[unit].Status       = ADC_IDLE;   /* Status of the HW unit */
        ADC_UnitStatus[unit].QueueIndex   = 0U;         /* Filled slots in the queue */
        /* Mark all the queue slots as "empty" */
        for(q_index = 0U; q_index < (uint16)Adc_Cfg_Ptr->Misc.ADC_QUEUE_MAX_DEPTH; q_index++)
        {
            ADC_UnitStatus[unit].Queue[q_index] = 0U;
        }
        #if (ADC_HW_TRIGGER_API == STD_ON)
        ADC_UnitStatus[unit].HwQueue[0] =0U;
        ADC_UnitStatus[unit].HwQueueIndex   = 0U;         /* Filled slots in the Hw queue */
        #endif
    }

    eQADC_AorB = (uint8)ADC_EQADC_A;
    for(unit = (Adc_HwUnitType)0; unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; unit++)
    {
        /* if Andorra2M and Andorra4M or Monaco 1.5M*/
        #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
        #else
        if(unit == 2U)
        {
            eQADC_AorB = (uint8)ADC_EQADC_B;
        }
        #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

        /* If HW unit is configured to use, enable it and update the calibration constants */
        if(ADC_HW_UNITS(unit) == (uint8)STD_ON)
        {
            #if (IPV_EQADC == IPV_EQADC_01_00_07_00)
            for(HwIndex = 0U; HwIndex < (Adc_HwUnitType)(Adc_Cfg_Ptr->Misc.ADC_MAX_HWCFG); HwIndex++)
            {
                /* Get the index of hardware unit in structure which will match with the hardware unit ID*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                /*lint -save -e960 */
                if(Adc_Cfg_Ptr->ADC[HwIndex].AdcHardwareUnitId == unit)
                /*lint -restore */
                {
                  break;
                }
            }
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_07_00) */
            /* if Andorra2M and Andorra4M or Monaco 1.5M*/
            #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
            /* If ADC0 of EQADC-A  */
            if(unit == 0U)
            {
            #else
            /* If ADC0 of EQADC-A/B  */
            if((unit % 2U) == 0U)
            {
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
                /* command buffer to be used is ZERO */
                c_buffer = ADC_CONV_COM_BN0;
                /* Get the 1st fifo that is configured for the hardware which is being used for the ADC calibration */
                for(Group=0U; Group<CfgPtr->GroupCount; Group++)
                {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                    /*lint -save -e960 */
                    if(ADC_GroupUnit(Group) == unit)
                    /*lint -restore */
                    {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                        /*lint -save -e960 */
                        fifoindex = (uint8)EQADC_GroupFifoIndex(Group);
                        /*lint -restore */
                        break;
                    }
                }
            }
            /* if Andorra2M and Andorra4M or Monaco 1.5M*/
            #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
            else /* ADC1 of EQADC-A */
            {
            #else
            else /* ADC1 of EQADC-A/B */
            {
            #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
                c_buffer = ADC_CONV_COM_BN1;
                /* Get the 1st fifo that is configured for the hardware which is being used for the ADC calibration */
                for(Group=0U; Group<CfgPtr->GroupCount; Group++)
                {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                    /*lint -save -e960 */
                    if(ADC_GroupUnit(Group) == unit)
                    /*lint -restore */
                    {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                        /*lint -save -e960 */
                        fifoindex = (uint8)EQADC_GroupFifoIndex(Group);
                        /*lint -restore */
                        break;
                    }
                }
            }
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
            /*lint -save -e961 */
            /* Enable the ADC unit 0 and set the Prescaler using CFIFOi, where i is confiured fifo */
            /* ADCn_EN=1, ADCn_EMUX=0, ADCn_CLK_PS=ADC[unit].Prescale */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            #if (IPV_EQADC == IPV_EQADC_01_00_07_00)
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | ADC_WRITE_CONFIG_EOQ | ((uint32)(Adc_Cfg_Ptr->ADC[HwIndex].AdcControlConfig) << 8U) | (uint32)ADC_CR));
            #else
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | ADC_WRITE_CONFIG_EOQ | ((uint32)(Adc_Cfg_Ptr->ADC[unit].AdcControlConfig) << 8U) | (uint32)ADC_CR));
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_07_00) */
            /*lint -restore */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref EQADC_LLD_c_REF_3
*/
            /*lint -save -e961 */
            /* Set SW SS mode and Start the Queue for the CFIFOi */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
            /*lint -restore */

            /* Wait for EOQ flag to be set */
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;
            while ((EQADC_FISRx_EOQF != (REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
            {
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            /* Disable the Queue and Clear the EOQ flag */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), EQADC_FISRx_EOQF);

            /* Configure the Alternate register ADC_ACR1 is used for 10BIT  and ADC_ACR2 is used for the 8BIT ADC channel's resolution for eQADC-A and eQADC_B  */
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (ADC_CONV_COM_BN0 | ADC_WRITE_CONFIG_EOQ | ((uint32)(ADC_ACR1_RESSEL_10BIT) << 8U) | (uint32)ADC_ACR1));
            /* Set SW SS mode and Start the Queue for the CFIFOi */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
            /* Wait for EOQ flag to be set */
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;
            while ((EQADC_FISRx_EOQF != (REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
            {
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            /* Disable the Queue and Clear the EOQ flag */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), EQADC_FISRx_EOQF);

            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (ADC_CONV_COM_BN0 | ADC_WRITE_CONFIG_EOQ | ((uint32)(ADC_ACR2_RESSEL_8BIT) << 8U) | (uint32)ADC_ACR2));
            /* Set SW SS mode and Start the Queue for the CFIFO0 */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
            /* Wait for EOQ flag to be set */
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;
            while ((EQADC_FISRx_EOQF != (REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
            {
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            /* Disable the Queue and Clear the EOQ flag */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), EQADC_FISRx_EOQF);

            #if (STD_ON == ADC_CALIBRATION)
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            #if (IPV_EQADC == IPV_EQADC_01_00_07_00)
            if (Adc_Cfg_Ptr->ADC[HwIndex].AdcCal == ADC_CAL_ON)
            #else
            if (Adc_Cfg_Ptr->ADC[unit].AdcCal == ADC_CAL_ON)
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_07_00) */
            /*lint -restore */
            {
                /* calibration: convert 25% and 75% VREF, compute calibration constants and write them into GCC and OCC registers */
                /* write command messages to sample 25% and 75% VREF */
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (RESULT_FIFO_OFFSET*fifoindex) | EQADC_COMMAND_CAL_CHANNEL25));
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (RESULT_FIFO_OFFSET*fifoindex) | EQADC_COMMAND_CAL_CHANNEL75));
                /* start conversion */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
                /* Reload counter */
                Timeout = ADC_TIMEOUT_COUNTER;
                while (((((REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR) >> 4U) < 2U) && (Timeout > (uint32)0U))
                {
                    Timeout--;
                }
                /** Test for FIFO's status failure. */
                if ( Timeout == (uint32)0U )
                {
                    /** Report production error and Return from function.  */
                    Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                }
                /* read results and compute calibration register values */
                res25 = (uint16) REG_READ32(EQADC_RFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U));
                res75 = (uint16) REG_READ32(EQADC_RFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U));
                /**
                @note  Violates MISRA 2004 Rule 1.2, Taking address of near auto variable  See @ref EQADC_LLD_c_REF_8
                */
                /*lint -save -e934 */
                Adc_CalculateCalConst(res25, res75, &cal_gcc, &occ);
                /*lint -restore */
                /* write command messages to write cal_gcc and occ calibration constants into */
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (((uint32)cal_gcc) << 8UL) | ADC_GCCR));
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | ((((uint32)occ) & ADC_OCC_REG) << 8UL) | ADC_CAL_CONST | ADC_OCCR));
                /* Reload counter */
                Timeout = ADC_TIMEOUT_COUNTER;
                /* wait until calibration constants are written to ADC */
                while ((EQADC_FISRx_EOQF != ((REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U))) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
                {
                    Timeout--;
                }
                /** Test for FIFO's status failure. */
                if ( Timeout == (uint32)0U )
                {
                    /** Report production error and Return from function.  */
                    Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                }
                /* disable CFIFO and clear flags */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
                REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));

                /* write command messages to write cal_gcc and occ calibration constants into ADC0/ADC1 Alternate Gain/Offset 1 Register */
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (((uint32)cal_gcc) << 8UL) | ADC_AG1R));
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | ((((uint32)occ) & ADC_OCC_REG) << 8UL) | ADC_CAL_CONST | ADC_AO1R));
                /* start conversion */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
                /* Reload counter */
                Timeout = ADC_TIMEOUT_COUNTER;
                /* wait until calibration constants are written to ADC */
                while ((EQADC_FISRx_EOQF != ((REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U))) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
                {
                    Timeout--;
                }
                /** Test for FIFO's status failure. */
                if ( Timeout == (uint32)0U )
                {
                    /** Report production error and Return from function.  */
                    Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                }

                /* disable CFIFO and clear flags */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
                REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));

                /* write command messages to write cal_gcc and occ calibration constants into ADC0/ADC1 Alternate Gain/Offset 2 Register */
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (((uint32)cal_gcc) << 8UL) | ADC_AG2R));
                REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | ((((uint32)occ) & ADC_OCC_REG) << 8UL) | ADC_CAL_CONST | ADC_AO2R));
                /* start conversion */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
                /* Reload counter */
                Timeout = ADC_TIMEOUT_COUNTER;
                /* wait until calibration constants are written to ADC */
                while ((EQADC_FISRx_EOQF != ((REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U))) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
                {
                    Timeout--;
                }
                /** Test for FIFO's status failure. */
                if ( Timeout == (uint32)0U )
                {
                    /** Report production error and Return from function.  */
                    Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                }
                /* disable CFIFO and clear flags */
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
                REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
            }
            #endif /* ADC_CALIBRATION */
        }
    }
} /* EQADC_LLD_Init */

#if (STD_ON == ADC_DEINIT_API) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function deinitializes the ADC driver, and the ADC hardware.
 *
 * @details This function deinitializes the ADC driver, and ensures that the ADC hardware will be in
 *          the power on after reset state.
 *
 * @remarks    Covers: ADC110, ADC111, ADC228, ADC366, ADC413.
 * @remarks    Implements: DADC10001.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_DeInit(void)
{
    VAR(uint8, AUTOMATIC) eQADC_AorB=(uint8)0U; /* eQADC_AorB */
    VAR(Adc_HwUnitType, AUTOMATIC) unit=(Adc_HwUnitType)0U; /* HW unit index */
    VAR(Adc_GroupType, AUTOMATIC) Group;    /* Group Index */
    VAR(uint8, AUTOMATIC) fifoindex=(uint8)0U; /* fifoindex */
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(uint8, AUTOMATIC) Temp;
    VAR(uint32, AUTOMATIC) c_buffer;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    /* enter critical region to avoid ISRs during register reset */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_06);

    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    /* Disable all the EQADC_A FIFO's */
    #else
    /* Disable all the EQADC_A and EQADC_B FIFO's */
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

    for(eQADC_AorB=0U; eQADC_AorB < EQADC_MAX; eQADC_AorB++)
    {
    /* ADC111-- ADC110*/
        for(fifoindex=0U; fifoindex < ADC_MAX_FIFO; fifoindex++)
        {
            if (eQADC_AorB == (uint8)ADC_EQADC_A)
            {
                if(EQADCA_Fifo_array[fifoindex] == (uint8)STD_ON)
                {
                    EQADC_Disable_FIFO((uint8)ADC_EQADC_A, (uint8)fifoindex);
                    /*    To clear RFDF flag    */
                    for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
                    {
                        if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                        {
                            break;
                        }
                        tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
                    }
                    REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
                }
            }
            /* if Andorra2M and Andorra4M or Monaco 1.5M */
            #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
            #else
            if (eQADC_AorB == (uint8)ADC_EQADC_B)
            {
                if(EQADCB_Fifo_array[fifoindex] == (uint8)STD_ON)
                {
                    EQADC_Disable_FIFO((uint8)ADC_EQADC_B, fifoindex);
                    /* To clear RFDF flag */
                    for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
                    {
                        if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                        {
                            break;
                        }
                        tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
                    }
                    REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
                }
            }
            #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
        }
    } /* for(eQADC_AorB =0; eQADC_AorB < EQADC_MAX; eQADC_AorB++)  */

    eQADC_AorB = (uint8)ADC_EQADC_A;
    for(unit = (Adc_HwUnitType)0; unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; unit++)
    {
        /* if Andorra2M and Andorra4M or Monaco 1.5M */
        #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
        #else
        if(unit == 2U)
        {
            eQADC_AorB = (uint8)ADC_EQADC_B;
        }
        #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

        /* If HW unit is configured to use, enable it and update the calibration constants */
        if(ADC_HW_UNITS(unit) == (uint8)STD_ON)
        {
            /* if Andorra2M and Andorra4M or Monaco 1.5M */
            #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
            /* If ADC0 of EQADC-A  */
            if(unit == 0U)
            {
            #else
            /* If ADC0 of EQADC-A/B  */
            if((unit % 2U) == 0U)
            {
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
                /* command buffer to be used is ZERO */
                c_buffer = ADC_CONV_COM_BN0;
                /* Get the 1st fifo that is configured for in the hardware*/
                for(Group=0U; Group<Adc_Cfg_Ptr->GroupCount; Group++)
                {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                    /*lint -save -e960 */
                    if(ADC_GroupUnit(Group) == unit)
                    /*lint -restore */
                    {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                        /*lint -save -e960 */
                        fifoindex = (uint8)EQADC_GroupFifoIndex(Group);
                        /*lint -restore */
                        break;
                    }
                }
            }
            /* if Andorra2M and Andorra4M or Monaco 1.5M */
            #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
            else /* ADC1 of EQADC-A */
            {
            #else
            else /* ADC1 of EQADC-A/B */
            {
            #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
                c_buffer = ADC_CONV_COM_BN1;
                /* Get the 1st fifo that is configured for in the hardware*/
                for(Group=0U; Group<Adc_Cfg_Ptr->GroupCount; Group++)
                {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                    /*lint -save -e960 */
                    if(ADC_GroupUnit(Group) == unit)
                    /*lint -restore */
                    {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                        /*lint -save -e960 */
                        fifoindex = (uint8)EQADC_GroupFifoIndex(Group);
                        /*lint -restore */
                        break;
                    }
                }
            }

            REG_WRITE32(EQADC_MCR(eQADC_AorB), EQADC_REG32_RESET_VALUE);
            REG_WRITE32(EQADC_ETDFR(eQADC_AorB), EQADC_REG32_RESET_VALUE);

            /* write command messages with reset default values of registers
             ADCn_CR, ADCn_GCCR and ADCn_OCCR */
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (((uint32) ADC_CFPR0_GCCR) << 8UL) | ADC_GCCR));
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (c_buffer | (0x0U) | ADC_OCCR));
            REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (ADC_WRITE_CONFIG_EOQ | c_buffer | ((((uint32) ADC_ADCn_CLK_PS_31)) << 8UL) |(uint32) ADC_CR));
            /* start CFIFO and wait until it is completed (EOQ flag set) */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;
            /* wait until calibration constants are written to ADC */
            while ((EQADC_FISRx_EOQF != (REG_READ32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U))) & EQADC_FISRx_EOQF)) && (Timeout > (uint32)0U))
            {
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            /* disable CFIFO and clear flags */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
        }
    }/* for(unit = (Adc_HwUnitType)0; unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; unit++) */
    #if (STD_ON == ADC_HW_TRIGGER_API)
        /* set SIU_ISEL(4-7) default reset value */
        SIU_LLD_ResetAllHwTrigger();
    #endif /* ADC_HW_TRIGGER_API */
    /* exit critical region */
    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_06);

    /* Undefine the global pointer to the configuration */
    Adc_Cfg_Ptr = NULL_PTR;
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    for(Group=(uint8)0U;Group<(uint8)ADC_MAX_GROUPS;Group++)
    {
        /* ADC 111*/
        ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
    }
    #endif
}
#endif /* #if (STD_ON == ADC_DEINIT_API) */

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function starts the group conversion.
 *
 * @details This function starts the group conversion.
 *
 * @param[in]  Group - the group of which conversion will be started.
 * @param[in]  unit  - the hardware unit. (on other platforms there are more hw units)
 *
 * @remarks    Covers: ADC061, ADC156, ADC259, ADC311, ADC332, ADC333, ADC340, ADC417.
 * @remarks    Implements: DADC10002.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_StartGroupConversion
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    VAR(Adc_GroupPriorityType, AUTOMATIC) gPri = (Adc_GroupPriorityType)0U; /* Priority of the requested Group */
    VAR(Adc_QueueIndexType, AUTOMATIC) pTem = (Adc_QueueIndexType)0U; /* Temporary index in the Queue */
    VAR(uint32, AUTOMATIC) eQADC_AorB;
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
    VAR(uint8, AUTOMATIC) Temp;
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(Adc_QueueIndexType, AUTOMATIC) pos = 0U; /* Position of the new Group in the Queue */
    VAR(volatile uint16, AUTOMATIC) ADCConversionTimeCounter;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    #endif
    #if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) qPtr = (Adc_QueueIndexType)0U; /* First available slot in the Queue */
    #endif

    /* enter critical region to work on queue, DMA, ADC registers */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_07);

    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) /* ADC311 -- ADC340 -- ADC332 -- ADC417*/
    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    eQADC_AorB = (uint8)ADC_EQADC_A;
    #else
    if(unit < ADC_UNIT_2)
    {
        eQADC_AorB = (uint8)ADC_EQADC_A;
    }
    else
    {
        eQADC_AorB = (uint8)ADC_EQADC_B;
    }
    #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
    #endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

    /* Mark the Group as BUSY when the Group goes to the Queue or gets started */
    ADC_GroupStatus[Group].Conversion = ADC_BUSY;
    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) /* ADC311 -- ADC340 -- ADC332 -- ADC417*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    gPri = EQADC_GroupPriority(Group);
    /*lint -restore */
    qPtr = ADC_UnitStatus[unit].QueueIndex;

    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Queue is NOT Empty */
        /* Find the right place in Queue */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        while((pos < qPtr) && (EQADC_GroupPriority(ADC_GroupInQueue(unit, pos)) >= gPri))
        /*lint -restore */
        {
          pos++;
        }

        if(pos==0U)
        {
            #ifdef ADC_DMA_SUPPORTED
            /* Abort the ongoing group conversion */
            if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA)
            {
                /* if Andorra2M and Andorra4M or Monaco 1.5M */
                #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
                /* Disable EQADC_A DMA interrupt */
                Dma_disable_interrupt((uint8)(fifoindex*2U));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + 1U));
                #else
                /* Disable EQADC_AorB DMA interrupt */
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
                #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
            } /* if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA) */
            #endif /* ADC_DMA_SUPPORTED  */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            fifoindex = EQADC_GroupFifoIndex(ADC_GroupInQueue(unit, pos));
            /*lint -restore */
            /* Disable the used CFIFO  for this Group */
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_CFFE);
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_RFDE);
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;

            while ((((REG_READ32(EQADC_CFSR(eQADC_AorB))) & ((EQADC_CFSR_CFS0) >> (fifoindex * 2U))) != 0x00U)  && (Timeout > (uint32)0U))
            {
                /* Decrease counter */
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            EQADC_Disable_FIFO((uint8)eQADC_AorB, (uint8)fifoindex);
            /* Worst case conversion time is 128 clock cycles at 1 MHZ */
            /* Assuming 264MHz clock speed for processor and single cycle  */
            /* execution of decrement operation */
            ADCConversionTimeCounter = ADC_CONVERSION_TIMEOUT;
            while(ADCConversionTimeCounter!=0x00U)
            {
                ADCConversionTimeCounter--;
            }
            /*    To clear RFDF flag    */
            for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
            {
                if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                {
                    break;
                }
                tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
            }
            REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), EQADC_FISRx_RFDF);
        }
        /* Make space for the new Group */
        if(qPtr > pos)
        {
            for(pTem = qPtr; pTem > pos; pTem--)
            {
                ADC_UnitStatus[unit].Queue[pTem] = ((Adc_GroupType)ADC_UnitStatus[unit].Queue[pTem-(Adc_QueueIndexType)1U]);
            }
        }
        /* Place the Group in the Queue */
        ADC_UnitStatus[unit].Queue[pos] = Group;
        /* Increase the Queue Index */
        ADC_UnitStatus[unit].QueueIndex++;
    } /* end of qPtr > (Adc_QueueIndexType)0U */
    #else /* ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE */
    #if (ADC_ENABLE_QUEUING == STD_ON) /* ADC333*/
    qPtr = ADC_UnitStatus[unit].QueueIndex;
    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Place the Group in the Queue */
        ADC_UnitStatus[unit].Queue[qPtr] = Group;
        /* Increase the Queue Index */
        ADC_UnitStatus[unit].QueueIndex++;
    }
    #else /* ADC_ENABLE_QUEUING == STD_OFF*/
    /* In this case all the StartConversion should be rejected by DET*/
    #endif
    #endif

    #if (ADC_ENABLE_QUEUING == STD_ON)
    /* No_priorities OR Queue_is_empty */
    if((ADC_UnitStatus[unit].Queue[0] == Group)||(ADC_UnitStatus[unit].QueueIndex == (Adc_QueueIndexType)0U))
    {
    #endif
        /* Indicate a new group was added to the queue */
        if (ADC_UnitStatus[unit].QueueIndex == (Adc_QueueIndexType)0U)
        {
            /* Place the Group in the Queue */
            ADC_UnitStatus[unit].Queue[0] = Group;
            ADC_UnitStatus[unit].QueueIndex++;
        }
        /* exit critical region */
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_07);
        /* ADC061*/
        EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
    #if (ADC_ENABLE_QUEUING == STD_ON)
    }
    else
    {
        /* exit critical region */
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_07);
    }
    #endif
}

/*================================================================================================*/
/**
 * @brief This function stops the group conversion.
 *
 * @details This function stops the group conversion.
 *
 * @param[in]  Group - the group of which conversion will be stopped.
 * @param[in]  unit  - the hardware unit. (on other platforms there are more hw units)
 * @remarks    Covers: ADC155, ADC260, ADC360, ADC368, ADC385, ADC386
 * @remarks    Implements: DADC10003
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_StopGroupConversion
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
  #if (ADC_ENABLE_QUEUING == STD_ON)
  VAR(Adc_QueueIndexType, AUTOMATIC) queueIndex = (Adc_QueueIndexType)0;
  VAR(Adc_QueueIndexType, AUTOMATIC) removedPos = (Adc_QueueIndexType)0;
  #endif
  VAR(uint32, AUTOMATIC) eQADC_AorB;
  VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
  VAR(uint32, AUTOMATIC) Timeout;
  VAR(uint8, AUTOMATIC) Temp;
  VAR(volatile uint16, AUTOMATIC) ADCConversionTimeCounter;
  VAR(volatile uint32, AUTOMATIC) tempBuffer;

  /* enter critical region to protect against queue changes from ISRs */
  SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_08);
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
  /*lint -save -e960 */
  fifoindex = EQADC_GroupFifoIndex(Group);
  /*lint -restore */
  /* if Andorra2M and Andorra4M or Monaco 1.5M */
  #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
  eQADC_AorB = (uint8)ADC_EQADC_A;
  #else
  if(unit < (Adc_HwUnitType)ADC_UNIT_2)
  {
    eQADC_AorB = (uint8)ADC_EQADC_A;
  }
  else
  {
    eQADC_AorB = (uint8)ADC_EQADC_B;
  }
  #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
  /*lint -save -e960 */
  if((((Adc_Cfg_Ptr->Groups[Group].mode) == ADC_CONV_MODE_ONESHOT)||
    ((Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
    (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)))&&
    (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED))
  /*lint -restore */
  { /*Stream Completed*/
    /* group is stopped, change its status to IDLE  ADC360 -- ADC221*/
    ADC_GroupStatus[Group].Conversion = ADC_IDLE;
    ADC_UnitStatus[unit].Status = ADC_IDLE;
    /* FD reset number of samples completed */
    ADC_GroupStatus[Group].ResultIndex = 0U;
    #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
    /* disable group notification (ADC155) */
    ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
    #endif
    /* exit critical region */
    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_08);
  }
  else
  {
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Find the Group in the Queue */
    removedPos= ADC_UnitStatus[unit].QueueIndex;  /* initialize with something invalid */
    /* Find the Group in the Queue */
    queueIndex = ADC_UnitStatus[unit].QueueIndex - (Adc_QueueIndexType)1U; /* Last valid Group in the Queue */
    while (queueIndex < (Adc_QueueIndexType)Adc_QueueIndexType_MAXIMUM)
    {
      if ( Group == ADC_UnitStatus[unit].Queue[queueIndex] ) /* The group is found in the Queue */
      {
        /* store the position of the group to be removed */
        removedPos= queueIndex;
        /* ADC385 ADC386: Stop the conversion of all channels belonging to this group */
        if(queueIndex == (Adc_QueueIndexType)0U) /* In this case the group might be under conversion */
#endif
        {
            #ifdef ADC_DMA_SUPPORTED
            /* Interrupt disable to protect code section  */
            if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA)
            {
                /* if Andorra2M and Andorra4M or Monaco 1.5M */
                #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
                /* Disable EQADC_A DMA interrupt */
                Dma_disable_interrupt((uint8)(fifoindex*2U));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + 1U));
                #else
                /* Disable EQADC_AorB DMA interrupt */
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
                #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
            } /* if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA) */
            #endif
            /* Disable the used CFIFO  for this Group */
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_CFFE);
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_RFDE);
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;
            while ((((REG_READ32(EQADC_CFSR(eQADC_AorB))) & ((EQADC_CFSR_CFS0) >> (fifoindex * 2U))) != 0x00U)  && (Timeout > (uint32)0U))
            {
                /* Decrease counter */
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            EQADC_Disable_FIFO((uint8)eQADC_AorB, (uint8)fifoindex);
            /* Worst case conversion time is 128 clock cycles at 1 MHZ */
            /* Assuming 264MHz clock speed for processor and single cycle  */
            /* execution of decrement operation */
            ADCConversionTimeCounter = ADC_CONVERSION_TIMEOUT;
            while(ADCConversionTimeCounter!=0x00U)
            {
                ADCConversionTimeCounter--;
            }
            /*    To clear RFDF flag    */
            for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
            {
                if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                {
                    break;
                }
                tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
            }
            REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), EQADC_FISRx_RFDF);
            ADC_UnitStatus[unit].Status = ADC_IDLE;
        }
        /* FD reset number of samples completed */
        ADC_GroupStatus[Group].ResultIndex = 0U;
         /* group is stopped, change its status to IDLE  ADC360 -- ADC221*/
        ADC_GroupStatus[Group].Conversion = ADC_IDLE;
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* disable group notification (ADC155) */
        ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
        #endif
#if (ADC_ENABLE_QUEUING == STD_ON)
        /* remove group from Queue */
         /* ADC385--ADC386*/
         EQADC_RemoveFromQueue(unit, queueIndex);
         break;
      }
      queueIndex--;
    }/* End od While */
        /* Start the next qroup in the Queue (if any) */
        if((removedPos == (Adc_QueueIndexType)0U) && (ADC_UnitStatus[unit].QueueIndex > (Adc_QueueIndexType)0U))
        {
            /* exit critical region */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_08);
            /* Structures and pointers will be initialized when the next Group starts */
            EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
        }
        else
        {
            /* exit critical region */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_08);
        }
    #else
        /* no element will be present in the queue */
        ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;

        /* exit critical region */
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_08);
    #endif
  }
}
#endif /* #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_READ_GROUP_API == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief This function reads the converted data for the requested group.
 *
 * @details Reads the converted data for the requested group.
 *
 * @param[in]  Group   - The group number.
 * @param[out] DataPtr - Pointer to a buffer which will be filled by the conversion results.
 *
 * @return     Result of reading converted data.
 *             E_OK - in case of successfull read of the converted data.
 *             E_NOT_OK - in case of an ongoing conversion.
 *
 * @remarks    Covers: ADC075, ADC113, ADC122, ADC329, ADC330, ADC331, ADC359, ADC369, ADC383.
 * @remarks    Implements: DADC10004.
 *
 * @api
 */
/*================================================================================================*/
FUNC(Std_ReturnType, ADC_CODE) EQADC_LLD_ReadGroup
(
  CONST(Adc_GroupType, ADC_CONST) Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataPtr
)
{
  VAR(uint8, AUTOMATIC) count = (uint8)0U;
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) ResultPtr = NULL_PTR;
  VAR(uint32, AUTOMATIC) DestOffset = (uint32)0U;
  VAR(Adc_StreamNumSampleType, AUTOMATIC) ResultIndex = (Adc_StreamNumSampleType)0U;
  VAR(Std_ReturnType, AUTOMATIC) EQAdc_ReadGroupRet = (Std_ReturnType)E_OK;
  /* Enter critical region */
  SchM_Enter_Adc(SCHM_ADC_INSTANCE_0,ADC_EXCLUSIVE_AREA_09);
  if (ADC_GroupStatus[Group].Conversion == ADC_BUSY)
  {
    EQAdc_ReadGroupRet = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
  #if (ADC_READ_GROUP_OPTIMIZATION == STD_ON)
  /* if SetupResultbuffer() and Adc_ReadGroup() APIs are not called with the same buffer OR the number of group samples is NOT 1 */
  if (!((DataPtr ==(Adc_ValueGroupType *)Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group])&&(Adc_Cfg_Ptr->Groups[Group].NumSamples == (Adc_StreamNumSampleType)1)))
  {
      /* ADC140 Disable Interrupt Mask*/
      /* get index of last completed sample */
      if (ADC_GroupStatus[Group].ResultIndex == (Adc_StreamNumSampleType)0U)
      {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        ResultIndex = Adc_Cfg_Ptr->Groups[Group].NumSamples - (Adc_StreamNumSampleType)1U;
        /*lint -restore */
      }
      else
      {
        ResultIndex = ADC_GroupStatus[Group].ResultIndex - (Adc_StreamNumSampleType)1U;
      }
/**
@note  Violates MISRA 2004 Rule 11.4, cast from pointer to pointer - See @ref EQADC_LLD_c_REF_5
*/
      /*lint -save -e961 */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
      /*lint -save -e960 */
      ResultPtr = (Adc_ValueGroupType *)(Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] + ResultIndex);
      DestOffset = Adc_Cfg_Ptr->Groups[Group].NumSamples;

      /* ADC075 copy results of last conversion from streaming buffer to internal buffer */
      for(count = 0U; count < (Adc_Cfg_Ptr->Groups[Group].AssignedChannelCount); count++)
      {
        /* ADC113-- ADC122 -- ADC383*/
        DataPtr[count] = (*ResultPtr);
        ResultPtr += DestOffset;
      }
  }
  #else /* (ADC_READ_GROUP_OPTIMIZATION == STD_OFF) */
        /* ADC140 Disable Interrupt Mask*/
      /* get index of last completed sample */
      if (ADC_GroupStatus[Group].ResultIndex == (Adc_StreamNumSampleType)0U)
      {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        ResultIndex = Adc_Cfg_Ptr->Groups[Group].NumSamples - (Adc_StreamNumSampleType)1U;
        /*lint -restore */
      }
      else
      {
        ResultIndex = ADC_GroupStatus[Group].ResultIndex - (Adc_StreamNumSampleType)1U;
      }
/**
@note  Violates MISRA 2004 Rule 11.4, cast from pointer to pointer - See @ref EQADC_LLD_c_REF_5
*/
      /*lint -save -e961 */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
      /*lint -save -e960 */
      ResultPtr = (Adc_ValueGroupType *)(Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] + ResultIndex);
      DestOffset = Adc_Cfg_Ptr->Groups[Group].NumSamples;

      /* ADC075 copy results of last conversion from streaming buffer to internal buffer */
      for(count = 0U; count < (Adc_Cfg_Ptr->Groups[Group].AssignedChannelCount); count++)
      {
        /* ADC113-- ADC122 -- ADC383*/
        DataPtr[count] = (*ResultPtr);
        ResultPtr += DestOffset;
      }
  #endif /* #if (ADC_READ_GROUP_OPTIMIZATION == STD_ON) */

      /*lint -restore */
      /* The following code has been added to respect the State Diagram of Streaming Access Mode */
      if (ADC_GroupStatus[Group].Conversion == ADC_COMPLETED)
      {
        ADC_GroupStatus[Group].ResultIndex = 0U;

        /* ADC331 -- ADC222*/
        ADC_GroupStatus[Group].Conversion = ADC_BUSY;
      }

      /* Compliance with State Diagram */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
      /*lint -save -e960 */
      if (Adc_Cfg_Ptr->Groups[Group].TriggerSource  == ADC_TRIGG_SRC_SW)
      /*lint -restore */
      {
        if (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED)
        {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
          /*lint -save -e960 */
          if((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_ONESHOT)||
              ((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_CONTINUOUS)&&
              (Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
              (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)))
          /*lint -restore */
          {
            /* ADC330 - ADC221*/
            ADC_GroupStatus[Group].Conversion = ADC_IDLE;
          }
          else
          { /* Continuous*/
            /* ADC329 -- ADC222*/
            ADC_GroupStatus[Group].Conversion = ADC_BUSY;
          }
        }
      }
      #if (ADC_HW_TRIGGER_API == STD_ON)
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
      /*lint -save -e960 */
      else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource  == ADC_TRIGG_SRC_HW)
      /*lint -restore */
      { /* Hw Trigger*/
        if (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED)
        {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
          /*lint -save -e960 */
          if((Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
              (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR))
          /*lint -restore */
          {
            /* ADC330 - ADC221*/
            ADC_GroupStatus[Group].Conversion = ADC_IDLE;
          }
          else
          { /* Simple One-shot mode, in other words in single access mode*/
            /* ADC329 -- ADC222*/
            ADC_GroupStatus[Group].Conversion = ADC_BUSY;
          }
        }
      }
      else
      {
         /* Catastrophic Errors Recovery (CER) */
         Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U, (uint8)ADC_EQADC_LLD_READGROUP_ID,(uint8)ADC_CER_TRIG_SRC_TYPE);
      }
      #endif
  }
    /* Exit critical region */
    SchM_Exit_Adc(SCHM_ADC_INSTANCE_0,ADC_EXCLUSIVE_AREA_09);
    return(EQAdc_ReadGroupRet);
}
#endif /* #if (STD_ON == ADC_READ_GROUP_API) */

#if (STD_ON == ADC_HW_TRIGGER_API) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief This function enables the hardware triggers for the specified group.
 *
 * @details This function enables the hardware triggers for the specified group.
 *
 * @param[in]  Group - the group for which the hardware triggers will be enabled.
 * @param[in]  unit  - the hardware unit. (on other platforms there are more hw units)
 *
 * @remarks    Covers: ADC114, ADC144, ADC265, ADC311, ADC332, ADC333, ADC340, ADC417, ADC336, ADC370, ADC432.
 * @remarks    Implements: DADC10005.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_EnableHardwareTrigger
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    VAR(Adc_GroupPriorityType, AUTOMATIC) gPri = (Adc_GroupPriorityType)0U; /* Priority of the requested Group */
    VAR(Adc_QueueIndexType, AUTOMATIC) pTem = (Adc_QueueIndexType)0U; /* Temporary index in the Queue */
    VAR(uint32, AUTOMATIC) eQADC_AorB;
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
    VAR(uint8, AUTOMATIC) Temp;
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(Adc_QueueIndexType, AUTOMATIC) pos = 0U; /* Position of the new Group in the Queue */
    VAR(volatile uint16, AUTOMATIC) ADCConversionTimeCounter;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    #endif
    #if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) qPtr = (Adc_QueueIndexType)0U; /* First available slot in the Queue */
    #endif

    /* enter critical region to work on queue, DMA, ADC registers */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_10);
    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) /* ADC311 -- ADC340 -- ADC332 -- ADC417*/
    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    eQADC_AorB = (uint8)ADC_EQADC_A;
    #else
    if(unit < ADC_UNIT_2)
    {
        eQADC_AorB = (uint8)ADC_EQADC_A;
    }
    else
    {
        eQADC_AorB = (uint8)ADC_EQADC_B;
    }
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
    #endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

    /* Mark the Group as BUSY when the Group goes to the Queue or gets started */
    /* ADC222*/
    ADC_GroupStatus[Group].Conversion = ADC_BUSY;
    /* if HW trigger is enabled for a group, its HW trigger status becoms ENABLED */
    ADC_GroupStatus[Group].HwTriggering = ADC_HWTRIGGER_ENABLED;
    /* ADC432 */
    /* Put the conversion results from Results Buffer Base Address */
    ADC_GroupStatus[Group].ResultIndex = 0U;

    #if  (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) /* ADC311 -- ADC340 -- ADC332 -- ADC417*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    gPri = EQADC_GroupPriority(Group);
    /*lint -restore */
    qPtr = ADC_UnitStatus[unit].QueueIndex;

    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Queue is NOT Empty */
        /* Find the right place in Queue */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        while((pos < qPtr) && (EQADC_GroupPriority(ADC_GroupInQueue(unit, pos)) >= gPri))
        /*lint -restore */
        {
          pos++;
        }

        if(pos==0U)
        {
            #ifdef ADC_DMA_SUPPORTED
            /* Abort the ongoing group conversion */
            if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA)
            {
                /* if Andorra2M and Andorra4M or Monaco 1.5M */
                #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
                /* Disable EQADC_A DMA interrupt */
                Dma_disable_interrupt((uint8)(fifoindex*2U));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + 1U));
                #else
                /* Disable EQADC_AorB DMA interrupt */
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
                Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
                #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
            } /* if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA) */
            #endif /* ADC_DMA_SUPPORTED  */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
/*lint -save -e960 */
            fifoindex = EQADC_GroupFifoIndex(ADC_GroupInQueue(unit, pos));
            /*lint -restore */
            /* Disable the used CFIFO  for this Group */
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_CFFE);
            REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_RFDE);
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)), EQADC_CFCR_MODE_DISABLED);
            /* Reload counter */
            Timeout = ADC_TIMEOUT_COUNTER;

            while ((((REG_READ32(EQADC_CFSR(eQADC_AorB))) & ((EQADC_CFSR_CFS0) >> (fifoindex * 2U))) != 0x00U)  && (Timeout > (uint32)0U))
            {
                /* Decrease counter */
                Timeout--;
            }
            /** Test for FIFO's status failure. */
            if ( Timeout == (uint32)0U )
            {
                /** Report production error and Return from function.  */
                Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                /*lint -save -e961 */
                return;
                /*lint -restore */
            }
            EQADC_Disable_FIFO((uint8)eQADC_AorB, (uint8)fifoindex);
            /* Worst case conversion time is 128 clock cycles at 1 MHZ */
            /* Assuming 264MHz clock speed for processor and single cycle  */
            /* execution of decrement operation */
            ADCConversionTimeCounter = ADC_CONVERSION_TIMEOUT;
            while(ADCConversionTimeCounter!=0x00U)
            {
                ADCConversionTimeCounter--;
            }
            /*    To clear RFDF flag    */
            for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
            {
                if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                {
                    break;
                }
                tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
            }
            REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), EQADC_FISRx_RFDF);
        }
        /* Make space for the new Group */
        if(qPtr > pos)
        {
            for(pTem = qPtr; pTem > pos; pTem--)
            {
                ADC_UnitStatus[unit].Queue[pTem] = ((Adc_GroupType)ADC_UnitStatus[unit].Queue[pTem-(Adc_QueueIndexType)1U]);
            }
        }
        /* Place the Group in the Queue */
        ADC_UnitStatus[unit].Queue[pos] = Group;
        /* This is used as redundent since only one Queue is maintained. This is required to report the DET's */
        ADC_UnitStatus[unit].HwQueue[pos] = Group;
        /* Increase the Queue Index */
        ADC_UnitStatus[unit].QueueIndex++;
        /* This is used as redundent since only one Queue is maintained. This is required to know the nos. of hardware trigger source enabled */
        ADC_UnitStatus[unit].HwQueueIndex++;
    } /* end of qPtr > (Adc_QueueIndexType)0U */
    #else /* ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE */
    #if (ADC_ENABLE_QUEUING == STD_ON) /* ADC333*/
    qPtr = ADC_UnitStatus[unit].QueueIndex;
    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Place the Group in the Queue */
        ADC_UnitStatus[unit].Queue[qPtr] = Group;
        /* This is used as redundent since only one Queue is maintained. This is required to report the DET's */
        ADC_UnitStatus[unit].HwQueue[qPtr] = Group;
        /* Increase the Queue Index */
        ADC_UnitStatus[unit].QueueIndex++;
        /* This is used as redundent since only one Queue is maintained. This is required to know the nos. of hardware trigger source enabled */
        ADC_UnitStatus[unit].HwQueueIndex++;
    }
    #else /* ADC_ENABLE_QUEUING == STD_OFF*/
    /* In this case all the Hardware trigger group should be rejected by DET*/
    #endif
    #endif

    #if (ADC_ENABLE_QUEUING == STD_ON)
    /* No_priorities OR Queue_is_empty */
    if((ADC_UnitStatus[unit].Queue[0] == Group)||(ADC_UnitStatus[unit].QueueIndex == (Adc_QueueIndexType)0U))
    {
    #endif
        /* Indicate a new group was added to the queue */
        if (ADC_UnitStatus[unit].QueueIndex == (Adc_QueueIndexType)0U)
        {
            /* Place the Group in the Queue */
            ADC_UnitStatus[unit].Queue[0] = Group;
            /* This is used as redundent since only one Queue is maintained. This is required to report the DET's */
            ADC_UnitStatus[unit].HwQueue[0] = Group;
            /* This is used as redundent since only one Queue is maintained. This is required to know the nos. of hardware trigger source enabled */
            ADC_UnitStatus[unit].HwQueueIndex++;
            ADC_UnitStatus[unit].QueueIndex++;
        }
        /* exit critical region */
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_10);
        /* ADC061*/
        EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
    #if (ADC_ENABLE_QUEUING == STD_ON)
    }
    else
    {
        /* exit critical region */
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_10);
    }
    #endif
}

/*================================================================================================*/
/**
 * @brief This function disables the hardware triggers for the specified group.
 *
 * @details This function disables the hardware triggers for the specified group.
 *
 * @param[in]  Group - the group for which the hardware triggers will be disabled.
 * @param[in]  unit  - the hardware unit. (on other platforms there are more hw units)
 *
 * @remarks    Covers: ADC116, ADC145, ADC157, ADC266, ADC361, ADC371, ADC429.
 * @remarks    Implements: DADC10006.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_DisableHardwareTrigger
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
    #if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) queueIndex = (Adc_QueueIndexType)0;
    VAR(Adc_QueueIndexType, AUTOMATIC) removedPos = (Adc_QueueIndexType)0;
    #endif
    VAR(uint32, AUTOMATIC) eQADC_AorB;
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(uint8, AUTOMATIC) Temp;
    VAR(volatile uint16, AUTOMATIC) ADCConversionTimeCounter;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;

    /* Enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_11);
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
/*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    /*lint -restore */
    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    eQADC_AorB = (uint8)ADC_EQADC_A;
    #else
    if(unit < (Adc_HwUnitType)ADC_UNIT_2)
    {
        eQADC_AorB = (uint8)ADC_EQADC_A;
    }
    else
    {
        eQADC_AorB = (uint8)ADC_EQADC_B;
    }
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
/*lint -save -e960 */
 if(((Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
    (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR))&&
    (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED))
 /*lint -restore */
  { /*Stream Completed*/
    /* group is stopped, change its status to IDLE  ADC361 */
    ADC_GroupStatus[Group].Conversion = ADC_IDLE;
    ADC_UnitStatus[unit].Status = ADC_IDLE;
    /* FD reset number of samples completed */
    ADC_GroupStatus[Group].ResultIndex = 0U;
    #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
    /* disable group notification (ADC157) */
    ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
    #endif
    ADC_GroupStatus[Group].HwTriggering = ADC_HWTRIGGER_DISABLED;
    /* exit critical region */
    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_11);
  }
  else
  {
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Find the Group in the Queue */
    removedPos= ADC_UnitStatus[unit].QueueIndex;  /* initialize with something invalid */
    /* Find the Group in the Queue */
    queueIndex = ADC_UnitStatus[unit].QueueIndex - (Adc_QueueIndexType)1U; /* Last valid Group in the Queue */
    while (queueIndex < (Adc_QueueIndexType)Adc_QueueIndexType_MAXIMUM)
    {
        if ( Group == ADC_UnitStatus[unit].Queue[queueIndex] ) /* The group is found in the Queue */
        {
        /* store the position of the group to be removed */
        removedPos= queueIndex;
        /* ADC116: disable the conversion of all channels belonging to this group */
            if(queueIndex == (Adc_QueueIndexType)0U) /* In this case the group might be under conversion */
#endif
            {
                /* Disable the hardware trigger source */
                SIU_LLD_DisableHwTrigger((uint8)eQADC_AorB, (uint8)fifoindex);

                #ifdef ADC_DMA_SUPPORTED
                if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA)
                {
                    /* if Andorra2M and Andorra4M or Monaco 1.5M */
                    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
                    /* Disable EQADC_A DMA interrupt */
                    Dma_disable_interrupt((uint8)(fifoindex*2U));
                    Dma_disable_interrupt((uint8)((fifoindex*2U) + 1U));
                    #else
                    /* Disable EQADC_AorB DMA interrupt */
                    Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
                    Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
                    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
                } /* if (Adc_Cfg_Ptr->Misc.ADC_DMA_INTERRUPT == ADC_DMA) */
                #endif /* ADC_DMA_SUPPORTED */
                /* Disable the used CFIFO  for this Group */
                REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_CFFE);
                REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(fifoindex)<<1U)),EQADC_IDCR_RFDE);
                REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + ((uint32)(fifoindex) << 1U)), EQADC_CFCR_MODE_DISABLED);
                /* Reload counter */
                Timeout = ADC_TIMEOUT_COUNTER;
                while ((((REG_READ32(EQADC_CFSR(eQADC_AorB))) & ((EQADC_CFSR_CFS0) >> (fifoindex * 2U))) != 0x00U)  && (Timeout > (uint32)0U))
                {
                    /* Decrease counter */
                    Timeout--;
                }
                /** Test for FIFOs status failure. */
                if ( Timeout == (uint32)0U )
                {
                    /** Report production error and Return from function.  */
                    Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                }
                EQADC_Disable_FIFO((uint8)eQADC_AorB, (uint8)fifoindex);
                /* Worst case conversion time is 128 clock cycles at 1 MHZ */
                /* Assuming 264MHz clock speed for processor and single cycle  */
                /* execution of decrement operation */
                ADCConversionTimeCounter = ADC_CONVERSION_TIMEOUT;
                while(ADCConversionTimeCounter!=0x00U)
                {
                    ADCConversionTimeCounter--;
                }
                /*    To clear RFDF flag    */
                for(Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
                {
                    if(((REG_READ32(EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U))) & EQADC_FISRx_RFCTR)==0x00U)
                    {
                        break;
                    }
                    tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(fifoindex)<<2U));
                }
                REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(fifoindex) << 2U)), EQADC_FISRx_RFDF);
                ADC_UnitStatus[unit].Status = ADC_IDLE;
            }
            /* ADC361*/
            ADC_GroupStatus[Group].ResultIndex = 0U;
             /* group hardware trigger is disabled, change its status to IDLE  ADC361 */
            ADC_GroupStatus[Group].Conversion = ADC_IDLE;
            /* ADC429*/
            ADC_UnitStatus[unit].HwQueue[0] =0U;
            ADC_UnitStatus[unit].HwQueueIndex = 0U;   /* Filled slots in the Hw queue */
            ADC_GroupStatus[Group].HwTriggering = ADC_HWTRIGGER_DISABLED;
            #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            /* [ADC157] if HW trigger is disabled for a group, its HW trigger status becoms DISABLED */
            ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
            #endif
    #if (ADC_ENABLE_QUEUING == STD_ON)
            /* remove group from Queue */
            /* ADC385--ADC386*/
            EQADC_RemoveFromQueue(unit, queueIndex);
         break;
      }
      queueIndex--;
    }/* End od While */
        /* Start the next qroup in the Queue (if any) */
        if((removedPos == (Adc_QueueIndexType)0U) && (ADC_UnitStatus[unit].QueueIndex > (Adc_QueueIndexType)0U))
        {
            /* exit critical region */
              SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_11);
            /* Structures and pointers will be initialized when the next Group starts */
            EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
        }
        else
        {
            /* exit critical region */
              SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_11);
        }
    #else
        /* no element will be present in the queue */
        ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
        ADC_UnitStatus[unit].HwQueueIndex = 0U;   /* Filled slots in the Hw queue */
        /* exit critical region */
          SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_11);
    #endif
  }
}

#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */

/*================================================================================================*/
/**
 * @brief This function returns the first empty position in the result buffer.
 *
 * @details This function returns the first empty position in the result buffer.
 *
 * @param[in]  Group          - the group index.
 * @param[in]  PtrToSamplePtr - pointer to the result buffer start address.

 * @return     Number of samples from the result buffer.

 * @remarks    Covers: ADC214, ADC216, ADC326, ADC327, ADC328, ADC375, ADC382, ADC387
 * @remarks    Implements: DADC10007
 *
 * @api
 */
/*================================================================================================*/
FUNC(Adc_StreamNumSampleType, ADC_CODE) EQADC_LLD_GetStreamLastPointer
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
)
{
  VAR(Adc_StreamNumSampleType, AUTOMATIC) NumberOfResults = (Adc_StreamNumSampleType)0U;
  VAR(Adc_StreamNumSampleType, AUTOMATIC) ResultIndex = (Adc_StreamNumSampleType)0U;

  *PtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;

  /* Enter critical region */
  SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_12);

  if ((ADC_GroupStatus[Group].Conversion == ADC_COMPLETED) || (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED))
  {
    if (ADC_GroupStatus[Group].ResultIndex == (Adc_StreamNumSampleType)0U)
    {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
/*lint -save -e960 */
      ResultIndex = Adc_Cfg_Ptr->Groups[Group].NumSamples - (Adc_StreamNumSampleType)1U;
      /* ADC387 Note*/
      NumberOfResults = Adc_Cfg_Ptr->Groups[Group].NumSamples;
      /*lint -restore */
    }
    else
    {
      ResultIndex = ADC_GroupStatus[Group].ResultIndex - (Adc_StreamNumSampleType)1U;
      NumberOfResults = ADC_GroupStatus[Group].ResultIndex;
    }


    /* The following code has been added to respect the State Diagram of Streaming Access Mode */
    if (ADC_GroupStatus[Group].Conversion == ADC_COMPLETED)
    {
      ADC_GroupStatus[Group].ResultIndex = 0U;

      /* ADC328 -- ADC222*/
      ADC_GroupStatus[Group].Conversion = ADC_BUSY;
    }
/**
@note  Violates MISRA 2004 Rule 11.4, cast from pointer to pointer - See @ref EQADC_LLD_c_REF_5
*/
    /*lint -save -e961 */
    /* ADC214 -- ADC418 -- ADC382*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    *PtrToSamplePtr = (Adc_ValueGroupType *)(Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group]+ ResultIndex);

    /* Compliance with State Diagram */
    if (Adc_Cfg_Ptr->Groups[Group].TriggerSource  == ADC_TRIGG_SRC_SW)
    /*lint -restore */
    {
      if (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED)
      {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        if((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_ONESHOT)||
          ((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_CONTINUOUS)&&
          (Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
          (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)))
        /*lint -restore */
        {
          /* ADC327 -- ADC221*/
          ADC_GroupStatus[Group].Conversion = ADC_IDLE;
        }
        else
        { /* Continuous*/
          /* ADC326 -- ADC222*/
          ADC_GroupStatus[Group].Conversion = ADC_BUSY;
        }
      }
    }
    else
    { /* Hw Trigger*/
      if (ADC_GroupStatus[Group].Conversion == ADC_STREAM_COMPLETED)
      {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
        /*lint -save -e960 */
        if((Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
          (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR))
        /*lint -restore */
        {
          /* ADC327 - ADC221*/
          ADC_GroupStatus[Group].Conversion = ADC_IDLE;
        }
        else
        { /* Simple One-shot mode, in other words in single access mode*/
          /* ADC326 -- ADC222*/
          ADC_GroupStatus[Group].Conversion = ADC_BUSY;
        }
      }
    }
  }

  /* Exit critical region */
  SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_12);

  /* ADC387 -- ADC382*/
  return(NumberOfResults);
}

/*================================================================================================*/
/**
 * @brief This function starts the conversion on the specified hardware unit.
 *
 * @details This function starts the conversion on the specified hardware unit.

 * @param[in]  unit - the used hw unit.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_LLD_StartNormalConversion
(
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
    P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) GroupPtr; /* Pointer to AdcGroup */
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0U; /* Active group in the Queue */
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
    VAR(uint8, AUTOMATIC) eQADC_AorB = 0U; /* eQADC nos. */

    if (ADC_UnitStatus[unit].QueueIndex == (Adc_QueueIndexType)0)
    {
/**
@note  Violates MISRA 2004 Rule 14.7, Return statement before end of function - See @ref EQADC_LLD_c_REF_4
*/
        /*lint -save -e961 */
        return;
        /*lint -restore */
    }

    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    eQADC_AorB = (uint8)ADC_EQADC_A;
    #else
    if(unit < (Adc_HwUnitType)ADC_UNIT_2)
    {
        eQADC_AorB = (uint8)ADC_EQADC_A;
    }
    else
    {
        eQADC_AorB = (uint8)ADC_EQADC_B;
    }
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

    /* Get the Group ID of the current active group */
    Group=ADC_UnitStatus[unit].Queue[0]; /* Load the first group in the queue (ADC_UnitStatus[unit].Queue[0])*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    GroupPtr = &(Adc_Cfg_Ptr->Groups[Group]);
    /*lint -restore */
    /* ADC431 */
    /* Put the conversion results from Results Buffer Base Address */
    ADC_GroupStatus[Group].ResultIndex = 0U;
    /* Mark the Unit as BUSY */
    ADC_UnitStatus[unit].Status = ADC_BUSY;

    /* init EQADC_IDCRx registers depending on selected hw unit */
    #ifdef ADC_DMA_SUPPORTED
        /* prepare conversion command messages */
        Adc_CopyQueueData2DMACommmandBuffer(unit);
        /* start eDMA channels, one to fill CFIFO and the another one to drain RFIFO */
        EQADC_StartDMAOperation(unit);
        /* Configure IDCR register for the DMA mode */
        REG_WRITE16((EQADC_IDCR0(eQADC_AorB) + (fifoindex<<1U)), (EQADC_IDCR_CFFE | EQADC_IDCR_CFFS | EQADC_IDCR_RFDE | EQADC_IDCR_RFDS));
    #else
        EQADC_CFIFOChannelCount[eQADC_AorB][fifoindex] = 0U;
        EQADC_RFIFOChannelCount[eQADC_AorB][fifoindex] = 0U;
        /* Enable CFIFO Fill and RFIFO Drain Interrupts */
        REG_WRITE16((EQADC_IDCR0(eQADC_AorB) + (fifoindex<<1U)), (EQADC_IDCR_CFFE | EQADC_IDCR_RFDE));
    #endif

    /* Initiate SW conversion i.e. set transfer mode according to the group settings */
    if (GroupPtr->TriggerSource==ADC_TRIGG_SRC_SW)
    {
        if (GroupPtr->mode==ADC_CONV_MODE_ONESHOT)
        {
            /* software trigger single scan mode */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (fifoindex<<1U)), (EQADC_CFCR_SSE | EQADC_CFCR_MODE_SWSS));
        }
        else
        {
            /* software trigger continous scan mode */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (fifoindex<<1U)), EQADC_CFCR_MODE_SWCS);
        }
    }
    #if (STD_ON == ADC_HW_TRIGGER_API)
    else if (GroupPtr->TriggerSource==ADC_TRIGG_SRC_HW) /* hardware trigger source */
    {

        /* Select the Triggering Source using the HW Trigger SelectorSIU_ISEL(4-5)  is used for the EQADC_A and SIU_ISEL(6-7)  is used for the EQADC_B */
        SIU_LLD_EnableHwTrigger(GroupPtr, (uint8)eQADC_AorB, (uint8)fifoindex);

        if (GroupPtr->TriggerEdge==ADC_HW_TRIG_RISING_EDGE)
        {
            /* hardware trigger continous scan rising edge trigger source */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (fifoindex<<1U)), EQADC_CFCR_MODE_HWCS_REd);
        }
        else if(GroupPtr->TriggerEdge==ADC_HW_TRIG_FALLING_EDGE)
        {
            /* hardware trigger continous scan falling edge trigger source */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (fifoindex<<1U)), EQADC_CFCR_MODE_HWCS_FEd);
        }
        else
        {
            /* hardware trigger continous scan both edge trigger source */
            REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (fifoindex<<1U)), EQADC_CFCR_MODE_HWCS_BEd);
        }
    }
    else
    {
        /* Catastrophic Errors Recovery (CER) */
        Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U, (uint8)ADC_EQADC_LLD_STARTNORMALCONVERSION_ID, (uint8)ADC_CER_TRIG_SRC_TYPE);
    }
    #endif /* ADC_HW_TRIGGER_API */
}

#if (ADC_ENABLE_QUEUING == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief This function implements the dequeue operation on the internal ADC queue.
 *
 * @details

 * @param[in]  unit - the used hw unit.
 * @param[in]  i    - the current queue index.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_RemoveFromQueue
(
  CONST(Adc_HwUnitType, ADC_CONST) unit,
  CONST(Adc_QueueIndexType, ADC_CONST) i
)
{
  Adc_QueueIndexType j = (Adc_QueueIndexType)0U;
    Adc_QueueIndexType current_index= ADC_UnitStatus[unit].QueueIndex;

    if( (Adc_QueueIndexType)current_index <= (Adc_QueueIndexType)1U)
    {
        /* zero or one element present in the queue */
        ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
    }
    else
    {
        /* more than one element in the queue */
        /* move all elements after the one to remove (from i position) one place to the left */
        for(j=(Adc_QueueIndexType)i+(Adc_QueueIndexType)1U; j<(Adc_QueueIndexType)current_index; j++)
        {
            ADC_UnitStatus[unit].Queue[j-(Adc_QueueIndexType)1U]=(Adc_GroupType)ADC_UnitStatus[unit].Queue[j];
        }
        ADC_UnitStatus[unit].QueueIndex--;
    }
}
#endif

#if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief This function  extracts the conversion commands from the config structure and copies it the RAM Buffers.
 *
 * @details  This function  extracts the conversion commands from the config structure and copies it the RAM Buffers

 * @param[in]  unit - the used hw unit.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC (void, ADC_CODE) Adc_CopyQueueData2DMACommmandBuffer(VAR(Adc_HwUnitType, AUTOMATIC) unit)
{
    VAR(Adc_GroupType, AUTOMATIC) Group;
    VAR(Adc_ChannelType, AUTOMATIC) ChannelsInGrp;
    VAR(uint16, AUTOMATIC) index = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(volatile uint32, AUTOMATIC) FifoCmdmsg;
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index */
    VAR(uint32, AUTOMATIC) EndOfQueue = 0U; /* end of queue */

    Group = EQADC_CurrentGroup(unit);
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    ChannelsInGrp = EQADC_GroupChannels(Group);
    ChIndex = EQADC_GroupChannelIndex(Group, index);
    /*lint -restore */
    FifoCmdmsg = (RESULT_FIFO_OFFSET*fifoindex);
        for(index = 0U;  index < ChannelsInGrp; index++)
        {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            ChIndex = EQADC_GroupChannelIndex(Group, index);
            if ((index == (uint16)((uint16)ChannelsInGrp-1U)) && (Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_ONESHOT))
            /*lint -restore */
            {
                /* Last ADC channel, hence set the EOQ Flag */
                EndOfQueue = ADC_WRITE_CONFIG_EOQ;
            }
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_12) /* 12 Bit conversion result */
            /*lint -restore */
            {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                /*lint -save -e960 */
                EQADC_DMACommandQueue[unit][index] = ((Adc_Cfg_Ptr->Channels[unit][ChIndex].Msg) | FifoCmdmsg | EQADC_STD_CONFIG_SEL_12BIT_RES | EndOfQueue);
                /*lint -restore */
            }
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            else if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_10) /* 10 Bit conversion result */
            /*lint -restore */
            {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                /*lint -save -e960 */
                EQADC_DMACommandQueue[unit][index] = ((Adc_Cfg_Ptr->Channels[unit][ChIndex].Msg) | FifoCmdmsg | EQADC_ALT_CONFIG_SEL_10BIT_RES | EndOfQueue);
                /*lint -restore */
            }
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
            /*lint -save -e960 */
            else if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_8)/* 8 Bit conversion result */
            /*lint -restore */
            {
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
                /*lint -save -e960 */
                EQADC_DMACommandQueue[unit][index] = ((Adc_Cfg_Ptr->Channels[unit][ChIndex].Msg) | FifoCmdmsg | EQADC_ALT_CONFIG_SEL_8BIT_RES | EndOfQueue);
                /*lint -restore */
            }
            else
            {
                /* Catastrophic Errors Recovery (CER) */
                Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U, (uint8)ADC_COPYQUEUEDATA2DMACOMMMANDBUFFER_ID, (uint8)ADC_CER_CORRUPTED_RES_TYPE);
            }
        }
}

/*================================================================================================*/
/**
 * @brief This function programs the DMA transfers involved in the ADC conversion process.
 *
 * @details This function programs the DMA transfers involved in the ADC conversion process.

 * @param[in]  unit - the used hw unit.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_StartDMAOperation
(
  VAR(Adc_HwUnitType, AUTOMATIC) unit
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0U;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) GroupPtr; /* Pointer to AdcGroup */
    VAR(Adc_ChannelType, AUTOMATIC)ChCount = (Adc_ChannelType)0U;
    VAR(uint32, AUTOMATIC) fifoindex = 0U; /* fifo index for the group */
    VAR(uint32, AUTOMATIC) SlastCommandValue;
    VAR(uint32, AUTOMATIC) DlastDataValue;
    VAR(uint32, AUTOMATIC) DestOffset;
    VAR(uint8, AUTOMATIC) eQADC_AorB = 0U; /* eQADC nos. */
    VAR(Adc_ChannelType, AUTOMATIC) ChannelsInGrp;

    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    eQADC_AorB = (uint8)ADC_EQADC_A;
    #else
    if(unit < ADC_UNIT_2)
    {
        eQADC_AorB = (uint8)ADC_EQADC_A;
    }
    else
    {
        eQADC_AorB = (uint8)ADC_EQADC_B;
    }
    #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

    /* Get the Group ID of the current active group */
    Group=ADC_UnitStatus[unit].Queue[0]; /* Load the first group in the queue (ADC_UnitStatus[unit].Queue[0])*/
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    fifoindex = EQADC_GroupFifoIndex(Group);
    GroupPtr = &(Adc_Cfg_Ptr->Groups[Group]);
    /*lint -restore */
    DestOffset = (uint32)(sizeof(Adc_ValueGroupType) * (uint32)GroupPtr->NumSamples);
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    ChCount = (Adc_Cfg_Ptr->Groups[Group].AssignedChannelCount);
    ChannelsInGrp = EQADC_GroupChannels(Group);
    /*lint -restore */
    SlastCommandValue = (uint32)((uint32)ChannelsInGrp * 4U);
    if (GroupPtr->NumSamples == 1U)
    {
        DlastDataValue = (uint32)((uint32)ChannelsInGrp * 2UL);
    }
    else
    {
        DlastDataValue = (uint32)((2U * (uint32)((uint32)((uint32)(GroupPtr->NumSamples) - 1U) + ((uint32)((uint32)ChannelsInGrp - 2U) * (uint32)(GroupPtr->NumSamples)))) + (uint32)DestOffset);
    }

    /* if Andorra2M and Andorra4M or Monaco 1.5M */
    #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
    /* Disable EQADC_A DMA interrupt */
    Dma_disable_interrupt((uint8)(fifoindex*2U));
    Dma_disable_interrupt((uint8)((fifoindex*2U) + 1U));
    #else
    /* Disable EQADC_AorB DMA interrupt */
    Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
    Dma_disable_interrupt((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
    #endif /* #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

    /* update result address of channel 0 and destination offset to support format of streaming buffer */
/**
@note  Violates MISRA 2004 Rule 17.4, pointer arithmetic other than array indexing used
- See @ref EQADC_LLD_c_REF_7
*/
    /*lint -save -e960 */
    pResult = GroupPtr->ResultsBufferPtr[Group] + ADC_GroupStatus[Group].ResultIndex;
    /*lint -restore */
    if (Adc_Cfg_Ptr->Misc.ADC_HW_UNIT[unit] == (uint8)STD_ON)
    {
        /* if Andorra2M and Andorra4M or Monaco 1.5M */
        #if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
        /* Configure the DMA to transfer the command */
        Dma_configure_channel((uint8)(fifoindex*2U),                           /* dma_channel */
                              (uint32)(&EQADC_DMACommandQueue[unit][0]),       /* src_addr */
                              (uint8)DMA_DATA_TRANSFER_32_BIT,                 /* src_transfer_size */
                              (uint8)DMA_DATA_TRANSFER_32_BIT,                 /* dest_transfer_size */
                              (uint16)4U,                                      /* src_next_offset */
                              (uint16)4U,                                      /* n_bytes_to_transfer */
                              (uint32)-SlastCommandValue,                      /* src_last_adj */
                              (uint32)(EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)),   /* dest_addr */
                              (uint16)ChCount,                                 /* current_iteration_count */
                              (uint16)0U,                                      /* dest_next_offset */
                              (uint32)0U,                                      /* dest_last_adj */
                              (uint16)ChCount,                                 /* begin_iteration_count */
                              (uint8)DMA_TCD_DISABLE_REQ                       /* interrupt_config_mask */
                          );

        /* Configure the DMA to transfer the result */
        Dma_configure_channel((uint8)((fifoindex*2U) + 1U),                    /* dma_channel */
                              (uint32)(EQADC_RFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U) + 2U), /* src_addr */
                              (uint8)DMA_DATA_TRANSFER_16_BIT,                 /* src_transfer_size */
                              (uint8)DMA_DATA_TRANSFER_16_BIT,                 /* dest_transfer_size */
                              (uint16)0U,                                      /* src_next_offset */
                              (uint16)2U,                                      /* n_bytes_to_transfer */
                              (uint32)0U,                                      /* src_last_adj */
                              (uint32)(pResult),                               /* dest_addr */
                              (uint16)ChCount,                                 /* current_iteration_count */
                              (uint16)(GroupPtr->NumSamples << 1U),            /* dest_next_offset */
                              (uint32)-DlastDataValue,                         /* dest_last_adj */
                              (uint16)ChCount,                                 /* begin_iteration_count */
                              (uint8)(DMA_TCD_DISABLE_REQ | DMA_TCD_INT_MAJOR) /* interrupt_config_mask */
                          );
        /* Start the DMA channel0 */
        Dma_start_channel((uint8)(fifoindex*2U));
        Dma_start_channel((uint8)((fifoindex*2U) + 1U));
        #else
        /* Configure the DMA to transfer the command */
        Dma_configure_channel((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)), /* dma_channel */
                              (uint32)(&EQADC_DMACommandQueue[unit][0]),       /* src_addr */
                              (uint8)DMA_DATA_TRANSFER_32_BIT,                 /* src_transfer_size */
                              (uint8)DMA_DATA_TRANSFER_32_BIT,                 /* dest_transfer_size */
                              (uint16)4U,                                      /* src_next_offset */
                              (uint16)4U,                                      /* n_bytes_to_transfer */
                              (uint32)-SlastCommandValue,                      /* src_last_adj */
                              (uint32)(EQADC_CFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U)),   /* dest_addr */
                              (uint16)ChCount,                                 /* current_iteration_count */
                              (uint16)0U,                                      /* dest_next_offset */
                              (uint32)0U,                                      /* dest_last_adj */
                              (uint16)ChCount,                                 /* begin_iteration_count */
                              (uint8)DMA_TCD_DISABLE_REQ                       /* interrupt_config_mask */
                          );

        /* Configure the DMA to transfer the result */
        Dma_configure_channel((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U),   /* dma_channel */
                              (uint32)(EQADC_RFPR0(eQADC_AorB)+((uint32)(fifoindex)<<2U) + 2U), /* src_addr */
                              (uint8)DMA_DATA_TRANSFER_16_BIT,                 /* src_transfer_size */
                              (uint8)DMA_DATA_TRANSFER_16_BIT,                 /* dest_transfer_size */
                              (uint16)0U,                                      /* src_next_offset */
                              (uint16)2U,                                      /* n_bytes_to_transfer */
                              (uint32)0U,                                      /* src_last_adj */
                              (uint32)(pResult),                               /* dest_addr */
                              (uint16)ChCount,                                 /* current_iteration_count */
                              (uint16)(GroupPtr->NumSamples << 1U),            /* dest_next_offset */
                              (uint32)-DlastDataValue,                         /* dest_last_adj */
                              (uint16)ChCount,                                 /* begin_iteration_count */
                              (uint8)(DMA_TCD_DISABLE_REQ | DMA_TCD_INT_MAJOR) /* interrupt_config_mask */
                          );
        /* Start the DMA channel0 */
        Dma_start_channel((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
        Dma_start_channel((uint8)((fifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
        #endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */
    }
}
#endif /* #if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__) */

/*================================================================================================*/
/**
 * @brief This function disables the CFIFO depends on the hardware unit and fifo index.
 *
 * @details This function disables the CFIFO depends on the hardware unit and fifo index.

 * @param[in]  eQADC   - eQADC number.
 * @param[in]  fifo_no - the fifo number.
 *
 * @api
 */
/*================================================================================================*/
FUNC(void, ADC_CODE) EQADC_Disable_FIFO
(
  VAR(uint8, AUTOMATIC) eQADC,
  VAR(uint8, AUTOMATIC) fifo_no
)
{
    /* Disable CFIFOi */
    REG_WRITE16((EQADC_CFCR0(eQADC)+((uint32)(fifo_no)<<(uint32)1U)), EQADC_CFCR_CFINV|EQADC_CFCR_MODE_DISABLED);

    /* Disable all Interrupts and eDMA for CFIFOi */
    REG_WRITE16((EQADC_IDCR0(eQADC)+((uint32)(fifo_no)<<(uint32)1U)), (uint32)0U);

    /* Clear all Interrupts and eDMA flags for CFIFOi */
    REG_WRITE32((EQADC_FISR0(eQADC)+((uint32)(fifo_no)<<(uint32)2U)), EQADC_FISRx_CLEAR_MASK);

    /* Clear the Tx Count Registers for CFIFOi */
    REG_WRITE16((EQADC_CFTCR0(eQADC)+((uint32)(fifo_no)<<(uint32)1U)), (uint32)0U);

    /* Invalidate CFIFOi */
    REG_WRITE16((EQADC_CFCR0(eQADC)+((uint32)(fifo_no)<<(uint32)1U)), EQADC_CFCR_CFINV);
}

#define ADC_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref EQADC_LLD_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref EQADC_LLD_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore */

#ifdef __cplusplus
}
#endif
/** @} */
