#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QPoint>
#include "stopleft.h"
#include "stopright.h"
#include "menu.h"
#include "ccenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void moveEvent(QMoveEvent *e);
    virtual void hideEvent(QHideEvent *e);

    virtual void mousePressEvent(QMouseEvent *e);



private:
    Ui::MainWindow  *ui;
    QHBoxLayout     *mtopLayout;
    STopLeft        *topLeft;
    STopRight       *topRight;
    Menu            *menu;
    CCenter         *center;
    bool            isMenuHide;
    QHBoxLayout     *centerLayout;

    void mainInit();
    void initSolt();
    void menuInit();
    void MenuConnectCCenter();

private slots:
    void slotNavigation();
    void dealSignalHomeBtn_clicked();
    void dealSignalHelpBtn_clicked();

    void Fun1();
    void Fun2();
    void Fun3();
    void Fun4();
    void Fun5();
    void Fun6();
    void Fun7();
    void Fun8();
};

#endif // MAINWINDOW_H
