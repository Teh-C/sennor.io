#ifndef CCENTER_H
#define CCENTER_H

#include <QWidget>
#include <QPixmap>
#include <QList>
#include <QVBoxLayout>
#include "./function/maintab.h"
namespace Ui {
class CCenter;
}

class CCenter : public QWidget
{
    Q_OBJECT

public:
    struct stuTab
    {
        QString name;
        QString desc;
        QWidget *wgt;
    };



public:
    explicit CCenter(QWidget *parent = 0);
    ~CCenter();
    MainTab *mainTab;

    void AddFunWidget(QString name, QString desc, QWidget *wgt);
    bool WidgetIsExist(QString name);

protected:
    void paintEvent(QPaintEvent *e);
private:
    Ui::CCenter *ui;

    void initUI();
    void initSlot();
    void setPixmap(const QPixmap &pix);
    QPixmap m_localPix;
    QList<struct stuTab> m_lstTabWidgetIndex;


    QVBoxLayout *mainLayout;

private slots:
    void SlotCurrentChanged(int index);
    void SlotTabCloseRequested(int index);
};

#endif // CCENTER_H
