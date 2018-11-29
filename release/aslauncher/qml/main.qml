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
import QtQuick 2.0
import Process 1.0

Rectangle {
    width: 300; height: 400
    color: "white"

    ListModel {
        id: appModel
        ListElement { name: "asone"; icon: "https://www.python.org/static/img/python-logo.png" }
        ListElement { name: "core-cfg"; icon: "http://www.arccore.com/images/logo.png" }
        ListElement { name: "boot-cfg"; icon: "http://www.arccore.com/images/logo.png" }
        ListElement { name: "aslua"; icon: "http://www.lua.org/images/lua.gif" }
        ListElement { name: "asboot"; icon: "https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/NewTux.svg/150px-NewTux.svg.png" }
        ListElement { name: "ascore"; icon: "http://www.autosar.org/typo3conf/templates/images/logo.png" }
    }
//! [0]
    GridView {
        anchors.fill: parent
        cellWidth: 100; cellHeight: 100
        focus: true
        model: appModel

        highlight: Rectangle { width: 80; height: 80; color: "lightsteelblue" }

        delegate: Item {
            width: 100; height: 100

            Image {
                id: myIcon
                y: 20; 
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.fill: parent
                anchors.margins: 20
                source: icon
            }
            Process {
                id: process
                onReadyRead: text.text = readAll();
            }

            Text {
                anchors { top: myIcon.bottom; horizontalCenter: parent.horizontalCenter }
                text: name
            }
            MouseArea {
                anchors.fill: parent
                onClicked: { parent.GridView.view.currentIndex = index;
                    if(index==0) {
                        process.setPWD("/home/parai/workspace/as/com/as.tool/as.one.py")
                        process.start("python3",["main.py"]);
                    }
                    else if(index==1) {
                        process.setPWD("/home/parai/workspace/as/com/as.tool/config.infrastructure.system");
                        process.start("python3",["studio.py","/home/parai/workspace/as/release/ascore/src/posix-tinyos-posix-gcc"]);
                    }
                    else if(index==2) {
                        process.setPWD("/home/parai/workspace/as/com/as.tool/config.infrastructure.system");
                        process.start("python3",["studio.py","/home/parai/workspace/as/release/asboot/src/posix-posix-gcc"]);
                    }
                    else if(index==3) {
                        process.setPWD("/home/parai/workspace/as/com/as.tool/lua/script")
                        process.start("gnome-terminal",[]);
                    }
                    else if(index==4) {
                        process.setPWD("/home/parai/workspace/as/release/asboot/out")
                        process.start("gnome-terminal",[]);
                    }
                    else if(index==5) {
                        process.setPWD("/home/parai/workspace/as/release/ascore/out")
                        process.start("gnome-terminal",[]);
                    }
                    else {}

                }
            }
        }
    }
//! [0]
}
