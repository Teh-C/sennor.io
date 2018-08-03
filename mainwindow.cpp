#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
#include <QPushButton>
#include <./function/onesensor.h>
#include <./function/doublesensor.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isMenuHide(true)
{
    ui->setupUi(this);
    mainInit();
    initSolt();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainInit()
{
    setMinimumSize(1000, 600);

    topLeft = new STopLeft;
    topRight = new STopRight;
    center = new CCenter(ui->centralWidget);

    mtopLayout = new QHBoxLayout(ui->mtop);
    mtopLayout->addWidget(topLeft);
    mtopLayout->addWidget(topRight);
    mtopLayout->setContentsMargins(0,0,0,0);
    mtopLayout->setSpacing(0);

    QLayout *mainLayout = ui->centralWidget->layout();
    mainLayout->addWidget(center);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    menuInit();
}

void MainWindow::menuInit()
{
    menu = new Menu(ui->centralWidget);
    menu->setCCenter(center);
    QPushButton *toolBtn1 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("单轴传感器校准"),
                  "QPushButton{border-image:url(:/ui/images/fun3_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                  "QPushButton:hover{border-image:url(:/ui/images/fun3_hov);color:#e3f9fc;}"
                  "QPushButton:pressed{border-image:url(:/ui/images/fun3_cli);color:#e8fdff;}"
                );

    QPushButton *toolBtn2 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("双轴传感器校准"),
                "QPushButton{border-image:url(:/ui/images/fun3_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun3_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun3_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn3 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                 tr("数据图表分析"),
                "QPushButton{border-image:url(:/ui/images/fun5_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun5_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun5_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn4 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("测试1"),
                "QPushButton{border-image:url(:/ui/images/fun1_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun1_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun1_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn5 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("测试2"),
                "QPushButton{border-image:url(:/ui/images/fun2_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun2_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun2_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn6 = menu->addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("测试3"),
                "QPushButton{border-image:url(:/ui/images/fun3_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun3_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun3_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn7 = menu-> addNewToolBtn(new QPushButton,
                  240, 34,
                  tr("测试4"),
                 "QPushButton{border-image:url(:/ui/images/fun4_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                 "QPushButton:hover{border-image:url(:/ui/images/fun4_hov);color:#e3f9fc;}"
                 "QPushButton:pressed{border-image:url(:/ui/images/fun4_cli);color:#e8fdff;}"
                );
    QPushButton *toolBtn8 = menu->addNewToolBtn(new QPushButton,
                240, 34,
                tr("测试5"),
                "QPushButton{border-image:url(:/ui/images/fun6_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                "QPushButton:hover{border-image:url(:/ui/images/fun6_hov);color:#e3f9fc;}"
                "QPushButton:pressed{border-image:url(:/ui/images/fun6_cli);color:#e8fdff;}"
                );
    menu->addNewToolBtn(new QPushButton,
                    240, 34,
                    tr("测试6"),
                    "QPushButton{border-image:url(:/ui/images/fun6_nor);color:#0089a0;font-size:13px;font-weight:bold;}"
                    "QPushButton:hover{border-image:url(:/ui/images/fun6_hov);color:#e3f9fc;}"
                    "QPushButton:pressed{border-image:url(:/ui/images/fun6_cli);color:#e8fdff;}"
                    );

    menu->addNewSpacer();
    connect(toolBtn1, SIGNAL(clicked()), this, SLOT(Fun1()));
    connect(toolBtn2, SIGNAL(clicked()), this, SLOT(Fun2()));
}


void MainWindow::slotNavigation()
{
    QPoint p = topLeft->GetNavigationPos();
    p = mapToGlobal(p);
    p.setY(p.y() + 37);
    menu->move(p);
    if (menu->isHidden())
        menu->show();
    else
        menu->hide();
    update();
}


void MainWindow::initSolt()
{
    connect(topLeft, SIGNAL(SigNavigation()), this, SLOT(slotNavigation()));
    connect(topLeft, SIGNAL(signalHelpBtn_clicked()), this, SLOT(dealSignalHelpBtn_clicked()));
    connect(topLeft, SIGNAL(signalHomeBtn_clicked()), this, SLOT(dealSignalHomeBtn_clicked()));
    connect(topLeft, SIGNAL(signalquitBtn_clicked()), this, SLOT(dealSignalQuitBtn_clicked()));
    connect(center, SIGNAL(CcenterCurrentChanged(QString)), topLeft, SLOT(setTitleText(QString)));
}



void MainWindow::moveEvent(QMoveEvent *e)
{
    Q_UNUSED(e);
    QPoint p = topLeft->GetNavigationPos();
    p = mapToGlobal(p);
    p.setY(p.y() + 37);
    menu->move(p);
    update();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QPoint p = topLeft->GetNavigationPos();
    p = mapToGlobal(p);
    p.setY(p.y() + 37);
    menu->move(p);
    update();
    e->accept();
}\

void MainWindow::hideEvent(QHideEvent *e)
{
    if (menu->isHidden())
        isMenuHide = true;
    else
    {
        isMenuHide = false;
        menu->hide();
    }
    e->accept();
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{

    menu->hide();
    e->accept();
}


void MainWindow::Fun1(){
    OneSensor *oneSensor = new OneSensor;
    center->AddFunWidget(tr("单轴传感器校准"), NULL, oneSensor);
    oneSensor->setMainTab(center->mainTab);
    menu->hide();
}
void MainWindow::Fun2(){
    DoubleSensor *doubleSensor = new DoubleSensor;
    center->AddFunWidget(tr("双轴传感器校准"), NULL, doubleSensor);
    doubleSensor->setMainTab(center->mainTab);
    menu->hide();
}
void MainWindow::Fun3(){}
void MainWindow::Fun4(){}
void MainWindow::Fun5(){}
void MainWindow::Fun6(){}
void MainWindow::Fun7(){}
void MainWindow::Fun8(){}



void MainWindow::dealSignalHelpBtn_clicked()
{
    center->AddFunWidget(tr("帮助"), NULL, new QWidget);
    menu->hide();
}

void MainWindow::dealSignalHomeBtn_clicked()
{
    center->setDefaultWidget();
}


void MainWindow::dealSignalQuitBtn_clicked()
{
     qApp->exit(0);
}
