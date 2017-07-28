#include "uart2bt_device.h"


QByteArray Uart2BtDevice::readAll()
{

}

Uart2BtDevice::Uart2BtDevice(QString name, QObject *parent)
{
    static QByteArray head("BT");
    static QByteArray tail("U");
    serialPort = new QSerialPort(name, parent);
    cmdParser = new CmdParser(335, head, tail, parent);
}

bool Uart2BtDevice::open()
{

}

void Uart2BtDevice::close()
{

}

bool Uart2BtDevice::setBaudRate(ui32 baud)
{

}


