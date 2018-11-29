"""/* Copyright(C) 2013, OpenSAR by Fan Wang(parai). All rights reserved.
 *
 * This file is part of OpenSAR.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email: parai@foxmail.com
 * Source Open At: https://github.com/parai/OpenSAR/
 */
"""
import sys,os
from .GCF import *

__all__ = ['GenCan']

__dir = '.'

def GenCan(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('ControllerList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen Can DONE <<<')
    

def GenH():
    global __dir
    fp = open('%s/Can_Cfg.h'%(__dir),'w')
    fp.write(GHeader('Can'))
    General=GLGet('General')
    List=GLGet('ControllerList')
    fp.write("""#ifndef CAN_CFG_H_
#define CAN_CFG_H_

/* ################ Can General ################ */

#define CAN_DEV_ERROR_DETECT STD_%s
#define CAN_VERSION_INFO_API STD_%s
#define CAN_TIMEOUT_DURATION 10 /* ms */

/* Number of controller configs */
#define CAN_CTRL_CONFIG_CNT %s

/* Info used by CanIF,index of configure in Can_ControllerCfgData[] */\n"""%(
        GAGet(General,'DevelopmentErrorDetection'),
        GAGet(General,'VersionInfoApi'),
        len(List)))
    for i in range(0,len(List)):
        fp.write('#define INDEX_OF_%s %s\n'%(GAGet(List[i],'Name'),i))
    
    cstrR=cstrT=''
    NUM_OF_HTHS=0
    NUM_OF_HRHS=0
    for ctrl in List:
        for hoh in GLGet(ctrl,'HohList'):
            if(GAGet(hoh,'ObjectType')=='RECEIVE'):
                NUM_OF_HRHS += 1
                cstrR+='\t%-32s,/* %-32s */ \n'%(GAGet(hoh,'Name'),GAGet(ctrl,'Name'))
            elif(GAGet(hoh,'ObjectType')=='TRANSMIT'):
                NUM_OF_HTHS += 1
                cstrT+='\t%-32s,/* %-32s */ \n'%(GAGet(hoh,'Name'),GAGet(ctrl,'Name'))
    fp.write("""

typedef enum {
    CAN_CTRL_0 = 0,
    CAN_CTRL_1 = 1,
    CAN_CTRL_2 = 2,
    CAN_CTRL_3 = 3,
    CAN_CTRL_4 = 4,
    CAN_CONTROLLER_CNT = 5
}CanControllerIdType;

typedef enum {
    CAN_ID_TYPE_EXTENDED,
    CAN_ID_TYPE_MIXED,
    CAN_ID_TYPE_STANDARD
} Can_IdTypeType;
#ifdef USE_CAN_HOH_ID
typedef uint16 Can_Arc_HTHType;
typedef uint16 Can_Arc_HRHType;
enum {
%s
%s
};
#define NUM_OF_HRHS %s
#define NUM_OF_HTHS %s
#else
typedef enum {
%s
    NUM_OF_HTHS
} Can_Arc_HTHType;

typedef enum {
%s
    NUM_OF_HRHS
} Can_Arc_HRHType;
#endif
typedef struct {
    void (*CancelTxConfirmation)( const Can_PduType *);
    void (*RxIndication)( uint8 ,Can_IdType ,uint8 , const uint8 * );
    void (*ControllerBusOff)(uint8);
    void (*TxConfirmation)(PduIdType);
    void (*ControllerWakeup)(uint8);
    void (*Arc_Error)(uint8,Can_Arc_ErrorType);
} Can_CallbackType;

/** Start mc9s12 unique */
typedef enum {
  CAN_IDAM_2_32BIT = 0,
  CAN_IDAM_4_16BIT = 1,
  CAN_IDAM_8_8BIT  = 2,
  CAN_IDAM_FILTER_CLOSED = 3,
} Can_IDAMType;

typedef enum {
    CAN_ARC_PROCESS_TYPE_INTERRUPT,
    CAN_ARC_PROCESS_TYPE_POLLING
} Can_Arc_ProcessType;

typedef enum {
    CAN_OBJECT_TYPE_RECEIVE,
    CAN_OBJECT_TYPE_TRANSMIT
} Can_ObjectTypeType;

typedef enum {
    CAN_ARC_HANDLE_TYPE_BASIC,
    CAN_ARC_HANDLE_TYPE_FULL
} Can_Arc_HohType;

typedef struct
{
    uint8 idmr[8]; /* Identifier Mask Register, 1 = ignore corresponding acceptance code register bit*/
    uint8 idar[8]; /* Identifier Acceptance Register*/
    Can_IDAMType idam;
} Can_FilterMaskType;

typedef struct Can_HardwareObjectStruct {
    /** Specifies the type (Full-CAN or Basic-CAN) of a hardware object.*/
    Can_Arc_HohType CanHandleType;

    /** Specifies whether the IdValue is of type - standard identifier - extended
    identifier - mixed mode ImplementationType: Can_IdType*/
    Can_IdTypeType CanIdType;

    /**    Specifies (together with the filter mask) the identifiers range that passes
    the hardware filter.*/
    uint32 CanIdValue;

    /**    Holds the handle ID of HRH or HTH. The value of this parameter is unique
    in a given CAN Driver, and it should start with 0 and continue without any
    gaps. The HRH and HTH Ids are defined under two different name-spaces.
    Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3.*/
    uint16 CanObjectId;

    /** Specifies if the HardwareObject is used as Transmit or as Receive object*/
    Can_ObjectTypeType CanObjectType;

    /** Reference to the filter mask that is used for hardware filtering togerther
    with the CAN_ID_VALUE*/
    const Can_FilterMaskType *CanFilterMaskRef;

    /** A "1" in this mask tells the driver that that HW Message Box should be
    occupied by this Hoh. A "1" in bit 31(ppc) occupies Mb 0 in HW.*/
    uint32 Can_MbMask;

    /** End Of List. Set to TRUE is this is the last object in the list.*/
    boolean Can_Arc_EOL;
} Can_HardwareObjectType;

typedef struct
{
    /** Enables / disables API Can_MainFunction_BusOff() for
    handling busoff events in polling mode. */
    //Can_ProcessType CanBusoffProcessing;
    /** Defines if a CAN controller is used in the configuration. */
    //boolean         CanControllerActivation;
    /** This parameter provides the controller ID which is unique in a
    given CAN Driver. The value for this parameter starts with 0 and
    continue without any gaps. */
    CanControllerIdType  CanControllerId;
    /** Enables / disables API Can_MainFunction_Read() for
    handling PDU reception events in polling mode. */
    Can_Arc_ProcessType CanRxProcessing;
    /** Enables / disables API Can_MainFunction_Write() for
    handling PDU transmission events in polling mode.  */
    Can_Arc_ProcessType CanTxProcessing;
    /** Enables / disables API Can_MainFunction_Wakeup() for
    handling wakeup events in polling mode. */
    Can_Arc_ProcessType CanWakeupProcessing;
    Can_Arc_ProcessType CanBusOffProcessing;
    /** CAN driver support for wakeup over CAN Bus. */
    //boolean         CanWakeupSupport;
    /**    Reference to the CPU clock configuration, which is set in the MCU driver
    configuration.*/
    //uint32 CanCpuClockRef;
    /** This parameter contains a reference to the Wakeup Source for this
    ontroller as defined in the ECU State Manager. Implementation Type:
    reference to EcuM_WakeupSourceType.*/
    //uint32/* ref to EcuMWakeupSource */ CanWakeupSourceRef;
    /** Specifies the baudrate of the controller in kbps. */
    uint16          CanControllerBaudRate;
    /** Specifies propagation delay in time quantas(1..8).*/
    uint16          CanControllerPropSeg;
    /** Specifies phase segment 1 in time quantas(1..16).*/
    uint16          CanControllerSeg1;
    /** Specifies phase segment 2 in time quantas(1..8).*/
    uint16          CanControllerSeg2;
    /**    Specifies the synchronization jump width(1..4) for the controller in
    time quantas.*/
    //uint16          CanControllerSyncJumpWidth;
    /** List of Hoh id's that belong to this controller */
    const Can_HardwareObjectType  *Can_Arc_Hoh;
    boolean Can_Arc_Loopback;
}Can_ControllerConfigType;

typedef struct {
    const Can_ControllerConfigType *CanController;
    // Callbacks( Extension )
    const Can_CallbackType *CanCallbacks;
} Can_ConfigSetType;

/*
    This is  the type of the external data structure containing the overall initialization
    data for the CAN driver and SFR settings affecting all controllers. Furthermore it
    contains pointers to controller configuration structures. The contents of the
    initialization data structure are CAN hardware specific.
*/
typedef struct
{
    /** This is the multiple configuration set container for CAN Driver
     Multiplicity 1..*  */
    const Can_ConfigSetType     *CanConfigSet;
}Can_ConfigType;



extern const Can_ConfigType Can_ConfigData;
#endif /* CAN_CFG_H_ */\n\n"""%(cstrR,cstrT,
                                NUM_OF_HRHS,NUM_OF_HTHS,
                                cstrT,cstrR))
    fp.close()

def GenC():
    global __dir
    fp = open('%s/Can_PBCfg.c'%(__dir),'w')
    fp.write(GHeader('Can'))
    fp.write('#if defined(USE_CAN) && !defined(NOT_PYGEN_CAN)\n')
    fp.write("""#include "Can.h"

static const Can_FilterMaskType vCanFilterMask0=
{
    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    {0,0,0,0,0,0,0,0},
    CAN_IDAM_2_32BIT
};\n\n""")
    List=GLGet('ControllerList')
    cstr=''
    for ctrl in List:
        cstr += 'static const Can_HardwareObjectType %s_HOHCfgData[]=\n{\n'%(GAGet(ctrl,'Name'))
        for hoh in GLGet(ctrl,'HohList'):
            cstr +="""
    {    /* %s */
        .CanHandleType=CAN_ARC_HANDLE_TYPE_%s,
        .CanIdType=CAN_ID_TYPE_%s,
        .CanIdValue=0x00,/*TODO*/
        .CanObjectId=%s,
        .CanObjectType=CAN_OBJECT_TYPE_%s,
        .CanFilterMaskRef=&vCanFilterMask0,/*TODO*/
        .Can_MbMask=0x00000000,/*TODO*/
        .Can_Arc_EOL=FALSE
    },\n"""%(GAGet(hoh,'Name'),
             GAGet(hoh,'HohType'),
             GAGet(hoh,'IdentifierType'),
             GAGet(hoh,'Name'),
             GAGet(hoh,'ObjectType')
             )
        cstr += """
    {
        .Can_Arc_EOL = TRUE,
    }
};\n\n"""
    fp.write(cstr)
    cstr='const Can_ControllerConfigType  Can_ControllerCfgData[]=\n{\n'
    for ctrl in List:
        cstr += """
    {
        .CanControllerId=%s,
        .CanRxProcessing=CAN_ARC_PROCESS_TYPE_INTERRUPT,
        .CanTxProcessing=CAN_ARC_PROCESS_TYPE_INTERRUPT,
        .CanWakeupProcessing=CAN_ARC_PROCESS_TYPE_INTERRUPT,
        .CanBusOffProcessing=CAN_ARC_PROCESS_TYPE_INTERRUPT,
        .CanControllerBaudRate=%s,
        .CanControllerPropSeg=0,/* (SJW) */
        .CanControllerSeg1=%s,
        .CanControllerSeg2=%s,
        .Can_Arc_Hoh=%s_HOHCfgData,
        .Can_Arc_Loopback=FALSE
    },\n"""%(GAGet(ctrl,'Name'),
             GAGet(ctrl,'Baudrate'),
             GAGet(ctrl,'Seg1'),
             GAGet(ctrl,'Seg2'),
             GAGet(ctrl,'Name'))
    cstr += """    
};
extern void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc,const uint8 *CanSduPtr);
extern void CanIf_TxConfirmation(PduIdType canTxPduId);
const Can_CallbackType CanCallbackConfigData = {
     NULL, //CanIf_CancelTxConfirmation,
     CanIf_RxIndication,
     NULL,//CanIf_ControllerBusOff,
     CanIf_TxConfirmation,
     NULL, //CanIf_ControllerWakeup,
     NULL //CanIf_Arc_Error,
 };
const Can_ConfigSetType Can_ConfigSetData ={Can_ControllerCfgData,&CanCallbackConfigData};
const Can_ConfigType Can_ConfigData ={&Can_ConfigSetData};\n\n"""
    fp.write(cstr)
    fp.write('#endif /* USE_CAN */\n\n')
    fp.close()