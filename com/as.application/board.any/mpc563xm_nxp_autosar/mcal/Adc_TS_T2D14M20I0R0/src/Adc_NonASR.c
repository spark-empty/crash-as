/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    Adc_NonASR.c
    @version 2.0.0

    @brief   AUTOSAR Adc - Common Level Driver source file.
    @details Non Autosar layer of ADC MCAL driver.

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
 * @page    misra_violations MISRA-C:2004 violations
 *
 * @section AdcNonASR_c_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
 *
 * @section AdcNonASR_c_REF_2
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code section.
 *
 * @section Adc_NonASR_c_REF_3
 *          Violates MISRA 2004 Required Rule 8.10, External function could be made static.
 *          Not required from Autosar specification.
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
#include "Adc_NonASR.h"
#include "Adc_LLD.h"
#include "SchM_Adc.h"

/**
 * @brief   Dependencies to other modules.
 * @details The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 * @note    The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 * @requirements            ADC355, ADC267.
 *
 * @remarks Cover:          ADC355, ADC267.
 */
/**
 * @brief   The module include the Dem.h file to the error production.
 *
 * @requirements            ADC239.
 *
 * @remarks Cover:          ADC239.
 */
/* ADC239, ADC355 */
#include "Dem.h"
/**
 * @brief   Dependencies to other modules.
 * @details If development error detection for the ADC module is
 *          enables: The ADC module shall raise errors to the
 *          Development Error Trace (DET) whenever a development
 *          error is encountered by  this module.
 *
 * @note    If development error detection for the ADC module is
 *          enables: The ADC module shall raise errors to the
 *          Development Error Trace (DET) whenever a development error
 *          is encountered by this module.
 *
 * @requirements            ADC354.
 *
 * @remarks Cover:          ADC354.
 */
#if (ADC_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/* Source File Version Information */
/**
 * @remarks Covers:  BSW00374, BSW00318.
 */
#define ADC_VENDOR_ID_C_NONASR         43
#define ADC_AR_MAJOR_VERSION_C_NONASR  3
#define ADC_AR_MINOR_VERSION_C_NONASR  0
#define ADC_AR_PATCH_VERSION_C_NONASR  2
#define ADC_SW_MAJOR_VERSION_C_NONASR  2
#define ADC_SW_MINOR_VERSION_C_NONASR  0
#define ADC_SW_PATCH_VERSION_C_NONASR  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
 * @brief   The integration of incompatible files is to be avoided, so
 *          the minimum implementation is the version check between .c
 *          files and .h files.
 *
 * @note    Check if ASR source files and Non ASR source files are of the same Software version.
 *
 * @requirements
 *
 * @remarks Cover
 */

/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_C_NONASR != ADC_VENDOR_ID)
    #error "Adc_NonASR.c and Adc.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_C_NONASR != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_C_NONASR != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_C_NONASR != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Adc_NonASR.c and Adc.h are different"
    #endif
#endif

/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_C_NONASR != ADC_SW_MAJOR_VERSION)  || \
     (ADC_SW_MINOR_VERSION_C_NONASR != ADC_SW_MINOR_VERSION)  || \
     (ADC_SW_PATCH_VERSION_C_NONASR != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Adc_NonASR.c and Adc.h are different"
#endif

/* Check if source file and ADC LLD header file are of the same vendor */
#if (ADC_VENDOR_ID_C_NONASR != ADC_VENDOR_ID_LLD_H)
    #error "Adc_NonASR.c and Adc_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC LLD header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_C_NONASR != ADC_AR_MAJOR_VERSION_LLD_H) || \
         (ADC_AR_MINOR_VERSION_C_NONASR != ADC_AR_MINOR_VERSION_LLD_H) || \
         (ADC_AR_PATCH_VERSION_C_NONASR != ADC_AR_PATCH_VERSION_LLD_H))
        #error "AutoSar Version Numbers of Adc_NonASR.c and Adc_LLD.h are different"
    #endif
#endif

/* Check if source file and ADC LLD header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_C_NONASR != ADC_SW_MAJOR_VERSION_LLD_H) || \
     (ADC_SW_MINOR_VERSION_C_NONASR != ADC_SW_MINOR_VERSION_LLD_H) || \
     (ADC_SW_PATCH_VERSION_C_NONASR != ADC_SW_PATCH_VERSION_LLD_H))
    #error "Software Version Numbers of Adc_NonASR.c and Adc_LLD.h are different"
#endif

/* Check if source file and DET header file are of the same version */
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((ADC_AR_MAJOR_VERSION_C_NONASR != DET_AR_MAJOR_VERSION) || \
             (ADC_AR_MINOR_VERSION_C_NONASR != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Adc_NonASR.c and Det.h are different"
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
/* lint -save -e961 -e537 -e451 */
/* put all ADC code into defined section */
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref AdcNonASR_c_REF_1
*/
#define ADC_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/* lint -restore */

/**
* @brief          Unit status structure
* @details        Structure for the unit status.
*
* @requirements   PR-MCAL-3233
* @implements
*
*/
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
VAR(Adc_NCMR_Type, AUTOMATIC) Adc_NCMRx_Mask[ADC_NO_OF_ENABLE_CH_DISABLE_CH_GROUPS];
#endif

/* lint -save -e961 -e537 -e451 */
/* put all ADC code into defined section */
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref AdcNonASR_c_REF_1
*/
#define ADC_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/* lint -restore */
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/* lint -save -e961 -e537 -e451 */
/* put all ADC code into defined section */
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref AdcNonASR_c_REF_1
*/
#define ADC_START_SEC_CODE
#include "MemMap.h"
/* lint -restore */

#if (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__)
#if (ADC_ENABLE_HWTRIG_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Function enables the TriggerSource for group selected by Group parameter.
 * @details This non autosar API is used to enable any one of the configured
 *          TriggerSource of the Group. When this non autosar API is used to
 *          enable the trigger source the CTU interrupt will be disabled by the driver.
 *          So user has to call the non autosar API Adc_HwResultReadGroup to read
 *          the converted result from the ADC hardware register.
 *
 * @note    The function Service ID[hex]: 0x0E.
 * @note    Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]  Group - index of group
 * @param[in]  TriggerSource- Trigger source to be use for the group.
 *             (Configuration file should contain the TriggerSource for called group).
 *
 * @remarks Covers       PR-MCAL-3176, PR-MCAL-3188.
 *                       DADC10000.
 * @remarks Implements
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_EnableHwTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) /* No priority */
    #if (ADC_ENABLE_QUEUING == STD_OFF) /* No Queue */
      /* ADC Hardware Unit on which the requested group will run */
      VAR(Adc_HwUnitType,AUTOMATIC) unit = (Adc_HwUnitType)0;
      /* number of groups in software queue */
      VAR(Adc_QueueIndexType,AUTOMATIC) noGroupsInSWQueue = (Adc_QueueIndexType)0;
      /* number of groups in hardware queue */
      VAR(Adc_QueueIndexType,AUTOMATIC) noGroupsInHWQueue = (Adc_QueueIndexType)0;
    #endif /* #if (ADC_ENABLE_QUEUING == STD_OFF)  */
#endif /* #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(boolean, AUTOMATIC) Error_flag = (boolean)FALSE; /*  Set flag when error is reported */
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC297): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEHWTRIGGER_ID,
                        (uint8)ADC_E_UNINIT);
        Error_flag = (boolean)TRUE;
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC128): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEHWTRIGGER_ID,
                        (uint8)ADC_E_PARAM_GROUP);
        Error_flag = (boolean)TRUE;
    }
    else {
      /* do nothig for misra */
    }
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Error_flag == (boolean)FALSE)
    {
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) /* No priority */
        #if (ADC_ENABLE_QUEUING == STD_OFF) /* No Queue */
            /* Get the unit to which the group belongs to */
            unit = ADC_GroupUnit(Group);
        #endif /* #if (ADC_ENABLE_QUEUING == STD_OFF) */
    #endif /* #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */
        if (Adc_Cfg_Ptr->Groups[Group].TriggerSource == ADC_TRIGG_SRC_SW)
        {
            /* Error (ADC136): trigger source configured as software */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_ENABLEHWTRIGGER_ID,
                            (uint8)ADC_E_WRONG_TRIGG_SRC);
        }
        else if ((Adc_Cfg_Ptr->Groups[Group].mode) != ADC_CONV_MODE_ONESHOT)
        {
            /* Error (ADC281): group configured in continuous mode */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_ENABLEHWTRIGGER_ID,
                            (uint8)ADC_E_WRONG_CONV_MODE);
        }
        else
        {
            /* enter critical section to protect agains queue modifications */
            SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_20);
        #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) /* No priority */
          #if (ADC_ENABLE_QUEUING == STD_OFF) /* No Queue */

           /* read now the queue sizes */
            noGroupsInHWQueue= ADC_GroupsInHwQueue(unit); /* hardware queue size */
            noGroupsInSWQueue= ADC_UnitStatus[unit].QueueIndex; /* software queue size */
            /* In this case any conversion is ongoing */
            if ((noGroupsInSWQueue!=(Adc_QueueIndexType)0)||
                (noGroupsInHWQueue!=(Adc_QueueIndexType)0))
            {
                /* error occured, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_20);
                /* [ADC321] unit is busy */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHWTRIGGER_ID,
                                (uint8)ADC_E_BUSY);
            }
            else
            #endif/* #if (ADC_ENABLE_QUEUING == STD_OFF) */
        #endif /* #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */
            {
            /* everything ok, exit critical section */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_20);
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
                {
                    Adc_LLD_EnableHwTrigger(Group,TriggerSource);
                }
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
            }
        }
    } /* end of if (flag == (boolean)FALSE) condition */
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
}

/**
 * @brief      Function disable the TriggerSource for group selected by Group parameter.
 * @details    This non autosar API is used to disable the already enabled
 *             TriggerSource of the Group.
 *
 * @note       The function Service ID[hex]: 0x0F.
 * @note       Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]  Group         Index of group
 * @param[in]  TriggerSource Trigger source to be disable for the group.
 *             (Configuration file should contain the TriggerSource for called group).
 *
 * @remarks Covers       PR-MCAL-3189, PR-MCAL-3190.
 *                       DADC10001.
 * @remarks Implements
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_DisableHwTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC298): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHWTRIGGER_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC129): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHWTRIGGER_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
    else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource == ADC_TRIGG_SRC_SW)
    {
        /* Error (ADC137): trigger source configured as software */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHWTRIGGER_ID,
                        (uint8)ADC_E_WRONG_TRIGG_SRC);
    }
    else if ((Adc_Cfg_Ptr->Groups[Group].mode) != ADC_CONV_MODE_ONESHOT)
    {
        /* Error (ADC282): group configured in continuous mode */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHWTRIGGER_ID,
                        (uint8)ADC_E_WRONG_CONV_MODE);
    }
    else
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
            Adc_LLD_DisableHwTrigger(Group, TriggerSource);
    }
}

/**
 * @brief      Function reads the result of the hardware triggered groups conversion result.
 * @details    This non autosar API is used to read the result of the hardware
 *             triggered groups conversion result from the ADC hardware register
 *             in this case the CTU interrupt will be disabled for the group.
 *             The VALID bit CDR register will be cleared automatically when we read the results
 *             from the channel data register. If the user calls non-autosar function
 *             Adc_HwResultReadGroup() once again before the next conversion takes place, the
 *             Adc_HwResultReadGroup() returns E_NOT_OK.
 *
 * @note       The function Service ID[hex]: 0x0D.
 * @note       Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]  Group     Index of group
 * @param[out] DataPtr   Pointer to a buffer which will be filled by the
 *             conversion results.
 *
 * @return    Std_ReturnType - E_OK or E_NOT_OK.
 * @remarks   Covers       PR-MCAL-3191, PR-MCAL-3192.
 *                         DADC10002.
 * @remarks   Implements
 *
 * @api
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_HwResultReadGroup
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Adc_ReadGroupRet = (Std_ReturnType)E_NOT_OK;

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC296): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_HWRESULTREADGROUP_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC152): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_HWRESULTREADGROUP_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
    else
    #endif /* #if (ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        Adc_ReadGroupRet = Adc_LLD_HwResultReadGroup(Group, DataPtr);
    }

    /* return the result */
    return(Adc_ReadGroupRet);
}

#endif /* #if (ADC_ENABLE_HWTRIG_NONAUTO_API == STD_ON) */
#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */
/**
 * @brief   Set the clock ADC clock prescaler.
 * @details This function set the clock ADC clock prescaler
 * @note    The function NON Autosar Service.
 * @note    Synchronous.
 * @note    Non Reentrant function.
 * @note    Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]   ClockMode  NORMAL mode or ALTERNATE mode.
 *
 *
 * @api
 */
#if (ADC_DUAL_CLOCK_MODE == STD_ON) || defined(__DOXYGEN__)
FUNC(Std_ReturnType, ADC_CODE) ADC_SetClockMode
(
  VAR(Adc_NonASR_DualClockModeType, AUTOMATIC) ClockMode
)
{
  return Adc_LLD_SetClockMode(ClockMode);
}
#endif

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief          Enable a channel inside a group.
 * @details        This function allows to active a channel assigned to a group for SW normal conversion
 *
 * @note           The function Service ID[hex]: 0x12.
 * @note           Synchronous.
 * @note           Reentrant function.
 * @note           Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]      GroupId         Symbolic name of group.
 * @param[in]      ChannelId       Symbolic name of channel.
 *
 * @return         void
 *
 * @api
 *
 * @requirements   PR-MCAL-3233
 * @implements
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_EnableChannel
(
   VAR(Adc_GroupType, AUTOMATIC) GroupId,
   VAR(Adc_ChannelType, AUTOMATIC)ChannelId
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) index = (uint8)0;
    VAR(boolean, AUTOMATIC) channelFound = (boolean)FALSE;
#endif
    VAR(Adc_ChannelType, AUTOMATIC) Adc_IdCh;
    VAR(Adc_GroupType, AUTOMATIC) Adc_GroupId = ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX;
    VAR(Adc_HwUnitType, AUTOMATIC) UnitId = (Adc_HwUnitType)0;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC302): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (GroupId >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC218): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
    else if (Adc_Cfg_Ptr->Groups[GroupId].TriggerSource != ADC_TRIGG_SRC_SW)
    {
        /* Error (ADC133): trigger source configured as hardware */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_TRIGG_SRC);
    }
    else if(Adc_Cfg_Ptr->Groups[GroupId].type != ADC_CONV_TYPE_NORMAL)
    {
        /* Error: If it is not the normal group converstion */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_CONV_MODE);
    }
    else if((Adc_GroupType)Adc_Cfg_Ptr->Groups[GroupId].EnableChDisableChGroupIndex ==
             ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX)
    {
        /* Error: The Group does not support the individual channel enable or disable support */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_EN_CH_DIS_CH_GROUP);
    }
    else
    {
        P2CONST(Adc_GroupDefType, AUTOMATIC, ADC_APPL_DATA) GroupChIndexPtr; /* Ptr to AdcGroupChIndex */
        GroupChIndexPtr = Adc_Cfg_Ptr->Groups[GroupId].Assignment;

        /* Check if ChannelId is valid: assigned to that group */
        for(index=(uint8)0;index<(uint8)(Adc_Cfg_Ptr->Groups[GroupId].AssignedChannelCount);index++)
        {
            if((Adc_ChannelType)ChannelId == (Adc_ChannelType)GroupChIndexPtr[index])
            {
                channelFound = (boolean)TRUE;
                break;
            }
        }

        /* Further steps must only be done if the ChannelId is valid */
        if(channelFound != (boolean)TRUE)
        {
            /* Error: The Group doesnot support the individual channel enable or disable support */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_ENABLE_CHANNEL_ID,
                            (uint8)ADC_E_WRONG_EN_CH_DIS_CH_ID);
        }
        else
#endif
        {
            /* Get the unit to which the group belongs to */
            UnitId = ADC_GroupUnit(GroupId);

            /* Calculate HwChannelId of AdcChannel */
            Adc_IdCh = Adc_Cfg_Ptr->Channels[UnitId][ChannelId].ChId;

            /* Get the group index of the channels which supports individual channel enable or disable support */
            Adc_GroupId = (Adc_GroupType)Adc_Cfg_Ptr->Groups[GroupId].EnableChDisableChGroupIndex;

            /* Global Interrupt disable to protect code section */
            SchM_Enter_Adc(SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_25);

            if(Adc_IdCh < ADC_ST_EXTENDED_CH)
            {   /* Precision channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR0 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR0)|((uint32)(1U)<<Adc_IdCh));
            }
            else if ((Adc_IdCh >= ADC_ST_EXTENDED_CH) && (Adc_IdCh <= ADC_ED_EXTENDED_CH))
            {   /* Standard channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR1 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR1)|((uint32)(1U)<<(Adc_IdCh-ADC_ST_EXTENDED_CH)));
            }
            else if ((Adc_IdCh >= ADC_ST_EXTERNAL_CH) && (Adc_IdCh <= ADC_ED_EXTERNAL_CH))
            {   /* External multiplexed channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR2 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR2)|((uint32)(1U)<<(Adc_IdCh-ADC_ST_EXTERNAL_CH)));
            }
            else
            {
                /* Catastrophic Errors Recovery (CER) */
                Cer_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLE_CHANNEL_ID,
                        (uint8)ADC_CER_CHANNEL_ID_CORRUPTED_TYPE);
            }

            /* Global Interrupt enable to protect code section */
            SchM_Exit_Adc(SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_25);
        }
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

/**
 * @brief          Disable a channel inside a group.
 * @details        This function allows to de-active a channel assigned to a group for SW normal conversion
 *
 * @note           The function Service ID[hex]: 0x13.
 * @note           Synchronous.
 * @note           Reentrant function.
 * @note           Violates @ref Adc_NonASR_c_REF_3: External function could be made static.
 *
 * @param[in]      GroupId         Symbolic name of group.
 * @param[in]      ChannelId       Symbolic name of channel.
 *
 * @return         void
 *
 * @requirements   PR-MCAL-3233
 * @implements
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_DisableChannel
(
  VAR(Adc_GroupType, AUTOMATIC)GroupId,
  VAR(Adc_ChannelType, AUTOMATIC)ChannelId
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) index = (uint8)0;
    VAR(boolean, AUTOMATIC) channelFound = (boolean)FALSE;
#endif
    VAR(Adc_ChannelType, AUTOMATIC) Adc_IdCh;
    VAR(Adc_GroupType, AUTOMATIC) Adc_GroupId = ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX;
    VAR(Adc_HwUnitType, AUTOMATIC) UnitId = (Adc_HwUnitType)0;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC302): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (GroupId >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC218): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8) ADC_E_PARAM_GROUP);
    }
    else if (Adc_Cfg_Ptr->Groups[GroupId].TriggerSource != ADC_TRIGG_SRC_SW)
    {
        /* Error (ADC133): trigger source configured as hardware */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_TRIGG_SRC);
    }
    else if(Adc_Cfg_Ptr->Groups[GroupId].type != ADC_CONV_TYPE_NORMAL)
    {
        /* Error: If it is not the normal group converstion */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_CONV_MODE);
    }
    else if((Adc_GroupType)Adc_Cfg_Ptr->Groups[GroupId].EnableChDisableChGroupIndex ==
             ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX)
    {
        /* Error: The Group does not support the individual channel enable or disable support */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8)ADC_E_WRONG_EN_CH_DIS_CH_GROUP);
    }
    else
    {
        P2CONST(Adc_GroupDefType, AUTOMATIC, ADC_APPL_DATA) GroupChIndexPtr; /* Ptr to AdcGroupChIndex */

        GroupChIndexPtr = Adc_Cfg_Ptr->Groups[GroupId].Assignment;

        /* Check if ChannelId is valid */
        for(index=(uint8)0;index<(uint8)(Adc_Cfg_Ptr->Groups[GroupId].AssignedChannelCount);index++)
        {
            if((Adc_ChannelType)ChannelId == (Adc_ChannelType)GroupChIndexPtr[index])
            {
                channelFound = (boolean)TRUE;
                break;
            }
        }

        /* Further steps must only be done if the ChannelId is valid */
        if(channelFound != (boolean)TRUE)
        {
            /* Error: The Group does not support the individual channel enable or disable support */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_DISABLE_CHANNEL_ID,
                            (uint8)ADC_E_WRONG_EN_CH_DIS_CH_ID);
        }
        else
#endif
        {
            /* Get the unit to which the group belongs to */
            UnitId = ADC_GroupUnit(GroupId);

            /* Calculate HwChannelId of AdcChannel */
            Adc_IdCh = Adc_Cfg_Ptr->Channels[UnitId][ChannelId].ChId;

            /* Get the group index of the channels which supports individual channel enable or disable support */
            Adc_GroupId = (Adc_GroupType)Adc_Cfg_Ptr->Groups[GroupId].EnableChDisableChGroupIndex;

            /* Global Interrupt disable to protect code section */
            SchM_Enter_Adc(SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_25);

            if(Adc_IdCh < ADC_ST_EXTENDED_CH)
            {   /* Precision channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR0 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR0)&(~((uint32)(1U)<<Adc_IdCh)));
            }
            else if ((Adc_IdCh >= ADC_ST_EXTENDED_CH) && (Adc_IdCh <= ADC_ED_EXTENDED_CH))
            {   /* Standard channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR1 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR1)&(~((uint32)(1U)<<(Adc_IdCh-ADC_ST_EXTENDED_CH))));
            }
            else if ((Adc_IdCh >= ADC_ST_EXTERNAL_CH) && (Adc_IdCh <= ADC_ED_EXTERNAL_CH))
            {   /* External multiplexed channel */
                Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR2 = ((Adc_NCMRx_Mask[Adc_GroupId].Adc_NCMR2)&(~((uint32)(1U)<<(Adc_IdCh-ADC_ST_EXTERNAL_CH))));
            }
            else
            {
                /* Catastrophic Errors Recovery (CER) */
                Cer_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLE_CHANNEL_ID,
                        (uint8)ADC_CER_CHANNEL_ID_CORRUPTED_TYPE);
            }

            /* Global Interrupt enable to protect code section */
            SchM_Exit_Adc(SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_25);
        }
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif /* #if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */

/* lint -save -e961 -e537 -e451 */
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref AdcNonASR_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated inclusion of file
- See @ref AdcNonASR_c_REF_2
*/
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/* lint -restore */

#ifdef __cplusplus
}
#endif

/** @} */
