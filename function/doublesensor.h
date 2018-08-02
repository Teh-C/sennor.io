#ifndef DOUBLESENSOR_H
#define DOUBLESENSOR_H

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
#include <QCheckBox>
#include "./function/maintab.h"
namespace Ui {
class DoubleSensor;
}

class DoubleSensor : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleSensor(QWidget *parent = 0);
    ~DoubleSensor();

    void setMainTab(MainTab *mainTab);
private:
    Ui::DoubleSensor *ui;


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
    void dealxCheckBoxStatus(int state);
    void dealyCheckBoxStatus(int state);



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
    QCheckBox *xCheckBox;
    QCheckBox *yCheckBox;

    QHBoxLayout *btnLayout;
    QHBoxLayout *checkBoxLayout;

    void getItemData(QSqlQuery &query,QString str, QStandardItemModel *model, int row, int column);
};

#endif // DOUBLESENSOR_H
