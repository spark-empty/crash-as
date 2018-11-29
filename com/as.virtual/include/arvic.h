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
#ifndef RELEASE_ASCORE_VIRTUAL_INCLUDE_ARVIC_H_
#define RELEASE_ASCORE_VIRTUAL_INCLUDE_ARVIC_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "ardevice.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QImage>
/* ============================ [ MACROS    ] ====================================================== */
#define VIC_DEVICE_NAME "Vic"
#ifdef __WINDOWS__
#define VIC_PICS_PATH "D:/repository/as/release/ascore/SgDesign/virtual_cluster/pics"
#else
#define VIC_PICS_PATH "/home/parai/workspace/as/release/ascore/SgDesign/virtual_cluster/pics"
#endif
/* ============================ [ TYPES     ] ====================================================== */
typedef enum
{
    STMO_ID_SPEED,
    STMO_ID_TACHO,
    STMO_ID_TEMP,
    STMO_ID_FUEL,
    STMO_CFG_NUM
}Stmo_IdType;
typedef qint32 Stmo_DegreeType;

typedef enum
{
    TELLTALE_ID_TPMS,
    TELLTALE_ID_LOW_OIL_PRESSURE,
    TELLTALE_CFG_NUM
}Telltale_IdType;
typedef enum
{
    TELLTALE_OFF,
    TELLTALE_ON
}Telltale_StatueType;
/* ============================ [ CLASS     ] ====================================================== */
/*
 * Virtual Instrument Cluster
 */

class arVICPointer : public QGraphicsItem
{
private:
    Stmo_IdType id;
    Stmo_DegreeType posDegree;
public:
    explicit arVICPointer(Stmo_IdType id,QGraphicsItem *parent = 0);
    ~arVICPointer();
    void setPosDegree(quint32 degree);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

class arVICTelltale : public QGraphicsItem
{
private:
    Telltale_IdType id;
    Telltale_StatueType status;
public:
    explicit arVICTelltale(Telltale_IdType id,QGraphicsItem *parent = 0);
    ~arVICTelltale();
    void setStatus(Telltale_StatueType status);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

class arVICGraphicView : public QGraphicsView
{
    Q_OBJECT
private:
    arVICPointer* pointers[STMO_CFG_NUM];
    arVICTelltale* telltales[TELLTALE_CFG_NUM];
public:
    explicit arVICGraphicView(QWidget *parent=0);
    ~arVICGraphicView();
private:
    void drawBackground(QPainter *painter, const QRectF &rect);
private slots:
    void timerEvent(QTimerEvent* e);
};

class arVIC : public arDevice
{
    Q_OBJECT
private:
    arVICGraphicView* gview;
public:
    explicit arVIC(QString name,QWidget *parent=0);
    ~arVIC();
private slots:
private:
signals:

};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* RELEASE_ASCORE_VIRTUAL_INCLUDE_ARVIC_H_ */
