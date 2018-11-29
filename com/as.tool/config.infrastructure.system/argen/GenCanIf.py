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

__all__ = ['GenCanIf']


__dir = '.'


    
def GenCanIf(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('ChannelList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen CanIf DONE <<<')

def GenH():
    global __dir
    fp = open('%s/CanIf_Cfg.h'%(__dir),'w')
    fp.write(GHeader('CanIf'))
    General=GLGet('General')
    fp.write("""
#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Can.h"
/* ============================ [ MACROS    ] ====================================================== */
#define CANIF_VERSION_INFO_API   STD_%s
#define CANIF_DEV_ERROR_DETECT   STD_%s
#define CANIF_DLC_CHECK          STD_%s

#define CANIF_TASK_FIFO_MODE     STD_%s
#define CANIF_RX_FIFO_SIZE       %s
#define CANIF_TX_FIFO_SIZE       %s

#define CANIF_MULITPLE_DRIVER_SUPPORT       STD_OFF   /*  Not supported */
#define CANIF_READRXPDU_DATA_API            STD_OFF   /*  Not supported */
#define CANIF_READRXPDU_NOTIFY_STATUS_API   STD_OFF   /*  Not supported */
#define CANIF_READTXPDU_NOTIFY_STATUS_API   STD_OFF   /*  Not supported */
#define CANIF_SETDYNAMICTXID_API            STD_OFF   /*  Not supported */
#define CANIF_WAKEUP_EVENT_API              STD_OFF   /*  Not supported */
#define CANIF_TRANSCEIVER_API               STD_OFF   /*  Not supported */
#define CANIF_TRANSMIT_CANCELLATION         STD_OFF   /*  Not supported */
#define CANIF_ARC_RUNTIME_PDU_CONFIGURATION STD_OFF   /*  Not supported */
#define CANIF_CANPDUID_READDATA_API         STD_OFF   /*  Not supported */
#define CANIF_READRXPDU_NOTIF_STATUS_API    STD_OFF   /*  Not supported */
\n"""%(GAGet(General,'VersionInfoApi'),
         GAGet(General,'DevelopmentErrorDetection'),
         GAGet(General,'DataLengthCodeCheck'),
         GAGet(General,'TaskFifoMode'),GAGet(General,'RxFifoSize'),GAGet(General,'TxFifoSize')))
    cstr1=cstr2=''
    startId = 0 
    fp.write("/*CanIf Receive */\n")    
    for chl in GLGet('ChannelList'):
        cstr1+='\t%s_CONFIG_0,\n'%(GAGet(chl,'Name'))
        cstr2+='\t%-32s,/* %-32s */\n'%(GAGet(chl,'Name'),GAGet(chl,'ControllerRef'))
        for pdu in GLGet(chl,'RxPduList'):
            fp.write('#define CANIF_ID_%-32s %s\n'%(GAGet(pdu,'EcuCPduRef'),startId))
            startId += 1
    startId = 0 
    fp.write("/*CanIf Transmit */\n")    
    for chl in GLGet('ChannelList'):
        for pdu in GLGet(chl,'TxPduList'):
            fp.write('#define CANIF_ID_%-32s %s\n'%(GAGet(pdu,'EcuCPduRef'),startId))
            startId += 1
    fp.write("""
/* ============================ [ TYPES     ] ====================================================== */
/* Identifiers for the elements in CanIfControllerConfig[]
 * This is the ConfigurationIndex in CanIf_InitController() */
typedef enum {
%s
    CANIF_CHANNEL_CONFIGURATION_CNT
}CanIf_Arc_ConfigurationIndexType;

typedef enum {
%s
    CANIF_CHANNEL_CNT
}CanIf_Arc_ChannelIdType;

#include "CanIf_ConfigTypes.h"

extern const CanIf_ConfigType CanIf_Config; 

#endif\n\n"""%(cstr1,cstr2))
    fp.close()
    
def GenC():   
    global __dir
    fp = open('%s/CanIf_Cfg.c'%(__dir),'w')
    fp.write(GHeader('CanIf'))
    fp.write('#ifdef USE_CANIF\n')
    cstr1=cstr2=cstr3=''    
    for chl in GLGet('ChannelList'):
        cstr1+='\t%-32s,/* %-32s */\n'%(GAGet(chl,'ControllerRef'),GAGet(chl,'Name'))
        cstr2+='\t%s_CONFIG_0,\n'%(GAGet(chl,'Name'))
        cstr3+="""
    {
        /* .WakeupSupport = CANIF_WAKEUP_SUPPORT_NO_WAKEUP, */
        .CanIfControllerIdRef = %s,
        /* .CanIfDriverNameRef = "FLEXCAN", */  /* Not used */
        .CanIfInitControllerRef = &Can_ControllerCfgData[INDEX_OF_%s],
    },\n"""%(GAGet(chl,'Name'),GAGet(chl,'ControllerRef'))
    fp.write("""
/* ============================ [ INCLUDES  ] ====================================================== */
#include "CanIf.h"
#if defined(USE_CANTP)
#include "CanTp.h"
#include "CanTp_Cbk.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"
#endif
#if defined(USE_PDUR)
#include "PduR.h"
#endif
#if defined(USE_CANNM)
#include "CanNm_Cbk.h"
#endif
#if defined(USE_OSEKNM)
#include "OsekNm.h"
#endif
#if defined(USE_XCP)
#include "Xcp.h"
#include "XcpOnCan_Cbk.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define PDUR_ID2_STDOUT 0
#define PDUR_ID_STDIN 0
/* ============================ [ DECLARES  ] ====================================================== */
/* Imported structs from Can_PBcfg.c */
extern const Can_ControllerConfigType Can_ControllerCfgData[];
extern const Can_ConfigSetType Can_ConfigSetData;
""")
    if(GAGet(GLGet('General'),'BusOffNotification')!='NULL'):
        fp.write('extern void %s(uint8);\n'%(GAGet(GLGet('General'),'BusOffNotification')))
    if(GAGet(GLGet('General'),'ErrorNotification')!='NULL'):
        fp.write('extern void %s(uint8,Can_Arc_ErrorType);\n'%(GAGet(GLGet('General'),'ErrorNotification')))

    for chl in GLGet('ChannelList'):
        for pdu in GLGet(chl,'RxPduList'):
            if(GAGet(pdu,'ReceivedNotifier')=='User'):
                fp.write('extern void %sRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);\n'%(GAGet(pdu,'UserNotification')))
        for pdu in GLGet(chl,'TxPduList'):
            if(GAGet(pdu,'TransmitNotifier')=='User'):
                fp.write('extern void %sTxConfirmation(PduIdType);\n'%(GAGet(pdu,'UserNotification')))
    fp.write("""
/* ============================ [ DATAS     ] ====================================================== */
/* Contains the mapping from CanIf-specific Channels to Can Controllers */
const CanControllerIdType CanIf_Arc_ChannelToControllerMap[CANIF_CHANNEL_CNT] = {
%s
};

const uint8 CanIf_Arc_ChannelDefaultConfIndex[CANIF_CHANNEL_CNT] = {
%s
};

/* Container that gets slamed into CanIf_InitController()
 * Inits ALL controllers
 * Multiplicity 1..* */
const CanIf_ControllerConfigType CanIfControllerConfig[] = {
%s
};\n\n"""%(cstr1,cstr2,cstr3))
    fp.write("""
/* Function callbacks for higher layers */
const CanIf_DispatchConfigType CanIfDispatchConfig =
{
    .CanIfBusOffNotification = %s,
    .CanIfWakeUpNotification = NULL,        /* Not used */
    .CanIfWakeupValidNotification = NULL,   /* Not used */
    .CanIfErrorNotificaton = %s,
};\n"""%(GAGet(GLGet('General'),'BusOffNotification'),GAGet(GLGet('General'),'ErrorNotification')))


    for chl in GLGet('ChannelList'):
        if(len(GLGet(chl,'HthList'))>0):
            cstr = 'static const CanIf_HthConfigType CanIfHthConfigData_%s[]=\n{\n'%(GAGet(chl,'Name'))
            Number=0
            for hth in GLGet(chl,'HthList'):
                Number += 1
                if(Number==len(GLGet(chl,'HthList'))):
                   isEol='TRUE'
                else:
                    isEol='FALSE'
                cstr += """
    {
        .CanIfHthType = CAN_ARC_HANDLE_TYPE_BASIC, /* TODO */
        .CanIfCanControllerIdRef = %s,
        .CanIfHthIdSymRef = %s,
        .CanIf_Arc_EOL = %s
    },\n"""%(GAGet(chl,'Name'),GAGet(hth,'HthRef'),isEol)
            cstr += '};\n\n'
            fp.write(cstr)
    for chl in GLGet('ChannelList'):
        if(len(GLGet(chl,'HrhList'))>0):
            cstr = 'static const CanIf_HrhConfigType CanIfHrhConfigData_%s[]=\n{\n'%(GAGet(chl,'Name'))
            Number=0
            for hrh in GLGet(chl,'HrhList'):
                Number += 1
                if(Number==len(GLGet(chl,'HrhList'))):
                   isEol='TRUE'
                else:
                    isEol='FALSE'
                cstr += """
    {
        .CanIfHrhType = CAN_ARC_HANDLE_TYPE_BASIC, /* TODO: not used by CanIf now. */
        .CanIfSoftwareFilterHrh = TRUE, /* Must Be True */
        .CanIfCanControllerHrhIdRef = %s,
        .CanIfHrhIdSymRef = %s,
        .CanIfHrhRangeConfig = NULL,
        .CanIf_Arc_EOL = %s
    },\n"""%(GAGet(chl,'Name'),GAGet(hrh,'HrhRef'),isEol)
            cstr += '};\n\n'
            fp.write(cstr)
    cstr = 'const CanIf_InitHohConfigType CanIfHohConfigData[] =\n{\n'
    Number=0
    for chl in GLGet('ChannelList'):
        Number += 1
        if(Number==len(GLGet('ChannelList'))):
           isEol='TRUE'
        else:
            isEol='FALSE'
        cstr += """
    {
        .CanIfHrhConfig = CanIfHrhConfigData_%s,
        .CanIfHthConfig = CanIfHthConfigData_%s,
        .CanIf_Arc_EOL = %s
    },\n"""%(GAGet(chl,'Name'),GAGet(chl,'Name'),isEol)
    cstr+='};\n\n'
    fp.write(cstr)
    def GetHohIndex(hohList,name):
        index = -1
        for i,hoh in enumerate(hohList):
            if(GAGet(hoh,'Name') == name):
                index = i
        return index
    ## Tx PDU ID
    cstr =''
    for chl in GLGet('ChannelList'):
        for pdu in GLGet(chl,'TxPduList'):
            Index = GetHohIndex(GLGet(chl,'HthList'),GAGet(pdu,'HthRef'))
            if(GAGet(pdu,'TransmitNotifier')=='CanTp'):
                IdPrfix='CANTP_ID'
            elif(GAGet(pdu,'TransmitNotifier')=='CanNm'):
                IdPrfix='CANNM_ID'
            elif(GAGet(pdu,'TransmitNotifier')=='Xcp'):
                IdPrfix='XCP_ID'
            elif(GAGet(pdu,'TransmitNotifier')=='J1939Tp'):
                IdPrfix='J1939TP_ID'
            else:
                IdPrfix='PDUR_ID2'
            if(GAGet(pdu,'TransmitNotifier')=='Nobody'):
                notifier='NULL'
            elif(GAGet(pdu,'TransmitNotifier')!='User'):
                if(GAGet(pdu,'TransmitNotifier')=='PduR'):
                    notifier='PduR_CanIfTxConfirmation'
                elif(GAGet(pdu,'TransmitNotifier')=='Xcp'):
                    notifier='Xcp_CanIfTxConfirmation'
                else:
                    notifier='%s_TxConfirmation'%(GAGet(pdu,'TransmitNotifier'))
            else:
                notifier='%sTxConfirmation'%(GAGet(pdu,'UserNotification'))
            if(Integer(GAGet(pdu,'Identifier')) > 0x7FF):
                IdType='CANIF_CAN_ID_TYPE_29'
            else:
                IdType='CANIF_CAN_ID_TYPE_11'
            cstr += """
    {
        .CanIfTxPduId = %s_%s,
        .CanIfCanTxPduIdCanId = %s, 
        .CanIfCanTxPduIdDlc = %s,
        .CanIfCanTxPduType = CANIF_PDU_TYPE_STATIC,
    #if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
        .CanIfReadTxPduNotifyStatus = TRUE,
    #endif
        .CanIfTxPduIdCanIdType = %s,
        .CanIfUserTxConfirmation = %s,
        .CanIfCanTxPduHthRef = &CanIfHthConfigData_%s[%s],
        .PduIdRef = NULL
    },\n"""%(IdPrfix,GAGet(pdu,'EcuCPduRef'),
         GAGet(pdu,'Identifier'),
         GAGet(pdu,'DataLengthCode'),
         IdType,
         notifier,
         GAGet(chl,'Name'),Index)
    fp.write("""
#if defined(__WINDOWS__) || defined(__LINUX__)
#else
static const
#endif
CanIf_TxPduConfigType CanIfTxPduConfigData[] = 
{
    %s
};\n\n"""%(cstr))
    
    ## Rx Pdu
    cstr =''
    for chl in GLGet('ChannelList'):
        for pdu in GLGet(chl,'RxPduList'):
            Index = GetHohIndex(GLGet(chl,'HrhList'),GAGet(pdu,'HrhRef'))
            if(GAGet(pdu,'ReceivedNotifier')=='CanTp'):
                IdPrfix='CANTP'
            elif(GAGet(pdu,'ReceivedNotifier')=='Xcp'):
                IdPrfix='XCP'
            elif(GAGet(pdu,'ReceivedNotifier')=='J1939Tp'):
                IdPrfix='J1939TP'
            else:
                IdPrfix='PDUR'
            if((GAGet(pdu,'ReceivedNotifier')!='Nobody') and
               (GAGet(pdu,'ReceivedNotifier')!='User')):
                notifier='NULL'
            else:
                notifier='%sRxIndication'%(GAGet(pdu,'UserNotification'))
            if(GAGet(pdu,'ReceivedNotifier')=='PduR'):
                notifierT='CANIF_USER_TYPE_CAN_PDUR'
            elif(GAGet(pdu,'ReceivedNotifier')=='CanTp'):
                notifierT='CANIF_USER_TYPE_CAN_TP'
            elif(GAGet(pdu,'ReceivedNotifier')=='CanNm'):
                notifierT='CANIF_USER_TYPE_CAN_NM'
            elif(GAGet(pdu,'ReceivedNotifier')=='J1939Tp'):
                notifierT='CANIF_USER_TYPE_J1939TP'
            elif(GAGet(pdu,'ReceivedNotifier')=='Xcp'):
                notifierT='CANIF_USER_TYPE_XCP'
            else:
                notifierT='CANIF_USER_TYPE_CAN_SPECIAL'
            if(Integer(GAGet(pdu,'Identifier')) > 0x7FF):
                IdType='CANIF_CAN_ID_TYPE_29'
            else:
                IdType='CANIF_CAN_ID_TYPE_11'
            cstr += """
    {
        .CanIfCanRxPduId = %s_ID_%s,
        .CanIfCanRxPduCanId = %s,
        .CanIfCanRxPduDlc = %s,
#if ( CANIF_CANPDUID_READDATA_API == STD_ON )
        .CanIfReadRxPduData = TRUE,
#endif
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
        .CanIfReadRxPduNotifyStatus = TRUE,
#endif
        .CanIfRxPduIdCanIdType = %s,
        .CanIfRxUserType = %s,
        .CanIfUserRxIndication = %s,
        .CanIfCanRxPduHrhRef = &CanIfHrhConfigData_%s[%s],
        .PduIdRef = NULL,
        .CanIfSoftwareFilterType = CANIF_SOFTFILTER_TYPE_MASK,
        .CanIfCanRxPduCanIdMask = %s
    },\n"""%(IdPrfix,GAGet(pdu,'EcuCPduRef'),
             GAGet(pdu,'Identifier'),
             GAGet(pdu,'DataLengthCode'),
             IdType,
             notifierT,
             notifier,
             GAGet(chl,'Name'),Index,
             GAGet(pdu,'FilterMask'))
    fp.write("""
static const CanIf_RxPduConfigType CanIfRxPduConfigData[] = 
{
    %s
};

/* This container contains the init parameters of the CAN
 * Multiplicity 1..* */
const CanIf_InitConfigType CanIfInitConfig =
{
    .CanIfConfigSet = 0, /* Not used */
    .CanIfNumberOfCanRxPduIds = sizeof(CanIfRxPduConfigData)/sizeof(CanIf_RxPduConfigType),
    .CanIfNumberOfCanTXPduIds = sizeof(CanIfTxPduConfigData)/sizeof(CanIf_TxPduConfigType),
    .CanIfNumberOfDynamicCanTXPduIds = 0, /* Not used */
    /* Containers */
    .CanIfHohConfigPtr = CanIfHohConfigData,
    .CanIfRxPduConfigPtr = CanIfRxPduConfigData,
    .CanIfTxPduConfigPtr = CanIfTxPduConfigData,
};
/* This container includes all necessary configuration sub-containers
 * according the CAN Interface configuration structure */
const CanIf_ConfigType CanIf_Config =
{
    .ControllerConfig = CanIfControllerConfig,
    .DispatchConfig = &CanIfDispatchConfig,
    .InitConfig = &CanIfInitConfig,
    .TransceiverConfig = NULL, /* Not used */
    .Arc_ChannelToControllerMap = CanIf_Arc_ChannelToControllerMap,
    .Arc_ChannelDefaultConfIndex = CanIf_Arc_ChannelDefaultConfIndex,
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifndef USE_STDIO_CAN
void __weak CanIf_StdioTxConfirmation(PduIdType id)
{
    (void)id;
}

void __weak CanIf_StdioRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId)
{
    (void)channel;
    (void)pduId;
    (void)sduPtr;
    (void)dlc;
    (void)canId;
}
#endif
#ifndef USE_OSEKNM
void CanIf_OsekNmUserRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId) {
    (void)channel;
    (void)pduId;
    (void)sduPtr;
    (void)dlc;
    (void)canId;
}
void CanIf_OsekNmUserTxConfirmation(PduIdType pduId) { (void)pduId; }
#endif
\n\n"""%(cstr))
    fp.write('#endif /* USE_CANIF */')
    fp.close() 
