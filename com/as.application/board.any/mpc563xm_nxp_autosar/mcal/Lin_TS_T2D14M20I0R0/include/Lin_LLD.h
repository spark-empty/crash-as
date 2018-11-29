/**
    @file     Lin_LLD.h
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Isolation level
    @details  Header file for function definition on isolation level betwen high and 
              low level driver.
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.

*/
/*==================================================================================================
==================================================================================================*/

#ifndef LIN_LLD_H
#define LIN_LLD_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @brief   Published Information
 * @{
 */
#define LIN_AR_MAJOR_VERSION_LLD    3
#define LIN_AR_MINOR_VERSION_LLD    0
#define LIN_AR_PATCH_VERSION_LLD    0

#define LIN_SW_MAJOR_VERSION_LLD    2
#define LIN_SW_MINOR_VERSION_LLD    0
#define LIN_SW_PATCH_VERSION_LLD    0
/**@}*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/**
 * @brief       Check if a LIN channel (ESCI_0 or ESCI_1) has been waked-up
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be waked-up
 * @return      TRUE if Channel has the wake up flag set and the wake up ISR disabled
 *              FALSE otherwise.
 * @remarks     Implements DLIN02000, DLIN19002
 */
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_WakeUpValidation(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Initialize a LIN channel (ESCI_0 or ESCI_1)
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be initialized
 * @remarks     Implements DLIN02000
 */
FUNC (void, LIN_CODE) Lin_LLD_InitChannel(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Deinitialize and disable a LIN channel (ESCI_0 or ESCI_1)
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be de-initialized
 * @remarks
 */
FUNC (void, LIN_CODE) Lin_LLD_DeInitChannel(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Initiates the transmission of the header
 *              part of the LIN frame on Channel (ESCI_0 or ESCI_1)
 *              using information stored on PduInfoPtr pointer.
 *              If response type is MASTER_RESPONSE then nothing is sent over the bus
 *              the entire frame (including header) is sent with the ESCI_LLD_SendReponse
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *              Response type, Dl and SDU data pointer
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @remarks     Implements DLIN15002
 */
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_SendHeader(CONST(uint8, LIN_CONST) Channel, \
                                                   CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

/**
 * @brief       Initiates the transmission of the data
 *              part of the LIN frame on Channel (ESCI_0 or ESCI_1)
 *              using information stored on PduInfoPtr pointer.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *              Response type, Dl and SDU data pointer
 * @remarks
 */
FUNC (void, LIN_CODE) Lin_LLD_SendResponse(CONST(uint8, LIN_CONST) Channel, \
                                           CONST(Lin_PduType*, LIN_CONST) PduInfoPtr);

/**
 * @brief       Prepares and send a go-to-sleep-command
 *              frame on Channel (ESCI_0 or ESCI_1).
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and initiates
 *              the transmission of the sleep command (master command frame with
 *              ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF).
 *              LIN 2.0 protocol specifications
 * @remarks     Implements DLIN23002
 */
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_GoToSleep(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Same function as ESCI_LLD_GoToSleep but
 *              without sending a go-to-sleep-command on the bus.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and put the
 *              Channel in sleep mode (then LIN hardware enters a
 *              reduced power operation mode).
 * @remarks     Implements DLIN24003
 */
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel);

/**
 * @brief       Gets the status of the LIN driver when Channel is operating.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
 *              mapped LIN Hardware receive buffer where the current SDU is
 *              stored
 * @return      LIN_NOT_OK if the LIN driver is not in LIN_INIT state or
 *                    LIN Channel is not valid or
 *                    LIN Channel is not activated or
 *                    LIN Channel is not initialized or
 *                    LIN Channel is in sleep state
 *              LIN_TX_OK - Successful transmission
 *              LIN_TX_BUSY - Ongoing transmission of header or response
 *              LIN_TX_HEADER_ERROR - Error occurred during header
 *                                    transmission
 *              LIN_TX_ERROR - Error occurred during response transmission
 *              LIN_RX_OK - Reception of correct response
 *              LIN_RX_BUSY - Ongoing reception where at least one
 *                            byte has been received
 *              LIN_RX_ERROR - Error occurred during reception
 *              LIN_RX_NO_REPONSE - No data byte has been received yet
 *              LIN_CH_UNINIT - Channel is not initialized
 *              LIN_CH_OPERATIONAL - Channel is ready for next header
 *                                   transmission and no data are available
 *              LIN_CH_SLEEP - Channel is sleep mode
 *              LIN_NOT_OK otherwise.
 * @note        This function returns the state of the current transmission,
 *              reception or operation status, only if Channel is in the
 *              LIN_CH_OPERATIONAL_STATE If the reception of a Slave response
 *              was successful then it provides a pointer to buffer where the data is stored.
 * @remarks     Implements DLIN14002
 */
FUNC (Lin_StatusType, LIN_CODE) Lin_LLD_HardwareGetStatus(CONST(uint8, LIN_CONST) Channel, \
                                                P2VAR(uint8, AUTOMATIC, LIN_VAR) LinSduPtr);

/**
 * @brief       Copy the data received from the ESCI data registers to LinSduPtr.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
 *              mapped LIN Hardware receive buffer where the current SDU is stored
 * @note        Internal driver function.
 * @remarks     Implements DLIN12000
 */
FUNC (void, LIN_CODE) Lin_LLD_CopyData(CONST(uint8, LIN_CONST) Channel, \
                                       VAR(uint8, AUTOMATIC) * LinSduPtr);

/**
 * @brief       Send a wake up signal to the LIN bus
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @remarks
 */
FUNC (void, LIN_CODE) Lin_LLD_WakeUp(CONST(uint8, LIN_CONST) Channel);

#ifdef __cplusplus
}
#endif

#endif /* LIN_LLD_H */

/* End of File */
