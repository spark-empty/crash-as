/**
    @file    Icu.c
    @version 2.0.0

    @brief   AUTOSAR Icu - ICU Driver source file.
    @details ICU driver source file, containing the Autosar API specification and other variables
             and functions that are exported by the ICU driver.

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
/*==================================================================================================
==================================================================================================*/

/**
@file    Icu.c
@remarks Implements DICU01001
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_c_1
Violates MISRA-C 2004 Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section Icu_c_2
Violates MISRA-C:2004 Advisory Rule 19.15 Precautions shall be taken in order to prevent the
contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions

@section Icu_c_3
Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.
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
#include "Icu.h"
#include "Icu_LLD.h"
#include "SchM_Icu.h"

#if (ICU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_VENDOR_ID_C         43

#define ICU_AR_MAJOR_VERSION_C  3
#define ICU_AR_MINOR_VERSION_C  0
#define ICU_AR_PATCH_VERSION_C  0
#define ICU_SW_MAJOR_VERSION_C  2
#define ICU_SW_MINOR_VERSION_C  0
#define ICU_SW_PATCH_VERSION_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and ICU header file are of the same vendor */
#if (ICU_VENDOR_ID_C != ICU_VENDOR_ID)
#error "Icu.c and Icu.h have different vendor IDs"
#endif
/* [ICU005]: The integration of incompatible files shall be avoided.
   Minimum implementation is the version check of the header file.
   For included header files:
       ICU_AR_MAJOR_VERSION and ICU_AR_MINOR_VERSION shall be identical.

   For the module internal c and h files:
       ICU_SW_MAJOR_VERSION, ICU_SW_MINOR_VERSION, ICU_AR_MAJOR_VERSION,
       ICU_AR_MINOR_VERSION, ICU_AR_PATCH_VERSION shall be identical.
*/
/**
 @file    Icu.c
 @remarks Covers ICU005
*/
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_AR_MAJOR_VERSION_C != ICU_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION_C != ICU_AR_MINOR_VERSION) || \
         (ICU_AR_PATCH_VERSION_C != ICU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu.c and Icu.h are different"
    #endif
#endif
/* Check if source file and ICU header file are of the same Software version */
#if ((ICU_SW_MAJOR_VERSION_C != ICU_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_C != ICU_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_C != ICU_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu.c and Icu.h are different"
#endif

/* Check if source file and DET header file are of the same version */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((ICU_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (ICU_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Icu.c and Det.h are different"
        #endif
    #endif
/* ICU_DEV_ERROR_DETECT */
#endif 

/* Check if source file and ICU configuration header file are of the same vendor */
#if (ICU_VENDOR_ID_C != ICU_LLD_VENDOR_ID)
    #error "Icu.c and Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Icu_LLD header file are of the same version */
    #if ((ICU_AR_MAJOR_VERSION_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION_C != ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_AR_PATCH_VERSION_C != ICU_LLD_AR_PATCH_VERSION))
    #error "Autosar Version Numbers of Icu.c and Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and Icu_LLD header file are of the same Software Version */
#if ((ICU_SW_MAJOR_VERSION_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_C != ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_C != ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu.c and Icu_LLD.h are different"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and SchM_Icu header file are of the same version */
    #if ((ICU_AR_MAJOR_VERSION_C != SCHM_ICU_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION_C != SCHM_ICU_AR_MINOR_VERSION))
    #error "Autosar Version Numbers of Icu.c and SchM_Icu.h are different"
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
#define ICU_START_SEC_VAR_UNSPECIFIED
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/
/*
@brief Pointer initialized during init with the address of the received configuration structure.
@details Will be used by all functions to access the configuration data.
*/
P2CONST(Icu_ConfigType, ICU_VAR, ICU_APPL_CONST) Icu_Cfg_Ptr = NULL_PTR;

/**
@brief Saves the current Icu mode
*/
volatile VAR(Icu_ModeType, ICU_VAR) Icu_Current_Mode;

/**
@{
@brief   Stores actual state and configuration of ICU Channels
*/
volatile VAR(Icu_ChannelStateType, ICU_VAR) Icu_ChannelState[ICU_MAX_CHANNEL];
/**@}*/

#if (ICU_TIMESTAMP_API == STD_ON)
/**
@brief Pointer to the buffer-array where the timestamp values shall be placed.
*/
P2VAR(Icu_ValueType, ICU_VAR, ICU_APPL_DATA) Icu_Buffer[ICU_MAX_CHANNEL];
/**
@brief Array for saving the size of the external buffer (number of entries)
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_BufferSize[ICU_MAX_CHANNEL];
/**
@brief Array for saving Notification interval (number of events).
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_BufferNotify[ICU_MAX_CHANNEL];
/**
@brief Array for saving the number of notify counts
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_NotifyCount[ICU_MAX_CHANNEL];
/**
@brief Array for saving the time stamp index
*/
volatile VAR(Icu_IndexType, ICU_VAR) Icu_BufferIndex[ICU_MAX_CHANNEL];
/* ICU_TIMESTAMP_API */
#endif 

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/**
@brief Array for saving the period
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_Period[ICU_MAX_CHANNEL];
/**
@brief Array for saving the pulse width of active time
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_ActivePulseWidth[ICU_MAX_CHANNEL];
/* ICU_SIGNAL_MEASUREMENT_API */
#endif 

#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define ICU_START_SEC_CONST_UNSPECIFIED
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#define ICU_STOP_SEC_CONST_UNSPECIFIED
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
@brief      This function initializes the driver.
@details    This service is a non reentrant function used for driver initialization.
        The  Initialization function  shall initialize  all relevant  registers of  the configured
        hardware with the  values of the  structure referenced by  the parameter ConfigPtr.
         If  the  hardware  allows  for   only  one  usage   of  the  register,   the  driver module
         implementing that functionality is responsible for initializing the register.
         The initialization function of this module shall always have a pointer as a parameter, even
         though for Variant PC no configuration set shall be given.
         Instead a NULL pointer shall be passed to the initialization function.
         The Icu  module environment  shall not  call Icu_Init  during a  running operation (e. g.
         timestamp measurement or edge counting).
@param[in]     ConfigPtr        Pointer to a selected configuration structure.
@remarks Covers ICU002, ICU111, ICU220, ICU023, ICU054, ICU060
@remarks Implements DICU20100, DICU01015, DICU10001
*/
/*================================================================================================*/

/* Compiler_Warning : This warning is thrown due to the fact that if ICU_PRECOMPILE_SUPPORT is
   enabled we will not use ConfigPtr */
FUNC (void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{

    VAR(Icu_ChannelType, AUTOMATIC) numChl;
    P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr;
    VAR(Icu_ChannelType, AUTOMATIC) msChannel;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* [ICU220]:   If development  error detection  for the  ICU module  is enabled and the function
    Icu_Init  is called  when the  ICU driver  and hardware  are already  initialized, the  function
    Icu_Init shall raise development error ICU_E_ALREADY_INITIALIZED and return without any  action.
    */
    if (NULL_PTR != Icu_Cfg_Ptr)
    {
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_INIT_ID,
                        (uint8)ICU_E_ALREADY_INITIALIZED);
    }
    else
    {
#ifndef ICU_PRECOMPILE_SUPPORT
        /*  ICU023: If  development error  detection for  the Icu  module is  enabled: The  function
        Icu_Init  shall  check the  parameter  ConfigPtr for  not  being NULL  and  shall raise  the
        development error code ICU_E_PARAM_CONFIG if the check fails
        */
        if (NULL_PTR == ConfigPtr)
        {
            Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_INIT_ID,
                            (uint8)ICU_E_PARAM_CONFIG);
        }
        else
        {
/* !ICU_PRECOMPILE_SUPPORT */        
#endif
/* ICU_DEV_ERROR_DETECT */    
#endif 
            /* Precompile always uses default configuration */
#ifdef ICU_PRECOMPILE_SUPPORT
            Icu_Cfg_Ptr = &Icu_Configs_PC;
#else
            Icu_Cfg_Ptr = ConfigPtr;
/* ICU_PRECOMPILE_SUPPORT */        
#endif 

/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
            for (numChl = 0U; numChl < Icu_Cfg_Ptr->Icu_MaxChannels; numChl++)
            {
                /* [ICU054]: Only the specified  resources that are configured in  the configuration
                file shall be set (including clearing of pending interrupt flags).
                */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
                tempPtr = &Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl];
                msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];
                /* Call low level function */
                Icu_LLD_InitChannel(tempPtr, numChl, msChannel);
            }
            /* [ICU060]: After initialization the module mode shall be ICU_MODE_NORMAL */
            Icu_Current_Mode = ICU_MODE_NORMAL;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
#ifndef ICU_PRECOMPILE_SUPPORT
        }
/* ICU_PRECOMPILE_SUPPORT */    
#endif 
    }
/* ICU_DEV_ERROR_DETECT */    
#endif 
}


#if (ICU_DE_INIT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function de-initializes the ICU module.
@details This service is a Non reentrant function used for ICU De-Initialization
         After the call of this service, the state of the peripherals used by configuration shall be
         the  same as  after power  on reset.  Values of  registers which  are not  writable  are
         excluded.
         This service shall disable all used interrupts and notifications.
         The Icu module environment shall not  call Icu_DeInit during a running  operation  (e. g.
         timestamp measurement or edge counting)
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU091, ICU036
@remarks Implements DICU01002, DICU10002
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_DeInit(void)
{
    VAR(Icu_ChannelType, AUTOMATIC) numChl;
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */

    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */

    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT  is enabled, API parameter checking is  enabled.
    */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DEINIT_ID,
                (uint8)ICU_E_UNINIT);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif 
        /* [ICU091]:  The service  influences only  the peripherals  which are  allocated by  static
        configuration  and/or  the  runtime  configuration  set  passed  by  the  previous  call  of
        Icu_Init().
        */
        /* [ICU036] Leave devices as after power on reset */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        for (numChl = 0U; numChl < Icu_Cfg_Ptr->Icu_MaxChannels; numChl++)
        {
            /* Call low level function */
            Icu_LLD_DeInitChannel(numChl);
        }
        Icu_Cfg_Ptr = NULL_PTR;
        Icu_Current_Mode = ICU_MODE_NORMAL;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif 
}
/* ICU_DE_INIT_API */
#endif 

#if (ICU_SET_MODE_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function sets the ICU mode.
@details This service is a non reentrant function used for ICU mode  selection.
         This service shall  set the  operation mode  to the given mode parameter.
         This service  can be  called during  running operations.  If so,  an ongoing operation that
         generates interrupts on a wakeup capable  channel like e.g. time stamping or  edge counting
         might lead to the  ICU module not being  able to properly enter sleep  mode. This is then a
         system or ECU configuration issue not a problem of this specification.
@param[in]      Mode        Specifies the operation mode
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU095, ICU125, ICU011, ICU012
@remarks Implements DICU01020, DICU10003
*/
/*================================================================================================*/
/*  [ICU095]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_SET_MODE_API.
*/
FUNC (void, ICU_CODE) Icu_SetMode(VAR(Icu_ModeType, AUTOMATIC) Mode)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
       enabled.
    */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_SETMODE_ID,
                        (uint8)ICU_E_UNINIT);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else if ((ICU_MODE_NORMAL != Mode) && (ICU_MODE_SLEEP != Mode))
    {
        /* [ICU125] - If development error detection is enabled, the parameter Mode shall be checked
        by this service.  If Mode is invalid,  then the error ICU_E_PARAM_MODE shall be reported  to
        the Development Error Tracer.
         */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_SETMODE_ID,
                        (uint8)ICU_E_PARAM_MODE);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        if (Icu_Current_Mode != Mode)
        {
            VAR(Icu_ChannelType, AUTOMATIC) numChl;

/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
            for (numChl = 0U; numChl < Icu_Cfg_Ptr->Icu_MaxChannels; numChl++)
            {
                VAR(boolean, AUTOMATIC) active = (boolean)FALSE;

                if (ICU_MODE_SLEEP == Mode)
                {
                    /*
                     * Channels active during ICU_MODE_SLEEP are the ones:
                     *  - configured as wakeup capable
                     *  - enabled via Icu_EnableWakeup() after Icu_Init() and which are not
                     *    disabled via service Icu_DisableWakeup()
                     */
                    active = (boolean)(((Icu_ChannelState[numChl] &
                             ICU_CHANNEL_STATE_WKUP) != 0U) ? TRUE : FALSE);

                    /* Call low level function */
                    Icu_LLD_SetSleepMode(numChl, active);
                }
                else
                {
                    /*
                     *  In ICU_MODE_NORMAL mode all notifications are available as
                     *   - configured by service Icu_SetActivationCondition() or IcuDefaultStartEdge
                     *   - selected by Icu_EnableNotification services before or after the call of
                   Icu_SetMode()
                     */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
                    if (ICU_MODE_SIGNAL_EDGE_DETECT == \
            Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_Channel_Mode)
                    {
                        active = (boolean)(((Icu_ChannelState[numChl] &  \
                                     ICU_CHANNEL_STATE_NOTIFICATION) == \
                             ICU_CHANNEL_STATE_NOTIFICATION) ? TRUE : FALSE);
                    }
                    else
                    {
                        active = (boolean)(((Icu_ChannelState[numChl] &  \
                             ICU_CHANNEL_STATE_RUNNING) == \
                             ICU_CHANNEL_STATE_RUNNING) ? TRUE : FALSE);
                    }

                    /* Call low level function */
                    Icu_LLD_SetNormalMode(numChl, active);
                }

            }

            Icu_Current_Mode = Mode;
        }
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_SET_MODE_API */
#endif 

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function disables the wakeup capability of a single ICU channel.
@details This service is reentrant function and shall disable  the wakeup capability of
         a single ICU channel.This  service is only feasible for ICU channels configured statically
         as wakeup capable true.
         The  function  Icu_DisableWakeup shall  be  pre compile  time  configurable On/Off  by  the
         configuration parameter IcuDisableWakeupApi.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU024, ICU059
@remarks Implements DICU01005, DICU10004
*/
/*================================================================================================*/
/*  This service  shall be  pre compile  time configurable  On/Off by  the configuration  parameter:
ICU_DISABLE_WAKEUP_API.
*/
FUNC (void, ICU_CODE) Icu_DisableWakeup(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error ICU is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEWAKEUP_ID,
                        (uint8)ICU_E_UNINIT);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and  report ICU_E_PARAM_CHANNEL Test for non-wakeup capable  channel
    and report ICU_E_PARAM_CHANNEL
    */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((Channel >= Icu_Cfg_Ptr->Icu_MaxChannels))
    {
        /* [ICU024]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is invalid, then the error ICU_E_PARAM_CHANNEL shall  be
        reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEWAKEUP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((uint32)ICU_WAKEUP_MASK !=  \
             (Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_ParamValue & (uint32)ICU_WAKEUP_MASK))
    {
        /* [ICU059]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is indexing an ICU channel statically not configured  as
        wakeup capable,  then the  error ICU_E_PARAM_CHANNEL  shall be  reported to  the Development
        Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEWAKEUP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        if (ICU_MODE_NORMAL == Icu_Current_Mode)
        {
            /* Call low level function */
            Icu_LLD_DisableWakeup(Channel);
        }
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_DISABLE_WAKEUP_API */
#endif 

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function (re-)enables the wakeup capability of the given ICU channel.
@details The function is reentrant and re-enable the wake-up capability of a single ICU channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The channel must be configured as wakeup capable.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU155, ICU156
@remarks Implements DICU01008, DICU10005
*/
/*================================================================================================*/
/*  This service  shall be  pre compile  time configurable  On/Off by  the configuration  parameter:
ICU_ENABLE_WAKEUP_API.
*/
FUNC (void, ICU_CODE) Icu_EnableWakeup(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEWAKEUP_ID,
                        (uint8)ICU_E_UNINIT);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL
       Test for non-wakeup capable channel and report ICU_E_PARAM_CHANNEL
    */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((Channel >= Icu_Cfg_Ptr->Icu_MaxChannels))
    {
        /* [ICU155]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is invalid, then the error ICU_E_PARAM_CHANNEL shall  be
        reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEWAKEUP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((uint32)ICU_WAKEUP_MASK != \
         (Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_ParamValue & (uint32)ICU_WAKEUP_MASK))
    {
        /* [ICU156]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is indexing an ICU channel statically not configured  as
        wakeup capable,  then the  error ICU_E_PARAM_CHANNEL  shall be  reported to  the Development
        Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEWAKEUP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#else
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    if (0U != (Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_ParamValue & (uint32)ICU_WAKEUP_MASK))
    {
#endif
        /* Only if ICU is wakeup capable, this lines are executed */
        if (ICU_MODE_NORMAL == Icu_Current_Mode)
        {
            /* Call low level function */
            Icu_LLD_EnableWakeup(Channel);
        }
#if (ICU_DEV_ERROR_DETECT == STD_OFF)
    }
#else
    }
#endif

}
/* ICU_ENABLE_WAKEUP_API */
#endif 

/*================================================================================================*/
/**
@brief   This function sets the activation-edge for the given channel.
@details This service  is reentrant and shall set  the  activation-edge according to Activation
         parameter for the given channel.
         This service shall support channels which are configured
         for  the following Icu_MeasurementMode:
         - ICU_MODE_SIGNAL_EDGE_DETECT
         - ICU_MODE_TIMESTAMP
         - ICU_MODE_EDGE_COUNTER
@param[in]     Channel          Numeric identifier of the ICU channel
@param[in]     Activation       Type of activation.
@pre Icu_Init must be called before.
@pre The channel must be properly configured (ICU_MODE_SIGNAL_EDGE_DETECT,
     ICU_MODE_TIMESTAMP, ICU_MODE_EDGE_COUNTER).
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU159, ICU043
@remarks Implements DICU01019, DICU10006
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_SetActivationCondition(VAR(Icu_ChannelType, AUTOMATIC) Channel,
                                                 VAR(Icu_ActivationType, AUTOMATIC) Activation)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* If Development  Error Detection is  enabled, report error  Icu is uninitialized  is passed as
       a NULL Pointer
     */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_SETACTIVATIONCONDITION_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU159]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is invalid, then the error ICU_E_PARAM_CHANNEL shall  be
        reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_SETACTIVATIONCONDITION_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid mode and report ICU_E_PARAM_MODE */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (((ICU_RISING_EDGE != Activation) && (ICU_FALLING_EDGE != Activation) && 
              (ICU_BOTH_EDGES != Activation)) || (ICU_MODE_SIGNAL_MEASUREMENT == \
               Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode))
    {
        /* [ICU043] - If development error  detection is enabled, the parameter Activation  shall be
        checked by  this service.   If Mode  is invalid,  then the  error ICU_E_PARAM_MODE  shall be
        reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_SETACTIVATIONCONDITION_ID,
                        (uint8)ICU_E_PARAM_ACTIVATION);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        /* Call low level function */
        Icu_LLD_SetActivationCondition(Channel, Activation);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

/*================================================================================================*/
/**
@brief   This function disables the notification of a channel.
@details This function is reentrant and disables the notification of a channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU160
@remarks Implements DICU01004, DICU10007
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_DisableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
       enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLENOTIFICATION_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU160]: If development error detection is enabled: The function Icu_DisableNotification
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLENOTIFICATION_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((ICU_MODE_SIGNAL_EDGE_DETECT != \
              Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode) &&
             (ICU_MODE_TIMESTAMP != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode))
    {
        /* [ICU160]: If development error detection is enabled: The function Icu_DisableNotification
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLENOTIFICATION_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        /* Call low level function */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        Icu_LLD_DisableNotification(Channel,
        (boolean)((Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode != \
        ICU_MODE_TIMESTAMP) ? TRUE : FALSE));

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

/*================================================================================================*/
/**
@brief   This function enables the notification on the given channel.
@details This function is reentrant and enables the notification on the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU161
@remarks Implements DICU01007, DICU10008
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_EnableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLENOTIFICATION_ID,
                        (uint8)ICU_E_UNINIT);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU161]: If development error detection is enabled: The function Icu_DisableNotification
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLENOTIFICATION_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((ICU_MODE_SIGNAL_EDGE_DETECT != \
              Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode) &&
             (ICU_MODE_TIMESTAMP != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode))
    {
        /* [ICU161]: If development error detection is enabled: The function Icu_DisableNotification
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLENOTIFICATION_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        /* Call low level function */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic.  See @ref Icu_c_3
*/
        Icu_LLD_EnableNotification(Channel,
        (boolean)((Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode != \
        ICU_MODE_TIMESTAMP) ? TRUE : FALSE));

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function returns the status of the ICU input.
@details This service is reentrant shall return the status of  the ICU input.
         Only channels which are configured for the following Icu_MeasurementMode shall be
         supported:
         - ICU_MODE_SIGNAL_EDGE_DETECT,
         - ICU_MODE_SIGNAL_MEASUREMENT.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_InputStateType
         - ICU_ACTIVE: An activation edge has been detected
         - ICU_IDLE: No activation edge has been detected since the last call of
                    Icu_GetInputState() or Icu_Init().
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU162
@remarks Implements DICU01011, DICU10009
*/
/*================================================================================================*/
/*  [ICU122]:This  service  shall be  pre  compile  time configurable  On/Off  by  the configuration
parameter: ICU_GET_INPUT_STATE_API.
*/
FUNC (Icu_InputStateType, ICU_CODE) Icu_GetInputState(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_InputStateType, AUTOMATIC) tempReturn = ICU_IDLE;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch  ICU_DEV_ERROR_DETECTshall activate  or deactivate  the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETINPUTSTATE_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU049] - If development error detection is enabled and an error is detected the service
        returns ICU_IDLE.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL
       Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL
    */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU162]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is invalid (invalid channel or channel not configured as
        ICU_MODE_SIGNAL_EDGE_DETECT     or    ICU_MODE_SIGNAL_MEASUREMENT,     then    the     error
        ICU_E_PARAM_CHANNEL shall be reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETINPUTSTATE_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU049] - If development error detection is enabled and an error is detected the service
        returns ICU_IDLE.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if ((ICU_MODE_SIGNAL_EDGE_DETECT !=  \
              Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode) &&
             (ICU_MODE_SIGNAL_MEASUREMENT !=  \
              Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode ))
    {
        /* [ICU162]  - If  development error  detection is  enabled, the  parameter Channel shall be
        checked by this service. If Channel is invalid (invalid channel or channel not configured as
        ICU_MODE_SIGNAL_EDGE_DETECT     or    ICU_MODE_SIGNAL_MEASUREMENT,     then    the     error
        ICU_E_PARAM_CHANNEL shall be reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETINPUTSTATE_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU049] - If development error detection is enabled and an error is detected the service
        returns ICU_IDLE.
        */
    }
    else
    {
#endif

        /* Call low level function */
        tempReturn = Icu_LLD_GetInputState(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
    return (tempReturn);
}
/* ICU_GET_INPUT_STATE_API */
#endif 

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function starts the capturing of timer values on the edges.
@details This function is reentrant and starts the capturing of timer values on the edges activated
         by the service Icu_SetActivationCondition() to an external buffer.
@param[in]     Channel          Numeric identifier of the ICU channel
@param[in]     BufferPtr        Pointer to the buffer-array where the timestamp values shall be
                                placed.
@param[in]     BufferSize       Size of the external buffer (number of entries)
@param[in]     NotifyInterval   Notification interval (number of events).
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU163, ICU120, ICU108
@remarks Implements DICU01022, DICU10010
*/
/*================================================================================================*/
/*  This service  shall be  pre compile  time configurable  On/Off by  the configuration  parameter:
ICU_TIMESTAMP_API.
*/
FUNC (void, ICU_CODE) Icu_StartTimestamp(VAR(Icu_ChannelType, AUTOMATIC) Channel,
        P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
        VAR(uint16, AUTOMATIC) BufferSize,
        VAR(uint16, AUTOMATIC) NotifyInterval)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTTIMESTAMP_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL
       Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL
    */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)

    {
        /* [ICU163]:  If development  error detection  is enabled:  The function  Icu_StartTimestamp
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier or channel not configured for mode ICU_MODE_TIMESTAMP).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_TIMESTAMP != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU163]:  If development  error detection  is enabled:  The function  Icu_StartTimestamp
        shall check the parameter Channel and  shall raise the error ICU_E_PARAM_CHANNEL if  Channel
        is invalid (invalid identifier or channel not configured for mode ICU_MODE_TIMESTAMP).
        */

        /* This service shall only be available in Measurement Mode "ICU_MODE_TIMESTAMP" */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else if (NULL_PTR == BufferPtr)
    {
        /* [ICU120] - If  development error detection is  enabled, the parameter BufferPtr  shall be
        checked  by  this   service.   If  BufferPtr   is  invalid  (e.g.   "0"),  then  the   error
        ICU_E_PARAM_BUFFER_PTR shall be reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_BUFFER_PTR);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else if ((uint16)0U == BufferSize)
    {
        /* [ICU108] - If development error  detection is enabled, the parameter BufferSize  shall be
        checked  by  this   service.  If  BufferSize   is  invalid  (e.g.   "0"),  then  the   error
        ICU_E_PARAM_BUFFER_SIZE shall be reported to the Development Error Tracer.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_BUFFER_SIZE);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        VAR(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[Channel];

        /* Call low level function */
        Icu_LLD_StartTimestamp(Channel, msChannel, BufferPtr, BufferSize, NotifyInterval);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function stops the timestamp measurement of the given channel.
@details This function is reentrant and stops the timestamp measurement of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU164, ICU166
@remarks Implements DICU01024, DICU10011
*/
/*================================================================================================*/
/*  This service  shall be  pre compile  time configurable  On/Off by  the configuration  parameter:
ICU_TIMESTAMP_API.
*/
FUNC (void, ICU_CODE) Icu_StopTimestamp(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPTIMESTAMP_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU164]: If development error detection is enabled: The function Icu_StopTimestamp shall
        check the parameter Channel and shall raise development error ICU_E_PARAM_CHANNEL if Channel
        is invalid (invalid identifier or channel not configured for mode ICU_MODE_TIMESTAMP)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_TIMESTAMP != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU164]: If development error detection is enabled: The function Icu_StopTimestamp shall
        check the parameter Channel and shall raise development error ICU_E_PARAM_CHANNEL if Channel
        is invalid (invalid identifier or channel not configured for mode ICU_MODE_TIMESTAMP)
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPTIMESTAMP_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for channel not started */

    else if (Icu_LLD_Channel_Get_Status(Channel)==(boolean)FALSE)
    {
        /* [ICU166]: If development error detection is enabled: The function Icu_StopTimestamp shall
        raise development error ICU_E_NOT_STARTED if Channel is  not active ( has not started or  is
        already stopped).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPTIMESTAMP_ID,
                        (uint8)ICU_E_NOT_STARTED);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif 
        /* Call low level function */
        Icu_LLD_StopTimestamp(Channel);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif 
}
/* ICU_TIMESTAMP_API */
#endif 

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the timestamp index of the given channel.
@details This function reentrant and reads the timestamp index of the given channel,
         which is next to be written.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_IndexType - Timestamp index of the given channel
@pre Icu_Init must be called before.
@pre Icu_StartTimestamp must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU169, ICU107, ICU004
@remarks Implements DICU01013, DICU10012
*/
/*================================================================================================*/
/*  [ICU100]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_TIMESTAMP_API.
*/
FUNC (Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_IndexType, AUTOMATIC) tempIndex = 0U;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMESTAMPINDEX_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* ICU169: If  development error detection  is enabled: the  function Icu_GetTimestamp shall
        check  the parameter  Channel. If  Channel is  invalid (invalid  identifier or  channel  not
        configured  for   mode   Icu_GetTimestamp),   the  function   Icu_GetTimeStamp  shall  raise
        development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMESTAMPINDEX_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_TIMESTAMP != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* ICU169: If  development error detection  is enabled: the  function Icu_GetTimestamp shall
        check  the parameter  Channel. If  Channel is  invalid (invalid  identifier or  channel not
        configured for mode Icu_GetTimestamp), the function Icu_GetTimeStamp shall raise development
        error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMESTAMPINDEX_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
#if (!defined(ICU_OVERFLOW_NOTIFICATION_API)) || (ICU_OVERFLOW_NOTIFICATION_API == STD_OFF)
    else if (Icu_LLD_Get_Overflow(Channel))
    {
        /*  [ICU004]:Additional errors that are  detected because of specific implementation  and/or
        specific  hardware properties  shall be  added in  the ICU  device specific  implementation
        specification. The classification and enumeration shall be compatible with the errors listed
        above.
         */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMESTAMPINDEX_ID,
                        (uint8)ICU_E_TIMESTAMP_OVERFLOW);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
/* ICU_OVERFLOW_NOTIFICATION_API == STD_OFF */   
#endif  
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif  
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        VAR(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[Channel];
        tempIndex = Icu_LLD_GetTimestampIndex(msChannel);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif  
    return (tempIndex);
}
/* ICU_TIMESTAMP_API */
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function resets the value of the counted edges to zero.
@details This function is reentrant and resets the value of the counted edges to zero.
@param[in]     Channel          Numeric identifier of the ICU channel.
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU171
@remarks Implements DICU01018, DICU10013
*/
/*================================================================================================*/
/*  [ICU101]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_EDGE_COUNT_API.
*/
FUNC (void, ICU_CODE) Icu_ResetEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
     */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_RESETEDGECOUNT_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU171]:  If development  error detection  is enabled:  the function  Icu_ResetEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for mode ICU_MODE_EDGE_COUNTER), then Icu_ResetEdgeCount shall raise  development
        error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_RESETEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error */
        /* is detected the desired functionality shall be skipped and the */
        /* requested service is left without any action. */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_EDGE_COUNTER != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU171]:  If development  error detection  is enabled:  the function  Icu_ResetEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for mode ICU_MODE_EDGE_COUNTER), then Icu_ResetEdgeCount shall raise  development
        error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_RESETEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        /* Call low level function */
        Icu_LLD_ResetEdgeCount(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function enables the counting of edges of the given channel.
@details This service is reentrant and shall enable the counting of  edges of the given channel.
         Note: This  service doesnot do the real counting itself. This is done by the hardware
         (capture unit). Only the configured edges shall be counted (rising edge / falling edge /
         both edges).

         Configuration  of  the  edge  is  done  in  Icu_Init  or  Icu_SetActivationCondition.   The
         configured edge can be  changed during runtime using  Icu_SetActivationCondition.Interrupts
         are not required for edge counting.If interrupts are enabled, the interrupt service routine
         will set the overflow flag if more than 0xFFFFFF edges are measured.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU172
@remarks Implements DICU01006, DICU10014
*/
/*================================================================================================*/
/*  [ICU102]:  This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_EDGE_COUNT_API.
*/
FUNC (void, ICU_CODE) Icu_EnableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEEDGECOUNT_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* This service shall be available for each ICU channel in Measurement Mode "Edge Counter".*/
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU172]:  If development  error detection  is enabled,  the function Icu_EnableEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for  mode  ICU_MODE_EDGE_COUNTER),  then the  function Icu_EnableEdgeCount  shall
        raise development error ICU_E_PARAM_CHANNEL
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_EDGE_COUNTER != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU172]:  If development  error detection  is enabled,  the function Icu_EnableEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured  for mode  ICU_MODE_EDGE_COUNTER), then  the function  Icu_EnableEdgeCount shall
        raise development error ICU_E_PARAM_CHANNEL
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_ENABLEEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        Icu_LLD_EnableEdgeCount(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_EDGE_COUNT_API */
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function disables the counting of edges of the given channel.
@details This function is reentrant and disables the counting of edges of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU173
@remarks Implements DICU01003, DICU10015
*/
/*================================================================================================*/
/*[ICU103]:   This  service shall  be  pre compile  time  configurable On/Off  by  the configuration
parameter: ICU_EDGE_COUNT_API.
*/
FUNC (void, ICU_CODE) Icu_DisableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEEDGECOUNT_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU173]: If  development error detection  is enabled: the  function Icu_DisableEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for mode  ICU_MODE_EDGE_COUNTER), the function Icu_DisableEdgeCount  shall  raise
        development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_EDGE_COUNTER != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU173]: If  development error detection  is enabled: the  function Icu_DisableEdgeCount
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for  mode ICU_MODE_EDGE_COUNTER),  the function  Icu_DisableEdgeCount shall raise
        development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_DISABLEEDGECOUNT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error */
        /* is detected the desired functionality shall be skipped and the */
        /* requested service is left without any action. */
    }
    else
    {
#endif
        Icu_LLD_DisableEdgeCount(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_EDGE_COUNT_API */
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the number of counted edges.
@details This function is reentrant reads the number of counted edges after the last call
         of Icu_ResetEdgeCount().
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_EdgeNumberType - Number of the counted edges.
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU107, ICU174, ICU175, ICU004
@remarks Implements DICU01010, DICU10016
*/
/*================================================================================================*/
/*  [ICU104]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_EDGE_COUNT_API.
*/
FUNC (Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_EdgeNumberType, AUTOMATIC) tempEdge = 0U;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error
        detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETEDGENUMBERS_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU174]:  If development  error detection  is enabled,  the function  Icu_GetEdgeNumbers
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured  for mode  ICU_MODE_EDGE_COUNTER), the  function Icu_GetEdgeNumbers  shall raise
        development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETEDGENUMBERS_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
        /* [ICU107] - If development error detection is enabled and an
         error is detected this service shall return "0".
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_EDGE_COUNTER != Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU174]:  If development  error detection  is enabled,  the function  Icu_GetEdgeNumbers
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured for  mode  ICU_MODE_EDGE_COUNTER),  the function  Icu_GetEdgeNumbers  shall raise
        development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETEDGENUMBERS_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
        /* [ICU175]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
#if (!defined(ICU_OVERFLOW_NOTIFICATION_API)) || (ICU_OVERFLOW_NOTIFICATION_API == STD_OFF)
    /* If counter rolls over, report an error */
    else if (Icu_LLD_Get_Overflow(Channel))
    {
        /*  [ICU004]:Additional errors that are  detected because of specific implementation  and/or
        specific  hardware properties  shall be  added in  the ICU  device specific  implementation
        specification. The classification and enumeration shall be compatible with the errors listed
        above.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETEDGENUMBERS_ID,
                        (uint8)ICU_E_EDGECOUNTING_OVERFLOW);
    }
/* ICU_OVERFLOW_NOTIFICATION_API == STD_OFF */    
#endif  
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif  

        tempEdge = Icu_LLD_GetEdgeNumbers(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif  

    return (tempEdge);
}
/* ICU_EDGE_COUNT_API */
#endif 

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function starts the measurement of signals.
@details This service is reentrant and starts the measurement of signals beginning with the
         configured default start edge which occurs first after the call of this service.
         This service shall only be available in Measurement Mode ICU_MODE_SIGNAL_MEASUREMENT.
         This service shall reset the state for the given channel to ICU_IDLE.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU176
@remarks Implements DICU01021, DICU10017
*/
/*================================================================================================*/
/*  [ICU142]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_SIGNAL_MEASUREMENT_API.
*/
FUNC (void, ICU_CODE) Icu_StartSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_ChannelType, AUTOMATIC) tempChannel;
    VAR(Icu_ChannelType, AUTOMATIC) msChannel;
    VAR(Icu_ParamType, AUTOMATIC) tempProperty;
    P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch     ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* This service shall be available for each ICU channel in Measurement Mode "Signal
       Measurement". */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU176]:    If    development    error    detection    is    enabled,    the    function
        Icu_StartSignalMeasurement shall check the parameter Channel. If Channel is invalid (invalid
        identifier or channel  not configured for  mode  ICU_MODE_SIGNAL_MEASUREMENT), the  function
        Icu_StartSignalMeasurement shall raise development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_SIGNAL_MEASUREMENT != \
             Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU176]:    If    development    error    detection    is    enabled,    the    function
        Icu_StartSignalMeasurement shall check the parameter Channel. If Channel is invalid (invalid
        identifier or channel  not configured for  mode  ICU_MODE_SIGNAL_MEASUREMENT), the  function
        Icu_StartSignalMeasurement shall raise development error ICU_E_PARAM_CHANNEL.
        */

        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STARTSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        tempPtr = &Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel];
        tempChannel = Icu_Cfg_Ptr->Icu_ChannelId[Channel];
        tempProperty = tempPtr->Icu_Channel_Property;
        msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[Channel];

        /* Call low level function */
        Icu_LLD_StartSignalMeasurement(tempPtr, tempChannel, tempProperty, msChannel, Channel);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif 

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function stops the measurement of signals of the given channel.
@details This function is reentrant and stops the measurement of signals of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU177
@remarks Implements DICU01023, DICU10018
*/
/*================================================================================================*/
/*  [ICU145]: This  service shall  be pre  compile time  configurable On/Off  by the  configuration
parameter: ICU_SIGNAL_MEASUREMENT_API.
*/
FUNC (void, ICU_CODE) Icu_StopSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development Error Detection is enabled, report error Icu is uninitialized */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error
         detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL
       This service shall be available for each ICU channel in Measurement Mode "Signal
       Measurement".
    */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /*    [ICU177]:    If   development    error    detection   is    enabled:    the   function
        Icu_StopSignalMeasurement shall check the parameter Channel. If Channel is invalid  (invalid
        identifier or  channel not  configured for  mode ICU_MODE_SIGNAL_MEASUREMENT),  the function
        Icu_StopSignalMeasurement shall raise development error  ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the
         requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_SIGNAL_MEASUREMENT !=
             Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /*    [ICU177]:    If   development    error    detection   is    enabled:    the   function
        Icu_StopSignalMeasurement shall check the parameter Channel. If Channel is invalid  (invalid
        identifier or  channel not  configured for  mode ICU_MODE_SIGNAL_MEASUREMENT),  the function
        Icu_StopSignalMeasurement shall raise development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_STOPSIGNALMEASUREMENT_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
    {
#endif
        /* Call low level function */
        Icu_LLD_StopSignalMeasurement(Channel);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif 

#if (ICU_GET_TIME_ELAPSED_API== STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the elapsed Signal Low/High/Period Time for the given channel.
@details This service is reentrant and reads the elapsed Signal Low Time for the given channel
         that is configured  in Measurement Mode Signal Measurement, Signal Low Time.
         The elapsed time is measured between a falling edge and the consecutive rising edge of  the
         channel.
         This service reads the elapsed Signal High Time for the given channel that is configured in
         Measurement Mode Signal Measurement,Signal High Time.The elapsed time is measured between
         a rising edge and the consecutive falling edge of the channel.
         This service reads the elapsed Signal Period Time for the given channel that is  configured
         in Measurement Mode Signal Measurement,  Signal Period Time.The elapsed time  is measured
         between consecutive  rising (or  falling) edges  of the  channel. The  period start edge is
         configurable.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_ValueType - The elapsed Signal Low Time for the given channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU107, ICU178, ICU004, ICU179, ICU136
@remarks Implements DICU01012, DICU10019
*/
/*================================================================================================*/
/*  [ICU105]:This  service  shall be  pre  compile  time configurable  On/Off  by  the configuration
parameter: ICU_GET_TIME_ELAPSED_API.
*/
FUNC (Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_ValueType, AUTOMATIC) tempValue = (Icu_ValueType)0U;


    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development  Error Detection is  enabled, report error  Icu is uninitialized  is passed
    as a NULL Pointer
    */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMEELAPSED_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU178]:   If development  error detection  is enabled,  the parameter  Channel shall be
        checked by this service. If Channel is invalid (invalid identifier or channel not configured
        for mode ICU_MODE_SIGNAL_MEASUREMENT), then the error ICU_E_PARAM_CHANNEL shall be  reported
        to the Development Error Tracer
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMEELAPSED_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_SIGNAL_MEASUREMENT != \
             Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU178]:   If development  error detection  is enabled,  the parameter  Channel shall be
        checked by this service. If Channel is invalid (invalid identifier or channel not configured
        for mode ICU_MODE_SIGNAL_MEASUREMENT), then the error ICU_E_PARAM_CHANNEL shall be  reported
        to the Development Error Tracer
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMEELAPSED_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
        */
    }
#if (!defined(ICU_OVERFLOW_NOTIFICATION_API)) || (ICU_OVERFLOW_NOTIFICATION_API == STD_OFF)
    else if (Icu_LLD_Get_Overflow(Channel))
    {
        /*  [ICU004]:Additional errors that are  detected because of specific implementation  and/or
        specific  hardware properties  shall be  added in  the ICU  device specific  implementation
        specification. The classification and enumeration shall be compatible with the errors listed
        above.
         */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETTIMEELAPSED_ID,
                        (uint8)ICU_E_MEASUREMENT_OVERFLOW);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
         */

        /* [ICU179]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
         */
    }
/* ICU_OVERFLOW_NOTIFICATION_API == STD_OFF */    
#endif  
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif  
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        if (ICU_DUTY_CYCLE != (Icu_SignalMeasurementPropertyType) \
            Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Property)
        {
            /* [ICU136]: The function Icu_GetTimeElapsed shall return "0" in case
                 -no requested time has been captured (see Figure 9.19, letter "A")
                 -the capturing of a requested time is ongoing and not finished (see Figure 9.19,
                  letter "B")
                 -a captured time was already returned once  by this service and this service is
                  called again (see Figure 9.19, letter "D")
             */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
            VAR(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[Channel];

            SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_00);
            {
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
                if (ICU_PERIOD_TIME == (Icu_SignalMeasurementPropertyType) \
                    Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Property)
                {
                    tempValue = Icu_Period[msChannel];
                    Icu_Period[msChannel] = (Icu_ValueType)0U;
                }
                else
                {
                    tempValue = Icu_ActivePulseWidth[msChannel];
                    Icu_ActivePulseWidth[msChannel] = (Icu_ValueType)0U;
                }
            }
            SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_00);
        }
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif  

    return (tempValue);
}
/* ICU_GET_TIME_ELAPSED_API */
#endif 

#if (ICU_GET_DUTY_CYCLE_VALUES_API== STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the coherent active time and period time for the given ICU Channel.
@details The function is reentrant and reads the coherent active time and period time for
         the given ICU Channel, if it is configured in Measurement Mode Signal Measurement, Duty
         Cycle Values.
@param[in]     Channel          Numeric identifier of the ICU channel
@param[out]    DutyCycleValues  Pointer to a buffer where the results (high time and period time)
                                shall be placed.
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement, Duty Cycle Values.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU180, ICU107, ICU004, ICu181, ICU137
@remarks Implements DICU01009, DICU10020
*/
/*================================================================================================*/
/*  [ICU106]:This  service  shall be  pre  compile  time configurable  On/Off  by  the configuration
parameter: ICU_GET_DUTY_CYCLE_VALUES_API
*/
FUNC (void, ICU_CODE) Icu_GetDutyCycleValues(VAR(Icu_ChannelType, AUTOMATIC) Channel,
        P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues)
{
    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is
    enabled. */
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    /* If Development  Error Detection is  enabled, report error  Icu is uninitialized  is passed
    as a NULL Pointer
    */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETDUTYCYCLEVALUES_ID,
                        (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    /* Test for invalid channel and report ICU_E_PARAM_CHANNEL */
    /* Test if channel is not configured for proper mode and report ICU_E_PARAM_CHANNEL */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic.  See @ref Icu_c_3
*/
    else if (Channel >= Icu_Cfg_Ptr->Icu_MaxChannels)
    {
        /* [ICU180]: If development error detection is enabled: the function  Icu_GetDutyCycleValues
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured  for   mode  ICU_MODE_SIGNAL_MEASUREMENT,   Duty  Cycle   Values),  the  function
        Icu_GetDutyCycleValues shall raise development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0, (uint8)ICU_GETDUTYCYCLEVALUES_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
    else if (ICU_MODE_SIGNAL_MEASUREMENT != \
             Icu_Cfg_Ptr->Icu_ChannelConfigPtr[Channel].Icu_Channel_Mode)
    {
        /* [ICU180]: If development error detection is enabled: the function  Icu_GetDutyCycleValues
        shall check the parameter Channel. If Channel is invalid (invalid identifier or channel  not
        configured  for   mode  ICU_MODE_SIGNAL_MEASUREMENT,   Duty  Cycle   Values),  the  function
        Icu_GetDutyCycleValues shall raise development error ICU_E_PARAM_CHANNEL.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETDUTYCYCLEVALUES_ID,
                        (uint8)ICU_E_PARAM_CHANNEL);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else if (NULL_PTR == DutyCycleValues)
    {
        /* [ICU181]: If development error detection is enabled, the function  Icu_GetDutyCycleValues
        shall check the parameter DutyCycleValues.
        If DutyCycleValues is invalid,  the function Icu_GetDutyCycleValues shall  raise development
        error ICU_E_PARAM_BUFFER_PTR.
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETDUTYCYCLEVALUES_ID,
                        (uint8)ICU_E_PARAM_BUFFER_PTR);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
#if (!defined(ICU_OVERFLOW_NOTIFICATION_API)) || (ICU_OVERFLOW_NOTIFICATION_API == STD_OFF)
    else if (Icu_LLD_Get_Overflow(Channel))
    {
        /*  [ICU004]:Additional errors that are  detected because of specific implementation  and/or
        specific  hardware properties  shall be  added in  the ICU  device specific  implementation
        specification. The classification and enumeration shall be compatible with the errors listed
        above.
         */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, (uint8)ICU_GETDUTYCYCLEVALUES_ID,
                        (uint8)ICU_E_MEASUREMENT_OVERFLOW);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
         */

        /* [ICU107]  - If  development error  detection is  enabled and  an error  is detected  this
        service shall return "0".
         */
    }
/* ICU_OVERFLOW_NOTIFICATION_API == STD_OFF */    
#endif  
    else
    {
/* ICU_DEV_ERROR_DETECT */    
#endif  
        /* [ICU137]: The function Icu_GetDutyCycleValues shall return "0" in case
         -no coherent active- and period time has been captured (similar to Figure 9.19, letter "A")
         -the capturing of a  requested high- and period  time is ongoing  and  not finished (meant:
         the function  shall return  "0" until  the first   valid value  has been  captured and  the
         captured value  shall be  stored until  a new  value is  captured) (similar to Figure 9.19,
         letter "B")
         -captured duty cycle values were already returned once by this service and this service  is
         called again (similar to Figure 9.19, letter "D")
         */
/**
@note  Violates MISRA-C:2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_c_3
*/
        VAR(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[Channel];

        SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_01);
        {
            if ((Icu_ValueType)0U != Icu_Period[msChannel])
            {
                DutyCycleValues->ActiveTime     = (Icu_ValueType)Icu_ActivePulseWidth[msChannel];
                DutyCycleValues->PeriodTime     = (Icu_ValueType)Icu_Period[msChannel];
                Icu_ActivePulseWidth[msChannel] = (Icu_ValueType)0U;
                Icu_Period[msChannel]           = (Icu_ValueType)0U;
            }
            else
            {
                DutyCycleValues->ActiveTime = (Icu_ValueType)0U;
                DutyCycleValues->PeriodTime = (Icu_ValueType)0U;
            }
        }
        SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_01);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    }
/* ICU_DEV_ERROR_DETECT */    
#endif  
}
/* ICU_GET_DUTY_CYCLE_VALUES_API */
#endif 

#if (ICU_GET_VERSION_INFO_API == STD_ON)
/*================================================================================================*/
/**
@brief   This service returns the version information of this module.
@details This  service is Non reentrant and returns the version information of this module.
         The version information includes:
         - Module Id
         - Vendor Id
         - Vendor specific version numbers
         If source code for caller and callee of this function is available this function should  be
         realized as a macro. The macro should be defined in the modules header file.
@param[out]    versioninfo      Pointer to location to store version info
@remarks Covers ICU005
@remarks Implements DICU01014
*/
/*================================================================================================*/
FUNC(void, ICU_CODE) Icu_GetVersionInfo(
                                   P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo)
{
    (versioninfo)->vendorID         = (uint16)ICU_VENDOR_ID;
    (versioninfo)->moduleID         = (uint8)ICU_MODULE_ID;
    (versioninfo)->instanceID       = (uint8)0U;
    (versioninfo)->sw_major_version = (uint8)ICU_SW_MAJOR_VERSION;
    (versioninfo)->sw_minor_version = (uint8)ICU_SW_MINOR_VERSION;
    (versioninfo)->sw_patch_version = (uint8)ICU_SW_PATCH_VERSION;
}
/* ICU_GET_VERSION_INFO_API == STD_ON */
#endif  

#define ICU_STOP_SEC_CODE
/**
@file  Icu.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header
       file being included twice See @ref Icu_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif


/* End of file */
