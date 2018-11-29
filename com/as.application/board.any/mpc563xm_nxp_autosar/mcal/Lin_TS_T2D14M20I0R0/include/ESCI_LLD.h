/**
   @file    ESCI_LLD.h
   @version 2.0.0

   @brief   AUTOSAR Lin - Low level driver header file.
   @details Function prototypes defined in the LIN low level driver for ESCI.

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
*/
/*=================================================================================================
=================================================================================================*/
/**
@file    Lin.h
@remarks Implements DLIN01000
*/

#ifndef ESCI_LLD_H
#define ESCI_LLD_H

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/


/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
@brief Published Information
@{
*/
#define LIN_AR_MAJOR_VERSION_ESCI    1
#define LIN_AR_MINOR_VERSION_ESCI    2
#define LIN_AR_PATCH_VERSION_ESCI    1

#define LIN_SW_MAJOR_VERSION_ESCI    2
#define LIN_SW_MINOR_VERSION_ESCI    0
#define LIN_SW_PATCH_VERSION_ESCI    0
/**@}*/

/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/

/* Time out for the slave data byte */
#define LIN_TIMEOUT_DATABYTE_ZERO           ((uint8)63U)
#define LIN_TIMEOUT_DATABYTE_ONE            ((uint8)77U)
#define LIN_TIMEOUT_DATABYTE_TWO            ((uint8)91U)
#define LIN_TIMEOUT_DATABYTE_THREE          ((uint8)105U)
#define LIN_TIMEOUT_DATABYTE_FOUR           ((uint8)119U)
#define LIN_TIMEOUT_DATABYTE_FIVE           ((uint8)133U)
#define LIN_TIMEOUT_DATABYTE_SIX            ((uint8)147U)
#define LIN_TIMEOUT_DATABYTE_SEVEN          ((uint8)161U)
#define LIN_TIMEOUT_DATABYTE_EIGHT          ((uint8)175U)

/** @brief Interrupt Errors conditions */
#define CRC_ERROR                  0x09U /**< @brief CRC error occurred on a channel. */
#define OVERFLOW_ERROR             0x0AU /**< @brief Overflow error occurred on a channel. */
#define SLAVE_TIMEOUT_ERROR        0x0BU /**< @brief Slave Timeout error occurred on a channel. */
#define UNREQUESTED_DATA_ERROR     0x0CU /**< @brief Unrequested Data error occurred on a channel*/
#define PHYSICAL_BUS_ERROR         0x0DU /**< @brief Phisical Bus error occurred on a channel. */

/** @brief LIN frames states */
#define LIN_CH_SEND_HEADER         0x09U /**< @brief the channel is not ready to proceess a frame*/
#define LIN_CH_SEND_DATA           0x0AU /**< @brief the channel is not ready to proceess a frame*/
#define LIN_CH_SEND_HEADER_ERROR   0x0BU /**< @brief the channel is not ready to proceess a frame*/
#define LIN_CH_SEND_DATA_ERROR     0x0CU /**< @brief the channel is not ready to proceess a frame*/
#define LIN_CH_RECEIVE_DATA        0x0DU /**< @brief the channel is not ready to proceess a frame*/

#define SLEEP_CMD_TYPE                      (uint8)0x03U

#define MASTER_RESPONSE_HEADER_WRITE_COUNT  (uint8)3U
#define SLAVE_RESPONSE_HEADER_WRITE_COUNT   (uint8)4U
#define LIN_HEADER_DATA_WRITE_COUNT         (uint8)11U

#define ESCI_ZERO                           (uint8)0U
#define ESCI_ONE                            (uint8)1U
#define ESCI_MAX_DATA_LENGTH                (uint8)8U

#define ESCI_NONMAPPED_CHANNEL_VALUE               -1

#define ESCI_HEADER_ZERO                    (uint8)0U
#define ESCI_HEADER_ONE                     (uint8)1U
#define ESCI_HEADER_TWO                     (uint8)2U
#define ESCI_HEADER_THREE                   (uint8)3U

#define ESCI_ID_BIT_SEVEN_MASK              (uint8)0x80U
#define ESCI_ID_BIT_SIX_MASK                (uint8)0x40U
#define ESCI_ID_BIT_SIX_SEVEN_MASK          (uint8)0xC0U

#define ESCI_ID_BIT_SHIFT_BY_TWO            (uint8)2U
#define ESCI_ID_BIT_SHIFT_BY_THREE          (uint8)3U
#define ESCI_ID_BIT_SHIFT_BY_FOUR           (uint8)4U
#define ESCI_ID_BIT_SHIFT_BY_FIVE           (uint8)5U
#define ESCI_ID_BIT_SHIFT_BY_SIX            (uint8)6U

#define SLEEP_IDENTIFIER_VALUE              (uint8)0x3CU
#define SLEEP_DATABYTE_ONE_VALUE            (uint8)0x00U
#define SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE   (uint8)0xFFU

#define DMA_D_REQ_MASK                      ((uint8)0x08U)
#define DMA_INT_HALF_MASK                   ((uint8)0x04U)
#define DMA_INT_MAJ_MASK                    ((uint8)0x02U)

/* Catastrophic Errors Recovery (CER) Codes returned by the LIN driver.*/

#define LIN_CER_NONMAPPED_CHANNEL_INTERRUPT ((uint8)0x00U) /**< @brief
                                                    Not mapped
                                                    channel.*/
#define LIN_CER_UNEXPECTED_FRAME_STATUS_INTERRUPT ((uint8)0x01U)
                                               /**< @brief Unexpected
                                                    frame status.*/
#define LIN_CER_UNEXPECTED_FRAME_ERROR_STATUS_INTERRUPT ((uint8)0x02U)
                                               /**< @brief Unexpected
                                                    frame error
                                                    status.*/
/**@}*/
/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/**
 * @brief API ESCI LLD functions service IDs.
 */
typedef enum
    {
    ESCI_LLD_TX_IRQHANDLER_EDMA = (uint8)0x01U, /**< @brief
                                  ESCI_LLD_Tx_InterruptHandler_eDma()
                                               ID.*/
    ESCI_LLD_RX_IRQHANDLER_EDMA = (uint8)0x02U, /**< @brief
                                  ESCI_LLD_Rx_InterruptHandler_eDma()
                                               ID.*/
    ESCI_LLD_COPYDATA_ID        = (uint8)0x03U, /**< @brief
                                  ESCI_LLD_CopyData() ID.*/
    ESCI_LLD_HWGETSTATUS_ID     = (uint8)0x04U, /**< @brief
                                  ESCI_LLD_HardwareGetStatus() ID.*/
    ESCI_LLD_WAKEUP_ID          = (uint8)0x05U, /**< @brief
                                  ESCI_LLD_WakeUp() ID.*/
    ESCI_LLD_GOTOSLEEPINT_ID    = (uint8)0x06U, /**< @brief
                                  ESCI_LLD_GoToSleepInternal() ID.*/
    ESCI_LLD_GOTOSLEEP_ID       = (uint8)0x07U, /**< @brief
                                  ESCI_LLD_GoToSleep() ID.*/
    ESCI_LLD_SENDRESPONSE_ID    = (uint8)0x08U, /**< @brief
                                  ESCI_LLD_SendResponse()ID.*/
    ESCI_LLD_SENDHEADER_ID      = (uint8)0x09U, /**< @brief
                                  ESCI_LLD_SendHeader() ID.*/
    ESCI_LLD_DEINITCHANNEL_ID   = (uint8)0x0AU, /**< @brief
                                  ESCI_LLD_DeInitChannel() ID.*/
    ESCI_LLD_INITCHANNEL_ID     = (uint8)0x0BU, /**< @brief
                                  ESCI_LLD_InitChannel() ID.*/
    ESCI_LLD_WAKEUPVALID_ID     = (uint8)0x0CU, /**< @brief
                                  ESCI_LLD_WakeUpValidation() ID.*/
    ESCI_LLD_IRQHANDLER_ID      = (uint8)0x0DU  /**< @brief
                                  ESCI_LLD_InterruptHandler() ID.*/
    } API_ESCI_LLD_Function_IDs;

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*=================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/
extern volatile VAR(uint8,LIN_VAR)Lin_LinChStatus[];
extern volatile VAR(uint8,LIN_VAR)Lin_LinChFrameStatus[];
extern VAR(uint8, LIN_VAR)TransmitHeaderCommand[];
extern volatile VAR(uint8,LIN_VAR)Lin_LinChFrameErrorStatus[];
extern P2CONST(Lin_ConfigType,LIN_VAR,LIN_APPL_CONST) Lin_Cfg_Ptr;
extern P2CONST(Lin_ChannelConfigType,LIN_VAR,LIN_APPL_CONST)Lin_Channel_Cfg_Ptr[];
extern VAR(sint8,LIN_VAR)Lin_ChannelHardwareMap[];

/*=================================================================================================
                                     FUNCTION PROTOTYPES
=================================================================================================*/

/*!
 * @brief       Interrupt handler for TX and RX on ESCI.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @note        Internal driver function.
 * @remarks        implements DLIN30005
 */
FUNC (void, LIN_CODE) ESCI_LLD_InterruptHandler(CONST(uint8, LIN_CONST) Channel);


/*****************************************************************************
**                          Non-AUTOSAR LIN Low Level Driver API's          **
*****************************************************************************/
/*!
 * @brief Check if a LIN channel (ESCI_0 or ESCI_1) has been waked-up.
 * @param[in] Channel LIN channel (ESCI_0 or ESCI_1) to be waked-up.
 * @return TRUE if Channel has the wake up flag set and the wake up ISR disabled
 *         FALSE otherwise.
 * @remarks implements DLIN30011
 */
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_WakeUpValidation(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Initialize a LIN channel (ESCI_0 or ESCI_1).
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be initialized.
 * @remarks     implements DLIN30004
 */
FUNC (void, LIN_CODE) ESCI_LLD_InitChannel(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief Deinitialize and disable a LIN channel (ESCI_0 or ESCI_1).
 * @param[in] Channel LIN channel (ESCI_0 or ESCI_1) to be de-initialized.
 * @remarks implements DLIN30000
 */
FUNC (void, LIN_CODE) ESCI_LLD_DeInitChannel(CONST(uint8, LIN_CONST) Channel);

/*!
 * @brief       Initiates the transmission of the header
 *              part of the LIN frame on Channel (ESCI_0 or ESCI_1)
 *              using information stored on PduInfoPtr pointer.
 *              If response type is MASTER_RESPONSE then nothing is sent over the bus
 *              the entire frame (including header) is sent with the ESCI_LLD_SendReponse
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *              Response type, Dl and SDU data pointer
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @remarks implements DLIN30008
 */
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_SendHeader(CONST(uint8, LIN_CONST) Channel,
                          CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

/*!
 * @brief       Initiates the transmission of the data
 *              part of the LIN frame on Channel (ESCI_0 or ESCI_1)
 *              using information stored on PduInfoPtr pointer.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *              Response type, Dl and SDU data pointer
 * @remarks implements DLIN30007
 */
FUNC (void, LIN_CODE) ESCI_LLD_SendResponse(CONST(uint8, LIN_CONST) Channel,
                      CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

/*!
 * @brief       Prepares and send a go-to-sleep-command
 *              frame on Channel (ESCI_0 or ESCI_1).
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and initiates
 *              the transmission of the sleep command (master command frame with
 *              ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF).
 *              LIN 2.0 protocol specifications
 * @remarks implements DLIN30001
 */
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_GoToSleep(CONST(uint8, LIN_CONST) Channel);

/*!
 * @brief       Same function as ESCI_LLD_GoToSleep but
 *              without sending a go-to-sleep-command on the bus.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and put the
 *              Channel in sleep mode (then LIN hardware enters a
 *              reduced power operation mode).
 * @remarks     Implements DLIN30002
 */
FUNC (Std_ReturnType, LIN_CODE) ESCI_LLD_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel);

/*!
 * @brief       Send a wake up signal to the LIN bus.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @remarks implements DLIN30010
 */
FUNC (void, LIN_CODE) ESCI_LLD_WakeUp(CONST(uint8, LIN_CONST) Channel);

/*!
 * @brief       Gets the status of the LIN driver when Channel is operating.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
 *              mapped LIN Hardware receive buffer where the current SDU is
 *              stored
 * @return LIN_NOT_OK if the LIN driver is not in LIN_INIT state or
 *                    LIN Channel is not valid or
 *                    LIN Channel is not activated or
 *                    LIN Channel is not initialized or
 *                    LIN Channel is in sleep state
 *         LIN_TX_OK - Successful transmission
 *         LIN_TX_BUSY - Ongoing transmission of header or response
 *         LIN_TX_HEADER_ERROR - Error occurred during header
 *                               transmission
 *         LIN_TX_ERROR - Error occurred during response transmission
 *         LIN_RX_OK - Reception of correct response
 *         LIN_RX_BUSY - Ongoing reception where at least one
 *                       byte has been received
 *         LIN_RX_ERROR - Error occurred during reception
 *         LIN_RX_NO_REPONSE - No data byte has been received yet
 *         LIN_CH_UNINIT - Channel is not initialized
 *         LIN_CH_OPERATIONAL - Channel is ready for next header
 *                              transmission and no data are available
 *         LIN_CH_SLEEP - Channel is sleep mode
 *         LIN_NOT_OK otherwise.
 * @note This function returns the state of the current transmission,
 *       reception or operation status, only if Channel is in the
 *       LIN_CH_OPERATIONAL_STATE If the reception of a Slave response
 *       was successful then it provides a pointer to buffer where the data is stored.
 * @remarks implements DLIN30003
 */
FUNC (Lin_StatusType, LIN_CODE) ESCI_LLD_HardwareGetStatus(CONST(uint8, LIN_CONST) Channel,
                            P2VAR(uint8, AUTOMATIC, LIN_VAR) LinSduPtr);

/*!
 * @brief       Copy the data received from the ESCI data registers to "LinSduPtr".
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
 *              mapped LIN Hardware receive buffer where the current SDU is stored
 * @note        Internal driver function.
 * @remarks     implements DLIN12000
 */
FUNC (void, LIN_CODE) ESCI_LLD_CopyData(CONST(uint8, LIN_CONST) Channel,
                    VAR(uint8, AUTOMATIC) * LinSduPtr);

#ifdef LIN_USE_DMA
/*===============================================================================================*/
/*!
 * @brief          ESCI_LLD_InterruptHandler_eDma.
 * @param[in]      Channel to be addressed.
 * @param[out]     None
 * @note           Internal driver function for DMA functionality.
 * @remarks implements DLIN30009
 */
/*===============================================================================================*/
FUNC(void, LIN_CODE) ESCI_LLD_Tx_InterruptHandler_eDma(CONST(uint8,LIN_CONST) Channel);

/*===============================================================================================*/
/*!
 * @brief          ESCI_LLD_InterruptHandler_eDma.
 * @param[in]      Channel to be addressed.
 * @param[out]     None
 * @note           Internal driver function for DMA functionality.
 * @remarks implements DLIN30006
 */
/*===============================================================================================*/
FUNC(void, LIN_CODE) ESCI_LLD_Rx_InterruptHandler_eDma(CONST(uint8,LIN_CONST) Channel);
#endif
#ifdef __cplusplus
}
#endif

#endif /* ESCI_LLD_H */

/* End of File */
