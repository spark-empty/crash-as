/**
 * WhatsApp - the open source AUTOSAR platform https://github.com/parai
 *
 * Copyright (C) 2014  WhatsApp <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef ARCAN_H
#define ARCAN_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include "ardevice.h"
#include <QTextEdit>
/* ============================ [ MACROS    ] ====================================================== */
#define TICK_MAX (TickType)-1
#define CAN_DEVICE_NAME   "Can"
#define CAN_CTRL_NUM   1

/* 1 : display CAN message by QTableWidget; 0 : display by QTextEdit */
#define cfgDISPLAY_BY_TABLE  0
/* ============================ [ TYPES     ] ====================================================== */
typedef quint32 TickType;
/* ============================ [ CLASS     ] ====================================================== */
class arCan : public arDevice
{
    Q_OBJECT
private:
    unsigned long channelNumber;
    QPushButton* btnPlayPause;
    QPushButton* btnHexlDeci;
    QPushButton* btnAbsRelTime;
    QPushButton* btnLoadTrace;
    QPushButton* btnStop;
    QComboBox*   cbBus;
    QLineEdit*   leId;
    QLineEdit*   leData;
    #if (cfgDISPLAY_BY_TABLE == 1)
    QTableWidget* tableTrace;
    #else
    QTextEdit*    textTrace;
    quint32       rxSize;
    #endif
    bool displayTimeInReal;
    TickType preTime;
    TickType startTime;
public:
    explicit arCan(QString name,unsigned long channelNumber,QWidget *parent=0);
    ~arCan();
    void RxIndication(QString from,quint8 busid,quint32 canid,quint8 dlc,quint8* data);
    void Transmit(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
private slots:
    void on_btnClearTrace_clicked(void);
    void on_btnSaveTrace_clicked(void);
    void on_btnHexlDeci_clicked(void);
    void on_btnAbsRelTime_clicked(void);
    void on_btnTriggerTx_clicked(void);
#ifdef __AS_CAN_BUS__
    void timerEvent(QTimerEvent* e);
#endif
private:
    void createGui(void);
    void putMsg(QString from,quint8 busid,quint32 canid,quint8 dlc,quint8* data,bool isRx=true);
    void clear(void);
signals:

};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
TickType GetOsTick(void);
TickType  GetOsElapsedTick  ( TickType prevTick );
#endif /* ARCAN_H */
