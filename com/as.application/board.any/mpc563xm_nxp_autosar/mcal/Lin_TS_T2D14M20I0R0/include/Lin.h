/**
   @file    Lin.h
   @version 2.0.0

   @brief   AUTOSAR Lin - API header file.
   @details Header file data definition and functions prototypes exported by the Lin module.

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
 * @file    Lin.h
 * @remarks Implements DLIN01000
 */

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section LIN_H_REF_1
 * Violates MISRA 2004 Required Rule 20.2, Re-use of C90 reserved identifier 
 * This violation is due to the use of "_" which is required as per Autosar.
 *
 * @section LIN_H_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Repeated include file Std_Types.h 
 * This comes from the order of includes in the .c file and from include dependencies. 
 * As a safe approach, any file must include all its dependencies.
 */

#ifndef _LIN_H_
/**
 * @file Lin.h
 * @note Violates MISRA 2004 Required Rule 20.2, Re-use of C90 reserved identifier: 
 *       See @ref LIN_H_REF_1
 */
#define _LIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
/**
 * @file Lin.h
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file Std_Types.h: 
 *       See @ref LIN_H_REF_2
 */
#include "Std_Types.h"
#include "Lin_Cfg.h"
/* It was moved the P2P2VAR and P2P2CONST defines from Compiler.h to Mcal.h */
#include "Mcal.h"
/**
 * @"ASR?" what is the benefit of including ComStack_Types.h here
 * no data type defined are used in the Lin driver???.
 */
#include "ComStack_Types.h"
/**
 * @"ASR?" including Lin_Cfg.h here forces carrying EcuM_Cfg.h in all
 * the files that include Lin.h just because of the
 * EcuM_WakeupSourceType definition.
 */

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
 * @brief   Parameters that shall be published within the Lin header
 *          file and also in the module's description file.
 * @remarks Covers LIN062
 * @{
 */
#define LIN_MODULE_ID               82
#define LIN_VENDOR_ID               43
#define LIN_AR_MAJOR_VERSION        1
#define LIN_AR_MINOR_VERSION        2
#define LIN_AR_PATCH_VERSION        1


#define LIN_SW_MAJOR_VERSION        2
#define LIN_SW_MINOR_VERSION        0
#define LIN_SW_PATCH_VERSION        0
/**@}*/
/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/** @remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION != LIN_AR_MAJOR_VERSION_CFG_H) || \
       (LIN_AR_MINOR_VERSION != LIN_AR_MINOR_VERSION_CFG_H) || \
       (LIN_AR_PATCH_VERSION != LIN_AR_PATCH_VERSION_CFG_H))
    #error "AutoSar Version Numbers of Lin.h and Lin_Cfg.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION != LIN_SW_MAJOR_VERSION_CFG_H) || \
     (LIN_SW_MINOR_VERSION != LIN_SW_MINOR_VERSION_CFG_H))
  #error "Software Version Numbers of Lin.h and Lin_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION != COMSTACKTYPE_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION != COMSTACKTYPE_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION != COMSTACKTYPE_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Lin.h and ComStack_Types.h are different"
  #endif
#endif


/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/
/* Development Error Codes returned by the LIN driver.*/
#define LIN_E_UNINIT            ((uint8)0x00U) /**< @brief LIN driver
                                                    not initialized.*/
#define LIN_E_CHANNEL_UNINIT    ((uint8)0x01U) /**< @brief LIN channel
                                                    not initialized.*/
#define LIN_E_INVALID_CHANNEL   ((uint8)0x02U) /**< @brief LIN channel
                                                    is not valid.*/
#define LIN_E_INVALID_POINTER   ((uint8)0x03U) /**< @brief pointer used
                                                    is not valid or
                                                    null.*/
#define LIN_E_STATE_TRANSITION  ((uint8)0x04U) /**< @brief invalid
                                                    state transition
                                                    from the current
                                                    state.*/
#define LIN_E_DEFAULT           ((uint8)0x05U) /**< @brief CER invalid
                                                    state.*/
/**@}*/


/* LIN driver states */
#define LIN_UNINIT              0x01U /**< @brief LIN driver has not
                                           been initialized yet and
                                           cannot be used.*/
#define LIN_INIT                0x02U /**< @brief LIN driver has been
                                           initialized.*/

/* LIN Channel states */
#define LIN_CH_UNINIT_STATE             0x01U /**< @brief the LIN
                                                   driver is
                                                   initialized but the
                                                   LIN channel is not
                                                   initialized.*/
#define LIN_CH_SLEEP_STATE              0x02U /**< @brief the detection
                                                   of a "wake-up" pulse
                                                   is enabled and the
                                                   LIN hardware is into
                                                   a low power mode if
                                                   such a mode is
                                                   provided by the
                                                   hardware.*/
#define LIN_CH_OPERATIONAL_STATE        0x03U /**< @brief the
                                                   individual channel
                                                   has been initialized
                                                   (using at least one
                                                   statically
                                                   configured data set)
                                                   and is able to
                                                   participate in the
                                                   LIN cluster.*/

/* LIN frames states */
#define LIN_CH_NOT_READY_STATE          0x04U /**< @brief the channel
                                                   is not ready to
                                                   proceess a frame.*/
#define LIN_CH_READY_STATE              0x05U /**< @brief the channel
                                                   is ready to proceess
                                                   a frame.*/
#define LIN_TX_COMPLETE_STATE           0x06U /**< @brief LIN frame was
                                                   sent; no errors.*/
#define LIN_RX_COMPLETE_STATE           0x07U /**< @brief LIN frame was
                                                   received; no
                                                   errors.*/
#define LIN_CH_RECEIVE_NOTHING_STATE    0x08U /**< @brief after the LIN
                                                   frame header was
                                                   correctly sent.*/


/** @brief Interrupt Errors conditions */
#define LIN_NO_ERROR                    0x00U /**< @brief o error occurred
                                                   on a channel.*/
#define LIN_BIT_ERROR                   0x01U /**< @brief bit error on a
                                                   channel;
                                                    - During response
                                                      field transmission
                                                      (Slave and Master
                                                       modes)
                                                    - During header
                                                      transmission (in
                                                      Master mode).*/
#define LIN_CHECKSUM_ERROR              0x02U /**< @brief Checksum error
                                                   on a channel.*/
#define LIN_SYNCH_FIELD_ERROR           0x03U /**< @brief Inconsistent
                                                   Synch Field.*/
#define LIN_BREAK_DELIMITER_ERROR       0x04U /**< @brief Break Delimiter
                                                   too short (< 1 bit).*/
#define LIN_IDENTIFIER_PARITY_ERROR     0x05U /**< @brief Parity error.*/
#define LIN_FRAMING_ERROR               0x06U /**< @brief Invalid stop bit
                                                    - during reception of
                                                      any data in the
                                                      response field
                                                      (Master or Slave
                                                       mode)
                                                    - during reception of
                                                      Synch or Identifier
                                                      Field Slave mode.*/
#define LIN_BUFFER_OVER_RUN_ERROR       0x07U /**< @brief new data byte is
                                                   received on a channel
                                                   and the buffer full flag
                                                   is not cleared.*/
#define LIN_NOISE_ERROR                 0x08U /**< @brief noise detected on
                                                   a received character.*/


/* Commands IDs */
#define LIN_TX_MASTER_RES_COMMAND       0x01U /**< @brief tx frame is a
                                                   master frame (response
                                                   is provided by
                                                   master).*/
#define LIN_TX_SLAVE_RES_COMMAND        0x02U /**< @brief tx frame is a
                                                   slave frame (response is
                                                   provided by slave).*/
#define LIN_TX_SLEEP_COMMAND            0x03U /**< @brief tx frame is a
                                                   sleep command frame.*/
#define LIN_TX_NO_COMMAND               0x04U /**< @brief no tx master
                                                   command pending.*/


/*=================================================================================================
                                             ENUMS
=================================================================================================*/
/**
 * @brief API functions service IDs.
 * @remarks implements DLIN01100
 */
typedef enum
    {

#ifdef LIN_USE_MSC

    MSC_INITCHANNEL_ID       =   (uint8)0x0BU, /**< @brief
                                               Msc_InitChannel() ID.*/
    MSC_DEINITCHANNEL_ID     =   (uint8)0x0CU,  /**< @brief
                                               Msc_DeInitChannel() ID.*/
    MSC_GETSTATUS_ID         =   (uint8)0x0DU,  /**< @brief
                                               Msc_GetStatus() ID.*/
    MSC_POLLING_ID           =   (uint8)0x0EU,  /**< @brief
                                               Msc_Polling() ID.*/
#endif

    LIN_DEINITCHANNEL_ID     =   (uint8)0x03U, /**< @brief
                                               Lin_DeInitChannel()
                                               ID.*/
    LIN_GETSTATUS_ID         =   (uint8)0x08U, /**< @brief
                                               Lin_GetStatus() ID.*/
    LIN_GETVERSIONINFO_ID    =   (uint8)0x01U, /**< @brief
                                               Lin_GetVersionInfo() ID.*/
    LIN_GOTOSLEEP_ID         =   (uint8)0x06U, /**< @brief
                                               Lin_GoToSleep() ID.*/
    LIN_GOTOSLEEPINTERNAL_ID =   (uint8)0x09U, /**< @brief
                                               Lin_GoToSleepInternal() ID.*/
    LIN_INIT_ID              =   (uint8)0x00U, /**< @brief
                                               Lin_Init()ID.*/
    LIN_INITCHANNEL_ID       =   (uint8)0x02U, /**< @brief
                                               Lin_InitChannel() ID.*/
    LIN_SENDHEADER_ID        =   (uint8)0x04U, /**< @brief
                                               Lin_SendHeader() ID.*/
    LIN_SENDRESPONSE_ID      =   (uint8)0x05U, /**< @brief
                                               Lin_SendResponse() ID.*/
    LIN_WAKEUP_ID            =   (uint8)0x07U, /**< @brief
                                               Lin_WakeUp() ID.*/
    LIN_WAKEUPVALIDATION_ID  =   (uint8)0x0AU  /**< @brief
                                               Lin_WakeupValidation() ID.*/
    } API_Function_IDs;


/*!
 * @brief This type is used to specify the Checksum model to be used
 *        for the LIN Frame.
 */
typedef enum
    {
    LIN_ENHANCED_CS,    /**< @brief Enhanced checksum model.*/
    LIN_CLASSIC_CS      /**< @brief Classic checksum model.*/
    } Lin_FrameCsModelType;

/**
 * @brief This type is used to specify whether the frame processor is
 *        required to transmit the response part of the LIN frame.
 */
typedef enum
    {
    LIN_MASTER_RESPONSE,    /**< @brief Response is generated from
                                        this (master) node.*/
    LIN_SLAVE_RESPONSE,     /**< @brief Response is generated from a
                                        remote slave node.*/
    LIN_SLAVE_TO_SLAVE      /**< @brief Response is generated from one
                                        slave to another slave.*/
                            /**< @brief For the master the response
                                        will be anonymous, it does not
                                        have to receive the response.*/
    } Lin_FrameResponseType;

/*!
 * @brief LIN Frame status operation, as returned by the API service
 *        Lin_GetStatus().
 * @brief LIN Channel status operation, as returned by the API service
 *        Lin_GetStatus().
 */
typedef enum
    {
    LIN_NOT_OK = 0,     /**< @brief Development or production error
                                    occurred.*/
    LIN_TX_OK,          /**< @brief Successful transmission.*/
    LIN_TX_BUSY,        /**< @brief Ongoing transmission (Header or
                                    Response).*/
    LIN_TX_HEADER_ERROR,/**< @brief Erroneous header transmission such
                                    as:
                                     - Mismatch between sent and read
                                       back data
                                     - Identifier parity error
                                     - Physical bus error.*/
    LIN_TX_ERROR,       /**< @brief Erroneous transmission such as:
                                     - Mismatch between sent and read
                                       back data
                                     - Physical bus error.*/
    LIN_RX_OK,          /**< @brief Reception of correct response.*/
    LIN_RX_BUSY,        /**< @brief Ongoing reception:
                                    at least one response byte has
                                    been received, but the checksum
                                    byte has not been received.*/
    LIN_RX_ERROR,       /**< @brief Erroneous reception such as:
                                     - Framing error
                                     - Overrun error
                                     - Checksum error
                                     - Short response.*/
    LIN_RX_NO_RESPONSE, /**< @brief No response byte has been received
                                    so far.*/
                        /**< @brief This is a mess !!
                                   Frame status is mixed with channel
                                   status but i kept it here only
                                   because of LIN168.*/
    LIN_CH_UNINIT,      /**< @brief LIN channel not initialized.*/
    LIN_CH_OPERATIONAL, /**< @brief Normal operation;
                                     - The related LIN channel is ready
                                       to transmit next header
                                     - No data from previous frame
                                       available (e.g. after
                                       initialization).*/
    LIN_CH_SLEEP        /**< @brief Sleep mode operation;
                                     - In this mode wake-up detection
                                       from slave nodes is enabled.*/
    } Lin_StatusType;

/*=================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/*!
 * @brief This type is used to specify the number of SDU data bytes to copy.
 */
typedef uint8 Lin_FrameDlType;

/*!
 * @brief Represents all valid protected Identifier used by Lin_SendHeader().
 */
typedef uint8 Lin_FramePidType;

/*!
 * @brief This Type is used to provide PID, checksum model, data length
 *        and SDU pointer from the LIN Interface to the LIN driver.
 * @remarks implements DLIN01101
 */
typedef struct
    {
    Lin_FramePidType      Pid;     /**< @brief LIN frame identifier.*/
    Lin_FrameCsModelType  Cs;      /**< @brief Checksum model type.*/
    Lin_FrameResponseType Drc;     /**< @brief Response type.*/
    Lin_FrameDlType       Dl;      /**< @brief Data length.*/
    uint8*                SduPtr;  /**< @brief Pointer to Sdu.*/
    } Lin_PduType;



/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

/*=================================================================================================
                                     FUNCTION PROTOTYPES
=================================================================================================*/
/**
 * @file    Lin.h
 * @brief API exported function prototypes
 * @remarks implements DLIN01200
*/

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
FUNC(void, LIN_CODE)            Lin_WakeUpValidation(void);

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
FUNC(void, LIN_CODE)            Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_CONST) Config);

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
FUNC(void, LIN_CODE)            Lin_DeInitChannel(CONST(uint8, LIN_CONST) Channel);

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
 *               LIN143, LIN144.
 *
 * @api
 *
 * @remarks Implements: DLIN14000, DLIN14002
 */
FUNC(Lin_StatusType, LIN_CODE)           Lin_GetStatus(CONST(uint8, LIN_CONST) Channel, \
                                           P2P2VAR(uint8, AUTOMATIC, LIN_VAR) Lin_SduPtr);

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
FUNC(Std_ReturnType, LIN_CODE)  Lin_GoToSleep(CONST(uint8, LIN_CONST) Channel);

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
FUNC(Std_ReturnType, LIN_CODE)  Lin_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel);

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
FUNC(void, LIN_CODE)            Lin_InitChannel(CONST(uint8, LIN_CONST) Channel, \
                   P2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_CONST)Config);

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
FUNC(Std_ReturnType, LIN_CODE)  Lin_SendHeader(CONST(uint8, LIN_CONST) Channel, \
                             CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

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
FUNC(Std_ReturnType, LIN_CODE)  Lin_SendResponse(CONST(uint8, LIN_CONST) Channel, \
                            CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

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
FUNC(Std_ReturnType, LIN_CODE)  Lin_WakeUp(CONST(uint8, LIN_CONST) Channel);

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

FUNC(void, LIN_CODE) Lin_GetVersionInfo(P2VAR(Std_VersionInfoType ,AUTOMATIC,LIN_VAR) versioninfo);

#endif   /* (LIN_VERSION_INFO_API == STD_ON) */



#ifdef __cplusplus
}
#endif

#endif /* _LIN_H_ */

/* End of File */

/** @}*/
