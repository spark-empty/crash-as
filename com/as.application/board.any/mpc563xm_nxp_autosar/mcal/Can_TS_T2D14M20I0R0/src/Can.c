/**
    @file             Can.c
    @version          2.0.0

    @brief            AUTOSAR Can module interface
    @details          API implementation for CAN driver.

    Project           AUTOSAR 3.0 MCAL
    Platform          PA
    Peripheral        FLEXCAN
    Dependencies      

    ARVersion         3.0.0
    ARRevision        ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion         2.0.0
    BuildVersion      XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section Can_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Can_c_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
here are different kinds of execution code sections.

@section Can_c_REF_3
Violates MISRA 2004 Advisory Rule 17.4 , Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.
*/

/**
@file  Can.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_c_REF_2
*/

/*
Driver Limitations:
    1. The maximum number of Can_DisableControllerInterrupts levels of nesting is 127. (variable "sint8" used for nesting level: -128 .. +127)
    2. The Hth parameter of Can_Write API is of type 'Can_HWObjectCountType'. Autosar requires this parameter to be of type uint8, but having platforms with 6 Can controllers and every one having 64 MBs, uint8 type is not enough to cover all the number pf MBs
    3. This file contains 2 types of functions: first are the Autosar APIs and then are some user defined functions.
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
#include "Can.h"
#include "Can_LLD.h"

#include "CanIf_Cbk.h"
#include "Dem.h"


/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   (CAN111) Can.c shall check if the correct version of Can.h is included.
            This shall be done by a preprocessor check of the version numbers CAN_SW_MAJOR_VERSION, CAN_SW_MINOR_VERSION and CAN_SW_PATCH_VERSION.
@remarks Covers CAN111
@remarks Implements DCAN00111
*/
#define CAN_VENDOR_ID_C        43
#define CAN_AR_MAJOR_VERSION_C 3
#define CAN_AR_MINOR_VERSION_C 0
#define CAN_AR_PATCH_VERSION_C 0
#define CAN_SW_MAJOR_VERSION_C 2
#define CAN_SW_MINOR_VERSION_C 0
#define CAN_SW_PATCH_VERSION_C 0
/**@}*/


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#if (CAN_VENDOR_ID_C != CAN_VENDOR_ID)
#error "Can.c and Can.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_C != CAN_AR_MAJOR_VERSION) || \
     (CAN_AR_MINOR_VERSION_C != CAN_AR_MINOR_VERSION) || \
     (CAN_AR_PATCH_VERSION_C != CAN_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Can.c and Can.h are different"
#endif
#endif

#if ((CAN_SW_MAJOR_VERSION_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_SW_MINOR_VERSION_C != CAN_SW_MINOR_VERSION))
#error "Software Version Numbers of Can.c and Can.h are different"
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
     (CAN_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Can.c and Det.h are different"
#endif
#endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
     (CAN_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
#error "Software Version Numbers of Can.c and Dem.h are different"
#endif
#endif


/*==================================================================================================
                                    VARIABLES
==================================================================================================*/
#define CAN_START_SEC_VAR_UNSPECIFIED

/**
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_c_REF_2
*/
/*lint -save -e961 -e537*/
#include "MemMap.h"
/*lint -restore*/

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/**
@remarks  This variable holds the state of the driver. After reset is UNINIT. The output of Can_Init() function
          (only to first call) should set this variable into READY state.
          CAN_UNINIT = The CAN controller is not initialized. All registers belonging to the CAN module are in reset state, CAN interrupts are disabled.
          The CAN Controller is not participating on the CAN bus.
          The Can module must only implement a variable for the module state, when the development error tracing is switched on.
          When the development error tracing is switched off, the Can module does not need to implement this 'state machine',
          because the state information is only needed to check if Can_Init was called prior to any Can module function.
@brief    (CAN103) After power-up/reset, the Can module shall be in the state CAN_UNINIT.
@remarks  Covers CAN103
@remarks  Implements DCAN00103
*/
VAR(Can_StatusType, CAN_VAR) Can_DriverStatus = CAN_UNINIT;
#endif


/* Pointer to the current Driver Configuration (passed to the driver during initialization). Initialized by Can_Init(). */
P2CONST(Can_ConfigType, CAN_VAR, CAN_APPL_CONST) Can_CurrentConfigPtr = NULL_PTR;
P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Can_ControllerConfigPtr = NULL_PTR;


#define CAN_STOP_SEC_VAR_UNSPECIFIED

/**
@file  Can.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_c_REF_2
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                        GLOBAL FUNCTIONS
==================================================================================================*/
#define CAN_START_SEC_CODE
/**
@file  Can.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_c_REF_2
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*================================================================================================*/
/**
@brief         Returns the version information of this module. SID = 0x07
@details       This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     versioninfo A pointer to location to store version info

@pre           The CAN_VERSION_INFO_API define must be configured on.
@post          The version information is return if the parameter versionInfo is not a null pointer.

@remarks       (CAN224) Can_GetVersionInfo service.
@remarks       (CAN251) If source code for caller and callee is available, the function Can_GetVersionInfo should be realized as a macro, defined in the Can module header file.
@remarks       Covers CAN224, CAN251
@remarks       Implements DCAN00224, DCAN00251
*/
/*================================================================================================*/
#if (CAN_VERSION_INFO_API == STD_ON)

FUNC(void, CAN_CODE) Can_GetVersionInfo( P2VAR(Std_VersionInfoType, CAN_VAR, CAN_APPL_DATA) versioninfo)
    {

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /**
        @brief     (CAN177) If development error detection for the Can module is enabled: The function Can_GetVersionInfo shall
                     raise the error CAN_E_PARAM_POINTER if the parameter versionInfo is a null pointer.
        @remarks   Covers CAN177
        @remarks   Implements DCAN00177
        */
        if ( NULL_PTR == versioninfo )
        {
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_GET_VERSION_INFO, (uint8)CAN_E_PARAM_POINTER);
        }
        else
        {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
            /**
            @remarks   (CAN105) The function Can_GetVersionInfo shall return the version information of this module. The version information
                         includes: Module Id, Vendor Id, Vendor specific version numbers.
            @remarks   Covers CAN105
            @remarks   Implements DCAN00105
            */
            versioninfo->vendorID         = (uint16)CAN_VENDOR_ID;
            versioninfo->moduleID         = (uint16)CAN_MODULE_ID;
            versioninfo->instanceID       = (uint8)CAN_INSTANCE;
            versioninfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION;
            versioninfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION;
            versioninfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION;
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }

#endif /* (CAN_VERSION_INFO_API == STD_ON) */


/*================================================================================================*/
/**
@brief         Initialize the CAN driver. SID = 0x00.
@details       Initialize all the controllers.
               The CAN module shall be initialized by Can_Init(<&Can_Configuration>) service call during the start-up.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Config Pointer to driver configuration.

@pre           Can_Init shall be called at most once during runtime.
@post          Can_Init shall initialize all the controllers and set the driver in READY state.

@remarks       (CAN223) Can_Init service.
@remarks       (CAN021) The desired CAN controller configuration can be selected with the parameter Config.
@remarks       (CAN291) Config is a pointer into an array of hardware specific data structure stored in ROM.The different controller configuration sets are located as data structures in ROM.
@remarks       Covers CAN223, CAN021, CAN291
@remarks       Implements DCAN00223, DCAN00021, DCAN00291
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_Init( P2CONST(Can_ConfigType, CAN_VAR, CAN_APPL_CONST) Config)
    {

        /* Variable for indexing the controllers. */
        VAR(uint8, CAN_VAR) can_controller = 0U;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /**
        @brief   (CAN027) Detected development errors shall be reported to the Det_ReportError service of the Development Error Tracer (DET)
                   if the pre-processor switch CanDevErrorDetection is set.
        @brief   (CAN083) If the CanDevErrorDetection switch is enabled API parameter checking is enabled.
        @brief   (CAN028)Development Errors call the Development Error Tracer when DET is switched on and the Can module detects an error.
        @remarks Covers CAN027, CAN083, CAN028
        @remarks Implements DCAN00027, DCAN00083, DCAN00028
        */
        if ( CAN_READY == Can_DriverStatus )
        {
            /**
            @brief   (CAN247) The Can module environment shall call Can_Init at most once during runtime.
            @brief   (CAN091) After return of the DET the Can module function that raised the development error shall return immediately.
            @brief   (CAN174) If development error detection for the Can module is enabled: The function Can_Init shall raise the
                       error CAN_E_TRANSITION if the driver is not in 'uninitialized' state.
            @brief   (CAN248) The function Can_Init shall report the error CAN_E_UNINIT, if Can_Init was called prior to any Can module function.
            @remarks Covers CAN247, CAN091, CAN174, CAN248
            @remarks Implements DCAN00247, DCAN00091, DCAN00174, DCAN00248
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT, (uint8)CAN_E_TRANSITION);
        }
        else
        {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

#ifdef CAN_PRECOMPILE_SUPPORT
            /* Update config pointer with default configuration if precompile support on. */
            Can_CurrentConfigPtr = (NULL_PTR == Config) ? &Can_ConfigSet_PC : Config;
            Can_ControllerConfigPtr = Can_CurrentConfigPtr->ControllerConfigsPtr;
#endif /* CAN_PRECOMPILE_SUPPORT */

            /**
            @brief   (CAN056) Post-Build configuration elements that are marked as 'm ultiple' ('M' or 'x') can be selected by passing
                       the pointer 'Config' to the init function of the module..
            @remarks Covers CAN056
            @remarks Implements DCAN00056
            */
#ifndef CAN_PRECOMPILE_SUPPORT
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
            if ( NULL_PTR == Config )
            {
                /**
                @brief   (CAN175) If development error detection for the Can module is enabled: The function Can_Init shall raise the
                           error CAN_E_PARAM_POINTER if a NULL pointer was given as config parameter.
                @remarks Covers CAN175
                @remarks Implements DCAN00175
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT, (uint8)CAN_E_PARAM_POINTER);
            }
            else
            {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                /* Copy pointer to current Can Driver configuration. */
                Can_CurrentConfigPtr = Config;
                Can_ControllerConfigPtr = Config->ControllerConfigsPtr;
#endif /* CAN_PRECOMPILE_SUPPORT */

                /* Initialisation of usefull indicators. */
                Can_LLD_InitVariables();

                /* Loop through all Can controllers configured based CanControllerId parameter. */
                for ( can_controller = 0U; can_controller < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_controller++)
                {
                    /* The initialization is skipped for the controllers that are not enabled. */
                      /**
                      @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                      */
                    if ( FLEXCAN_NULL_OFFSET != Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset )
                    {
                        /* Init - ControllerState, FirstHrhIndex, HthOffset, DefaultConfigIndex, MaxMBCount, CanWakeupSourceID, Freeze controller and more ... */
                        /**
                        @brief   (CAN239) The function Can_Init shall initialize all on-chip hardware resources that are used by the CAN controller.
                        @remarks Covers CAN239
                        @remarks Implements DCAN00239
                        */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                        */
                        Can_LLD_Init( &Can_CurrentConfigPtr->ControlerDescriptors[can_controller]);

                        /**
                        @brief   (CAN250) The function Can_Init shall initialize: static variables, including flags, Common setting for the
                                   complete CAN HW unit, CAN controller specific settings for each CAN controller.
                        @brief   (CAN245) The function Can_Init shall initialize all CAN controllers according to their configuration.
                        @brief   (CAN053) Can module/controller initalization - registers of CAN controller hardware resources that are not used.
                        @remarks Covers CAN250, CAN245, CAN053
                        @remarks Implements DCAN00250, DCAN00245, DCAN00053
                        */
                       /**
                       @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_7
                       */
                        Can_LLD_InitController( can_controller, Can_ControllerConfigPtr + can_controller);
                    }
                }

#if (CAN_DEV_ERROR_DETECT == STD_ON)
                /**
                @brief   (CAN246) After initializing all controllers inside the HW Unit, the function Can_Init shall change the module state to CAN_READY.
                @remarks Covers CAN246
                @remarks Implements DCAN00246
                */
                Can_DriverStatus = CAN_READY;
    #ifndef CAN_PRECOMPILE_SUPPORT
            }
    #endif /* # CAN_PRECOMPILE_SUPPORT */
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

    }


/*================================================================================================*/
/**
@brief         Initialize the CAN controllers. SID = 0x02.
@details       Initialize the controller based on ID input parameter.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Controller Can controller to be initialized - based on configuration order list (CanControllerId).
@param[in]     Config Pointer to controller configuration.

@pre           Before controller re-initalization the driver must be initialized and the controllers must be in Stop state.
@post          Interrupts and MBs must be configured for respond to CAN bus.

@remarks       (CAN229) Can_InitController service.
@remarks       Covers CAN229
@remarks       Implements DCAN00229
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_InitController( VAR(uint8, CAN_VAR) Controller,
                                          P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Config)
    {

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* If Can_DriverStatus is CAN_UNINIT then the driver was not initialised yet. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN187) If development error detection for the Can module is enabled: The function Can_InitController shall raise the
                       error CAN_E_UNINIT if the driver is not yet initialized.
            @remarks Covers CAN187
            @remarks Implements DCAN00187
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_UNINIT);
        }
        else
        {
            /* If Config is NULL_PTR then the supplied configuration is wrong. */
            if ( NULL_PTR == Config )
            {
                /**
                @brief   (CAN188) If development error detection for the Can module is enabled: The function Can_InitController shall raise
                           the error CAN_E_PARAM_POINTER if the parameter Config is an null pointer.
                @remarks Covers CAN188
                @remarks Implements DCAN00188
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_PARAM_POINTER);
            }
            else
            {
                /* The Controller ID must be within range and the selected controller must be configured for use in the config tool. */
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                */
                if ( (Controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                     (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[Controller].ControllerOffset) )
                {
                    /**
                    @brief   (CAN189) If development error detection for the Can module is enabled: The function Can_InitController shall raise the
                               error CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
                    @remarks Covers CAN189
                    @remarks Implements DCAN00189
                    */
                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_PARAM_CONTROLLER);
                }
                else
                {
                    if ( CAN_T_STOP != Can_ControllerStatuses[Controller].ControllerState )
                    {
                        /**
                        @brief   (CAN190) If development error detection for the Can module is enabled: if the controller is not in state CANIF_CS_STOPPED,
                                   the function Can_InitController shall raise the error CAN_E_TRANSITION.
                        @brief   (CAN256) The Can module environment shall only call Can_InitController when the CAN controller is in state CANIF_CS_STOPPED.
                        @remarks Covers CAN190, CAN256
                        @remarks Implements DCAN00190, DCAN00256
                        */
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                        /**
                        @brief   (CAN062) The function Can_InitController shall re-initialize the CAN controller and the controller specific settings.
                        @brief   (CAN255) The function Can_InitController shall only affect register areas that contain specific configuration for a single CAN controller.
                        @remarks Covers CAN062, CAN255
                        @remarks Implements DCAN00062, DCAN00255
                        */
                        Can_LLD_InitController( Controller, Config);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
                }
            }
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }


/*================================================================================================*/
/**
@brief         Put the controller into a required state. SID = 0x03.
@details       Switch the controller from one state to another.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Controller Can controller for which the status shall be changed - based on configuration order list (CanControllerId).
@param[in]     Transition Possible transitions (CAN_T_STOP / CAN_T_START / CAN_T_SLEEP / CAN_T_WAKEUP)

@return        Can_ReturnType  Result of the transition.
@retval        CAN_OK   Transition initiated.
@retval        CAN_NOT_OK  Development or production error.

@pre           Before changing the controller state the driver must be initialized.
@post          After the transition to the new state the interrupts required for that state must be enebaled.

@remarks       (CAN230) Can_SetControllerMode service.
@remarks       Covers CAN230
@remarks       Implements DCAN00230
*/
/*================================================================================================*/
FUNC (Can_ReturnType, CAN_CODE) Can_SetControllerMode( VAR(uint8, CAN_VAR) Controller,
                                                       VAR(Can_StateTransitionType, CAN_VAR) Transition )
    {

        /* Returns the result of transition mode. */
        VAR(Can_ReturnType, CAN_VAR)  Out_can_return = CAN_NOT_OK;

        /**
        @brief   (CAN089) The Can module environment shall indicate development errors only in the return values of a function of the Can module when DET
                   is switched on and the function provides a return value. The returned value is CAN_NOT_OK.
        @remarks Covers CAN089
        @remarks Implements DCAN00089
        */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* If Can_CurrentConfigPtr is NULL_PTR then the Driver was not initialised yet. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN198) If development error detection for the Can module is enabled: if the module is not yet initialized, the
                       function Can_SetControllerMode shall raise development error CAN_E_UNINIT and return CAN_NOT_OK.
            @remarks Covers CAN198
            @remarks Implements DCAN00198
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_UNINIT);
        }
        else
        {
            /* Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
            */
            if ( (Controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                 (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[Controller].ControllerOffset) )
            {
                /**
                @brief   (CAN199) If development error detection for the Can module is enabled: if the parameter Controller is out of range,
                           the function Can_SetControllerMode shall raise development error CAN_E_PARAM_CONTROLLER and return CAN_NOT_OK.
                @remarks Covers CAN199
                @remarks Implements DCAN00199
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                /* Call the LLD function for transition execution. */
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                */
                Out_can_return = Can_LLD_SetControllerMode( Controller, &Can_CurrentConfigPtr->ControlerDescriptors[Controller], Transition);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
#endif /* (CAN_DEV_ERROR_DETECT==STD_ON)  */

        return (Out_can_return);
    }


/*================================================================================================*/
/**
@brief         Disable INTs. SID = 0x04.
@details       Switch OFF the controller's interrupts.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Controller Can controller for which interrupts shall be disabled - based on configuration order list (CanControllerId).

@pre           Driver must be initalzied before changing the interrupts state (en/dis).
@post          Controller must not respond to any interrupt assertion.

@remarks       (CAN231) Can_DisableControllerInterrupts service.
@remarks       Covers CAN231
@remarks       Implements DCAN00231
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_DisableControllerInterrupts( VAR(uint8, CAN_VAR) Controller)
    {

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* If Can_CurrentConfigPtr is NULL_PTR then the driver was not initialised yet. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN205) If development error detection for the Can module is enabled: The function Can_DisableControllerInterrupts shall
                       raise the error CAN_E_UNINIT if the driver not yet initialized.
            @remarks Covers CAN205
            remarks  Implements DCAN00205
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_E_UNINIT);
        }
        else
        {
            /* The Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
            */
            if ( (Controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                 (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[Controller].ControllerOffset) )
            {
                /**
                @brief   (CAN206) If development error detection for the Can module is enabled: The function Can_DisableControllerInterrupts shall
                           raise the error CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
                @remarks Covers CAN206
                @remarks Implements DCAN00206
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                /* Call the LLD function for disabling interrupts. */
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                */
                Can_LLD_DisableControllerInterrupts( Controller, &Can_CurrentConfigPtr->ControlerDescriptors[Controller]);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }


/*================================================================================================*/
/**
@brief         Enable INTs. SID = 0x05.
@details       Switch ON the controller's interrupts.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Controller Can controller for which interrupts shall be disabled - based on configuration order list (CanControllerId).

@pre           Driver must be initalzied before changing the interrupts state (en/dis).
@post          Controller must respond to interrupt assertion.

@remarks       (CAN232) Can_EnableControllerInterrupts service.
@remarks       Covers CAN232
@remarks       Implements DCAN00232
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_EnableControllerInterrupts( VAR(uint8, CAN_VAR) Controller)
    {

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* If Can_CurrentConfigPtr is NULL_PTR then the driver was not initialised yet. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN209) If development error detection for the Can module is enabled: The function Can_EnableControllerInterrupts shall raise
                       the error CAN_E_UNINIT if the driver not yet initialized.
            @remarks Covers CAN209
            @remarks Implements DCAN00209
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_E_UNINIT);
        }
        else
        {
            /* Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
            */
            if ( (Controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                 (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[Controller].ControllerOffset) )
            {
                /**
                @brief   (CAN210) If development error detection for the Can module is enabled: The function Can_EnableControllerInterrupts shall
                           raise the error CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
                @remarks Covers CAN210
                @remarks Implements DCAN00210
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                /* Call the LLD function for enabling interrupts. */
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                */
                Can_LLD_EnableControllerInterrupts( Controller, &Can_CurrentConfigPtr->ControlerDescriptors[Controller]);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }


/*================================================================================================*/
/**
@brief         Transmit information on CAN bus. SID = 0x06.
@details       Can_Write checks if hardware transmit object that is identified by the HTH is free.
                    Can_Write checks if another Can_Write is ongoing for the same HTH.
                    a) hardware transmit object is free:
                        The mutex for that HTH is set to 'signaled' the ID, DLC and SDU are put in a format appropriate for
                          the hardware (if necessary) and copied in the appropriate hardware registers/buffers.
                        All necessary control operations to initiate the transmit are done.
                        The mutex for that HTH is released. The function returns with CAN_OK.
                    b) hardware transmit object is busy with another transmit request.
                        The function returns with CAN_BUSY.
                    c) A preemptive call of Can_Write has been issued, that could not be handled reentrant (i.e. a call with the same HTH).
                        The function returns with CAN_BUSY the function is non blocking
                    d) The hardware transmit object is busy with another transmit request for an L-PDU that has lower priority than that for the current request
                        The transmission of the previous L-PDU is cancelled (asynchronously).
                        The function returns with CAN_BUSY.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     Hth Information which HW-transmit handle shall be used for transmit.
               Implicitly this is also the information about the controller to use because the Hth numbers are unique inside one hardware unit.
@param[in]     PduInfo Pointer to SDU user memory, DLC and Identifier.

@return        Can_ReturnType   Result of the write operation.
@retval        CAN_OK   Write command has been accepted.
@retval        CAN_NOT_OK  Development error occured.
@retval        CAN_BUSY   No of TX hardware buffer available or preemtive call of Can_Write() that can't be implemented reentrant.

@pre           Driver must be initialized and MB must be configured for Tx.
@post          The data can be transmitted or rejected because of another data with a higher priority.

@remarks       (CAN233) Can_Write service.
@remarks       Covers CAN233
@remarks       Implements DCAN00233
*/
/*================================================================================================*/
FUNC (Can_ReturnType, CAN_CODE) Can_Write( VAR(Can_HWObjectCountType, CAN_VAR) Hth,
                                           P2CONST(Can_PduType, CAN_VAR, CAN_APPL_CONST) PduInfo )
    {

        /* Variable for return status */
        VAR(Can_ReturnType, CAN_VAR)  Out_can_return = CAN_NOT_OK;


#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* If Can_CurrentConfigPtr is NULL_PTR then the driver was not initialised yet. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN216) If development error detection for the Can module is enabled: The function Can_Write shall raise the error CAN_E_UNINIT if
                       the driver not yet initialized.
            @remarks Covers CAN216
            @remarks Implements DCAN00216
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_UNINIT);
            Out_can_return = CAN_NOT_OK;
        }
        else
        {
            /* Hth must be below MessageBufferConfigCount and should be a Tx MB type. */
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
            */
            if ( (Hth >= Can_CurrentConfigPtr->Can_max_object_Id) ||
                 (TRANSMIT != (Can_ObjType)Can_CurrentConfigPtr->Can_ObjectType_Mapping[Hth]) )
            {
                /**
                @brief   (CAN217) If development error detection for the Can module is enabled: The function Can_Write shall raise the error CAN_E_PARAM_HANDLE
                           if the parameter Hth is not a configured Hardware Transmit Handle.
                @remarks Covers CAN217
                @remarks Implements DCAN00217
                */
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_PARAM_HANDLE);
                Out_can_return = CAN_NOT_OK;
            }
            else
            {
                /* Report Error if Protocol Data Unit information pointer is NULL. */
                if ( (NULL_PTR == PduInfo) || (NULL_PTR == PduInfo->sdu) )
                {
                    /**
                    @brief   (CAN219) If development error detection for the Can module is enabled: The function Can_Write shall raise the
                               error CAN_E_PARAM_POINTER if the parameter PduInfo or the SDU pointer inside PduInfo is a null-pointer.
                    @remarks Covers CAN219
                    @remarks Implements DCAN00219
                     */
                    Det_ReportError ( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, CAN_E_PARAM_POINTER);
                    Out_can_return = CAN_NOT_OK;
                }
                else
                {
                    /* Report error if length > 8 bytes. */
                    if ( (PduInfo->length) > FLEXCAN_MB_DATABYTES )
                    {
                        /**
                        @brief   (CAN218) If development error detection for the Can module is enabled: The function Can_Write shall raise the
                                   error CAN_E_PARAM_DLC if the length is more than 8 byte.
                        @remarks Covers CAN218
                        @remarks Implements DCAN00218
                        */
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_PARAM_DLC);
                        Out_can_return = CAN_NOT_OK;
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                        /* Call the LLD function for transmitting data. */
                        Out_can_return = Can_LLD_Write( Hth, PduInfo);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
                }
            }
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

        return (Out_can_return);
    }


/*================================================================================================*/
/**
@brief         Function called at fixed cyclic time. SID 0x01.
@details       Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@pre           Driver must be initialized.
@post          Send the data from that MB that is configured for Tx.

@remarks       (CAN225) Can_MainFunction_Write service.
@remarks       Covers CAN225
@remarks       Implements DCAN00225
*/
/*================================================================================================*/
#if (CAN_TXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_MainFunction_Write( void)
    {

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test whether the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN179) If development error detection for the module Can is enabled: The function Can_MainFunction_Write shall raise
                       the error CAN_E_UNINIT if the driver is not yet initialized.
            @remarks Covers CAN179
            @remarks Implements DCAN00179
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_E_UNINIT);
        }
        else
        {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
            /* Poll all controllers for Tx MB statuses. */
            Can_LLD_MainFunction_Write();

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }

#endif /*(CAN_TXPOLL_SUPPORTED == STD_ON)   */


/*================================================================================================*/
/**
@brief         Function called at fixed cyclic time.  SID = 0x08.
@details       Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@pre           Driver must be initialized.
@post          Receive the data from that MB that is configured for Rx.

@remarks       (CAN226) Can_MainFunction_Read service.
@remarks       Covers CAN226
@remarks       Implements DCAN00226
*/
/*================================================================================================*/
#if (CAN_RXPOLL_SUPPORTED  == STD_ON)

FUNC (void, CAN_CODE) Can_MainFunction_Read( void)
    {

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test whether the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN181) If development error detection for the Can module is enabled: The function Can_MainFunction_Read shall raise the
                       error CAN_E_UNINIT if the driver not yet initialized.
            @remarks Covers CAN181
            @remarks Implements DCAN00181
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_E_UNINIT);
        }
        else
        {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
            /* Poll all controllers for Rx MB statuses. */
            Can_LLD_MainFunction_Read();

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }

#endif /* (CAN_RXPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
@brief         Function called at fixed cyclic time. SID - 0x09.
@details       Service for performs the polling of BusOff events that are configured statically as 'to be polled'.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@pre           Driver must be initialized.
@post          Handle the Busoff event.

@remarks       (CAN227) Can_MainFunction_BusOff service.
@remarks       Covers CAN227
@remarks       Implements DCAN00227
*/
/*================================================================================================*/
#if (CAN_BUSOFFPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_MainFunction_BusOff( void)
    {

        /* Variable for indexing the controllers */
        VAR(uint8, CAN_VAR) can_controller = 0U;


    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test whether the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN184) If development error detection for the Can module is enabled: The function Can_MainFunction_BusOff shall raise
                       the error CAN_E_UNINIT if the driver not yet initialized.
            @remarks Covers CAN184
            @remarks Implements DCAN00184
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_BUS_OFF, (uint8)CAN_E_UNINIT);
        }
        else
        {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

            /* Loop through all Can controllers configured based CanControllerId parameter. */
            for ( can_controller = (uint8)0U; can_controller < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_controller++)
            {
                /**
                @brief   (CAN109) The function Can_MainFunction_BusOff shall perform the polling of bus-off events that are configured statically as 'to be polled'.
                @remarks Covers CAN109
                @remarks Implements DCAN00109
                */
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
                */
                if ( (FLEXCAN_NULL_OFFSET != Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset) &&
                     ((CAN_CONTROLLERCONFIG_BOPOL_EN & (uint16)((Can_ControllerConfigPtr + can_controller)->Options)) != (uint16)0x0U) )
                {
                    /* Check for BusOff status. */
                    if ( (uint8)E_OK == Can_LLD_CheckBusOff(can_controller) )
                    {
                        /* Process BusOff event. */
                        Can_Process_BusOff( can_controller);
                    }
                }
            }
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }

#endif /* (CAN_BUSOFFPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
@brief         Function called at fixed cyclic time. SID = 0x0A.
@details       Service for performs performs the polling of WakeUp events that are configured statically as 'to be polled'.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@pre           Driver must be initialized.
@post          Handle the Wakeup event.

@remarks       (CAN228) Can_MainFunction_Wakeup service.
@remarks       Covers CAN228
@remarks       Implements DCAN00228
*/
/*================================================================================================*/
#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUPPOLL_SUPPORTED == STD_ON))

FUNC (void, CAN_CODE) Can_MainFunction_Wakeup( void)
    {

        /* Variable for indexing the controllers */
        VAR(uint8, CAN_VAR) can_controller = 0U;


    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test whether the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN186) If development error detection for the Can module is enabled: The function Can_MainFunction_Wakeup shall raise the error CAN_E_UNINIT if the driver not yet initialized.
            @remarks Covers CAN186
            @remarks Implements DCAN00186
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_WAKEUP, (uint8)CAN_E_UNINIT);
        }
        else
        {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

            /* Loop through all Can controllers configured based CanControllerId parameter. */
            for ( can_controller = (uint8)0U; can_controller < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_controller++)
            {
                /**
                @brief   (CAN112) The function Can_MainFunction_Wakeup shall perform the polling of wake-up events that are configured
                           statically as 'to be polled'.
                @remarks Covers CAN112
                @remarks Implements DCAN00112
                */
                if ( (FLEXCAN_NULL_OFFSET != Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset) &&
                     ((CAN_CONTROLLERCONFIG_WKPOL_EN & (uint16)((Can_ControllerConfigPtr + can_controller)->Options)) != (uint16)0x0U) )
                {
                    /* Check for wake up condition. */
                    if ( (uint8)E_OK == Can_LLD_Cbk_CheckWakeup( can_controller) )
                    {
                        /* Process Wakeup event. */
                        Can_Process_Wakeup( can_controller);
                    }
                }
            }

    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    }

#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUPPOLL_SUPPORTED == STD_ON)) */


/*================================================================================================*/
/**
@brief         Process check of WakeUp condition. SID = 0x0B.
@details       This service shall evaluate the WakeupSource parameter to get the information,
                 which dedicate wakeup source needs to be checked, either a CAN transceiver or controller device.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     controller Can controller ID - based on configuration order list (CanControllerId).

@return        Std_ReturnType Result of the wakeup verification.
@retval        E_OK  Wakeup was detected for the given controller.
@retval        E_NOT_OK  No wakeup was detected for the given controller.

@pre           Driver must be initialized.
@post          Return the Wakeup event occurence.

@remarks       (CAN360) Can_Cbk_CheckWakeup service.
@remarks       Covers CAN360
@remarks       Implements DCAN00360
*/
/*================================================================================================*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (Std_ReturnType, CAN_CODE) Can_Cbk_CheckWakeup( VAR(uint8, CAN_VAR) controller)
    {

        /* E_NOT_OK is defined as (uint8)0x01 */
        VAR(boolean, CAN_VAR) Out_can_return = (uint8)E_NOT_OK;


    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test whether the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            /**
            @brief   (CAN362) If development error detection for the Can module is enabled: The function Can_Cbk_CheckWakeup shall raise
                       the error CAN_E_UNINIT if the driver is not yet initialized.
            @remarks Covers CAN362
            @remarks Implements DCAN00362
            */
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_CBK_CHECK_WAKEUP, (uint8)CAN_E_UNINIT);
        }
        else
        {
            /**
            @brief   (CAN363) If development error detection for the Can module is enabled: The function Can_Cbk_CheckWakeup shall raise the
                       error CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            @remarks Covers CAN363
            @remarks Implements DCAN00363
            */
            if ( (controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                 (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset) )
            {
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_CBK_CHECK_WAKEUP, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                /* Call LLD function for checking wakeup status. */
                Out_can_return = Can_LLD_Cbk_CheckWakeup( controller);
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

        return (Out_can_return);
    }

#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
@brief      Process BusOff event.
@details    This routine is called by:
              - Can_MainFunction_BusOff() from Can.c file.
              - Can_IsrFC##FC##_BO() from Can_Irq.c file.

@param[in]  controller Can controller ID - based on configuration order list (CanControllerId).

@pre        Driver must be initialized.
@post       Handle the Busoff event.

@remarks    Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Process_BusOff( CONST(uint8, CAN_CONST) controller)
    {

        /* Used for internal logic - return value */
        VAR(Can_ReturnType, CAN_VAR) can_return = CAN_NOT_OK;


        /**
        @brief   (CAN272) After bus-off detection, the Can module shall transition to the state CANIF_CS_STOPPED and shall ensure that
                   the CAN controller doesn't participate on the network anymore.
        @remarks Covers CAN272
        @remarks Implements DCAN00272
        */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref Can_c_REF_3
        */
        can_return = Can_LLD_SetControllerMode( controller,  &Can_CurrentConfigPtr->ControlerDescriptors[controller], CAN_T_STOP);

        /* Process Busoff event only if controller was passed to Stop mode. */
        if ( CAN_OK == can_return )
        {
            /* Process Busoff event. Clear the bus off interrupt flag. */
            Can_LLD_Process_BusOff( controller);

            /**
            @brief   (CAN020) The CanIf module is notified with the callback function CanIf_ControllerBusOff after stopped state is reached.
            @remarks Covers CAN020
            @remarks Implements DCAN00020
            */
            CanIf_ControllerBusOff( controller);
        }
}


/*================================================================================================*/
/**
@brief         Process WakeUp event.
@details       This routine is called by:
                - Can_MainFunction_Wakeup() from Can.c file.
                - Can_IsrFC##FC##_WKP() from Can_Irq.c file.

@param[in]     controller Can controller ID - based on configuration order list (CanControllerId).

@pre           Driver must be initialized.
@post          Handle the Wakeup event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC(void, CAN_CODE) Can_Process_Wakeup( CONST(uint8, CAN_CONST) controller )
    {

        /* Used for internal logic - return value */
        VAR(Can_ReturnType, CAN_VAR)  can_return = CAN_NOT_OK;


        /* Transition the controller to WAKEUP mode. */
        can_return = Can_LLD_SetControllerMode( controller, &Can_CurrentConfigPtr->ControlerDescriptors[controller], CAN_T_WAKEUP);

        /* Process Wakeup event only if transition from Sleep to Wakeup was ok. */
        if ( CAN_OK == can_return )
        {
            /* Process WakeUp event. Clear the wakeup interrupt flag. */
            Can_LLD_Process_Wakeup (controller);
        }
    }

#endif  /* (CAN_WAKEUP_SUPPORT == STD_ON) */


/*================================================================================================*/
/**
@brief         Process Receive Data event.
@details       This routine is called by:
                - Can_IsrFC##FC##_UNI() from Can_Irq.c file.
                - Can_IsrFC##FC##_##Name() from Can_Irq.c file.

@param[in]     controller Can controller ID - based on configuration order list (CanControllerId).
@param[in]     mbindex_start first MB to process.
@param[in]     mbindex_end last MB to process.

@pre           Driver must be initialized.
@post          Handle the Receive event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Process_Rx( CONST(uint8, CAN_CONST) controller,
                                     CONST(uint8, CAN_CONST) mbindex_start,
                                     CONST(uint8, CAN_CONST) mbindex_end )
    {

        /* Process Rx event. Clear the rx interrupt flag. */
        Can_LLD_Process_Rx( controller, mbindex_start, mbindex_end);
    }


/*================================================================================================*/
/**
@brief         Process Transmit Data event.
@details       This routine is called by:
                - Can_IsrFC##FC##_UNI() from Can_Irq.c file.
                - Can_IsrFC##FC##_##Name() from Can_Irq.c file.

@param[in]     controller Can controller ID - based on configuration order list (CanControllerId).
@param[in]     mbindex_start first MB to process.
@param[in]     mbindex_end last MB to process.

@pre           Driver must be initialized.
@post          Handle the Transmit event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Process_Tx( CONST(uint8, CAN_CONST) controller,
                                     CONST(uint8, CAN_CONST) mbindex_start,
                                     CONST(uint8, CAN_CONST) mbindex_end )
    {

        /* Process Rx event. Clear the rx interrupt flag. */
        Can_LLD_Process_Tx( controller, mbindex_start, mbindex_end );
    }


/*================================================================================================*/
/**
@brief         Process Rx Fifo FrameAvailable events
@details       This function is much faster for handling FrameAvailable interrupt events than Can_Process_Rx, specific to MB (Mapped to MB5).
               This routine is called by:
                - Can_IsrFC##FC##_FrameAv() from Can_Irq.c file.
                - Can_IsrFC##FC##_RxFifoEvents() from Can_Irq.c file.

@param[in]     controller Can controller ID - based on configuration order list (CanControllerId).

@pre           Driver must be initialized.
@post          Rx fifo must be enabled.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
#if (CAN_RXFIFO_ENABLE == STD_ON)

FUNC(void, CAN_CODE) Can_RxFifoFrameAvNotif( CONST(uint8, CAN_CONST) controller)
    {

        /* Process RxFifo frame available event. Clear the rxfifo frame available interrupt flag.*/
        Can_LLD_RxFifoFrameAvNotif( controller);
    }

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/*================================================================================================*/
/**
@brief         Process a message buffer abort
@details       This function write a abort code (b'1001) to MBCS[CODE] field of the MB.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     can_controller controller ID
@param[in]     can_mb message buffer ID

@pre           Driver must be initialized and the current MB transmission should be ready for transmit.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
#if ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON))

FUNC(void, CAN_CODE) Can_AbortMb( VAR(Can_HWObjectCountType, CAN_VAR) Hth )
    {

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test if the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_ABORT_MB, (uint8)CAN_E_UNINIT);
        }
        else
        {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

            Can_LLD_AbortMb(Hth);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

    }

#endif /* ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON)) */


/*================================================================================================*/
/**
@brief         Process a transition from one clock source to another.
@details       This function is configuring Can controllers to run on the same baudrate, but having a different MCU source clock.
               This routine is called by:
                - CanIf or an upper layer according to Autosar requirements.

@param[in]     can_controller controller ID
@param[in]     can_clk_mode clock mode selection
@return        Std_ReturnType Result of the clock switch operation.
@retval        E_OK  Switch clock operation was ok.
@retval        E_NOT_OK  Switch clock operation was not ok.

@pre           Driver must be initialized and all the controllers must be in Stop state.

@remarks       Not AUTOSAR required. This is user implementation.
*/
/*================================================================================================*/
#if (CAN_DUAL_CLOCK_MODE == STD_ON)

FUNC(Std_ReturnType, CAN_CODE) Can_SetClockMode( VAR(uint8, CAN_VAR) can_controller, VAR(Can_ClockMode, CAN_VAR) can_clk_mode)
    {

        VAR(Std_ReturnType, CAN_VAR) Out_can_return = (uint8)E_NOT_OK;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Test if the driver is already initialised. */
        if ( CAN_UNINIT == Can_DriverStatus )
        {
            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SETCLOCKMODE, (uint8)CAN_E_UNINIT);
        }
        else
        {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

            if ( CAN_T_STOP == Can_ControllerStatuses[can_controller].ControllerState )
            {
                Out_can_return = Can_LLD_SetClockMode( can_controller, can_clk_mode);
            }

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

        return (Out_can_return);
    }

#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

#define CAN_STOP_SEC_CODE
/**
@file  Can.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.  - See @ref Can_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_c_REF_2
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
