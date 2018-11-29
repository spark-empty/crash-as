/**
   @file    Lin.c
   @version 2.0.0

   @brief   AUTOSAR Lin - API functions implementations
   @details API functions implementations

   Project AUTOSAR 3.0 MCAL
   Patform PA
   Peripheral ESCI
   Dependencies 

   ARVersion 3.0.0
   ARRevision ASR_REL_3_0_REV_0003
   ARConfVariant
   SWVersion 2.0.0
   BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

   (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
   All Rights Reserved.

   @addtogroup LIN
   @{
*/
/*=================================================================================================
=================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section LIN_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 *
 * @section LIN_C_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 *
 * @section LIN_C_REF_3
 * Violates MISRA 2004 Required Rule 19.15, Repeated include file EcuM.h 
 * This comes from the order of includes in the .c file and from include dependencies. 
 * As a safe approach, any file must include all its dependencies.
 *
 * @section LIN_C_REF_4
 * Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or 
 * functions at file scope shall have internal linkage unless external linkage is required. 
 * The respective code could not be made static because of layers architecture design of 
 * the driver.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Lin.h"
#include "Lin_LLD.h"
/*
 * @remarks Covers LIN075
 */
#include "LinIf_Cbk.h"
#include "Dem.h"
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file EcuM.h: 
 *       See @ref LIN_C_REF_3
 */
#include "EcuM.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*=================================================================================================
                                        LOCAL MACROS
=================================================================================================*/
/**
 * @remarks Covers LIN062
 * @{
 */
#define LIN_VENDOR_ID_C             43
#define LIN_AR_MAJOR_VERSION_C      3
#define LIN_AR_MINOR_VERSION_C      0
#define LIN_AR_PATCH_VERSION_C      0

#define LIN_SW_MAJOR_VERSION_C      2
#define LIN_SW_MINOR_VERSION_C      0
#define LIN_SW_PATCH_VERSION_C      0
/**@}*/
/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/** @remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_C != LIN_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin.c and Lin.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_C != LIN_AR_MAJOR_VERSION_LLD) || \
       (LIN_AR_MINOR_VERSION_C != LIN_AR_MINOR_VERSION_LLD) || \
       (LIN_AR_PATCH_VERSION_C != LIN_AR_PATCH_VERSION_LLD))
      #error "AutoSar Version Numbers of Lin.c and Lin_LLD.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_C != LIN_SW_MAJOR_VERSION_LLD) || \
     (LIN_SW_MINOR_VERSION_C != LIN_SW_MINOR_VERSION_LLD))
    #error "Software Version Numbers of Lin.c and Lin_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_C != STD_TYPES_AR_MAJOR_VERSION) || \
     (LIN_AR_MINOR_VERSION_C != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Lin.c and Std_Types.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_C != LIN_IF_AR_MAJOR_VERSION_CBK) || \
       (LIN_AR_MINOR_VERSION_C != LIN_IF_AR_MINOR_VERSION_CBK))
      #error "AutoSar Version Numbers of Lin.c and LinIf_Cbk.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_C != ECUM_CBK_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_C != ECUM_CBK_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin.c and EcuM_CBK.h are different"
  #endif

  #if ((LIN_AR_MAJOR_VERSION_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_C != ECUM_CFG_AR_MINOR_VERSION))
      #error "Software Version Numbers of Lin.c and EcuM_Cfg.h are different"
  #endif

  /* Check if the source file and Dem header file are of the same version */
  #if ((LIN_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin.c and Dem.h are different"
  #endif
#endif

#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* Check if the source file and Det header file are of the same version */
  #ifdef CHECK_AUTOSAR_VERSION
    #if ((LIN_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
         (LIN_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Lin.c and Det.h are different"
    #endif
  #endif
#endif

/*=================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
                                       LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/

/* put all LIN variables into defined section */
#define LIN_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* Global Configuration Pointer */
/**
 * @brief Pointer to the configuration structure.
 */
P2CONST(Lin_ConfigType,LIN_VAR,LIN_APPL_CONST) Lin_Cfg_Ptr = NULL_PTR;

/**
 * @brief Array containing channel configurations.
 */
P2CONST(Lin_ChannelConfigType,LIN_VAR,LIN_APPL_CONST) Lin_Channel_Cfg_Ptr[LIN_HW_MAX_MODULES];

/**
 * @brief LIN driver state machine.
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref LIN_C_REF_4
 */
VAR(uint8,LIN_VAR)Lin_LinDrvStatus = LIN_UNINIT;

/**
 * @brief LIN channel state machine.
 * @@remarks implements DLIN01102
 */
volatile VAR(uint8,LIN_VAR)Lin_LinChStatus[LIN_HW_MAX_MODULES];

/**
 * @brief LIN frame state machine.
 */
volatile VAR(uint8,LIN_VAR)Lin_LinChFrameStatus[LIN_HW_MAX_MODULES];

/**
 * @brief Frame header state machine.
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref LIN_C_REF_4
 */
volatile VAR(uint8,LIN_VAR)Lin_LinChHeaderStatus[LIN_HW_MAX_MODULES];

/**
 * @brief Frame error status.
 */
volatile VAR(uint8,LIN_VAR)Lin_LinChFrameErrorStatus[LIN_HW_MAX_MODULES];

/**
 * @brief Lin channel hardware map.
 */
VAR(sint8,LIN_VAR)Lin_ChannelHardwareMap[LIN_HW_MAX_AVAILABLE_MODULES];

/**
 * @brief LIN driver state machine.
 */
VAR(uint8, LIN_VAR) TransmitHeaderCommand[LIN_HW_MAX_MODULES];

/**
 * @brief LIN SDU buffer to be returned.
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, external ... could be made static: 
 *       See @ref LIN_C_REF_4
 */
VAR(uint8, AUTOMATIC) LinSduBuffAddress[LIN_HW_MAX_MODULES][LIN_MAX_DATA_LENGTH];

#define LIN_STOP_SEC_VAR_UNSPECIFIED
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_C_REF_2
 */
#include "MemMap.h"

/*=================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/

/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/
/**
@note put all LIN code into defined section
*/
#define LIN_START_SEC_CODE
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_C_REF_2
 */
#include "MemMap.h"

/**
 * @brief   Initializes the LIN module.
 * @details This function performs software initialization of LIN
 *          driver:
 *          - Clears the shadow buffer of all available Lin channels
 *          - Set LIN channel state machine of all available Lin
 *            channels to LIN_CH_UNINIT_STATE
 *          - Set frame operation state machine of all available LIN
 *            channels to LIN_CH_NOT_READY_STATE
 *          - Set driver state machine to LIN_INIT.
 *          .
 * @post    Driver status = LIN_INIT, channel status =
 *          LIN_CH_UNINIT_STATE.
 * @note    Autosar Service ID: 0x00.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Config        Pointer to LIN driver configuration set.
 *
 * @requirements LIN146, LIN171, LIN006,
 *               LIN084, LIN150, LIN008,
 *               LIN106, LIN099, LIN105.
 *
 * @api
 *
 * @remarks Implements: DLIN18000, DLIN01201
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */
FUNC(void, LIN_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_CONST) Config)
    {
    VAR(uint8,AUTOMATIC)Lin_ChLoop;
    VAR(uint8,AUTOMATIC)Lin_Hw_ChLoop;
    /* Check whether the LIN driver is in LIN_UNINIT state */
    /** @remarks implements DLIN18001 */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    if (Lin_LinDrvStatus != LIN_UNINIT)
        {
        /* LIN driver has been already initialized */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_INIT_ID,\
                (uint8)LIN_E_STATE_TRANSITION);
        }
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    /* i dont think it should be allowed to call the function with a NULL config pointer
    * no matter precompile support is defined or not
    * #ifndef LIN_PRECOMPILE_SUPPORT*/
    /* Check Config for not being a null pointer
    */
    if (Config == NULL_PTR)
        {
        /* Invalid pointer */
        /** @remarks implements DLIN18001 */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError ((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_INIT_ID,\
                 (uint8)LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
/* see the commnet above */
/*#ifdef LIN_PRECOMPILE_SUPPORT
    if (Config == NULL_PTR)
        {
        Config = Lin_Config_PC;
        }
#endif*/
    else
        {
        Lin_Cfg_Ptr = Config;
        /** @remarks implements DLIN01103*/
        for(Lin_ChLoop=(uint8)0U;Lin_ChLoop<LIN_HW_MAX_MODULES;Lin_ChLoop++)
            {
            /* Set LIN channel state machine to UNINT */
            Lin_LinChStatus[Lin_ChLoop] = LIN_CH_UNINIT_STATE;
            /* Set LIN channel frame operation state machine to LIN_CH_NOT_READY_STATE */
            Lin_LinChFrameStatus[Lin_ChLoop] = LIN_CH_NOT_READY_STATE;
            }
        for(Lin_Hw_ChLoop=(uint8)0U;Lin_Hw_ChLoop<LIN_HW_MAX_AVAILABLE_MODULES;Lin_Hw_ChLoop++)
            {
                Lin_ChannelHardwareMap[Lin_Hw_ChLoop]= -1;
            }
        /* Update LIN driver status to LIN_INIT */
        Lin_LinDrvStatus = LIN_INIT;
        }
    return; /* Exit function with no return */
    }

/**
 * @brief   Validates for upper layers the wake up of LIN channels.
 * @details This function identifies which LIN channel has been woken
 *          up by the LIN bus transceiver This API is used when the
 *          LIN channel wake up functionality is disabled (wake up
 *          interrupt is disabled) it checks the wake up flag from
 *          all LIN channels which are in sleep mode and which
 *          have the wake up functionality disabled.
 * @note    Autosar Service ID: 0x0A.
 * @note    Synchronous, non reentrant function.
 *
 * @requirements LIN160, LIN098, LIN107,
 *               LIN108, LIN109.
 *
 * @api
 *
 * @remarks Implements: DLIN19000, DLIN01202
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(void, LIN_CODE) Lin_WakeUpValidation(void)
    {
    VAR(uint8,AUTOMATIC)chLoop, chInSleep;

    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
/** @remarks implements DLIN19001 */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_WAKEUPVALIDATION_ID, \
                (uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
    else
        {
        /* Check whether one of the LIN channels has been initialized */
        for(chLoop=(uint8)0U; chLoop < LIN_HW_MAX_MODULES; chLoop++)
            {
            if (Lin_LinChStatus[chLoop]!= LIN_CH_UNINIT_STATE)
                {
                break;
                }
            }
        if (chLoop < LIN_HW_MAX_MODULES)
            {
            /* at least 1 channel is initialized */
            /** @remarks implements DLIN19002 */
            /* Check for each LIN channel */
            chInSleep = 0U;
            for(chLoop=(uint8)0U; chLoop < LIN_HW_MAX_MODULES; chLoop++)
                {
              /* Check whether LIN channel is in LIN_CH_SLEEP_STATE state */
                if (Lin_LinChStatus[chLoop] == LIN_CH_SLEEP_STATE)
                    {
                    /* Channel is in LIN_CH_SLEEP_STATE state */
                    chInSleep++;
                    /* Check if 'Lin_ChLoop' has detected a wake-up and */
                    /* its wake up ISR is disabled */
                    if (Lin_LLD_WakeUpValidation(chLoop) == (uint8)TRUE)
                        {
#ifdef LIN_GLOBAL_WAKEUP_SUPPORT
                      /* Indicates a valid timer wakeup event to ECU State Manager */
                      EcuM_SetWakeupEvent(Lin_Channel_Cfg_Ptr[chLoop]->LinChannelEcuMWakeUpSource);
#endif
                        /* Update LIN channel status to LIN_CH_OPERATIONAL_STATE */
                        Lin_LinChStatus[chLoop] = LIN_CH_OPERATIONAL_STATE;

                        /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
                        Lin_LinChFrameStatus[chLoop] = LIN_CH_READY_STATE;
                        }
                    }
                }
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            if(chInSleep == 0U)
                {
                /* no LIN channel in sleep */
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0, (uint8)LIN_WAKEUPVALIDATION_ID, \
                    (uint8)LIN_E_STATE_TRANSITION);
                }
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            }
        else
            {
            /* No LIN channel has been initialized yet */
            /** @remarks implements DLIN19001 */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID, (uint8)0, (uint8)LIN_WAKEUPVALIDATION_ID, \
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            }
        }
    return; /* Exit function with no return */
    }

/**
 * @brief   De-Inits a LIN channel.
 * @details This function disables the LIN module which is
 *          assigned to Channel, clears the channel shadow
 *          buffer and update the state machines.
 * @note    Autosar Service ID: 0x03.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be de-initialized.
 *
 * @requirements LIN009, LIN086, LIN152,
 *               LIN178, LIN116.
 *
 * @api
 *
 * @remarks Implements: DLIN21000, DLIN01204
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(void, LIN_CODE) Lin_DeInitChannel(CONST(uint8, LIN_CONST) Channel)
    {
  /* Check for invalid channel */
    if (Channel >= LIN_HW_MAX_MODULES) /* Invalid channel */
        {
/** @remarks implements DLIN21001 */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_DEINITCHANNEL_ID,\
                (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
    else
        {
        /** @remarks implements DLIN21002 */
        if(Lin_LinChStatus[Channel] == LIN_CH_OPERATIONAL_STATE)
            {
            Lin_LLD_DeInitChannel(Channel);
            /* Update LIN channel status to LIN_CH_UNINIT_STATE */
            Lin_LinChStatus[Channel] = LIN_CH_UNINIT_STATE;
            /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
            Lin_LinChFrameStatus[Channel] = LIN_CH_NOT_READY_STATE;
            /* Remove channel from hardware map */
            Lin_ChannelHardwareMap[Lin_Channel_Cfg_Ptr[Channel]->LinChannelID] = -1;
            }
        }
    return; /* Exit function with no return */
    }

/**
 * @brief   Gets the status of the LIN driver.
 * @details This function returns the state of the current
 *          transmission, reception or operation status.
 *          If the reception of a Slave response was successful then
 *          this service provides a pointer to the buffer where the
 *          data is stored.
 * @note    Autosar Service ID: 0x08.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be checked.
 *
 * @param[out] Lin_SduPtr   Lin_SduPtr pointer to pointer to a shadow
 *                          buffer or memory mapped LIN Hardware
 *                          receive buffer where the current SDU is
 *                          stored.
 * @return Lin_StatusType   The LIN driver status.
 * - LIN_NOT_OK          Development or production error rised
 *                       none of the below conditions.
 * - LIN_TX_OK           Successful transmission.
 * - LIN_TX_BUSY         Ongoing transmission of header or response.
 * - LIN_TX_HEADER_ERROR Error occurred during header
 *                       transmission.
 * - LIN_TX_ERROR        Error occurred during response
 *                       transmission.
 * - LIN_RX_OK           Reception of correct response.
 * - LIN_RX_BUSY         Ongoing reception where at least one byte
 *                       has been received.
 * - LIN_RX_ERROR        Error occurred during reception.
 * - LIN_RX_NO_REPONSE   No data byte has been received yet.
 * - LIN_CH_UNINIT       Channel is not initialized.
 * - LIN_CH_OPERATIONAL  Channel is ready for next header.
 *                       transmission and no data are available.
 * - LIN_CH_SLEEP        Channel is in sleep mode.
 *
 * @requirements LIN022, LIN024, LIN060,
 *               LIN087, LIN168, LIN091,
 *               LIN092, LIN141, LIN142,
 *               LIN143, LIN144, PR-MCAL-3207,
 *               PR-MCAL-3208, PR-MCAL-3209, PR-MCAL-3210.
 *
 * @api
 *
 * @remarks Implements: DLIN14000, DLIN14002
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Lin_StatusType, LIN_CODE) Lin_GetStatus(CONST(uint8, LIN_CONST) Channel, \
                                         P2P2VAR(uint8, AUTOMATIC, LIN_VAR) Lin_SduPtr)
    {
    Lin_StatusType tempReturn = LIN_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if(Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
       Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GETSTATUS_ID,(uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = LIN_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GETSTATUS_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn = LIN_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if(Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
                /* Report error to development error tracer */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GETSTATUS_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = LIN_NOT_OK;
                }
            else
                {
                /* Check PduInfoPtr for not being a null pointer */
                if(Lin_SduPtr == NULL_PTR)
                    {
                    /* Invalid pointer */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GETSTATUS_ID,\
                        (uint8)LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = LIN_NOT_OK;
                    }
                else
                    {
                        /* LIN channel state */
                        switch(Lin_LinChStatus[Channel])
                            {
                            case LIN_CH_SLEEP_STATE:
                                tempReturn = LIN_CH_SLEEP;
                                break;
                            case LIN_CH_OPERATIONAL_STATE:
                                /* LIN Channel frame state */
                                /* Initialize the pointer to return with */
                                /* the address of the data receive buffer */
                                *Lin_SduPtr = LinSduBuffAddress[Channel];

                                /** @remarks implements DLIN14002 */
                                tempReturn = Lin_LLD_HardwareGetStatus(Channel, LinSduBuffAddress[Channel]);
                                break;
                            default :

                Cer_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GETSTATUS_ID,(uint8)LIN_E_DEFAULT);
                        /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                              Cer_ReportError() function implementation */
                                break;
                            }

                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   The service instructs the driver to transmit a
 *          go-to-sleep-command on the addressed LIN channel.
 * @details This function stops any ongoing transmission and initiates
 *          the transmission of the sleep command (master command
 *          frame with ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF,
 *          0xFF, 0xFF, 0xFF, 0xFF). State transition in
 *          LIN_CH_SLEEP_STATE shall be done after the completion of
 *          the sleep command transmission regardless of the success
 *          (therefore the ISR is responsible to put the channel in
 *          LIN_CH_SLEEP_STATE).
 * @note    Autosar Service ID: 0x06.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be addressed.
 * @return Std_ReturnType   The updated driver status.
 * - E_NOT_OK               If the LIN Channel is not valid or
 *                          LIN Channel is not initialized or
 *                          LIN driver is not initialized or
 *                          LIN Channel is in sleep state or
 *                          a timeout occurs.
 * - E_OK                   Otherwise.
 *
 * @requirements LIN172, LIN032, LIN033,
 *               LIN166, LIN089, LIN073,
 *               LIN034, LIN074, LIN129,
 *               LIN130, LIN131, LIN132.
 *
 * @api
 *
 * @remarks Implements: DLIN06005, DLIN23000, DLIN23002
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)E_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
       Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEP_ID,(uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = (uint8)E_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEP_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn = (uint8)E_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if(Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEP_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = (uint8)E_NOT_OK;
                }
            else
                {
                /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
                if(Lin_LinChStatus[Channel] == LIN_CH_SLEEP_STATE)
                    {
                    /* LIN channel is in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEP_ID,\
                        (uint8)LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = (uint8)E_NOT_OK;
                    }
                else
                    {
                    TransmitHeaderCommand[Channel] = LIN_TX_SLEEP_COMMAND;
                    /** @remarks implements DLIN23003 */
                    if(Lin_LLD_GoToSleep(Channel) == (uint8)E_NOT_OK)
                        {
                        /** @remarks implements DLIN23005 */
                        /* Report Production error */
                        Dem_ReportErrorStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                        tempReturn = (uint8)E_NOT_OK;
                        }
                    else
                        {
                        tempReturn = (uint8)E_OK;
                        }
                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   Put a Lin channel in the internal sleep state.
 * @details Stops any ongoing transmission, sets the channel
 *          state to LIN_CH_SLEEP and put the LIN
 *          hardware unit to a reduced power operation mode.
 * @note    Autosar Service ID: 0x09.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be addressed.
 * @return Std_ReturnType   The updated driver status.
 * - E_NOT_OK               If the LIN Channel is not valid or
 *                          LIN Channel is not initialized or
 *                          LIN driver is not initialized or
 *                          LIN Channel is in sleep state or
 *                          a timeout occurs.
 * - E_OK                   Otherwise.
 *
 * @requirements LIN167, LIN032, LIN033,
 *               LIN095, LIN133, LIN134,
 *               LIN135, LIN136.
 *
 * @api
 *
 * @remarks Implements: DLIN24000, DLIN24001, DLIN24002
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)E_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEPINTERNAL_ID,\
                (uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = (uint8)E_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEPINTERNAL_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn =  (uint8)E_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if (Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_GOTOSLEEPINTERNAL_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = (uint8)E_NOT_OK;
                }
            else
                {
                /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
                if (Lin_LinChStatus[Channel] == LIN_CH_SLEEP_STATE)
                    {
                    /* LIN channel is in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16) LIN_MODULE_ID, (uint8) 0, \
                (uint8) LIN_GOTOSLEEPINTERNAL_ID, (uint8) LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = (uint8)E_NOT_OK;
                    }
                else
                    {
                    /* Call LLD function */
                    if(Lin_LLD_GoToSleepInternal(Channel) == (uint8)E_NOT_OK)
                        {
                        /** @remarks implements DLIN24004 */
                        /* Report Production error */
                        Dem_ReportErrorStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                        tempReturn = (uint8)E_NOT_OK;
                        }
                    else
                        {
                        /* Update LIN channel status to LIN_CH_SLEEP_STATE */
                        Lin_LinChStatus[Channel] = LIN_CH_SLEEP_STATE;
                        /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
                        Lin_LinChFrameStatus[Channel] = LIN_CH_NOT_READY_STATE;
                        tempReturn = (uint8)E_OK;
                        }
                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   (Re-)initializes a LIN channel.
 * @note    Autosar Service ID: 0x02.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be initialized.
 * @param[in] Config        pointer to LIN channel configuration set.
 *
 * @requirements LIN012, LIN147, LIN007,
 *               LIN112, LIN113, LIN100,
 *               LIN114, LIN115.
 *
 * @api
 *
 * @remarks Implements: DLIN20000, DLIN20001, DLIN06004
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(void, LIN_CODE) Lin_InitChannel(CONST(uint8, LIN_CONST)Channel,P2CONST(Lin_ChannelConfigType,\
                                 AUTOMATIC, LIN_CONST)Config)
    {
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_INITCHANNEL_ID,\
                (uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_INITCHANNEL_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            }
        else
            {
            /* Check Config for not being a null pointer */
            if (Config == NULL_PTR)
                {
                /* Invalid pointer */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_INITCHANNEL_ID,\
                    (uint8)LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                }
            else
               {
               Lin_Channel_Cfg_Ptr[Channel] = Config;
               Lin_LLD_InitChannel(Channel);
               /* Update LIN channel status to LIN_CH_OPERATIONAL_STATE */
               Lin_LinChStatus[Channel] = LIN_CH_OPERATIONAL_STATE;
               /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
               Lin_LinChFrameStatus[Channel] = LIN_CH_READY_STATE;
               /* Header status flag */
               Lin_LinChHeaderStatus[Channel] = (uint8)FALSE;
               /* Reset header command type */
               TransmitHeaderCommand[Channel] = LIN_TX_NO_COMMAND;
               /* Reset error status global flag */
               Lin_LinChFrameErrorStatus[Channel] = LIN_NO_ERROR;
               /* Map configured hardware channel to logical channel */
               Lin_ChannelHardwareMap[Lin_Channel_Cfg_Ptr[Channel]->LinChannelID] = (sint8)Channel;
               }
            }
        }
    return;
    }

/**
 * @brief   Sends a LIN header.
 * @note    Autosar Service ID: 0x04.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be addressed.
 * @param[in] PduInfoPtr    pointer to PDU containing the PID,
 *                          Checksum model, Response type, Dl and SDU
 *                          data pointer.
 * @return Std_ReturnType   The return type of the api.
 * - E_NOT_OK               If the LIN Channel is not valid or
 *                          LIN Channel is not initialized or
 *                          LIN driver is not initialized or
 *                          PduInfoPtr is NULL or
 *                          a timeout occurs or
 *                          LIN Channel is in sleep state.
 * - E_OK                   Otherwise.
 *
 * @requirements LIN016, LIN017, LIN018,
 *               LIN019, LIN021, LIN164,
 *               LIN087, LIN117, LIN118,
 *               LIN119, LIN120, LIN121,
 *               LIN122.
 *
 * @api
 *
 * @remarks Implements: DLIN15000, DLIN15001, DLIN15002, DLIN15005
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Std_ReturnType, LIN_CODE) Lin_SendHeader(CONST(uint8, LIN_CONST) Channel, CONST(Lin_PduType*,\
                                          LIN_CONST) PduInfoPtr)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)E_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report error to development error tracer */
      Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDHEADER_ID,(uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = (uint8)E_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDHEADER_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn = (uint8)E_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if (Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDHEADER_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = (uint8)E_NOT_OK;
                }
            else
                {
                /* Check PduInfoPtr for not being a null pointer */
                if (PduInfoPtr == NULL_PTR)
                    {
                    /* Invalid pointer */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDHEADER_ID,\
                        (uint8)LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = (uint8)E_NOT_OK;
                    }
                else
                    {
                    /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
                    if (Lin_LinChStatus[Channel] == LIN_CH_SLEEP_STATE)
                        {
                        /* LIN channel is in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                        /* Report error to development error tracer */
                        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDHEADER_ID,\
                        (uint8)LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                        tempReturn = (uint8)E_NOT_OK;
                        }
                    else
                        {
                        /* Reset error status global flag */
                        Lin_LinChFrameErrorStatus[Channel] = LIN_NO_ERROR;
                        /* Set header status to TRUE if master wants to send the response frame */
                        if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE)
                            {
                            Lin_LinChHeaderStatus[Channel]= (uint8)TRUE;
                            TransmitHeaderCommand[Channel] = LIN_TX_MASTER_RES_COMMAND;
                            /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
                            Lin_LinChFrameStatus[Channel] = LIN_CH_READY_STATE;
                            }
                        else
                            {
                            TransmitHeaderCommand[Channel] = LIN_TX_SLAVE_RES_COMMAND;
                            Lin_LinChFrameStatus[Channel] = LIN_CH_RECEIVE_NOTHING_STATE;
                            }
                        if(Lin_LLD_SendHeader(Channel,PduInfoPtr) == (uint8)E_NOT_OK)
                            {
                            /** Report Production error */
                            /** @remarks implements DLIN15005 */
                            Dem_ReportErrorStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                            tempReturn = (uint8)E_NOT_OK;
                            }
                        else
                            {
                            tempReturn = (uint8)E_OK;
                            }
                        }
                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   Sends a LIN response.
 * @note    Autosar Service ID: 0x05.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be addressed.
 * @param[in] PduInfoPtr    pointer to PDU containing the PID,
 *                          Checksum model, Response type, Dl and SDU
 *                          data pointer.
 * @return Std_ReturnType   The return type of the api.
 * - E_NOT_OK               If the LIN Channel is not valid or
 *                          LIN Channel is not initialized or
 *                          LIN driver is not initialized or
 *                          PduInfoPtr is NULL or
 *                          LIN Channel is in sleep state.
 * - E_OK                   Otherwise.
 *
 * @requirements LIN018, LIN025, LIN026,
 *               LIN027, LIN028, LIN165,
 *               LIN088, LIN128, LIN153,
 *               LIN123, LIN124, LIN125,
 *               LIN126, LIN127.
 *
 * @api
 *
 * @remarks Implements: DLIN22000, DLIN22001, DLIN22002
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Std_ReturnType, LIN_CODE) Lin_SendResponse(CONST(uint8, LIN_CONST) Channel, \
                                            CONST(Lin_PduType*, LIN_CONST) PduInfoPtr)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)E_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDRESPONSE_ID,\
                (uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = (uint8)E_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDRESPONSE_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn = (uint8)E_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if (Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDRESPONSE_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = (uint8)E_NOT_OK;
                }
            else
                {
                /* Check PduInfoPtr for not being a null pointer */
                if (PduInfoPtr == NULL_PTR)
                    {
                    /* Invalid pointer */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDRESPONSE_ID,\
                        (uint8)LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = (uint8)E_NOT_OK;
                    }
                else
                    {
                    /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
                    if (Lin_LinChStatus[Channel] == LIN_CH_SLEEP_STATE)
                        {
                        /* LIN channel is in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                        /* Report error to development error tracer */
                        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_SENDRESPONSE_ID,\
                        (uint8)LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                        tempReturn = (uint8)E_NOT_OK;
                        }
                    else
                        {
                        /* Lin_SendHeader() function should be called first */
                        if (Lin_LinChHeaderStatus[Channel] != (uint8)FALSE)
                            {
                            Lin_LinChHeaderStatus[Channel] = (uint8)FALSE;
                            Lin_LLD_SendResponse(Channel,PduInfoPtr);
                            tempReturn = (uint8)E_OK;
                            }
                        }
                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   Generates a wake up pulse.
 * @details This function shall sent a wake up signal to the LIN bus
 *          and put the LIN channel in LIN_CH_OPERATIONAL_STATE state.
 * @note    Autosar Service ID: 0x07.
 * @note    Synchronous, non reentrant function.
 *
 * @param[in] Channel       LIN channel to be addressed.
 * @return Std_ReturnType   The return type of the api.
 * - E_NOT_OK               If the LIN driver is not in sleep state or
 *                          LIN Channel is not valid or
 *                          LIN Channel is not initialized or
 *                          LIN driver is not initialized.
 * - E_OK                   Otherwise.
 *
 * @requirements LIN174, LIN043, LIN090,
 *               LIN169, LIN154, LIN137,
 *               LIN138, LIN139, LIN140.
 *
 * @api
 *
 * @remarks Implements: DLIN25000, DLIN25001, DLIN25002, DLIN25003
 */
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */ 
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeUp(CONST(uint8, LIN_CONST) Channel)
    {
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)E_NOT_OK;
    /* Check whether the LIN driver is in LIN_INIT state */
    if (Lin_LinDrvStatus != LIN_INIT)
        {
        /* LIN driver has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_WAKEUP_ID,(uint8)LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        tempReturn = (uint8)E_NOT_OK;
        }
    else
        {
        /* Check for invalid channel */
        if (Channel >= LIN_HW_MAX_MODULES)
            {
            /* Invalid channel */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_WAKEUP_ID,\
                    (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
            tempReturn = (uint8)E_NOT_OK;
            }
        else
            {
            /* Check whether the LIN channel is in LIN_CH_UNINIT_STATE state */
            if (Lin_LinChStatus[Channel] == LIN_CH_UNINIT_STATE)
                {
                /* LIN channel has not been initialized yet */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* Report error to development error tracer */
                Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_WAKEUP_ID,\
                    (uint8)LIN_E_CHANNEL_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                tempReturn = (uint8)E_NOT_OK;
                }
            else
                {
                /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
                if (Lin_LinChStatus[Channel] != LIN_CH_SLEEP_STATE)
                    {
                    /* LIN channel is not in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                    /* Report error to development error tracer */
                    Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)LIN_WAKEUP_ID,\
                        (uint8)LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
                    tempReturn = (uint8)E_NOT_OK;
                    }
                else
                    {
                    /* Update LIN channel status to LIN_CH_OPERATIONAL_STATE */
                    Lin_LinChStatus[Channel] = LIN_CH_OPERATIONAL_STATE;
                    /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
                    Lin_LinChFrameStatus[Channel] = LIN_CH_READY_STATE;
                    /* Call LLD function */
                    Lin_LLD_WakeUp(Channel);
                    tempReturn = (uint8)E_OK;
                    }
                }
            }
        }
    return tempReturn;
    }

/**
 * @brief   Returns the version information of this module.
 * @note    Autosar Service ID: 0x01.
 * @note    Synchronous, non reentrant function.
 *
 * @param[out] versioninfo  Pointer to a @p Std_VersionInfoType
 *                          structure.
 *
 * @requirements LIN161, LIN001, LIN110,
 *               LIN111, LIN067.
 *
 * @api
 *
 * @remarks covers LIN161, LIN001, LIN110, LIN111, LIN067
 */
#if (LIN_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref LIN_C_REF_4
 */
FUNC(void, LIN_CODE) Lin_GetVersionInfo(P2VAR(Std_VersionInfoType , AUTOMATIC, LIN_VAR)versioninfo)
{

    (versioninfo)->vendorID         = (uint16)LIN_VENDOR_ID;
    (versioninfo)->moduleID         = (uint16)LIN_MODULE_ID;
    (versioninfo)->instanceID       = (uint8)0;

    (versioninfo)->sw_major_version = (uint8)LIN_SW_MAJOR_VERSION;
    (versioninfo)->sw_minor_version = (uint8)LIN_SW_MINOR_VERSION;
    (versioninfo)->sw_patch_version = (uint8)LIN_SW_PATCH_VERSION;

}
#endif /* (LIN_VERSION_INFO_API == STD_ON) */


#define LIN_STOP_SEC_CODE
/**
 * @file Lin.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_C_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/* End of File */

/** @}*/
