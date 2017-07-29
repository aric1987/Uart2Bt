#include "uart2bt_device.h"

static QByteArray HeadByteArray("BT", 2);
static QByteArray TailByteArray("U", 1);

static void calc_check_value(const ui8 byte[], si32 byteLen, ui8 checkValueByte[], si32 checkValueByteNum)
{
    ui32 crc = crc_calc_32bits(0, byte, byteLen);
    cmd_parser_encode_little_endian_uint(crc, checkValueByte, checkValueByteNum);
}

Uart2BtDevice::Uart2BtDevice(QString name, QObject *parent) : serialPort(name, parent), cmdParser(335, HeadByteArray, TailByteArray)
{
    cmdParser.setPrefixLen(1);
    cmdParser.configDataLen(2, true);
    cmdParser.configCheckValue(4, calc_check_value);
    cmdParser.setTimeout(500);
    connect(&cmdParser, SIGNAL(newCmd(const ui8*,const ui8*,ui32)), this, SLOT(processReply(const ui8*,const ui8*,ui32)));
}

bool Uart2BtDevice::open()
{
    if(!serialPort.open(QIODevice::ReadWrite))
    {
        return false;
    }
    if(!serialPort.setBaudRate(QSerialPort::Baud115200) ||
            !serialPort.setDataBits(QSerialPort::Data8) ||
            !serialPort.setStopBits(QSerialPort::OneStop) ||
            !serialPort.setParity(QSerialPort::NoParity) ||
            !serialPort.setFlowControl(QSerialPort::NoFlowControl))
    {
        serialPort.close();
        return false;
    }

    return true;
}

void Uart2BtDevice::setPortName(QString name)
{
    serialPort.setPortName(name);
}

void Uart2BtDevice::close()
{
    serialPort.close();
}

bool Uart2BtDevice::getConfig(Uart2BtDevice::Config_ST &config)
{

}

bool Uart2BtDevice::setConfig(Uart2BtDevice::Config_ST config)
{

}

bool Uart2BtDevice::setBaudRate(ui32 baud)
{

}

bool Uart2BtDevice::sendCmd(ui8 type, ui8 *data, si32 dataLen)
{
    QByteArray prefixByteArray;
    QByteArray dataByteArray;
    QByteArray cmdByteArray;

    usleep(1000);
    prefixByteArray.append((quint8)type);
    dataByteArray.append((const char *)data, dataLen);
    cmdByteArray.resize(335);
    si32 length = cmdParser.encode(&prefixByteArray, &dataByteArray, cmdByteArray);
    if(length > 0)
    {
        serialPort.write(cmdByteArray.data(), length);
        cmdByteArray.resize(length);
    }
}

bool Uart2BtDevice::writeData(char *data, si32 datalen)
{
    int length;
    while(dataLen > 0) {
        length = dataLen;
        if(length > 300) {
            length = 300;
        }
        if(!sendCmd(CMD_TYPE_TRANSMIT_BT_TO_UART, data, length)) {
            return false;
        }
        data += length;
        dataLen -= length;
    }

    return true;
}


void Uart2BtDevice::processReply(const ui8 *prefix, const ui8 *data, ui32 dataLen)
{
    switch(prefix[0])
    {
    case CMD_TYPE_GET_CONFIG:
        if(dataLen != 8)
        {
            return;
        }
        RecvReply = true;

        break;
    case CMD_TYPE_SET_CONFIG:
        if(dataLen != 1)
        {
            return;
        }
        RecvReply = true;
        break;
    case CMD_TYPE_TRANSMIT_BT_TO_UART:
        if(dataLen != 1)
        {
            return;
        }
        break;
    case CMD_TYPE_TRANSMIT_UART_TO_BT:
        if(dataLen < 0)
        {
            return;
        }
        RecvReply = true;
        if(data > 0) {
            dataByteArray.append((const char *)data, dataLen);
        }

        break;
    }
}

QByteArray Uart2BtDevice::readAll()
{
    return dataByteArray;
}
