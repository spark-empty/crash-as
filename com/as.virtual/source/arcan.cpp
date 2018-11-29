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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "arcan.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <sys/time.h>
#include <assert.h>
#include <entry.h>

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef __AS_CAN_BUS__
extern "C" int can_open(unsigned long busid,const char* device_name,unsigned long port, unsigned long baudrate);
extern "C" int can_write(unsigned long busid,unsigned long canid,unsigned long dlc,unsigned char* data);
extern "C" int can_read(unsigned long busid,unsigned long canid,unsigned long* p_canid,unsigned long *dlc,unsigned char* data);
extern "C" void luai_canlib_open(void);
extern "C" void luai_canlib_close(void);
#endif
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
TickType GetOsTick(void)
{
    static struct timeval m0 = { -1 , -1 };

    if( (-1 == m0.tv_sec) && (-1 == m0.tv_usec) )
    {
        gettimeofday(&m0,NULL);
    }

    struct timeval m1;
    gettimeofday(&m1,NULL);

    float rtim = m1.tv_sec-m0.tv_sec;

    if(m1.tv_usec > m0.tv_usec)
    {
        rtim += (float)(m1.tv_usec-m0.tv_usec)/1000000.0;
    }
    else
    {
        rtim = rtim - 1 + (float)(1000000.0+m1.tv_usec-m0.tv_usec)/1000000.0;
    }

    return (TickType)(rtim*1000);
}

/* ============================ [ FUNCTIONS ] ====================================================== */
arCan::arCan(QString name,unsigned long channelNumber, QWidget *parent) : arDevice(name,parent)
{
    this->channelNumber = channelNumber;
    this->createGui();
    this->setGeometry(50,150,1200,500);
#ifdef __AS_CAN_BUS__
    luai_canlib_open();
    for(int i=0;i<channelNumber;i++)
    {
        if(!can_open(i,"socket",i,1000000))
        {
            assert(0);
        }
    }
    startTimer(1);
#endif
    setVisible(true);

}

#ifdef __AS_CAN_BUS__
void arCan::timerEvent(QTimerEvent* e)
{
    unsigned long canid,dlc;
    unsigned char data[8];
    int ercd;
    for(int i=0;i<channelNumber;i++)
    {
        ercd = can_read(i,-1,&canid,&dlc,data);
        if(ercd)
        {
            RxIndication("socket",i,canid,dlc,data);
        }
    }
}
#endif
arCan::~arCan()
{
#ifdef __AS_CAN_BUS__
    luai_canlib_close();
#endif
}

void arCan::on_btnClearTrace_clicked(void)
{
#if (cfgDISPLAY_BY_TABLE == 1)
    QStringList  list;
    tableTrace->clear();
    if(displayTimeInReal)
    {
        list<<"from"<<"Bus"<<"Rel(ms)"<<"Dir"<<"Id"<<"dlc"<<"B0"<<"B1"<< "B2"<< "B3"<< "B4"<< "B5"<< "B6"<< "B7";
    }
    else
    {
        list<<"from"<<"Bus"<<"Abs(ms)"<<"Dir"<<"Id"<<"dlc"<<"B0"<<"B1"<< "B2"<< "B3"<< "B4"<< "B5"<< "B6"<< "B7";
    }
    tableTrace->setColumnCount(list.size());
    tableTrace->setRowCount(0);
    tableTrace->setHorizontalHeaderLabels(list);
    tableTrace->setColumnWidth(0,150);
    tableTrace->setColumnWidth(1,60);
    tableTrace->setColumnWidth(2,150);
    tableTrace->setColumnWidth(3,60);
    tableTrace->setColumnWidth(4,80);
    for(int i=5;i<list.size();i++)
    {
        tableTrace->setColumnWidth(i,60);
    }
    tableTrace->setRowCount(0);
    tableTrace->setHorizontalHeaderLabels(list);
#else
    textTrace->clear();
    rxSize = 0;
#endif
}

void arCan::on_btnSaveTrace_clicked(void)
{
    QString filename = QFileDialog::getSaveFileName(this,"Save CAN Trace",".",tr("CAN Trace (*.rec *.txt)"));
    QFile file(filename);

    if(file.open(QFile::WriteOnly))
    {
        #if (cfgDISPLAY_BY_TABLE == 1)
        int size = tableTrace->rowCount();
        for(int i=0;i<size;i++)
        {
            QString from =  tableTrace->item(i,0)->text();
            QString bus  =  tableTrace->item(i,1)->text();
            QString time =  tableTrace->item(i,2)->text();
            QString dir  =  tableTrace->item(i,3)->text();
            QString id   =  tableTrace->item(i,4)->text();
            QString dlc  =  tableTrace->item(i,5)->text();
            QString b0 =  tableTrace->item(i,6)->text();
            QString b1 =  tableTrace->item(i,7)->text();
            QString b2 =  tableTrace->item(i,8)->text();
            QString b3 =  tableTrace->item(i,9)->text();
            QString b4 =  tableTrace->item(i,10)->text();
            QString b5 =  tableTrace->item(i,11)->text();
            QString b6 =  tableTrace->item(i,12)->text();
            QString b7 =  tableTrace->item(i,13)->text();

            char text[512];
            snprintf(text,512,"from %-16s bus(%s) time(%-8s) %2s id=0x%3s dlc=%s data=[%s,%s,%s,%s,%s,%s,%s,%s]\n",
                     from.toStdString().c_str(),bus.toStdString().c_str(),time.toStdString().c_str(),
                     dir.toStdString().c_str(),id.toStdString().c_str(),dlc.toStdString().c_str(),
                     b0.toStdString().c_str(),b1.toStdString().c_str(),b2.toStdString().c_str(),b3.toStdString().c_str(),
                     b4.toStdString().c_str(),b5.toStdString().c_str(),b6.toStdString().c_str(),b7.toStdString().c_str());
            file.write(text);
        }
        #else
        file.write(textTrace->toPlainText().toStdString().c_str());
        #endif
    	file.close();
    }
}
void arCan::on_btnHexlDeci_clicked(void)
{
    QString str = btnHexlDeci->text();

    if(str == "Hexl")
    {
        btnHexlDeci->setText("Decimal");
    }
    else
    {
        btnHexlDeci->setText("Hexl");
    }
}

void arCan::on_btnAbsRelTime_clicked(void)
{
    QString str = btnAbsRelTime->text();

    if(str == "Realated Time")
    {
        displayTimeInReal = true;
        btnAbsRelTime->setText("Absolute Time");
        #if (cfgDISPLAY_BY_TABLE == 1)
        int size = tableTrace->rowCount();
        TickType pre;
        for(int i=0;i<size;i++)
        {
            QTableWidgetItem* item =  tableTrace->item(i,2);
            if(0==i)
            {
                pre = item->text().toInt();
            }
            else
            {
                TickType rel = item->text().toInt() - pre;
                pre = item->text().toInt();
                item->setText(QString("%1").arg(rel));
            }
        }
        QStringList list;
        list<<"from"<<"Bus"<<"Rel(ms)"<<"Dir"<<"Id"<<"dlc"<<"B0"<<"B1"<< "B2"<< "B3"<< "B4"<< "B5"<< "B6"<< "B7";
        tableTrace->setColumnCount(list.size());
        tableTrace->setHorizontalHeaderLabels(list);
        #endif
    }
    else
    {
        displayTimeInReal = false;
        btnAbsRelTime->setText("Realated Time");
        #if (cfgDISPLAY_BY_TABLE == 1)
        int size = tableTrace->rowCount();
        TickType pre;
        for(int i=0;i<size;i++)
        {
            QTableWidgetItem* item =  tableTrace->item(i,2);
            if(0==i)
            {
                pre = item->text().toInt();
            }
            else
            {
                pre += item->text().toInt();
                item->setText(QString("%1").arg(pre));
            }
        }
        QStringList list;
        list<<"from"<<"Bus"<<"Abs(ms)"<<"Dir"<<"Id"<<"dlc"<<"B0"<<"B1"<< "B2"<< "B3"<< "B4"<< "B5"<< "B6"<< "B7";
        tableTrace->setColumnCount(list.size());
        tableTrace->setHorizontalHeaderLabels(list);
        #endif
    }
}
void arCan::putMsg(QString from,quint8 busid,quint32 canid,quint8 dlc,quint8* data,bool isRx)
{
    static TickType disTime = -1;
    #if (cfgDISPLAY_BY_TABLE == 1)
    quint32 index = tableTrace->rowCount();
    tableTrace->setRowCount(index+1);
    tableTrace->setItem(index,0,new QTableWidgetItem(from));
    tableTrace->setItem(index,1,new QTableWidgetItem(QString("%1").arg(busid)));
    if(0 == index)
    {
        preTime   = GetOsTick();
        startTime = preTime;
        disTime = 0;
    }
    else
    {
        if(displayTimeInReal)
        {
            TickType now = GetOsTick();
            disTime = now - preTime;
            preTime = GetOsTick();
        }
        else
        {
            preTime = GetOsTick();
            disTime = preTime - startTime;
        }
    }
    tableTrace->setItem(index,2,new QTableWidgetItem(QString("%1").arg(disTime)));
    if(isRx)
    {
        tableTrace->setItem(index,3,new QTableWidgetItem(QString("RX")));
    }
    else
    {
        tableTrace->setItem(index,3,new QTableWidgetItem(QString("TX")));
    }
    tableTrace->setItem(index,4,new QTableWidgetItem(QString("%1").arg(canid,0,16)));
    tableTrace->setItem(index,5,new QTableWidgetItem(QString("%1").arg(dlc,0,16)));
    for(int i=0;i<8;i++)
    {
        tableTrace->setItem(index,6+i,new QTableWidgetItem(QString("%1").arg((uint)data[i],2,16,QLatin1Char('0')).toUpper()));
    }
    tableTrace->setCurrentCell(index,0);
    #else
    if((TickType)-1 == disTime)
    {
        preTime   = GetOsTick();
        startTime = preTime;
        disTime = 0;
    }
    else
    {
        if(displayTimeInReal)
        {
            TickType now = GetOsTick();
            disTime = now - preTime;
            preTime = GetOsTick();
        }
        else
        {
            preTime = GetOsTick();
            disTime = preTime - startTime;
        }
    }
    char text[512];
    snprintf(text,512,"bus(%d) %2s id=0x%04x dlc=%d data=[%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x] @ %dms from %s & %d",
             busid,isRx?"rx":"tx",canid,dlc,
             data[0],data[1],data[2],data[3],
             data[4],data[5],data[6],data[7],
             disTime,from.toStdString().c_str(),rxSize);
    textTrace->append(QString(text));
    rxSize ++;
    #endif
}

void arCan::RxIndication(QString from,quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    putMsg(from,busid,canid,dlc,data);
}

void arCan::Transmit(quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    (void)time;
    putMsg("Qt",busid,canid,dlc,data,false);
#ifndef __AS_CAN_BUS__
    Entry::Self()->Can_Write(busid,canid,dlc,data);
#else
    if(!can_write(busid,canid,dlc,data))
    {
        assert(0);
    }
#endif
}

void arCan::on_btnTriggerTx_clicked(void)
{
    bool ok;
    quint32 id = leId->text().toLong(&ok,16);
    if(ok)
    {
        int i;
        quint8 data[8];
        quint32 bus = cbBus->currentIndex();
        QStringList sdata = leData->text().split(" ",QString::SkipEmptyParts);
        ok = true;
        if((sdata.size()>0) && (sdata.size()<=8))
        {
            for(i=0;i<sdata.size();i++)
            {
                bool iOk;
                data[i] = sdata[i].toLong(&iOk,16);
                if(!iOk)
                {
                    ok = false;
                }
            }
            for(;i<8;i++)
            {
                data[i] = 0x55;
            }
        }
        else
        {
            ok = false;
        }

        if(ok)
        {
            this->Transmit(bus,id,8,data);
        }
        else
        {
            QMessageBox::warning(this,"Invalid Data",QString("Invalid Data: \" %1 \"" ).arg(leData->text()));
        }
    }
    else
    {
        QMessageBox::warning(this,"Invalid Id",QString("Invalid Id: \" %1 \"").arg(leId->text()));
    }
}

void arCan::createGui(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {   /* create trace */
        #if (cfgDISPLAY_BY_TABLE == 1)
        tableTrace = new QTableWidget();
        QStringList  list;
        list<<"from"<<"Bus"<<"Rel(ms)"<<"Dir"<<"Id"<<"dlc"<<"B0"<<"B1"<< "B2"<< "B3"<< "B4"<< "B5"<< "B6"<< "B7";
        tableTrace->setColumnCount(list.size());
        tableTrace->setRowCount(0);
        tableTrace->setHorizontalHeaderLabels(list);
        tableTrace->setColumnWidth(0,150);
        tableTrace->setColumnWidth(1,60);
        tableTrace->setColumnWidth(2,150);
        tableTrace->setColumnWidth(3,60);
        tableTrace->setColumnWidth(4,80);
        for(int i=5;i<list.size();i++)
        {
            tableTrace->setColumnWidth(i,60);
        }
        vbox->addWidget(tableTrace);
        #else
        textTrace = new QTextEdit();
        textTrace->setReadOnly(true);
        vbox->addWidget(textTrace);
        rxSize = 0;
        #endif
    }

    {   // create control
        QPushButton* button;
        QHBoxLayout* hbox = new QHBoxLayout();

        button = new QPushButton("Clear Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(on_btnClearTrace_clicked()));
        hbox->addWidget(button);

        button = new QPushButton("Save Trace");
        this->connect(button,SIGNAL(clicked()),this,SLOT(on_btnSaveTrace_clicked()));
        hbox->addWidget(button);

        btnHexlDeci = new QPushButton("Hexl");
        this->connect(btnHexlDeci,SIGNAL(clicked()),this,SLOT(on_btnHexlDeci_clicked()));
        hbox->addWidget(btnHexlDeci);
        btnHexlDeci->setDisabled(true); // TODO

        btnAbsRelTime = new QPushButton("Absolute Time");
        this->connect(btnAbsRelTime,SIGNAL(clicked()),this,SLOT(on_btnAbsRelTime_clicked()));
        hbox->addWidget(btnAbsRelTime);
        #if (cfgDISPLAY_BY_TABLE == 1)
        #else
        btnAbsRelTime->setDisabled(true);
        #endif
        displayTimeInReal = true;
        hbox->setSpacing(20);

        vbox->addItem(hbox);
    }
    // automatic send
    {
        QHBoxLayout* hbox = new QHBoxLayout();
        QLabel *label = new QLabel("Bus:");
        QPushButton *button;
        hbox->addWidget(label);
        cbBus = new QComboBox();
        for(unsigned long i=0;i<channelNumber;i++)
        {
            cbBus->addItem(QString("%1").arg(i));
        }
        cbBus->setCurrentIndex(0);
        hbox->addWidget(cbBus);

        label = new QLabel("Id:");
        hbox->addWidget(label);
        leId = new QLineEdit();
        hbox->addWidget(leId);
        leId->setMaximumWidth(50);
        leId->setText("731");

        label = new QLabel("Data:");
        hbox->addWidget(label);
        leData = new QLineEdit();
        hbox->addWidget(leData);
        leData->setText(("55 55 55 55 55 55 55 55"));

        button = new QPushButton("Trigger Tx");
        connect(button,SIGNAL(clicked()),this,SLOT(on_btnTriggerTx_clicked()));
        hbox->addWidget(button);

        hbox->setSpacing(5);

        vbox->addItem(hbox);
    }

    widget->setLayout(vbox);
    this->setCentralWidget(widget);
}

