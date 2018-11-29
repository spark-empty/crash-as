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


[!NOCODE!]
/*
 Example 1 of valid configuration:
   Source Clock = 8MHz, Bit Rate = 1Mb/sec,
   CanControllerTimeQuanta  = 125ns
      -> Presclaer = 1, CanBit = 8Tq (these ale calculated in background)
   CanControllerPropSeg  = 3, CanControllerSeg1 = 0, CanControllerSeg2 = 1, CanSyncJumpWidth = 0.

 Example 2 of valid configuration:
   Source Clock = 8MHz, Bit Rate = 125Kb/sec,
   CanControllerTimeQuanta  = 1000ns,
      -> Presclaer = 8, CanBit = 8Tq (these ale calculated in background)
   CanControllerPropSeg  = 0, CanControllerSeg1 = 2, CanControllerSeg2 = 2, CanSyncJumpWidth = 2.
*/
[!ENDNOCODE!]

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
[!NOCODE!][!INCLUDE "Can_NotifyCheck_Src_PB.m"!][!ENDNOCODE!]

[!NOCODE!][!INCLUDE "Can_SourceClock.m"!][!ENDNOCODE!]

[!NOCODE!][!CALL "CanRxFifoWarningNotification_PB"!][!ENDNOCODE!]
[!NOCODE!][!CALL "CanRxFifoOverflowNotification_PB"!][!ENDNOCODE!]
[!NOCODE!][!CALL "CanErrorControllerNotification_PB"!][!ENDNOCODE!]
/**@}*/
/*==================================================================================================*/


[!NOCODE!][!/* This section is for global variables, local to this file */!]
    [!VAR "Tsyncsegment" = "1"!][!/* Sync_seg has 1 Tq length */!]
    [!/*
        Sync-seg = is the segment that is used to synchronise the nodes on the bus. A bit edge (if there is a data change) is expected during this segment.
        Prop-Seg = is a period of time that is used to compensate for physical delay times within the network.
        Phase-seg1 = is a buffer segment that may be lengthened during resynchronisation to compensate for oscillator drift and positive phase differences between the oscillators of the transmitting and receiving node(s).
        Phase-seg2 = is a buffer segment that may be shortened during resynchronisation (described below) to compensate for negative phase errors and oscillator drift.

        The Sample point is always at the end of Phase-seg1 and is the time at which the bus level is read and interpreted as the value of the current bit.
        Whether transmitting or receiving, all nodes on a single CAN bus must have the same nominal bit time. Bit time is programmable at each node on a CAN Bus and is a function
            of the period of the oscillator local to each node, the value that is user-programmed into a Baud Rate Prescaler (BRP) register in the controller at each node, and the programmed number of time quanta per bit.
        When any node receives a data frame or a remote frame, it is necessary for the receiver to synchronise with the transmitter.
            1. The first is hard synchronisation and occurs at Start-of-Frame (SOF).
            2. For subsequent bits in any received frame, if a bit edge does not occur in the Sync-seg segment of bit time, resynchronisation is automatically invoked and will shorten or lengthen the current bit time depending
                on where the edge occurs. The maximum amount by which the bit time is lengthened or shortened is determined by a user-programmable number of time quanta known as the Synchronisation Jump Width (SJW).
    */!]
[!ENDNOCODE!]

[!NOCODE!]
    [!LOOP "CanConfigSet/*"!]
    [!VAR "TableIdCount" = "0"!]
        [!LOOP "CanController/*"!]
            [!IF "CanControllerRxFifoEnable = 'true'"!]
                [!VAR "TableIdCount" = "$TableIdCount+8"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!IF "$TableIdCount != 0"!]
[!CODE!]

#if (CAN_RXFIFO_ENABLE == STD_ON)
/*==================================================================================================*/
/**
@brief    Can_RxFiFoTableIdConfigType
            Identifier FormatA:
            - StandardID: bits [29:19]
            - ExtendedID: bits [29:1]
            Identifier FormatB:
            - StandardID: bits [29:19] & [13:3]
            - ExtendedID: bits [29:16] & [13:0] (only 14 MSB)
            Identifier FormatC:
            - StandardID: bits [31::24] & [23:16] & [15:8] & [7:0] (only 8 MSB)
            - ExtendedID: bits [31::24] & [23:16] & [15:8] & [7:0] (only 8 MSB)
*/
/*==================================================================================================*/
CONST(Can_RxFiFoTableIdConfigType, CAN_CONST) RxFifoTableID_PBConfig[!"@index"!][CAN_MAXTABLEID_[!"@index"!]] =
    {[!ENDCODE!]
    [!VAR "TableIdCountLocal" = "0"!]
    [!LOOP "CanController/*"!]
        [!VAR "ControllerCanHwChannel" = "CanHwChannel"!]
        [!IF "CanControllerRxFifoEnable = 'true'"!]
            [!VAR "tableidvalue" = "0"!]
            [!LOOP "CanRxFifo/CanRxFifoTable/*"!]
                [!VAR "TableIdCountLocal" = "$TableIdCountLocal+1"!]
                [!IF "../../CanControllerIDAcceptanceMode = 'D'"!]
                    [!VAR "tableidvalue" = "0"!]
                [!ELSE!]
                    [!VAR "tableidvalue" = "num:i(CanIDValue0)"!]
                [!ENDIF!]
                [!VAR "tablefiltermaskvalue" = "num:i(CanMBFilterMaskValue)"!]

                [!IF "../../CanControllerIDAcceptanceMode = 'C'"!]
                    [!VAR "tableidvalue0" = "bit:shl($tableidvalue,24)"!]
                    [!VAR "tableidvalue1" = "bit:shl(num:i(CanIDValue1),16)"!]
                    [!VAR "tableidvalue2" = "bit:shl(num:i(CanIDValue2),8)"!]
                    [!VAR "tableidvalue3" = "bit:shl(num:i(CanIDValue3),0)"!]
                    [!VAR "tableidvalue" = "bit:or($tableidvalue0,$tableidvalue1)"!]
                    [!VAR "tableidvalue" = "bit:or($tableidvalue,$tableidvalue2)"!]
                    [!VAR "tableidvalue" = "bit:or($tableidvalue,$tableidvalue3)"!]
                [!ELSEIF "CanTableIDType = 'Standard'"!]
                    [!IF "../../CanControllerIDAcceptanceMode = 'A'"!]
                        [!VAR "tableidvalue" = "bit:shl($tableidvalue,19)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:shl($tablefiltermaskvalue,19)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue,num:hextoint('0xc0000000'))"!]
                    [!ENDIF!]
                    [!IF "../../CanControllerIDAcceptanceMode = 'B'"!]
                        [!VAR "tableidvalue0" = "bit:shl($tableidvalue,19)"!]
                        [!VAR "tableidvalue1" = "bit:shl(num:i(CanIDValue1),3)"!]
                        [!VAR "tableidvalue" = "bit:or($tableidvalue0,$tableidvalue1)"!]
                        [!VAR "tablefiltermaskvalue0" = "bit:and($tablefiltermaskvalue,num:hextoint('0x3ff800'))"!]
                        [!VAR "tablefiltermaskvalue1" = "bit:and($tablefiltermaskvalue,num:hextoint('0x7ff'))"!]
                        [!VAR "tablefiltermaskvalue0" = "bit:shl($tablefiltermaskvalue0,8)"!]
                        [!VAR "tablefiltermaskvalue1" = "bit:shl($tablefiltermaskvalue1,3)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue0,$tablefiltermaskvalue1)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue,num:hextoint('0xc000c000'))"!]
                    [!ENDIF!]
                [!ELSE!]
                    [!IF "../../CanControllerIDAcceptanceMode = 'A'"!]
                        [!VAR "tableidvalue" = "bit:shl($tableidvalue,1)"!]
                        [!VAR "tableidvalue" = "bit:bitset($tableidvalue,30)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:shl($tablefiltermaskvalue,1)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue,num:hextoint('0xc0000000'))"!]
                    [!ENDIF!]
                    [!IF "../../CanControllerIDAcceptanceMode = 'B'"!]
                        [!VAR "tableidvalue0" = "bit:shl($tableidvalue,16)"!]
                        [!VAR "tableidvalue" = "bit:or($tableidvalue0,num:i(CanIDValue1))"!]
                        [!VAR "tableidvalue" = "bit:bitset($tableidvalue,30)"!]
                        [!VAR "tableidvalue" = "bit:bitset($tableidvalue,14)"!]
                        [!VAR "tablefiltermaskvalue0" = "bit:and($tablefiltermaskvalue,num:hextoint('0xfffc000'))"!]
                        [!VAR "tablefiltermaskvalue1" = "bit:and($tablefiltermaskvalue,num:hextoint('0x3fff'))"!]
                        [!VAR "tablefiltermaskvalue0" = "bit:shl($tablefiltermaskvalue0,2)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue0,$tablefiltermaskvalue1)"!]
                        [!VAR "tablefiltermaskvalue" = "bit:or($tablefiltermaskvalue,num:hextoint('0xc000c000'))"!]
                    [!ENDIF!]
                [!ENDIF!]
        [!CODE!]
        {
            /* [!"@name"!] of [!IF "../../CanControllerIDAcceptanceMode != 'C'"!]type [!"(CanTableIDType)"!] and[!ENDIF!] format[!"../../CanControllerIDAcceptanceMode"!] for [!"$ControllerCanHwChannel"!] */
            (uint32)[!"num:inttohex($tableidvalue,8)"!]U,
            /* Filter Mask (correspond to RXIMR register) */
            (uint32)[!"num:inttohex($tablefiltermaskvalue,8)"!]U
        }[!IF "$TableIdCount != $TableIdCountLocal"!],[!ENDIF!][!ENDCODE!]
            [!ENDLOOP!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]};
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */[!ENDCODE!]

    [!ENDIF!]
    [!ENDLOOP!]
    [!ENDNOCODE!]


/*==================================================================================================*/
/**
@brief    Filter Masks
*/
/*==================================================================================================*/
[!LOOP "CanConfigSet/*"!]CONST(Can_IdType, CAN_CONST) Can_FilterMasks[!"@index"!]_PB[CAN_MAXFILTERCOUNT_[!"@index"!]] =
    {   [!VAR "filtermaskcount" = "0"!][!NOCODE!][!VAR "MASK_COUNT"="num:i(count(CanController/*/CanFilterMask/*))"!][!VAR "END_COMMA"="0"!][!ENDNOCODE!][!LOOP "CanController/*"!][!LOOP "CanFilterMask/*"!][!VAR "END_COMMA"="$END_COMMA + 1"!]
        /* FilterMasks0[[!"num:i($filtermaskcount)"!]], "[!"@name"!]" */
        (Can_IdType)[!"num:inttohex(CanFilterMaskValue)"!]U[!NOCODE!][!IF "$END_COMMA < $MASK_COUNT"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!][!VAR "filtermaskcount" = "$filtermaskcount + 1"!][!ENDLOOP!][!ENDLOOP!]
    };

[!ENDLOOP!]


/*==================================================================================================*/
/**
@brief    Information about message buffers
@brief    (CAN100)Several TX hardware objects with unique HTHs may be configured. The CanIf module provides the HTH as parameter of the TX request. See Figure 7-2 for a possible configuration.
@remarks  Covers CAN100
@remarks  Implements DCAN00100
*/
/*==================================================================================================*/
[!LOOP "CanConfigSet/*"!]
CONST(Can_MBConfigObjectType, CAN_CONST) MessageBufferConfigs[!"@index"!]_PB[CAN_MAXMBCOUNT_[!"@index"!]] =
    {
        [!VAR "CanControllerIdValue"="0"!][!VAR "ObjectID"="0"!][!VAR "END_COMMA"="0"!][!VAR "MASK_COUNT"="num:i(count(CanHardwareObject/*))"!][!LOOP "CanHardwareObject/*"!][!VAR "END_COMMA"="$END_COMMA + 1"!]
        [!NOCODE!]
        /*
        When Backwards Compatibility Configuration (BCC) feature of CAN controller is used in the configuration, below should be the
        configuration of CanHardwareObject.

        CanFilterMask configuration in CanController container:
        ========================================================
        CanFilterMask_0
        CanFilterMask_1
        CanFilterMask_3

        CanHardwareObject_0 to CanHardwareObject_13 and CanHardwareObject_16 to CanHardwareObject_32/CanHardwareObject_63:
        ==================================================================================================================
        CanFilterMask_0 should be selected in CanFilterMaskRef

        CanHardwareObject_14 :
        ======================
        CanFilterMask_1 should be selected in CanFilterMaskRef

        CanHardwareObject_15 :
        ======================
        CanFilterMask_2 should be selected in CanFilterMaskRef
        */
        [!VAR "BccSupportStatus"="0"!]
        [!VAR "CanObjectName"="node:name(.)"!]
        [!SELECT "node:ref(CanControllerRef)"!]
         [!IF "CanBccSupport = 'true'"!]
          [!VAR "BccSupportStatus"="1"!]
         [!ENDIF!]
        [!ENDSELECT!]
        [!IF "contains(node:path(node:ref(CanFilterMaskRef)),node:path(node:ref(CanControllerRef)))"!]
        [!ELSE!]
         [!ERROR!]
         Please select below FilterMaskReference from the "[!"substring-after(node:path(node:ref(CanControllerRef)),'ELEMENTS/')"!]" to which "[!"node:name(.)"!]" belongs to.
         [!SELECT "node:ref(CanControllerRef)"!]
          [!LOOP "CanFilterMask/*"!]
           [!"node:name(.)"!]
          [!ENDLOOP!]
         [!ENDSELECT!]
         [!ENDERROR!]
        [!ENDIF!]
       [!IF "$BccSupportStatus = 1"!]
         [!SELECT "node:ref(CanControllerRef)"!]
          [!LOOP "CanFilterMask/*"!]
           [!IF "@index = 0"!]
            [!VAR "FirstFilterMask"="node:name(.)"!]
           [!ELSEIF "@index = 1"!]
            [!VAR "SecondFilterMask"="node:name(.)"!]
           [!ELSEIF "@index = 2"!]
            [!VAR "ThirdFilterMask"="node:name(.)"!]
           [!ENDIF!]
          [!ENDLOOP!]
         [!ENDSELECT!]
         [!SELECT "node:ref(CanFilterMaskRef)"!]
          [!VAR "FilterMaskIndex"="@index"!]
         [!ENDSELECT!]
         [!IF "((num:i($ObjectID) < 14) or (num:i($ObjectID) > 15)) and ($FilterMaskIndex > 0)"!]
         [!ERROR!]
          [!SELECT "node:ref(CanFilterMaskRef)"!] Wrong FilterMask "[!"node:name(.)"!]" is selected for "[!"$CanObjectName"!]".
           Select "[!"$FirstFilterMask"!]" for MB0-MB13 and MB16-MB31(Corresponds to RxGlobalMask).
          [!ENDSELECT!]
         [!ENDERROR!]
         [!ELSEIF "(num:i($ObjectID) = 14) and ($FilterMaskIndex != 1)"!]
         [!ERROR!]
          [!SELECT "node:ref(CanFilterMaskRef)"!] Wrong FilterMask "[!"node:name(.)"!]" is selected for "[!"$CanObjectName"!]".
           Select "[!"$SecondFilterMask"!]" for MB14 (Corresponds to Rx14Mask).
          [!ENDSELECT!]
         [!ENDERROR!]
         [!ELSEIF "(num:i($ObjectID) = 15) and ($FilterMaskIndex != 2)"!]
         [!ERROR!]
          [!SELECT "node:ref(CanFilterMaskRef)"!] Wrong FilterMask "[!"node:name(.)"!]" is selected for "[!"$CanObjectName"!]".
           Select "[!"$ThirdFilterMask"!]" for MB15 (Corresponds to Rx15Mask).
          [!ENDSELECT!]
         [!ENDERROR!]
         [!ENDIF!]
        [!SELECT "node:ref(CanControllerRef)"!]
        [!IF "CanControllerId = num:i($CanControllerIdValue)"!]
         [!VAR "ObjectID"="$ObjectID + 1"!]
        [!ELSE!]
         [!VAR "ObjectID"="0"!]
         [!VAR "CanControllerIdValue"="$CanControllerIdValue + 1"!]
        [!ENDIF!]
        [!ENDSELECT!]
       [!ENDIF!]
        [!ENDNOCODE!]
        /* [!"@name"!] Message Buffer of Can Controller ID = [!SELECT "node:ref(CanControllerRef)"!][!"num:i(CanControllerId)"!]U[!ENDSELECT!] */
        {
            /* IdMaskIndex */
            [!VAR "filtermaskref" = "node:path(node:ref(CanFilterMaskRef))"!][!VAR "filtermaskcount" = "0"!][!LOOP "../../CanController/*"!][!LOOP "CanFilterMask/*"!][!IF "$filtermaskref = node:path(.)"!](Can_HWObjectCountType)[!"num:i($filtermaskcount)"!]U,[!BREAK!][!ENDIF!][!VAR "filtermaskcount" = "$filtermaskcount + 1"!][!ENDLOOP!][!ENDLOOP!]
            /* ControllerId  - based on the order from CanController list */
            [!SELECT "node:ref(CanControllerRef)"!](uint8)[!"num:i(CanControllerId)"!]U,[!ENDSELECT!]
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)[!"CanIdType"!],
            /* Receive/Transmit MB configuration */
            (Can_ObjType)[!"CanObjectType"!],
            /* MessageId */
            (Can_IdType)[!"num:inttohex(CanIdValue)"!]U,
            /* Local priority bits used for arbitration */
            (uint8)[!"num:inttohex(CanMBPrio)"!]U,
            /* Hardware Object ID */
            (Can_HWObjectCountType)[!"num:inttohex(CanObjectId)"!]U
        }[!NOCODE!][!IF "$END_COMMA < $MASK_COUNT"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!]
        [!ENDLOOP!]
    };
[!ENDLOOP!]

/*==================================================================================================*/
/**
@brief    Configuration of FlexCan controllers
*/
/*==================================================================================================*/
[!LOOP "CanConfigSet/*"!][!VAR "LoopVar"="0"!]
CONST(Can_ControllerConfigType, CAN_CONST) ControllerConfigs[!"@index"!]_PB[CAN_MAXCONTROLLERCOUNT_[!"@index"!]] = {
    [!NOCODE!][!VAR "MASK_COUNT2"="num:i(count(CanController/*))"!][!VAR "END_COMMA2"="0"!][!ENDNOCODE!]
    [!FOR "x" = "0" TO "num:i(count(CanController/*))"!]
        [!LOOP "CanController/*"!][!VAR "Loop"="num:i($LoopVar)"!]
            [!IF "CanControllerId = $Loop"!][!VAR "END_COMMA2"="$END_COMMA2 + 1"!]
    [!NOCODE!]
        [!/*
        Sync-seg = is the segment that is used to synchronise the nodes on the bus. A bit edge (if there is a data change) is expected during this segment.
        Prop-Seg = is a period of time that is used to compensate for physical delay times within the network.
        Phase-seg1 = is a buffer segment that may be lengthened during resynchronisation to compensate for oscillator drift and positive phase differences between the oscillators of the transmitting and receiving node(s).
        Phase-seg2 = is a buffer segment that may be shortened during resynchronisation (described below) to compensate for negative phase errors and oscillator drift.

        The Sample point is always at the end of Phase-seg1 and is the time at which the bus level is read and interpreted as the value of the current bit.
        Whether transmitting or receiving, all nodes on a single CAN bus must have the same nominal bit time. Bit time is programmable at each node on a CAN Bus and is a function
            of the period of the oscillator local to each node, the value that is user-programmed into a Baud Rate Prescaler (BRP) register in the controller at each node, and the programmed number of time quanta per bit.

        When any node receives a data frame or a remote frame, it is necessary for the receiver to synchronise with the transmitter.
            1. The first is hard synchronisation and occurs at Start-of-Frame (SOF).
            2. For subsequent bits in any received frame, if a bit edge does not occur in the Sync-seg segment of bit time, resynchronisation is automatically invoked and will shorten or lengthen the current bit time depending
                on where the edge occurs. The maximum amount by which the bit time is lengthened or shortened is determined by a user-programmable number of time quanta known as the Synchronisation Jump Width (SJW).
        */!]
        [!/* Make the selection of source clock: from MCU or from CAN bus. */!]
        [!IF "CanClockFromBus"!][!/* Select the source for Can module */!]
            [!VAR "CANClockFrequencyFromMcu" = "0"!]
            [!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]
                [!VAR "CANClockFrequencyFromMcu_Alternate" = "0"!]
            [!ENDIF!][!ENDIF!]
            [!NOCODE!][!CALL "CanClockFrequency_M"!][!ENDNOCODE!]
            [!VAR "CANClockFrequency" = "$CANClockFrequencyFromMcu"!][!/* Get the clock from MCU */!]
            [!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]
                [!VAR "CANClockFrequency_Alternate" = "$CANClockFrequencyFromMcu_Alternate"!][!/* Get the clock from MCU */!]
            [!ENDIF!][!ENDIF!]
        [!ELSE!]
            [!NOCODE!][!CALL "CanOscillatorFrequency_M"!][!ENDNOCODE!]
            [!VAR "CANClockFrequency" = "$CanCrystalFrequency"!][!/* Get the value from extern OSC without Mcu connection */!]
        [!ENDIF!]

        [!/* Calculate the prescaler in background based on Clock source and Time Quantum */!]
        [!VAR "Prescaler" = "num:i(round(num:i($CANClockFrequency) * (CanControllerTimeQuanta div 1000000000)))"!][!/* Calculate Prescaler value. CANClockFrequency is in Mhz/Khz/Hz. CanControllerTimeQuanta is in ns. */!]
        [!IF "($Prescaler < 1) or ($Prescaler > 256)"!]
            [!ERROR!]
                Invalid CAN Prescaler value: [!"$Prescaler"!]. Can Prescaler must be in 1 - 256 range. Increase CanClock or CanControllerTimeQuanta.
                Current CanClock is [!"$CANClockFrequency"!] Hz and CanControllerTimeQuanta is [!"num:i(CanControllerTimeQuanta)"!] ns.
                Prescaler = CANClockFrequency * (CanControllerTimeQuanta / 1000000000). CANClockFrequency Hz. CanControllerTimeQuanta is in ns.
            [!ENDERROR!]
        [!ENDIF!]

        [!IF "CanClockFromBus"!][!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]
            [!VAR "Prescaler_Alternate" = "num:i(round(num:i($CANClockFrequency_Alternate) * (CanControllerTimeQuanta_Alt div 1000000000)))"!][!/* Calculate Prescaler value. CANClockFrequency is in Mhz/Khz/Hz. CanControllerTimeQuanta is in ns. */!]
            [!IF "($Prescaler_Alternate < 1) or ($Prescaler_Alternate > 256)"!]
                [!ERROR!]
                    Invalid CAN Prescaler value: [!"$Prescaler_Alternate"!]. Can Prescaler must be in 1 - 256 range. Increase Can source Clock or CanControllerTimeQuanta_Alt.
                    Current CanClock is [!"$CANClockFrequency_Alternate"!] Hz and CanControllerTimeQuanta_Alt is [!"num:i(CanControllerTimeQuanta_Alt)"!] ns.
                    Prescaler_Alternate = CANClockFrequency_Alternate * (CanControllerTimeQuanta_Alt / 1000000000). CANClockFrequency=[Hz]. CanControllerTimeQuanta=[ns].
                [!ENDERROR!]
            [!ENDIF!]
            [!/* Calculate how many Tq has a CAN bit */!]
            [!VAR "CANTimeQuanta_Alternate" = "num:i(round((1 div (num:i(CanControllerBaudRate) * 1000)) div (CanControllerTimeQuanta_Alt div 1000000000)))"!]
            [!/* Check the number Time Quanta per bit to be in the valid 8 - 25 interval  */!]
            [!IF "($CANTimeQuanta_Alternate < 8) or ($CANTimeQuanta_Alternate > 25)"!]
                [!ERROR!]
                    For CanController [!"CanHwChannel"!], the desired CAN bus Nominal Bit Time (NBT) should be an integer number of Time Quanta (CAN system clock periods) from 8 to 25.
                    Current No of CanTimeQuantas = [!"num:i($CANTimeQuanta_Alternate)"!]   --->>> OUT of RANGE [8-25]
                    No of CanTimeQuantas = (1 / CanControllerBaudRate) / CanControllerTimeQuanta_Alt;
                [!ENDERROR!]
            [!ENDIF!]
        [!ENDIF!][!ENDIF!][!ENDIF!]

        [!/* Calculate the Number of Tq/Can bit for the current baud rate and clock selection. */!]
        [!IF "($Prescaler >= 1) or ($Prescaler <= 256)"!][!/* Having a value of 0 for this variable, means Sclock=CPI/0, which is not ok. */!]
            [!/* Calculate how many Tq has a CAN bit */!]
            [!VAR "CANTimeQuanta" = "num:i(round((1 div (num:i(CanControllerBaudRate) * 1000)) div (CanControllerTimeQuanta div 1000000000)))"!]
            [!/* Check the number Time Quanta per bit to be in the valid 8 - 25 interval  */!]
            [!IF "($CANTimeQuanta < 8) or ($CANTimeQuanta > 25)"!]
                [!ERROR!]
                    For CanController [!"CanHwChannel"!], the desired CAN bus Nominal Bit Time (NBT) should be an integer number of Time Quanta (CAN system clock periods) from 8 to 25.
                    Current No of CanTimeQuantas = [!"num:i($CANTimeQuanta)"!]   --->>> OUT of RANGE [8-25]
                    No of CanTimeQuantas = (1 / CanControllerBaudRate) / CanControllerTimeQuanta;
                [!ENDERROR!]
            [!ENDIF!]

            [!IF "CanAdvancedSetting = 'false'"!]
            [!/* User will set the time segments. If wants  can validate or not the verification. */!]
                [!IF "CanControllerCheckCanStandard"!]
                    [!/* Check the CAN bit time compliance  - get the values from Tresos interface and check.*/!]
                    [!VAR "NoTimeQuantas"= "num:i($Tsyncsegment + num:i(CanControllerPropSeg) + num:i(CanControllerSeg1) + 2 + num:i(CanControllerSeg2) + 1)"!]
                    [!VAR "TimeSegment1" = "num:i(num:i(CanControllerPropSeg) + num:i(CanControllerSeg1) + 2)"!]
                    [!VAR "TimeSegment2" = "num:i(num:i(CanControllerSeg2) + 1)"!]

                    [!IF "($TimeSegment2 < 2) or ($TimeSegment2 > 8)"!]
                        [!ERROR!]
                            TimeSegment2 [=CanControllerSeg2] should be between [2 .. 8], current value is [!"num:i($TimeSegment2)"!]
                        [!ENDERROR!]
                    [!ENDIF!]
                    [!/* TimeSegment1: [5..10], TimeSegment2: 2, ResynchronizationJumpWidth: [1..2] */!]
                    [!IF "$TimeSegment2 = 2"!]
                        [!IF "(num:i($TimeSegment1) < 5) or (num:i($TimeSegment1) > 10)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [5 .. 10], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 2)"!]
                            [!ERROR!]If TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 2] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [4..11], TimeSegment2: 3, ResynchronizationJumpWidth: [1 .. 3] */!]
                    [!IF "$TimeSegment2 = 3"!]
                        [!IF "(num:i($TimeSegment1) < 4) or (num:i($TimeSegment1) > 11)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [4 .. 11], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 3)"!]
                            [!ERROR!]If TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 3] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [5..12], TimeSegment2: 4, Re-synchronizationJumpWidth: [1 .. 4] */!]
                    [!IF "$TimeSegment2 = 4"!]
                        [!IF "(num:i($TimeSegment1) < 5) or (num:i($TimeSegment1) > 12)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [5 .. 12], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 4)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 4] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [6..13], TimeSegment2: 5, ResynchronizationJumpWidth: [1..4] */!]
                    [!IF "$TimeSegment2 = 5"!]
                        [!IF "(num:i($TimeSegment1) < 6) or (num:i($TimeSegment1) > 13)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [6 .. 13], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 4)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 4] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [7..14], TimeSegment2: 6, ResynchronizationJumpWidth: [1..4] */!]
                    [!IF "$TimeSegment2 = 6"!]
                        [!IF "(num:i($TimeSegment1) < 7) or (num:i($TimeSegment1) > 14)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [7 .. 14], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 4)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 4] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [8..15], TimeSegment2: 7, ResynchronizationJumpWidth: [1..4] */!]
                    [!IF "$TimeSegment2 = 7"!]
                        [!IF "(num:i($TimeSegment1) < 8) or (num:i($TimeSegment1) > 15)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [8 .. 15], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 4)"!]
                            [!ERROR!]When TimeSegment2 [=anControllerSeg2+1] is [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 4] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!/* TimeSegment1: [9..16], TimeSegment2: 8, ResynchronizationJumpWidth: [1..4] */!]
                    [!IF "$TimeSegment2 = 8"!]
                        [!IF "(num:i($TimeSegment1) < 9) or (num:i($TimeSegment1) > 16)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] was [!"num:i(num:i(CanControllerSeg2)+1)"!], TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [9 .. 16], current value is [!"num:i($TimeSegment1)"!].[!ENDERROR!]
                        [!ENDIF!]
                        [!IF "((CanSyncJumpWidth+1) < 1) or ((CanSyncJumpWidth+1) > 4)"!]
                            [!ERROR!]When TimeSegment2 [=CanControllerSeg2+1] was [!"num:i(num:i(CanControllerSeg2)+1)"!], (CanSyncJumpWidth+1) should be between [1 .. 4] instead of [!"CanSyncJumpWidth"!]+1.[!ENDERROR!]
                        [!ENDIF!]
                    [!ENDIF!]

                    [!IF "($TimeSegment1 < 4) or ($TimeSegment1 > 16)"!]
                        [!ERROR!]TimeSegment1 [= CanControllerPropSeg + CanControllerSeg1 + 2] should be between [4 .. 16], current value is [!"num:i($TimeSegment1)"!][!ENDERROR!]
                    [!ENDIF!]

                    [!IF "($NoTimeQuantas < 8) or ($NoTimeQuantas > 25)"!]
                        [!ERROR!]No of CanTimeQuantas should be between [8 .. 25], current value is [!"num:i($NoTimeQuantas)"!].
                        BitTimeQuanta = SyncSeg + PropSeg + PSEG1 + 2 + PSEG2 + 1.
                        SyncSeg = 1. PropSeg = [!"num:i(CanControllerPropSeg)"!]. PSEG1 = [!"num:i(CanControllerSeg1)"!]. PSEG2 = [!"num:i(CanControllerSeg2)"!].[!ENDERROR!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ELSE!]
                [!/* Initiates the derivation of the CAN bit timing values from the CanControllerBaudRate parameter. */!]
                [!VAR "BusPropogationDelay" ="5 div 1000000000"!][!/* Hard coded to 5ns/m. */!]
                [!VAR "PhysicalDelayOfBus"="CanBusLength * $BusPropogationDelay"!]
                [!/* Tprop_seg=TpropAB + TpropBA = 2 * (Tbus + Trx + Ttx). Ussually Trx=Ttx. */!]
                [!VAR "Tpropogationsegment"="2*($PhysicalDelayOfBus + 2 * (CanPropDelayTranceiver div 1000000000))"!]
                [!VAR "PropogationSegment"="round($Tpropogationsegment div (CanControllerTimeQuanta div 1000000000))"!]

                [!IF "($PropogationSegment >= 0) and ($PropogationSegment <= 7)"!]
                    [!VAR "PhaseSegments" = "($CANTimeQuanta - $PropogationSegment - $Tsyncsegment - 3)"!]
                    [!IF "$PhaseSegments >= 3"!]
                        [!VAR "Modulo" = "$PhaseSegments mod 2"!]
                        [!IF "$Modulo = 0"!]
                            [!VAR "PhaseSegment1" = "num:i($PhaseSegments div 2)"!]
                            [!VAR "PhaseSegment2" = "num:i($PhaseSegment1)"!]
                        [!ELSE!]
                            [!VAR "PhaseSegment1" = "num:i(($PhaseSegments - 1) div 2)"!]
                            [!VAR "PhaseSegment2" = "num:i($PhaseSegment1 + 1)"!]
                        [!ENDIF!]
                        [[!IF "($PhaseSegment1 > 7)"!]
                            [!ERROR!]
                            PropSegment1 is out of range [0:7]. Current value is [!"num:i($PhaseSegment1)"!].
                            The bit length has [!"num:i($CANTimeQuanta)"!] Time Quantas.
                            Propagation Segment based bus length and tranceiver delay has [!"num:i($PropogationSegment)"!] Time Quantas.
                            Need to increase PropogationSegment or to decrease the number of Time Quantas per bit.
                            [!ENDERROR!]
                        [!ENDIF!]
                        [!IF "($PhaseSegment2 < 1) or ($PhaseSegment2 > 7)"!]
                            [!ERROR!]
                            PropSegment2 is out of range [1:7]. Current value is [!"num:i($PhaseSegment2)"!]
                            The bit length has [!"num:i($CANTimeQuanta)"!] Time Quantas.
                            Propagation Segment based bus length and tranceiver delay has [!"num:i($PropogationSegment)"!] Time Quantas.
                            Need to increase PropogationSegment or to decrease the number of Time Quantas per bit.
                            [!ENDERROR!]
                        [!ENDIF!]
                        [!IF "$PhaseSegment1 < 4"!]
                            [!VAR "RJW" = "num:i($PhaseSegment1)"!]
                        [!ELSE!]
                            [!VAR "RJW" = "3"!]
                        [!ENDIF!]
                    [!ELSE!]
                        [!ERROR!] (Phase Segment1+Phase Segment2) must be >= 3. Increase no of CANTimeQuanta ([!"num:i($CANTimeQuanta)"!]) per bit or decrease PropSegment ([!"num:i($PropogationSegment)"!])(based CanBusLength and CanPropDelayTranceiver).[!ENDERROR!]
                    [!ENDIF!]
                [!ELSE!]
                    [!ERROR "Propagation Segment is out of range [0:7]. If >7 then need to increase CanControllerTimeQuanta or decrease CanBusLength/BusPropogationDelay."!]
                [!ENDIF!]

                [!VAR "NoTimeQuantas"= "num:i($Tsyncsegment + $PropogationSegment + 1 + $PhaseSegment1 + 1 + $PhaseSegment2 + 1)"!]
            [!ENDIF!]

            [!IF "CanControllerCheckCanStandard"!]
                [!/* Minimum ratio between the peripheral clock frequency and Can Bit rate Check */!]
                [!VAR "maxmb" = "0"!]
                [!LOOP "../../CanHardwareObject/*"!]
                    [!SELECT "node:ref(CanControllerRef)"!]
                        [!IF "num:i(CanControllerId) = num:i($x)"!]
                            [!VAR "maxmb" = "$maxmb+1"!]
                        [!ENDIF!]
                    [!ENDSELECT!]
                [!ENDLOOP!]

                [!IF "num:i($maxmb) <= 16"!]
                    [!IF "($NoTimeQuantas * $Prescaler < 8)"!]
                        [!ERROR!]When CanMessageBufferCount is <=16, Prescaler is [!"num:i($Prescaler)"!], No of CanTimeQuantas is [!"num:i($NoTimeQuantas)"!],
                        Minimum Ratio should be 8, current value is [!"num:i($NoTimeQuantas * $Prescaler)"!].
                        Increase Prescaler or NoTimeQuantas values.[!ENDERROR!]
                    [!ENDIF!]
                [!ENDIF!]

                [!IF "(num:i($maxmb) > 16) and (num:i($maxmb) <= 32)"!]
                    [!IF "($NoTimeQuantas * $Prescaler < 8)"!]
                        [!ERROR!]When CanMessageBufferCount is >16 and <=32, Prescaler is [!"num:i($Prescaler)"!], No of CanTimeQuantas is [!"num:i($NoTimeQuantas)"!],
                        Minimum Ratio should be 8, current value is [!"num:i($NoTimeQuantas * $Prescaler)"!].
                        Increase Prescaler or NoTimeQuantas values.[!ENDERROR!]
                    [!ENDIF!]
                [!ENDIF!]

                [!IF "(num:i($maxmb) > 32) and (num:i($maxmb) <= 64)"!]
                    [!IF "($NoTimeQuantas * $Prescaler < 16)"!]
                        [!ERROR!]When CanMessageBufferCount is >32 and <=64, Prescaler is [!"num:i($Prescaler)"!], No of CanTimeQuantas is [!"num:i($NoTimeQuantas)"!],
                        Minimum Ratio should be 16, current value is [!"num:i($NoTimeQuantas * $Prescaler)"!].
                        Increase Prescaler or NoTimeQuantas values.[!ENDERROR!]
                    [!ENDIF!]
                [!ENDIF!]

                [!IF "num:i($CANTimeQuanta) != num:i($NoTimeQuantas)"!]
                    [!WARNING!] The No of CanTimeQuantas set by you ([!"$NoTimeQuantas"!]) is different by No of CanTimeQuantas calculated from clock settings ([!"num:i($CANTimeQuanta)"!]).
                        NoTimeQuantas = SyncSeg + PropSeg + PSEG1 + 2 + PSEG2 + 1 (from user settings).
                        NoCANTimeQuantas = (1 / CanControllerBaudRate) / CanControllerTimeQuanta;
                    [!ENDWARNING!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDNOCODE!]/*
        =================================================
        Clock Size = [!"$CANClockFrequency"!] Hz [!IF "CanClockFromBus"!] - Clock from MCU. [!ELSE!] - Clock from external OSC.[!ENDIF!]
        [!IF "CanClockFromBus"!][!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]Clock Size Alternate = [!"$CANClockFrequency_Alternate"!] Hz [!IF "CanClockFromBus"!] - Clock from MCU. [!ELSE!] - Clock from external OSC.[!ENDIF!] [!ENDIF!][!ENDIF!][!ENDIF!]
        Clock Prescaler = [!"$Prescaler"!] (1..256)
        [!IF "CanClockFromBus"!][!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]Clock Prescaler_Alternate = [!"$Prescaler_Alternate"!] (1..256)[!ENDIF!][!ENDIF!][!ENDIF!]
        CanBitRate = [!"CanControllerBaudRate"!] Kbps (1bps..1Mbps)
        Number CANTimeQuantas per bit = [!"$CANTimeQuanta"!] (8..25)
        [!IF "CanClockFromBus"!][!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]Number CANTimeQuantas_Alternate per bit = [!"$CANTimeQuanta_Alternate"!] (8..25)[!ENDIF!][!ENDIF!][!ENDIF!]
        CTRL Register Fields:
            PSEG1 = [!IF "CanAdvancedSetting"!][!"$PhaseSegment1"!][!ELSE!][!"CanControllerSeg1"!][!ENDIF!] (0..7)
            PSEG2 = [!IF "CanAdvancedSetting"!][!"$PhaseSegment2"!][!ELSE!][!"CanControllerSeg2"!][!ENDIF!] (1..7)
            PROPSEG = [!IF "CanAdvancedSetting"!][!"num:i($PropogationSegment)"!][!ELSE!][!"num:i(CanControllerPropSeg)"!][!ENDIF!] (0..7)
            RJW = [!IF "CanAdvancedSetting"!][!"$RJW"!][!ELSE!][!"CanSyncJumpWidth"!][!ENDIF!] (0..3)
        =================================================
    */
    [!IF "CanControllerActivation = 'true'"!]
    /* Configuration for CanController ID[!"num:i(CanControllerId)"!] == [!"CanHwChannel"!] */
    {
      /* ===== Control Register - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)(([!"num:i(num:i($Prescaler) - 1)"!]U << FLEXCAN_CTRL_PRESDIV_SHIFT) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanSyncJumpWidth)"!][!ELSE!][!"num:i($RJW)"!][!ENDIF!]U << FLEXCAN_CTRL_RJW_SHIFT) |
        /* CTRL[PSEG1] - Segment 1 */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerSeg1)"!][!ELSE!][!"num:i($PhaseSegment1)"!][!ENDIF!]U << FLEXCAN_CTRL_PSEG1_SHIFT) |
        /* CTRL[PSEG2] - Segment 2 */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerSeg2)"!][!ELSE!][!"num:i($PhaseSegment2)"!][!ENDIF!]U << FLEXCAN_CTRL_PSEG2_SHIFT) |
        /* CTRL[CLK_SRC] - Clock source */
        ([!IF "CanClockFromBus = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_CLKSRC_SHIFT) |
        /* CTRL[LPB] - Loop-back mode */
        ([!IF "CanLoopBackMode = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LPB_SHIFT) |
        /* CTRL[SMP] - Sampling mode */
        ([!IF "CanTrippleSamplingEnable = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_SMP_SHIFT) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        ([!IF "CanAutoBusOffRecovery = 'true'"!]0U[!ELSE!]1U[!ENDIF!] << FLEXCAN_CTRL_BOFFREC_SHIFT) |
        /* CTRL[LBUF] - Lowest Buffer Transmitted First */
        ([!IF "CanLowestBuffTransmitFirst = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LBUF_SHIFT) |
        /* CTRL[LOM] - Listen only mode */
        ([!IF "CanListenOnlyMode = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LOM_SHIFT) |
        /* CTRL[PROPSEG] - Propagation segment */
        [!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerPropSeg)"!][!ELSE!][!"num:i($PropogationSegment)"!][!ENDIF!]U) ,

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
    [!IF "CanClockFromBus"!][!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]
      /* ===== Control Register Alternate - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)(([!"num:i(num:i($Prescaler_Alternate) - 1)"!]U << FLEXCAN_CTRL_PRESDIV_SHIFT) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanSyncJumpWidth)"!][!ELSE!][!"num:i($RJW)"!][!ENDIF!]U << FLEXCAN_CTRL_RJW_SHIFT) |
        /* CTRL[PSEG1] - Segment 1 */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerSeg1)"!][!ELSE!][!"num:i($PhaseSegment1)"!][!ENDIF!]U << FLEXCAN_CTRL_PSEG1_SHIFT) |
        /* CTRL[PSEG2] - Segment 2 */
        ([!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerSeg2)"!][!ELSE!][!"num:i($PhaseSegment2)"!][!ENDIF!]U << FLEXCAN_CTRL_PSEG2_SHIFT) |
        /* CTRL[CLK_SRC] - Clock source */
        ([!IF "CanClockFromBus = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_CLKSRC_SHIFT) |
        /* CTRL[LPB] - Loop-back mode */
        ([!IF "CanLoopBackMode = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LPB_SHIFT) |
        /* CTRL[SMP] - Sampling mode */
        ([!IF "CanTrippleSamplingEnable = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_SMP_SHIFT) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        ([!IF "CanAutoBusOffRecovery = 'true'"!]0U[!ELSE!]1U[!ENDIF!] << FLEXCAN_CTRL_BOFFREC_SHIFT) |
        /* CTRL[LBUF] - Lowest Buffer Transmitted First */
        ([!IF "CanLowestBuffTransmitFirst = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LBUF_SHIFT) |
        /* CTRL[LOM] - Listen only mode */
        ([!IF "CanListenOnlyMode = 'true'"!]1U[!ELSE!]0U[!ENDIF!] << FLEXCAN_CTRL_LOM_SHIFT) |
        /* CTRL[PROPSEG] - Propagation segment */
        [!IF "CanAdvancedSetting = 'false'"!][!"num:i(CanControllerPropSeg)"!][!ELSE!][!"num:i($PropogationSegment)"!][!ENDIF!]U) ,
    [!ELSE!]    0U),[!ENDIF!][!ELSE!]0U),[!ENDIF!]
    [!ELSE!]    0U),[!ENDIF!]
        [!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode) and (./../../../../CanGeneral/CanEnableDualClockMode = 'true') and (CanClockFromBus = 'false')"!]
    [!WARNING!]When dual clock feature is enabled (CanEnableDualClockMode), the clock from MCU should be selected (CanClockFromBus).[!ENDWARNING!][!ENDIF!]
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

      /* ===== Controller Options ===== */
        (uint16)([!IF "CanWakeUpSourceFilter = 'true'"!]/* This setting defines whether the integrated low-pass filter is applied to protect the Rx CAN input from spurious wake up. */[!//
        CAN_CONTROLLERCONFIG_WAKEUP_SRC | [!ENDIF!]
        [!IF "CanSoftwareBusOffRecovery = 'true' "!]/* Software BusOff Recovery */
        CAN_CONTROLLERCONFIG_BUSOFFSWREC | [!ENDIF!]
        [!IF "CanControllerRxFifoEnable = 'true' "!]/* RX Fifo Enabled */
        CAN_CONTROLLERCONFIG_RXFIFO | [!ELSE!] /* RX Fifo Disabled */ [!ENDIF!]
        [!IF "CanLocalPriorityEn = 'true' "!]/* Local Priority Feature */
        CAN_CONTROLLERCONFIG_LPRIO_EN | [!ENDIF!]
        [!IF "CanWarningEnable = 'true' "!]/* Warning Interrupt Enable Feature */
        CAN_CONTROLLERCONFIG_WRNINT_EN | [!ENDIF!]
[!IF "CanControllerRxFifoEnable = 'true'"!]#if (CAN_RXFIFO_ENABLE == STD_ON)
        [!IF "(normalize-space(CanRxFifoOverflowNotification) != 'NULL_PTR') and (normalize-space(CanRxFifoOverflowNotification) != '"NULL"') and (normalize-space(CanRxFifoOverflowNotification) != 'NULL')"!]/* Rx Fifo Overflow handling enabled */
        CAN_CONTROLLERCONFIG_OVER_EN | [!ELSE!] /* Rx Fifo Overflow handling disabled */ [!ENDIF!]
        [!IF "(normalize-space(CanRxFifoWarningNotification) != 'NULL_PTR') and (normalize-space(CanRxFifoWarningNotification) != '"NULL"') and (normalize-space(CanRxFifoWarningNotification) != 'NULL')"!]/* Rx Fifo Warning handling enabled */
        CAN_CONTROLLERCONFIG_WARN_EN | [!ELSE!] /* Rx Fifo Warning handling disabled */ [!ENDIF!]
        [!IF "CanRxFifo/CanControllerIDAcceptanceMode = 'A'"!]/* ID Acceptance Mode A */
        CAN_CONTROLLERCONFIG_IDAM_A |
        [!ELSEIF "CanRxFifo/CanControllerIDAcceptanceMode = 'B'"!]/* ID Acceptance Mode B */
        CAN_CONTROLLERCONFIG_IDAM_B |
        [!ELSEIF "CanRxFifo/CanControllerIDAcceptanceMode = 'C'"!]/* ID Acceptance Mode C */
        CAN_CONTROLLERCONFIG_IDAM_C |
        [!ELSEIF "CanRxFifo/CanControllerIDAcceptanceMode = 'D'"!]/* ID Acceptance Mode D: All frames rejected */
        CAN_CONTROLLERCONFIG_IDAM_D | [!ENDIF!]
#endif[!ENDIF!]
        [!IF "CanRxProcessing = 'Polling'"!]/* RxPoll Enabled */
        CAN_CONTROLLERCONFIG_RXPOL_EN | [!ELSE!]/* Rx select by interrupt */[!ENDIF!]
        [!IF "CanTxProcessing = 'Polling'"!]/* TxPoll Enabled */
        CAN_CONTROLLERCONFIG_TXPOL_EN | [!ELSE!]/* Tx select by interrupt */[!ENDIF!]
        [!IF "CanBusoffProcessing = 'Polling'"!]/* BusOffPoll Enabled */
        CAN_CONTROLLERCONFIG_BOPOL_EN | [!ELSE!]/* BusOff select by interrupt */[!ENDIF!]
#if (CAN_WAKEUP_SUPPORT == STD_ON)
        [!IF "CanWakeupProcessing = 'Polling'"!]/* WakeupPoll Enabled */
        CAN_CONTROLLERCONFIG_WKPOL_EN | [!ELSE!] /* Wakeup select by interrupt */[!ENDIF!]
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
[!IF "CanBccSupport = 'true'"!]#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
        CAN_CONTROLLERCONFIG_BCC_EN |
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */[!ELSE!][!ENDIF!]
        0U),
#if (CAN_MIX_MB_SUPPORT == STD_ON)
         /* Maximum MBs supported for this controller. */
         [!IF "ecu:get('Can.CanConfig.MixMB')='STD_ON'"!]
            [!IF "CanHwChannel = 'FlexCAN_A'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 0]"!]U,
            [!ELSEIF "CanHwChannel = 'FlexCAN_B'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 1]"!]U,
            [!ELSEIF "CanHwChannel = 'FlexCAN_C'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 2]"!]U,
            [!ELSEIF "CanHwChannel = 'FlexCAN_D'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 3]"!]U,
            [!ELSEIF "CanHwChannel = 'FlexCAN_E'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 4]"!]U,
            [!ELSEIF "CanHwChannel = 'FlexCAN_F'"!](uint8)[!"text:split(ecu:get('Can.CanConfigSet.CanController.NoMB'), ',')[position()-1 = 5]"!]U,
            [!ENDIF!]
         [!ELSE!]
           (uint8)32U,
         [!ENDIF!]
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
    }[!NOCODE!][!IF "$END_COMMA2 < $MASK_COUNT2"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!]
    [!ELSE!]{
      /* [!"CanHwChannel"!] ControlRegister Default Configuration: 125 Kbps BaudRate with Oscillator clock 8MHz as Clock source and TimeQuantum of 1000ns. */
      /* ===== Control Register - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)((7U << FLEXCAN_CTRL_PRESDIV_SHIFT) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        (2U << FLEXCAN_CTRL_RJW_SHIFT) |
        /* CTRL[PSEG1] - Segment 1 */
        (2U << FLEXCAN_CTRL_PSEG1_SHIFT) |
        /* CTRL[PSEG2] - Segment 2 */
        (2U << FLEXCAN_CTRL_PSEG2_SHIFT) |
        /* CTRL[CLK_SRC] - Clock source */
        (0U << FLEXCAN_CTRL_CLKSRC_SHIFT) |
        /* CTRL[LPB] - Loop-back mode */
        (0U << FLEXCAN_CTRL_LPB_SHIFT) |
        /* CTRL[SMP] - Sampling mode */
        (0U << FLEXCAN_CTRL_SMP_SHIFT) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        (1U << FLEXCAN_CTRL_BOFFREC_SHIFT) |
        /* CTRL[LBUF]  - Lowest Buffer Transmitted First */
        (0U << FLEXCAN_CTRL_LBUF_SHIFT) |
        /* CTRL[LOM] - Listen only mode */
        (0U << FLEXCAN_CTRL_LOM_SHIFT) |
        /* CTRL[PROPSEG] - Propagation segment */
        0U) ,

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
      /* ===== Control Register Alternate - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)((7U << FLEXCAN_CTRL_PRESDIV_SHIFT) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        (2U << FLEXCAN_CTRL_RJW_SHIFT ) |
        /* CTRL[PSEG1] - Segment 1 */
        (2U << FLEXCAN_CTRL_PSEG1_SHIFT) |
        /* CTRL[PSEG2] - Segment 2 */
        (2U << FLEXCAN_CTRL_PSEG2_SHIFT) |
        /* CTRL[CLK_SRC] - Clock source */
        (0U << FLEXCAN_CTRL_CLKSRC_SHIFT) |
        /* CTRL[LPB] - Loop-back mode */
        (0U << FLEXCAN_CTRL_LPB_SHIFT) |
        /* CTRL[SMP] - Sampling mode */
        (0U << FLEXCAN_CTRL_SMP_SHIFT) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        (1U << FLEXCAN_CTRL_BOFFREC_SHIFT) |
        /* CTRL[LBUF]  - Lowest Buffer Transmitted First */
        (0U << FLEXCAN_CTRL_LBUF_SHIFT) |
        /* CTRL[LOM] - Listen only mode */
        (0U << FLEXCAN_CTRL_LOM_SHIFT) |
        /* CTRL[PROPSEG] - Propagation segment */
        0U) ,
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

      /* ===== Controller Options ===== */
        (uint8)0U,

#if (CAN_MIX_MB_SUPPORT == STD_ON)
        /* Maximum MBs supported for this controller. */
        (uint8)32U,
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */

    }[!NOCODE!] [!IF "$END_COMMA2 < $MASK_COUNT2"!] [!CODE!],[!ENDCODE!] [!ELSE!] [!ENDIF!][!ENDNOCODE!]
    [!ENDIF!]
    [!ENDIF!][!ENDLOOP!][!VAR "LoopVar" = "$LoopVar + 1"!][!ENDFOR!]
};
[!ENDLOOP!]


/*==================================================================================================*/
/**
@brief    Description of individual FlexCan controllers on chip
*/
/*==================================================================================================*/
[!NOCODE!][!VAR "ext_wak" = "0"!]
[!IF "ecu:get('Can.CanConfig.ExternalWakeupSupport')='STD_ON'"!]
            [!VAR "ext_wak" = "1"!]
[!ENDIF!][!ENDNOCODE!]
[!LOOP "CanConfigSet/*"!]CONST(Can_ControlerDescriptorType, CAN_CONST) ControlerDescriptors[!"@index"!]_PB[CAN_MAXCONTROLLERCOUNT_[!"@index"!]] =
    {   [!NOCODE!][!VAR "MASK_COUNT4"="num:i(count(CanController/*))"!][!VAR "END_COMMA4"="0"!][!ENDNOCODE!][!VAR "tableidcount" = "0"!]
        [!FOR "controllerid" = "0" TO "num:i(count(CanController/*) - 1)"!][!VAR "controllercount" = "0"!][!LOOP "CanController/*"!][!IF "CanControllerActivation = 'true' and CanControllerId = $controllerid"!][!VAR "END_COMMA4"="$END_COMMA4 + 1"!]/* ControlerDescriptor of [!"@name"!] */
        {
            /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. */
            [!IF "CanControllerActivation = 'true'"!]FLEXCAN_[!"substring-after(CanHwChannel,'FlexCAN_')"!]_OFFSET,[!ELSE!]FLEXCAN_NULL_OFFSET,[!ENDIF!]

            /* No. of Message Buffers for current controller */
            [!NOCODE!][!VAR "maxmbcount" = "0"!][!LOOP "../../CanHardwareObject/*"!][!SELECT "node:ref(CanControllerRef)"!][!IF "num:i(CanControllerId) = num:i($controllerid)"!][!VAR "maxmbcount" = "$maxmbcount+1"!][!ENDIF!][!ENDSELECT!][!ENDLOOP!][!ENDNOCODE!]
            [!IF "CanControllerRxFifoEnable = 'true'"!][!VAR "maxmbcount" = "$maxmbcount+8"!][!ENDIF!](uint8)[!"num:i($maxmbcount)"!]U,
            [!IF "$maxmbcount>ecu:get('Can.CanConfigSet.CanMB')"!][!ERROR!]Maximum MBs + RxFifo (if enabled) exceed [!"ecu:get('Can.CanConfigSet.CanMB')"!] space.[!ENDERROR!][!ENDIF!]

            [!NOCODE!]
            [!VAR "firsthrh" = "num:i(num:i(count(../../CanHardwareObject/*))+1)"!]
            [!VAR "firsthth" = "num:i(num:i(count(../../CanHardwareObject/*))+1)"!]
            [!VAR "hrhcount" = "0"!]
            [!FOR "canhwobjectid" = "0" TO "num:i(count(../../CanHardwareObject/*))-1"!]
                [!LOOP "../../CanHardwareObject/*"!]
                    [!IF "CanObjectId = $canhwobjectid"!]
                        [!IF "CanObjectType = 'RECEIVE'"!]
                            [!SELECT "node:ref(CanControllerRef)"!]
                                [!IF "num:i(CanControllerId) = $controllerid"!]
                                    [!IF "$firsthrh > $canhwobjectid"!]
                                        [!VAR "firsthrh" = "$canhwobjectid"!]
                                    [!ENDIF!]
                                    [!VAR "hrhcount" = "$hrhcount + 1"!]
                                [!ENDIF!]
                            [!ENDSELECT!]
                        [!ELSE!]
                            [!SELECT "node:ref(CanControllerRef)"!]
                                [!IF "num:i(CanControllerId) = $controllerid and $firsthth > $canhwobjectid"!]
                                    [!VAR "firsthth" = "$canhwobjectid"!]
                                [!ENDIF!]
                            [!ENDSELECT!]
                        [!ENDIF!]
                        [!BREAK!]
                    [!ENDIF!]
                [!ENDLOOP!]
            [!ENDFOR!]
            [!ENDNOCODE!]
            /* HthOffset - (FirstHTH - No.of Rx MBs) */
            (Can_HWObjectCountType)[!"num:i($firsthth - $hrhcount)"!]U,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* WakeUp source ID (ECU State Manager) */
            [!IF "node:refexists(CanWakeupSourceRef)"!][!SELECT "node:ref(CanWakeupSourceRef)"!][!CODE!](uint32)[!"num:i(EcuMWakeupSourceId)"!]U,[!ENDCODE!][!ENDSELECT!][!ELSE!][!CODE!](uint8)0U, /* EcuM source not used */[!ENDCODE!][!ENDIF!]
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /* TableID Controller index */
            [!NOCODE!][!IF "CanControllerRxFifoEnable = 'true'"!][!VAR "tableidcontrollerindex" = "$tableidcount"!][!VAR "tableidcount" = "$tableidcount+8"!][!ELSE!][!VAR "tableidcontrollerindex" = "0"!][!ENDIF!][!ENDNOCODE!]
            (uint8)[!"num:i($tableidcontrollerindex)"!]U,

            /* Pointer to RxFifo Overflow notification function. */
            [!IF "CanControllerRxFifoEnable = 'true'"!](Can_PCallBackType)[!"normalize-space(CanRxFifoOverflowNotification)"!],[!ELSE!](Can_PCallBackType)NULL_PTR,[!ENDIF!]

            /* Pointer to RxFifo Warning notification function. */
            [!IF "CanControllerRxFifoEnable = 'true'"!](Can_PCallBackType)[!"normalize-space(CanRxFifoWarningNotification)"!],[!ELSE!](Can_PCallBackType)NULL_PTR,[!ENDIF!]
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

            /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */
            (Can_PCallBackType)[!"normalize-space(CanErrorControllerNotification)"!],

#if (CAN_WAKEUP_SUPPORT == STD_ON)
    #if (CAN_WKP_EXT_SUPPORT == STD_ON)
            /* WKPU source */
            [!IF "$ext_wak = 1"!](uint8)[!"substring-after(CanControllerExternalWakeupCh,'WKPU')"!]U,[!ELSE!](uint8)0U, /* External Wakeup not used */[!ENDIF!]
    #endif /*  (CAN_WKP_EXT_SUPPORT == STD_ON)*/
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
        }[!NOCODE!][!IF "$END_COMMA4 < $MASK_COUNT4"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!]  /* ControlerDescriptors[[!"num:i($controllerid)"!]] end */[!BREAK!][!ENDIF!][!VAR "controllercount" = "$controllercount + 1"!][!ENDLOOP!]
        [!IF "$controllercount = num:i(count(CanController/*))"!]/* ControlerDescriptor of [!"@name"!] */
        {
            /* Can Controller Offset */
            (uint8)FLEXCAN_NULL_OFFSET,

            /* Max Message Buffer number */
            (uint8)0U,

            /* HthOffset - (FirstHTH - No.of Rx MBs) */
            (uint8)0U,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* WakeUp source ID as defined in the ECU State Manager */
            (uint8)0U,
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
            (uint8)0U,
    #endif /*  (CAN_WKP_EXT_SUPPORT == STD_ON)*/
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
        }[!NOCODE!][!IF "$END_COMMA4 < $MASK_COUNT4"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!]

    [!ENDIF!][!ENDFOR!]
    };
[!ENDLOOP!]


/*==================================================================================================*/
/**
@brief    Top level structure containing all can driver configurations
*/
/*==================================================================================================*/
[!LOOP "CanConfigSet/*"!]CONST(Can_ConfigType, CAN_CONST) [!"@name"!] =
    {
        /* Number of CAN controllers configured */
       (uint8) [!"num:i(count(CanController/*))"!]U,

        /* FilterMasksPtr */
       (Can_IdPtrType) Can_FilterMasks[!"@index"!]_PB,

        /* ControllerConfigsPtr */
        ControllerConfigs[!"@index"!]_PB,

        /* MessageBufferConfigContainer */
        {
            /* MessageBufferConfigsPtr */
            MessageBufferConfigs[!"@index"!]_PB,

            /* MessageBufferConfigCount */
            (Can_HWObjectCountType)[!"num:i(count(CanHardwareObject/*))"!]U,
        },

        /* FlexCAN controller description */
        ControlerDescriptors[!"@index"!]_PB,

#if (CAN_RXFIFO_ENABLE == STD_ON)
        /* Can_RxFiFoTableIdConfigType */
        [!NOCODE!]
        [!VAR "rxfifoenable" = "0"!]
        [!LOOP "CanController/*"!]
            [!IF "CanControllerRxFifoEnable = 'true'"!][!VAR "rxfifoenable" = "1"!][!ENDIF!]
        [!ENDLOOP!]
            [!IF "$rxfifoenable = 1"!][!CODE!]RxFifoTableID_PBConfig[!"@index"!],[!ENDCODE!][!ELSE!][!CODE!]NULL_PTR, /* Rx fifo disabled */[!ENDCODE!]
        [!ENDIF!][!ENDNOCODE!]
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */
        [!NOCODE!]
        [!VAR "Can_hardware_ob_id" = "0"!]
        [!LOOP "CanHardwareObject/*"!]
        [!IF "$Can_hardware_ob_id < CanObjectId"!]
        [!VAR "Can_hardware_ob_id" = "CanObjectId"!]
        [!ENDIF!]
        [!ENDLOOP!][!ENDNOCODE!]

        /*Maximum Object IDs configured */
        (Can_HWObjectCountType)[!"num:i($Can_hardware_ob_id + 1)"!]U,

        /*Controller ID mapping*/
        {[!NOCODE!]
                [!VAR "Can_hardware_ob_id" = "0"!][!VAR "END_COMMA"="0"!]
                [!VAR "MASK_COUNT"="num:i(count(CanHardwareObject/*))"!]
                [!FOR "objectid" = "0" TO "num:i(count(CanHardwareObject/*) - 1)"!]
                [!LOOP "CanHardwareObject/*"!]
                [!IF "CanObjectId = $objectid"!]
                [!VAR "END_COMMA"="$END_COMMA + 1"!]
                [!IF "$Can_hardware_ob_id != CanObjectId"!]
                [!VAR "Can_hardware_ob_id" = "CanObjectId"!]
                [!SELECT "node:ref(CanControllerRef)"!]
                [!CODE!][!"num:i(CanControllerId)"!]U[!ENDCODE!][!ENDSELECT!]
                [!NOCODE!][!IF "$END_COMMA < $MASK_COUNT"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!][!ELSE!][!VAR "END_COMMA"="$END_COMMA + 1"!][!ENDIF!]
                [!BREAK!][!ENDIF!][!ENDLOOP!][!ENDFOR!][!ENDNOCODE!]},

        /*Can Object Type mapping*/
        {[!NOCODE!]
                [!VAR "Can_hardware_ob_id" = "0"!][!VAR "END_COMMA"="0"!]
                [!VAR "MASK_COUNT"="num:i(count(CanHardwareObject/*))"!]
                [!FOR "objectid" = "0" TO "num:i(count(CanHardwareObject/*) - 1)"!]
                [!LOOP "CanHardwareObject/*"!]
                [!IF "CanObjectId = $objectid"!]
                [!VAR "END_COMMA"="$END_COMMA + 1"!]
                [!IF "$Can_hardware_ob_id != CanObjectId"!]
                [!VAR "Can_hardware_ob_id" = "CanObjectId"!]
                [!CODE!](Can_ObjType)[!"CanObjectType"!][!ENDCODE!]
                [!NOCODE!][!IF "$END_COMMA < $MASK_COUNT"!][!CODE!],[!ENDCODE!][!ELSE!][!ENDIF!][!ENDNOCODE!][!ELSE!][!VAR "END_COMMA"="$END_COMMA + 1"!][!ENDIF!]
                [!BREAK!][!ENDIF!][!ENDLOOP!][!ENDFOR!][!ENDNOCODE!]}

    };

[!ENDLOOP!]


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
