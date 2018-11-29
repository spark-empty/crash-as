/**
    @file    ComStack_Types.h
    @version 2.0.0

    @brief   AUTOSAR Base - Communication stack types header file.
    @details AUTOSAR communication stack type header file
    
    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : XPC563XM
    Dependencies : none
    
    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant : 
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@file        ComStack_Types.h
@remarks Covers COMTYPE003, COMTYPE004
@remarks Implements DBASE09000
*/

/**   
@file        ComStack_Types.h
@remarks Covers COMTYPE016
COMTYPE016
*/
#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
/**
@file    ComStack_Types.h
@remarks Covers COMTYPE001
*/
#include "Std_Types.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
@{
@brief Parameters that shall be published within the standard types header file and also in the 
       module's description file
@remarks Covers COMTYPE002
@remarks Implements DBASE09003
*/
#define COMSTACKTYPE_VENDOR_ID            43
#define COMSTACKTYPE_AR_MAJOR_VERSION     2
#define COMSTACKTYPE_AR_MINOR_VERSION     2
#define COMSTACKTYPE_AR_PATCH_VERSION     1
#define COMSTACKTYPE_SW_MAJOR_VERSION     2
#define COMSTACKTYPE_SW_MINOR_VERSION     0
#define COMSTACKTYPE_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief  Action has been successfully finished 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_OK           0x00
/**
@brief  Message not successfully received or sent out 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_NOT_OK     0x01
/**
@brief  Timer N_Ar/N_As has passed its time-out value N_Asmax/N_Armax 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_TIMEOUT_A  0x02
/**
@brief  Timer N_Bs has passed its time-out value N_Bsmax 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_TIMEOUT_BS 0x03
/**
@brief  Timer N_Cr has passed its time-out value N_Crmax 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_TIMEOUT_CR 0x04
/**
@brief  Unexpected sequence number (PCI.SN) value received 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_WRONG_SN   0x05
/**
@brief  Invalid or unknown FlowStatus value has been received 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_INVALID_FS 0x06
/**
@brief  Unexpected protocol data unit received 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_UNEXP_PDU  0x07
/**
@brief  Flow control WAIT frame that exceeds the maximum counter N_WFTmax received 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_WFT_OVRN   0x08
/**
@brief  Flow control (FC) N_PDU with FlowStatus = OVFLW received 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_NO_BUFFER  0x09
/**
@brief  Requested cancellation has been executed 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_CANCELATION_OK 0x0A
/**
@brief  Request cancellation has not been executed
     Due to an internal error the requested cancelation has not been executed.
     This will happen e.g. if the to be canceled transmission has been executed already. 
@details   General return codes for NotifResultType
@remarks Covers COMTYPE018
@remarks Implements DBASE09001
*/
#define NTFRSLT_E_CANCELATION_NOT_OK 0x0B

/**
@brief   There is no bus transceiver error seen or transceiver does not support the detection of bus errors 
@details   General return codes for BusTrcvErrorType
@remarks Covers COMTYPE021
@remarks Implements DBASE09002
*/
#define BUSTRCV_OK           0x00
/**
@brief  Bus transceiver detected an unclassified error 
@details   General return codes for BusTrcvErrorType
@remarks Covers COMTYPE021
@remarks Implements DBASE09002
*/
#define BUSTRCV_E_ERROR      0x01

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/** 
@brief Variables of this type are used to store the result of a buffer request.
@remarks Covers COMTYPE012
@remarks Implements DBASE09004
*/
typedef enum
{
    BUFREQ_OK = 0,         /**< @brief Buffer request accomplished successful */
    BUFREQ_E_NOT_OK = 1,   /**< @brief Buffer request not successful. Buffer cannot be accessed */
    BUFREQ_E_BUSY = 2,     /**< @brief Temporarily no buffer available. It's up the requestor to retry request for a certain time. */
    BUFREQ_E_OVFL = 3      /**< @brief No Buffer of the required length can be provided */
} BufReq_ReturnType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
@brief   This type serve as a unique identifier of a PDU within a software module.
         Allowed ranges: uint8 .. uint16
@remarks Covers COMTYPE005,COMTYPE006,COMTYPE007,COMTYPE014
@remarks Implements DBASE09008
*/
typedef uint16        PduIdType;

/** 
@brief   This type serve as length information of a PDU in bytes.
         Allowed ranges: uint8 .. uint32 
@remarks Covers COMTYPE008,COMTYPE010,COMTYPE017
@remarks Implements DBASE09010
*/
typedef uint16       PduLengthType; 

/** 
@brief Variables of this type are used to store the result status of a notification (confirmation or indication).
@remarks Covers COMTYPE013
@remarks Implements DBASE09007
*/
typedef uint8        NotifResultType;

/** 
@brief Variables of this type are used to return the bus status evaluated by a transceiver.
@remarks Covers COMTYPE020
@remarks Implements DBASE09005
*/
typedef uint8        BusTrcvErrorType; 

/** 
@brief   Variables of the type NetworkHandleType are used to store the identifier 
         of a communication channel.
@remarks Covers COMTYPE026
@remarks Implements DBASE09006
*/
typedef uint8        NetworkHandleType;  

/** 
@brief Variables of this type are used to store the basic information about a PDU of any type,
       namely a pointer variable pointing to it's SDU (payload), and the corresponding length 
       of the SDU in bytes.
@remarks Covers COMTYPE011
@remarks Implements DBASE09009
*/
typedef struct
{
    P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SduDataPtr;   /**< pointer to the SDU (i.e. payload data) of the PDU */
    PduLengthType  SduLength;                                   /**< length of the SDU in bytes */
} PduInfoType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* COMSTACK_TYPES_H */
