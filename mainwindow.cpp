#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isMenuHide(true)
{
    ui->setupUi(this);
    mainInit();
    initSolt();
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
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun1_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun1_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun1_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun2_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun2_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun2_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun3_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun3_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun3_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun4_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun4_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun4_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun5_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun5_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun5_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun6_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun6_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun6_cli);}"
                );
    menu-> addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun7_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun7_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun7_cli);}"
                );
    menu->addNewToolBtn(new QToolButton,
                  240, 34,
                  QString::null,
                  "QToolButton{border-image:url(:/ui/images/fun8_nor)}"
                  "QToolButton::hover{border-image:url(:/ui/images/fun8_hov);}"
                  "QToolButton::pressed{border-image:url(:/ui/images/fun8_cli);}");
}

MainWindow::~MainWindow()
{
    delete ui;
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
    Q_UNUSED(e);
    QPoint p = topLeft->GetNavigationPos();
    p = mapToGlobal(p);
    p.setY(p.y() + 37);
    menu->move(p);
    update();
}\

void MainWindow::hideEvent(QHideEvent *e)
{
    Q_UNUSED(e);
    if (menu->isHidden())
        isMenuHide = true;
    else
    {
        isMenuHide = false;
        menu->hide();
    }
}
