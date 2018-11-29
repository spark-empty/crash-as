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
#include "arshell.h"
#include "entry.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

arShell::arShell(QString name,QWidget *parent)  : arDevice(name,parent)
{
    createGui();
    setGeometry(650,50,800,50);

    setVisible(true);
}
arShell::~arShell()
{

}
void arShell::addEcu(QString name)
{
    cbEcu->addItem(name);
}

void arShell::removeEcu(QString name)
{
    cbEcu->removeItem(cbEcu->findText(name));
}

void arShell::createGui(void)
{
    QWidget* widget= new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout();

    {
           QHBoxLayout* hbox = new QHBoxLayout();
           QLabel *label = new QLabel("to Ecu:");
           QPushButton *button;
           hbox->addWidget(label);
           cbEcu = new QComboBox();
           cbEcu->setCurrentIndex(0);
           hbox->addWidget(cbEcu);

           label = new QLabel("Command:");
           hbox->addWidget(label);

           leCmd = new QLineEdit();
           hbox->addWidget(leCmd);
           leCmd->setText(("lua d:/repository/as/com/as.tool/lua/script/flashloader.lua"));

           button = new QPushButton("send");
           connect(button,SIGNAL(clicked()),this,SLOT(on_btnSendCommand_clicked()));
           hbox->addWidget(button);

           hbox->setSpacing(5);

           vbox->addItem(hbox);
       }

    widget->setLayout(vbox);
    this->setCentralWidget(widget);
}

void arShell::on_btnSendCommand_clicked(void)
{
    Entry::Self()->Shell_Write(cbEcu->currentText(),leCmd->text());
}
