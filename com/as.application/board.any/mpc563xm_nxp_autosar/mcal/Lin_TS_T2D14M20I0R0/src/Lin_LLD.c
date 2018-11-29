/**
    @file     Lin_LLD.c
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Isolation level
    @details  Implementation file for function definition on isolation level betwen 
              high and low level driver.
    
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

/**
 * @page misra_violations MISRA-C:2004 violations
 * 
 * @section LIN_LLD_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 * 
 * @section LIN_LLD_C_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
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

#include "Lin.h"
#include "Lin_LLD.h"
#include "ESCI_LLD.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define LIN_AR_MAJOR_VERSION_LLD_C    3
#define LIN_AR_MINOR_VERSION_LLD_C    0
#define LIN_AR_PATCH_VERSION_LLD_C    0

#define LIN_SW_MAJOR_VERSION_LLD_C    2
#define LIN_SW_MINOR_VERSION_LLD_C    0
#define LIN_SW_PATCH_VERSION_LLD_C    0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Lin_LLD.c vs Lin.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_LLD_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_LLD_C != LIN_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_LLD_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_LLD.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_LLD_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_LLD_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin_LLD.c and Lin.h are different"
#endif

/* Lin_LLD.c vs Lin_LLD.h */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_LLD_C != LIN_AR_MAJOR_VERSION_LLD) || \
       (LIN_AR_MINOR_VERSION_LLD_C != LIN_AR_MINOR_VERSION_LLD) || \
       (LIN_AR_PATCH_VERSION_LLD_C != LIN_AR_PATCH_VERSION_LLD))
      #error "AutoSar Version Numbers of Lin_LLD.c and Lin_LLD.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_LLD_C != LIN_SW_MAJOR_VERSION_LLD) || \
     (LIN_SW_MINOR_VERSION_LLD_C != LIN_SW_MINOR_VERSION_LLD))
    #error "Software Version Numbers of Lin_LLD.c and Lin_LLD.h are different"
#endif

/* Lin_LLD.c vs ESCI_LLD.h */
#ifdef CHECK_AUTOSAR_VERSION
#if ((LIN_AR_MAJOR_VERSION_LLD_C != LIN_AR_MAJOR_VERSION_ESCI) || \
     (LIN_AR_MINOR_VERSION_LLD_C != LIN_AR_MINOR_VERSION_ESCI) || \
     (LIN_AR_PATCH_VERSION_LLD_C != LIN_AR_PATCH_VERSION_ESCI))
    #error "AutoSar Version Numbers of Lin_LLD.c and ESCI_LLD.h are different"
#endif
#endif

#if ((LIN_SW_MAJOR_VERSION_LLD_C != LIN_SW_MAJOR_VERSION_ESCI) || \
     (LIN_SW_MINOR_VERSION_LLD_C != LIN_SW_MINOR_VERSION_ESCI))
    #error "Software Version Numbers of Lin_LLD.c and ESCI_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_LLD_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_LLD_C != ECUM_CFG_AR_MINOR_VERSION))
      #error "Software Version Numbers of Lin_LLD.c and EcuM_Cfg.h are different"
  #endif
#endif

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define LIN_START_SEC_CODE
#include "MemMap.h"

/*================================================================================================*/
/**
 * @brief       Check if a LIN channel (ESCI_0 or ESCI_1) has been waked-up
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be waked-up
 * @return      TRUE if Channel has the wake up flag set and the wake up ISR disabled
 *              FALSE otherwise
 * @remarks     Implements DLIN02000, DLIN19002
 */
/*================================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_WakeUpValidation(CONST(uint8, LIN_CONST) Channel)
{
    return ESCI_LLD_WakeUpValidation(Channel);
}

/*================================================================================================*/
/**
 * @brief       Initialize a LIN channel (ESCI_0 or ESCI_1)
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be initialized
 * @remarks     Implements DLIN02000
 */
/*================================================================================================*/
FUNC (void, LIN_CODE) Lin_LLD_InitChannel(CONST(uint8, LIN_CONST) Channel)
{
    ESCI_LLD_InitChannel(Channel);
}

/*================================================================================================*/
/**
 * @brief       Deinitialize and disable a LIN channel (ESCI_0 or ESCI_1)
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be de-initialized
 * @remarks
 */
/*================================================================================================*/
FUNC (void, LIN_CODE) Lin_LLD_DeInitChannel(CONST(uint8, LIN_CONST) Channel)
{
    ESCI_LLD_DeInitChannel(Channel);
}

/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_SendHeader(CONST(uint8, LIN_CONST) Channel, \
                                                   CONST(Lin_PduType*, LIN_CONST) PduInfoPtr)
{
    return ESCI_LLD_SendHeader(Channel, PduInfoPtr);
}

/*================================================================================================*/
/**
 * @brief       Initiates the transmission of the data
 *              part of the LIN frame on Channel (ESCI_0 or ESCI_1)
 *              using information stored on PduInfoPtr pointer.
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
 *              Response type, Dl and SDU data pointer
 * @remarks
 */
/*================================================================================================*/
FUNC (void, LIN_CODE) Lin_LLD_SendResponse(CONST(uint8, LIN_CONST) Channel, \
                                           CONST(Lin_PduType*, LIN_CONST) PduInfoPtr)
{
    ESCI_LLD_SendResponse(Channel, PduInfoPtr);
}

/*================================================================================================*/
/**
 * @brief       Prepares and send a go-to-sleep-command
 *              frame on Channel (ESCI_0 or ESCI_1).
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @return      E_NOT_OK in case of a timeout situation only, else returns E_OK
 * @note        This function stops any ongoing transmission and initiates
 *              the transmission of the sleep command (master command frame with
 *              ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF)
 *              LIN 2.0 protocol specifications
 * @remarks     DLIN23002
 */
/*================================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_GoToSleep(CONST(uint8, LIN_CONST) Channel)
{
    return ESCI_LLD_GoToSleep(Channel);
}

/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Std_ReturnType, LIN_CODE) Lin_LLD_GoToSleepInternal(CONST(uint8, LIN_CONST) Channel)
{
    return ESCI_LLD_GoToSleepInternal(Channel);
}

/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Lin_StatusType, LIN_CODE) Lin_LLD_HardwareGetStatus(CONST(uint8, LIN_CONST) Channel, \
                                                   P2VAR(uint8, AUTOMATIC, LIN_VAR) LinSduPtr)
{
    return ESCI_LLD_HardwareGetStatus(Channel, LinSduPtr);
}

/*================================================================================================*/
/**
 * @brief       Send a wake up signal to the LIN bus
 * @param[in]   Channel LIN channel (ESCI_0 or ESCI_1) to be addressed
 * @remarks
 */
/*================================================================================================*/
FUNC (void, LIN_CODE) Lin_LLD_WakeUp(CONST(uint8, LIN_CONST) Channel)
{
    ESCI_LLD_WakeUp(Channel);
}

#define LIN_STOP_SEC_CODE
/**
 * @file Lin_LLD.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_LLD_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_LLD_C_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

