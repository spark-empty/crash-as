/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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
#ifndef RELEASE_ASCORE_VIRTUAL_INCLUDE_VECU_H_
#define RELEASE_ASCORE_VIRTUAL_INCLUDE_VECU_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QAction>
#include <assert.h>
#include "Virtio.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef void (*PF_MAIN)(int argc,const char* argv[]);

/* ============================ [ CLASS     ] ====================================================== */
class vEcu: public QThread
{
Q_OBJECT
private:
    void* hxDll;
    PF_MAIN pfMain;
    QString name;
    Virtio* virtio;

public:
    explicit vEcu ( QString dll, QObject *parent = 0);
    ~vEcu ( );
    QString Name(void) { return name; }
#ifndef __AS_CAN_BUS__
    void Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
#endif
    void Shell_Write(QString cmd);
private slots:
#ifndef __AS_CAN_BUS__
    void On_Can_RxIndication(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
#endif
private:
    void run(void);
signals:
#ifndef __AS_CAN_BUS__
    void Can_RxIndication(vEcu* ecu, quint8 busid,quint32 canid,quint8 dlc,quint8* data);
#endif
protected:

private slots:

};

class vmEcu : public QAction
{
Q_OBJECT
private:
    vEcu* ecu;
public:
    explicit vmEcu(vEcu* ecu,QWidget* parent = 0);
private slots:
    void start(void);

};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* RELEASE_ASCORE_VIRTUAL_INCLUDE_VECU_H_ */
