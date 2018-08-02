#ifndef ONESENSOR_H
#define ONESENSOR_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QSerialPort>
#include <QMessageBox>
#include <QGridLayout>
#include <QItemSelectionModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QSqlError>
#include "./function/maintab.h"
namespace Ui {
class OneSensor;
}

class OneSensor : public QWidget
{
    Q_OBJECT

public:
    explicit OneSensor(QWidget *parent = 0);
    ~OneSensor();

    void setMainTab(MainTab *mainTab);
private:
    Ui::OneSensor *ui;


    enum calibrationError{
        NO_ERROR,
        VALUE_NULL_ERROR,
    };

private slots:
    void GetAngleValue();
    void deleteLastAngleValue();
    int CountKbValue(void);
    void SetKbValue(void);
    void ResetKbValue(void);

    void setFilePath(void);
    void saveFile(void);

    void countDiffValue();



private:
    QTableView *tableview;
    QStandardItemModel *model;
    QLineEdit *klineedit;
    QLineEdit *blineedit;

    QPushButton *getvaluebutton;
    QPushButton *countbutton;
    QPushButton *setkbbutton;
    QPushButton *resetbutton;
    QPushButton *removeButton;

    QPushButton *setFilePathBtn;
    QPushButton *saveFileBtn;
    QString filePathStr;
    QLabel *filePathLabel;
    QLabel *deviceNumLabel;
    QLineEdit *deviceNumEdit;

    QPushButton *countDiffValueBtn;
    QItemSelectionModel *itemSelectionModel;

    double kvalue,bvalue;
    int valueindex;

    QLabel *klabel;
    QLabel *blabel;

    QGridLayout *glayout;

    MainTab *mainTab;
    void getItemData(QSqlQuery &query,QString str, QStandardItemModel *model, int row, int column);
};

#endif // ONESENSOR_H
