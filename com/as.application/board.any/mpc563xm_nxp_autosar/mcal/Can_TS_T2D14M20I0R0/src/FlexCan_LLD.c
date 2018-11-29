/**
    @file             FlexCan_LLD.c
    @version          2.0.0

    @brief            AUTOSAR Can LLD module implementation.
    @details          Low Level Driver implementation.

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

@section FlexCan_LLD_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section FlexCan_LLD_c_REF_2
Violates MISRA 2004 Advisory Rule 11.3 [Encompasses MISRA 2004 Rule 11.1] cast from unsigned long to pointer.
This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
is passed to  a amcro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).

@section FlexCan_LLD_c_REF_3
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.

@section FlexCan_LLD_c_REF_4
Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable
The code is not dynamically linked. An absolute stack address is obtained when taking the address of the near auto variable.
A source of error in writing dynamic code is that the stack segment may be different from the data segment.

@section FlexCan_LLD_c_REF_5
Violates MISRA 2004 Advisory Rule 17.4 , Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.

@section FlexCan_LLD_c_REF_6
Violates MISRA 2004 Advisory Rule 10.3 , The value of a complex expression of integer type may only be
cast to a type that is narrower and of the same signedness as the
underlying type of the expression
be accessed.

@section FlexCan_LLD_c_REF_7
Violates MISRA 2004 Advisory Rule 10.1 , The value of an expression of integer type shall not be implicitly
converted to a different underlying type if: a) it is not a
conversion to a wider integer type of the same signedness, or b)
the expression is complex, or c) the expression is not constant
and is a function argument, or d) the expression is not constant
and is a return expression

@section FlexCan_LLD_c_REF_8
Violates MISRA 2004 Advisory Rule 12.4 , side effects on right hand of logical operator: '&&'
The right hand side of the && doesnot have any side effect since in the codition CancelMBIndex has been accessed
to compare with the current can_mb_index.
*/


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
#include "Can.h"
#include "Can_LLD.h"
#include "CanIf_Cbk.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif
#include "Cer.h"
#include "Dem.h"
#include "SchM_Can.h"


/*==================================================================================================
                        DEFINES AND MACROS
==================================================================================================*/
/**
@{
@brief   Internal micro-dependent versioning.
         Check of AUTOSAR specification version & Vendor specific implementation version.
*/
#define CAN_VENDOR_ID_C                 43
#define CAN_AR_MAJOR_VERSION_LLD_C      3
#define CAN_AR_MINOR_VERSION_LLD_C      0
#define CAN_AR_PATCH_VERSION_LLD_C      0
#define CAN_SW_MAJOR_VERSION_LLD_C      2
#define CAN_SW_MINOR_VERSION_LLD_C      0
#define CAN_SW_PATCH_VERSION_LLD_C      0
/**@}*/


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_LLD_C != CAN_AR_MAJOR_VERSION) || \
     (CAN_AR_MINOR_VERSION_LLD_C != CAN_AR_MINOR_VERSION) || \
     (CAN_AR_PATCH_VERSION_LLD_C != CAN_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Can_LLD.c and FlexCan_LLD.h are different"
#endif
#endif

#if ((CAN_SW_MAJOR_VERSION_LLD_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_SW_MINOR_VERSION_LLD_C != CAN_SW_MINOR_VERSION))
#error "Software Version Numbers of Can_LLD.c and Can_LLD.h are different"
#endif



/*==================================================================================================
                                   VARIABLES
==================================================================================================*/
#define CAN_START_SEC_VAR_UNSPECIFIED

/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref FlexCan_LLD_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief   Array holding current status/run-time configuration of individual FlexCAN controllers
           - information like Guard bits, Pre-calculated MB INT masks, Storage space for id, INT nesting level,
         Index of MB buffer being cancelled, Index of the first MB used for Tx , Controller Options.
*/
VAR(Can_ControllerStatusType, CAN_VAR) Can_ControllerStatuses[CAN_MAXCTRL_SUPPORTED];


#define CAN_STOP_SEC_VAR_UNSPECIFIED
/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e451 -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/



/*==================================================================================================
                                       CONSTANTS
==================================================================================================*/

#define CAN_START_SEC_CONST_UNSPECIFIED

/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e451 -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief CAN base address array
*/
CONST(uint32, CAN_CONST) CAN_BASE_ADDRS[] = {
#ifdef  FLEXCAN0_BASEADDR
        FLEXCAN0_BASEADDR,
#endif /* FLEXCAN0_BASEADDR */
#ifdef  FLEXCAN1_BASEADDR
        FLEXCAN1_BASEADDR,
#endif /* FLEXCAN1_BASEADDR */
#ifdef  FLEXCAN2_BASEADDR
        FLEXCAN2_BASEADDR,
#endif /* FLEXCAN2_BASEADDR */
#ifdef  FLEXCAN3_BASEADDR
        FLEXCAN3_BASEADDR,
#endif /* FLEXCAN3_BASEADDR */
#ifdef  FLEXCAN4_BASEADDR
        FLEXCAN4_BASEADDR,
#endif /* FLEXCAN4_BASEADDR */
#ifdef  FLEXCAN5_BASEADDR
        FLEXCAN5_BASEADDR
#endif /* FLEXCAN5_BASEADDR */
    };


#define CAN_STOP_SEC_CONST_UNSPECIFIED


/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e451 -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                        FUNCTIONS
==================================================================================================*/
#define CAN_START_SEC_CODE
/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref FlexCan_LLD_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e451 -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*================================================================================================*/
/**
@brief     Initialisation of indicator, statuses, etc.
           This routine is called by:
            - Can_Init() from Can.c file.

@pre       At least one controller must be configured in the Driver structure.
@post      Set variables into a definite state.
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_InitVariables( void )
    {

        /* Index CAN controllers from configuration. */
        VAR(uint8, CAN_VAR) can_ctrl_index = 0U;
        VAR(uint8, CAN_VAR) can_mb_index = 0U;

        /* Init all global varibales/statuses for all controllers. */
        for ( can_ctrl_index = 0U; can_ctrl_index < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_ctrl_index++)
        {
            /* Init INT Disable nesting indicator. It is incremented after every call of Can_DisableControllerInterrupts().
               The function Can_EnableControllerInterrupts() shall perform no action when Can_DisableControllerInterrupts() has not been called before. */
            Can_ControllerStatuses[can_ctrl_index].IntDisableLevel = (sint8)0;

            /* Set interrupt mode status to interrupt disabled mode. */
            Can_ControllerStatuses[can_ctrl_index].ControllerSWFlag = (uint8)0U;

            /* Set to null the first Tx MB index for every controller. */
            Can_ControllerStatuses[can_ctrl_index].FirstTxMBIndex = (uint8)0U;

            /* Set  interrupt mode status to interrupt disabled mode. */
            Can_ControllerStatuses[can_ctrl_index].InterruptMode = (uint8)CAN_INTERRUPT_ENABLED;

            /* Set the controller state to STOP after power-up */
            Can_ControllerStatuses[can_ctrl_index].ControllerState = CAN_T_STOP;

            for (can_mb_index = 0U; can_mb_index < (uint8)CAN_MAXMB_SUPPORTED; can_mb_index++)
            {
                Can_ControllerStatuses[can_ctrl_index].Can_MBMapping[can_mb_index] = (uint32)0U;
           }

        }
    }


/*================================================================================================*/
/**
@brief         Service for initializing the Can driver module according to a configuration set referenced by Config.
@details       Driver Module Initialization - LLD Driver Module Initialization
               This routine is called by:
                - Can_Init() from Can.c file.

@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           At least one controller must be configured in the Driver structure.
@post          Controller is enabled and set into Stop mode.
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_Init( P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor )
    {

        /* Hardware Can controller offset. */
        VAR(uint8, CAN_VAR)  can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        can_hw_offset = can_ptrControlerDescriptor->ControllerOffset;

        /* Enter Freeze mode after enabling, Self-Reception disabled, individual MB filter masks set. */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        FLEXCAN_MCR_CONFIG( can_hw_offset, (uint32)(FLEXCAN_MCR_MDIS | FLEXCAN_MCR_FRZ | FLEXCAN_MCR_HALT | FLEXCAN_MCR_SRXDIS));
        /**
        @brief   (CAN259) The function Can_Init shall set all CAN controllers in the state CANIF_CS_STOPPED.
        @brief   (CAN260) The function Can_InitController shall maintain the CAN controller in the state CANIF_CS_STOPPED.
                 The function Can_InitController shall ensure that any settings that will cause the CAN controller to participate in the network are not set.
        @remarks Covers CAN259, CAN260
        @remarks Implements DCAN00259, DCAN00260
        */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        FLEXCAN_MCR_CONFIG( can_hw_offset, (uint32)(FLEXCAN_MCR_FRZ | FLEXCAN_MCR_HALT | FLEXCAN_MCR_SRXDIS));
    }


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_ResetController( VAR(uint8, CAN_VAR) Controller)
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, CAN_VAR) Out_can_return = CAN_OK;
        /* Timeout counter. */
        VAR(uint32, CAN_VAR)         can_timeout_count = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)          can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[Controller].ControllerOffset;


        /* The re-initialization of controller start with a Soft-Reset. Test if Can is not ready -> can be in any of disable, Doze/Stop/Freeze modes. */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        if ( FLEXCAN_MCR_NOTRDY == ((uint32)(FLEXCAN_MCR_READ(can_hw_offset)) & FLEXCAN_MCR_NOTRDY) )
        {
            /* Enable Can module. */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_CLEAR_MCR_MDIS( can_hw_offset);

            /* Exit from Stop Mode/Freeze/LowPower mode. */
            /**
            @{
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2

            */
            FLEXCAN_CLEAR_MCR_FRZ( can_hw_offset);
            FLEXCAN_CLEAR_MCR_HALT( can_hw_offset);
            /**@}*/
        }

        /* MCR[FLEXCAN_MCR_NOTRDY] not set yet -> controller still not terminate the reset procedure. */
        can_timeout_count = (uint32)CAN_TIMEOUT_DURATION;
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        while ( (FLEXCAN_MCR_NOTRDY == ((uint32)FLEXCAN_MCR_READ(can_hw_offset) & FLEXCAN_MCR_NOTRDY)) &&
                (can_timeout_count > (uint32)0x0U) )
        {
            can_timeout_count--;
        }


        /* Test for Hardware failure. */
        if ( (uint32)0x0U == can_timeout_count )
        {
            /* Report production error and Return from function (all the functionality is implemented by "else"). */
            Dem_ReportErrorStatus( (Dem_EventIdType)CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
            Out_can_return = CAN_NOT_OK;
        }
        else
        {
            /* Execute Controller Reset. */
            FLEXCAN_SET_MCR_SOFT_RST(can_hw_offset);

            /* Wait the Reset end off. */
            can_timeout_count = (uint32)CAN_TIMEOUT_DURATION;
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            while ( (FLEXCAN_MCR_SOFTRST == ((uint32)FLEXCAN_MCR_READ(can_hw_offset) & FLEXCAN_MCR_SOFTRST)) &&
                    (can_timeout_count > (uint32)0x0U) )
            {
                /* MCR[SOFT_RST] still set -> reset in progress. */
                can_timeout_count--;
            }

            /* Test for Hardware failure. */
            if ( (uint32)0x0U == can_timeout_count )
            {
                /* Report production error and Return from function (all the functionality is implemented by "else"). */
                Dem_ReportErrorStatus( (Dem_EventIdType)CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                Out_can_return = CAN_NOT_OK;

            }
            else
            {
                /* Enable access to module and enter in freeze mode - clearing MCR[MDIS] bit. */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_MCR_CONFIG( can_hw_offset, (uint32)(FLEXCAN_MCR_FRZ | FLEXCAN_MCR_HALT | FLEXCAN_MCR_SRXDIS));
                Can_ControllerStatuses[Controller].ControllerState = CAN_T_STOP;
            }
        }

        return (Out_can_return);
    }


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_InitController( VAR(uint8, CAN_VAR) Controller,
                                              P2CONST(Can_ControllerConfigType, CAN_VAR, CAN_APPL_CONST) Config )
    {

        /* Local copy of pointer to the controller descriptor. */
        VAR(Can_PtrControlerDescriptorType, CAN_VAR) can_ptrControlerDescriptor = NULL_PTR;
        /* Pointer to the MB container structure. */
        VAR(Can_PtrMBConfigContainerType, CAN_VAR)   can_ptrMBConfigContainer = NULL_PTR;
        /* Variable for indexing all the MBs fron hardware unit chain (all controllers). */
        VAR(uint16, CAN_VAR)            can_mb_global_index = 0U;
        /* Variable for indexing the MBs inside a single controller. */
        VAR(uint8, CAN_VAR)             can_mb_ctrl_index = 0U;
        /* ID of current MB. */
        VAR(uint32, CAN_VAR)            can_mb_messageid = 0U;
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
        /* Variable for calculating the interrupt masks of IMASK1 & IMASK2 register s*/
        VAR(uint8, AUTOMATIC) rxglobal_mskupdate = 0U;
        VAR(uint8, AUTOMATIC) Temp14 = 0U;
        VAR(uint8, AUTOMATIC) Temp15 = 0U;
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
        /* Used to access configured table id and filtermask. */
        VAR(uint8, CAN_VAR)             can_temp_index = 0U;
        /* Used to save the the index pointing to the table id connfiguration. */
        VAR(uint8, CAN_VAR)             can_rxfifo_tableid_index = 0U;
        /* Used to index the Table ID for RxFifo. */
        VAR(uint8, CAN_VAR)             can_rxfifo_tableid = 0U;
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)             can_hw_offset = 0U;
        /* Temporary register value. */
        VAR(uint32, CAN_VAR)            can_mb_config = 0U;
        /* Variable for return status. */
        VAR(Can_ReturnType, CAN_VAR)    can_reset_return = CAN_OK;


        /* Fill the local pointer copy with address of the Controller Descriptor.  */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_ptrControlerDescriptor = &(Can_CurrentConfigPtr->ControlerDescriptors[Controller]);
        can_ptrMBConfigContainer   = &(Can_CurrentConfigPtr->MBConfigContainer);


        /* Get the hardware offset for this controller. */
        can_hw_offset = can_ptrControlerDescriptor->ControllerOffset;

        /* Reset Controller. */
        can_reset_return = Can_LLD_ResetController( Controller);

        if (can_reset_return == CAN_OK)
        {
            /* Reset software Flags. */
            Can_ControllerStatuses[Controller].ControllerSWFlag = (uint8)0x0U;

#ifdef E2656_FLEXCAN_XPC56XXX
       #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
            /* If RFIFO is enabled then the first 8 MB will be used by the FIFO, initialize the
            CancelMBIndex to the value of Max. MB supported to avoid the false TX-MB cancellation */
            if ( CAN_CONTROLLERCONFIG_RXFIFO == (Config->Options & CAN_CONTROLLERCONFIG_RXFIFO))
            {
                Can_ControllerStatuses[Controller].CancelMBIndex = CAN_MAXMB_SUPPORTED;
            }
            else /* RFIFO is disabled */
            {
                /* Init the Cancelled MB index with a precalculated value - out of range for every controller. */
                Can_ControllerStatuses[Controller].CancelMBIndex = can_ptrMBConfigContainer->MessageBufferConfigCount;
            }
       #endif
#else
            /* Init the Cancelled MB index with a precalculated value - out of range for every controller. */
            Can_ControllerStatuses[Controller].CancelMBIndex = can_ptrMBConfigContainer->MessageBufferConfigCount;
#endif /* E2656_FLEXCAN_XPC56XXX */

            /* Clear Tx guard flags. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            /* Check whether Can controller supports 64 message buffers */
            if ( FLEXCAN_MB_64 == Config->Can_NumberOfMB)
            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                Can_ControllerStatuses[Controller].TxGuard[1U] = (uint32)0x0UL;
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64 ) */
            Can_ControllerStatuses[Controller].TxGuard[0U] = (uint32)0x0UL;


#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
            /* Check if BCC support is enabled in configuration */
            if ( CAN_CONTROLLERCONFIG_BCC_EN != (Config->Options & CAN_CONTROLLERCONFIG_BCC_EN) )
            {
                /* Enable individual MB filter masking. */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */

                FLEXCAN_SET_MCR_BCC(can_hw_offset);
            }
#else /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                /* Enable individual MB filter masking. */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */

                FLEXCAN_SET_MCR_BCC(can_hw_offset);

#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* FlexCan uses the filtered RX input to detect recessive to dominant edges on the bus. */
            if ( CAN_CONTROLLERCONFIG_WAKEUP_SRC == (Config->Options & CAN_CONTROLLERCONFIG_WAKEUP_SRC) )
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_SET_MCR_WAK_SRC( can_hw_offset);
            }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* FlexCan uses local priority feature - extend the ID during the arbitration process with PRIO field from MB reg. */
            if ( CAN_CONTROLLERCONFIG_LPRIO_EN == (Config->Options & CAN_CONTROLLERCONFIG_LPRIO_EN) )
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_SET_MCR_LPRIOEN( can_hw_offset);
            }

            /* If WRN_EN is set the TWRN_INT and RWRN_INT will be set error counter transition from <96 to >= 96. */
            if ( CAN_CONTROLLERCONFIG_WRNINT_EN == (Config->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_SET_MCR_WRNEN( can_hw_offset);
            }

            /* Set-up Control Register (CTRL - Controller Configuration) - Config->ControlRegister is configured by user using Tresos tool. */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_CTRL_CONFIG( can_hw_offset, (uint32)(Config->ControlRegister));

            /* Loop Back Mode configuration. Clear also the MCR[SRCXDIS] to allow receiving frames transmitted by itself. */
            if ( FLEXCAN_CTRL_LPB == (Config->ControlRegister & FLEXCAN_CTRL_LPB) )
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_CLEAR_MCR_SRXDIS( can_hw_offset);
            }


            /* Stage1: init RxFifo ******************************************************************** */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /* If RX FIFO is used, then configure the Controller's registers for Rx Fifo. */
            if ( CAN_CONTROLLERCONFIG_RXFIFO == (Config->Options & CAN_CONTROLLERCONFIG_RXFIFO) )
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_SET_MCR_FEN( can_hw_offset);

                /* Processing MB must start from index 8 if RxFifo is enabled when configure MBs. */
                can_mb_ctrl_index += FLEXCAN_FIFO_MB_COUNT;

                switch (Config->Options & CAN_CONTROLLERCONFIG_IDAM_MASK)
                {
                    case CAN_CONTROLLERCONFIG_IDAM_A:
                        /* One full ID per filter element - clear IDAM bits. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_SET_MCR_IDAM( can_hw_offset, FLEXCAN_MCR_IDAM32);
                        break;

                    case CAN_CONTROLLERCONFIG_IDAM_B:
                        /* Two full standard IDs or two partial 14-bit exteneded IDs per filter element. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_SET_MCR_IDAM( can_hw_offset, FLEXCAN_MCR_IDAM16);
                        break;

                    case CAN_CONTROLLERCONFIG_IDAM_C:
                        /* Four partial 8-bit IDs (standard or extended) per filter element. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_SET_MCR_IDAM( can_hw_offset, FLEXCAN_MCR_IDAM08);
                        break;

                    case CAN_CONTROLLERCONFIG_IDAM_D:
                        /* RX Fifo is enabled, but all frames will be rejected. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_SET_MCR_IDAM( can_hw_offset, FLEXCAN_MCR_IDAM);
                        break;

                    default:
                        /* This case should never occurs. */
                        Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_DEFAULT);
                        /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                              Cer_ReportError() function implementation */
                        break;
                } /* end switch. */

                /* Save the index pointing to table id configuration. */
                can_rxfifo_tableid_index = Can_CurrentConfigPtr->ControlerDescriptors[Controller].RxFiFoTableIdConfigIndex;

                /* Init the IDTable and RXIMR registers of RxFifo. */
                for ( can_temp_index = can_rxfifo_tableid_index; can_temp_index < (can_rxfifo_tableid_index + FLEXCAN_FIFO_MB_COUNT); can_temp_index++)
                {
                    /* Calculate the physical address for each table to write the Table ID and FilterMask. */
                    /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                    FLEXCAN_RXFIFO_ID_CONFIG( can_hw_offset, can_rxfifo_tableid,
                                            (uint32)(((Can_CurrentConfigPtr->Can_RxFiFoTableIdConfigPtr) + can_temp_index)->TableId) );
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                    /* Check if BCC support is enabled in configuration */
                    if ( CAN_CONTROLLERCONFIG_BCC_EN != (Config->Options & CAN_CONTROLLERCONFIG_BCC_EN) )
                    {
#endif
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_RXIMR_CONFIG( can_hw_offset, can_rxfifo_tableid,
                                        (uint32)((((Can_CurrentConfigPtr->Can_RxFiFoTableIdConfigPtr) + can_temp_index))->TableFilterMask));
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                    }
#endif
                    /* Increment the Table Id index for RxFifo configuration. */
                    can_rxfifo_tableid++;
                }

                /* Configure Interrupt Mask Bits in case handling of RX is implemented by interrupts (not by polling). */
                if ( CAN_CONTROLLERCONFIG_RXPOL_EN != (CAN_CONTROLLERCONFIG_RXPOL_EN & Config->Options) )
                {
                    /* Check if Overflow RxFifo interrupt is enabled and set the IMASK bit if yes. */
                    if ( CAN_CONTROLLERCONFIG_OVER_EN == (Config->Options & CAN_CONTROLLERCONFIG_OVER_EN) )
                    {
                        Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX] |= FLEXCAN_FIFO_OVERFLOW_INT_MASK;
                    }
                    /* Check if Warning RxFifo interrupt is enabled and set the IMASK bit if yes. */
                    if ( CAN_CONTROLLERCONFIG_WARN_EN == (Config->Options & CAN_CONTROLLERCONFIG_WARN_EN) )
                    {
                        Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX] |= FLEXCAN_FIFO_WARNING_INT_MASK;
                    }
                    /* If RxFifo is enabled, then frames are implicitly enabled. IDAM bits can filter the messages or can block at all. */
                    Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX] |= FLEXCAN_FIFO_AVAILABLE_INT_MASK;
                }
            }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

            /* Stage2: Init Rx/Tx MBs ******************************************************************** */

            /* Parse all MBs from the chain list, but process only the MBs for controller transmitted as parameter in this function. */
            while ( (can_mb_ctrl_index < can_ptrControlerDescriptor->MaxMBCount) &&
                    (can_mb_global_index < can_ptrMBConfigContainer->MessageBufferConfigCount) )
            {
                /* can_mb_global_index variable is incrementing based of existing HOH for MBs. */
                /**
                 @{
                 @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                */
                if ( Controller == (((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->ControllerId))
                {
                    switch ( ((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->MBType )
                    {
                        case (RECEIVE):
                            /* Get the ID of the current MB. */
                            can_mb_messageid = (uint32)((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->MessageId;
               /** @} */

                            /* Clear variable for every MB. */
                            can_mb_config = (uint32)0U;

#if (CAN_EXTENDEDID == STD_ON)
                   /**
                    @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                   */
                            if ( STANDARD == (((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdType) )
                            {
#endif /* (CAN_EXTENDEDID == STD_ON) */
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                /* Check if BCC support is enabled in configuration */
                                    if ( CAN_CONTROLLERCONFIG_BCC_EN == (Config->Options & CAN_CONTROLLERCONFIG_BCC_EN) )
                                    {
#if (CAN_RXFIFO_ENABLE == STD_ON)
                                        /* If RX FIFO is used, then configure the Controller's registers for Rx Fifo. */
                                        if ( CAN_CONTROLLERCONFIG_RXFIFO != (Config->Options & CAN_CONTROLLERCONFIG_RXFIFO) )
                                        {
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

                                            if((can_mb_ctrl_index != CAN_MB_14) && (can_mb_ctrl_index != CAN_MB_15) && (rxglobal_mskupdate == 0U))
                                            {
                                               /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */


                                                FLEXCAN_RXGMASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex] << 18U) );
                                                rxglobal_mskupdate++;
                                            }
                                            else if((can_mb_ctrl_index == CAN_MB_14) && (Temp14 == 0U))
                                            {
                                                /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */
                                                FLEXCAN_RX14MASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex] << 18U) );
                                                Temp14++;
                                            }
                                            else if((can_mb_ctrl_index == CAN_MB_15) && (Temp15 == 0U))
                                            {
                                                /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */
                                                FLEXCAN_RX15MASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex] << 18U) );
                                                Temp15++;
                                            }
                                            else
                                            {
                                                /* Already the  RX Global MASK register is updated, its used as acceptance mask for all Rx MBs except for 14 and 15 MB's*/
                                            }
#if (CAN_RXFIFO_ENABLE == STD_ON)
                                        }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
                                    }
                                    else
                                    {
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                        /**
                                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                        */
                                        FLEXCAN_RXIMR_CONFIG( can_hw_offset, can_mb_ctrl_index, (uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex] << 18U) );
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                    }
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                /* Copy the Message ID (serves as acceptance filter for Rx MBs). For Standard type, ID is placed on bits 28:18 on ID Reg of the MB structure. */
                                can_mb_messageid <<= FLEXCAN_STANDARD_ID_SHIFT;
#if (CAN_EXTENDEDID == STD_ON)
                            }
                            else
                            {
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                    /* Check if BCC support is enabled in configuration */
                                    if ( CAN_CONTROLLERCONFIG_BCC_EN == (Config->Options & CAN_CONTROLLERCONFIG_BCC_EN) )
                                    {

#if (CAN_RXFIFO_ENABLE == STD_ON)
                                        /* If RX FIFO is used, then configure the Controller's registers for Rx Fifo. */
                                        if ( CAN_CONTROLLERCONFIG_RXFIFO != (Config->Options & CAN_CONTROLLERCONFIG_RXFIFO) )
                                        {
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
                                            if((can_mb_ctrl_index != CAN_MB_14) && (can_mb_ctrl_index != CAN_MB_15) && (rxglobal_mskupdate == 0U))
                                            {
                                                /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */
                                                FLEXCAN_RXGMASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex]) );
                                                rxglobal_mskupdate++;
                                            }
                                            else if((can_mb_ctrl_index == CAN_MB_14) && (Temp14 == 0U))
                                            {
                                                /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */
                                                FLEXCAN_RX14MASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex]) );
                                                Temp14++;
                                            }
                                            else if((can_mb_ctrl_index == CAN_MB_15) && (Temp15 == 0U))
                                            {
                                                /**
                                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                                */
                                                FLEXCAN_RX15MASK_CONFIG(can_hw_offset,(uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex]) );
                                                Temp15++;
                                            }
                                            else
                                            {
                                                /* Already the  RX Global MASK register is updated, its used as acceptance mask for all Rx MBs except for 14 and 15 MB's*/
                                            }

#if (CAN_RXFIFO_ENABLE == STD_ON)
                                        }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
                                    }
                                    else
                                    {
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                        /**
                                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                        */
                                        FLEXCAN_RXIMR_CONFIG( can_hw_offset, can_mb_ctrl_index, (uint32)((Can_CurrentConfigPtr->FilterMasksPtr)[((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->IdMaskIndex]) );
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                    }
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                /* Set the IDE bit if the ID type is EXTENDED or MIXED. */
                                can_mb_config = FLEXCAN_MBCS_IDE ;

                                /* For EXTENDED MB type the ID is placed starting from bits 0 ( unlike STANDARD type when is placed starting to bit 18). */
                            }
#endif /* (CAN_EXTENDEDID == STD_ON) */

                            /* Enable the MB as a Rx object. MB is used for Rx & Mark the buffer as empty. */
                            can_mb_config |= FLEXCAN_MBCS_CODERXEMPTY;
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_MB_CS_CONFIG( can_hw_offset, can_mb_ctrl_index, can_mb_config);

                            /* Copy the Message ID (serves as acceptance filter for Rx MBs). */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_MB_ID_CONFIG( can_hw_offset, can_mb_ctrl_index, can_mb_messageid);

                            /* Save the mask bit from IMASK register for this MB used by Can_EnableControllerInterrupts() API. */
                            if ( CAN_CONTROLLERCONFIG_RXPOL_EN != (CAN_CONTROLLERCONFIG_RXPOL_EN & Config->Options) )
                            {
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                                if ( can_mb_ctrl_index >= FLEXCAN_MB_32 )
                                {
                                    Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK2_INDEX] |= ((uint32)1U << (can_mb_ctrl_index - FLEXCAN_MB_32));
                                }
                                else
                                {
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                                    Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX] |= ((uint32)1U << can_mb_ctrl_index);
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                                }
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                            }

                            /* Record for current controller the HTH/HRH assigned foe every MB. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                            */
                            Can_ControllerStatuses[Controller].Can_MBMapping[can_mb_ctrl_index] = ((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->HWObjID;

                            /* Increment current index for the controller on every RxMB configured. */
                            can_mb_ctrl_index++;

                            /* At this point "FirstTxMBIndex" is updated and considering RxFifo if enebaled also. */
                            Can_ControllerStatuses[Controller].FirstTxMBIndex = can_mb_ctrl_index;

                            break;

                        case (TRANSMIT):
                            /* Enable the MB as an TX object. MB is used for Tx & SRR must be set for Tx buffers. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_MB_CS_CONFIG( can_hw_offset, can_mb_ctrl_index, (uint32)(FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_SRR));

                            /* Configure only PRIO field of MBCS register of every Tx MB. */
                            if ( CAN_CONTROLLERCONFIG_LPRIO_EN == (Config->Options & CAN_CONTROLLERCONFIG_LPRIO_EN) )
                            {
                            /**
                            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                            */
                                can_mb_messageid = (uint32)((uint32)(((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->LocalPriority) << FLEXCAN_MB_ID_PRIO_SHIFT) ;
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                */
                                FLEXCAN_MB_ID_CONFIG( can_hw_offset, can_mb_ctrl_index, can_mb_messageid );
                            }

                            if ( CAN_CONTROLLERCONFIG_TXPOL_EN != (CAN_CONTROLLERCONFIG_TXPOL_EN & Config->Options) )
                            {
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                                if ( can_mb_ctrl_index >= FLEXCAN_MB_32 )
                                {
                                    Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK2_INDEX] |= ((uint32)1U << (can_mb_ctrl_index - FLEXCAN_MB_32));
                                }
                                else
                                {
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                                    Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX] |= ((uint32)1U << can_mb_ctrl_index);
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                                }
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                            }

                            /* Record for current controller the HTH/HRH assigned foe every MB. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                            */
                            Can_ControllerStatuses[Controller].Can_MBMapping[can_mb_ctrl_index] = ((can_ptrMBConfigContainer->MessageBufferConfigsPtr) + can_mb_global_index)->HWObjID;

                            /* Increment current index for the controller on every RxMB configured. */
                            can_mb_ctrl_index++;

                            break;

                        default:
                            /* This case should never occurs. */
                            Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_INIT_CONTROLLER, (uint8)CAN_E_DEFAULT);
                            /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                                  Cer_ReportError() function implementation */
                            break;
                    }
                }

                /* Increment the MB index for the controller even is Tx or Rx MB.
                  "can_mb_global_index" should parse all HOH or at least all the MBs for this controller are configured. */
                can_mb_global_index++;
            }

            /* Set the number of MBs configured for this controller (Rx + Tx MBs). */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            @note Violates MISRA 2004 Advisory Rule 10.3 , Cast of complex integer expression to larger type - See @ref FlexCan_LLD_c_REF_6
            */
            FLEXCAN_SET_MCR_MAXMB( can_hw_offset, (can_ptrControlerDescriptor->MaxMBCount - 1U) );
#ifdef E2656_FLEXCAN_XPC56XXX
       #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
            /* Do not set the Abort Enable bit of the MCR */
       #endif
#else
       #if (CAN_TXCANCEL_SUPPORTED == STD_ON)
        /* Abort Enable: Tx Cancelation supported and used for this Controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        FLEXCAN_SET_MCR_AEN ( can_hw_offset);
       #endif /* (CAN_TXCANCEL_SUPPORTED==STD_ON) */
#endif /* E2656_FLEXCAN_XPC56XXX */

            /* Pre-calculated MB INT masks (used in Can_EnableControllerInterrupts) - If events are set for polling mode these bits are not set.
                Clear all INTs flags  .. for MBs (w1c bits). */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64 )
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            /* Check whether Can controller supports 64 message buffers */
            if ( FLEXCAN_MB_64 == Config->Can_NumberOfMB)
            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
                FLEXCAN_IFLAG2_CONFIG( can_hw_offset, FLEXCAN_32BITMASK);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64 ) */

            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_IFLAG1_CONFIG( can_hw_offset, FLEXCAN_32BITMASK);

            /* Clear bits for Tx/Rx/BusOff/Err/WakeUp (w1c bits). */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_ESR_CONFIG( can_hw_offset, (uint32)(FLEXCAN_ESR_BOFFINT | FLEXCAN_ESR_ERRINT | FLEXCAN_ESR_WAK_INT));

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* After controller is (re-)initialized the state is CAN_T_STOP. For this state the Wakeup support must not be enabled.
            Wakeup is used for the transition out of CAN_T_SLEEP state. */
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
            /* If internal WakeUp is supported clear Wakeup status int flag (w1c bit). */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_SET_ESR_WAK_INT( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
            /* Init WKPU module. */
            Can_Init_ExtWkp( can_ptrControlerDescriptor->WakeupChannel);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */

#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* Clear the Error Counters Register. */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_ECR_CONFIG( can_hw_offset, (uint32)0UL);

            /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
                unless the CPU reads the C/S word of another MB.*/
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_TIMER_READ( can_hw_offset);

        } /* (can_reset_return == CAN_OK) */
    }


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_SetControllerMode( VAR(uint8, CAN_VAR) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor,
                                                           VAR(Can_StateTransitionType, CAN_VAR) Transition)
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, CAN_VAR)  Out_can_return = CAN_NOT_OK;
        /* Variable for indexing the MBs. */
        VAR(uint8, CAN_VAR)           can_mb_ctrl_index = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)           can_hw_offset = 0U;
        /* Temporary variable for CTRL register. */
        VAR(uint32, CAN_VAR)          can_ctrl_reg = 0U;
        /* Temporary variable for MB config register. */
        VAR(uint32, CAN_VAR)          can_mb_config = 0U;
#if (CAN_WAKEUP_SUPPORT == STD_ON)
        /* Timeout counter. */
        VAR(uint32, CAN_VAR)          can_timeout_count = 0U;
        VAR(uint32, CAN_VAR)          can_temp_var = 0U;
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


        /* Get the hardware offset for this controller. */
        can_hw_offset = can_ptrControlerDescriptor->ControllerOffset;

        /**
        @brief   (CAN017) The function Can_SetControllerMode shall perform software triggered state transitions of the CAN controller State machine.
        @remarks Covers CAN017
        @remarks Implements DCAN00017
        */
        switch (Transition)
        {
            /* CANIF_CS_STARTED -> CANIF_CS_STOPPED. */
            /**
            @brief   (CAN283) The function Can_SetControllerMode(CAN_T_STOP) shall not call a cancellation notification.
            @remarks Covers CAN283
            @remarks Implements DCAN00283
            */
            case (CAN_T_STOP):
                /**
                @brief   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                @remarks Covers PR-MCAL-3057
                @remarks Implements DCAN03057
                */
                if ( CAN_T_STOP == Can_ControllerStatuses[Controller].ControllerState)
                {
                    /* If the controller is already in STOP state, return CAN_OK. */
                    Out_can_return = CAN_OK;
                }
                else
                {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Stop are only from Start and Wakeup. */
                    if ( CAN_T_START != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                        /**
                        @brief   (CAN263) The function Can_SetControllerMode(CAN_T_STOP) shall set the bits inside the CAN hardware such that the CAN controller
                                   stops participating on the network.
                        @remarks Covers CAN263
                        @remarks Implements DCAN00263
                        */

                        /**
                        @{
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_SET_MCR_FRZ( can_hw_offset);
                        FLEXCAN_SET_MCR_HALT( can_hw_offset);
                        /**@}*/

                        /**
                        @brief   (CAN264) The function Can_SetControllerMode(CAN_T_STOP) shall be non-blocking and shall not wait until the Can controller is
                                   really switched off.
                        @remarks Covers CAN264
                        @remarks Implements DCAN00264
                        */
                        /* This means will not wait until MCR[FRZ_ACK] is set. */

                        /* Check if Software BusOff Recovery is enabled. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                        */
                        if ( CAN_CONTROLLERCONFIG_BUSOFFSWREC == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_BUSOFFSWREC) )
                        {
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                            FLEXCAN_CLEAR_CTRL_BOFFREC( can_hw_offset);
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                            FLEXCAN_SET_CTRL_BOFFREC( can_hw_offset);
                        }

                        /* Loop through all Tx MBs. -> must abort transmission for all MBs for Tx. */
                        for ( can_mb_ctrl_index = Can_ControllerStatuses[Controller].FirstTxMBIndex; can_mb_ctrl_index < can_ptrControlerDescriptor->MaxMBCount; can_mb_ctrl_index++)
                        {
                            /* Cancel the MB (just in case it is scheduled for Tx). This is a HARD ABORT, confirmation of whether the MB was transmitted or not is not required. */
                            /**
                            @brief   (CAN282) The function Can_SetControllerMode(CAN_T_STOP) shall cancel pending messages.
                            @brief   (CAN273)After bus-off detection, the Can module shall cancel still pending messages without raising a cancellation notification.
                            @remarks Covers CAN282, CAN273
                            @remarks Implements DCAN00282, DCAN00273
                            */
                            can_mb_config = ( ((uint32)FLEXCAN_MB_READ( can_hw_offset, can_mb_ctrl_index) & ~FLEXCAN_MBCS_CODE) | FLEXCAN_MBCS_CODETX );
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_MB_CS_CONFIG( can_hw_offset, can_mb_ctrl_index, can_mb_config);
                        }

                        /*
                        The Can module shall track all individual enabling and disabling of  interrupts
                            in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
                        When Freeze mode (or Autosar equiv Stop mode) need to not participate on network ->
                            no interrupt is required to be enabled.
                        */
                        Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~(SWF_BOFF_MASK | SWF_ERR_MASK | SWF_MB_MASK | SWF_WRNINT_MASK));
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~SWF_WAK_MASK);
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/

                        /* Check if Ints are enabled by Can_EnableControllerInterrupts. */
                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                        {
                            /**
                            @brief   (CAN197) The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state.
                                        Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                            @remarks Covers CAN197
                            @remarks Implements DCAN00197
                            */
                            /**
                                @{
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_CLEAR_CTRL_BOFFMSK( can_hw_offset);
                            FLEXCAN_CLEAR_CTRL_ERRMSK( can_hw_offset);
                            /**
                            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                            */
                            if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                            {
                                FLEXCAN_CLEAR_CTRL_TWRNMSK( can_hw_offset);
                                FLEXCAN_CLEAR_CTRL_RWRNMSK( can_hw_offset);
                            }
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                            /* Check whether Can controller supports 64 message buffers */
                            if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB )
                            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                                FLEXCAN_IMASK2_CONFIG( can_hw_offset, (uint32)0U);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                            FLEXCAN_IMASK1_CONFIG( can_hw_offset, (uint32)0U);

#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                            /* No need for Wakeup support in Stop mode (only for Sleep). */
                            FLEXCAN_CLEAR_MCR_WAK_MSK(can_hw_offset);
                            /**@}*/
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                            /* Setup WKPU module: Wkp channel, Int disable, Wkp disable. */
                            Can_EnDis_ExtWkp(can_ptrControlerDescriptor->WakeupChannel, (uint8)0x0U, (uint8)0x0U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/
                        }

#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                        /* For internal wakeup the ESR[WAK_INT] bit is always activated  - it's a status bit that is masked by MCR[WAK_MSK].
                           This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */
                        FLEXCAN_CLEAR_MCR_SLF_WAK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/

                        /* Set the Stop state to the controller. */
                        Can_ControllerStatuses[Controller].ControllerState = CAN_T_STOP;
                        Out_can_return = CAN_OK;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                }
                break;

            /* CANIF_CS_STOPPED -> CANIF_CS_STARTED. */
            case (CAN_T_START):
                /**
                @brief   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                @remarks Covers PR-MCAL-3057
                @remarks Implements DCAN03057
                */
                if ( CAN_T_START == Can_ControllerStatuses[Controller].ControllerState)
                {
                    /* If the controller is already in START state, return CAN_OK. */
                    Out_can_return = CAN_OK;
                }
                else
                {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Start mode are only from Stop state. */
                    if ( CAN_T_STOP != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                        /**
                        @brief (CAN261) The function Can_SetControllerMode(CAN_T_START) shall set the hardware registers in a way that makes the CAN controller participating on the network.
                        @remarks Covers CAN261
                        @remarks Implements DCAN00261
                        */
                        /**
                        @{
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_CLEAR_MCR_FRZ( can_hw_offset);
                        FLEXCAN_CLEAR_MCR_HALT( can_hw_offset);
                        /**@}*/

                        /**
                        @brief   (CAN262) The function Can_SetControllerMode(CAN_T_START) shall be non-blocking and shall not wait until the CAN controller is fully operational.
                        @remarks Covers CAN262
                        @remarks Implements DCAN00262
                        */

                        /* Driver will not wait until MCR[FRZ_ACK] is cleared, meaning that Can controller is out of Freeze mode (or Autosar equiv Stop mode). */

                        /**
                        @brief The function Can_SetControllerMode shall enable interrupts that are needed in the new state.
                            Enabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                        @remarks Covers CAN196
                        @remarks Implements DCAN00196
                         */
                        /*
                        The Can module shall track all individual enabling and disabling of interrupts in
                            other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
                        */
                        Can_ControllerStatuses[Controller].ControllerSWFlag |= (uint8)(SWF_BOFF_MASK | SWF_ERR_MASK | SWF_MB_MASK);
                        /**
                        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                        */
                        if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                        {
                            Can_ControllerStatuses[Controller].ControllerSWFlag |= (uint8)(SWF_WRNINT_MASK);
                        }
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        /* Wakeup interrupt is not required in Start mode. */
                        Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~SWF_WAK_MASK);

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                        /* Setup WKPU module: Wkp channel, Int disable, Wkp disable. */
                        Can_EnDis_ExtWkp(can_ptrControlerDescriptor->WakeupChannel, (uint8)0x0U, (uint8)0x0U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                        /* This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_CLEAR_MCR_SLF_WAK(can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                        {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                            /* No need for Wakeup support in Run mode. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_CLEAR_MCR_WAK_MSK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

                            can_ctrl_reg = ( (uint32)FLEXCAN_CTRL_READ(can_hw_offset) | (FLEXCAN_CTRL_BOFFMSK | FLEXCAN_CTRL_ERRMSK) );

                            if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                            {
                                can_ctrl_reg |= FLEXCAN_CTRL_TWRNMSK | FLEXCAN_CTRL_RWRNMSK;
                            }
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_CTRL_CONFIG( can_hw_offset, can_ctrl_reg);

#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                            /* Check whether Can controller supports 64 message buffers */
                            if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                */
                                FLEXCAN_IMASK2_CONFIG( can_hw_offset, Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK2_INDEX]);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_IMASK1_CONFIG( can_hw_offset, Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX]);
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

                        /* Set the Stop State. */
                        Can_ControllerStatuses[Controller].ControllerState = CAN_T_START;
                        Out_can_return = CAN_OK;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                }
                break;

            /* CANIF_CS_STOPPED -> CANIF_CS_SLEEP. */
            case (CAN_T_SLEEP):

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                /**
                @brief   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                @remarks Covers PR-MCAL-3057
                @remarks Implements DCAN03057
                */
                if ( CAN_T_SLEEP == Can_ControllerStatuses[Controller].ControllerState )
                {
                    /* If the controller is already in SLEEP state, return CAN_OK. */
                    Out_can_return = CAN_OK;
                }
                else
                {
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Sleep state are only from Stop state. */
                    if ( CAN_T_STOP != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                        /**
                        @brief   (CAN290)If the CAN HW does not support a sleep mode, the function Can_SetControllerMode(CAN_T_SLEEP) shall have no
                                   effect (as the controller is already in stopped state).
                        @remarks Covers CAN290
                        @remarks Implements DCAN00290
                        */
                        /* If Wakeup is not supported no operation is done. */
                        if ( CAN_CONTROLLERCONFIG_WKPOL_EN != (CAN_CONTROLLERCONFIG_WKPOL_EN & (Can_ControllerConfigPtr + Controller)->Options))
                        {
                            /**
                            @brief   (CAN294) The function Can_SetControllerMode shall disable the wake-up interrupt, while checking the wake-up status.
                            @remarks Covers CAN294
                            @remarks Implements DCAN00294
                            */
                            /* First of all, disable WakeUp interrupt. */
                            Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~SWF_WAK_MASK);

                            if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                            {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                                /**
                                @{
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                */
                                FLEXCAN_CLEAR_MCR_WAK_MSK( can_hw_offset);
                                FLEXCAN_CLEAR_MCR_SLF_WAK( can_hw_offset);
                                /**@}*/
  #endif /* ((CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                                /* Setup WKPU module: Wkp channel, Int disable, Wkp  disable */
                                Can_EnDis_ExtWkp( can_ptrControlerDescriptor->WakeupChannel, (uint8)0x0U, (uint8)0x0U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
                            }

                            /**
                            @brief   (CAN048) In case of a CAN bus wake-up during sleep transition, the function Can_SetControllerMode(CAN_T_WAKEUP) shall return CAN_NOT_OK.
                            @remarks Covers CAN048
                            @remarks Implements DCAN00048
                            */
                            /* Init this value with CAN_OK = 0x00. */
                            Out_can_return = CAN_OK;
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                            /* Check for Wakeup flag status. */
                            if ( FLEXCAN_ESR_WAK_INT == (FLEXCAN_ESR_WAK_INT & FLEXCAN_ESR_READ(can_hw_offset)) )
                            {
                                /* Wakeup interrupt occurred, return with error. */
                                Out_can_return = CAN_NOT_OK;
                            }
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                            /**
                                @brief   (CAN048) In case of a CAN bus wake-up during sleep transition, the function Can_SetControllerMode(CAN_T_WAKEUP) shall return CAN_NOT_OK.
                                @remarks Covers CAN048
                                @remarks Implements DCAN0048
                                */
                            /* Can_GetStatus_ExtWkp returns E_OK (0x00) if wakeup is detected or E_NOT_OK (0x01) if no wakleup event detected. */
                            if ( (uint8)E_OK == Can_GetStatus_ExtWkp( can_ptrControlerDescriptor->WakeupChannel))
                            {
                                /* Wakeup interrupt occurred, return with error. */
                                Out_can_return = CAN_NOT_OK;
                            }
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */

                            /**
                            @brief   (CAN257) When the CAN hardware supports sleep mode, when transitioning into mode CANIF_CS_SLEEP, the Can module shall set the controller to a state from which the hardware can be woken over CAN Bus.
                            @brief   (CAN197) The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state.
                                    Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                            @remarks Covers CAN257, CAN197
                            @remarks Implements DCAN00257,  DCAN00197
                            */
                            if ( CAN_OK == Out_can_return )
                            {
                                /* Enable interrupts that are needed in this state. */
                                Can_ControllerStatuses[Controller].ControllerSWFlag |= (uint8)SWF_WAK_MASK;

                                /* Disable interrupts that are not needed in this state. */
                                Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~(SWF_BOFF_MASK | SWF_ERR_MASK | SWF_WRNINT_MASK | SWF_MB_MASK));

                                if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                                {
#if (CAN_WKP_INT_SUPPORT == STD_ON)
                                    /* Enable the Wakeup interrupt generation. */
                                    /**
                                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                    */
                                    FLEXCAN_SET_MCR_WAK_MSK( can_hw_offset);

                                    /**
                                    @{
                                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                    */
                                    FLEXCAN_CLEAR_CTRL_BOFFMSK( can_hw_offset);
                                    FLEXCAN_CLEAR_CTRL_ERRMSK( can_hw_offset);
                                    if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                                    {
                                        FLEXCAN_CLEAR_CTRL_TWRNMSK( can_hw_offset);
                                        FLEXCAN_CLEAR_CTRL_RWRNMSK( can_hw_offset);
                                    }
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                                    /* Check whether Can controller supports 64 message buffers */
                                    if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                                    {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                                        FLEXCAN_IMASK2_CONFIG( can_hw_offset, (uint32)0U);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                                    }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                                    FLEXCAN_IMASK1_CONFIG( can_hw_offset, (uint32)0U);
                                    /**@}*/
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                                    /* Setup WKPU module: Wkp channel, Int enable, Wkp enable. */
                                    Can_EnDis_ExtWkp( can_ptrControlerDescriptor->WakeupChannel, (uint8)0x1U, (uint8)0x1U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
                                }
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                                /* This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode.
                                   If a transition from recessive to dominant is detected during Stop Mode, then FlexCAN generates, if enabled to do so, a Wake Up interrupt to the CPU so that it can resume the clocks globally. */
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                */
                                FLEXCAN_SET_MCR_SLF_WAK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */


                                Can_ControllerStatuses[Controller].ControllerState = CAN_T_SLEEP;

                                /* The hardware settings only differ from CANIF_CS_STOPPED for CAN hardware that support a sleep mode (wake-up over CAN bus directly supported by CAN hardware).  */
                                /**
                                @brief   (CAN265)The function Can_SetControllerMode(CAN_T_SLEEP) shall put the controller into sleep mode.
                                @remarks Covers CAN265
                                @remarks Implements DCAN00265
                                */
                                Out_can_return = CAN_OK;
                            }
                        }
                        else
                        /* POLLING mode */
                        {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                            /* For internal wakeup the ESR[WAK_INT] bit is always activated  - it's a status bit that is masked by MCR[WAK_MSK].
                               This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_SET_MCR_SLF_WAK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                            /* Setup WKPU module: Wkp channel, Int disable, Wkp event enable. */
                            Can_EnDis_ExtWkp( can_ptrControlerDescriptor->WakeupChannel, (uint8)0x0U, (uint8)0x1U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON)  */
                            Can_ControllerStatuses[Controller].ControllerState = CAN_T_SLEEP;
                            Out_can_return = CAN_OK;
                        }
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */


                    /**
                    @brief   (CAN266) If the CAN HW does support a sleep mode, the function Can_SetControllerMode(CAN_T_SLEEP) shall be blocking and
                               shall only return when it is assured that the CAN hardware is wakeable.
                    @remarks Covers CAN266
                    @remarks Implements DCAN00266
                    */
                    /* Now must assure that when return from this function Can controller is wakeable. For all state changes except the
                            change to state CANIF_CS_SLEEP, the function does not wait until the state change has really performed. */
                    can_timeout_count = (uint32)CAN_TIMEOUT_DURATION;
                    can_temp_var = (uint32)0U;
                    do {
                        /* ... stay in loop */
                       can_timeout_count--;

                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                        {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            can_temp_var |= ( (uint32)FLEXCAN_MCR_READ( can_hw_offset) & FLEXCAN_MCR_WAK_MSK );
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                            can_temp_var |= (uint32)Can_GetIRER_Status();
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
                        }
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                        /* Self Wakeup must be set. */
                        can_temp_var |= ( (uint32)FLEXCAN_MCR_READ( can_hw_offset) & FLEXCAN_MCR_SLF_WAK );
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
                    } while ((can_timeout_count > (uint32)0x0U) && ( (uint32)0x0U == can_temp_var));

                    if ( (uint32)0x0U == can_timeout_count )
                    {
                        /**
                        @brief     (CAN093)The function of the Can module which provides a return value and which raised a production error shall return with CAN_NOT_OK.
                        @remarks   Covers CAN093
                        @remarks   Implements DCAN00093
                        */
                        Out_can_return = CAN_NOT_OK;

                        /* Report production error. */
                        Dem_ReportErrorStatus( (Dem_EventIdType)CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                    }
                }
#else /* (CAN_WAKEUP_SUPPORT == STD_OFF) */
                /* When Wakeup is not supported the driver should do nothing and return CAN_OK. */
                Out_can_return = CAN_OK;
#endif /* (CAN_WAKEUP_SUPPORT == STD_OFF) */
                break;

            /* CANIF_CS_SLEEP -> CANIF_CS_STOPPED */
            case (CAN_T_WAKEUP):

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                /**
                @brief   (CAN268) The function Can_SetControllerMode(CAN_T_WAKEUP) shall be non-blocking.
                @brief   (CAN270)On hardware wakeup (triggered by a wake-up event from CAN bus), the Can module shall transition into the state CAN_IF_CS_STOPPED.
                @remarks Covers CAN268, CAN270
                @remarks Implements DCAN00268, DCAN00270
                    */
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                /* Valid transitions to Wakeup state are ony from Sleep state. */
                if (CAN_T_SLEEP != Can_ControllerStatuses[Controller].ControllerState)
                {
                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                }
                else
                {
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                    /**
                    @brief   (CAN294) The function Can_SetControllerMode shall disable the wake-up interrupt, while checking the wake-up status.
                    @remarks Covers CAN294
                    @remarks Implements DCAN00294
                    */

                    /* The Can module shall track all individual enabling and disabling of  interrupts in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored. */
                    Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~SWF_WAK_MASK);

                    Can_ControllerStatuses[Controller].ControllerSWFlag &= (uint8)(~(SWF_BOFF_MASK | SWF_ERR_MASK | SWF_WRNINT_MASK | SWF_MB_MASK));

                    if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].InterruptMode )
                    {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                        /* Disable WakeUp Interrupt. */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_CLEAR_MCR_WAK_MSK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                        /* Setup WKPU module: Wkp channel, Int enable, Wkp enable. */
                        Can_EnDis_ExtWkp(can_ptrControlerDescriptor->WakeupChannel, (uint8)0x0U, (uint8)0x0U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */

                        /**
                        @{
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_CLEAR_CTRL_BOFFMSK( can_hw_offset);
                        FLEXCAN_CLEAR_CTRL_ERRMSK( can_hw_offset);
                        if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                        {
                            FLEXCAN_CLEAR_CTRL_TWRNMSK( can_hw_offset);
                            FLEXCAN_CLEAR_CTRL_RWRNMSK( can_hw_offset);
                        }
  #if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers */
                        if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                        {
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            FLEXCAN_IMASK2_CONFIG( can_hw_offset, (uint32)0U);
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
  #endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                        FLEXCAN_IMASK1_CONFIG( can_hw_offset, (uint32)0U);
                        /**@}*/
                    }

  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                    FLEXCAN_CLEAR_MCR_SLF_WAK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

                    /* Set the Stop state. */
                    Can_ControllerStatuses[Controller].ControllerState = CAN_T_STOP;

                    /* Report "transition initiated". */
                    Out_can_return = CAN_OK;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                }
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

#else /* (CAN_WAKEUP_SUPPORT == STD_OFF) */

                /* When Wakeup is not supported the driver should do nothing and return CAN_OK. */
                Out_can_return = CAN_OK;

#endif /* (CAN_WAKEUP_SUPPORT == STD_OFF) */
                break;

            /* Unknown transition requested. */
            default:
                /**
                @brief   (CAN200) If development error detection for the Can module is enabled: if an invalid transition has been requested, the function Can_SetControllerMode shall raise the error CAN_E_TRANSITION and return CAN_NOT_OK.
                @remarks Covers CAN200
                @remarks Implements DCAN00200
                */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                break;

        } /* end switch */

        return (Out_can_return);
    }


/*================================================================================================*/
/**
@brief         Service disables all interrupts for the given CAN controller.
@details       This routine is called by:
                - Can_DisableControllerInterrupts() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           Disable interrupts must be called prior to enable interrupts.
@post          Clear all flags/bits that are needded for disabling the interrupts.
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_DisableControllerInterrupts( VAR(uint8, CAN_VAR) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor)
    {

        /* Timeout counter. */
        VAR(uint32, CAN_VAR)  can_timeout_count = CAN_TIMEOUT_DURATION;
        /* Temp variable to get the interrupt masks. */
        VAR(uint32, CAN_VAR)  can_temp_var = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)   can_hw_offset = 0U;


        SchM_Enter_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_00);
        /**
        @brief   (CAN202) When Can_DisableControllerInterrupts has been called several times, Can_EnableControllerInterrupts must be called
                    as many times before the interrupts are re-enabled.
        @remarks Covers CAN202
        @remarks Implements DCAN00202
        */
        Can_ControllerStatuses[Controller].IntDisableLevel++;
        SchM_Exit_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_00);

        /* If nesting level is zero or below zero; <0 needed for reentrancy. */
        /**
        @brief   (CAN049) The function Can_DisableControllerInterrupts shall disable all interrupts for this CAN controller only at the first call of this function.
        @remarks Covers CAN049
        @remarks Implements DCAN00049
        */
        if ( (sint8)1 == Can_ControllerStatuses[Controller].IntDisableLevel )
        {
            /* Switch to disabled mode. */
            Can_ControllerStatuses[Controller].InterruptMode = (uint8)CAN_INTERRUPT_DISABLED;

            /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
            can_hw_offset = can_ptrControlerDescriptor->ControllerOffset;

            /**
            @brief   (CAN033) The Can module shall implement the interrupt service routines for all CAN Hardware Unit interrupts that are needed.
                        The Can module shall disable all unused interrupts in the CAN controller.
                        The Can module shall reset the interrupt flag at the end of the ISR (if not done automatically by hardware).
                        The Can module shall not set the configuration (i.e. priority) of the vector table entry.
            @remarks Covers CAN033
            @remarks Implements DCAN00033
            */
            /* Can_DisableControllerInterrupts and Can_EnableControllerInterrupts should not modify the software flags. */
            /* Disable MB Rx/Tx interrupts. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            /* Check whether Can controller supports 64 message buffers */
            if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_IMASK2_CONFIG( can_hw_offset, (uint32)0x0UL);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_IMASK1_CONFIG( can_hw_offset, (uint32)0x0UL);

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* Disable Wakeup interrupts. */
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_CLEAR_MCR_WAK_MSK( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
            /* Setup WKPU module: Wkp channel, Int enable, Wkp enable. */
            Can_EnDis_ExtWkp( can_ptrControlerDescriptor->WakeupChannel, (uint8)0U, (uint8)0U);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* Disable BusOff, Error, TxW, RxW interrupts. */
            /**
            @{
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
            */
            FLEXCAN_CLEAR_CTRL_BOFFMSK( can_hw_offset);
            FLEXCAN_CLEAR_CTRL_ERRMSK( can_hw_offset);
            /**@}*/
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
            */
            if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
            {
                /**
                @{
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_CLEAR_CTRL_TWRNMSK( can_hw_offset);
                FLEXCAN_CLEAR_CTRL_RWRNMSK( can_hw_offset);
                /**@}*/
            }

            /**
            @brief   (CAN292) The function Can_DisableControllerInterrupts shall raise the production error CAN_E_TIMEOUT if the disabling of
                       the interrupts could not be performed (indicates defective hardware).
            @remarks Covers CAN292
            @remarks Implements DCAN00292
            */
            do {
                /* ... stay in loop. */
                can_timeout_count--;

                /* Get the interrupt masks from registers. */
#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                can_temp_var |= ( (uint32)FLEXCAN_MCR_READ( can_hw_offset) & FLEXCAN_MCR_WAK_MSK );
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                can_temp_var |= (Can_GetIRER_Status() & ((uint32)0x01U << (uint32)can_ptrControlerDescriptor->WakeupChannel));
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
                can_temp_var |= ( (uint32)FLEXCAN_CTRL_READ( can_hw_offset) & (uint32)(FLEXCAN_CTRL_BOFFMSK | FLEXCAN_CTRL_ERRMSK) );
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
            */
                if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
                {
                    can_temp_var |= ( (uint32)FLEXCAN_CTRL_READ( can_hw_offset) & (uint32)(FLEXCAN_CTRL_TWRNMSK | FLEXCAN_CTRL_RWRNMSK) );
                }
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                /* Check whether Can controller supports 64 message buffers */
                if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                    can_temp_var |= (uint32)FLEXCAN_IMASK2_READ( can_hw_offset);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                can_temp_var |= (uint32)FLEXCAN_IMASK1_READ( can_hw_offset);

            } while ( (can_timeout_count > (uint32)0U) && ((uint32)0x0UL != can_temp_var));


            if ( (uint32)0x0U == can_timeout_count )
            {
                /* Report production error. */
                Dem_ReportErrorStatus( (Dem_EventIdType)CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
            }
        }
    }


/*================================================================================================*/
/**
@brief         Service enables all interrupts that shall be enabled according the current software status.
@details       This routine is called by:
                - Can_EnableControllerInterrupts() from Can.c file.

@param[in]     Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
@param[in]     can_ptrControlerDescriptor Pointer to controller descriptor configuration

@pre           Can be executed only if disable interrupts was called before.
@post          Enable all interrupts that must be enabled according the current sw status.
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_EnableControllerInterrupts( VAR(uint8, CAN_VAR) Controller,
                                                          P2CONST(Can_ControlerDescriptorType, CAN_VAR, CAN_APPL_CONST) can_ptrControlerDescriptor )
    {

        /* Timeout counter. */
        VAR(uint32, CAN_VAR)  can_timeout_count = CAN_TIMEOUT_DURATION;
        /* Temp variable to get the interrupt masks. */
        VAR(uint32, CAN_VAR)  can_temp_var = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)   can_hw_offset = 0U;
        /* Variable that tells if disable ints was called at least once before. */
        VAR(uint8, CAN_VAR)   can_dis_called_before = 0U;
        /* Variable that tells if at least one interrupt is enabled according to software flags - used only for Timeout checking. */
        VAR(uint8, CAN_VAR)   can_int_set = 0U;


        /**
        @brief   (CAN202) When Can_DisableControllerInterrupts has been called several times, Can_EnableControllerInterrupts must be called as many
                   times before the interrupts are re-enabled.
        @remarks Covers CAN202
        @remarks Implements DCAN00202
        */
        if ( Can_ControllerStatuses[Controller].IntDisableLevel > (sint8)0 )
        {
            /* When IntDisableLevel is greater than 0  means Can_DisableControllerInterrupts was called at least once before this call of current function. */
            SchM_Enter_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_01);
            /* Decrement the nesting level. */
            Can_ControllerStatuses[Controller].IntDisableLevel--;
            SchM_Exit_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_01);

            can_dis_called_before = (uint8)0x1U;
        }

        /* Can_DisableControllerInterrupts and Can_EnableControllerInterrupts do not modify the software flags. */

        /**
        @brief   (CAN208) The function Can_EnableControllerInterrupts shall perform no action when Can_DisableControllerInterrupts has not been called before.
        @remarks Covers CAN208
        @remarks Implements DCAN00208
        */
        if ( ((sint8)0 == Can_ControllerStatuses[Controller].IntDisableLevel) && ((uint8)0x1U == can_dis_called_before) )
        {
            /* Switch to enabled mode. */
            Can_ControllerStatuses[Controller].InterruptMode = (uint8)CAN_INTERRUPT_ENABLED;

            /**
            @brief   (CAN050) The function Can_EnableControllerInterrupts shall enable all interrupts that must be enabled according the current software status.
            @remarks Covers CAN050
            @remarks Implements DCAN0050
            */
            /* Get the hardware offset for this controller. */
            can_hw_offset = can_ptrControlerDescriptor->ControllerOffset;
            /**
               @{
               @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
            */

            if ( (CAN_CONTROLLERCONFIG_TXPOL_EN != (CAN_CONTROLLERCONFIG_TXPOL_EN & (Can_ControllerConfigPtr + Controller)->Options)) ||
                 (CAN_CONTROLLERCONFIG_RXPOL_EN != (CAN_CONTROLLERCONFIG_RXPOL_EN & (Can_ControllerConfigPtr + Controller)->Options)) )
             /**@}*/
            {
                if ( (uint8)SWF_MB_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & (uint8)SWF_MB_MASK) )
                {
                    /* Enable INTs from MBs. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    /* Check whether Can controller supports 64 message buffers */
                    if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                    {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        FLEXCAN_IMASK2_CONFIG( can_hw_offset, Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK2_INDEX]);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                    /* Set here the interrupts for RX FIFO is FEN bit is set, but will clear the bits if functionality of Overflow or Warning is not enabled (below). */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    FLEXCAN_IMASK1_CONFIG( can_hw_offset, Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX]);

                    /* Mark flag that tells if at least one INT is enabled. */
                    can_int_set |= (uint8)1U;
                }
            }

            /**
            @brief   (CAN204) The Can module shall track all individual enabling and disabling of interrupts in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
            @remarks Covers CAN204
            @remarks Implements DCAN00204
            */
#if (CAN_WAKEUP_SUPPORT == STD_ON)
            if ( CAN_CONTROLLERCONFIG_WKPOL_EN != (CAN_CONTROLLERCONFIG_WKPOL_EN & (Can_ControllerConfigPtr + Controller)->Options) )
            {
                /* Check the software flag - if set then interrupt must be enabled. */
                if ( SWF_WAK_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_WAK_MASK) )
                {
                    /* WakeUp - enable the interrupt. */
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    FLEXCAN_SET_MCR_WAK_MSK( can_hw_offset);
                    /* Mark flag that tells if at least one INT is enabled. */
                    can_int_set |= (uint8)1U;
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                    Can_EnDis_ExtWkp( can_ptrControlerDescriptor->WakeupChannel, (uint8)0x1U, (uint8)0x1U);
                    /* Mark flag that tells if at least one INT is enabled. */
                    can_int_set |= (uint8)1U;
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
                }
            }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                    */
            if ( CAN_CONTROLLERCONFIG_BOPOL_EN != (CAN_CONTROLLERCONFIG_BOPOL_EN & (Can_ControllerConfigPtr + Controller)->Options))
            {
                /* Check the software flag - if set then interrupt must be enabled. */
                if ( SWF_BOFF_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_BOFF_MASK) )
                {
                    /* BusOff - enable the interrupt. */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    FLEXCAN_SET_CTRL_BOFFMSK( can_hw_offset);
                    /* Mark flag that tells if at least one INT is enabled. */
                    can_int_set |= (uint8)1U;
                }
            }

            /* Check the software flag - if set then interrupt must be enabled. */
            if ( SWF_ERR_MASK == (SWF_ERR_MASK & Can_ControllerStatuses[Controller].ControllerSWFlag))
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                FLEXCAN_SET_CTRL_ERRMSK( can_hw_offset);
                /* Mark flag that tells if at least one INT is enabled. */
                can_int_set |= (uint8)1U;
            }

            /* Check the software flag - if set then warning interrupts are enabled. */
               /**
               @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
               */
            if ( CAN_CONTROLLERCONFIG_WRNINT_EN == ((Can_ControllerConfigPtr + Controller)->Options & CAN_CONTROLLERCONFIG_WRNINT_EN) )
            {
                if ( SWF_WRNINT_MASK == (SWF_WRNINT_MASK & Can_ControllerStatuses[Controller].ControllerSWFlag) )
                {
                    FLEXCAN_SET_CTRL_TWRNMSK( can_hw_offset);
                    FLEXCAN_SET_CTRL_RWRNMSK( can_hw_offset);
                    /* Mark flag that tells if at least one INT is enabled. */
                    can_int_set |= (uint8)1U;
                }
            }

            /**
            @brief   (CAN293) The function Can_EnableControllerInterrupts shall raise the production error CAN_E_TIMEOUT
                     if the enabling of the interrupts could not be performed (indicates defective hardware).
            @remarks Covers CAN293
            @remarks Implements DCAN00293
            */
            do {
                /* ... stay in loop */
                can_timeout_count--;
                /* Get the interrupt masks from registers only for the ones that had been enabled. */

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                if ( SWF_WAK_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_WAK_MASK) )
                {
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
                    /* Check if Internal Wakeup interrupt was correctly set. */
                    can_temp_var |= (FLEXCAN_MCR_READ( can_hw_offset) & FLEXCAN_MCR_WAK_MSK);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
                    /* Check if External Wakeup interrupt was correctly set. */
                    can_temp_var |= (Can_GetIRER_Status() & ((uint8)0x01U << can_ptrControlerDescriptor->WakeupChannel));
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */
                }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

                if ( SWF_BOFF_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_BOFF_MASK) )
                {
                    can_temp_var |= (uint32)(FLEXCAN_CTRL_READ(can_hw_offset) & FLEXCAN_CTRL_BOFFMSK);
                }
                if ( SWF_ERR_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_ERR_MASK) )
                {
                    can_temp_var |= (uint32)(FLEXCAN_CTRL_READ(can_hw_offset) & FLEXCAN_CTRL_ERRMSK);
                }
                if ( SWF_WRNINT_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_WRNINT_MASK) )
                {
                    can_temp_var |= (uint32)(FLEXCAN_CTRL_READ(can_hw_offset) & (FLEXCAN_CTRL_TWRNMSK | FLEXCAN_CTRL_RWRNMSK));
                }
                if ( SWF_MB_MASK == (Can_ControllerStatuses[Controller].ControllerSWFlag & SWF_MB_MASK))
                {
                        /**
                        @{
                         @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                         */
                    if ( ( CAN_CONTROLLERCONFIG_TXPOL_EN != (CAN_CONTROLLERCONFIG_TXPOL_EN & (Can_ControllerConfigPtr + Controller)->Options)) ||
                         ( CAN_CONTROLLERCONFIG_RXPOL_EN != (CAN_CONTROLLERCONFIG_RXPOL_EN & (Can_ControllerConfigPtr + Controller)->Options)) )
                         /**@}*/
                    {
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers. */
                        if (FLEXCAN_MB_64 == (Can_ControllerConfigPtr + Controller)->Can_NumberOfMB)
                        {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            can_temp_var |= (FLEXCAN_IMASK2_READ(can_hw_offset) & Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK2_INDEX]);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        can_temp_var |= (FLEXCAN_IMASK1_READ(can_hw_offset) & Can_ControllerStatuses[Controller].MBInterruptMask[FLEXCAN_IMASK1_INDEX]);
                    }
                }
            }
            while ( (can_timeout_count > (uint32)0U) && ((uint32)0x0UL == can_temp_var) && ((uint8)0x1U == can_int_set) );

            if ( (uint32)0U == can_timeout_count )
            {
                /* Report production error. */
                Dem_ReportErrorStatus( (Dem_EventIdType)CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
            }
        }
    }


/*================================================================================================*/
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
/*================================================================================================*/
#if (CAN_TXCANCEL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_Cancel( VAR(uint8, CAN_VAR) controller,
                                      VAR(uint8, CAN_VAR) mbindex)
    {

        /* Variable for storing the content of the MB. */
        VAR(Can_PduType, CAN_VAR) can_Pdu;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)    can_hw_offset = 0U;
        /* Some temporary variables for registers read/write.  */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        VAR(uint8, CAN_VAR)    can_iflag_reg_index = 0U;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
        /* Temporary variable for mbindex calculation. */
        VAR(uint32, CAN_VAR)   can_temp_flag = 0U;
        /* Index of the IFLAG register for current MB. */
        VAR(uint32, CAN_VAR)   can_iflag_reg = 0U;
        /* Variable for storing the data. */
        VAR(uint8, CAN_VAR)    can_mb_data[8];
        /* Configuration register for current MB. */
        VAR(uint32, CAN_VAR)   can_mb_config = 0U;
        /* Index for data byte of MB. */
        VAR(uint8, CAN_VAR)    can_databyte_index = 0U;


        /* Tell the interrupt routine that cancellation of this MB is in progress. */
        Can_ControllerStatuses[controller].CancelMBIndex = (Can_HWObjectCountType)mbindex;

        /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        /* Check if the MB is still full. */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
        */
        if ( (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, mbindex) == (uint32)(FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXEN) )
        {
            #ifdef E2656_FLEXCAN_XPC56XXX
                #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                    /* MB still full -> deactivate it. */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    can_mb_config = ( FLEXCAN_MB_READ( can_hw_offset, mbindex) & (uint32)(~FLEXCAN_MBCS_CODE)) | FLEXCAN_MBCS_CODETX;
               #endif
            #else
                    /* MB still full -> cancel it. */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    can_mb_config = ( FLEXCAN_MB_READ( can_hw_offset, mbindex) & (uint32)(~FLEXCAN_MBCS_CODE)) | FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXABORT;
            #endif /* E2656_FLEXCAN_XPC56XXX */
            FLEXCAN_MB_CS_CONFIG(can_hw_offset, mbindex, can_mb_config);

            /* Did the interrupt routine execute between the check and the abort command? i.e. did we possibly just try to cancel an empty MB? */
            if ( Can_ControllerStatuses[controller].CancelMBIndex == (Can_HWObjectCountType)mbindex)
            {
                /* INT routine did not execute and nobody else would clear the INT flag. We can continue checking the MB for cancellation.
                            Check whether the message has been cancelled. */
            #ifdef E2656_FLEXCAN_XPC56XXX
                #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                if ( (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, mbindex) == (uint32)(FLEXCAN_MBCS_CODETX) )
                #endif
            #else
                if ( (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, mbindex) == (uint32)(FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXABORT) )
            #endif /* E2656_FLEXCAN_XPC56XXX */
                {
                    /* Message has been sucessfully aborted -> test the interrupt flag, is it set? */

                    /* Some temporary registers value. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    /* Check whether Can controller supports 64 message buffers */
                    if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                    {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                        /* Calculate the index of the IFLAG register and Txguard (index=0 for MB32...MB63, index=1 for MB0...MB31). */
                        can_iflag_reg_index = (uint8)((uint8)mbindex >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x01U;
                        can_iflag_reg = (((uint32)0x0U == (uint32)can_iflag_reg_index) ? (uint32)FLEXCAN_IFLAG2_READ(can_hw_offset) : (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset));
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    }
                    else
                    {
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        can_iflag_reg = FLEXCAN_IFLAG1_READ(can_hw_offset);
                    }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                    */
                    can_iflag_reg = FLEXCAN_IFLAG1_READ(can_hw_offset);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                    /* Calculate the flag value. */
                    can_temp_flag = ((uint32)0x01U) << ((uint32)mbindex & FLEXCAN_MASK_32BITS);

                    if ( (uint32)0x0UL == (can_iflag_reg & can_temp_flag) )
                    {
                        /* The INT flag = 0: the INT routine either already executed or will never execute for this cancellation. Is the message still marked as cancelled? */
                    #ifdef E2656_FLEXCAN_XPC56XXX
                        #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                        if ( (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, mbindex) == (uint32)(FLEXCAN_MBCS_CODETX ) )
                        #endif
                    #else
                        if ( (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, mbindex) == (uint32)(FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXABORT) )
                    #endif /* E2656_FLEXCAN_XPC56XXX */
                        {

                            /* Variable for storing the Control and Status register of the MB. */
                            can_mb_config = (uint32)FLEXCAN_MB_READ( can_hw_offset, mbindex);

                            /* Transfer the DLC. */
                            can_Pdu.length = (uint8) ((can_mb_config & FLEXCAN_MBCS_LENGTH) >> FLEXCAN_MBCS_LENGTH_SHIFT);

                            /* Get the ID of the message.
                                If the ID is EXTENTED type then it will be marked with the most significant bit set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            can_Pdu.id = ((uint32)0x0UL == (can_mb_config & FLEXCAN_MBCS_IDE)) ? /* condition to test */
                                            (Can_IdType)(FLEXCAN_MB_READ_ID_STANDARD( can_hw_offset, mbindex)) : /* value if condition is true */
                                            (Can_IdType)(FLEXCAN_MB_READ_ID_EXTENDED( can_hw_offset, mbindex) | FLEXCAN_MBC_ID_IDE); /* value if condition is false */

                            /* Copy the Pdu handle. */
                            can_Pdu.swPduHandle = Can_ControllerStatuses[controller].TxPduId[mbindex];

                            /* Copy the data. */
                            for ( can_databyte_index = (uint8)0U; can_databyte_index < can_Pdu.length; can_databyte_index++)
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                */
                                can_mb_data[can_databyte_index] = FLEXCAN_MB_READ_DATA_BYTE (can_hw_offset, mbindex, can_databyte_index);
                            }

                            /* Payload pointer points to the data. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
                            */
                            /*lint -save -e934*/
                            can_Pdu.sdu = can_mb_data;
                            /*lint -restore*/

                    #ifndef E2656_FLEXCAN_XPC56XXX
                            /* Clear the Cancellation Flag. */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            can_mb_config = ((uint32)FLEXCAN_MB_READ( can_hw_offset, mbindex) & (uint32)(~FLEXCAN_MBCS_CODE)) | FLEXCAN_MBCS_CODETX;
                            FLEXCAN_MB_CS_CONFIG( can_hw_offset, mbindex, can_mb_config);
                    #endif /* E2656_FLEXCAN_XPC56XXX */
                            /* Call the CANCEL CONFIRMATION CALLBACK - This service is implemented in the CAN Interface and called by the
                            CAN Driver after a previous request for cancellation of a pending L-PDU transmit request was successfully performed. */

                            /**
                            @brief   (CAN058) The Can module interacts among other modules (eg. Diagnostic Event Manager (DEM), Development Error Tracer (DET)) with
                                        the CanIf module in a direct way. The driver only sees the CanIf module as origin and destination.
                            @brief   (CAN287) The Can module shall raise a notification when the cancellation was successful by calling the function CanIf_CancelTxConfirmation.
                            @remarks Covers CAN058, CAN287
                            @remarks Implements DCAN00058, DCAN00287
                            */
                            /**
                            @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
                            */
                            /*lint -save -e934*/
                            CanIf_CancelTxConfirmation( &can_Pdu);
                            /*lint -restore*/
                        }
                    }
                }
            }
            else
            {
                /* The MB either transmitted before it was cancelled (i.e. cancellation of an empty MB) and the interrupt routine already processed it.
                    Clear the cancellation flag (to take care of the first of the two possibilities) */
                    can_mb_config = ((uint32)FLEXCAN_MB_READ( can_hw_offset, mbindex) & (uint32)(~FLEXCAN_MBCS_CODE)) | FLEXCAN_MBCS_CODETX;
                    FLEXCAN_MB_CS_CONFIG( can_hw_offset, mbindex, can_mb_config);
                /* No other action needed, the MB will now be empty and the interrupt routine has taken care of reporting to CanIf. */
            }
        }
    }

#endif /* (CAN_TXCANCEL_SUPPORTED == STD_ON) */

#if ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON))
/*================================================================================================*/
/**
* @brief          Process a message buffer abort
* @details        This function write a abort code (b'1001) to MBCS[CODE] field of the MB.
*                This routine is called by:
*                - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Hth - HW-transmit handler
*
* @pre            Driver must be initialized and the current MB transmission should be ready for transmit.
*
* @implements     DCAN02809
*
*/
/*================================================================================================*/

FUNC(void, CAN_CODE) Can_LLD_AbortMb( VAR(Can_HWObjectCountType, CAN_VAR) Hth )
{
    VAR(uint8, CAN_VAR) can_controller;
    /* Variable for indexing the MBs */
    VAR(uint8, CAN_VAR) can_mb_index = 0U;
    /* Controller hardware offset on chip. */
    VAR(uint8, CAN_VAR)    can_hw_offset = 0U;

    can_controller = Can_CurrentConfigPtr->Can_ControllerID_Mapping[Hth];
    can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset;

    /* Here, we are positioning to the forst MessageBuffer that has ObjectId = Hth*/
    can_mb_index = Can_ControllerStatuses[can_controller].FirstTxMBIndex;
    while( (Can_ControllerStatuses[can_controller].Can_MBMapping[can_mb_index] != Hth) &&
           (can_mb_index < Can_CurrentConfigPtr->ControlerDescriptors[can_controller].MaxMBCount) )
    {
        can_mb_index ++;
    }
    /*Now we must search the MessageBuffer that has problems, in the range of the Hth.*/
    while( (Can_ControllerStatuses[can_controller].Can_MBMapping[can_mb_index] == Hth) &&
            ((uint32)FLEXCAN_MB_READ_CS( can_hw_offset, can_mb_index) != (uint32)(FLEXCAN_MBCS_CODETX)) &&
            (can_mb_index < (Can_CurrentConfigPtr->ControlerDescriptors[can_controller].MaxMBCount)) )
    {
        can_mb_index ++;
    }

    /* Here, we have the correct MessageBuffer to be canceled*/

#if (CAN_DEV_ERROR_DETECT == STD_ON)
            /* Test if controller is in valid range. */
            if ( (can_controller >= (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured) ||
                 (FLEXCAN_NULL_OFFSET == Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset) )
            {
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_ABORT_MB, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
                if ( CAN_CONTROLLERCONFIG_RXFIFO == ((uint32)((Can_ControllerConfigPtr + can_controller)->Options) & CAN_CONTROLLERCONFIG_RXFIFO) )
                {
                    can_mb_index += FLEXCAN_FIFO_MB_COUNT;
                }
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */

                Can_LLD_Cancel( can_controller, can_mb_index);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
}
#endif /* (CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */
/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Can_ReturnType, CAN_CODE) Can_LLD_Write( Can_HWObjectCountType Hth,
                                               P2CONST(Can_PduType, CAN_VAR, CAN_APPL_CONST) PduInfo )
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, CAN_VAR) Out_can_return = CAN_BUSY;
        /* Variable for keeping the controller Id. */
        VAR(uint8, CAN_VAR)          can_ctrl_id = 0U;
        /* Variable for indexing the MBs. */
        VAR(uint8, CAN_VAR)          can_mb_index = 0U;
        /* General purpose variable */
#if ((CAN_TXMUX_SUPPORTED == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON))
        /* Variables for keeping track of the lowest prio message. */
        VAR(uint8, CAN_VAR)          can_mb_lprio_index = 0U;
        VAR(uint32, CAN_VAR)         can_mb_lprio_id = 0U;
#endif /* ((CAN_TXMUX_SUPPORTED == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON)) */
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)          can_hw_offset = 0U;
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        /* Variable for determining the IFLAG register for every MB: IFLAG1 or IFLAG2. */
        VAR(uint8, CAN_VAR)          can_iflag_reg_index = 0U;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, CAN_VAR)         can_temp_flag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, CAN_VAR)         can_iflag_reg = 0U;
        /* Variable for storing the ID of the MB from MB structure. */
        VAR(uint32, CAN_VAR)         can_mb_messageid = 0U;
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, CAN_VAR)         can_mb_config = 0U;
        /* Variable for byte index of the MB data. */
        VAR(uint8, CAN_VAR)          can_mb_data_byte = 0U;


        /* Get the Controller ID for the current Hth MB. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_ctrl_id = Can_CurrentConfigPtr->Can_ControllerID_Mapping[Hth];

#if ((CAN_TXMUX_SUPPORTED == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON))
        /* Define variable for keeping track of the lowest prio message. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_mb_lprio_index = Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].MaxMBCount - (uint8)0x1U;
#endif /* ((CAN_TXMUX_SUPPORTED == STD_ON) && (CAN_TXCANCEL_SUPPORTED == STD_ON)) */

        /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].ControllerOffset;

#if (CAN_TXMUX_SUPPORTED == STD_ON)
        /* Need to find a free MB for transmission. This do-while block is executed only when multiplex transmission is ON because the data can be stored in any MB. */

        /* Calculate the MB index. When transmit multiplex is enabled search any MB to be free, else use the MB mapped to current HTH. */
        can_mb_index = Can_ControllerStatuses[can_ctrl_id].FirstTxMBIndex;
        while( (Can_ControllerStatuses[can_ctrl_id].Can_MBMapping[can_mb_index] != Hth) &&
               (can_mb_index < Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].MaxMBCount) )
        {
            can_mb_index ++;
        }
        /* This do-while is executed only if TX multiplexing is activated. */
        do
        {
#else /* (CAN_TXMUX_SUPPORTED == STD_OFF) */

            /* Calculate the MB index. */
            can_mb_index = (uint8)((Can_HWObjectCountType)Hth - (Can_HWObjectCountType)Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].HthOffset);

    #if (CAN_RXFIFO_ENABLE == STD_ON)
            /* When RxFifo is enabled the mbindex should consider the space reserved for this fifo.  */
            if ( CAN_CONTROLLERCONFIG_RXFIFO == ((Can_ControllerConfigPtr + can_ctrl_id)->Options & CAN_CONTROLLERCONFIG_RXFIFO) )
            {
                can_mb_index += FLEXCAN_FIFO_MB_COUNT;
            }
    #endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */

#endif /* (CAN_TXMUX_SUPPORTED == STD_OFF) */

            /* Is the MB empty?
                 This test is a bit early; the TxGuard is not set yet and someone else can grab this MB before we reserve it
                 but it saves setting the guard on full or cancelled MBs only to discover they are not empty and clearing the guard again. */
            if ( FLEXCAN_MBCS_CODETX == (uint32)FLEXCAN_MB_READ_CS( can_hw_offset, can_mb_index) )
            {
                /**
                @brief   (CAN212) The function Can_Write shall perform following actions if the hardware transmit object is free: The mutex for that HTH is set to 'signaled';
                         the ID, DLC and SDU are put in a format appropriate for the hardware; All necessary control operations to initiate the transmit are done;
                         The mutex for that HTH is released; The function returns with CAN_OK.
                @remarks Covers CAN212
                @remarks Implements DCAN00212
                */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                /* Check whether Can controller supports 64 message buffers */
                if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + can_ctrl_id)->Can_NumberOfMB)
                {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                    /* Calculate the index of the IFLAG register and Txguard (index=0 for MB32...MB63, index=1 for MB0...MB31). */
                    can_iflag_reg_index = (uint8)((uint8)can_mb_index >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x01U;
                    /* Get the content of IFLAG register for which corresponds this MB. */
                    can_iflag_reg = ((uint32)0x0U == (uint32)can_iflag_reg_index) ? (uint32)FLEXCAN_IFLAG2_READ(can_hw_offset) : (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                }
                else
                {
                    /* Get the content of IFLAG register for which corresponds this MB. */
                    can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
                }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                /* Get the content of IFLAG register for which corresponds this MB. */
                can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                /* Calculate the bit in the IFLAG register. */
                can_temp_flag = ((uint32)0x01U) << ((uint32)can_mb_index & FLEXCAN_MASK_32BITS);

                SchM_Enter_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_02);

                /* Test the GUARD MASK and the INTERRUPT FLAG.
                     Cannot operate on locked out MBs (re-entry).. also cannot operate on MBs for which the Tx confirmation has not been sent yet.
                     Below is read-modify-write cycle for TxGuard flag which may be interrupted -> must use SchM_Enter_Can() for preventing broken TxGuard value. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                if ( (uint32)0x0U == (Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] & can_temp_flag) )
#else /* (CAN_MAXMB_SUPPORTED != FLEXCAN_MB_64) */
                if ( (uint32)0x0U == (Can_ControllerStatuses[can_ctrl_id].TxGuard[0] & can_temp_flag) )
#endif /* (CAN_MAXMB_SUPPORTED != FLEXCAN_MB_64) */
                {
                    /* This MB is not signaled as used by another message. */
                    if ( (uint32)0x0U == (can_iflag_reg & can_temp_flag) )
                    {
                        /* Interrupt flag is not set for this MB this meaning MB is not in progress. */

                        /* The mutex for that HTH is set to 'signaled': The guard is 0, the MB is not locked out at the moment -> lock it out. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                        Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] |= can_temp_flag;
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                        Can_ControllerStatuses[can_ctrl_id].TxGuard[0] |= can_temp_flag;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                        /* TxGuard was set without any risk of broken data - now can free the Critical section. */
                        SchM_Exit_Can(SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_02);

                        /* Is the MB still empty? */
                        if ( FLEXCAN_MBCS_CODETX == (uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index) )
                        {
                            can_mb_messageid = (uint32)PduInfo->id;
                            can_mb_config = (FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXEN | FLEXCAN_MBCS_SRR | (((uint32)PduInfo->length) << (uint32)16U));

                            /* Set-up the MB content for Tx. Remember the PduId for reporting when the frame is transmitted. */
                            Can_ControllerStatuses[can_ctrl_id].TxPduId[can_mb_index] = PduInfo->swPduHandle;

#if (CAN_EXTENDEDID == STD_ON)
                            if ( (can_mb_messageid & FLEXCAN_MBC_ID_IDE) != (uint32)0U)
                            {
                                /* Set the IDE bit in the MBCS register of the MB */
                                can_mb_config |= FLEXCAN_MBCS_IDE;
                                /* Clear the MSB bit of the id - this is used for sending embedded information by CanIf to Can to say if it is an extended or standard message type. */
                                can_mb_messageid &= (~FLEXCAN_MBC_ID_IDE);
                            }
                            else
                            {
#endif /* (CAN_EXTENDEDID == STD_ON) */
                                /* Standard ID - need to shift left 18 bits. */
                                can_mb_messageid <<= FLEXCAN_STANDARD_ID_SHIFT;
#if (CAN_EXTENDEDID == STD_ON)
                            }
#endif /* (CAN_EXTENDEDID == STD_ON) */

                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            FLEXCAN_MB_ID_CONFIG( can_hw_offset, can_mb_index, can_mb_messageid);

                            /* Copy the data into the MB memory. The driver will not read from a null pointer SDU. */
                            for ( can_mb_data_byte = (uint8)0U; can_mb_data_byte < PduInfo->length; can_mb_data_byte++)
                            {
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                                */
                                FLEXCAN_MB_DATA_CONFIG( can_hw_offset, can_mb_index, can_mb_data_byte, (PduInfo->sdu)[can_mb_data_byte]);
                            }

                            /* Transmit the Data - now the data should be on Can Bus. Configure the DLC. */
                            FLEXCAN_MB_CS_CONFIG( can_hw_offset, can_mb_index, can_mb_config);

                            /* When the Abort feature is enabled (AEN in MCR is asserted), after the Interrupt Flag is
                            asserted for a MB configured as transmit buffer, the MB is blocked, therefore the CPU is not able to update
                            it until the Interrupt Flag be negated by CPU. It means that the CPU must clear the corresponding IFLAG
                            before starting to prepare this MB for a new transmission or reception.
                            TxGuard is a software flag and IFLAG are hardware flags */

                            /* Clear the guard, end of critical section. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                            Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] &= (uint32)(~can_temp_flag);
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                            Can_ControllerStatuses[can_ctrl_id].TxGuard[0] &= (uint32)(~can_temp_flag);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                            /* Set-up return value to indicate sucessful Tx.
                                The Transmit succesufull operation is signaled to CanIf when IFLAG bit will be handled by polling/interrupt routine (Can_LLD_Process_Rx).*/
                            Out_can_return = CAN_OK;
                        }
                        else
                        /* MB not empty anymore, preempting code has grabbed it before we managed to set the guard bit. Clear the guard bit. */
                        {
                            /**
                            @brief   (CAN213) The function Can_Write shall perform no actions if the hardware transmit object is busy with another transmit request for an L-PDU that has higher priority than that for the current request:
                                  - The transmission of the L-PDU with higher priority shall not be cancelled and the function Can_Write is left without any actions.
                                  - The function Can_Write shall return CAN_BUSY.
                            @remarks Covers CAN213
                            @remarks Implements DCAN00213
                            */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                            Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] &= (uint32)(~can_temp_flag);
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                            Can_ControllerStatuses[can_ctrl_id].TxGuard[0] &= (uint32)(~can_temp_flag);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                            /* MB not TX empty anymore, preempting code has grabbed it before we managed to set the guard bit. Clear the guard, end of critical section. */
                            Out_can_return = CAN_BUSY;
                        }
                    }
                    else /* else of "if((uint32)0x0U==(can_iflag_reg&can_temp_flag))" */
                    /* MB is locked because it has the IFLAG bit set. */
                    {
                        SchM_Exit_Can( SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_02);
                        /*
                        The fact that the return value of the function is the same irrespective of whether the MB is locked out or busy with a lower prio message is a deficiency in the AutoSAR spec.
                        CanIf has no way of telling whether the message was cancelled or not in the special case and a priority inversion can occur.
                        */
                        /**
                        @brief   (CAN214) The function Can_Write shall return CAN_BUSY if a preemptive call of Can_Write has been issued, that could not be
                                    handled reentrant (i.e. a call with the same HTH).
                        @remarks Covers CAN214
                        @remarks Implements DCAN00214
                        */
                        Out_can_return = CAN_BUSY;
                    }
                }
                else /* else of "if((uint32)0x0U==(Can_ControllerStatuses[can_ctrl_id].TxGuard[0]&can_temp_flag))" */
                {
                    /* MB is locked out because software flag (Guart bit) is set. */
                    Out_can_return = CAN_BUSY;

                    SchM_Exit_Can( SCHM_CAN_INSTANCE_0, CAN_EXCLUSIVE_AREA_02);
#if ((CAN_TXCANCEL_SUPPORTED == STD_ON) && (CAN_TXMUX_SUPPORTED == STD_ON))
                    /* Do not Cancel the locked out message when TXMUX is enabled. */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                    */
                    can_mb_lprio_index = Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].MaxMBCount;
                    break;
#endif /* ((CAN_TXCANCEL_SUPPORTED == STD_ON) && (CAN_TXMUX_SUPPORTED == STD_ON)) */
                }

            }
            else /* else of "if(FLEXCAN_MBCS_CODETX==(uint32)FLEXCAN_MB_READ_CS(can_hw_offset,can_mb_index))" */
            /* MB is not empty */
            {
                /**
                @brief   (CAN286) The Can module shall initiate a cancellation, when all available hardware transmit objects are busy and an L-PDU with
                            higher priority is requested to be transmitted.
                @remarks Covers CAN286
                @remarks Implements DCAN00286
                */

#if (CAN_TXCANCEL_SUPPORTED == STD_ON)
                /* Keep track of the lowest prio message (highest ID). */
                can_mb_messageid = (((uint32)FLEXCAN_MB_READ( can_hw_offset, can_mb_index) & (uint32)FLEXCAN_MBCS_IDE) != (uint32)FLEXCAN_MBCS_IDE) ? /* condition to test */
                                      (uint32)FLEXCAN_MB_READ_ID_STANDARD( can_hw_offset, can_mb_index) : /* value if condition is true */
                                      (uint32)FLEXCAN_MB_READ_ID_EXTENDED( can_hw_offset, can_mb_index); /* value if condition is false */
  #if (CAN_TXMUX_SUPPORTED == STD_ON)
                /**
                    @brief   (CAN101) The Can module shall support multiplexed transmission mechanisms for devices where either:
                              - multiple transmit buffers can be filled over the same register set, and the uC stores the L-PDU into a free buffer autonomously or
                              - HW supported registers or functions to identify a free buffer are provided or
                              - L-PDUs of the multiplexed Transmit Objects are send in order of L-PDU priority.
                    @remarks Covers CAN101
                    @remarks Implements DCAN00101
                    */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                if ( (uint32)can_mb_lprio_id < (uint32)can_mb_messageid )
                {
                    /* Create a copy of the lowest priority ID and the index of MB which holds it. */
                    /* MISRA-C:2004 12.1 VIOLATION: Refer to REF 1 above */
                    can_mb_lprio_id = can_mb_messageid;
                    can_mb_lprio_index = can_mb_index;
                }

  #else /* (CAN_TXMUX_SUPPORTED == STD_OFF) */
                /* If cancellation is enabled and TxMux is disabled, make now the cancellation if it's the case.
                     Check the priority of the current message that is already in the MB (temp_id) with the priority of the new message (PduInfo). */
                if ( (uint32)can_mb_messageid > (uint32)PduInfo->id )
                {
                    /**
                    @brief   (CAN215) The function Can_Write shall perform following actions if the hardware transmit object is busy with another
                    transmit request for an L-PDU that has lower priority than that for the current request:
                    - The transmission of the L-PDU with lower priority shall be cancelled (asynchronously).
                    - The function CAN_Write shall return CAN_BUSY.
                    @remarks Covers CAN215
                    @remarks Implements DCAN00215
                    */
                    Can_LLD_Cancel( can_ctrl_id, can_mb_index);
                }
  #endif /* (CAN_TXMUX_SUPPORTED == STD_OFF) */

#endif /* (CAN_TXCANCEL_SUPPORTED == STD_ON) */

                /* MB is not empty. */
                Out_can_return = CAN_BUSY;
            }

#if (CAN_TXMUX_SUPPORTED == STD_ON)
            /* Increment the MB index. */
            can_mb_index++;

        }
              /**
              @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
              */
         while ( (Can_ControllerStatuses[can_ctrl_id].Can_MBMapping[can_mb_index] == Hth) && (CAN_BUSY == Out_can_return));
#endif /* (CAN_TXMUX_SUPPORTED == STD_ON) */


#if ((CAN_TXCANCEL_SUPPORTED == STD_ON) && (CAN_TXMUX_SUPPORTED == STD_ON))
        /* Was the message scheduled for transmission? */
        if ( CAN_OK != Out_can_return )
        {
            /* Did the search find a lower priority message? */
            /**
            @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
            */
            if ( can_mb_lprio_index < Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_id].MaxMBCount)
            {
                /* Calculate the index of the Txguard (index = 0 for MB32...MB63, index = 1 fro MB0...MB31). */
  #if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                /* Check whether Can controller supports 64 message buffers. */
                if (FLEXCAN_MB_64 == (Can_ControllerConfigPtr + can_ctrl_id)->Can_NumberOfMB)
                {
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                    can_iflag_reg_index = (uint8)(can_mb_lprio_index >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x01U;
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                }
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
  #endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
                /* Calculate the iflag value. */
                can_temp_flag = ((uint32)0x01U) << ((uint32)can_mb_lprio_index & FLEXCAN_MASK_32BITS);

                /* Cancel the lowest prio message providing it is of lower priority than the current message.
                  Lock the lowest prio MB out, no need to check if it is already locked (it was not locked during the search so it cannot be locked now). */
  #if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                /* Check whether Can controller supports 64 message buffers. */
                if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + can_ctrl_id)->Can_NumberOfMB)
                {
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                    Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] |= can_temp_flag;
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                }
                else
                {
                    Can_ControllerStatuses[can_ctrl_id].TxGuard[0U] |= can_temp_flag;
                }
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
  #else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                Can_ControllerStatuses[can_ctrl_id].TxGuard[0U] |= can_temp_flag;
  #endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                /* Check if the current message is standard to shift accordingly. */
                can_mb_messageid = ((FLEXCAN_MB_READ( can_hw_offset, can_mb_lprio_index) & (uint32)FLEXCAN_MBCS_IDE) != (uint32)FLEXCAN_MBCS_IDE) ? /* condition to test */
                                    (uint32)FLEXCAN_MB_READ_ID_STANDARD( can_hw_offset, can_mb_lprio_index) : /* value if condition is true */
                                    (uint32)FLEXCAN_MB_READ_ID_EXTENDED( can_hw_offset, can_mb_lprio_index); /* value if condition is false */

                /* Check the priority of the current message is greater that the one requested to send. */
                if ( (uint32)can_mb_messageid > (uint32)PduInfo->id )
                {
                    /* Message currently in the MB has lower priority, cancel it.
                          If the message is transmitted in the meantime, the MB will be blocked until the interrupt flag is cleared.
                          However an interrupt may come in reaction to the flag and send Tx confirmation -> Can_Cancel must check that. */
                    Can_LLD_Cancel( can_ctrl_id, can_mb_lprio_index);
                }

                /* Unlock the MB TxGuard. */
  #if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                /* Check whether Can controller supports 64 message buffers. */
                if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + can_ctrl_id)->Can_NumberOfMB)
                {
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                    Can_ControllerStatuses[can_ctrl_id].TxGuard[can_iflag_reg_index] &= (uint32)(~can_temp_flag);
    #if (CAN_MIX_MB_SUPPORT == STD_ON)
                }
                else
                {
                    Can_ControllerStatuses[can_ctrl_id].TxGuard[0U] &= (uint32)(~can_temp_flag);
                }
    #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
  #else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                Can_ControllerStatuses[can_ctrl_id].TxGuard[0U] &= (uint32)(~can_temp_flag);
  #endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
            }
        }
#endif /* ((CAN_TXCANCEL_SUPPORTED == STD_ON) && (CAN_TXMUX_SUPPORTED == STD_ON)) */

        return (Out_can_return);
    }


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_Process_Tx( CONST(uint8, CAN_CONST) controller,
                                          CONST(uint8, CAN_CONST) mbindex_start,
                                          CONST(uint8, CAN_CONST) mbindex_end )
    {

        /* Variable for indexing the MBs. */
        VAR(uint8, CAN_VAR)            can_mb_index = 0U;
        /* Pointer to the MBs structure configuration. */
        VAR(Can_PtrMBConfigContainerType, CAN_VAR) can_ptrMBConfigContainer = NULL_PTR;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)            can_hw_offset = 0U;
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        /* Variable for determining the IFLAG register for every MB: IFLAG1 or IFLAG2. */
        VAR(uint8, CAN_VAR)            can_iflag_reg_index = 0U;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, CAN_VAR)           can_temp_flag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, CAN_VAR)           can_iflag_reg = 0U;
#if (CAN_TXCANCEL_SUPPORTED == STD_ON)
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, CAN_VAR)           can_mb_config = 0U;
        /* Variable for Can message content. */
        VAR(Can_PduType, CAN_VAR)      can_Pdu;
        /* Variable for storing the data. */
        VAR(uint8, CAN_VAR)            can_mb_data[8];
        /* Index for data byte of MB. */
        VAR(uint8, CAN_VAR)            can_databyte_index = 0U;
#endif /* (CAN_TXCANCEL_SUPPORTED == STD_ON) */
#ifdef E2656_FLEXCAN_XPC56XXX
       #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
        /* define a variable to know the tx MBs cancellation status */
        VAR(uint8, CAN_VAR) can_cancelledflag = 0U;
       #endif
#endif /* E2656_FLEXCAN_XPC56XXX */
        /* Get the hardware offset for this controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        can_ptrMBConfigContainer = &(Can_CurrentConfigPtr->MBConfigContainer);

        /* Loop through all MBs to process. */
        for ( can_mb_index = mbindex_start; can_mb_index <= mbindex_end; can_mb_index++)
        {
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            /* Check whether Can controller supports 64 message buffers */
            if (FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
            {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                /* Calculate the index of the IFLAG register. */
                can_iflag_reg_index = (uint8)((uint8)can_mb_index >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x01U;
                /* Get the content of IFLAG register for which corresponds this MB. */
                can_iflag_reg = ((uint32)0x0U == (uint32)can_iflag_reg_index) ? (uint32)FLEXCAN_IFLAG2_READ(can_hw_offset) : (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
            }
            else
            {
                can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
            }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
            can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

            /* Calculate the bit in the IFLAG register. */
            can_temp_flag = ((uint32)0x01U) << ((uint32)can_mb_index & FLEXCAN_MASK_32BITS);

            /* Check the interrupt flag of the current MB. */
            if ( (can_iflag_reg & can_temp_flag) != (uint32)0x0U)
            {
                /* The interrupt flag is set, message was either transmitted or cancelled.
                     This code does not check whether the TxGuard is set.
                     It does not have to do the check as it only operates on MBs with the interrupt flag set and CanWrite does not
                        operate on MBs which have the interrupt flag set.
                     Set the TxGuard. */

                /* Check if Can_Write is currently trying to cancel this MB. If so, tell it that there is no need as the MB has just transmitted (or cancelled). */
                #ifdef E2656_FLEXCAN_XPC56XXX
                    #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        @note Violates MISRA 2004 Advisory Rule 12.4, side effects on right hand of logical operator: '&&'. - See @ref FlexCan_LLD_c_REF_8
                        */
                        if((((uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index)) == FLEXCAN_MBCS_CODETX) && ( (Can_HWObjectCountType)can_mb_index == Can_ControllerStatuses[controller].CancelMBIndex))
                    #endif
                #else
                        if ((Can_HWObjectCountType)can_mb_index == Can_ControllerStatuses[controller].CancelMBIndex)
                #endif /* E2656_FLEXCAN_XPC56XXX */
                {
                    Can_ControllerStatuses[controller].CancelMBIndex = can_ptrMBConfigContainer->MessageBufferConfigCount;
                    #ifdef E2656_FLEXCAN_XPC56XXX
                        #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                        can_cancelledflag = (uint8)1U;
                        #endif
                    #endif /* E2656_FLEXCAN_XPC56XXX */
                }

                /**
                @brief   (CAN031) The function Can_MainFunction_Write shall perform the polling of TX confirmation and TX cancellation confirmation when CanTxProcessing is set to POLLING.
                @remarks Covers CAN031
                @remarks Implements DCAN00031
                */
            #ifdef E2656_FLEXCAN_XPC56XXX
                #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                if((((uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index)) == FLEXCAN_MBCS_CODETX) && (can_cancelledflag == (uint8)1U))
                #endif
            #else
                switch ( (uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index) )
            #endif /* E2656_FLEXCAN_XPC56XXX */
                {
#if (CAN_TXCANCEL_SUPPORTED == STD_ON)
            #ifndef E2656_FLEXCAN_XPC56XXX
                /* The frame was aborted (cancelled). */
                case ( FLEXCAN_MBCS_CODETX | FLEXCAN_MBCS_CODETXABORT):
                {
            #endif /* E2656_FLEXCAN_XPC56XXX */
                        /* The interrupt flag is set, message was either transmitted or cancelled.
                          This code does not check whether the TxGuard is set.
                          It does not have to do the check as it only operates on MBs with the interrupt flag set and CanWrite does not
                            operate on MBs which have the interrupt flag set.
                          Set the TxGuard. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers */
                        if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                        {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            Can_ControllerStatuses[controller].TxGuard[can_iflag_reg_index] |= can_temp_flag;
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
                        else
                        {
                            Can_ControllerStatuses[controller].TxGuard[0] |= can_temp_flag;
                        }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                        Can_ControllerStatuses[controller].TxGuard[0] |= can_temp_flag;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                        /* Check if Can_Write is currently trying to cancel this MB. If so, tell it that there is no need as the MB has just transmitted (or cancelled). */
                        #ifdef E2656_FLEXCAN_XPC56XXX
                            #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                                /**
                                @note Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                                @note Violates MISRA 2004 Advisory Rule 12.4, side effects on right hand of logical operator: '&&'. - See @ref FlexCan_LLD_c_REF_8
                                */
                                if((((uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index)) == FLEXCAN_MBCS_CODETX) && ((Can_HWObjectCountType)can_mb_index == Can_ControllerStatuses[controller].CancelMBIndex))
                            #endif
                        #else
                                if ((Can_HWObjectCountType)can_mb_index == Can_ControllerStatuses[controller].CancelMBIndex)
                        #endif /* E2656_FLEXCAN_XPC56XXX */
                        {
                            Can_ControllerStatuses[controller].CancelMBIndex = can_ptrMBConfigContainer->MessageBufferConfigCount;
                        }

                        /* Read Control and Status Register of the MB. */
                        can_mb_config = (uint32)FLEXCAN_MB_READ( can_hw_offset, can_mb_index);

                        /* Transfer the DLC. */
                        can_Pdu.length = (uint8)((can_mb_config & FLEXCAN_MBCS_LENGTH) >> FLEXCAN_MBCS_LENGTH_SHIFT);

                        /* Get the message ID. Test to see whether the ID is Extended/Standard.
                            For extended IDs the most significant bit mus tbe set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/
                        can_Pdu.id = ((uint32)0x0U == (can_mb_config & FLEXCAN_MBCS_IDE)) ? /* condition to test */
                                        (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_STANDARD( can_hw_offset, can_mb_index)) : /* value if condition is true */
                                        (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_EXTENDED( can_hw_offset, can_mb_index) | FLEXCAN_MBC_ID_IDE); /* value if condition is false */

                        /**
                        @brief   (CAN276) The function Can_Write shall store the swPduHandle that is given inside the parameter PduInfo until the Can module
                                   calls the CanIf_TXConfirmation for this request where the swPduHandle is given as parameter.
                        @remarks Covers CAN276
                        @remarks Implements DCAN00276
                        */
                        can_Pdu.swPduHandle = Can_ControllerStatuses[controller].TxPduId[can_mb_index];

                        /**
                        @brief   (CAN059) Data mapping by CAN to memory is defined in a way that the CAN data byte which is sent out first is array element 0,
                                    the CAN data byte which is sent out last is array element 7.
                        @remarks Covers CAN059
                        @remarks Implements DCAN00059
                        */
                        for ( can_databyte_index = (uint8)0U; can_databyte_index < can_Pdu.length; can_databyte_index++)
                        {
                            /**
                            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                            */
                            can_mb_data[can_databyte_index] = FLEXCAN_MB_READ_DATA_BYTE (can_hw_offset, can_mb_index, can_databyte_index);
                        }

                        /**
                        @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
                        */
                        /*lint -save -e934*/
                        can_Pdu.sdu = can_mb_data;
                        /*lint -restore*/

                        /* Clear the cancellation flag. */
                        FLEXCAN_MB_CS_CONFIG( can_hw_offset, can_mb_index, (uint32)((can_mb_config & (uint32)(~FLEXCAN_MBCS_CODE)) | FLEXCAN_MBCS_CODETX) );

                        /* Clear the interrupt flag - w1c. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers */
                        if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                        {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            FLEXCAN_IFLAG_CONFIG( can_hw_offset, can_iflag_reg_index, can_temp_flag);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
                        else
                        {
                            FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);
                        }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                        FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                        /* Release the MB, from now on the MB is free for Tx -> Clear TxGuard. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers */
                        if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                        {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            Can_ControllerStatuses[controller].TxGuard[can_iflag_reg_index] &= (uint32)(~can_temp_flag);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
                        else
                        {
                            Can_ControllerStatuses[controller].TxGuard[0U] &= (uint32)(~can_temp_flag);
                        }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                        Can_ControllerStatuses[controller].TxGuard[0U] &= (uint32)(~can_temp_flag);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                        /**
                        @brief   (CAN058) The Can module interacts among other modules (eg. Diagnostic Event Manager (DEM), Development Error Tracer (DET)) with the CanIf module in a direct way.
                                    The driver only sees the CanIf module as origin and destination.
                        @remarks Covers CAN058
                        @remarks Implements DCAN00058
                        */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
                        */
                        /*lint -save -e934*/
                        CanIf_CancelTxConfirmation( &can_Pdu);
                        /*lint -restore*/
            #ifndef E2656_FLEXCAN_XPC56XXX
                }
                        break;
            #endif /* E2656_FLEXCAN_XPC56XXX */
#endif /* (CAN_TXCANCEL_SUPPORTED == STD_ON) */
            #ifdef E2656_FLEXCAN_XPC56XXX
                #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                }
                else if((((uint32)FLEXCAN_MB_READ_CS(can_hw_offset, can_mb_index)) == FLEXCAN_MBCS_CODETX) && (can_cancelledflag == (uint8)0U))
                #endif
            #else
                /* Frame was transmitted */
                case ( FLEXCAN_MBCS_CODETX ):
            #endif /* E2656_FLEXCAN_XPC56XXX */
                {
                        /* Clear the interrupt flag - w1c. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        /* Check whether Can controller supports 64 message buffers */
                        if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                        {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                            FLEXCAN_IFLAG_CONFIG( can_hw_offset, can_iflag_reg_index, can_temp_flag);

  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                        }
                        else
                        {
                            FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);
                        }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                        FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);

#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                        /**
                        @brief   (CAN058) The Can module interacts among other modules (eg. Diagnostic Event Manager (DEM), Development Error Tracer (DET)) with the CanIf module in a direct way.
                                    The driver only sees the CanIf module as origin and destination.
                        @remarks Covers CAN058
                        @remarks Implements DCAN00058
                        */
                        CanIf_TxConfirmation( Can_ControllerStatuses[controller].TxPduId[can_mb_index]);
                }
            #ifdef E2656_FLEXCAN_XPC56XXX
                #if (E2656_FLEXCAN_XPC56XXX == STD_ON)
                else /* error condition, this should never occur */
                {
                        /* This case should never occurs. */
                        Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_DEFAULT);
                        /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                              Cer_ReportError() function implementation */
                }
                #endif
            #else
                        break;
                default:
                        /* This case should never occurs. */
                        Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_DEFAULT);
                        /* Error condition, this should never occur. */
                        /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                              Cer_ReportError() function implementation */
                        break;
                } /* end switch */
            #endif /* E2656_FLEXCAN_XPC56XXX */
            }
        }
    }


/*================================================================================================*/
/**
@brief         Service to perform the polling of TX confirmation and TX cancellation confirmation
@details       This routine is called by:
                - Can_MainFunction_Write() from Can.c file.
@pre           The controller must be configured for transmit in polling mode and at least one MB is configured for Tx.
@post          Process the transmission data in case of availability.
*/
/*================================================================================================*/
#if (CAN_TXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_MainFunction_Write(void)
    {

        /* Variable for indexing the controllers. */
        VAR(uint8, CAN_VAR)   can_ctrl_index = 0U;
        /* First MB to process. */
        VAR(uint8, CAN_VAR)   can_mb_first = 0U;
        /* Last MB to process. */
        VAR(uint8, CAN_VAR)   can_mb_last = 0U;

        /* Loop through all configured controller descriptors. */
        for ( can_ctrl_index = 0U; can_ctrl_index < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_ctrl_index++)
        {
            /* Check whether the controller is enabled and whether Tx polling is used for this controller. */
                 /**
                  @{
                  @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                  */
            if ( (FLEXCAN_NULL_OFFSET != Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_index].ControllerOffset) &&
                 ((uint16)0U != (CAN_CONTROLLERCONFIG_TXPOL_EN & (Can_ControllerConfigPtr + can_ctrl_index)->Options)) &&
                 ((uint8)0U != Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_index].MaxMBCount) )
                 /**@}*/
            {
                /* Init indexes that should be parsed for polling mode for current controller.
                  "FirstTxMBIndex" and "MaxMBCount" are updated considering RxFifo. */
                can_mb_first = (uint8)Can_ControllerStatuses[can_ctrl_index].FirstTxMBIndex;
                /**
                @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
                */
                can_mb_last = (uint8)Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_index].MaxMBCount - (uint8)1U;

                /* Enabled & TxPoll used. Process Tx interrupt flags. Start with the first Tx MB and finish at the last used MB. */
                Can_LLD_Process_Tx( (uint8)can_ctrl_index, (uint8)can_mb_first, (uint8)can_mb_last );
            }
        }
    }

#endif /* (CAN_TXPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_Process_Rx( CONST(uint8, CAN_CONST) controller,
                                          CONST(uint8, CAN_CONST) mbindex_start,
                                          CONST(uint8, CAN_CONST) mbindex_end )
    {
        /* Variable for indexing the MBs. */
        VAR(Can_HWObjectCountType, CAN_VAR)     can_mb_index = 0U;
        /* Number of data bytes. */
        VAR(uint8, CAN_VAR)      can_mb_data_length = 0U;
        /* Physical data bytes. */
        VAR(uint8, CAN_VAR)      can_mb_data[8];
        /* Index for data byte of MB. */
        VAR(uint8, CAN_VAR)      can_databyte_index = 0U;
        /* Variable for storing the Hrh. */
        VAR(Can_HWObjectCountType, CAN_VAR)      can_mb_hrh = 0U;
        /* Variables for storing the CanID. */
        VAR(Can_IdType, CAN_VAR) can_mb_messageid = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, CAN_VAR)      can_hw_offset = 0U;
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        /* Variable for determining the IFLAG register for every MB: IFLAG1 or IFLAG2. */
        VAR(uint8, CAN_VAR)      can_iflag_reg_index = 0U;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, CAN_VAR)     can_temp_flag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, CAN_VAR)     can_iflag_reg = 0U;
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, CAN_VAR)     can_mb_config = 0U;
        /* Is set when process an warning or overflow for RxFifo only. */
        VAR(uint8, CAN_VAR)      can_mb_nodata = 0U;


        /* Get the hardware offset for this controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

#if (CAN_ISROPTCODESIZE == STD_OFF)
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        if(mbindex_start >= FLEXCAN_MB_32)
        {
            /* Get the content of IFLAG2 register for which corresponds this MB. */
            can_iflag_reg = (uint32)FLEXCAN_IFLAG2_READ(can_hw_offset);
        }
        else
        {
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
            /* Get the content of IFLAG1 register for which corresponds this MB. */
            can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
        }
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
#endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
        /*
        Loop through all MBs to process.
            Phase1: If RXFifo is activated Overflow and Warning interrupts are processed separated because implies no data transfer.
            Phase2: Frame Avaibale Fifo and all other MB interrupts are processes after and have the logic of normal data read from buffer and transmit to CanIf.
        */
        for ( can_mb_index = mbindex_start; can_mb_index <= mbindex_end; can_mb_index++)
        {
#if (CAN_ISROPTCODESIZE == STD_ON)
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
#if (CAN_MIX_MB_SUPPORT == STD_ON)
            /* Check whether Can controller supports 64 message buffers */
            if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
            {
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                /* Calculate the Index of the IFLAG register. */
                can_iflag_reg_index = (uint8)((uint8)can_mb_index >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x1U;
                /* Get the content of IFLAG register for which corresponds this MB. */
                can_iflag_reg = ((uint32)can_iflag_reg_index == (uint32)0x0U) ? (uint32)FLEXCAN_IFLAG2_READ(can_hw_offset) : (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
#if (CAN_MIX_MB_SUPPORT == STD_ON)
            }
            else
            {
                /* Get the content of IFLAG register for which corresponds this MB. */
                can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
            }
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
            /* Get the content of IFLAG register for which corresponds this MB. */
            can_iflag_reg = (uint32)FLEXCAN_IFLAG1_READ(can_hw_offset);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
#endif /* (CAN_ISROPTCODESIZE == STD_ON) */
            /* Calculate the Flag value. */
            can_temp_flag = ((uint32)0x1U) << ((uint32)can_mb_index & FLEXCAN_MASK_32BITS);

            /* Check the interrupt flag. */
            if ( (uint32)0x0U != (can_iflag_reg & can_temp_flag) )
            {

#if (CAN_ISROPTCODESIZE == STD_OFF)
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
                /* Calculate the Index of the IFLAG register. */
                can_iflag_reg_index = (uint8)((uint8)can_mb_index >> FLEXCAN_MB_SHIFT5BIT) ^ (uint8)0x1U;
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64) */
#endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
                /* ********************* Phase1 ********************* */
                /* Check if "mbindex" corresponds to flags for Int Fifo status: Overflow or Warning.
                            If Fifo is disabled, then current flags are normal MB interrupt bits. */
                if ( CAN_CONTROLLERCONFIG_RXFIFO == ((Can_ControllerConfigPtr + controller)->Options & CAN_CONTROLLERCONFIG_RXFIFO) )
                {
                    if ( FLEXCAN_FIFOOVERFLOW_INT_INDEX == (uint32)can_mb_index )
                    {
                        /* Call the handling routine for Overflow fifo event. */
                        Can_CurrentConfigPtr->ControlerDescriptors[controller].Can_RxFifoOverflowNotification();
                        can_mb_nodata = (uint8)1U;
                    }

                    if ( FLEXCAN_FIFOWARNING_INT_INDEX == (uint32)can_mb_index )
                    {
                        /* Call Rx FIFO warning Notification. */
                        Can_CurrentConfigPtr->ControlerDescriptors[controller].Can_RxFifoWarningNotification();
                        can_mb_nodata = (uint8)1U;
                    }

                    if ( FLEXCAN_FIFOFRAME_INT_INDEX == (uint32)can_mb_index )
                    {
                        /* Access data available in MB0 when there is Buffer MB5 Interrupt - Frames Available in FIFO. */
                        can_mb_hrh = (Can_HWObjectCountType)can_mb_index;
                        can_mb_index = (Can_HWObjectCountType)0x0U;
                    }
                }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


                /* ********************* Phase2 ********************* */
                /* Check the interrupt flag. Execute this only if it is MB dat or RxFifo data. */
                if (can_mb_nodata == (uint8)0U)
                {

                    can_mb_config = (uint32)FLEXCAN_MB_READ(can_hw_offset, can_mb_index);

                    /* Create a local copy of the MB to ensure that it is locked out for minimum amount of time.
                        Read the DLC; this read access also locks the MB. */
                    can_mb_data_length = (uint8)( (can_mb_config & FLEXCAN_MBCS_LENGTH) >> FLEXCAN_MBCS_LENGTH_SHIFT);

                    /* Get the ID of the message.
                      For extended IDs the most significant bit mus tbe set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/
                    can_mb_messageid = ((uint32)0x0U == (can_mb_config & (uint32)FLEXCAN_MBCS_IDE)) ? /* condition to test */
                                        (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_STANDARD( can_hw_offset, can_mb_index)) : /* value if condition is true */
                                        (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_EXTENDED( can_hw_offset, can_mb_index) | FLEXCAN_MBC_ID_IDE); /* value if condition is false */

                    /**
                    @brief   (CAN060) Data mapping by CAN to memory is defined in a way that the CAN data byte which is sent out first is array element 0,
                               the CAN data byte which is sent out last is array element 7.
                    @brief   (CAN299) The Can module shall copy the L-SDU in a shadow buffer after reception, if the RX buffer cannot be protected (locked)
                               by CAN Hardware against overwriting by a newly received message.
                    @brief   (CAN300) The Can module shall copy the L-SDU in a shadow buffer, if the CAN Hardware is not globally accessible.
                    @remarks Covers CAN060, CAN299, CAN300
                    @remarks Implements DCAN00060, DCAN00299, DCAN00300
                    */
                    for ( can_databyte_index = (uint8)0U; can_databyte_index < can_mb_data_length; can_databyte_index++)
                    {
                        /* Copy the data  */
                        /**
                        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                        */
                        can_mb_data[can_databyte_index] = FLEXCAN_MB_READ_DATA_BYTE (can_hw_offset, can_mb_index, can_databyte_index);
                    }

                /* Determine Hrh of the message. */
#if (CAN_RXFIFO_ENABLE == STD_ON)
                    if ( ((uint16)0U != (((Can_ControllerConfigPtr + controller)->Options) & (CAN_CONTROLLERCONFIG_RXFIFO))) &&
                         ((uint8)0U == can_mb_index) )
                    {
                        /* Restore the MB index. */
                        can_mb_index = can_mb_hrh;

                        /* If RxFifo is enabled and interrupt was for data in the RxFifo. */
                        can_mb_hrh = (Can_HWObjectCountType)0U;
                    }
                    else
                    {
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */
                        can_mb_hrh = (Can_HWObjectCountType)Can_ControllerStatuses[controller].Can_MBMapping[can_mb_index];
#if (CAN_RXFIFO_ENABLE == STD_ON)
                    }
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */


                    /* Clear the interrupt flag - w1c. */
#if (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64)
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    /* Check whether Can controller supports 64 message buffers. */
                    if ( FLEXCAN_MB_64 == (Can_ControllerConfigPtr + controller)->Can_NumberOfMB)
                    {
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
                        FLEXCAN_IFLAG_CONFIG( can_hw_offset, can_iflag_reg_index, can_temp_flag);
  #if (CAN_MIX_MB_SUPPORT == STD_ON)
                    }
                    else
                    {
                        FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);
                    }
  #endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#else /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */
                    FLEXCAN_IFLAG1_CONFIG( can_hw_offset, can_temp_flag);
#endif /* (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_32) */

                    /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
                        unless the CPU reads the C/S word of another MB.*/
                    FLEXCAN_TIMER_READ( can_hw_offset);

                    /**
                    @brief   (CAN279)  On L-PDU reception, the Can module shall call the RX indication callback function with ID, DLC and pointer to the L-SDU buffer as parameter.
                    @remarks Covers CAN279
                    @remarks Implements DCAN00279
                    */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
                    @note Violates MISRA 2004 Advisory Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type - See @ref FlexCan_LLD_c_REF_7
                    */
                    /*lint -save -e934*/
                    CanIf_RxIndication( can_mb_hrh, can_mb_messageid, can_mb_data_length, can_mb_data);
                    /* Compiler_Warning : This warning is due to the input argument 'can_mb_hrh'. can_mb_hrh in CanIf_RxIndication()
                                          is uint8 but 'can_mb_hrh' can be uint16 when CAN_MBCOUNTEXTENSION is STD_ON */

                    /*lint -restore*/
                }
            }
        } /* end for */
    }


/*================================================================================================*/
/**
@brief         Service to perform the polling of RX indications.
@details       This routine is called by:
                - Can_MainFunction_Read() from Can.c file.

@pre           The controller must be configured for receive in polling mode and at least one MB is configured for Rx.
@post          Process the reception data in case of availability.
*/
/*================================================================================================*/
#if (CAN_RXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_MainFunction_Read( void)
    {

        /* Variable for indexing the controllers. */
        VAR(uint8, CAN_VAR)  can_ctrl_index = 0U;
        /* First MB to process. */
        VAR(uint8, CAN_VAR)  can_mb_first = 0U;
        /* Last MB to process. */
        VAR(uint8, CAN_VAR)  can_mb_last = 0U;

        /* Loop through all configured controller descriptors. */
        for ( can_ctrl_index = (uint8)0U; can_ctrl_index < (uint8)Can_CurrentConfigPtr->Can_ControllersConfigured; can_ctrl_index++)
        {
            /**
            @brief   (CAN108) The function Can_MainFunction_Read shall perform the polling of RX indications when CanRxProcessing is set to POLLING.
            @remarks Covers CAN108
            @remarks Implements DCAN00108
            */
            if ( (FLEXCAN_NULL_OFFSET != Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_index].ControllerOffset) &&
                 ((uint16)0U != (CAN_CONTROLLERCONFIG_RXPOL_EN & (Can_ControllerConfigPtr + can_ctrl_index)->Options)) &&
                 (Can_CurrentConfigPtr->ControlerDescriptors[can_ctrl_index].MaxMBCount != (uint8)0U) )
            {
                /* Init last MB to process for RX. "FirstTxMBIndex" is updated considering RxFifo. */
                can_mb_last = (uint8)(Can_ControllerStatuses[can_ctrl_index].FirstTxMBIndex - (uint8)1U);

                /* Enabled & RxPoll used : process Rx interrupt flags, start with the first Rx MB (0) and finish before the first Tx MB. */
                Can_LLD_Process_Rx( (uint8)can_ctrl_index, (uint8)can_mb_first, (uint8)can_mb_last);
            }
        }
    }

#endif /* (CAN_RXPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
@brief         Local function for calling notification function to notify upper layer during
                 Can_MainFunction_BusOff if polling is selected or from ISR when Interrupt mode selected.
@details       This routine is called by:
                - Can_Process_BusOff() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).

@pre           A busoff condition must to be fulfilled.
@post          Status flag is cleared.
*/
/*================================================================================================*/
FUNC (void, CAN_CODE) Can_LLD_Process_BusOff( CONST(uint8, CAN_CONST) controller)
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        /* Clear the ESR[BOFF_INT] bus off interrupt flag (w1c). */
        FLEXCAN_SET_ESR_BOFFINT( can_hw_offset);
    }


/*================================================================================================*/
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
/*================================================================================================*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (void, CAN_CODE) Can_LLD_Process_Wakeup( CONST(uint8, CAN_CONST) controller)
    {

  #if (CAN_WKP_INT_SUPPORT == STD_ON)
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) can_hw_offset = 0U;
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */


  #if (CAN_WKP_INT_SUPPORT == STD_ON)
        /* Get the hardware offset for this controller. */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        /* Clear the ESR[WAK_INT]  WakeUp interrupt flag (w1c). */
        FLEXCAN_SET_ESR_WAK_INT( can_hw_offset);
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
        /* Clear pending interrupt serviced. */
        Can_AckInt_ExtWkp( Can_CurrentConfigPtr->ControlerDescriptors[controller].WakeupChannel);
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) */

    }

#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/*================================================================================================*/
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
@post          Report the occurence or not for an wakeup event.
*/
/*================================================================================================*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (Std_ReturnType, CAN_CODE) Can_LLD_Cbk_CheckWakeup( VAR(uint8, CAN_VAR) controller)
    {

        /* Return value. */
        Std_ReturnType        Out_can_return = (uint8)E_NOT_OK;
  #if (CAN_WKP_INT_SUPPORT == STD_ON)
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */


  #if (CAN_WKP_INT_SUPPORT == STD_ON)
        /**
        @brief   (CAN361) The function Can_Cbk_CheckWakeup shall check if the requested CAN controller has detected a wakeup.
                    If a wakeup event was successfully detected, the function shall return E_OK, otherwise E_NOT_OK.
        @remarks Covers CAN361
        @remarks Implements DCAN00361
        */
        if ( FLEXCAN_ESR_WAK_INT == (FLEXCAN_ESR_WAK_INT & (uint32)FLEXCAN_ESR_READ(can_hw_offset)) )
        {
            /* Controller is in WakeUp state. */
            Out_can_return = (uint8)E_OK;
        }
  #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_OFF) */

  #if (CAN_WKP_EXT_SUPPORT == STD_ON)
        /* Read the WakeUp Unit's Status Register (WISR)*/
        /**
        @brief   (CAN361) The function Can_Cbk_CheckWakeup shall check if the requested CAN controller has detected a wakeup. If a wakeup event was successfully detected, the function shall return E_OK, otherwise E_NOT_OK.
        @remarks Covers CAN361
        @remarks Implements DCAN00361
        */
        if ( (uint8)E_NOT_OK == Out_can_return)
        {
            Out_can_return = Can_GetStatus_ExtWkp( Can_CurrentConfigPtr->ControlerDescriptors[controller].WakeupChannel);
        }
  #endif /* (CAN_WKP_EXT_SUPPORT == STD_ON) && (CAN_WKP_INT_SUPPORT == STD_OFF) */

        return (Out_can_return);
    }

#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/*================================================================================================*/
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
/*================================================================================================*/
FUNC (Std_ReturnType, CAN_CODE) Can_LLD_CheckBusOff( VAR(uint8, CAN_VAR) controller)
    {

        /* Return value. */
        VAR(uint8, CAN_VAR) Out_can_return = (uint8)E_NOT_OK;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        /**
        @note Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref FlexCan_LLD_c_REF_5
        */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        /* Check Busoff flag if it's set. */
        if ( FLEXCAN_ESR_BOFFINT == (FLEXCAN_ESR_BOFFINT & (uint32)FLEXCAN_ESR_READ(can_hw_offset)) )
        {
            /* Controller is in BusOff state. */
            Out_can_return = (uint8)E_OK;
        }

        return (Out_can_return);
    }


/*================================================================================================*/
/**
@brief         Process Rx Fifo FrameAvailable events.
@details       This routine is called by:
                - Can_RxFifoFrameAvNotif() from Can.c file.

@param[in]     controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).

@pre           Driver must be initialized and RxFifo should be enabled.
*/
/*================================================================================================*/
#if (CAN_RXFIFO_ENABLE == STD_ON)

FUNC(void, CAN_CODE) Can_LLD_RxFifoFrameAvNotif( CONST(uint8, CAN_CONST) controller)
    {
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)  can_hw_offset = 0U;
        /* Variable for indexing the MBs. */
        VAR(uint8, CAN_VAR)    can_mb_index = 0U;
        /* Number of data bytes. */
        VAR(uint8, CAN_VAR)    can_mb_data_length = 0U;
        /* Physical data bytes. */
        VAR(uint8, CAN_VAR)    can_mb_data[8];
        /* Index for data byte of MB. */
        VAR(uint8, CAN_VAR)    can_databyte_index = 0U;
        /* Variable for storing the Hrh. */
        VAR(uint8, CAN_VAR)    can_hrh = 0U;
        /* Variables for storing the CanID. */
        VAR(Can_IdType, CAN_VAR) can_mb_messageid = 0U;
        /* Temporary variable. */
        VAR(uint32, CAN_VAR)   can_mb_config = 0U;


        /* Get the hardware offset for this controller. */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[controller].ControllerOffset;

        /* Check Frame Available int flag. */
        if ( FLEXCAN_FIFO_AVAILABLE_INT_MASK == (FLEXCAN_IFLAG1_READ(can_hw_offset) & FLEXCAN_FIFO_AVAILABLE_INT_MASK) )
        {
            can_mb_config = (uint32)FLEXCAN_MB_READ(can_hw_offset, can_mb_index);

            /* Create a local copy of the MB to ensure that it is locked out for minimum amount of time. Read the DLC; this read access also locks the MB. */
            can_mb_data_length = (uint8)((can_mb_config & FLEXCAN_MBCS_LENGTH) >> FLEXCAN_MBCS_LENGTH_SHIFT);

            /* Get the ID of the message.
            For extended IDs the most significant bit must be set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/
            can_mb_messageid = ((uint32)0x0U == (can_mb_config & (uint32)FLEXCAN_MBCS_IDE)) ? /* condition to test */
                                    (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_STANDARD(can_hw_offset, can_mb_index)) : /* value if condition is true */
                                    (Can_IdType)((uint32)FLEXCAN_MB_READ_ID_EXTENDED(can_hw_offset, can_mb_index) | FLEXCAN_MBC_ID_IDE); /* value if condition is false */

            /* Copy the data. */
            for ( can_databyte_index = (uint8)0U; can_databyte_index < can_mb_data_length; can_databyte_index++)
            {
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref FlexCan_LLD_c_REF_2
                */
                can_mb_data[can_databyte_index] = FLEXCAN_MB_READ_DATA_BYTE (can_hw_offset, can_mb_index, can_databyte_index);
            }

            /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
                unless the CPU reads the C/S word of another MB.*/
            FLEXCAN_TIMER_READ( can_hw_offset);

            /*
            Call the RxIndication function - This service is implemented in the CAN Interface and called by the CAN Driver after a CAN L-PDU has been received.
            Within this service, the CAN Interface translates the CanId into the configured target PDU ID and routes this indication to the configured upper layer target service(s).
            */
            /**
            @note Violates MISRA 2004 Advisory Rule 1.2, Taking address of near auto variable - See @ref FlexCan_LLD_c_REF_4
            */
            /*lint -save -e934*/
            CanIf_RxIndication( can_hrh, can_mb_messageid, can_mb_data_length, can_mb_data);
            /*lint -restore*/

            /* Ack interrupt flag - w1c bit. */
            FLEXCAN_IFLAG1_CONFIG( can_hw_offset, FLEXCAN_FIFO_AVAILABLE_INT_MASK);
        }

    }

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/*================================================================================================*/
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
/*================================================================================================*/

#if (CAN_DUAL_CLOCK_MODE == STD_ON)

FUNC(Std_ReturnType, CAN_CODE) Can_LLD_SetClockMode( VAR(uint8, CAN_VAR) can_controller, VAR(Can_ClockMode, CAN_VAR) can_clk_mode)
    {
        /* Return the operation success. */
        VAR(Std_ReturnType, CAN_VAR) Out_can_return = (uint8)E_OK;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)  can_hw_offset = 0U;


        /* Get the hardware offset for this controller. */
        can_hw_offset = Can_CurrentConfigPtr->ControlerDescriptors[can_controller].ControllerOffset;

        switch (can_clk_mode)
        {
            case (CAN_NORMAL):
                FLEXCAN_CTRL_CONFIG( can_hw_offset, (uint32)((Can_ControllerConfigPtr + can_controller)->ControlRegister));
                break;

            case (CAN_ALTERNATE):
                FLEXCAN_CTRL_CONFIG( can_hw_offset, (uint32)((Can_ControllerConfigPtr + can_controller)->ControlRegister_Alternate));
                break;

            default:
                Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SETCLOCKMODE, (uint8)CAN_E_DEFAULT);
                Out_can_return = (uint8)E_NOT_OK;
                /* Compiler_Warning : This warning is thrown due to the infinite loop while(1) in the
                                      Cer_ReportError() function implementation */
                break;
        }

        return (Out_can_return);

    }

#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */


#define CAN_STOP_SEC_CODE
/**
@file  FlexCan_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref FlexCan_LLD_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref FlexCan_LLD_c_REF_3
*/
/*lint -save -e451 -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
