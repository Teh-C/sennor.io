#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QList>
#include <QToolButton>
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();


    void addNewToolBtn(QToolButton *btn,int w, int h, QString text, QString style);
    void addNewSpacer();

private:
    Ui::Menu *ui;
    void menuInit();
    void slotInit();
    QList<QToolButton *> toolBtnList;

    int moveIndex;
    int currentIndex;




 private slots:
    void upBtn_clicked();
    void downBnt_clicked();
};

#endif // MENU_H
