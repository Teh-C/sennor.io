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

private slots:
    void slotNavigation();
};

#endif // MAINWINDOW_H
