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
#include "entry.h"
#include "arcan.h"
#include "arshell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include "arvic.h"
static class Entry* self = NULL;

Entry::Entry ( QWidget *parent )
		: QMainWindow(parent)
{
	self = this;
	this->setWindowTitle(tr("WhatsApp ( parai@foxmail.com )"));
	this->createMenuAndToolbar();

    this->setGeometry(50,50,600,20);

    //registerDevice(new arCan(CAN_DEVICE_NAME,CAN_CTRL_NUM,this));
    //registerDevice(new arShell(SHELL_DEVICE_NAME,this));
    registerDevice(new arVIC(VIC_DEVICE_NAME,this));

    //loadEcu();
}

class Entry* Entry::Self ( void )
{
	return self;
}
Entry::~Entry ( )
{
	map_device.clear(); // this in charge to destroy VirtualDevice
}

void Entry::registerDevice ( arDevice* device )
{
	if ( map_device.contains(device->Name()) )
	{
		qDebug() << "System error: Device " << device->Name() << " re-registeration!\n";
		delete device;
	}
	else
	{
		map_device[device->Name()] = device;
		QAction * action = new QAction(device->Name(),this);
		this->connect(action,SIGNAL(triggered()),device,SLOT(wakeup()));
		menuVD->addAction(action);
	}
}
void Entry::deleteDevice ( QString name )
{
	if ( map_device.contains(name) )
	{
		arDevice* device = map_device.take(name);
		delete device;
		/* menu virtual device re-build */
		menuVD->clear();
		QList<arDevice*> devices = 	map_device.values();
		for(int i=0;i<devices.size();i++)
		{
			device = devices[i];
			QAction * action = new QAction(device->Name(),this);
			this->connect(action,SIGNAL(triggered()),device,SLOT(wakeup()));
			menuVD->addAction(action);
		}
	}
	else
	{
		qDebug() << "System error: Virtual device " << name  << " delete!\n";
	}
}

arDevice* Entry::getDevice ( QString name )
{
	if ( map_device.contains(name) )
	{
		return map_device[name];
	}
	else
	{
		return NULL;
	}
}

void Entry::registerEcu ( vEcu* ecu )
{
    if ( map_ecu.contains(ecu->Name()) )
    {
        qDebug() << "System error: ECU " << ecu->Name() << " re-registeration!\n";
        delete ecu;
    }
    else
    {
        map_ecu[ecu->Name()] = ecu;
        vmEcu * action = new vmEcu(ecu,this);
        connect(startAllEcu,SIGNAL(triggered()),action,SLOT(start()));
        toolbar->addAction(action);
#ifndef __AS_CAN_BUS__
        connect(ecu,SIGNAL(Can_RxIndication(vEcu*,quint8,quint32,quint8,quint8*)),this,
                SLOT(On_Can_RxIndication(vEcu*,quint8,quint32,quint8,quint8*)));
#endif
        arShell* sh = (arShell*)getDevice(SHELL_DEVICE_NAME);
        if(sh != NULL)
        {
            sh->addEcu(ecu->Name());
        }
    }
}

void Entry::deleteEcu ( QString name )
{
    if ( map_device.contains(name) )
    {
        vEcu* ecu = map_ecu.take(name);
        delete ecu;
        /* menu virtual device re-build */
        toolbar->clear();
        QList<vEcu*> ecus = 	map_ecu.values();
        for(int i=0;i<ecus.size();i++)
        {
            ecu = ecus[i];
            QAction * action = new QAction(ecu->Name(),this);
            this->connect(action,SIGNAL(triggered()),ecu,SLOT(start()));
            toolbar->addAction(action);
        }

        arShell* sh = (arShell*)getDevice(SHELL_DEVICE_NAME);
        if(sh != NULL)
        {
            sh->addEcu(name);
        }
    }
    else
    {
        qDebug() << "System error: Virtual ECU " << name  << " delete!\n";
    }
}

vEcu* Entry::getEcu ( QString name )
{
    if ( map_ecu.contains(name) )
    {
        return map_ecu[name];
    }
    else
    {
        return NULL;
    }
}
#ifndef __AS_CAN_BUS__
void Entry::Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    vEcu* ecu;
    QList<vEcu*> ecus = 	map_ecu.values();
    for(int i=0;i<ecus.size();i++)
    {
        ecu = ecus[i];
        ecu->Can_Write(busid,canid,dlc,data);
    }
}

void Entry::On_Can_RxIndication(vEcu* fromEcu,quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    arCan* can = (arCan*)getDevice(CAN_DEVICE_NAME);
    assert(can);
    can->RxIndication(fromEcu->Name(),busid,canid,dlc,data);
    /* broadcast this message to others */
    vEcu* ecu;
    QList<vEcu*> ecus = 	map_ecu.values();
    for(int i=0;i<ecus.size();i++)
    {
        ecu = ecus[i];
        if(ecu != fromEcu)
        {
            ecu->Can_Write(busid,canid,dlc,data);
        }
        else
        {
            /* skip self */
        }
    }
}
#endif
void Entry::Shell_Write(QString ecu_name,QString cmd)
{
    vEcu* ecu = getEcu(ecu_name);
    assert(ecu);
    ecu->Shell_Write(cmd);
}
// ==================== [ SIGNALS       ] =====================================

// ==================== [ PRIVATE SLOTS ] ======================================
void Entry::open ( void )
{

}

void Entry::save ( void )
{

}

// ==================== [ PRIVATE FUNCTIONS ] ==================================
void Entry::createMenuAndToolbar ( void )
{
    toolbar = this->addToolBar("virtual machine");

	this->menuBSW = this->menuBar()->addMenu(tr("BSW"));

	this->menuVD = menuBSW->addMenu(tr("Device"));
}

void Entry::loadEcu(void)
{
    startAllEcu = new QAction("Start All",this);
    toolbar->addAction(startAllEcu);

    char* cwd = getcwd(NULL,0);
    ASLOG(OFF,cwd);
    chdir("../../out");
    char* workpath = getcwd(NULL,0);

    free(cwd);
    free(workpath);

    DIR* d = opendir(".");
    struct dirent *file;
    while((file = readdir(d)) != NULL)
    {
        if(strstr(file->d_name,".dll"))
        {
            ASLOG(OFF,"load %s\n",file->d_name);
            registerEcu(new vEcu(file->d_name));
        }
    }
    closedir(d);
}
