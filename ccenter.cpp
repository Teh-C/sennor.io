#include "ccenter.h"
#include "ui_ccenter.h"
#include <QPainter>
CCenter::CCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCenter)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);

    initUI();
    initSlot();
}

CCenter::~CCenter()
{
    delete ui;
}



void CCenter::initUI()
{
    setPixmap(QPixmap(":/ui/images/center_bg.png"));

    mainLayout = new QVBoxLayout(ui->tab);
    mainTab = new MainTab(this);
    mainLayout->addWidget(mainTab);
    ui->tab->setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);
    AddFunWidget("hello", "what", new QWidget);
}

void CCenter::initSlot()
{
    connect(ui->tabWidget,
            SIGNAL(tabCloseRequested(int)),
            this,
            SLOT(SlotTabCloseRequested(int)));
    connect(ui->tabWidget,
            SIGNAL(currentChanged(int)),
            this,
            SLOT(SlotCurrentChanged(int)));
}

void CCenter::setPixmap(const QPixmap &pix)
{
    m_localPix = pix;
    update();
}


// 描述：绘制Ccenter的背景
void CCenter::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, rect().width(), rect().height(), m_localPix, 0, 0, m_localPix.width(), m_localPix.height());
}


void CCenter::SlotCurrentChanged(int index)
{


}



void CCenter::SlotTabCloseRequested(int index)
{
    for(int i = 0; i < m_lstTabWidgetIndex.count(); i++)
    {
        if(m_lstTabWidgetIndex.at(i).name == ui->tabWidget->tabText(index))
        {
            m_lstTabWidgetIndex.removeAt(i);
            ui->tabWidget->removeTab(index);
            break;
        }
    }
}

void CCenter::AddFunWidget(QString name, QString desc, QWidget *wgt)
{
   for(int i = 0; i < m_lstTabWidgetIndex.count(); i++)
   {
       // 判断名字是否已经存在该widget
       if(m_lstTabWidgetIndex.at(i).name == name)
       {
           ui->tabWidget->setCurrentWidget(m_lstTabWidgetIndex.at(i).wgt);
           ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), m_lstTabWidgetIndex.at(i).name);
           return;
       }
   }
   int index = ui->tabWidget->addTab(wgt, QIcon(":/ui/images/application"), name);
   ui->tabWidget->setCurrentIndex(index);

   struct stuTab tab;
   tab.name = name;
   tab.desc = desc;
   tab.wgt = wgt;
   m_lstTabWidgetIndex.append(tab);
}



bool CCenter::WidgetIsExist(QString name)
{
    for(int i = 0; i < m_lstTabWidgetIndex.count(); i++)
    {

        if(m_lstTabWidgetIndex.at(i).name == name)
        {
            return true;
        }
    }
    return false;
}
