/*!
 * @file    Port.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - PORT driver high level driver.
 * @details Implementation of the AutoSar high level PORT driver.
 *
 * @addtogroup Port
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 **************************************************************************/

/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section PORT_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
 * This is an Autosar memory management requirement.
 *
 * @section PORT_C_REF_2
 * Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
 * There are different kinds of execution code sections.
 */

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @remarks Covers BSW00374, BSW00379, BSW00318
 */
#define PORT_VENDOR_ID_C         43
#define PORT_AR_MAJOR_VERSION_C  3
#define PORT_AR_MINOR_VERSION_C  0
#define PORT_AR_PATCH_VERSION_C  0
#define PORT_SW_MAJOR_VERSION_C  2
#define PORT_SW_MINOR_VERSION_C  0
#define PORT_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 * @file    Port.c
 * @remarks Covers PORT114, PORT131
 */
#include "Port.h"
#include "Port_LLD.h"

/**
 * @file    Port.c
 * @remarks Covers PORT129
 */
#include "Dem.h"

/**
 * @file    Port.c
 * @remarks Covers PORT100, PORT107
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
 * @file    Port.c
 * @remarks Covers PORT114
 */
/* Check if source file and Port header file are of the same vendor */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID)
    #error "Port.c and Port.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Port header file are of the same Autosar version */
    #if ((PORT_AR_MAJOR_VERSION_C != PORT_AR_MAJOR_VERSION) || \
         (PORT_AR_MINOR_VERSION_C != PORT_AR_MINOR_VERSION) || \
         (PORT_AR_PATCH_VERSION_C != PORT_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Port.c and Port.h are different"
    #endif
#endif
/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION))
  #error "Software Version Numbers of Port.c and Port.h are different"
#endif

/* Check if source file and Port_LLD.h file are of the same vendor */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID_LLD_H)
    #error "Port.c and Port_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if the source file and Port_LLD.h file are of the same Autosar version */
    #if ((PORT_AR_MAJOR_VERSION_C != PORT_AR_MAJOR_VERSION_LLD_H) || \
         (PORT_AR_MINOR_VERSION_C != PORT_AR_MINOR_VERSION_LLD_H) || \
         (PORT_AR_PATCH_VERSION_C != PORT_AR_PATCH_VERSION_LLD_H))
      #error "AutoSar Version Numbers of Port.c and Port_LLD.h are different"
    #endif
#endif
/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION_LLD_H) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION_LLD_H) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION_LLD_H))
  #error "Software Version Numbers of Port.c and Port_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((PORT_AR_MAJOR_VERSION != DEM_AR_MAJOR_VERSION) || \
         (PORT_AR_MINOR_VERSION != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Port.h and Dem.h are different"
    #endif
#endif

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((PORT_AR_MAJOR_VERSION != DET_AR_MAJOR_VERSION) || \
             (PORT_AR_MINOR_VERSION != DET_AR_MINOR_VERSION))
          #error "AutoSar Version Numbers of Port.h and Det.h are different"
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
/**
 * @brief Segment descriptor for data arranged in array
 * @remarks Covers REQ001, REQ002
 * @remarks Implements DESIGN001, DESIGN002
 */
#define PORT_START_SEC_VAR_UNSPECIFIED
/**
 * @file  Port.c
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_C_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_C_REF_2
 */
#include "MemMap.h"

/**
 * @brief Pointer initialized during init with the address of the received configuration structure.
 * @details Will be used by all functions to access the configuration data.
 */
P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_DATA) Port_Cfg_Ptr = NULL_PTR;

#define PORT_STOP_SEC_VAR_UNSPECIFIED
/**
 * @file  Port.c
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_C_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_C_REF_2
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
#define PORT_START_SEC_CODE
/**
 * @file  Port.c
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_C_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_C_REF_2
 */
#include "MemMap.h"


/**
 * @brief   Initializes the Port Driver module.
 * @details The function @p Port_Init() will initialize ALL ports and port pins
 *          with the configuration set pointed to by the parameter @p ConfigPtr.
 * @post    Port_Init() must be called before all other Port Driver module's functions
 *          otherwise no operation can occur on the MCU ports and port pins.
 *
 * @param[in] ConfigPtr     A pointer to the structure which contains
 *                          initialization parameters.
 *
 * @requirements    PORT078, PORT071, PORT113, PORT140, PORT100, PORT107,
 *                  PORT031, PORT051, PORT087, PORT105, PORT121, PORT002,
 *                  PORT003, PORT005, PORT113, PORT041, PORT042, PORT043.
 *
 * @api
 *
 * @remarks Covers PORT078, PORT071, PORT55, PORT140
 * @remarks Covers PORT100, PORT107
 * @remarks Covers PORT031, PORT051, PORT087
 * @remarks Covers PORT105
 * @remarks Covers PORT121
 * @remarks Covers PORT002, PORT003, PORT005, PORT113
 * @remarks Covers PORT041, PORT042, PORT043
 * @remarks Implements DESIGN001, DESIGN002, DPORT01013, DPORT01030
 * @remarks Implements DPORT01011, DPORT01015, DPORT01014, DPORT05000
 */
FUNC(void, PORT_CODE) Port_Init
(
    P2CONST(Port_ConfigType,AUTOMATIC,PORT_APPL_DATA) ConfigPtr
)
{
/**
 * @remarks Covers PORT100, PORT107
 */
#ifndef PORT_PRECOMPILE_SUPPORT
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (ConfigPtr == NULL_PTR)
    {

        /**
         * @remarks Covers PORT031, PORT051, PORT087
         */
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_ID,PORT_E_PARAM_CONFIG);
        /**
         * @remarks Covers PORT105
         */
        return;
    }
    else
#endif /*PORT_DEV_ERROR_DETECT */
#endif /* PORT_PRECOMPILE_SUPPORT*/
    {

#ifdef PORT_PRECOMPILE_SUPPORT
        if (ConfigPtr == NULL_PTR)
        {
            /**
             * @remarks Covers PORT121
             */
            /*If Development Error Detection is disabled and configPtr is a NULL Pointer, it's
            initialized to the default configuration */
            ConfigPtr = &Port_ConfigPC;

        }
#endif /* PORT_PRECOMPILE_SUPPORT*/

        /**
         * @remarks Covers PORT002, PORT003, PORT005, PORT113
         * @remarks Covers PORT041, PORT042, PORT043
         */
        /* Call Initialization function depending of the platform */
        PORT_LLD_Init(ConfigPtr);

        /* Save pointer in global variable for refreshing pin directions */
        Port_Cfg_Ptr = ConfigPtr;
    }
}

/**
 * @brief   Sets the port pin direction.
 * @details The function @p Port_SetPinDirection() will set the port pin direction
 *          during runtime.
 * @pre     @p Port_Init() must have been called first. In order to change the
 *          pin direction the PortPinDirectionChangeable flag must have been set
 *          to @p TRUE.
 *
 * @param[in] Pin           Pin ID number.
 * @param[in] Direction     Port Pin direction.
 *
 * @requirements    PORT059, PORT063, PORT086, PORT117, PORT141.
 *
 * @api
 *
 * @remarks Covers PORT059, PORT063, PORT086, PORT117, PORT141
 * @remarks Implements DESIGN001, DESIGN002, DPORT01013
 */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON) || defined(__DOXYGEN__)
FUNC(void, PORT_CODE) Port_SetPinDirection
(
    VAR(Port_PinType, PORT_VAR) Pin,
    VAR(Port_PinDirectionType, PORT_VAR) Direction
)
{
    /* Variable used to get current Pin configuration. */
    VAR(uint8, PORT_VAR) pinDirError;
/**
 * @remarks Covers PORT100, PORT107
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if port is initialized */
    if (Port_Cfg_Ptr == NULL_PTR)
    {
        /**
         * @remarks Covers PORT031, PORT051, PORT087
         */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check port pin validity */
    else if (Pin >= (Port_PinType)Port_Cfg_Ptr->numPins)
    {
        /**
         * @remarks Covers PORT031, PORT051, PORT087
         */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_PARAM_PIN);
    }
    /* Check port pin Direction validity */
    else if (!((Direction == PORT_PIN_IN) || (Direction == PORT_PIN_OUT)))
    {
        /**
         * @remarks Covers PORT038, PORT077
         */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_INVALID_DIRECTION);
    }
    /**
     * @remarks Covers PORT065
     */
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {

        pinDirError = (uint8)PORT_LLD_SetPinDirection(Pin, (Port_PinDirectionType)Direction );

/**
 * @remarks Covers PORT100, PORT107
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        if (pinDirError)
        {
            /**
             * @remarks Covers PORT031, PORT051, PORT087
             */
            Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_DIRECTION_UNCHANGEABLE);
        }
#endif /* PORT_DEV_ERROR_DETECT */
    }
}
#endif

/**
 * @brief   Refreshes port direction.
 * @details This function will refresh the direction of all configured ports to
 *          the configured direction.<br>
 *          The PORT driver will exclude from refreshing those port pins that
 *          are configured as "pin direction changeable during runtime".
 * @pre     @p Port_Init() must have been called first.
 *
 * @requirements    PORT060, PORT061, PORT117, PORT142.
 *
 * @api
 *
 * @remarks Covers PORT060, PORT061, PORT117, PORT142
 * @remarks Implements DESIGN001, DESIGN002, DPORT01012
 * @remarks Test_case TST_CS_001, TST_CS_001
 */
FUNC(void, PORT_CODE) Port_RefreshPortDirection
(
    void
)
{
/**
 * @remarks Covers PORT100, PORT107
 */
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if port is initialized */
    if (Port_Cfg_Ptr == NULL_PTR)
    {
        /** @remarks Covers PORT031, PORT051, PORT087, PORT146  */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_REFRESHPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {
        PORT_LLD_RefreshPortDirection(Port_Cfg_Ptr->numPins);
    }
}

/**
 * @brief   Sets the port pin mode.
 * @details The function @p Port_SetPinMode() will set the port pin mode of the
 *          referenced pin during runtime.
 * @pre     @p Port_Init() must have been called first.
 *
 * @param[in] Pin       Pin ID number.
 * @param[in] Mode      New Port Pin mode to be set on port pin.
 *
 * @requirements    PORT117, PORT145.
 *
 * @api
 *
 * @remarks Covers PORT117, PORT145
 * @remarks Implements DESIGN001, DESIGN002, DPORT01014
 */
#if (PORT_SET_PIN_MODE_API == STD_ON) || defined(__DOXYGEN__)
FUNC(void, PORT_CODE) Port_SetPinMode
(
    VAR(Port_PinType, PORT_VAR) Pin,
    VAR(Port_PinModeType, PORT_VAR) Mode
)
{
    VAR(uint8, PORT_VAR) pinModeError = (uint8)0U;

/**
 * @remarks Covers PORT100, PORT107
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if port is initialized */
    if (Port_Cfg_Ptr == NULL_PTR)
    {
        /**
         * @remarks Covers PORT031, PORT051, PORT087, PORT146
         */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_UNINIT);
    }
    else if (Pin >= (Port_PinType)Port_Cfg_Ptr->numPins)
    /* Check port pin validity */
    {
        /**
         * @remarks Covers PORT031, PORT051, PORT087, PORT146
         */
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_PARAM_PIN);
    }
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {
        /* Sets the port pin direction */
        pinModeError = (uint8)PORT_LLD_SetPinMode(Pin, Mode);

/**
 * @remarks Covers PORT100, PORT107
 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        if (pinModeError != (uint8)0)
        {
            /**
             * @remarks Covers PORT031, PORT051, PORT087, PORT146
             */
            Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)pinModeError);
        }
#endif /* PORT_DEV_ERROR_DETECT */
    }
}
#endif

/**
 * @brief   Returns the version information of this module.
 * @details The function @p Port_GetVersionInfo() will return the version
 *          information of this module. The version information includes:<br>
 *          - Module Id,
 *          - Vendor Id,
 *          - Vendor specific version numbers.
 *          .
 *
 * @param[in,out] pVersionInfo      Pointer to where to store the version
 *                                  information of this module.
 *
 * @requirements    PORT103
 *
 * @api
 *
 * @remarks Covers PORT103
 * @remarks Implements DESIGN001, DESIGN002, DPORT01015
 */
#if  (PORT_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
extern FUNC (void, PORT_CODE) Port_GetVersionInfo(P2VAR(Std_VersionInfoType, PORT_VAR_FAST, PORT_APPL_DATA) pVersionInfo)
{
/**
 * @remarks Covers PORT038, PORT077
 */
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if port is initialized */
    if (NULL_PTR == pVersionInfo)
    {
        Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_GETVERSIONINFO_ID, (uint8)PORT_E_INVALID_POINTER);
    }
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {
        /**
         * @remarks Covers PORT102
         */
        (pVersionInfo)->vendorID = (uint16)PORT_VENDOR_ID;
        (pVersionInfo)->moduleID = (uint16)PORT_MODULE_ID;
        (pVersionInfo)->instanceID = (uint8)PORT_INSTANCE_ID;
        (pVersionInfo)->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        (pVersionInfo)->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        (pVersionInfo)->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif /* PORT_VERSION_INFO_API == STD_ON */

#define PORT_STOP_SEC_CODE
/**
 * @file  Port.c
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_C_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_C_REF_2
 */
#include "MemMap.h"


#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
