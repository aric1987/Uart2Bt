#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "../Uart2BtDevice/uart2bt_device.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Uart2BtDevice *uart2BtDevice;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAIN_WINDOW_H
