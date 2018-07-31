#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPortInfo>
#include <QSerialPort>
#include "serialconfiginfo.h"
#include <QObject>
#include <QTimer>
class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(SerialConfigInfo *serialConfigInfo);
    SerialPort();
    ~SerialPort();

    SerialConfigInfo::Serial_Err openSerial();
    void closeSerial();

    void setSerialConfigInfo(SerialConfigInfo *serialConfigInfo);

private:
    SerialConfigInfo *serialConfigInfo;
    QSerialPort serialPort;
    QString strSum;



    void initSlots();
private slots:
    void serialError(QSerialPort::SerialPortError error);
    void receive_data(void);

signals:
    void serialErrorOccurred();
    void serialNoError();
    void serialReceiveDate(QString str);
    void sendDealData(QString id, QString xAngle, QString yAngle, QString temp);
};

#endif // SERIALPORT_H
