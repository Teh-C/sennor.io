#ifndef STOPLEFT_H
#define STOPLEFT_H

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
namespace Ui {
class STopLeft;
}

class STopLeft : public QWidget
{
    Q_OBJECT

public:
    explicit STopLeft(QWidget *parent = 0);
    ~STopLeft();


    QPoint GetNavigationPos();


protected:
    void paintEvent(QPaintEvent *e);
private:
    Ui::STopLeft *ui;
    void initUI();
    void initSlot();


    QPixmap m_localPix;
    void SetPixMap(const QPixmap &pix);
signals:
    void SigNavigation();
    void signalHomeBtn_clicked();
    void signalHelpBtn_clicked();
    void signalquitBtn_clicked();

private slots:
    void SlotNavigation();
    void homeBtn_clicked();
    void helpBtn_clicked();
    void quitBtn_clicked();
    void setTitleText(QString name);
};

#endif // STOPLEFT_H
