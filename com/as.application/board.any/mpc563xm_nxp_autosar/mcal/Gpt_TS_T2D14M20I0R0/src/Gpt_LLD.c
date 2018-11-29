/**
    @file    Gpt_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver source file.
    @details GPT driver source file, containing the C implementation of functions prototypes that:
             - are Autosar specific and are not exported by the GPT driver.
             - are not related to the GPT driver related IPs.
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200_Stm_PitRti
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

@section GPT_LLD_C_REF1
MISRA-C:2004   19.1:  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
    statements and comments before '#include'
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003.

@section GPT_LLD_C_REF2
    MISRA-C:2004   19.15:  Repeated include file
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003.

 @section GPT_LLD_C_REF3
   MISRA-C:2004  17.4: pointer arithmetic other than array indexing used
   This violation is due to the use of pointer arithmatic, which is used for the speed optimization,
   the indexing of the pointer is taken care and hence the unintended memory location will not be
   accessed.
    
@section GPT_LLD_C_REF4
    MISRA-C:2004   13.6: for loop index variable is modified in body of the for loop. 
    This violation is due to the modification of channelIndex variable inside the for loop which is
    necessary to break the loop when the GPT channel is configured as wakeup enabled channel.  

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
/**
@remarks Implements DGPT11038,DGPT11042,DGPT11045,DGPT11047,DGPT11033,DGPT11055
*/
#include "Gpt.h"
#include "Gpt_LLD.h"
#include "eMIOS_Gpt_LLD.h"
#include "Reg_eSys_EMIOS.h"
#include "Stm_Gpt_LLD.h"
#include "Reg_eSys_STM.h"
#include "PitRti_Gpt_LLD.h"
#include "Reg_eSys_PITRTI.h"
#include "Cer.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_LLD_VENDOR_ID           43
#define GPT_LLD_AR_MAJOR_VERSION_C  3
#define GPT_LLD_AR_MINOR_VERSION_C  0
#define GPT_LLD_AR_PATCH_VERSION_C  0
#define GPT_LLD_SW_MAJOR_VERSION_C  2
#define GPT_LLD_SW_MINOR_VERSION_C  0
#define GPT_LLD_SW_PATCH_VERSION_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (GPT_LLD_VENDOR_ID != GPT_VENDOR_ID)
    #error "Gpt_LLD.c and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != GPT_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != GPT_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and Gpt.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and Gpt.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != GPT_LLD_VENDOR_ID)
    #error "Gpt_LLD.c and Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and Gpt_LLD.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and Gpt_LLD.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != EMIOS_GPT_LLD_VENDOR_ID)
    #error "Gpt_LLD.c and eMios_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != EMIOS_GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != EMIOS_GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != EMIOS_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and eMios_Gpt_LLD.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != EMIOS_GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != EMIOS_GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != EMIOS_GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and eMios_Gpt_LLD.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != STM_GPT_LLD_VENDOR_ID)
    #error "Gpt_LLD.c and Stm_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != STM_GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != STM_GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != STM_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and Stm_Gpt_LLD.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != STM_GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != STM_GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != STM_GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and Stm_Gpt_LLD.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != PITRTI_GPT_LLD_VENDOR_ID)
    #error "Gpt_LLD.c and PitRti_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != PITRTI_GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != PITRTI_GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != PITRTI_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and PitRti_Gpt_LLD.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != PITRTI_GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != PITRTI_GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != PITRTI_GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and PitRti_Gpt_LLD.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "Gpt_LLD.c and Reg_eSys_EMIOS.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
     (GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
     (GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Gpt_LLD.c and Reg_eSys_EMIOS.h are different"
#endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Sofware Version Numbers of Gpt_LLD.c and Reg_eSys_EMIOS.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != REG_ESYS_STM_VENDOR_ID)
    #error "Gpt_LLD.c and Reg_eSys_STM.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_STM_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_STM_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_STM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and Reg_eSys_STM.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_STM_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_STM_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_STM_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and Reg_eSys_STM.h are different"
#endif

#if (GPT_LLD_VENDOR_ID != REG_ESYS_PITRTI_VENDOR_ID)
    #error "Gpt_LLD.c and Reg_eSys_PITRTI.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_PITRTI_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_PITRTI_AR_MINOR_VERSION) || \
         (GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_PITRTI_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.c and Reg_eSys_PITRTI.h are different"
    #endif
#endif
#if ((GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_PITRTI_SW_MAJOR_VERSION) || \
     (GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_PITRTI_SW_MINOR_VERSION) || \
     (GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_PITRTI_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_LLD.c and Reg_eSys_PITRTI.h are different"
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
#define GPT_START_SEC_VAR_UNSPECIFIED
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
/**
@brief Array of data structure elements storing timeout, channel mode, wakeup and notification
       information.
@remarks Implements DGPT03101
*/
VAR(Gpt_LLD_ChannelInfoType, GPT_VAR) Gpt_LLD_ChannelInfo[GPT_HW_CHANNEL_NUM];

/**
@brief Pointer to a data structure containing channel configuration information (set in tresos)
@remarks Implements DGPT03100
*/
P2CONST(Gpt_LLD_ChannelConfigType, GPT_VAR, GPT_APPL_CONST) Gpt_LLD_ChannelConfigPtr = NULL_PTR;

/*Possible values:
        0xffu                   : channel not configured
        "logical channel" index : channel configured and logical channel index (channel index
                                  configured in tresos) is corresponding to HW channel
        This is mainly used for determining the GPT interrupt source
*/
/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for EMIOS:
@remarks Implements DGPT03102
*/
VAR(uint8, GPT_VAR) GPT_LLD_EMIOS_HardwareMap[GPT_EMIOS_CHAN_NUM];
/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for PIT:
@remarks Implements DGPT03103
*/
VAR(uint8, GPT_VAR) GPT_LLD_PITRTI_HardwareMap[GPT_PITRTI_CHAN_NUM];
/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for STM:
@remarks Implements DGPT03104
*/
VAR(uint8, GPT_VAR) GPT_LLD_STM_HardwareMap[GPT_STM_CHAN_NUM];

#define GPT_STOP_SEC_VAR_UNSPECIFIED
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef GPT_PRECOMPILE_SUPPORT

#define GPT_START_SEC_CONST_UNSPECIFIED
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief Configuration structure for Precompile Config Variant
@remarks Implements DGPT03102
*/
extern CONST(Gpt_ConfigType, GPT_CONST) Gpt_InitConfigPC;

#define GPT_STOP_SEC_CONST_UNSPECIFIED
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define GPT_START_SEC_CODE
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent initialization function.
@details This function is called only once and sets up all the channels from the current configuration.
         It initializes the internal GPT driver variables and arrays and calls the IP-specific
         initialization function.

@remarks Implements DGPT03208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_Init()
{
    /*
    */

    VAR(Gpt_ChannelType, AUTOMATIC) hwChannel;
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;

    /* Clear hardware channel map and set global initialization */

    for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_EMIOS_CHAN_NUM; channelIndex++)
    {
        GPT_LLD_EMIOS_HardwareMap[channelIndex] = 0xffu;
    }

    for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_PITRTI_CHAN_NUM; channelIndex++)
    {
        GPT_LLD_PITRTI_HardwareMap[channelIndex] = 0xffu;
    }

    for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_STM_CHAN_NUM; channelIndex++)
    {
        GPT_LLD_STM_HardwareMap[channelIndex] = 0xffu;
    }

    for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_HW_CHANNEL_NUM; channelIndex++)
    {
        /* Clear Notification, GPT MODE (ONE-SHOT/CONT) */
        Gpt_LLD_ChannelInfo[channelIndex].BitInfo = GPT_INDEX_ZERO;

        /* Reset Reload value */
        Gpt_LLD_ChannelInfo[channelIndex].Gpt_ReloadValue = GPT_INDEX_ZERO;
    }

    Gpt_LLD_ChannelConfigPtr = Gpt_Cfg_Ptr->Gpt_ChannelConfigPtr;


    /* Save copy of current hardware channel number in local variable */
    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        hwChannel = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel;
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        module_type = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module;

        /* Store Channel Mode (ONE_SHOT / CONTINUOUS) this macro does not set any registers*/
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        GPT_SET_CHANNEL_MODE(channelIndex, (uint8) Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelMode);

        /* call the LLD level function for this module */
        /*lint -save -e961*/
        switch(module_type)
        {
        case GPT_EMIOS_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Emios_LLD_InitChannel(hwChannel, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_FreezeEnable);

            GPT_LLD_EMIOS_HardwareMap[hwChannel] = channelIndex;
        break;
        case GPT_PITRTI_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            PitRti_LLD_InitChannel(hwChannel, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_FreezeEnable);
            GPT_LLD_PITRTI_HardwareMap[hwChannel] = channelIndex;
        break;
        case GPT_STM_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Stm_LLD_InitChannel(hwChannel, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_FreezeEnable);
            GPT_LLD_STM_HardwareMap[hwChannel] = channelIndex;
            break;
        default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_INIT_ID, (uint8)GPT_CER_WRONGMODULE);
            break;
        }
        /*lint -restore */

        Gpt_ChannelStatus[channelIndex] = GPT_STATUS_INITIALIZED;
    }
}


/*************************************************************************************************/

/* [GPT194]: This function shall be pre compile time configurable */
/* On/Off by the configuration parameter: GPT_DEINIT_API */
#if (GPT_DEINIT_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent de-initialization function.
@details This function is called only once and sets up all the channels from the current configuration.
         It de-initializes the internal GPT driver variables and calls the IP-specific de-initialization function.

@remarks Implements DGPT03201
*/
FUNC (void, GPT_CODE) Gpt_LLD_DeInit(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;

    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        module_type = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module;
        /*lint -save -e961*/
        switch(module_type)
        {
        case GPT_EMIOS_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Emios_LLD_DeInit(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel);
            break;
        case GPT_PITRTI_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            PitRti_LLD_DeInit(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel);
            break;
        case GPT_STM_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Stm_LLD_DeInit(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel);
            break;
        default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_DEINIT_ID, (uint8)GPT_CER_WRONGMODULE);
        break;
        }
        /*lint -restore */
    }

    /* Reset ChannelConfig pointer */
    Gpt_LLD_ChannelConfigPtr = NULL_PTR;
}
#endif

/*************************************************************************************************/
/* [GPT195]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_TIME_ELAPSED_API */
#if (GPT_TIME_ELAPSED_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for fetching the elapsed timer value.
@details It determines the type of the HW channel (e.g. eMIOS, STM,etc...) and calls the
         appropriate IP function for reading the HW timer and then it calculates the
         elapsed timer value.

@param[in]     channel         Numeric identifier of the GPT channel
@param[out]    returnValuePtr  Pointer to elapsed timer value

@pre  requires GPT_TIME_ELAPSED_API = STD_ON

@remarks Implements DGPT03206
*/

FUNC (void, GPT_CODE) Gpt_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
    /*lint -save -e961*/
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Emios_LLD_GetTimeElapsed(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, returnValuePtr);
        break;
    case GPT_PITRTI_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        PitRti_LLD_GetTimeElapsed(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, returnValuePtr);
    break;
    case GPT_STM_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Stm_LLD_GetTimeElapsed(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, Gpt_LLD_ChannelInfo[channel].Gpt_ReloadValue, returnValuePtr);
        break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_TIMEELAPSED_ID, (uint8)GPT_CER_WRONGMODULE);
        break;    
    }
    /*lint -restore */
}
#endif

/*************************************************************************************************/
/* [GPT196]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_TIME_REMAINING_API */
#if (GPT_TIME_REMAINING_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for fetching the remaining timer value.
@details It determines the type of the HW channel (e.g. eMIOS, STM,etc...) and calls the
         appropriate IP function for reading the HW timer and then it calculates the
         remaining timer value.

@param[in]     channel         Numeric identifier of the GPT channel
@param[out]    returnValuePtr  Pointer to elapsed timer value

@pre  requires GPT_TIME_REMAINING_API = STD_ON

@remarks Implements DGPT03207
*/
FUNC (void, GPT_CODE) Gpt_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                                         P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
     /*lint -save -e961*/
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
        Emios_LLD_GetTimeRemaining(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, returnValuePtr);
    break;
    case GPT_PITRTI_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        PitRti_LLD_GetTimeRemaining(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, returnValuePtr);
    break;
    case GPT_STM_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Stm_LLD_GetTimeElapsed(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, Gpt_LLD_ChannelInfo[channel].Gpt_ReloadValue, returnValuePtr);

        /* time remaining = timeout - time elapsed */
        *returnValuePtr = Gpt_LLD_ChannelInfo[channel].Gpt_ReloadValue - *returnValuePtr;
    break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_TIMEREMAINING_ID, (uint8)GPT_CER_WRONGMODULE);
    break;
    }
    /*lint -restore */
}
#endif

/*************************************************************************************************/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for checking the timeout value of
         a channel.
@details It determines the type of the HW channel (e.g. eMIOS, STM,etc...) and checks the
         provided value against the maximum supported HW value.

@param[in]     channel       Numeric identifier of the GPT channel
@param[in]     value         Timeout period (in ticks) after which a notification shall occur (if
                             enabled).

@pre  requires GPT_DEV_ERROR_DETECT = STD_ON

@remarks Implements DGPT03213
*/
FUNC (Std_ReturnType, GPT_CODE) Gpt_LLD_CheckStartTimeoutValue(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                                               VAR(Gpt_ValueType, AUTOMATIC) value)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    VAR(Std_ReturnType, AUTOMATIC) returnCode = (Std_ReturnType)E_OK;
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
        if(EMIOS_LLD_INVALID_TIMEOUT_VALUE(value))
        {
            returnCode = GPT_E_PARAM_VALUE;
        }
    break;
    case GPT_PITRTI_MODULE:
        returnCode = (Std_ReturnType)E_OK;
    break;
    case GPT_STM_MODULE:
        returnCode = (Std_ReturnType)E_OK;
    break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_CHECKTIMEOUTVALUE_ID, (uint8)GPT_CER_WRONGMODULE);
    break;
    }
    /*lint -restore */
    return returnCode;
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for starting the timer channel.
@details It determines the type of the HW channel (e.g. eMios, STM,etc...), calculates
         its ID and calls the appropriate IP function for starting the timer channel.

@param[in]     channel       Numeric identifier of the GPT channel
@param[in]     value         Timeout period (in ticks) after which a notification shall occur (if
                             enabled).

@remarks Implements DGPT03211
*/
FUNC (void, GPT_CODE) Gpt_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
        Emios_LLD_StartTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, value , Gpt_LLD_ChannelConfigPtr[channel].Gpt_ChannelMode);
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        /* Save desired value in ReloadValue */
    break;
    case GPT_PITRTI_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        PitRti_LLD_StartTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, value, Gpt_LLD_ChannelConfigPtr[channel].Gpt_ChannelMode);
    break;
    case GPT_STM_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Stm_LLD_StartTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel, value);
        /* Save desired value in ReloadValue */
        Gpt_LLD_ChannelInfo[channel].Gpt_ReloadValue = value;
    break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STARTTIMER_ID, (uint8)GPT_CER_WRONGMODULE);
    break;
    }
    /*lint -restore */
}

/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for stopping the timer channel.
@details It determines the type of the HW channel (e.g. eMios, STM,etc...), calculates
                   its ID and calls the appropriate IP function for stopping the timer channel.


@param[in]     channel       Numeric identifier of the GPT channel

@remarks Implements DGPT03212
*/
FUNC (void, GPT_CODE) Gpt_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Emios_LLD_StopTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
    break;
    case GPT_PITRTI_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        PitRti_LLD_StopTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
    break;
    case GPT_STM_MODULE:
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        Stm_LLD_StopTimer(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
    break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STOPTIMER_ID, (uint8)GPT_CER_WRONGMODULE);
    break;
    }
    /*lint -restore */
}
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for setting the SLEEP mode.
@details For each of the configured channels, it determines the type of the HW channel
         (e.g. eMios, STM,etc...) and stops the non-wake-up capable channel. The wake-up capable
are not stopped.


*/

/* [GPT201]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_WAKEUP_FUNCTIONALITY _API */

/**
@brief   Gpt driver Autosar independent and IP dependent function for setting the SLEEP mode.
@details For each of the configured channels, it determines the type of the HW channel
         (e.g. eMIOS, STM,etc...) and stops the non-wake-up capable channel. The wake-up capable
         channels are not stopped.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03210
*/
FUNC (void, GPT_CODE) Gpt_LLD_SetSleepMode(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    VAR(boolean, AUTOMATIC) enableStmCounter = (boolean)FALSE;

    /* determine if there is at least one wakeup capable STM channel for which the wakeup
       capability is enabled */
    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        if (GPT_STM_MODULE == Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module)
        {
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            if (((uint8)TRUE == Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_EnableWakeup)&&
                ((boolean)TRUE == (boolean)(GPT_GET_WAKE_UP(channelIndex))))
            {
                enableStmCounter = (boolean)TRUE;
            }
        }
    }

    /*
    */
    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {

        /*
        */
        module_type = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module;
        switch(module_type)
        {
        case GPT_EMIOS_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Emios_LLD_SetSleepMode(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel, (boolean)(GPT_GET_WAKE_UP(channelIndex)));
            break;
        case GPT_PITRTI_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            PitRti_LLD_SetSleepMode(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel, (boolean)(GPT_GET_WAKE_UP(channelIndex)));
            break;
        case GPT_STM_MODULE:
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Stm_LLD_SetSleepMode(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel, (boolean)(GPT_GET_WAKE_UP(channelIndex)), enableStmCounter);
            break;
        default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_SETMODE_ID, (uint8)GPT_CER_WRONGMODULE);
            /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                                      Cer_ReportError() function implementation */
        break;
        }
        /*lint -restore */
        if ((boolean)FALSE == (GPT_GET_WAKE_UP(channelIndex)))
        {
        /*lint -restore */
        Gpt_ChannelStatus[channelIndex] = GPT_STATUS_STOPPED;
        }
    }
}
#endif

/*************************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for setting the Normal mode.
@details For each of the configured channels, it determines the type of the HW channel
         (e.g. eMIOS, STM,etc...) and enables the ocunter for STM channels.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03209
*/
FUNC (void, GPT_CODE) Gpt_LLD_SetNormalMode(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    VAR(boolean, AUTOMATIC) atLeastOneStmChannelConfigured = (boolean)FALSE;

    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        /*lint -save -e961*/
        if (GPT_STM_MODULE == Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module)
        {
            atLeastOneStmChannelConfigured = (boolean)TRUE;
            /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                                      Cer_ReportError() function implementation */
        }
        /*lint -restore */
    }

    if((boolean)TRUE == atLeastOneStmChannelConfigured)
    {
        Stm_LLD_SetNormalMode();
    }
}
#endif

/*************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for enabling the timer channel notification.
@details It resets the notification bit-field of Gpt_LLD_ChannelInfo[channel] and determines the
         type of the HW channel (e.g. eMIOS, STM,etc...), and enables the corresponding IRQ, for
         all the channels except for the STM channels.

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_ENABLE_DISABLE_NOTIFICATION_API = STD_ON

@remarks Implements DGPT03204
*/
FUNC (void, GPT_CODE) Gpt_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;

    GPT_SET_NOTIFICATION(channel, GPT_NOTIFICATION_ENABLED);
    switch(module_type)
    {
    case GPT_EMIOS_MODULE:
        Emios_LLD_EnableNotification(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
    break;
    case GPT_PITRTI_MODULE:
     /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        PitRti_LLD_EnableNotification(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
    break;

    case GPT_STM_MODULE:        
    break;
    default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_ENABLENOTIFICATION_ID, (uint8)GPT_CER_WRONGMODULE);
    /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                                  Cer_ReportError() function implementation */
    break;
    }
    /*lint -restore */
}
#endif

/*************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for disabling the timer channel notification.
@details It resets the notification bit-field of Gpt_LLD_ChannelInfo[channel] and determines the
         type of the HW channel (e.g. eMios, STM,etc...), and disables the corresponding IRQ, for
         all the channels except for the STM channels.

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_ENABLE_DISABLE_NOTIFICATION_API = STD_ON

@remarks Implements DGPT03202
*/
FUNC (void, GPT_CODE) Gpt_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    GPT_SET_NOTIFICATION(channel, GPT_NOTIFICATION_DISABLED);

    /* note - the IRQs are only enabled when in continous mode. In One-shot mode the IRQs are
       needed in order to know when the timeout had expired */
   /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    if (GPT_MODE_CONTINOUS == (Gpt_LLD_ChannelConfigPtr[channel].Gpt_ChannelMode))
    {
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        module_type = Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Module;
        /*lint -save -e961*/
        switch(module_type)
        {
        case GPT_EMIOS_MODULE:
         /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            Emios_LLD_DisableNotification(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
        break;
        case GPT_PITRTI_MODULE:
       /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
            PitRti_LLD_DisableNotification(Gpt_LLD_ChannelConfigPtr[channel].Gpt_HW_Channel);
           break;
        case GPT_STM_MODULE:
        break;
        default:
            Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_DISABLENOTIFICATION_ID, (uint8)GPT_CER_WRONGMODULE);
            /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                                      Cer_ReportError() function implementation */
            break;
        }
        /*lint -restore */
    }
}
#endif
/*************************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for disabling the wakeup interrupt invocation
         of a timer channel.
@details It resets the wakeup bit-field of Gpt_LLD_ChannelInfo[channel].

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03203
*/
FUNC (void, GPT_CODE) Gpt_LLD_DisableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    /* Change Wakeup status in the channel info */
    GPT_SET_WAKE_UP(channel, GPT_WAKE_UP_DISABLED);
}
#endif

/*************************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for enabling the wakeup interrupt invocation
         of a timer channel.
@details It sets the wakeup bit-field of Gpt_LLD_ChannelInfo[channel].

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03205
*/
FUNC (void, GPT_CODE) Gpt_LLD_EnableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    /* Change Wakeup status in the channel info */
    /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
    if ((boolean)TRUE == Gpt_Cfg_Ptr->Gpt_ChannelConfigPtr[channel].Gpt_EnableWakeup)
    {
    GPT_SET_WAKE_UP(channel, GPT_WAKE_UP_ENABLED);
}
}
#endif

/*************************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for checking if a GPT channel is the source for
         wakeup event .
@details It checks if a GPT channel is the source for wakeup event and calls the ECU state manager
         service EcuM_SetWakeupEvent in case of a valid GPT channel wakeup event.
         channel wakeup event.


@param[in]     wakeupSource        Information on wakeup source to be checked.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API == STD_ON

@remarks Implements DGPT03200
*/
FUNC (void, GPT_CODE) Gpt_LLD_Cbk_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {

        /* [GPT328]: Checks if a wakeup capable GPT channel is the source for a wakeup event */
        /* and calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid GPT
        channel wakeup event. */
        /*
        */
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_LLD_C_REF3*/
        if ((GPT_GET_WAKE_UP(channelIndex) == GPT_WAKE_UP_ENABLED)
            && (Gpt_Cfg_Ptr->Gpt_ChannelConfigPtr[channelIndex].Gpt_ChannelWakeUpInfo == wakeupSource))

        {
            /* Calling EcuM_SetWakeupEvent */
            EcuM_SetWakeupEvent(wakeupSource);
            /** @note  Violates MISRA 2004 Advisory Rule 13.6, for loop index variable is modified in body of the for loop. - See @ref GPT_LLD_C_REF4 */ 
            channelIndex = Gpt_Cfg_Ptr->Gpt_Channel_Count;
        }
    }
}
#endif

/*************************************************************************************************/
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.

@param[in]  Prescaler  - Prescaler type ( Normal or Alternate )
@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11024
*/
FUNC (void, GPT_CODE) Gpt_LLD_SelectPrescaler(VAR(Gpt_ClockModeType, AUTOMATIC) ClkMode)
{
    VAR(Gpt_ChannelType, AUTOMATIC) hwChannel;
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;
    VAR(Gpt_ChannelType, AUTOMATIC) module_type;
    VAR(boolean, AUTOMATIC) enableStmCounter = (boolean)FALSE;

    /* Save copy of current hardware channel number in local variable */
    for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
    {
        hwChannel = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Channel;
        module_type = Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_HW_Module;

        /* call the LLD level function for this module */
        if(GPT_EMIOS_MODULE == module_type)
        {
            if(GPT_NORMAL == ClkMode)
            {
                Emios_LLD_SelectPrescaler(hwChannel, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale);
            }
            else
            {
                Emios_LLD_SelectPrescaler(hwChannel, Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale_Alternate);
            }
        }
        else if((GPT_STM_MODULE == module_type) && ((boolean)FALSE == enableStmCounter))
        {
            if (GPT_NORMAL == ClkMode)
            {
                Stm_LLD_SelectPrescaler(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale);
                enableStmCounter = (boolean)TRUE;
            }
            else
            {
                Stm_LLD_SelectPrescaler(Gpt_LLD_ChannelConfigPtr[channelIndex].Gpt_ChannelPrescale_Alternate);
                enableStmCounter = (boolean)TRUE;
            }

        }
        else
        {
           /*Empty else added to fix misra violations*/
        }
        /*lint -restore */
    }
}
/* GPT_DUAL_CLOCK_MODE == STD_ON */
#endif 

#define GPT_STOP_SEC_CODE
/**
@file   Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
