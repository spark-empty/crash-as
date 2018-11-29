/**
@file    Pwm_NonASR.c
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm NonAutosar high level interface implementation.
@details Pwm NonAutosar high level interface implementation.

Project AUTOSAR 3.0 MCAL
Platform PA
Peripheral eMIOS200
Dependencies none

ARVersion 3.0.0
ARRevision ASR_REL_3_0_REV_0003
ARConfVariant
SWVersion 2.0.0
BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

(c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
All Rights Reserved.
*/
/*===============================================================================================
================================================================================================*/
    

/**
@page misra_violations MISRA-C:2004 violations

@section Pwm_NonASR_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Pwm_NonASR_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15, :  Repeated include files,  Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section Pwm_NonASR_C_REF_3
Violates MISRA 2004 Advisory Rule 8.10,All declarations and definitions of objects or functions
at file scope shall have internal linkage unless external linkage is required.
*/



#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/


#include "Pwm.h"
#include "Pwm_NonASR.h"
#include "Pwm_LLD.h"


#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif


/*===============================================================================================
                                        LOCAL MACROS
===============================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_NONASR_C            43
#define PWM_AR_MAJOR_VERSION_NONASR_C     3
#define PWM_AR_MINOR_VERSION_NONASR_C     0
#define PWM_AR_PATCH_VERSION_NONASR_C     0
#define PWM_SW_MAJOR_VERSION_NONASR_C    2
#define PWM_SW_MINOR_VERSION_NONASR_C     0
#define PWM_SW_PATCH_VERSION_NONASR_C     0
/**@}*/

/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

/* Check if source file and PWM header file are of the same vendor */
#if (PWM_VENDOR_ID_NONASR_C != PWM_VENDOR_ID)
    #error "Pwm_NonASR.c and Pwm.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_NONASR_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_NONASR_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_NONASR_C != PWM_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Pwm_NonASR.c and Pwm.h are different"
    #endif
#endif

/* Check if source file and PWM header file are of the same Software version */
#if ((PWM_SW_MAJOR_VERSION_NONASR_C != PWM_SW_MAJOR_VERSION)  || \
     (PWM_SW_MINOR_VERSION_NONASR_C != PWM_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_NONASR_C != PWM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Pwm_NonASR.c and Pwm.h are different"
#endif



/* Check if source file and Pwm_NonASR.h are of the same vendor */
#if (PWM_VENDOR_ID_NONASR_C != PWM_VENDOR_ID_NONASR_H)
    #error "Pwm_NonASR.c and Pwm_NonASR.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Pwm_NonASR.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_NONASR_C != PWM_AR_MAJOR_VERSION_NONASR_H) || \
         (PWM_AR_MINOR_VERSION_NONASR_C != PWM_AR_MINOR_VERSION_NONASR_H) || \
         (PWM_AR_PATCH_VERSION_NONASR_C != PWM_AR_PATCH_VERSION_NONASR_H))
        #error "AutoSar Version Numbers of Pwm_NonASR.c and Pwm_NonASR.h are different"
    #endif
#endif

/* Check if source file and Pwm_NonASR.h are of the same Software version */
#if ((PWM_SW_MAJOR_VERSION_NONASR_C != PWM_SW_MAJOR_VERSION_NONASR_H) || \
     (PWM_SW_MINOR_VERSION_NONASR_C != PWM_SW_MINOR_VERSION_NONASR_H) || \
     (PWM_SW_PATCH_VERSION_NONASR_C != PWM_SW_PATCH_VERSION_NONASR_H))
    #error "Software Version Numbers of Pwm_NonASR.c and Pwm_NonASR.h are different"
#endif



/* Check if source file and PWM LLD header file are of the same vendor */
#if (PWM_VENDOR_ID_NONASR_C != PWM_VENDOR_ID_LLD_H)
    #error "Pwm_NonASR.c and Pwm.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM LLD header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_NONASR_C != PWM_AR_MAJOR_VERSION_LLD_H) || \
         (PWM_AR_MINOR_VERSION_NONASR_C != PWM_AR_MINOR_VERSION_LLD_H) || \
         (PWM_AR_PATCH_VERSION_NONASR_C != PWM_AR_PATCH_VERSION_LLD_H))
        #error "AutoSar Version Numbers of Pwm_NonASR.c and Pwm.h are different"
    #endif
#endif

/* Check if source file and PWM LLD header file are of the same Software version */
#if ((PWM_SW_MAJOR_VERSION_NONASR_C != PWM_SW_MAJOR_VERSION_LLD_H) || \
     (PWM_SW_MINOR_VERSION_NONASR_C != PWM_SW_MINOR_VERSION_LLD_H) || \
     (PWM_SW_PATCH_VERSION_NONASR_C != PWM_SW_PATCH_VERSION_LLD_H))
    #error "Software Version Numbers of Pwm_NonASR.c and Pwm.h are different"
#endif





/* Check if source file and DET header file are of the same version */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((PWM_AR_MAJOR_VERSION_NONASR_C != DET_AR_MAJOR_VERSION) || \
             (PWM_AR_MINOR_VERSION_NONASR_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Pwm_NonASR.c and Det.h are different"
        #endif
    #endif
#endif

/*===============================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
===============================================================================================*/

/*===============================================================================================
                                       LOCAL CONSTANTS
===============================================================================================*/

/*===============================================================================================
                                       LOCAL VARIABLES
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL CONSTANTS
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL VARIABLES
===============================================================================================*/

/*===============================================================================================
                                   LOCAL FUNCTION PROTOTYPES
===============================================================================================*/

/*===============================================================================================
                                       LOCAL FUNCTIONS
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL FUNCTIONS
===============================================================================================*/
#define PWM_START_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file Pwm_NonASR.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Pwm_NonASR_C_REF_1,
    Pwm_NonASR_C_REF_2 */
#include "MemMap.h"
/*lint -restore */

#if (PWM_SETCOUNTERBUS_API == STD_ON)
/**
@brief  Implementation specific function to change the frequency of pwm channels running on
        PWM_MODE_OPWMB or PWM_MODE_OPWMT mode

@details    This function is useful to change the frequency of the output PWM signal between
            two counter buses frequency

    If no DET error reported then the selected counter bus period will be read and the function
    Pwm_LLD_SetDutyCycle() will be called to change the output signal frequency and dutycycle

    If development error detection for the Pwm module is enabled:

        - if any function (except Pwm_Init) is called before Pwm_Init has been called,
        the called function shall raise development error PWM_E_UNINIT.

    If development error detection for the Pwm module is enabled:

        - this function shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled:

        - when a development error occurs, the corresponding PWM function shall:

            Report the error to the Development Error Tracer.

            Skip the desired functionality in order to avoid any corruptions of
            data or hardware registers: This means leave the function without any actions

@param[in] ChannelNumber - pwm channel id
@param[in] Bus           - the eMIOS bus to change to

@remarks Covers       PWM_CUSTOM001, PWM064, PWM117, PWM047, PWM051
@remarks Implements   DPWM01010
*/
        /** @file Pwm.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_C_REF_3 */
FUNC (void, PWM_CODE) Pwm_SetCounterBus
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                          VAR(uint32, AUTOMATIC) Bus
                      )
{
#if (PWM_DEV_ERROR_DETECT == STD_ON)

    if (NULL_PTR == Pwm_Cfg_Ptr)
    {

        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_SETCOUNTERBUS_ID,
            (uint8) PWM_E_UNINIT
        );
    }
    else if (ChannelNumber >= Pwm_Cfg_Ptr->ChannelCount)
    {

        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_SETCOUNTERBUS_ID,
            (uint8) PWM_E_PARAM_CHANNEL
        );
    }
    else if ((Bus != PWM_BUS_A) && (Bus != PWM_BUS_DIVERSE))
    {

        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_SETCOUNTERBUS_ID,
            (uint8) PWM_E_COUNTERBUS
        );
    } else
#endif /* PWM_DEV_ERROR_DETECT */
    {
        Pwm_LLD_SetCounterBus( ChannelNumber, Bus );
    }

}
#endif /* API SWITCH */

#if (PWM_SETCHANNELOUTPUT_API == STD_ON)
/**
@brief  Implementation specific function to set the state of the PWM pin
        as requested for the current cycle

@details    This function is useful to set the state of the PWM pin as requested
            for the current cycle and continues with normal PWM operation from the next cycle

    If no DET error reported then the state of the PWM pin will be Active
    (Same as the configured polarity) or Inactive (Opposite state of the configured polarity)
    based on the passed input parameter.

    If development error detection for the Pwm module is enabled:

        - if any function (except Pwm_Init) is called before Pwm_Init has been called,
        the called function shall raise development error PWM_E_UNINIT.

    If development error detection for the Pwm module is enabled:

        - this function shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled:

        - when a development error occurs, the corresponding PWM function shall:

            Report the error to the Development Error Tracer.

            Skip the desired functionality in order to avoid any corruptions of
            data or hardware registers: This means leave the function without any actions

@param[in] ChannelNumber - pwm channel id
@param[in] State         - Active/Inactive state of the channel

@remarks Covers       PR-MCAL-3173, PWM064, PWM117, PWM047, PWM051
@remarks Implements   DPWM01030
*/
        /** @file Pwm.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_C_REF_3 */
FUNC (void, PWM_CODE) Pwm_SetChannelOutput
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                          VAR(Pwm_StateType, AUTOMATIC) State
                      )
{

#if (PWM_DEV_ERROR_DETECT == STD_ON)

    if (NULL_PTR == Pwm_Cfg_Ptr)
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_SETCHANNELOUTPUT_ID,
            (uint8) PWM_E_UNINIT
        );
    }
    else if (ChannelNumber >= Pwm_Cfg_Ptr->ChannelCount)
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_SETCHANNELOUTPUT_ID,
            (uint8) PWM_E_PARAM_CHANNEL
        );
    } else
#endif /* PWM_DEV_ERROR_DETECT */
    {
        Pwm_LLD_SetChannelOutput( ChannelNumber, State );
    }
}
#endif /* API SWITCH */

#if (PWM_DUAL_CLOCK_MODE == STD_ON)
/**
@brief      Implementation specific function to change the peripheral clock frequency.

@details    This function is useful to set the prescalers that divide the PWM channels
            clock frequency.

    If no DET error reported then the prescalers of the PWM channels will be set.

    If development error detection for the Pwm module is enabled:

    - if any function (except Pwm_Init) is called before Pwm_Init has been called,
    the called function shall raise development error PWM_E_UNINIT.

    Report the error to the Development Error Tracer.

    Skip the desired functionality in order to avoid any corruptions of
    data or hardware registers: This means leave the function without any actions.

@param[in] Prescaler - prescaler type

@remarks Covers       PR-MCAL-3199
@remarks Implements   DPWM01040
*/
FUNC (void, PWM_CODE) Pwm_SetClockMode(VAR(Pwm_SelectPrescalerType, AUTOMATIC) Prescaler)
{
#if (PWM_DEV_ERROR_DETECT == STD_ON)

        if (NULL_PTR == Pwm_Cfg_Ptr)
        {
            Det_ReportError
            (
                (uint16) PWM_MODULE_ID,
                (uint8) 0,
                (uint8) PWM_SETCLOCKMODE_ID,
                (uint8) PWM_E_UNINIT
            );
        }
        else
#endif /* PWM_DEV_ERROR_DETECT */
        {
            Pwm_LLD_SelectPrescaler(Prescaler);
        }
}
#endif

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
/**
@brief      Implementation specific function to change the trigger delay

@details    This function is useful to set the trigger delay to opwmt mode

    If no DET error reported then the trigger delay for  the PWM channels will be set.

    If development error detection for the Pwm module is enabled:

    Report the error to the Development Error Tracer.

    Skip the desired functionality in order to avoid any corruptions of
    data or hardware registers: This means leave the function without any actions.

@param[in] ChannelNumber - pwm channel id
@param[in] TriggerDelay         - triggerdelay

@remarks Covers       PR-MCAL-3234
@remarks Implements   DPWM07050
*/
/*@remarks Covers PR-MCAL-3234*/
FUNC (void, PWM_CODE) Pwm_SetTriggerDelay
                        (
                              VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                              VAR(uint16, AUTOMATIC) TriggerDelay
                        )
{
#if (PWM_DEV_ERROR_DETECT == STD_ON)

        if (NULL_PTR == Pwm_Cfg_Ptr)
        {
            Det_ReportError
            (
                (uint16) PWM_MODULE_ID,
                (uint8) 0,
                (uint8) PWM_SETTRIGGERDELAY_ID,
                (uint8) PWM_E_UNINIT
            );
        }
        else if (ChannelNumber >= Pwm_Cfg_Ptr->ChannelCount)
        {

            Det_ReportError
            (
                (uint16) PWM_MODULE_ID,
                (uint8) 0,
                (uint8) PWM_SETTRIGGERDELAY_ID,
                (uint8) PWM_E_PARAM_CHANNEL
            );
        }
        else if 
            (
                (Pwm_Cfg_Ptr->ChannelsPtr[ChannelNumber].SpecificCfg.EmiosCfg.Pwm_ParamValue
                   & 
                CCR_MODE_MASK) != CCR_MODE_OPWMT                    
            )
        {
            Det_ReportError
            (
                (uint16) PWM_MODULE_ID, 
                (uint8) 0,  
                (uint8) PWM_SETTRIGGERDELAY_ID, 
                (uint8) PWM_E_PARAM_CHANNEL
            );
        }
        else if(TriggerDelay > (uint16)(Pwm_Cfg_Ptr->ChannelsPtr[ChannelNumber].Pwm_DefaultPeriodValue))
        {    
            Det_ReportError
            (
                (uint16) PWM_MODULE_ID, 
                (uint8) 0, 
                (uint8) PWM_SETTRIGGERDELAY_ID, 
                (uint8) PWM_E_OPWMT_CHANNEL_TRIGGER_RANGE
            );
        }
        else
#endif /* PWM_DEV_ERROR_DETECT */
        {
            Pwm_LLD_SetTriggerDelay(ChannelNumber,TriggerDelay);
        }
}
#endif
#endif
#endif
#define PWM_STOP_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file Pwm_NonASR.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Pwm_NonASR_C_REF_1,
    Pwm_NonASR_C_REF_2 */
#include "MemMap.h"
/*lint -restore */

#ifdef __cplusplus
}
#endif
