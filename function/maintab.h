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
    QString getSennorAngle_ID();
    QString getSennorAngle_X();
    QString getSennorAngle_Y();
    QString getSennorTemp();
    bool sendStringToSennor(QString str);

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


    QString id;
    QString xAngle;
    QString yAngle;
    QString temp;

private slots:
    void openSerialBtn_clicked();
    void closeSerialBtn_clicked();
    void dataFromSerial(QString str);
    void angleFromSerial(QString id, QString xAngle, QString yAngle, QString temp);
    void clearReveiceBtn_clicked();


protected:

    virtual void mouseMoveEvent(QMouseEvent *event);



};

#endif // MAINTAB_H
