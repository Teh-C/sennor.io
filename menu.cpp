#include "menu.h"
#include "ui_menu.h"
#include <QLayout>
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu),
    moveIndex(0),
    currentIndex(0)
{
    ui->setupUi(this);
    menuInit();
    slotInit();
}

Menu::~Menu()
{
    delete ui;
    QToolButton *btn;
    foreach (btn, toolBtnList) {
        delete btn;
    }
}


void Menu::menuInit()
{
    setFixedWidth(250);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    ui->btnUp->setFixedSize(250, 20);
    ui->btnUp->setText(QString::null);
    ui->btnUp->setCursor(QCursor(Qt::PointingHandCursor));
    ui->btnUp->setStyleSheet(
                "QToolButton{border-image:url(:/ui/images/arr_up_nor);}"
                "QToolButton::hover{border-image:url(:/ui/images/arr_up_hov);}"
                "QToolButton::pressed{border-image:url(:/ui/images/arr_up_cli);}");


    ui->btnDown->setFixedSize(250,20);
    ui->btnDown->setText(QString::null);
    ui->btnDown->setCursor(QCursor(Qt::PointingHandCursor));
    ui->btnDown->setStyleSheet(
                "QToolButton{border-image:url(:/ui/images/arr_down_nor);}"
                "QToolButton::hover{border-image:url(:/ui/images/arr_down_hov);}"
                "QToolButton::pressed{border-image:url(:/ui/images/arr_down_cli);}"
                );

    QLayout *menuLayout = this->layout();
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setSpacing(0);

    ui->btnWidget->layout()->setContentsMargins(5,9,9,9);
    ui->btnWidget->layout()->setSpacing(10);
}

void Menu::slotInit()
{
    connect(ui->btnUp, SIGNAL(clicked()), this, SLOT(upBtn_clicked()));
    connect(ui->btnDown, SIGNAL(clicked()), this, SLOT(downBnt_clicked()));
}

QToolButton  *Menu::addNewToolBtn(QToolButton *btn,int w, int h, QString text, QString style)
{
    toolBtnList.append(btn);
    btn->setFixedSize(w, h);
    btn->setText(text);
    btn->setCursor(QCursor(Qt::PointingHandCursor));
    btn->setStyleSheet(style);
    ui->btnWidget->layout()->addWidget(btn);
    if(toolBtnList.count() > 8)
        btn->hide();
    return btn;
}

void Menu::upBtn_clicked()
{
    if(moveIndex > 0)
    {
        moveIndex--;
        toolBtnList.at(moveIndex+8)->hide();
        toolBtnList.at(moveIndex)->show();
    }
}

void Menu::downBnt_clicked()
{
    if(moveIndex < (toolBtnList.count() - 8))
    {
        toolBtnList.at(moveIndex)->hide();
        toolBtnList.at(moveIndex+8)->show();
        moveIndex++;
    }
}


void Menu::setCCenter(CCenter *ccenter)
{
    this->ccenter = ccenter;
}

