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
#include "vEcu.h"
#include "asdebug.h"
#include <QDebug>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __WINDOWS__
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>
#include <dlfcn.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
typedef void (*aslog_t)(const char*,const char*,...);
typedef void (*setlog_t)(const char*,aslog_t);
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
vEcu::vEcu ( QString dll, QObject *parent )
    : QThread(parent),name(dll)
{
    setlog_t p_setlog;
#ifdef __WINDOWS__
    char full_path[128];
    char* cwd = getcwd(NULL,0);
    sprintf(full_path,"%s\\%s",cwd,dll.toStdString().c_str());
    hxDll = LoadLibraryA(full_path);
    free(cwd);
#else
    char* full_path = realpath(dll.toStdString().c_str(),NULL);
    hxDll = dlopen(full_path,RTLD_NOW);
    free(full_path);
#endif
    assert(hxDll);

#ifdef __WINDOWS__
    pfMain = (PF_MAIN)GetProcAddress((HMODULE)hxDll,"main");
    p_setlog  = (setlog_t)GetProcAddress((HMODULE)hxDll,"aslog_init");
#else

    pfMain = (PF_MAIN)dlsym(hxDll,"main");
    p_setlog  = (setlog_t)dlsym(hxDll,"aslog_init");
#endif

     assert(pfMain);
     assert(p_setlog);
     p_setlog(dll.toStdString().c_str(),(aslog_t)aslog);

     virtio = new Virtio(hxDll,this);

#ifndef __AS_CAN_BUS__
     connect(virtio,SIGNAL(Can_RxIndication(quint8,quint32,quint8,quint8*)),this,
             SLOT(On_Can_RxIndication(quint8,quint32,quint8,quint8*)));
#endif
}
#ifndef __AS_CAN_BUS__
void vEcu::Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    virtio->Can_Write(busid,canid,dlc,data);
}

void vEcu::On_Can_RxIndication(quint8 busid,quint32 canid,quint8 dlc,quint8* data)
{
    emit Can_RxIndication(this,busid,canid,dlc,data);
}
#endif

void vEcu::Shell_Write(QString cmd)
{
    virtio->Shell_Write(cmd);
}

vEcu::~vEcu ( )
{
#ifdef __WINDOWS__
    FreeLibrary( (HMODULE)hxDll );
#else
    dlclose(hxDll);
#endif
    delete virtio;
}

void vEcu::run(void)
{
    ASLOG(VECU,"starting the Ecu<%s>\n",name.toStdString().c_str());
    virtio->start();

    const char* argv[1];
    argv[0] = name.toStdString().c_str();
    pfMain(1,argv);
}

vmEcu::vmEcu(vEcu* ecu,QWidget* parent)
    :QAction(ecu->Name(),parent), ecu(ecu)
{
    connect(this,SIGNAL(triggered()),this,SLOT(start()));
}

void vmEcu::start(void)
{
    ASLOG(OFF,"Start ECU<%s>\n",ecu->Name().toStdString().c_str());
    ecu->start();
    setDisabled(true);
}
