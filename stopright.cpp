#include "stopright.h"
#include "ui_stopright.h"
#include <QPixmap>

STopRight::STopRight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STopRight)
{
    ui->setupUi(this);
    setFixedSize(220, 80);
    SetPixmap((QPixmap(":/ui/images/top_right.png")));
}

STopRight::~STopRight()
{
    delete ui;
}


void STopRight::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(0, 0, rect().width(), rect().height(), m_localPix, 0, 0, m_localPix.width(), m_localPix.height());
}
void STopRight::SetPixmap(const QPixmap &pix)
{
    m_localPix = pix;
    update();
}
