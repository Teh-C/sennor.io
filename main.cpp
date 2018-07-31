#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "menu.h"
#include "ccenter.h"
#include "./function/maintab.h"

#include "./function/maintab.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/qss/m.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
       qApp->setStyleSheet(qss);
        file.close();
    }
    MainWindow w;
    w.show();

    return a.exec();
}
