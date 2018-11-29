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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "arvic.h"

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */

typedef struct
{
    qint32 x;  /* center position x */
    qint32 y;  /* center position y */
    qint32  offset; /* offset length of tail */
    qint32 length; /* head and tail length */
    qint32 tail_width;
    qint32 head_width;
    quint32 color;
    quint32 start; /* software zero angle */
    quint32 range;
    quint32 is_clockwise; /* rotate directin */
}Stmo_PointerConfigType;

typedef struct
{
    qint32 x;  /* top left position x */
    qint32 y;  /* top left position y */
    qint32 w;
    qint32 h;
    char*  p;
}Telltale_ConfigType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static const Stmo_PointerConfigType StmoConfig[STMO_CFG_NUM] = {
    {   /* speed */
        .x=850,
        .y=285,
        .offset=0,
        .length=175,
        .tail_width=16,
        .head_width=4,
        .color = 0x7453A2,
        .start=330,
        .range=240,
        .is_clockwise = true
    },
    {   /* tacho */
        .x=340,
        .y=285,
        .offset=0,
        .length=175,
        .tail_width=16,
        .head_width=4,
        .color = 0x7453A2,
        .start=330,
        .range=240,
        .is_clockwise = true
    },
    {   /* temperature */
        .x=134,
        .y=383,
        .offset=0,
        .length=80,
        .tail_width=10,
        .head_width=4,
        .color = 0xD63441,
        .start=311,
        .range=100,
        .is_clockwise = true
    },
    {   /* fuel level */
        .x=1055,
        .y=383,
        .offset=0,
        .length=80,
        .tail_width=10,
        .head_width=4,
        .color = 0xD63441,
        .start=227,
        .range=100,
        .is_clockwise = false
    }
};

static const Telltale_ConfigType TelltaleConfig[TELLTALE_CFG_NUM] =
{
    {
        .x=415,
        .y=320,
        .w=42,
        .h=36,
        .p=VIC_PICS_PATH"/tt_tpms.png"
    },
    {
        .x=220,
        .y=320,
        .w=64,
        .h=36,
        .p=VIC_PICS_PATH"/tt_low_oil.png"
    }
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
arVICPointer::arVICPointer(Stmo_IdType id, QGraphicsItem *parent) : QGraphicsItem(parent), id(id)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setZValue(1);
    posDegree = 0;
}

QRectF arVICPointer::boundingRect() const
{
    const Stmo_PointerConfigType* cfg =  &StmoConfig[id];
    return QRectF(-cfg->length-cfg->offset,-cfg->length-cfg->offset,(cfg->length+cfg->offset)*2,(cfg->length+cfg->offset)*2);
}

void arVICPointer::setPosDegree(quint32 degree)
{
    const Stmo_PointerConfigType* cfg =  &StmoConfig[id];

    degree = degree/100;
    if(degree > cfg->range) {
        degree = cfg->range;
    }

    if(cfg->is_clockwise)
    {
        degree = degree+cfg->start;
    }
    else
    {
        if(cfg->start > degree)
        {
            degree = cfg->start - degree;
        }
        else
        {
            degree = 360+degree-cfg->start;
        }
    }

    posDegree = degree;
    setRotation(degree);
}

void arVICPointer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)widget;
    (void)option;
    const Stmo_PointerConfigType* cfg =  &StmoConfig[id];
    quint32 radius,radius2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor((cfg->color>>16)&0xFF,(cfg->color>>8)&0xFF,(cfg->color>>0)&0xFF)));
    QPolygon polygon(4);
    polygon.setPoint(0,QPoint(-cfg->offset,                 cfg->tail_width/2));
    polygon.setPoint(1,QPoint(-cfg->offset-cfg->length,     cfg->head_width/2));
    polygon.setPoint(2,QPoint(-cfg->offset-cfg->length,    -cfg->head_width/2));
    polygon.setPoint(3,QPoint(-cfg->offset,                -cfg->tail_width/2));
    painter->drawConvexPolygon(polygon);
    if(cfg->offset < 0) {
        radius = -cfg->offset;
    }
    else if(cfg->offset > 0) {
        radius = cfg->offset;
    }
    else {
        radius = cfg->tail_width;
    }
    radius += 2;
    painter->drawEllipse(-radius,-radius,radius*2,radius*2);
    painter->setBrush(QBrush(QColor(0,0,0))); /* black */
    radius2 = radius*2/3;
    if(radius2 > cfg->tail_width) {
        radius2 = radius-cfg->tail_width*2/3;
    }
    painter->drawEllipse(-radius2,-radius2,radius2*2,radius2*2);
    setPos(cfg->x,cfg->y);

    setRotation(posDegree);
}

arVICPointer::~arVICPointer(){}

arVICTelltale::arVICTelltale(Telltale_IdType id, QGraphicsItem *parent) : QGraphicsItem(parent), id(id)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setZValue(1);
    status = TELLTALE_OFF;
}

QRectF arVICTelltale::boundingRect() const
{
    const Telltale_ConfigType* cfg =  &TelltaleConfig[id];
    return QRectF(cfg->x,cfg->y,cfg->w,cfg->h);
}

void arVICTelltale::setStatus(Telltale_StatueType st)
{
    status = st;

    if(status==TELLTALE_ON)
    {
        setVisible(true);
    }
    else
    {
        setVisible(false);
    }
}

void arVICTelltale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    const Telltale_ConfigType* cfg =  &TelltaleConfig[id];
    QImage tt(cfg->p);
    painter->drawImage(cfg->x,cfg->y,tt);
    if(status==TELLTALE_ON)
    {
        setVisible(true);
    }
    else
    {
        setVisible(false);
    }
}

arVICTelltale::~arVICTelltale(){}

arVICGraphicView::arVICGraphicView(QWidget *parent):QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);

    for(int i=0;i<TELLTALE_CFG_NUM;i++)
    {
        telltales[i] = new arVICTelltale((Telltale_IdType)i);
        scene->addItem(telltales[i]);
    }

    for(int i=0;i<STMO_CFG_NUM;i++)
    {
        pointers[i] = new arVICPointer((Stmo_IdType)i);
        scene->addItem(pointers[i]);
    }

    startTimer(10);
}

void arVICGraphicView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QImage bg(VIC_PICS_PATH"/bg.png");
    resize(bg.size());
    scene()->setSceneRect(0, 0, bg.size().width(), bg.size().height());
    painter->drawImage(0,0,bg);
#if 0
    /* I don't want to draw telltale here */
    for(int i=0;i<TELLTALE_CFG_NUM;i++)
    {
        const Telltale_ConfigType* cfg =  &TelltaleConfig[i];
        QImage tt(cfg->p);
        painter->drawImage(cfg->x,cfg->y,tt);
    }
#endif
    (void)rect;
}

void arVICGraphicView::timerEvent(QTimerEvent* e)
{
    (void)e;

    static qint32 tacho = 0;
    static qint32 speed = 0;
    static qint32 temp = 0;
    static qint32 fuel = 0;
    static bool tacho_up = true;
    static bool speed_up = true;
    static bool temp_up = true;
    static bool fuel_up = true;

    if(tacho_up)
    {
        tacho += 50;
        if(tacho >=  24000)
        {
            tacho = 24000;
            tacho_up = false;
        }
    }
    else
    {
        if(tacho > 100)
        {
            tacho -= 100;
        }
        else
        {
            tacho = 0;
            tacho_up = true;
        }
    }

    if(speed_up)
    {
        speed += 50;
        if(speed >=  24000)
        {
            speed = 24000;
            speed_up = false;
        }
    }
    else
    {
        if(speed > 100)
        {
            speed -= 100;
        }
        else
        {
            speed = 0;
            speed_up = true;
        }
    }

    if(temp_up)
    {
        temp += 50;
        if(temp >=  9700)
        {
            temp = 9700;
            temp_up = false;
        }
    }
    else
    {
        if(temp > 100)
        {
            temp -= 100;
        }
        else
        {
            temp = 0;
            temp_up = true;
        }
    }

    if(fuel_up)
    {
        fuel += 50;
        if(fuel >=  9700)
        {
            fuel = 9700;
            fuel_up = false;
        }
    }
    else
    {
        if(fuel > 100)
        {
            fuel -= 100;
        }
        else
        {
            fuel = 0;
            fuel_up = true;
        }
    }

    pointers[STMO_ID_SPEED]->setPosDegree(speed);
    pointers[STMO_ID_TACHO]->setPosDegree(tacho);
    pointers[STMO_ID_TEMP]->setPosDegree(temp);
    pointers[STMO_ID_FUEL]->setPosDegree(fuel);

    static qint32 tt_tpms = 0;
    static qint32 tt_low_oil = 0;
    tt_tpms ++;
    tt_low_oil ++;

    if(tt_tpms < 50)
    {
        telltales[TELLTALE_ID_TPMS]->setStatus(TELLTALE_ON);
    }
    else if(tt_tpms < 100)
    {
        telltales[TELLTALE_ID_TPMS]->setStatus(TELLTALE_OFF);
    }
    else
    {
       tt_tpms = 0;
    }

    if(tt_low_oil < 200)
    {
        telltales[TELLTALE_ID_LOW_OIL_PRESSURE]->setStatus(TELLTALE_ON);
    }
    else if(tt_low_oil < 400)
    {
        telltales[TELLTALE_ID_LOW_OIL_PRESSURE]->setStatus(TELLTALE_OFF);
    }
    else
    {
       tt_low_oil = 0;
    }
}

arVICGraphicView::~arVICGraphicView()
{

}

arVIC::arVIC(QString name,QWidget *parent) : arDevice(name,parent)
{
    gview = new arVICGraphicView(this);
    setCentralWidget(gview);
    this->setGeometry(50,150,1200,500);
    setVisible(true);
}
arVIC::~arVIC()
{

}
