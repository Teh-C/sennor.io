#include "serialport.h"
#include <QMessageBox>
#include <qDebug>
SerialPort::SerialPort(SerialConfigInfo *serialConfigInfo):
    serialConfigInfo(serialConfigInfo)
{
    initSlots();
}

SerialPort::SerialPort()
{

    initSlots();
}
SerialPort::~SerialPort()
{

}



// 函数：打开串口
// 描述：打开串口前，检查串口配置是否正确，无误后将开启串口。
SerialConfigInfo::Serial_Err SerialPort::openSerial()
{
    // 尝试从MainTab中传递过来的serialConfigInfo判断串口名称是否正确
//    if(serialConfigInfo->serialPortNum.contains("com", Qt::CaseInsensitive))
//    {
            serialPort.setPortName(serialConfigInfo->serialPortNum);
            serialPort.setBaudRate(serialConfigInfo->baudRateValue.toInt());
            serialPort.setDataBits(QSerialPort::DataBits(serialConfigInfo->dataBitsValue.toInt()));
            serialPort.setStopBits(QSerialPort::StopBits(serialConfigInfo->stopBitsValue.toInt()));
            serialPort.setParity(QSerialPort::Parity(serialConfigInfo->parityValue.toInt()));
            if(!serialPort.open(QIODevice::ReadWrite))
                return SerialConfigInfo::Serial_Err::SERIAL_OPEN_FAILED;
        return SerialConfigInfo::Serial_Err::SERIAL_OK;
//    }
    return SerialConfigInfo::Serial_Err::SERIAL_UNCONFIG;
}

// 接口：closeSerial
// 描述：仅仅通过QSerialPort提供的close()接口释放串口资源。
void SerialPort::closeSerial()
{
    serialPort.close();         // 关闭串口操作
}

// 接口：setSerialConfigInfo
// 描述：设置SerialConfigInfo
void SerialPort::setSerialConfigInfo(SerialConfigInfo *serialConfigInfo)
{
    this->serialConfigInfo = serialConfigInfo;
}

// 接口:initSlots
// 描述：连接信号槽
void SerialPort::initSlots()
{
    // Qt5.8之后不支持WIN XP，为了支持WIN XP，加入以下判断，因为5.8版本的errorOccurred在5.6版本中使error
    #if (QT_VERSION <= QT_VERSION_CHECK(5,8,0))
        connect(&serialPort, SIGNAL(error(QSerialPort::SerialPortError)),this, SLOT(serialError(QSerialPort::SerialPortError)));
    #else
        connect(&serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this, SLOT(serialError(QSerialPort::SerialPortError)));
    #endif
}

// 接口：serialError
// 描述：串口错误处理
void SerialPort::serialError(QSerialPort::SerialPortError error)
{
    qDebug() << error;
    if(error != QSerialPort::NoError)
    {
        switch(error)
        {
        // 串口无效(串口意外移除)
        case QSerialPort::ResourceError:
            QMessageBox::warning(NULL,
                                 "错误",
                                 "当前串口意外断开，检查无误后请再重新连接。",
                                 QMessageBox::Ok);
            break;

        // 串口无法打开(串口被占用了)
        case QSerialPort::OpenError:        // 重复打开
        case QSerialPort::PermissionError:  // 串口被其他设备占用
            QMessageBox::warning(NULL,
                                 "错误",
                                 "当前串口已被占用！",
                                 QMessageBox::Ok);
            break;
        // 串口号未找到
        case QSerialPort::DeviceNotFoundError:
            QMessageBox::warning(NULL,
                                 "错误",
                                 "未找到当前串口，请检查无误后再重新连接！",
                                 QMessageBox::Ok);
            break;
        // 未知错误产生(此处为了防止设置端口号名称不符合"COM"产生错误，当然这个是否能正常响应仍未测试过)
        case QSerialPort::UnknownError:
           QMessageBox::warning(NULL,
                             "错误",
                             "未知错误产生！",
                             QMessageBox::Ok);
          break;
        // 其他错误暂不处理
        default:
            break;
        }
        emit serialErrorOccurred();
    }
}
