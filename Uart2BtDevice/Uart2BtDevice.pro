#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T21:53:25
#
#-------------------------------------------------

QT       -= gui

TARGET = Uart2BtDevice
TEMPLATE = lib

DEFINES += UART2BTDEVICE_LIBRARY

SOURCES += uart2bt_device.cpp

HEADERS += uart2bt_device.h\
        uart2btdevice_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
LIBS += -lcommon-qt -lQtSerialPort -lcommon-c
