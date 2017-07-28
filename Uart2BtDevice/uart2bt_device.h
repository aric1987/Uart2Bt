#ifndef UART2BT_DEVICE_H
#define UART2BT_DEVICE_H

#include "uart2btdevice_global.h"

#include <common-qt.h>
#include <QtSerialPort/QSerialPort>

class UART2BTDEVICESHARED_EXPORT Uart2BtDevice
{
    Q_OBJECT
private:
    QSerialPort *serialPort;
    CmdParser *cmdParser;
    QByteArray dataByteArray;
signals:
    void dataReady();
private slots:
    void readSerialPortDataSlotFunc();
    void processCmd(const ui8 *prefix, const ui8 *data, ui32 dataLen);
protected:
    QByteArray readAll();
public:
public:
    Uart2BtDevice(QString name, QObject *parent = 0);
    bool open();
    void close();
    bool setConfig();
    bool setBaudRate(ui32 baud);
};

#endif // UART2BT_DEVICE_H
