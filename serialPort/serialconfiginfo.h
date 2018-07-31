#ifndef SERIALCONFIGINFO_H
#define SERIALCONFIGINFO_H

#include <QString>


class SerialConfigInfo
{
public:

    enum Serial_Err{
        SERIAL_OK,
        SERIAL_UNCONFIG,
        SERIAL_OPEN_FAILED,

    };


    SerialConfigInfo():
    serialPortNum("未配置！"),
    baudRateValue("9600"),
    stopBitsValue("1"),
    dataBitsValue("8"),
    parityValue("无"){}

    QString serialPortNum;              // 串口号
    QString baudRateValue;              // 波特率值
    QString stopBitsValue;              // 停止位
    QString dataBitsValue;              // 数据位
    QString parityValue;                // 校验位
};


#endif // SERIALCONFIGINFO_H
