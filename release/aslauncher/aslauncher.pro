TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += source/main.cpp

RESOURCES += aslauncher.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    include/aslauncher.h

INCLUDEPATH += include

