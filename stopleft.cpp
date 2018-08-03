#include "stopleft.h"
#include "ui_stopleft.h"
#include <QPainter>

STopLeft::STopLeft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STopLeft)
{
    ui->setupUi(this);
    initUI();
    initSlot();
}

STopLeft::~STopLeft()
{
    delete ui;
}


void STopLeft::initUI()
{
    setFixedHeight(80);
    SetPixMap(QPixmap(":/ui/images/top_bg.png"));

    ui->m_labelLogin->setText(tr("测试版"));
    ui->m_labelNavigation->setText(tr("传感器校准平台"));
    ui->m_labelNavigation->setStyleSheet("font:22px; "
                                         "font-family: Microsoft Yahei;"
                                         "color: #FFFFFF"
                                         );

    ui->m_btnHome->setFixedSize(60, 24);
    ui->m_btnHome->setCursor(QCursor(Qt::PointingHandCursor));  // 设置hover时，光标的形状
    ui->m_btnHome->setStyleSheet(
            "QToolButton{border-image:url(:/ui/images/home_nor.png);}"
            "QToolButton::hover{border-image:url(:/ui/images/home_hov.png);}"
            "QToolButton::pressed{border-image:url(:/ui/images/home_cli.png);}");


    ui->m_btnHelp->setFixedSize(60, 24);
    ui->m_btnHelp->setCursor(QCursor(Qt::PointingHandCursor));
    ui->m_btnHelp->setStyleSheet(
            "QToolButton{border-image:url(:/ui/images/help_nor.png);}"
            "QToolButton::hover{border-image:url(:/ui/images/help_hov.png);}"
            "QToolButton::pressed{border-image:url(:/ui/images/help_cli.png);}");

    ui->m_btnQuit->setFixedSize(60, 24);
    ui->m_btnQuit->setCursor(QCursor(Qt::PointingHandCursor));
    ui->m_btnQuit->setStyleSheet(
            "QToolButton{border-image:url(:/ui/images/quit_nor.png);}"
            "QToolButton::hover{border-image:url(:/ui/images/quit_hov.png);}"
            "QToolButton::pressed{border-image:url(:/ui/images/quit_cli.png);}");



    ui->m_btnNavigation->setFixedSize(250, 30);
    ui->m_btnNavigation->setCursor(QCursor(Qt::PointingHandCursor));
    ui->m_btnNavigation->setStyleSheet(
        "QPushButton{border-image:url(:/ui/images/nav_hov);}"
        "QPushButton::hover{border-image:url(:/ui/images/nav_hov);}"
        "QPushButton::pressed{border-image:url(:/ui/images/nav_hov);}");

    ui->m_hBoxLyout1->setContentsMargins(17, 0, 10, 0);
    ui->m_hBoxLyout1->setSpacing(20);


    ui->m_hBoxLyout2->setContentsMargins(0, 6, 0, 0);
    ui->m_hBoxLyout2->setSpacing(30);

    ui->m_hBoxLyout3->setContentsMargins(0, 0, 0, 0);
    ui->m_hBoxLyout3->setSpacing(50);

}



void STopLeft::initSlot()
{
    connect(ui->m_btnNavigation, SIGNAL(clicked()), this, SLOT(SlotNavigation()));
    connect(ui->m_btnHome, SIGNAL(clicked()), this, SLOT(homeBtn_clicked()));
    connect(ui->m_btnHelp, SIGNAL(clicked()), this, SLOT(helpBtn_clicked()));
    connect(ui->m_btnQuit, SIGNAL(clicked()), this, SLOT(quitBtn_clicked()));

}

void STopLeft::SetPixMap(const QPixmap &pix)
{
    m_localPix = pix;
}


void STopLeft::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, rect().width(), rect().height(), m_localPix, 0, 0, m_localPix.width(), m_localPix.height());
}


QPoint STopLeft::GetNavigationPos()
{
    return ui->m_btnNavigation->pos();
}


void STopLeft::SlotNavigation()
{
   emit SigNavigation();
}


void STopLeft::helpBtn_clicked()
{
    emit signalHelpBtn_clicked();
}

void STopLeft::homeBtn_clicked()
{
    emit signalHomeBtn_clicked();
}
void STopLeft::quitBtn_clicked()
{
    emit signalquitBtn_clicked();
}


void STopLeft::setTitleText(QString name)
{
    ui->m_labelNavigation->setText(name);
}
