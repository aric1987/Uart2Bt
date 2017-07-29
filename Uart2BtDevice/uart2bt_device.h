#ifndef UART2BT_DEVICE_H
#define UART2BT_DEVICE_H

#include "uart2btdevice_global.h"

#include <common-qt.h>
#include <QtSerialPort/QSerialPort>

class UART2BTDEVICESHARED_EXPORT Uart2BtDevice :QObject
{
    Q_OBJECT
private:

#define CMD_TYPE_GET_CONFIG						((ui8)0x10)
#define CMD_TYPE_SET_CONFIG						((ui8)0x20)
#define CMD_TYPE_TRANSMIT_BT_TO_UART			((ui8)0x30)
#define CMD_TYPE_TRANSMIT_UART_TO_BT			((ui8)0x40)
public:
    typedef enum
    {
        UART_DATA_BITS_7,
        UART_DATA_BITS_8,
        UART_DATA_BITS_NUM,
    }Uart_DataBits_ET;

    typedef enum
    {
        UART_STOP_BITS_1,
        UART_STOP_BITS_1_5,
        UART_STOP_BITS_2,
        UART_STOP_BITS_NUM,
    }Uart_StopBits_ET;

    typedef enum
    {
        UART_PARITY_NONE,
        UART_PARITY_EVEN,
        UART_PARITY_ODD,
        UART_PARITY_NUM,
    }Uart_Parity_ET;

    typedef enum
    {
        UART_FLOW_CTRL_NONE,
        UART_FLOW_CTRL_NUM,
    }Uart_FlowCtrl_ET;

    typedef struct
    {
        ui32 baud;
        ui8 dataBits;
        ui8 stopBits;
        ui8 parity;
        ui8 flowCtrl;
    }Config_ST;
private:
    QSerialPort serialPort;
    CmdParser cmdParser;
    QByteArray dataByteArray;
    Config_ST config;
signals:
    void dataReady();
private slots:
    void readSerialPortDataSlotFunc();
    void processReply(const ui8 *prefix, const ui8 *data, ui32 dataLen);
protected:
    QByteArray readAll();

public:
    Uart2BtDevice(QString name, QObject *parent = 0);
    bool open();
    void setPortName(QString name);
    void close();
    bool getConfig(Config_ST &config);
    bool setConfig(Config_ST config);
    bool setBaudRate(ui32 baud);
    bool sendCmd(ui8 type, ui8 *data, si32 dataLen);
    bool writeData(char *data, si32 datalen);
};

#endif // UART2BT_DEVICE_H
