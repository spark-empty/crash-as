/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    Adc.c
    @version 2.0.0

    @brief   AUTOSAR Adc - Common Level Driver source file.
    @details Autosar layer of ADC MCAL driver.

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
 * @section Adc_c_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
 *
 * @section Adc_c_REF_2
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code section.
 *
 * @section Adc_c_REF_3
 *          Violates MISRA 2004 Advisory Rule 8.10, external function could be made static. Not
 *          required from Autosar.
 *
 * @section Adc_c_REF_4
 *          Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing
 *          used. This violation is due to the use of pointer arithmatic, which is used for the
 *          speed optimization, the indexing of the pointer is taken care and hence the unintended
 *          memory location will not be accessed.
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
#define ADC_VENDOR_ID_C         43
#define ADC_AR_MAJOR_VERSION_C  3
#define ADC_AR_MINOR_VERSION_C  0
#define ADC_AR_PATCH_VERSION_C  0
#define ADC_SW_MAJOR_VERSION_C  2
#define ADC_SW_MINOR_VERSION_C  0
#define ADC_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
 * @brief   The integration of incompatible files is to be avoided, so
 *          the minimum implementation is the version check between .c
 *          files and .h files.
 * @details The version check consist in check for included header files,
 *          it's between Adc.h and Std_Types .h; check for internal
 *          module .c and .h files, it's between Adc.h and Adc_Cfg.h.
 *
 * @note    Check version is between Adc.h and Std_Types.h and Adc.h and
 *          Adc_Cfg.h.
 *
 * @requirements            ADC124.
 *
 * @remarks Cover:          ADC124.
 */

/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_C != ADC_VENDOR_ID)
    #error "ADC.c and ADC.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_C != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_C != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_C != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of ADC.c and ADC.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_C != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of ADC.c and ADC.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((ADC_AR_MAJOR_VERSION_C != SCHM_ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_C != SCHM_ADC_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of ADC.c and SchM_Adc.h are different"
    #endif
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((ADC_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of ADC.c and Dem.h are different"
    #endif
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DET header file are of the same version */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
        #if ((ADC_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (ADC_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of ADC.c and Det.h are different"
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

/* put all ADC variables into defined section */
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#define ADC_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/* lint -restore */

/* Global Configuration Pointer */
/**
 * @brief   Segment descriptor for data arranged in array.
 *
 * @remarks Covers:         REQ001, REQ002.
 * @remarks Implements      DESIGN001, DESIGN002.
 *
 * @api
 */
P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) Adc_Cfg_Ptr = NULL_PTR;

/**
 * @brief   Array to hold the group status.
 *
 * @api
 */
VAR(Adc_GroupStatusType, ADC_VAR) ADC_GroupStatus[ADC_MAX_GROUPS];

/**
 * @brief   Structure for the unit status.
 *
 *
 * @api
 */
VAR(Adc_UnitStatusType, ADC_VAR) ADC_UnitStatus[ADC_MAX_HW_UNITS];


/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
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
/* put all ADC code into defined section */
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#define ADC_START_SEC_CODE
#include "MemMap.h"
/* lint -restore */

/**
 * @brief   Initializes the ADC hardware unit and the driver.
 * @details This function will initialize both the ADC HW unit and
 *          the driver structures.
 * @note    The function Autosar Service ID[hex]: 0x00.
 * @note    Synchronous.
 * @note    Non Reentrant function.
 *
 * @param[in]   ConfigPtr   Pointer to configuration set in Variant PB
 *              (Variant PC requires a NULL_PTR).
 *
 * @requirements            ADC054, ADC056, ADC077, ADC107, ADC246,
 *                          ADC247, ADC248, ADC249, ADC250, ADC307,
 *                          ADC342, ADC343, ADC344, ADC365.
 *
 * @remarks Covers:         ADC054, ADC107, ADC246, ADC247, ADC248,
 *                          ADC249, ADC250, ADC342, ADC343, ADC344,
 *                          ADC365, ADC056, ADC077 and ADC307
 *                          are Implemented in ADCDig_LLD_Init()
 *                          function.
 * @remarks Implements:     DADC02001, DADC02002.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_Init
(
    P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) ConfigPtr
)
{
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* ADC107 */
    if (Adc_Cfg_Ptr != NULL_PTR)
    {
        /* Error: ADC already initialized */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_INIT_ID,
                        (uint8)ADC_E_ALREADY_INITIALIZED);
    }
    #ifdef ADC_PRECOMPILE_SUPPORT  /*  PC Variant*/
    /* ADC344 */
    else if (ConfigPtr != NULL_PTR)
    {
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_INIT_ID,
                        (uint8)ADC_E_PARAM_CONFIG);
    }
    #else  /* PB Variant*/
    /* ADC343 ....Error: Null pointer provided as parameter */
    else if (ConfigPtr == NULL_PTR)
    {
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_INIT_ID,
                        (uint8)ADC_E_PARAM_CONFIG);
    }
    #endif /*  ADC_PRECOMPILE_SUPPORT */
    else
    {
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
        #ifdef ADC_PRECOMPILE_SUPPORT  /*  PC Variant*/
        /* ADC342 */
        Adc_Cfg_Ptr = &Adc_ConfigPC;
        #else  /* PB Variant*/
        /* ADC054 */
        Adc_Cfg_Ptr = ConfigPtr;
        #endif /*  ADC_PRECOMPILE_SUPPORT */
        Adc_LLD_Init(Adc_Cfg_Ptr);
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
}

/**
 * @brief   Initializes the group specific ADC result buffer pointer as
 *          configured to point to the DataBufferPtr address which is
 *          passed as parameter.
 * @details Initializes the group specific ADC result buffer pointer as
 *          configured to point to the DataBufferPtr address which is
 *          passed as parameter. The ADC driver stores all group
 *          conversion results to result buffer addressed with the
 *          result buffer pointer. Adc_SetupResultBuffer determines the
 *          address of the result buffer. After reset, before a group
 *          conversion can be started, an initialization of the ADC
 *          result buffer pointer is required.
 *
 * @pre     ADC422.
 *
 * @note    The function Autosar Service ID[hex]: 0x0c.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 * @param[in]   DataBufferPtr   ADC result buffer pointer is initialized
 *                              with the value of the data buffer pointer.
 *
 * @return      Std_ReturnType  Standard return type.
 *
 * @retval      E_OK:           Result buffer pointer initialized correctly.
 * @retval      E_NOT_OK:       Operation failed or development error
 *                              occured.
 *

 *
 * @requirements                ADC419, ADC420, ADC421, ADC422, ADC423.
 *
 * @remarks Covers:             ADC419, ADC420, ADC421, ADC422, ADC423.
 * @remarks Implements:         DADC02013.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_SetupResultBuffer
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
)
{
    P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) GroupPtr = NULL_PTR;
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_NOT_OK;

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC423): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_SETUPRESULTBUFFER_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
    else
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
        /*lint -save -e960 */
        GroupPtr = &Adc_Cfg_Ptr->Groups[Group];
        /* ADC420 */
        (GroupPtr->ResultsBufferPtr[Group]) = DataBufferPtr;
        /*lint -restore */
        TempReturn = (Std_ReturnType)E_OK;
    }
    return(TempReturn);
}

#if (ADC_DEINIT_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Returns all ADC HW Units to a state comparable to their
 *          power on reset state.
 * @details Returns all ADC HW Units to a state comparable to their
 *          power on reset state, and de-initialize the ADC MCAL driver.
 *
 * @note    The function Autosar Service ID[hex]: 0x01.
 * @note    Synchronous.
 * @note    Non Reentrant function.
 *
 * @requirements            ADC110, ADC111, ADC112, ADC154, ADC228,
 *                          ADC366.
 *
 * @remarks Covers:         ADC110, ADC111, ADC112, ADC154, ADC228,
 *                          ADC366.
 * @remarks Implements:     DADC02006, DADC08005, DADC02013.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_DeInit(void)
{
    VAR(uint8,AUTOMATIC) Group=0U; /* Group index */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(boolean,AUTOMATIC) flag = (boolean)FALSE; /*  flag to set if ADC is still converting */

    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* ADC154  Error: called prior to initialization or after de-initialization */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DEINIT_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else
    {
        /*  Check if ADC is still converting */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_03);
        for(;Group<(uint8)ADC_MAX_GROUPS;Group++)
        {
            if((ADC_GroupStatus[Group].Conversion != ADC_IDLE)&&
               (ADC_GroupStatus[Group].Conversion != ADC_STREAM_COMPLETED))
            {
                flag = (boolean)TRUE;
                break;
            }
        }
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_03);
        if (flag == (boolean)TRUE)
        {
            /* ADC112: Error: ADC is converting */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_DEINIT_ID,
                            (uint8)ADC_E_BUSY);
        }
        else
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
        {
            for(Group=(uint8)0;Group<(uint8)(Adc_Cfg_Ptr->GroupCount);Group++)
            {
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
                /*lint -save -e960 */
                Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] = NULL_PTR;
                /*lint -restore */
            }
            Adc_LLD_DeInit();
        }
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
}
#endif /* #if (ADC_DEINIT_API == STD_ON) */


#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Starts the conversion of all channels of
 *          the requested ADC Channel group.
 * @details This function will start the SW conversion of all channels
 *          of the requested ADC channel group.
 * @note    The function Autosar Service ID[hex]: 0x02.
 * @note    Asynchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 *
 * @requirements                ADC061, ADC125, ADC133, ADC146, ADC156,
 *                              ADC259, ADC294, ADC346, ADC348, ADC351,
 *                              ADC367, ADC424, ADC426, ADC427, ADC428,
 *                              ADC431.
 * @remarks Covers:             ADC061, ADC125, ADC133, ADC146, ADC156,
 *                              ADC259, ADC294, ADC346, ADC348, ADC351,
 *                              ADC367, ADC424, ADC426, ADC427, ADC428,
 *                              ADC431, FSL_ADC001.
 * @remarks Implements:         DADC02004, DADC08006, DADC02013.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_StartGroupConversion
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware unit on which the requested group will run */
    VAR(Adc_HwUnitType, AUTOMATIC) unit = (Adc_HwUnitType)0;
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
        VAR(boolean, AUTOMATIC) Error_flag = (boolean)FALSE; /*  Set flag when error is reported */
    #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    VAR(boolean,AUTOMATIC) flag = (boolean)FALSE;
    VAR(uint8,AUTOMATIC) index = (uint8)0;
    #endif
    #if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(boolean,AUTOMATIC) Implicity = (boolean)FALSE;
    #endif
    #endif

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC294): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_STARTGROUPCONVERSION_ID,
                        (uint8)ADC_E_UNINIT);
        Error_flag = (boolean)TRUE;
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC125): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_STARTGROUPCONVERSION_ID,
                        (uint8)ADC_E_PARAM_GROUP);
        Error_flag = (boolean)TRUE;
    } else {
      /* do nothig for misra */
    }
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Error_flag == (boolean)FALSE)
    {
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
        /* Get the unit to which the group belongs to */
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
        /*lint -save -e960 */
        unit = ADC_GroupUnit(Group);
        /*lint -restore */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
            #if (ADC_ENABLE_QUEUING == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
                /*lint -save -e960 */
                if((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_ONESHOT)||
                    ((Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_CONTINUOUS)&&
                    (Adc_Cfg_Ptr->Groups[Group].AccessMode ==ADC_ACCESS_MODE_STREAMING)&&
                    (Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)))
                /*lint -restore */
                {
                    Implicity = (boolean)TRUE; /* The current group can be implicitly stopped */
                }
                else
                {
                    Implicity = (boolean)FALSE; /* The current group cannot be implicitly stopped */
                }
            #endif  /* ADC_ENABLE_QUEUING == STD_ON */
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            if (Adc_Cfg_Ptr->Groups[Group].TriggerSource  != ADC_TRIGG_SRC_SW)
            /*lint -restore */
            {
                /* Error (ADC133): trigger source configured as hardware */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_STARTGROUPCONVERSION_ID,
                                (uint8)ADC_E_WRONG_TRIGG_SRC);
            }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            else if (Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] == NULL_PTR)
            /*lint -restore */
            {
                /* Error (ADC424): Result buffer pointer uninitialized */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_STARTGROUPCONVERSION_ID,
                                (uint8)ADC_E_BUFFER_UNINIT);
            }
        else
        {
            /* enter critical section to protect against ISR updating the global
               variables used in tests - consistency */
            SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
            #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
                #if (ADC_ENABLE_QUEUING == STD_OFF)
                /* In this case any SW conversion is ongoing */
                if (ADC_UnitStatus[unit].QueueIndex != (Adc_QueueIndexType)0)
                {
                  #if (ADC_SW_INJ_CONFIGURED == STD_ON)
                  /* Injected conversion mode */
                  if (Adc_Cfg_Ptr->Groups[Group].type != (Adc_GroupConvType)ADC_CONV_TYPE_INJECTED)
                  #endif
                  {
                    /* error occured, exit critical section */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                    /* Error (ADC346):  (ADC426)*/
                    Det_ReportError((uint16)ADC_MODULE_ID,
                                    (uint8)0U,
                                    (uint8)ADC_STARTGROUPCONVERSION_ID,
                                    (uint8)ADC_E_BUSY);
                  }
                }
                #else /* ADC_ENABLE_QUEUING == STD_ON */
                if ((Implicity == (boolean)FALSE)&&(ADC_GroupStatus[Group].Conversion != ADC_IDLE))
                {
                  /* error occured, exit critical section */
                  SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                  /* Error (ADC351): */
                  Det_ReportError((uint16)ADC_MODULE_ID,
                                  (uint8)0U,
                                  (uint8)ADC_STARTGROUPCONVERSION_ID,
                                  (uint8)ADC_E_BUSY);
                }
                else if ((Implicity == (boolean)TRUE)&&
                         (ADC_GroupStatus[Group].Conversion != ADC_IDLE)&&
                         (ADC_GroupStatus[Group].Conversion != ADC_STREAM_COMPLETED))
                {
                  /* error occured, exit critical section */
                  SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                  /* Error (ADC428):  */
                  Det_ReportError((uint16)ADC_MODULE_ID,
                                  (uint8)0U,
                                  (uint8)ADC_STARTGROUPCONVERSION_ID,
                                  (uint8)ADC_E_BUSY);
                }
                #endif /* ADC_ENABLE_QUEUING == STD_ON */
            #else /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE*/
                if(ADC_UnitStatus[unit].QueueIndex > (Adc_QueueIndexType)0)
                {
                    for(index = (uint8)0; index < ADC_UnitStatus[unit].QueueIndex; index++)
                    {
                        if(ADC_GroupInQueue(unit,index) == Group)
                        {
                            flag = (boolean)TRUE;
                        }
                    }
                }
                if ((((ADC_UnitStatus[unit].Queue[0] == Group)&&
                      (ADC_UnitStatus[unit].QueueIndex > (Adc_QueueIndexType)0))||
                      (flag == (boolean)TRUE))&&
                      (Implicity == (boolean)FALSE))
                {
                    /* error occured, exit critical section */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                    /* Error (ADC348) -- ADC335*/
                    Det_ReportError((uint16)ADC_MODULE_ID,
                                   (uint8)0U,
                                   (uint8)ADC_STARTGROUPCONVERSION_ID,
                                   (uint8)ADC_E_BUSY);
                }
                else if (((ADC_GroupStatus[Group].Conversion != ADC_IDLE)&&
                          (ADC_GroupStatus[Group].Conversion != ADC_STREAM_COMPLETED))&&
                          (Implicity == (boolean)TRUE))
                {
                    /* error occured, exit critical section */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                     /* Error (ADC427)-- ADC335  */
                    Det_ReportError((uint16)ADC_MODULE_ID,
                                    (uint8)0U,
                                    (uint8)ADC_STARTGROUPCONVERSION_ID,
                                    (uint8)ADC_E_BUSY);
                }
            #endif  /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
            else if(ADC_UnitStatus[unit].QueueIndex >= (ADC_QUEUE_MAX_DEPTH_MAX))
            {
                /* error occured, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
                /* Error: queue is full */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_STARTGROUPCONVERSION_ID,
                                (uint8)ADC_E_QUEUE_FULL);
            }
            else
            {
                /* everything ok, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_05);
    #else
                /* open code blocks used if DET is on */
    {
        {
            {
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
            Adc_LLD_StartGroupConversion(Group,unit);
        }
        }
    } /* end of if (flag == (boolean)TRUE) condition */
}
/**
 * @brief   Stops the conversion of all channels of the requested ADC
 *          Channel group.
 * @details This function will stop the SW conversion of all channels
 *          of the requested ADC channel group.
 * @note    The function Autosar Service ID[hex]: 0x03.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 *
 * @requirements                ADC126, ADC155, ADC164, ADC241, ADC260,
 *                              ADC283, ADC295, ADC360, ADC368, ADC385,
 *                              ADC386.
 *
 * @remarks Covers:             ADC126, ADC155, ADC164, ADC241, ADC260,
 *                              ADC283, ADC295, ADC360, ADC368, ADC385,
 *                              ADC386.
 * @remarks Implements:         DADC02009, DADC08006.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_StopGroupConversion
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) unit = (Adc_HwUnitType)0;

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC295): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_STOPGROUPCONVERSION_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC126): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_STOPGROUPCONVERSION_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
    /*lint -save -e960 */
    else if ((Adc_Cfg_Ptr->Groups[Group].TriggerSource) != ADC_TRIGG_SRC_SW)
    /*lint -restore */
    {
        /* Error (ADC164): trigger source configured as hardware */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_STOPGROUPCONVERSION_ID,
                        (uint8)ADC_E_WRONG_TRIGG_SRC);
    }
    else
    {
        /* enter critical section */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_19);
        if(ADC_GroupStatus[Group].Conversion == ADC_IDLE)
        {
            /* exit critical section */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_19);
            /* Error (ADC241): group not started */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_STOPGROUPCONVERSION_ID,
                            (uint8)ADC_E_IDLE);
        }
        else
        {
            /* exit critical section */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_19);
    #else
    {
        {
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            unit = ADC_GroupUnit(Group);
            /*lint -restore */
            Adc_LLD_StopGroupConversion(Group,unit);
        }
    }
}
#endif /* #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */


#if (ADC_READ_GROUP_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Reads the group conversion results.
 * @details Reads the group conversion results of the last completed
            conversion round of the requested group and stores the
            channel values starting at the DataBufferPtr address.
            The group channel values are stored in ascending channel
            number order (in contrast to the storage layout of the
            result buffer if streaming access is configured).
 *
 * @note    The function Autosar Service ID[hex]: 0x04.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC Channel group.
 * @param[in]   DataPtr         ADC result buffer pointer is initialized
 *                              with the value of the data buffer pointer.
 *
 * @return      Std_ReturnType  Standard return type.
 *
 * @retval      E_OK:           results are available and written to the
 *                              data buffer.
 * @retval      E_NOT_OK:       no results are available or development
 *                              error occured.
 *
 * @requirements                ADC075, ADC113, ADC122, ADC152, ADC296,
 *                              ADC329, ADC330, ADC331, ADC359, ADC369,
 *                              ADC388.
 *
 * @remarks Covers:             ADC075, ADC113, ADC122, ADC152, ADC296,
 *                              ADC329, ADC330, ADC331, ADC359, ADC369,
 *                              ADC388.
 * @remarks Implements: DADC02005, DADC08008.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup
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
                        (uint8)ADC_VALUEREADGROUP_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC152): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_VALUEREADGROUP_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
    else
    {
        /* enter critical section */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_18);
        if ((ADC_GroupStatus[Group].Conversion == ADC_IDLE)&&
            (ADC_GroupStatus[Group].AlreadyConverted == ADC_NOT_YET_CONVERTED))
        {
            /* exit critical section */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_18);
            /* Error (ADC388): conversion not started */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_VALUEREADGROUP_ID,
                            (uint8)ADC_E_IDLE);
        }
        else
        {
            /* exit critical section */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_18);
    #else
    {
        {
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
            Adc_ReadGroupRet = Adc_LLD_ReadGroup(Group, DataPtr);
        }
    }
    return(Adc_ReadGroupRet);
}
#endif /* #if (ADC_READ_GROUP_API == STD_ON) */



#if (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Enables the hardware trigger for the requested ADC Channel group.
 * @details This function will enable the HW trigger source for the requested
 *          ADC channel group. This function does set the CTU register for all platform that have
 *          the CTU Hw Unit.
 * @note    The function Autosar Service ID[hex]: 0x05.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group       Numeric ID of requested ADC channel group.
 *
 * @requirements            ADC114, ADC120, ADC128, ADC136, ADC144,
 *                          ADC281, ADC297, ADC321, ADC349, ADC265,
 *                          ADC353, ADC370, ADC425, ADC432, ADC273.
 *
 * @remarks Covers:         ADC114, ADC120, ADC128, ADC136, ADC144,
 *                          ADC281, ADC297, ADC321, ADC349, ADC265,
 *                          ADC353, ADC370, ADC425, ADC432, ADC273.
 * @remarks Implements:     DADC02007, DADC08007, DADC02013.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware Unit on which the requested group will run */
    VAR(Adc_HwUnitType,AUTOMATIC) unit = (Adc_HwUnitType)0;
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(boolean, AUTOMATIC) Error_flag = (boolean)FALSE; /* Set flag when error is reported */
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC297): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_UNINIT);
        Error_flag = (boolean)TRUE;
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC128): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
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
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
        /* Get the unit to which the group belongs to */
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
        /*lint -save -e960 */
        unit = ADC_GroupUnit(Group);
        /*lint -restore */
        #if (ADC_DEV_ERROR_DETECT == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            if (Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] == NULL_PTR)
            /*lint -restore */
            {
                /* Error (ADC425): Result buffer pointer uninitialized */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                (uint8)ADC_E_BUFFER_UNINIT);
            }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource == ADC_TRIGG_SRC_SW)
            /*lint -restore */
            {
                /* Error (ADC136): trigger source configured as software */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                (uint8)ADC_E_WRONG_TRIGG_SRC);
            }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
            /*lint -save -e960 */
            else if ((Adc_Cfg_Ptr->Groups[Group].mode) != ADC_CONV_MODE_ONESHOT)
            /*lint -restore */
            {
                /* Error (ADC281): group configured in continuous mode */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                (uint8)ADC_E_WRONG_CONV_MODE);
            }
        else
        {
            /* number of groups in the hardware queue */
            VAR(Adc_QueueIndexType,AUTOMATIC) noGroupsInHWQueue = (Adc_QueueIndexType)0;
            #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) /* No priority */
                #if (ADC_ENABLE_QUEUING == STD_OFF) /* No Queue */
                    /* number of groups in the software queue */
                    VAR(Adc_QueueIndexType,AUTOMATIC) noGroupsInSWQueue = (Adc_QueueIndexType)0;
                #endif
            #endif
            /* enter critical section to protect agains queue modifications */
            SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_04);
            /* read now the queue sizes */
            noGroupsInHWQueue= ADC_GroupsInHwQueue(unit); /* hardware queue size */
            #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) /* No priority */
                #if (ADC_ENABLE_QUEUING == STD_OFF) /* No Queue */
                    noGroupsInSWQueue= ADC_UnitStatus[unit].QueueIndex; /* software queue size */
                    /* In this case any conversion is ongoing */
                    if ((noGroupsInSWQueue != (Adc_QueueIndexType)0)||
                        (noGroupsInHWQueue!=(Adc_QueueIndexType)0))
                    {
                        /* error occured, exit critical section */
                        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_04);
                        /* [ADC321] unit is busy */
                        Det_ReportError((uint16)ADC_MODULE_ID,
                                        (uint8)0U,
                                        (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                        (uint8)ADC_E_BUSY);
                    }
                    else
                #endif
            #endif
            #if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
            if ((ADC_GroupStatus[Group].HwTriggering == ADC_HWTRIGGER_ENABLED)||
                (noGroupsInHWQueue >= (uint8)ADC_HW_QUEUE))
            #else
            if ((ADC_GroupStatus[Group].HwTriggering == ADC_HWTRIGGER_ENABLED)&&
                (noGroupsInHWQueue!= (uint8)0))
            #endif
            {
                /* error occured, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_04);
                /* [ADC349] group is already enabled */
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                (uint8)ADC_E_BUSY);
            }
            else if (noGroupsInHWQueue >= (Adc_QueueIndexType)ADC_HW_QUEUE)
            {
                /* error occured, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_04);
                /*[ADC353]*/
                Det_ReportError((uint16)ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_ENABLEHARDWARETRIGGER_ID,
                                (uint8)ADC_E_QUEUE_FULL);
            }
            else
            {
                /* everything ok, exit critical section */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_04);
    #else /* ADC_DEV_ERROR_DETECT == STD_OFF */
            /* open code blocks used if DET is on */
    {
        {
            {
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
            Adc_LLD_EnableHardwareTrigger(Group,unit);
        }
        }
  } /* end of if (flag == (boolean)FALSE) condition */
}

/**
 * @brief   Disables the hardware trigger for the requested ADC Channel group.
 * @details This function will disable the HW trigger source for the requested
 *          ADC channel group.
 * @note    The function Autosar Service ID[hex]: 0x06.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group       Numeric ID of requested ADC channel group.
 *
 * @requirements            ADC116, ADC121, ADC129, ADC137, ADC145, ADC157,
 *                          ADC266, ADC282, ADC298, ADC304, ADC361,
 *                          ADC371, ADC429.
 *
 * @remarks Covers:         ADC116, ADC121, ADC129, ADC137, ADC145, ADC157,
 *                          ADC266, ADC282, ADC298, ADC304, ADC361,
 *                          ADC371, ADC429.
 * @remarks Implements:     DADC02008, DADC08007.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) unit = (Adc_HwUnitType)0;

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC298): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC129): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
    /*lint -save -e960 */
    else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource == ADC_TRIGG_SRC_SW)
    /*lint -restore */
    {
        /* Error (ADC137): trigger source configured as software */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_WRONG_TRIGG_SRC);
    }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
    /*lint -save -e960 */
    else if ((Adc_Cfg_Ptr->Groups[Group].mode) != ADC_CONV_MODE_ONESHOT)
    /*lint -restore */
    {
        /* Error (ADC282): group configured in continuous mode */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_WRONG_CONV_MODE);
    }
    else if (ADC_GroupStatus[Group].HwTriggering == ADC_HWTRIGGER_DISABLED)
    {
        /* ADC304: group not enabled */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEHARDWARETRIGGER_ID,
                        (uint8)ADC_E_IDLE);
    }
    else
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
        /* Get the unit to which the group belongs to */
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
        /*lint -save -e960 */
        unit = ADC_GroupUnit(Group);
        /*lint -restore */
        Adc_LLD_DisableHardwareTrigger(Group,unit);
    }
}
#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */


#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Enables the notification mechanism for the requested ADC
 *          Channel group.
 * @details This function will enable the notification mechanism only for
 *          the requested ADC channel group.
 * @note    The function Autosar Service ID[hex]: 0x07.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 *
 * @requirements                ADC057, ADC100, ADC130, ADC165, ADC299,
 *                              ADC372.
 *
 * @remarks Covers:             ADC057, ADC100, ADC130, ADC165, ADC299,
 *                              ADC372.
 * @remarks Implements:         DADC02002, DADC08003.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_EnableGroupNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr==NULL_PTR)
    {
        /* Error (ADC299): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC130): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
    /*lint -save -e960 */
    else if (Adc_Cfg_Ptr->Groups[Group].Notification == NULL_PTR)
    /*lint -restore */
    {
        /* Error (ADC165): notification function pointer is NULL */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_ENABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_NOTIF_CAPABILITY);
    }
    else
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
        /* ADC057 */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_00);
        ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_ENABLED;
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_00);
    }
}
/**
 * @brief   Disables the notification mechanism for the requested ADC
 *          Channel group.
 * @details This function will disable the notification mechanism only for
 *          the requested ADC channel group.
 * @note    The function Autosar Service ID[hex]: 0x08.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 *
 * @requirements                ADC058, ADC101, ADC131, ADC166, ADC300,
 *                              ADC373.
 *
 * @remarks Covers:             ADC058, ADC101, ADC131, ADC166, ADC300,
 *                              ADC373.
 * @remarks Implements:         DADC02003, DADC08003.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_DisableGroupNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC300): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC131): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_PARAM_GROUP);
    }
/**
@note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used
- See @ref Adc_c_REF_4
*/
    /*lint -save -e960 */
    else if (Adc_Cfg_Ptr->Groups[Group].Notification == NULL_PTR)
    /*lint -restore */
    {
        /* Error (ADC166): notification function pointer is NULL */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_DISABLEGROUPNOTIFICATION_ID,
                        (uint8)ADC_E_NOTIF_CAPABILITY);
    }
    else
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
        /* ADC058 */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_01);
        ADC_GroupStatus[Group].Notification = ADC_NOTIFICATION_DISABLED;
        SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_01);
    }
}
#endif /* #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */
/**
 * @brief   Returns the conversion status of the requested ADC Channel group.
 * @details This function will return the converison status of the requested
 *          ADC Channel group.
 * @note    The function Autosar Service ID[hex]: 0x09.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group           Numeric ID of requested ADC channel group.
 *
 * @return                      Adc_StatusType Conversion status for the
 *                              requested group.
 *
 * @retval                      ADC_IDLE  in case of errors.
 * @retval                      Conversion status else.
 *
 *
 * @requirements                ADC220, ADC221, ADC222, ADC224, ADC225,
 *                              ADC226, ADC301, ADC305, ADC325, ADC374.
 *
 * @remarks Covers:             ADC220, ADC221, ADC222, ADC224, ADC225,
 *                              ADC226, ADC301, ADC305, ADC325, ADC374.
 * @remarks Implements:         DADC02011.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_StatusType, AUTOMATIC) tempReturn = ADC_IDLE;

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC301): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_GETGROUPSTATUS_ID,
                        (uint8)ADC_E_UNINIT);
        tempReturn = ADC_IDLE;
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC225): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_GETGROUPSTATUS_ID,
                        (uint8)ADC_E_PARAM_GROUP);
        tempReturn = ADC_IDLE;
    }
    else
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    {
        /* ADC226 */
        SchM_Enter_Adc(SCHM_ADC_INSTANCE_0,ADC_EXCLUSIVE_AREA_02);

        /* ADC220 */
        tempReturn = ADC_GroupStatus[Group].Conversion;

        SchM_Exit_Adc(SCHM_ADC_INSTANCE_0,ADC_EXCLUSIVE_AREA_02);
    }
    return(tempReturn);
}
/**
 * @brief   Returns the number of valid samples per channel.
 * @details Returns the number of valid samples per channel, stored in
 *          the result buffer. Reads a pointer, pointing to a position
 *          in the group result buffer. With the pointer position, the
 *          results of all group channels of the last completed conversion
 *          round can be accessed. With the pointer and the return value,
 *          all valid group conversion results can be accessed (the user
 *          has to take the layout of the result buffer into account).
 *
 * @note    The function Autosar Service ID[hex]: 0x0b.
 * @note    Synchronous.
 * @note    Reentrant function.
 *
 * @param[in]   Group                   Numeric ID of requested ADC
 *                                      channel group.
 *
 * @param[out]  PtrToSamplePtr          Pointer to result
 *                                      buffer pointer.
 *
 * @return      Adc_StreamNumSampleType Number of valid samples per channel.
 *
 * @retval      0                       in case of errors.
 * @retval                              Number of valid samples per channel.
 *
 * @requirements                        ADC214, ADC215, ADC216, ADC218,
 *                                      ADC302, ADC326, ADC327, ADC328,
 *                                      ADC375, ADC382, ADC387, ADC219,
 *                                      ADC418.
 *
 * @remarks Covers:                     ADC214, ADC215, ADC216, ADC218,
 *                                      ADC302, ADC326, ADC327, ADC328,
 *                                      ADC375, ADC382, ADC387, ADC219,
 *                                      ADC418.
 * @remarks Implements:                 DADC02010.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_GetStreamLastPointer
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
)
{
    VAR(Adc_StreamNumSampleType, AUTOMATIC) NumberOfResults = (Adc_StreamNumSampleType)0U;
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC302): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_GETSTREAMLASTPOINTER_ID,
                        (uint8)ADC_E_UNINIT);
        *PtrToSamplePtr = NULL_PTR;
    }
    else if (Group >= Adc_Cfg_Ptr->GroupCount)
    {
        /* Error (ADC218): non-existing group ID */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_GETSTREAMLASTPOINTER_ID,
                        (uint8)ADC_E_PARAM_GROUP);
        *PtrToSamplePtr = NULL_PTR;
    }
    else
    {
        /* enter critical region */
        SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_17);

        if (ADC_GroupStatus[Group].Conversion == ADC_IDLE)
        {
            /* exit critical region */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_17);
            /* Error (ADC215): idle state */
            Det_ReportError((uint16)ADC_MODULE_ID,
                            (uint8)0U,
                            (uint8)ADC_GETSTREAMLASTPOINTER_ID,
                            (uint8)ADC_E_IDLE);
            *PtrToSamplePtr = NULL_PTR;
        }
        else
        {
            /* exit critical region */
            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_17);
    #else
    {
        {
    #endif /* ADC_DEV_ERROR_DETECT == STD_ON */
            NumberOfResults = Adc_LLD_GetStreamLastPointer(Group, PtrToSamplePtr);
        }
    }
    return(NumberOfResults);
}

#if (ADC_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Returns the version information of this module.
 *
 * @note    The function Autosar Service ID[hex]: 0x0A.
 * @note    Synchronous.
 * @note    Non Reentrant function.
 *
 * @param[out]  versioninfo     Pointer to where to store the version
 *                              information of this module.
 *
 * @requirements                ADC236, ADC237, ADC324, ADC376.
 *
 * @remarks Covers:             ADC236, ADC237, ADC324, ADC376.
 * @remarks Implements:         DADC02012, DADC08004, DADC02013.
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_GetVersionInfo
(
    P2VAR(Std_VersionInfoType , AUTOMATIC, ADC_APPL_DATA) versioninfo
)
{
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_Cfg_Ptr == NULL_PTR)
    {
        /* Error (ADC324): called prior to initializing */
        Det_ReportError((uint16)ADC_MODULE_ID,
                        (uint8)0U,
                        (uint8)ADC_GETVERSIONINFO_ID,
                        (uint8)ADC_E_UNINIT);
    }
    #endif  /* ADC_DEV_ERROR_DETECT == STD_ON */
    /* ADC236 */
    (versioninfo)->vendorID = (uint16)ADC_VENDOR_ID;
    (versioninfo)->moduleID = (uint16)ADC_MODULE_ID;
    (versioninfo)->instanceID = (uint8) 0;
    (versioninfo)->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
    (versioninfo)->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
    (versioninfo)->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;
}
#endif

#if (ADC_SET_MODE_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Set the ADC mode either to powerdown or normal.
 *
 * @note    The function Non Autosar Service ID[hex]: 0x10.
 * @note    Non Reentrant function.
 *
 * @param[in]  SetMode     ADC_NORMAL_MODE,ADC_POWER_DOWN_MODE
 * @return - Std_ReturnType - E_OK or E_NOT_OK.
 * @retval - E_OK - in case of successfull settings.
 * @retval - E_NOT_OK - in case of unsuccessfull settings.
 *
 * @requirements:
 *
 * @remarks Covers:
 * @remarks Implements:
 *
 * @note Violates MISRA 2004 Advisory Rule 8.10, external function could be made static
 *       - See @ref Adc_c_REF_3
 *
 * @api
 */
FUNC (Std_ReturnType, ADC_CODE) Adc_SetMode(VAR(Adc_SetModeType, AUTOMATIC) SetMode)
{
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_NOT_OK;
  if(SetMode == ADC_POWER_DOWN_MODE)
    {
        #if (ADC_DEV_ERROR_DETECT == STD_ON)

            VAR(Adc_HwUnitType, AUTOMATIC) unit=(Adc_HwUnitType)0; /* HW unit index */
            VAR(boolean, AUTOMATIC) Returnval = (boolean)FALSE;
            for(unit=(uint8)0U; unit<(Adc_HwUnitType)(Adc_Cfg_Ptr->Misc.ADC_MAX_HWCFG); unit++)
            {
                if((ADC_UnitStatus[unit].Status == ADC_BUSY)
                #if (ADC_HW_TRIGGER_API == STD_ON)
                    ||(ADC_GroupsInHwQueue(unit)!=(Adc_QueueIndexType)0)
                #endif
                  ) /* In this case any conversion is ongoing */
                {
                    Returnval = (boolean)TRUE;
                }
            }
            if(Returnval == (boolean)TRUE)
            {
                /* Can't enter into powerdown mode report error to DET */
                Det_ReportError((uint16) ADC_MODULE_ID,
                                (uint8)0U,
                                (uint8)ADC_SETMODE_ID,
                                (uint8)ADC_E_SET_MODE);
                return (TempReturn);
            }
    else
    {
        #endif
    }
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
    #endif
    if ((SetMode == ADC_NORMAL_MODE)||
        (SetMode == ADC_POWER_DOWN_MODE))
    {
        return(Adc_LLD_SetMode(SetMode));
    }
    else
    {
         return (TempReturn);
    }
}
#endif

/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_c_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/* lint -restore */

#ifdef __cplusplus
}
#endif

/** @} */
