#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
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
    QToolButton *toolBtn1 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun1_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun1_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun1_cli);}"
                );

    QToolButton *toolBtn2 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun2_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun2_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun2_cli);}"
                );
    QToolButton *toolBtn3 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun3_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun3_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun3_cli);}"
                );
    QToolButton *toolBtn4 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun4_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun4_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun4_cli);}"
                );
    QToolButton *toolBtn5 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun5_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun5_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun5_cli);}"
                );
    QToolButton *toolBtn6 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun6_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun6_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun6_cli);}"
                );
    QToolButton *toolBtn7 = menu-> addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun7_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun7_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun7_cli);}"
                );
    QToolButton *toolBtn8 = menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun8_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun8_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun8_cli);}");

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
    center->AddFunWidget(tr("单轴校准"), NULL, oneSensor);
    oneSensor->setMainTab(center->mainTab);
    menu->hide();
}
void MainWindow::Fun2(){
    DoubleSensor *doubleSensor = new DoubleSensor;
    center->AddFunWidget(tr("双轴校准"), NULL, doubleSensor);
    doubleSensor->setMainTab(center->mainTab);
    menu->hide();
}
void MainWindow::Fun3(){}
void MainWindow::Fun4(){}
void MainWindow::Fun5(){}
void MainWindow::Fun6(){}
void MainWindow::Fun7(){}
void MainWindow::Fun8(){}


