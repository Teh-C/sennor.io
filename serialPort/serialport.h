#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPortInfo>
#include <QSerialPort>
#include "serialconfiginfo.h"
#include <QObject>

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


    void initSlots();
private slots:
    void serialError(QSerialPort::SerialPortError error);

signals:
    void serialErrorOccurred();
    void serialNoError();
};

#endif // SERIALPORT_H
