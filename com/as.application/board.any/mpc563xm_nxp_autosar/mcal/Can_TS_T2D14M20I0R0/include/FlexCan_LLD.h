/**
    @file             FlexCan_LLD.h
    @version          2.0.0

    @brief            AUTOSAR Can LLD module interface.
    @details          Low Level Driver header file for IPV = FlexCan.

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
@page misra_violations MISRA-C:2004 violations

 @section Can_h_REF_1
Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar .
@section Can_h_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
here are different kinds of execution code sections.
*/
#ifndef _FLEXCAN_LLD_H_
/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier:_FLEXCAN_LLD_H_. - See @ref Can_h_REF_1
*/
#define _FLEXCAN_LLD_H_


#ifdef  __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@{
@brief   (CAN222) Imported types: Dem_Types.h, CanIf_Types.h, Std_Types.h, ComStack_Types.h
@remarks Covers CAN222
@remarks Implements DCAN00222
*/
#include "Reg_Macros.h"
/**@}*/
#include "Reg_eSys_FlexCan.h"


/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION                                       
==================================================================================================*/
/**
@{
@brief    Internal micro-dependent versioning.
*/
#define CAN_AR_MAJOR_VERSION_LLD   3
#define CAN_AR_MINOR_VERSION_LLD   0
#define CAN_AR_PATCH_VERSION_LLD   0
#define CAN_SW_MAJOR_VERSION_LLD   2
#define CAN_SW_MINOR_VERSION_LLD   0
#define CAN_SW_PATCH_VERSION_LLD   0
/**@}*/


/*==================================================================================================
                              ENUM SECTION
==================================================================================================*/
/**
@enum      Can_HandleType
            Used for value received by Tressos interface configuration.
            Controller does not provide any bit field to differentiate BASIC-CAN & FULL-CAN.
*/
typedef enum
    {
        BASIC = 0U,    /**< Basic-CAN device functions */
        FULL           /**< Full-CAN device functions */
    } Can_HandleType;


/**
@brief     CAN Interrupts state.
*/
typedef enum
    {
        CAN_INTERRUPT_DISABLED = 0U,  /**< Interrupts disabled */
        CAN_INTERRUPT_ENABLED         /**< Interrupts enabled */

    } Can_InterruptStateType;   



/*==================================================================================================
                              STRUCT SECTION
==================================================================================================*/
/**
@brief     Records the status of a CAN Controller during runtime. 
@remarks   This structure is not configured by Tresos.
*/
typedef struct
    {
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        /**
        @brief Guard bits for EXCLUSIVE ACCESS to Tx MBs
        */
        VAR(uint32, CAN_VAR) TxGuard[2];

        /**
        @brief Pre-calculated MB INT masks (used in Can_EnableControllerInterrupts)
        */
        VAR(uint32, CAN_VAR) MBInterruptMask[2];

        /**
        @brief Storage space for PDU_ID (supplied in call to Can_Write and needed after Tx in CanIf_TxConfirmation)
        */
        VAR(PduIdType, CAN_VAR) TxPduId[64];
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
        /**
        @brief Guard bits for EXCLUSIVE ACCESS to Tx MBs
        */
        VAR(uint32, CAN_VAR) TxGuard[1];

        /**
        @brief Pre-calculated MB INT masks (used in Can_EnableControllerInterrupts)
        */
        VAR(uint32, CAN_VAR) MBInterruptMask[1];

        /**
        @brief Storage space for PDU_ID (supplied in call to Can_Write and needed after Tx in CanIf_TxConfirmation)
        */
        VAR(PduIdType, CAN_VAR) TxPduId[32];
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

        /**
        @brief Storage space for Can_DisableControllerInterrupts nesting level
        */
        volatile VAR(sint8, CAN_VAR) IntDisableLevel;

        /**
        @brief Index of MB buffer being cancelled.
        */
        volatile VAR(Can_HWObjectCountType, CAN_VAR) CancelMBIndex;

        /**
        @brief Index of the first MB used for Tx for a specific controller. This value is relative to 0 (which is first MB).
        */
        volatile VAR(uint8, CAN_VAR) FirstTxMBIndex;

        /**
        @brief Software flags for tracking interrupt changes state
        */
        VAR(uint8, CAN_VAR) ControllerSWFlag;

        /**
        @brief Global interrupt autorization state
        */
        VAR(uint8, CAN_VAR) InterruptMode;

        /**
        @brief FlexCAN controller power state
        */
        VAR(Can_StateTransitionType, CAN_VAR) ControllerState;
        
        /**
        @brief Map for every MB the HOH assigned according to configuration.
        */
        VAR(uint32, CAN_VAR) Can_MBMapping[CAN_MAXMB_SUPPORTED];

    } Can_ControllerStatusType;


/*================================================================================================*/
/** 
@brief   Array holding current status/run-time configuration of individual FlexCAN controllers:
           - information like Guard bits, Pre-calculated MB INT masks, Storage space for PDU_ID, INT nesting level,
            Index of MB buffer being cancelled, Index of the first MB used for Tx
           - declared as global variable in "can_LLD.c" file.
        See FlexCan_LLD.c for declaration.
*/
#define CAN_START_SEC_VAR_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"
extern VAR(Can_ControllerStatusType, CAN_VAR) Can_ControllerStatuses[CAN_MAXCTRL_SUPPORTED];
#define CAN_STOP_SEC_VAR_UNSPECIFIED
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"
/*================================================================================================*/


/*================================================================================================*/
/**
@{
@brief     Typedef section.
*/
typedef P2CONST( Can_MBConfigContainerType, CAN_CONST, CAN_APPL_DATA)   Can_PtrMBConfigContainerType;
typedef P2CONST( Can_ControlerDescriptorType, CAN_CONST, CAN_APPL_DATA) Can_PtrControlerDescriptorType;
/**@}*/
/*================================================================================================*/


/*==================================================================================================
                            LLD FUNCTION PROTOTYPES SECTION
==================================================================================================*/
#define CAN_START_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"

/**
@brief     Initialisation of indicator, statuses, etc.
           This routine is called by:
            - Can_Init() from Can.c file.

@pre       At least one controller must be configured in the Driver structure.
@post      Set variables into a definite state.
*/
FUNC (void, CAN_CODE) Can_LLD_InitVariables( void);


/**
@brief         Service for initializing the Can driver module according to a configuration set referenced by Config.
@details       Driver Module Initialization - LLD Driver Module Initialization
               This routine is called by:
                - Can_Init() from Can.c file.

@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           At least one controller must be configured in the Driver structure.
@post          Controller is enabled and set into Stop mode.
*/
FUNC (void, CAN_CODE) Can_LLD_Init( P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor);


/**
@brief         Service for reset the controller.
@details       Re-initialization must start with a reset (soft).
               This routine is called by:
                - Can_LLD_InitController() from FlexCan_LLD.c file.

@param[in]     Controller CAN controller for which the init shall be done (CAN_FCA_INDEX / CAN_FCB_INDEX).
                This ID depends by the order of the controller's definition in the Tresos 'CanController' list.
                If CanController_0 is assigned to CANB then CAN_FCB_INDEX is 0.
                These indexes are used for access inside 'Can_ControlerDescriptorType' structure.

@post          Controller is enabled and reset.
*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_ResetController( VAR(uint8, CAN_VAR) Controller);


/**
@brief         Service for (re)initializing only CAN controller specific settings.
@details       CAN controller (re-)initialization.
               This routine is called by:
                - Can_Init() from Can.c file.
                - Can_InitController() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     Config Pointer to controller configuration (CTRL reg, some specific Options)

@pre           At least one controller must be configured in the Driver structure.
@post          Set the MBs and interrupts into predefinite state for Can bus communication.
*/
FUNC (void, CAN_CODE) Can_LLD_InitController( VAR(uint8, CAN_VAR) Controller,
                                              P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Config);


/**
@brief         Service to Perform software triggered state transitions of the CAN controller State machine.
@details       Transition controller to another state/mode.
               This routine is called by:
                - Can_SetControllerMode() from Can.c file.
                - Can_Process_BusOff() from Can.c file.
                - Can_Process_Wakeup() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration
@param[in]     Transition Possible transitions

@return        Can_ReturnType
@retval        CAN_OK transition initiated
@retval        CAN_NOT_OK development or production error

@pre           Controller is configured and must be into a state that permit the valid transition to another different state.
@post          Shall enable interrupts that are needed in the new state. Shall disable interrupts that are not allowed in the new state.
*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_SetControllerMode( VAR(uint8, CAN_VAR) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor,
                                                           Can_StateTransitionType Transition);


/**
@brief         Service disables all interrupts for the given CAN controller.
@details       This routine is called by:
                - Can_DisableControllerInterrupts() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           Disable interrupts must be called prior to enable interrupts.
@post          Clear all flags/bits that are needded for disabling the interrupts.
*/
FUNC (void, CAN_CODE) Can_LLD_DisableControllerInterrupts( VAR(uint8, CAN_VAR) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor);


/**
@brief         Service enables all interrupts that shall be enabled according the current software status.
@details       This routine is called by:
                - Can_EnableControllerInterrupts() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           Can be executed only if disable interrupts was called before.
@post          Enable all interrupts that must be enabled according the current sw status.
*/
FUNC (void, CAN_CODE) Can_LLD_EnableControllerInterrupts( VAR(uint8, CAN_VAR) Controller,
                                                          P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor);


/**
@brief         Local function for canceling low priority msg during Can Write operation.
@details       This routine is called by:
                - Can_LLD_Write() from FlexCan_LLD.c file.
                - Can_AbortMb() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     mbindex index of the message buffer to be canceled

@pre           A Tx message with a higher priority was requested for a MB.
@post          Inform CanIf about cancellation in case of success.
*/

#if (CAN_TXCANCEL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_Cancel( VAR(uint8, CAN_VAR) controller,
                                      VAR(uint8, CAN_VAR) mbindex);

#endif /* (CAN_TXCANCEL_SUPPORTED == STD_ON) */

/**
@brief         Process a message buffer abort
@details       This function write a abort code (b'1001) to MBCS[CODE] field of the MB.

@param[in]     can_mb message buffer ID

@pre           Driver must be initialized and the current MB transmission should be in progress.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON))

FUNC(void, CAN_CODE) Can_LLD_AbortMb( VAR(Can_HWObjectCountType, CAN_VAR) Hth );

#endif /* ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON)) */

/**
@brief         Can_LLD_Write checks if hardware transmit object that is identified by the HTH is free.
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

@details       This routine is called by:
                - Can_Write() from Can.c file.
                
@param[in]     Hth information which HW-transmit handle shall be used for transmit.
                 Implicitly this is also the information about the controller to use
                 because the Hth numbers are unique inside one hardware unit.
@param[in]     PduInfo Pointer to SDU user memory, DLC and Identifier

@return        Can_ReturnType
@retval        CAN_OK write command has been accepted
@retval        CAN_NOT_OK development error occured
@retval        CAN_BUSY no TX hardware buffer available or preemtive call of Can_Write() that can't be implemented reentrant

@pre           The MB must be configured for Tx.
@post          Transmit the data or ignore it in case of MB is full with another task.

@remarks       Algorithm Description:
               Case1: TxMUX supported = ON
                      Can_Write receive the Hth handle and the PduInfo for transmission. It starts to check from the first MBs of the
                      current controller to search for a free MB. On the first free MB it stops and place the PduInfo and activate the transmission.
                      In this case function set CAN_OK for return value and all other functionality is skipped.
                      If no MB is finded as free then the lowest priority MB is selected for comparing with the priority of the current PduInfo.
                      If the current PduInfo has a higher priority than the current lower priority (from all MBs) then this lower priority MB is canceled.
               Case2: TxMUX supported = OFF
                      CanWrite() receive the Hth handle and the PduInfo for transmission. It checks if MB with the same index as Hth is free and if yes prepare
                      and sends the current PduInfo data. If that MB is bussy with another data then it checks the priority between these 2 structures.
                      Depending by the last evaluation it decides what MB data to cancel.
*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_Write( Can_HWObjectCountType Hth,
                                               P2CONST(Can_PduType, CAN_VAR, CAN_APPL_CONST) PduInfo);


/** 
@brief         Local function for calling notification function to notify upper layer
                 during Can_MainFunction_Write if polling is selected or from ISR when Interrupt mode selected.
@details       Processes Tx interrupt flags.
               This routine is called by: 
                - Can_Process_Tx() from Can.c file.
                - Can_LLD_MainFunction_Write() from FlexCan_LLD.c file.
                - Can_IsrFC##FC##_UNI() / Can_IsrFC##FC##_##Name() from Can_Irq.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     mbindex_start first MB to process.
@param[in]     mbindex_end last MB to process.

@pre           MB is configured for Tx.
@post          CanIf is informed with cancellation or transmit success.
*/
FUNC (void, CAN_CODE) Can_LLD_Process_Tx( CONST(uint8, CAN_CONST) controller,
                                          CONST(uint8, CAN_CONST) mbindex_start,
                                          CONST(uint8, CAN_CONST) mbindex_end);


/**
@brief         Local function for calling notification function to notify upper layer during
                 Can_MainFunction_Read if polling is selected or from ISR when Interrupt mode selected.
@details       Processes Rx interrupt flags.
               This routine is called by: 
                    - Can_Process_Rx() from Can.c file
                    - Can_LLD_MainFunction_Read() from FlexCan_LLD.c file
                    - Can_IsrFC##FC##_UNI() / Can_IsrFC##FC##_##Name() from Can_Irq.c file

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     mbindex_start first MB to process
@param[in]     mbindex_end last MB to process

@pre           MB is configured for Rx.
@post          Inform CanIf in case a data frame was received.
*/
FUNC (void, CAN_CODE) Can_LLD_Process_Rx( CONST(uint8, CAN_CONST) controller,
                                          CONST(uint8, CAN_CONST) mbindex_start,
                                          CONST(uint8, CAN_CONST) mbindex_end);


/**
@brief         Local function for calling notification function to notify upper layer during
                 Can_MainFunction_Wakeup if polling is selected or from ISR when Interrupt mode selected.
@details       Processes WakeUp condition
               This routine is called by:
                - Can_Process_Wakeup from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 

@pre           A wakeup condition must be fulfilled.
@post          Clear the flag for wakeup condition.
*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_Process_Wakeup( CONST(uint8, CAN_CONST) controller);

#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/**
@brief         Service to perform the polling of TX confirmation and TX cancellation confirmation
@details       This routine is called by:
                - Can_MainFunction_Write() from Can.c file.
@pre           The controller must be configured for transmit in polling mode and at least one MB is configured for Tx.
@post          Process the transmission data in case of availability.
*/

#if (CAN_TXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_MainFunction_Write( void);

#endif /* (CAN_TXPOLL_SUPPORTED == STD_ON) */


/**
@brief         Service to perform the polling of RX indications.
@details       This routine is called by:
                - Can_MainFunction_Read() from Can.c file.

@pre           The controller must be configured for receive in polling mode and at least one MB is configured for Rx.
@post          Process the reception data in case of availability.
*/

#if (CAN_RXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_MainFunction_Read( void);

#endif /* (CAN_RXPOLL_SUPPORTED == STD_ON) */


/**
@brief         Local function for calling notification function to notify upper layer during
                 Can_MainFunction_BusOff if polling is selected or from ISR when Interrupt mode selected.
@details       This routine is called by:
                - Can_Process_BusOff() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 

@pre           A busoff condition must to be fulfilled.
@post          Status flag is cleared.
*/
FUNC (void, CAN_CODE) Can_LLD_Process_BusOff( CONST(uint8, CAN_CONST) controller);


/**
@brief         This function checks if a Wakeup has occurred for the given controller.
@details       This routine is called by:
                - Can_MainFunction_Wakeup() from Can.c file.
                - Can_Cbk_CheckWakeup() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 

@return        Std_ReturnType
@retval        E_OK wakeup detected
@retval        E_NOT_OK wakeup not detected

@pre           A request for wakeup checking is required.
@post          Report the occurence or not for a wakeup event.
*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (Std_ReturnType, CAN_CODE) Can_LLD_Cbk_CheckWakeup( VAR(uint8, CAN_VAR) controller);

#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


/**
@brief         This function checks if a BusOff has occurred for the given controller.
@details       This routine is called by:
                - Can_MainFunction_BusOff() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 

@return        Std_ReturnType
@retval        E_OK busoff detected
@retval        E_NOT_OK busoff not detected

@pre           A request for busoff checking is required.
@post          Report the occurence or not for a busoff event.
*/
FUNC (Std_ReturnType, CAN_CODE) Can_LLD_CheckBusOff( VAR(uint8, CAN_VAR) controller);


/**
@brief         Process Rx Fifo FrameAvailable events.
@details       This routine is called by:
                - Can_RxFifoFrameAvNotif() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 

@pre           Driver must be initialized and RxFifo should be enabled.
*/

#if (CAN_RXFIFO_ENABLE == STD_ON)

FUNC(void, CAN_CODE) Can_LLD_RxFifoFrameAvNotif( CONST(uint8, CAN_CONST) controller);

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/**
@brief         Process a transition from one clock source to another.
@details       This function is configuring Can controllers to run on the same baudrate, but having a different MCU source clock.
@details       This routine is called by:
                - Can_SetClockMode() from Can.c file.

@param[in]     can_controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId). 
@param[in]     can_clk_mode clock mode selection
@return        Std_ReturnType Result of the clock switch operation.
@retval        E_OK  Switch clock operation was ok.
@retval        E_NOT_OK  Switch clock operation was not ok.

@pre           Driver must be initialized and all the controllers must be in Stop state.

@remarks       Not AUTOSAR required. This is user implementation.
*/

#if (CAN_DUAL_CLOCK_MODE == STD_ON)

FUNC(Std_ReturnType, CAN_CODE) Can_LLD_SetClockMode( VAR(uint8, CAN_VAR) can_controller, VAR(Can_ClockMode, CAN_VAR) can_clk_mode);

#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */
#define CAN_STOP_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"

#ifdef  __cplusplus
}
#endif

#endif  /* _FLEXCAN_LLD_H_ */
