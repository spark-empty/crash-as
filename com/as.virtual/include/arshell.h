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
#ifndef ARSHELL_H_
#define ARSHELL_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "ardevice.h"
/* ============================ [ MACROS    ] ====================================================== */
#define SHELL_DEVICE_NAME   "Shell"
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
class arShell : public arDevice
{
    Q_OBJECT
private:
    QComboBox* cbEcu;
    QLineEdit* leCmd;
public:
    explicit arShell(QString name,QWidget *parent=0);

    void addEcu(QString name);
    void removeEcu(QString name);
    ~arShell();
private slots:
	void on_btnSendCommand_clicked(void);
private:
	void createGui(void);
signals:
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* ARSHELL_H_ */
