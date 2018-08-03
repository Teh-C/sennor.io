#include "maintab.h"
#include "ui_maintab.h"
#include <QStringList>
#include <QMessageBox>
#include "./serialPort/serialconfiginfo.h"

MainTab::MainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTab),
    serialPort(new SerialPort),
    serialStatus(false)
{
    ui->setupUi(this);

    initUI();
    serialUIInit();
    initSlots();
}

MainTab::~MainTab()
{
    delete ui;
    delete serialPort;
}

// 接口：initUI
// 描述：初始化MainTab的界面
void MainTab::initUI()
{
    refreshSerialPort();
    ui->sendWidget->setFixedHeight(60);
    ui->sendBtn->setText(tr("发送"));
    ui->sendClearBtn->setText(tr("清除发送"));
    ui->clearReceiveBtn->setText(tr("清除接收"));
    ui->sendBtn->setFixedSize(60, 24);
    ui->sendClearBtn->setFixedSize(60, 24);
    ui->serialPortLabel->setText(tr("端口号："));
    ui->baudRateLabel->setText(tr("波特率："));
    ui->dataBitLabel->setText(tr("数据位："));
    ui->stopBitLabel->setText(tr("停止位："));
    ui->parityLabel->setText(tr("奇偶校验："));

    ui->yLineEdit->setText(tr("000.00"));
    ui->yLineEdit->setReadOnly(true);
    ui->xLineEdit->setText(tr("000.00"));
    ui->xLineEdit->setReadOnly(true);
    ui->tempLineEdit->setText(tr("00.0"));
    ui->tempLineEdit->setReadOnly(true);
    ui->idLineEdit->setReadOnly(true);
    ui->rateLineEdit->setReadOnly(true);

    ui->idLabel->setText(tr("ID号："));
    ui->yLabel->setText(tr("Y轴："));
    ui->xLabel->setText(tr("X轴："));
    ui->tempLabel->setText(tr("温度："));
    ui->rateLabel->setText(tr("速率："));
    ui->openSerialBtn->setText("打开串口");
    ui->closeSerialBtn->setText("关闭串口");
    ui->openSerialBtn->setFixedWidth(80);
    ui->closeSerialBtn->setFixedWidth(80);
    ui->leftWidget->setFixedWidth(300);
    ui->clearReceiveBtn->setFixedWidth(80);


    ui->closeSerialBtn->setVisible(false);
    ui->receiveTextEdit->setReadOnly(true);

    setMouseTracking(true);
    ui->leftWidget->setMouseTracking(true);
    ui->serialPortComboBox->setMouseTracking(true);
    ui->serialWidget->setMouseTracking(true);

}

// 接口：serialUIInit
// 描述：初始化MainTabl界面中的串口设置面板
void MainTab::serialUIInit()
{
    QStringList baudRateList;
    baudRateList << "1200" << "2400" << "4800" << "9600"
                 << "14400" << "19200" << "38400" << "115200";
    ui->baudRateComboBox->addItems(baudRateList);

    ui->stopBitComboBox->addItem("1", "1");
    ui->stopBitComboBox->addItem("1.5", "3");
    ui->stopBitComboBox->addItem("2", "2");

    QStringList dataBitList;
    dataBitList << "8" << "7" << "6" << "5";
    ui->dataBitComboBox->addItems(dataBitList);

    ui->parityComboBox->addItem("无", "0");
    ui->parityComboBox->addItem("奇校验", "2");
    ui->parityComboBox->addItem("偶校验", "3");
}


// 接口：initSlots
// 描述：连接槽
void MainTab::initSlots()
{
    connect(ui->openSerialBtn, SIGNAL(clicked()), this, SLOT(openSerialBtn_clicked()));
    connect(ui->closeSerialBtn, SIGNAL(clicked()), this, SLOT(closeSerialBtn_clicked()));
    connect(serialPort, SIGNAL(serialErrorOccurred()), this, SLOT(closeSerialBtn_clicked()));
    connect(serialPort, SIGNAL(serialReceiveDate(QString)), this, SLOT(dataFromSerial(QString)));
    connect(serialPort, SIGNAL(sendDealData(QString,QString,QString,QString)),this,
            SLOT(angleFromSerial(QString,QString,QString,QString)));

    connect(ui->clearReceiveBtn, SIGNAL(clicked()), this, SLOT(clearReveiceBtn_clicked()));
}



// 接口：openSerialBtn_clicked
// 描述：打开串口操作以及界面重置
void MainTab::openSerialBtn_clicked()
{
    // 打开串口操作前，对串口信息进行赋值
    serialConfigInfo.serialPortNum = ui->serialPortComboBox->currentData().toString();
    serialConfigInfo.baudRateValue = ui->baudRateComboBox->currentText();
    serialConfigInfo.stopBitsValue = ui->stopBitComboBox->currentText();
    serialConfigInfo.dataBitsValue = ui->dataBitComboBox->currentText();
    serialConfigInfo.parityValue = ui->parityComboBox->currentText();

    serialPort->setSerialConfigInfo(&serialConfigInfo);
    int res = serialPort->openSerial();
    if(SerialConfigInfo::Serial_Err(res) == SerialConfigInfo::SERIAL_OK)
    {
        resetUI(true);
        serialStatus = true;
    }
}



// 接口：closeSerialBtn_clicked
// 描述：关闭串口操作以及界面重置
void MainTab::closeSerialBtn_clicked()
{
    // 判断串口是否曾经打开过，从而判断是否执行关闭串口操作
    if(serialStatus == true)
    {
        serialPort->closeSerial();
        serialStatus = false;
    }
    resetUI(false);
}

// 接口：resetUI
// 描述：根据串口开闭状态，设置下拉列表以及按钮控件的显隐、使能或使能状态。
void MainTab::resetUI(bool isSerialOpen)
{
    if(isSerialOpen == true)
    {
        ui->serialPortComboBox->setEnabled(false);
        ui->baudRateComboBox->setEnabled(false);
        ui->dataBitComboBox->setEnabled(false);
        ui->stopBitComboBox->setEnabled(false);
        ui->parityComboBox->setEnabled(false);
        ui->closeSerialBtn->setVisible(true);
        ui->openSerialBtn->setVisible(false);

    }else
    {
        ui->serialPortComboBox->setEnabled(true);
        ui->baudRateComboBox->setEnabled(true);
        ui->dataBitComboBox->setEnabled(true);
        ui->stopBitComboBox->setEnabled(true);
        ui->parityComboBox->setEnabled(true);
        ui->openSerialBtn->setVisible(true);
        ui->closeSerialBtn->setVisible(false);
    }
}


// 接口：refreshSerialPort
// 描述：刷新串口端口信息
void MainTab::refreshSerialPort()
{
    QString cur_str;
    QSerialPortInfo info;
    QString str;

    cur_str = ui->serialPortComboBox->currentText();    // 读取并记录当前的内容
    ui->serialPortComboBox->clear();                    // 清除serialPortComboBox
    foreach(info, QSerialPortInfo::availablePorts())    // 获取有效的端口
    {
        str = info.portName();
        str +="("+QSerialPortInfo(str).description()+")";
        ui->serialPortComboBox->addItem(str, info.portName());
    }
    ui->serialPortComboBox->setCurrentText(cur_str);
}



// 接口：mouseMoveEvent
// 描述：事件机制，通过判断鼠标是否在serialPortCOmboBox的区域内而刷新串口信息。
void MainTab::mouseMoveEvent(QMouseEvent *event)
{
    if((event->y() >= ui->serialPortComboBox->y())
            && (event->y() <= (ui->serialPortComboBox->y()
                +ui->serialPortComboBox->height())))
    {
        if((event->x() >= ui->serialPortComboBox->x())
            && (event->x() <= (ui->serialPortComboBox->x()
                +ui->serialPortComboBox->width())))
        {
           refreshSerialPort();
        }

    }
    event->accept();
}

// 接口：dataFromSerial
// 描述：从类SerialPort中提供的信号获取字符串数据
void MainTab::dataFromSerial(QString str)
{
    ui->receiveTextEdit->moveCursor(QTextCursor::End);
    ui->receiveTextEdit->insertPlainText(str);

}

// 接口：angleFromSerial
// 描述：从类SerialPort中提供的信号获取角度值等
void MainTab::angleFromSerial(QString id, QString xAngle, QString yAngle, QString temp)
{
    this->id = id;
    this->xAngle = xAngle;
    this->yAngle = yAngle;
    this->temp = temp;
    ui->idLineEdit->setText(id);
    ui->xLineEdit->setText(xAngle);
    ui->yLineEdit->setText(yAngle);
    ui->tempLineEdit->setText(temp);
}

// 接口：clearReveiceBtn_clicked
// 描述：槽函数，清除接收显示文本控件的内容
void MainTab::clearReveiceBtn_clicked()
{
    ui->receiveTextEdit->clear();
}



QString MainTab::getSennorAngle_ID()
{
    return id;
}
QString MainTab::getSennorAngle_X()
{
    return xAngle;
}
QString MainTab::getSennorAngle_Y()
{
    return yAngle;
}
QString MainTab::getSennorTemp()
{
    return temp;
}

bool MainTab::sendStringToSennor(QString str)
{
    if(serialStatus == true)
    {
        serialPort->sendStringToSerial(str);
        return serialStatus;
    }
    return serialStatus;
}
