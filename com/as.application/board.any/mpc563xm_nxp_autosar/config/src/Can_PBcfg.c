/**
    @file             Can_PBcfg.c
    @version          2.0.0

    @brief            AUTOSAR Can module interface
    @details          Configuration Structures for PostBuild.

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


#ifdef __cplusplus
extern "C" {
#endif

/**
@page misra_violations MISRA-C:2004 violations

@section Can_PBcfg_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Can_PBcfg_c_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.
*/

/**
@file    Can_PBcfg.c
@brief   (CAN078) The code file structure shall not be defined within this specification completely.
            At this point it shall be pointed out that the code-file structure shall include the following file named: Can_PBcfg.c.
            This file shall contain all post-build time configurable parameters.
@brief   (CAN221) VariantPB: (Mix of precompile and Post Build multiple selectable configurable configurations.
@remarks Covers CAN078, CAN221
@remarks Implements DCAN00078, DCAN00221
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can.h"
#include "Can_LLD.h"




/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief    Internal micro-dependent versioning.
          Check of AUTOSAR specification version & Vendor specific implementation version.
*/
#define CAN_AR_MAJOR_VERSION_PBCFG_C  3
#define CAN_AR_MINOR_VERSION_PBCFG_C  0
#define CAN_AR_PATCH_VERSION_PBCFG_C  0
#define CAN_SW_MAJOR_VERSION_PBCFG_C  2
#define CAN_SW_MINOR_VERSION_PBCFG_C  0
#define CAN_SW_PATCH_VERSION_PBCFG_C  0
/**@}*/


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_PBCFG_C != CAN_AR_MAJOR_VERSION) || \
     (CAN_AR_MINOR_VERSION_PBCFG_C != CAN_AR_MINOR_VERSION) || \
     (CAN_AR_PATCH_VERSION_PBCFG_C != CAN_AR_PATCH_VERSION))
  #error "AutoSar Version Numbers of Can_PBcfg.c and Can.h are different"
#endif
#endif

#if ((CAN_SW_MAJOR_VERSION_PBCFG_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_SW_MINOR_VERSION_PBCFG_C != CAN_SW_MINOR_VERSION) || \
     (CAN_SW_PATCH_VERSION_PBCFG_C != CAN_SW_PATCH_VERSION))
       #error "Software Version Numbers of Can_PBcfg.c and Can.h are different"
#endif


#define CAN_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"


/*==================================================================================================*/
/**
@{
@brief    Prototype of User Notifications
*/







/**@}*/
/*==================================================================================================*/







/*==================================================================================================*/
/**
@brief    Filter Masks
*/
/*==================================================================================================*/
CONST(Can_IdType, CAN_CONST) Can_FilterMasks0_PB[CAN_MAXFILTERCOUNT_0] =
    {   
        /* FilterMasks0[0], "CanFilterMask_0" */
        (Can_IdType)0x0U
    };




/*==================================================================================================*/
/**
@brief    Information about message buffers
@brief    (CAN100)Several TX hardware objects with unique HTHs may be configured. The CanIf module provides the HTH as parameter of the TX request. See Figure 7-2 for a possible configuration.
@remarks  Covers CAN100
@remarks  Implements DCAN00100
*/
/*==================================================================================================*/

CONST(Can_MBConfigObjectType, CAN_CONST) MessageBufferConfigs0_PB[CAN_MAXMBCOUNT_0] =
    {
        
        
        /* CanHardwareObject_0 Message Buffer of Can Controller ID = 0U */
        {
            /* IdMaskIndex */
            (Can_HWObjectCountType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)RECEIVE,
            /* MessageId */
            (Can_IdType)0x0U,
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HWObjectCountType)0x0U
        },
        
        
        /* CanHardwareObject_1 Message Buffer of Can Controller ID = 0U */
        {
            /* IdMaskIndex */
            (Can_HWObjectCountType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)TRANSMIT,
            /* MessageId */
            (Can_IdType)0x1U,
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HWObjectCountType)0x1U
        }
        
    };


/*==================================================================================================*/
/**
@brief    Configuration of FlexCan controllers
*/
/*==================================================================================================*/

CONST(Can_ControllerConfigType, CAN_CONST) ControllerConfigs0_PB[CAN_MAXCONTROLLERCOUNT_0] = {
    
    
        
            
    /*
        =================================================
        Clock Size = 6.4E7 Hz  - Clock from MCU. 
        
        Clock Prescaler = 4 (1..256)
        
        CanBitRate = 1000 Kbps (1bps..1Mbps)
        Number CANTimeQuantas per bit = 16 (8..25)
        
        CTRL Register Fields:
            PSEG1 = 3 (0..7)
            PSEG2 = 3 (1..7)
            PROPSEG = 6 (0..7)
            RJW = 3 (0..3)
        =================================================
    */
    
    /* Configuration for CanController ID0 == FlexCAN_A */
    {
      /* ===== Control Register - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)((3U << FLEXCAN_CTRL_PRESDIV_SHIFT) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        (3U << FLEXCAN_CTRL_RJW_SHIFT) |
        /* CTRL[PSEG1] - Segment 1 */
        (3U << FLEXCAN_CTRL_PSEG1_SHIFT) |
        /* CTRL[PSEG2] - Segment 2 */
        (3U << FLEXCAN_CTRL_PSEG2_SHIFT) |
        /* CTRL[CLK_SRC] - Clock source */
        (1U << FLEXCAN_CTRL_CLKSRC_SHIFT) |
        /* CTRL[LPB] - Loop-back mode */
        (0U << FLEXCAN_CTRL_LPB_SHIFT) |
        /* CTRL[SMP] - Sampling mode */
        (1U << FLEXCAN_CTRL_SMP_SHIFT) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        (1U << FLEXCAN_CTRL_BOFFREC_SHIFT) |
        /* CTRL[LBUF] - Lowest Buffer Transmitted First */
        (1U << FLEXCAN_CTRL_LBUF_SHIFT) |
        /* CTRL[LOM] - Listen only mode */
        (0U << FLEXCAN_CTRL_LOM_SHIFT) |
        /* CTRL[PROPSEG] - Propagation segment */
        6U) ,

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
        0U),
    
        
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

      /* ===== Controller Options ===== */
        (uint16)(
        
         /* RX Fifo Disabled */ 
        
        

        /* Rx select by interrupt */
        /* Tx select by interrupt */
        /* BusOff select by interrupt */
#if (CAN_WAKEUP_SUPPORT == STD_ON)
        /* WakeupPoll Enabled */
        CAN_CONTROLLERCONFIG_WKPOL_EN | 
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

        0U),
#if (CAN_MIX_MB_SUPPORT == STD_ON)
         /* Maximum MBs supported for this controller. */
         
            (uint8)64U,
            
         
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
    }
    
    
        
            
};



/*==================================================================================================*/
/**
@brief    Description of individual FlexCan controllers on chip
*/
/*==================================================================================================*/

CONST(Can_ControlerDescriptorType, CAN_CONST) ControlerDescriptors0_PB[CAN_MAXCONTROLLERCOUNT_0] =
    {   
        /* ControlerDescriptor of CanController_0 */
        {
            /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. */
            FLEXCAN_A_OFFSET,

            /* No. of Message Buffers for current controller */
            
            (uint8)2U,
            

            
            /* HthOffset - (FirstHTH - No.of Rx MBs) */
            (Can_HWObjectCountType)0U,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* WakeUp source ID (ECU State Manager) */
            (uint8)0U, /* EcuM source not used */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /* TableID Controller index */
            
            (uint8)0U,

            /* Pointer to RxFifo Overflow notification function. */
            (Can_PCallBackType)NULL_PTR,

            /* Pointer to RxFifo Warning notification function. */
            (Can_PCallBackType)NULL_PTR,
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

            /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */
            (Can_PCallBackType)NULL_PTR,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
    #if (CAN_WKP_EXT_SUPPORT == STD_ON)
            /* WKPU source */
            (uint8)0U, /* External Wakeup not used */
    #endif /*  (CAN_WKP_EXT_SUPPORT == STD_ON)*/
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
        }  /* ControlerDescriptors[0] end */
        
    };



/*==================================================================================================*/
/**
@brief    Top level structure containing all can driver configurations
*/
/*==================================================================================================*/
CONST(Can_ConfigType, CAN_CONST) CanConfigSet_0 =
    {
        /* Number of CAN controllers configured */
       (uint8) 1U,

        /* FilterMasksPtr */
       (Can_IdPtrType) Can_FilterMasks0_PB,

        /* ControllerConfigsPtr */
        ControllerConfigs0_PB,

        /* MessageBufferConfigContainer */
        {
            /* MessageBufferConfigsPtr */
            MessageBufferConfigs0_PB,

            /* MessageBufferConfigCount */
            (Can_HWObjectCountType)2U,
        },

        /* FlexCAN controller description */
        ControlerDescriptors0_PB,

#if (CAN_RXFIFO_ENABLE == STD_ON)
        /* Can_RxFiFoTableIdConfigType */
        NULL_PTR, /* Rx fifo disabled */
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */
        

        /*Maximum Object IDs configured */
        (Can_HWObjectCountType)2U,

        /*Controller ID mapping*/
        {0U,0U},

        /*Can Object Type mapping*/
        {(Can_ObjType)RECEIVE,(Can_ObjType)TRANSMIT}

    };




/**
@file  Can_PBcfg.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_PBcfg_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_PBcfg_c_REF_2
*/
#define CAN_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#ifdef __cplusplus
extern "C" }
#endif
