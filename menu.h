#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <ccenter.h>
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();


    QPushButton *addNewToolBtn(QPushButton *btn,int w, int h, QString text, QString style);
    void addNewSpacer();
    void setCCenter(CCenter *ccenter);
private:
    Ui::Menu *ui;
    CCenter *ccenter;
    void menuInit();
    void slotInit();
    QList<QPushButton *> toolBtnList;

    int moveIndex;
    int currentIndex;




 private slots:
    void upBtn_clicked();
    void downBnt_clicked();
};

#endif // MENU_H
