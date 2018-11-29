/**
  @file             Can.h
  @version          2.0.0

  @brief            AUTOSAR Can module interface.
  @details          API header for CAN driver.

  Project           AUTOSAR 3.0 MCAL
  Platform          PA
  Peripheral        FLEXCAN
  Dependencies      

  ARVersion         3.0.0
  ARRevision        ASR_REL_3_0_REV_0003
  ARConfVariant
  SWVersion         2.0.0
  BuildVersion      XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

  (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@file     Can.c
@brief    (CAN043) The file Can.h contains the declaration of the Can module API.
@brief    (CAN037) The file Can.h only contains 'extern' declarations of constants, global data, type definitions and services
            that are specified in the Can module SWS.
@remarks  Covers CAN043, CAN037
@remarks  Implements DCAN00043, DCAN00037
*/


/**
@page misra_violations MISRA-C:2004 violations

@section Can_h_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to the requirement that request to have empty APIs if polling is not used.

@section Can_h_REF_2
Violates MISRA 2004 Advisory Rule 8.10, external ... could be made static
The respective code could not be made static because of layers architecture design of the driver.
 @section Can_h_REF_3
Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar .
@section Can_h_REF_4
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
here are different kinds of execution code sections.
*/

#ifndef _CAN_H_
/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier: _CAN_H_. - See @ref Can_h_REF_3
*/
#define _CAN_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "ComStack_Types.h"
#include "Can_Cfg.h"
/*==================================================================================================
                                                           LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief    Internal micro-dependent versioning. Check of AUTOSAR & Vendor specification version.
*/
#define CAN_VENDOR_ID         43
#define CAN_MODULE_ID         80
#define CAN_AR_MAJOR_VERSION  2
#define CAN_AR_MINOR_VERSION  2
#define CAN_AR_PATCH_VERSION  2
#define CAN_SW_MAJOR_VERSION  2
#define CAN_SW_MINOR_VERSION  0
#define CAN_SW_PATCH_VERSION  0
/**@}*/


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION != CAN_AR_MAJOR_VERSION_CFG_H) || \
     (CAN_AR_MINOR_VERSION != CAN_AR_MINOR_VERSION_CFG_H) || \
     (CAN_AR_PATCH_VERSION != CAN_AR_PATCH_VERSION_CFG_H))
  #error "AutoSar Version Numbers of Can.h and Can_Cfg.h are different"
#endif
#endif

#if ((CAN_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION_CFG_H) || \
     (CAN_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION_CFG_H) || \
     (CAN_SW_PATCH_VERSION != CAN_SW_PATCH_VERSION_CFG_H))
  #error "Software Version Numbers of Can.h and Can_Cfg.h are different"
#endif


/*==================================================================================================
                              DEFINE SECTION
==================================================================================================*/
/**
@{
@brief   (CAN104) The Can module shall be able to detect the following errors and exceptions depending on its configuration (development/production).
@brief   (CAN026) Development Errors shall indicate errors that are caused by erroneous usage of the Can module API. This covers API
            parameter checks and call sequence errors.
@brief   (CAN080) Development error values are of type uint8.
@remarks Covers CAN104, CAN026, CAN080
@remarks Implements DCAN00104, DCAN00026, DCAN00080
*/
#define CAN_E_PARAM_POINTER      (uint8)0x01U
#define CAN_E_PARAM_HANDLE       (uint8)0x02U
#define CAN_E_PARAM_DLC          (uint8)0x03U
#define CAN_E_PARAM_CONTROLLER   (uint8)0x04U
#define CAN_E_UNINIT             (uint8)0x05U
#define CAN_E_TRANSITION         (uint8)0x06U
#define CAN_E_DEFAULT            (uint8)0x07U
/**@}*/


/**
@{
@brief   Service ID (APIs) for Det reporting
*/
#define CAN_SID_INIT                          (uint8)0x00U
#define CAN_SID_MAIN_FUNCTION_WRITE           (uint8)0x01U
#define CAN_SID_INIT_CONTROLLER               (uint8)0x02U
#define CAN_SID_SET_CONTROLLER_MODE           (uint8)0x03U
#define CAN_SID_DISABLE_CONTROLLER_INTERRUPTS (uint8)0x04U
#define CAN_SID_ENABLE_CONTROLLER_INTERRUPTS  (uint8)0x05U
#define CAN_SID_WRITE                         (uint8)0x06U
#define CAN_SID_GET_VERSION_INFO              (uint8)0x07U
#define CAN_SID_MAIN_FUNCTION_READ            (uint8)0x08U
#define CAN_SID_MAIN_FUNCTION_BUS_OFF         (uint8)0x09U
#define CAN_SID_MAIN_FUNCTION_WAKEUP          (uint8)0x0AU
#define CAN_SID_CBK_CHECK_WAKEUP              (uint8)0x0BU
#define CAN_SID_ABORT_MB                      (uint8)0x0CU
#define CAN_SID_SETCLOCKMODE                  (uint8)0x0DU
/**@}*/


/*==================================================================================================
                              TYPEDEF SECTION
==================================================================================================*/
/**
@{
@typedef   Can_IdPtrType
            Type for storing pointer to the Identifier Lenght Type.
             - used by "Can_ConfigType" structure (pointer to the FilterMasks).
*/

#if (CAN_EXTENDEDID == STD_ON)
typedef        CONSTP2CONST(uint32, CAN_CONST, CAN_APPL_CONST) Can_IdPtrType;
#else /* (CAN_EXTENDEDID == STD_OFF) */
typedef        CONSTP2CONST(uint16, CAN_CONST, CAN_APPL_CONST) Can_IdPtrType;
#endif /* (CAN_EXTENDEDID == STD_OFF) */
/**@}*/


/**
@{
@typedef   Can_IdType
            Type for storing the Identifier Length Type: Normal /Extended.
             - used by "Can_MessageBufferConfigObjectType" structure.
@remarks   The driver does not distinguish between Extended and Mixed transmission modes.
           Extended transmission mode of operation behaves the same as Mixed mode.
*/

#if (CAN_EXTENDEDID == STD_ON)
typedef        VAR(uint32, CAN_VAR) Can_IdType;
#else /* (CAN_EXTENDEDID == STD_OFF) */
typedef        VAR(uint16, CAN_VAR) Can_IdType;
#endif /* (CAN_EXTENDEDID == STD_OFF) */
/**@}*/


/**
@{
@typedef   Can_HWObjectCountType
            Type for indexes to and counts of ID Mask and MB config array members.
*/

#if (CAN_MBCOUNTEXTENSION == STD_ON)
typedef        VAR(uint16, CAN_VAR) Can_HWObjectCountType;
#else /* (CAN_MBCOUNTEXTENSION==STD_OFF) */
typedef        VAR(uint8, CAN_VAR) Can_HWObjectCountType;
#endif /* (CAN_MBCOUNTEXTENSION==STD_OFF) */
/**@}*/


/**
@brief     Type for pointer to function.
           Used for user handlers from plugin.
*/
typedef void (*Can_PCallBackType)( void);


/*==================================================================================================
                              ENUM SECTION
==================================================================================================*/
/**
@enum      Can_ObjType
            Used for value received by Tressos interface configuration.
            Describe the MB configuration.
*/
typedef enum
    {
        RECEIVE = 0U,   /*!< Receive MB */
        TRANSMIT        /*!< Transmit MB */
    } Can_ObjType;


/**
@brief     CAN Return Types from Functions.
*/
typedef enum
    {
        CAN_OK = 0U,    /*!< Operation was ok executed */
        CAN_NOT_OK,     /*!< Operation was not ok executed */
        CAN_BUSY        /*!< Operation was rejected because of busy state */

    } Can_ReturnType;


/**
@brief     CAN State Modes of operation.
               - used by "Can_SetControllerMode()" function.
@remarks   State transitions that are used by the function CAN_SetControllerMode().
*/
typedef enum
    {
        CAN_T_STOP = 0U,   /*!< CANIF_CS_STARTED -> CANIF_CS_STOPPED */
        CAN_T_START,       /*!< CANIF_CS_STOPPED -> CANIF_CS_STARTED */
        CAN_T_SLEEP,       /*!< CANIF_CS_STOPPED -> CANIF_CS_SLEEP */
        CAN_T_WAKEUP       /*!< CANIF_CS_SLEEP -> CANIF_CS_STOPPED */

    } Can_StateTransitionType;


/**
@enum      Can_ControllerState
            Used for registering the state of the controller: enabled/disabled.
            Controller can be enabled from the Tresos configuration.
*/
typedef enum
    {
        CONTRL_ENABLED = 0U,   /*!< Controller enabled */
        CONTRL_DISABLED        /*!< Controller disabled */
    } Can_ControllerState;


/**
@enum      CanIdType
            Used for value received by Tressos interface configuration.
            Used to diferentiate Extended, Mixed or Standard Id type.
*/
typedef enum
    {
        EXTENDED = 0U,  /*!< Extended ID (29 bits) */
        STANDARD,       /*!< Standard ID (11 bits) */
        MIXED           /*!< Mixed ID (29 bits) */
    } CanIdType;


/**
@brief    CAN Driver status used for checking and preventing double driver intialization.
*/
typedef enum
    {
        /** CAN_UNINIT = The CAN controller is not initialized. The CAN Controller is not participating on the CAN bus.
            All registers belonging to the CAN module are in reset state, CAN interrupts are disabled. */
        CAN_UNINIT = 0U,
        /** CAN_READY = Controller has initialized: static variables, including flags;
            Common setting for the complete CAN HW unit; CAN controller specific settings for each CAN controller. */
        CAN_READY
    } Can_StatusType;


/**
@brief    CAN source clock selection used in Can_SetClockMode Non-Autosar API.
*/
typedef enum
    {
        CAN_NORMAL = 0U, /*!< Standard configuration (default) */
        CAN_ALTERNATE    /*!< Second configuration (special) */
    } Can_ClockMode;

/*==================================================================================================
                              STRUCT SECTION
==================================================================================================*/

#if (CAN_RXFIFO_ENABLE == STD_ON)
/**
@brief     Rx Fifo Table IDs and Filter Masks
*/
typedef struct
    {
        /**
        @brief Table with the IDs specific for Rx Fifo
        */
        CONST(uint32, CAN_CONST) TableId;

        /**
        @brief Table with the Filter masks
        */
        CONST(uint32, CAN_CONST) TableFilterMask;

    } Can_RxFiFoTableIdConfigType;

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/**
@brief     Configuration of FlexCAN controller. This structure is initialized by Tresos considering user settings.
               - used by Can_ConfigType.
@remarks   Passed to Can_InitController() at initialization.
*/
typedef struct
    {
        /**
        @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG.
        */
        CONST(uint32, CAN_CONST) ControlRegister;

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
        /**
        @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG.
        */
        CONST(uint32, CAN_CONST) ControlRegister_Alternate;
#endif /* (CAN_DUAL_CLOCK_MODE == STD_ON) */

        /**
        @brief BusOff Sw Recovery, RXFifo En, IDAM Type,  Event Trigger Mode TxProcessing/RxProcessing/BusoffProcessing/WakeuProcessing: Polling vs Interrupt mode.
        */
        CONST(uint16, CAN_CONST) Options;

#if (CAN_MIX_MB_SUPPORT == STD_ON)
        /**
        @brief Number of message Buffers available for FlexCan unit.
        */
        CONST(uint8, CAN_CONST) Can_NumberOfMB;
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */

    } Can_ControllerConfigType;


/**
@brief     Type used to provide ID, DLC, SDU from CAN interface to CAN driver. HTH/HRH = ID+DLC+SDU.
*/
typedef struct
    {
        /**
        @brief CAN L-PDU = Data Link Layer Protocol Data Unit. Consists of Identifier, DLC and Data(SDU)  It is uint32 for CAN_EXTENDEDID=STD_ON, else is uint16.
        */
        VAR(Can_IdType, CAN_VAR) id;

        /**
        @brief The L-PDU Handle = defined and placed inside the CanIf module layer. Each handle represents an L-PDU, which is a constant structure with information for Tx/Rx processing.
        */
        VAR(PduIdType, CAN_VAR) swPduHandle;

        /**
        @brief DLC = Data Length Code (part of L-PDU that describes the SDU length).
        */
        VAR(uint8, CAN_VAR) length;

        /**
        @brief CAN L-SDU = Link Layer Service Data Unit. Data that is transported inside the L-PDU.
        */
        P2VAR(uint8, CAN_VAR, CAN_APPL_DATA) sdu;

    } Can_PduType;


/**
@brief     Type for storing information about Message Buffers (CAN hardware objs).
             - used by Can_MBConfigContainerType.
*/
typedef struct
    {
        /**
        @brief Index into array of Can_FilterMaskType values (uint8/uint16), Current MB and the coresponding filter mask.
        */
        VAR(Can_HWObjectCountType, CAN_VAR) IdMaskIndex;

        /**
        @brief Controller ID (index into controller address array containing Can_ControllerPtrType).
        */
        CONST(uint8, CAN_CONST) ControllerId;

        /**
        @brief ID type: EXTENDED, STANDARD, MIXED.
        */
        VAR(CanIdType, CAN_VAR) IdType;

        /**
        @brief Receive/Transmit
        */
        VAR(Can_ObjType, CAN_VAR) MBType;

        /**
        Message ID (extended identifier) (uint16/uint32). configurable by CanHardwareObject/CanIdValue.
        */
        VAR(Can_IdType, CAN_VAR) MessageId;

        /**
        @brief Local priority bits used for arbitration.
        */
        CONST(uint8, CAN_CONST) LocalPriority;

        /**
        @brief HW Obiect ID
        */
        VAR(uint32, CAN_VAR) HWObjID;

    } Can_MBConfigObjectType;


/**
@brief     Type for storing Message Buffer configurations.
           The MessageBufferConfigs array is sorted according to:
             - HRHs first, HTHs next (AutoSAR requirement)
             - Controller ID (HRHs and HTHs belonging to all controllers must be grouped together)
             - Message ID (to ensure top priority IDs are first which means they will be serviced first)
*/
typedef struct
    {
        /**
        @brief Pointer to the MB array .
        */
        CONSTP2CONST(Can_MBConfigObjectType, CAN_CONST, CAN_APPL_CONST) MessageBufferConfigsPtr;

        /**
        @brief Number of elements in the array -( having 6 controllers with 64MBs each uint8 is not enough to store this value -> the type is extended to uint16).
        */
        CONST(Can_HWObjectCountType, CAN_CONST) MessageBufferConfigCount;

    } Can_MBConfigContainerType;


/**
@brief     Structure for describing individual FlexCAN controllers on the chip.
           HRH = Hardware Receive Handle (HRH) is defined and provided by the CAN driver.
             Each HRH represents exactly one hardware object.
             The HRH can be used to optimize software filtering.
           HTH = The Hardware Transmit Handle (HTH) is defined and provided by the CAN driver.
             Each HTH represents one or several hardware objects, that are
               configured as hardware transmit pool.
*/
typedef struct
    {
        /**
        @brief Hardware Offset for Can controller: FLEXCAN_A = Offset[0], FLEXCAN_B = Offset[1], ...
        */
        CONST(uint8, CAN_CONST) ControllerOffset;

        /**
        @brief Max Message Buffer number.
        */
        CONST(uint8, CAN_CONST) MaxMBCount;

        /**
        @brief HthOffset is calculated (FirstHTH - No.of Rx MBs).
        */
        CONST(Can_HWObjectCountType, CAN_CONST) HthOffset;


#if (CAN_WAKEUP_SUPPORT == STD_ON)
        /**
        @brief WakeUp source ID (typedef uint32 EcuM_WakeupSourceType - in EcuM.h (uint32) ).
        */
        CONST(uint32, CAN_CONST) CanWakeupSourceID;
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
        /**
        @brief RxFifo TableID Controller index.
        */
        CONST(uint8, CAN_CONST) RxFiFoTableIdConfigIndex;

        /**
        @brief Pointer to RX FIFO Overflow notification function.
        */
        CONST(Can_PCallBackType, CAN_CONST) Can_RxFifoOverflowNotification;

        /**
        @brief Pointer to RX FIFO Warning notification function.
        */
        CONST(Can_PCallBackType, CAN_CONST) Can_RxFifoWarningNotification;
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */

        /**
        @brief Pointer to Error interrupt notification function (ESR[ERR_INT]).
        */
        CONST(Can_PCallBackType, CAN_CONST) Can_ErrorNotification;

#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
        /**
        @brief Wakeup channel from WakeupUnit - for External Wakeup support.
        */
        CONST(uint8, CAN_CONST) WakeupChannel;
  #endif  /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

    } Can_ControlerDescriptorType;


/**
@brief    Top Level structure containing all Driver configuration.
          A pointer to this structure is transmitted to Can_Init() to initalize the driver at startup.
          The application selects one of the configurations by using a pointer to one of the elements
            of this array as a parameter of the Can_Init function.
*/
typedef struct
    {
        /**
        @brief Number of Can Controllers configured in Tresos plugin.
        */
        VAR(uint8, CAN_VAR) Can_ControllersConfigured;

        /**
        @brief Pointer to the first FilterMask value - any controller can have many filter masks for Can messages.
        */
        VAR(Can_IdPtrType, CAN_VAR) FilterMasksPtr;

        /**
        @brief Pointer to the Configuration of FlexCAN controller ( CTRL value register & Options).
        */
        CONSTP2CONST(Can_ControllerConfigType, CAN_CONST, CAN_APPL_CONST) ControllerConfigsPtr;

        /**
        @brief Pointer to the first MB configuration of this Controller.
        */
        CONST(Can_MBConfigContainerType, CAN_CONST) MBConfigContainer;

        /**
        @brief Pointer to the first FlexCAN Controller description.
        */
        P2CONST(Can_ControlerDescriptorType, CAN_CONST, CAN_APPL_CONST) ControlerDescriptors;

#if (CAN_RXFIFO_ENABLE == STD_ON)

        /**
        @brief Pointer to the Table IDs for the RxFifo.
        */
        CONSTP2CONST(Can_RxFiFoTableIdConfigType, CAN_CONST, CAN_APPL_CONST) Can_RxFiFoTableIdConfigPtr;

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

        /*Maximum Object IDs configured */
        VAR(Can_HWObjectCountType, CAN_VAR) Can_max_object_Id;

        /*Controller ID mapping*/
        CONST(uint8, CAN_CONST) Can_ControllerID_Mapping[CAN_MAX_OBJECT_ID];

        /*Can Object Type mapping*/
        CONST(Can_ObjType, CAN_CONST) Can_ObjectType_Mapping[CAN_MAX_OBJECT_ID];

    } Can_ConfigType;


/*==================================================================================================
                                   API FUNCTION PROTOTYPES
==================================================================================================*/

/**
@brief         Initialize the CAN driver. SID = 0x00.
@details       Initialize all the controllers.
               The CAN module shall be initialized by Can_Init(<&Can_Configuration>) service call during the start-up.

@param[in]     Config Pointer to driver configuration

@pre           Can_Init shall be called at most once during runtime.
@post          Can_Init shall initialize all the controllers and set the driver in READY state.

@remarks       (CAN223) Can_Init service.
@remarks       (CAN021) The desired CAN controller configuration can be selected with the parameter Config.
@remarks       (CAN291) Config is a pointer into an array of hardware specific data structure stored in ROM.The different controller configuration
                 sets are located as data structures in ROM.
@remarks       Covers CAN223, CAN021, CAN291
@remarks       Implements DCAN00223, DCAN00021, DCAN00291
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
#define CAN_START_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"
extern FUNC (void, CAN_CODE) Can_Init( P2CONST(Can_ConfigType, CAN_VAR, CAN_APPL_CONST) Config);
/*lint -restore*/


/**
@brief         Returns the version information of this module. SID = 0x07.
@details       Implemented as a macro in Can.h file.

@param[in]     versioninfo A pointer to a variable to store version info.

@pre           The CAN_VERSION_INFO_API define must be configured on.
@post          The version information is return if the parameter versionInfo is not a null pointer.

@remarks       (CAN224) Can_GetVersionInfo service.
@remarks       (CAN105) The function Can_GetVersionInfo shall return the version information of this module. The version information includes: Module Id, Vendor Id, Vendor specific version numbers.
@remarks       (CAN251) If source code for caller and callee is available, the function Can_GetVersionInfo should be realized as a macro, defined in the Can module header file.
@remarks       Covers CAN224, CAN105, CAN251
@remarks       Implements DCAN00224, DCAN00105, DCAN00251
*/

#if (CAN_VERSION_INFO_API == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC(void, CAN_CODE) Can_GetVersionInfo( P2VAR(Std_VersionInfoType, CAN_VAR, CAN_APPL_DATA) versioninfo);
/*lint -restore*/
#endif /* (CAN_VERSION_INFO_API == STD_ON) */


/**
@brief         Initialize the CAN controllers. SID = 0x02.
@details       Initialize the controller based on ID input parameter.

@param[in]     Controller CAN ID controller to be initialized.
@param[in]     Config Pointer to controller configuration.

@pre           Before controller re-initalization the driver must be initialized and the controllers must be in Stop state.
@post          Interrupts and MBs must be configured for respond to CAN bus.

@remarks       (CAN229) Can_InitController service.
@remarks       Covers CAN229
@remarks       Implements DCAN00229
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_InitController( VAR(uint8, CAN_VAR) Controller,
                                                 P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Config);
/*lint -restore*/


/**
@brief         Put the controller into a required state. SID = 0x03.
@details       Switch the controller from one state to another.

@param[in]     Controller CAN controller for which the status shall be changed.
@param[in]     Transition Possible transitions (CAN_T_STOP / CAN_T_START / CAN_T_SLEEP / CAN_T_WAKEUP).

@return        Can_ReturnType  Result of the transition.
@retval        CAN_OK   Transition initiated.
@retval        CAN_NOT_OK  Development or production error.

@pre           Before changing the controller state the driver must be initialized.
@post          After the transition to the new state the interrupts required for that state must be enebaled.

@remarks       (CAN230) Can_SetControllerMode service.
@remarks       Covers CAN230
@remarks       Implements DCAN00230
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (Can_ReturnType, CAN_CODE) Can_SetControllerMode( VAR(uint8, CAN_VAR) Controller,
                                                              VAR(Can_StateTransitionType, CAN_VAR) Transition);
/*lint -restore*/

/**
@brief         Disable INTs. SID = 0x04.
@details       Switch off the controller's interrupts.

@param[in]     Controller CAN controller for which interrupts shall be disabled.

@pre           Driver must be initalzied before changing the interrupts state (en/dis).
@post          Controller must not respond to any interrupt assertion.

@remarks       (CAN231) Can_DisableControllerInterrupts service.
@remarks       Covers CAN231
@remarks       Implements DCAN00231
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_DisableControllerInterrupts( VAR(uint8, CAN_VAR) Controller);
/*lint -restore*/


/**
@brief         Enable INTs. SID = 0x05.
@details       Switch on the controller's interrupts.

@param[in]     Controller CAN controller for which interrupts shall be disabled.

@pre           Driver must be initalzied before changing the interrupts state (en/dis).
@post          Controller must respond to interrupt assertion.

@remarks       (CAN232) Can_EnableControllerInterrupts service.
@remarks       Covers CAN232
@remarks       Implements DCAN00232
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_EnableControllerInterrupts( VAR(uint8, CAN_VAR) Controller);
/*lint -restore*/


/**
@brief         Transmit information on CAN bus. SID = 0x06.
@details       Can_Write checks if hardware transmit object that is identified by the HTH is free.
               Can_Write checks if another Can_Write is ongoing for the same HTH.
                a) hardware transmit object is free:
                The mutex for that HTH is set to 'signaled' the ID, DLC and SDU are put in a format appropriate for
                the hardware (if necessary) and copied in the appropriate hardware registers/buffers.
                All necessary control operations to initiate the transmit are done.
                The mutex for that HTH is released. The function returns with CAN_OK.
                b) hardware transmit object is busy with another transmit request.
                The function returns with CAN_BUSY.
                c) A preemptive call of Can_Write has been issued, that could not be handled reentrant (i.e. a call with the same HTH).
                The function returns with CAN_BUSY the function is non blocking
                d) The hardware transmit object is busy with another transmit request for an L-PDU that has lower priority than that for the current request
                The transmission of the previous L-PDU is cancelled (asynchronously).
                The function returns with CAN_BUSY.

@param[in]     Hth Information which HW-transmit handle shall be used for transmit. Implicitly this is also the information about the controller to use because the Hth numbers are unique inside one hardware unit.
@param[in]     PduInfo Pointer to SDU user memory, DLC and Identifier.

@return        Can_ReturnType   Result of the write operation.
@retval        CAN_OK   Write command has been accepted.
@retval        CAN_NOT_OK  Development error occured.
@retval        CAN_BUSY   No of TX hardware buffer available or preemtive call of Can_Write() that can't be implemented reentrant.

@pre           Driver must be initialized and MB must be configured for Tx.
@post          The data can be transmitted or rejected because of another data with a higher priority.

@remarks       (CAN233) Can_Write service.
@remarks       Covers CAN233
@remarks       Implements DCAN00233
*/
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (Can_ReturnType, CAN_CODE) Can_Write( VAR(Can_HWObjectCountType, CAN_VAR) Hth,
                                                  P2CONST(Can_PduType, CAN_VAR, CAN_APPL_CONST) PduInfo);
/*lint -restore*/


/**
@brief         Process check of WakeUp condition. SID = 0x0B.
@details       This service shall evaluate the WakeupSource parameter to get the information,
               which dedicate wakeup source needs to be checked, either a CAN transceiver or controller device.

@param[in]     controller controllerID.

@return        Std_ReturnType Result of the wakeup verification.
@retval        E_OK  Wakeup was detected for the given controller.
@retval        E_NOT_OK  No wakeup was detected for the given controller.

@pre           Driver must be initialized.
@post          Return the wakeup event occurence.

@remarks       (CAN360) Can_Cbk_CheckWakeup service.
@remarks       Covers CAN360
@remarks       Implements DCAN00360
*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (Std_ReturnType, CAN_CODE) Can_Cbk_CheckWakeup( VAR(uint8, CAN_VAR) controller);
/*lint -restore*/
#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/**
@brief         Function called at fixed cyclic time. SID 0x01.
@details       Service for performs the polling of TX confirmation and TX cancellation confirmation
                   when CAN_TX_PROCESSING is set to POLLING.

@pre           Driver must be initialized.
@post          Send the data from that MB that is configured for Tx.

@remarks       (CAN225) Can_MainFunction_Write service.
@remarks       Covers CAN225
@remarks       Implements DCAN00225
*/

#if (CAN_TXPOLL_SUPPORTED == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_MainFunction_Write( void );
/*lint -restore*/
#else /* (CAN_TXPOLL_SUPPORTED == STD_OFF) */

/**
@brief    (CAN178) The Can module may implement the function Can_MainFunction_Write as empty define in case no polling at all is used.
@remarks  Covers CAN178
@remarks  Implements DCAN00178
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_h_REF_1
*/
/*lint -save -e961*/
#define Can_MainFunction_Write()
/*lint -restore*/

#endif /* (CAN_TXPOLL_SUPPORTED == STD_OFF) */


/**
@brief         Function called at fixed cyclic time.  SID = 0x08
@details       Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.

@pre           Driver must be initialized.
@post          Receive the data from that MB that is configured for Rx.

@remarks       (CAN226) Can_MainFunction_Read service.
@remarks       Covers CAN226
@remarks       Implements DCAN00226
*/

#if (CAN_RXPOLL_SUPPORTED == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_MainFunction_Read( void);
/*lint -restore*/
#else /* (CAN_RXPOLL_SUPPORTED == STD_OFF) */

/**
@brief   (CAN180) The Can module may implement the function Can_MainFunction_Read as empty define in case no polling at all is used.
@remarks Covers CAN180
@remarks Implements DCAN00180
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_h_REF_1
*/
/*lint -save -e961*/
#define Can_MainFunction_Read()
/*lint -restore*/

#endif /* (CAN_RXPOLL_SUPPORTED == STD_OFF) */


/**
@brief         Function called at fixed cyclic time. SID - 0x09
@details       Service for performs the polling of bus-off events that are configured statically as 'to be polled'.

@pre           Driver must be initialized.
@post          Handle the busoff event.

@remarks       (CAN227) Can_MainFunction_BusOff service.
@remarks       Covers CAN227
@remarks       Implements DCAN00227
*/

#if (CAN_BUSOFFPOLL_SUPPORTED == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_MainFunction_BusOff( void);
/*lint -restore*/
#else /* (CAN_BUSOFFPOLL_SUPPORTED == STD_OFF) */

/**
@brief   (CAN183) The Can module may implement the function Can_MainFunction_BusOff as empty define in case no polling at all is used.
@remarks Covers CAN183
@remarks Implements DCAN00183
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_h_REF_1
*/
/*lint -save -e961*/
#define Can_MainFunction_BusOff()
/*lint -restore*/

#endif /* (CAN_BUSOFFPOLL_SUPPORTED == STD_OFF) */


/**
@brief         Function called at fixed cyclic time. SID = 0x0A
@details       Service for performs performs the polling of wake-up events that are configured statically as 'to be polled'.

@pre           Driver must be initialized.
@post          Handle the wakeup event.

@remarks       (CAN228) Can_MainFunction_Wakeup service.
@remarks       Covers CAN228
@remarks       Implements DCAN00228
*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #if (CAN_WAKEUPPOLL_SUPPORTED == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC (void, CAN_CODE) Can_MainFunction_Wakeup( void);
/*lint -restore*/
  #else /* (CAN_WAKEUPPOLL_SUPPORTED == STD_OFF) */

/**
@brief   (CAN185) The Can module may implement the function Can_MainFunction_Wakeup as empty define in case no polling at all is used.
@remarks Covers CAN185
@remarks Implements DCAN00185
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_h_REF_1
*/
/*lint -save -e961*/
  #define Can_MainFunction_Wakeup()
/*lint -restore*/

  #endif /* (CAN_WAKEUPPOLL_SUPPORTED == STD_OFF) */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


/**
@brief         Process BusOff event.

@param[in]     controller controller ID

@pre           Driver must be initialized.
@post          Handle the Busoff event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
FUNC(void, CAN_CODE) Can_Process_BusOff( CONST(uint8, CAN_CONST) controller );


/**
@brief         Process WakeUp event.

@param[in]     controller controller ID

@pre           Driver must be initialized.
@post          Handle the Wakeup event.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)
FUNC(void, CAN_CODE) Can_Process_Wakeup( CONST(uint8, CAN_CONST) controller );
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


/**
@brief         Process Receive Data event.

@param[in]     controller controller ID
@param[in]     mbindex_start first MB to process.
@param[in]     mbindex_end last MB to process.

@pre           Driver must be initialized.
@post          Handle the Receive event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
FUNC(void, CAN_CODE) Can_Process_Rx( CONST(uint8, CAN_CONST) controller,
                                     CONST(uint8, CAN_CONST) mbindex_start,
                                     CONST(uint8, CAN_CONST) mbindex_end );


/**
@brief         Process Transmit Data event.

@param[in]     controller controller ID
@param[in]     mbindex_start first MB to process.
@param[in]     mbindex_end last MB to process.

@pre           Driver must be initialized.
@post          Handle the Transmit event.

@remarks       Not AUTOSAR required. This is user implementation.
*/
FUNC(void, CAN_CODE) Can_Process_Tx( CONST(uint8, CAN_CONST) controller,
                                     CONST(uint8, CAN_CONST) mbindex_start,
                                     CONST(uint8, CAN_CONST) mbindex_end );


/**
@brief         Process Rx Fifo FrameAvailable events
@details       This function is much faster for handling FrameAvailable interrupt events than Can_Process_Rx, specific to MB

@param[in]     controller controller ID

@pre           Driver must be initialized.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if (CAN_RXFIFO_ENABLE == STD_ON)
FUNC(void, CAN_CODE) Can_RxFifoFrameAvNotif( CONST(uint8, CAN_CONST) controller);
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/**
@brief         Process a message buffer abort
@details       This function write a abort code (b'1001) to MBCS[CODE] field of the MB.

@param[in]     can_mb message buffer ID

@pre           Driver must be initialized and the current MB transmission should be in progress.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if (CAN_API_ENABLE_ABORT_MB == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC(void, CAN_CODE) Can_AbortMb( VAR(Can_HWObjectCountType, CAN_VAR) Hth);
/*lint -restore*/
#endif /* (CAN_API_ENABLE_ABORT_MB == STD_ON) */


/**
@brief         Process a transition from one clock source to another.
@details       This function is configuring Can controllers to run on the same baudrate, but having a different MCU source clock.

@param[in]     can_controller controller ID
@param[in]     can_clk_mode clock mode selection
@return        Std_ReturnType Result of the clock switch operation.
@retval        E_OK  Switch clock operation was ok.
@retval        E_NOT_OK  Switch clock operation was not ok.

@pre           Driver must be initialized and all the controllers must be in Stop state.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
/**
@note Violates MISRA 2004 Advisory Rule 8.10, External .. could be made static. - See @ref Can_h_REF_2
*/
/*lint -save -e765*/
extern FUNC(Std_ReturnType, CAN_CODE) Can_SetClockMode( VAR(uint8, CAN_VAR) can_controller, VAR(Can_ClockMode, CAN_VAR) can_clk_mode);
/*lint -restore*/
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

#define CAN_STOP_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"



/*==================================================================================================
                           VARIABLES SECTION
==================================================================================================*/
/**
@brief    Holds current status/run-time of CAN driver: CAN_UNINIT or CAN_READY (declared as global variable in "Can.c" file).
@brief    (CAN103) After power-up/reset, the Can module shall be in the state CAN_UNINIT.
@remarks  Covers CAN103
@remarks  Implements DCAN00103
*/
#define CAN_START_SEC_VAR_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)

extern VAR(Can_StatusType, CAN_VAR) Can_DriverStatus;

#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

extern P2CONST(Can_ConfigType, CAN_VAR, CAN_APPL_CONST) Can_CurrentConfigPtr;
extern P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Can_ControllerConfigPtr;

#define CAN_STOP_SEC_VAR_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"

/* Pointer to the current Driver Configuration (passed to the driver during initialization). Initialized by Can_Init(). */
#define CAN_START_SEC_CONST_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"

/* Extern declarations for CanController Configuration and CanConfigType. Exports the PC or PB Can_ConfigType structures. */
#ifdef CAN_PRECOMPILE_SUPPORT
    /* Export Driver configuration */
    CAN_INIT_CONFIG_PC_DEFINES
    /* Export Controllers configuration */
    CAN_INIT_CONFIG_CONTROLLERS_PC
#endif /* ifdef CAN_PRECOMPILE_SUPPORT */

#define CAN_STOP_SEC_CONST_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"

#define CAN_START_CONFIG_DATA_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"

#ifndef CAN_PRECOMPILE_SUPPORT
    /* Export Driver configuration */
    CAN_INIT_CONFIG_PB_DEFINES
    /* Export Controllers configuration */
    CAN_INIT_CONFIG_CONTROLLERS_PB
#endif /* ifndef CAN_PRECOMPILE_SUPPORT */

#define CAN_STOP_CONFIG_DATA_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 4 above */
#include "MemMap.h"



#ifdef __cplusplus
}
#endif

#endif /* _CAN_H_ */
