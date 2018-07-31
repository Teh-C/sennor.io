#ifndef MAINTAB_H
#define MAINTAB_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMouseEvent>
#include "./serialPort/serialconfiginfo.h"
#include "./serialPort/serialport.h"

namespace Ui {
class MainTab;
}

class MainTab : public QWidget
{
    Q_OBJECT

public:
    explicit MainTab(QWidget *parent = 0);
    ~MainTab();

private:
    Ui::MainTab *ui;
    SerialConfigInfo serialConfigInfo;
    SerialPort *serialPort;
    bool serialStatus;

    void initUI();
    void serialUIInit();
    void initSlots();

    void resetUI(bool isSerialOpen);
    void refreshSerialPort();

private slots:
    void openSerialBtn_clicked();
    void closeSerialBtn_clicked();
protected:

    virtual void mouseMoveEvent(QMouseEvent *event);



};

#endif // MAINTAB_H
