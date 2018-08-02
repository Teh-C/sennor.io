#include "onesensor.h"
#include "ui_onesensor.h"
#include <QPushButton>
#include <QStringList>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>
#include <QModelIndex>
#include <QString>
#include <QDateTime>
#include <QFile>

#include <QSettings>


QByteArray xvalue;

OneSensor::OneSensor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneSensor),
    tableview(new QTableView()),
    model(new QStandardItemModel(this)),
    klineedit(new QLineEdit),
    blineedit(new QLineEdit),
    getvaluebutton(new QPushButton("获取角度值")),
    countbutton(new QPushButton("计算(KB)")),
    setkbbutton(new QPushButton("设置")),
    resetbutton(new QPushButton("重置")),
    removeButton(new QPushButton("删除")),
    setFilePathBtn(new QPushButton("设置路径")),
    saveFileBtn(new QPushButton("保存")),
    filePathLabel(new QLabel(filePathStr)),
    deviceNumLabel(new QLabel(tr("传感器编号:"))),
    deviceNumEdit(new QLineEdit),
    countDiffValueBtn(new QPushButton(tr("计算(差值)"))),
    kvalue(0.0),
    bvalue(0.0),
    valueindex(0),
    klabel(new QLabel("kvalue:")),
    blabel(new QLabel("bvalue:")),
    glayout(new QGridLayout(this))
{
    ui->setupUi(this);
    this->resize(QSize(650, 480));
    filePathLabel->setWordWrap(true);

    QStringList strlist;
    strlist<<"校准前实际值" << "校准前测量值" << "校准前差值" << "校准后实际值" << "校准后测量值" << "校准后差值";
    model->setHorizontalHeaderLabels(strlist);
    itemSelectionModel =  new QItemSelectionModel(model);
    tableview->setModel(model);
    tableview->setSelectionModel(itemSelectionModel);
    glayout->addWidget(tableview,0,0,4,5);

    // QPushButton
    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnLayout->addWidget(getvaluebutton);
    btnLayout->addWidget(removeButton);
    btnLayout->addWidget(countbutton);
    btnLayout->addWidget(countDiffValueBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(resetbutton);
    btnLayout->addWidget(setkbbutton);

    glayout->addLayout(btnLayout,4,0,1,5);

    QHBoxLayout *kLayout = new QHBoxLayout;
    QHBoxLayout *bLayout = new QHBoxLayout;
    kLayout->addWidget(klabel);
    kLayout->addWidget(klineedit);
    bLayout->addWidget(blabel);
    bLayout->addWidget(blineedit);
    glayout->addLayout(kLayout,5,0,1,5);
    glayout->addLayout(bLayout,6,0,1,5);


    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(deviceNumLabel);
    btnLayout->addWidget(deviceNumEdit);
    btnLayout->addStretch();
    btnLayout->addWidget(setFilePathBtn);
    btnLayout->addWidget(saveFileBtn);

    glayout->addLayout(btnLayout,7,0,1,5);
    glayout->addWidget(filePathLabel, 8, 0, 1, 5);


    glayout->setColumnStretch(0, 0);
    QObject::connect(getvaluebutton,SIGNAL(clicked()),this,SLOT(GetAngleValue()));
    QObject::connect(countbutton,SIGNAL(clicked()),this,SLOT(CountKbValue()));
    QObject::connect(setkbbutton,SIGNAL(clicked()),this,SLOT(SetKbValue()));
    QObject::connect(resetbutton,SIGNAL(clicked()),this,SLOT(ResetKbValue()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(deleteLastAngleValue()));
    connect(setFilePathBtn, SIGNAL(clicked()),this, SLOT(setFilePath()));
    connect(saveFileBtn, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(countDiffValueBtn, SIGNAL(clicked()), this, SLOT(countDiffValue()));
    this->setLayout(glayout);

    QSettings setting("./Setting.ini", QSettings::IniFormat);
    filePathStr = setting.value("LastFilePath").toString();
    filePathLabel->setText(filePathStr);
}

OneSensor::~OneSensor()
{
    delete ui;
}


void OneSensor::deleteLastAngleValue()
{
    QModelIndexList modelIndexList = itemSelectionModel->selectedIndexes();

    if(modelIndexList.count() == 1)
    {
        model->setItem(modelIndexList.at(0).row(), modelIndexList.at(0).column(), new QStandardItem(""));
    }
    else
    {

        QModelIndex index;
        QSet<int> set;                 // QSet<T>类似于C++中的HashSet<T>


        foreach (index, modelIndexList) {
            set << index.row();        // 获取选择的行号，除去重复行号
        }
        QList<int> list = set.toList();// QSet转QList，主要方便使用qSort()方法
        qSort(list.begin(), list.end(), qGreater<int>());
        foreach(int selectRow, list)
        {
            model->removeRows(selectRow, 1);          // 删除指定的行
            valueindex--;
        }
    }
}


/*****************************************************************************
 * 接口：GetAngleValue
 * 描述：获取X/Y轴的角度值，并写入表格中
 *****************************************************************************/
void OneSensor::GetAngleValue()
{
    QModelIndexList modelIndexList = itemSelectionModel->selectedIndexes();         // 获取选中区域
    if(modelIndexList.count() == 0)                                                 // 没有选中区域，则新建一行
    {
        model->setItem(valueindex,1,new QStandardItem(mainTab->getSennorAngle_Y()));
        valueindex++;
    }
    else if(modelIndexList.count() == 1)                                            // 选中了某个单元格，给这个单元格填值
    {
        model->setItem(modelIndexList.at(0).row(),modelIndexList.at(0).column(),new QStandardItem(mainTab->getSennorAngle_Y()));
        itemSelectionModel->clearSelection();                                       // 清除选择区域
    }
    else                                                                            // 选中了多个单元格，清除单元格
    {
        itemSelectionModel->clearSelection();                                       // 清除选择区域
    }
}

int OneSensor::CountKbValue()
{
    double dbSumXX,dbSumYY,dbSumXY,dbSumX,dbSumY,dbA,dbB,dbValueX,dbValueY;
    dbSumXX=dbSumYY=dbSumXY=dbSumX=dbSumY=dbValueX=dbValueY=0.0;
    int rows=tableview->model()->rowCount();                    // 获取行数
    if(rows == 0)                                               // 表格至少有1行才能进行一下步骤
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("请先获取角度值！"),
                             QMessageBox::Ok);
        return VALUE_NULL_ERROR;
    }
    for(int i=0;i<rows;i++)
    {
        // 判断表格某单元是否为空。如果为空又进行了计算步骤，会导致软件崩溃。
        for(int j = 0; j < 2; j++)
        {
            if(!model->data(model->indexFromItem(model->item(i, j))).isValid())
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString("(%1,%2)值不能为空！").arg(i+1).arg(j+1),
                                     QMessageBox::Ok);
                return VALUE_NULL_ERROR;
            }
            if(model->item(i, j)->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString("(%1,%2)值不能为空！").arg(i+1).arg(j+1),
                                     QMessageBox::Ok);
                return VALUE_NULL_ERROR;
            }
        }
        dbValueX=model->item(i,1)->text().toDouble();
        dbValueY=model->item(i,0)->text().toDouble()-(model->item(i,1)->text().toDouble());
        dbSumX+=dbValueX;
        dbSumY+=dbValueY;
        dbSumXX+=dbValueX*dbValueX;
        dbSumYY+=dbValueY*dbValueY;
        dbSumXY+=dbValueX*dbValueY;
    }
    //曲线系数
    dbB=(dbSumXX*dbSumY-dbSumXY*dbSumX)/(dbSumXX*rows-dbSumX*dbSumX);
    dbA=(dbSumXY*rows-dbSumX*dbSumY)/(dbSumXX*rows-dbSumX*dbSumX);
    kvalue=dbA;
    bvalue=dbB;

    for(int j=0;j<rows;j++)
    {
       dbValueX=model->item(j,1)->text().toDouble();     //测量角度值
       dbValueY=model->item(j,0)->text().toDouble();     //实际角度值
//       dbSumXX=dbValueX+dbValueX*kvalue+bvalue;          //校准角度值
       dbSumXY=dbValueY-dbValueX;

       model->setItem(j,2,new QStandardItem(QString("%1").arg(dbSumXY,0,'f',6))); // 校准前的差值
//       model->setItem(j,3,new QStandardItem(QString("%1").arg(dbSumXY,0,'f',6))); // 校准后的角度值与实际角度值的差值
    }
    klineedit->setText(QString::number(kvalue,'f',8));
    blineedit->setText(QString::number(bvalue,'f',8));
    return NO_ERROR;
}

void OneSensor::countDiffValue()
{
    double diffValue, lastActValue, lastMesValue;
    int model_row = model->rowCount();
    for(int i = 0; i < model_row; i++)
    {
        if(!model->data(model->indexFromItem(model->item(i, 3))).isValid())
        {
            continue;
        }
        if(!model->data(model->indexFromItem(model->item(i, 4))).isValid())
        {
            continue;
        }
        if(model->item(i,3)->text().isEmpty())
        {
            continue;
        }
        if(model->item(i,4)->text().isEmpty())
        {
            continue;
        }
        lastActValue=model->item(i,3)->text().toDouble();     //校准后的实际值
        lastMesValue=model->item(i,4)->text().toDouble();     //校准后的测量值
        diffValue = lastActValue - lastMesValue;
        model->setItem(i,5,new QStandardItem(QString("%1").arg(diffValue,0,'f',6))); // 校准前的差值
    }

}



void OneSensor::SetKbValue()
{
    QString str="$TDGKB25,";
    QString kStr=klineedit->text();
    QString bStr=blineedit->text();
    if(kvalue > -10 && kvalue < 10 && bvalue > -10 && bvalue < 10)
    {
        if(kvalue > 0)
            str.append("+");
            str.append(kStr);
            str.append(",");
        if(bvalue > 0)
            str.append("+");
            str.append(bStr);
            str.append("\r\n");

        if(mainTab->sendStringToSennor(str) == true)
            QMessageBox::information(this, "设置", "设置成功！", QMessageBox::Ok);
        else
            QMessageBox::warning(this, tr("提示"), tr("串口可能未打开，请检查串口再进行校准。"), QMessageBox::Ok);
     }
    else
    {
        QMessageBox::warning(this, tr("Warning"),
                             QString("KB值有误，请重新获取并计算！"),
                             QMessageBox::Ok);
    }
}

void OneSensor::ResetKbValue()
{
    QString str="$TDINT\r\n";
    if(mainTab->sendStringToSennor(str) == false)
        QMessageBox::warning(this, tr("提示"), tr("串口可能未打开，请检查串口再进行校准。"), QMessageBox::Ok);
}



void OneSensor::setFilePath()
{
    filePathStr  = QFileDialog::getExistingDirectory(this, "设置保存路径");
    filePathLabel->setText(filePathStr);
    QSettings setting("./Setting.ini", QSettings::IniFormat);
    setting.setValue("LastFilePath", filePathStr);

}


void OneSensor::getItemData(QSqlQuery &query,QString str, QStandardItemModel *model, int row, int column)
{
    if(model->data(model->indexFromItem(model->item(row, column))).isValid())
        query.bindValue(str, model->item(row,column)->text().toDouble());
}

void OneSensor::saveFile()
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    if(filePathStr.isEmpty() || deviceNumEdit->text().isEmpty())
       QMessageBox::warning(this, tr("警告"), "保存前，请先设置保存路径和编号！", QMessageBox::Ok);
    else
    {
//        QString filename = QFileDialog::getSaveFileName(this,
//                                                        tr("Save Excel"),
//                                                          "MacAddr",
//                                                        tr("*.xls;; *.xlsx")); //选择路径

        QString fileName = timeStr + "_" + deviceNumEdit->text()+".txt";
        QString filePathName = filePathStr + "/" + timeStr + "_" + deviceNumEdit->text();

        if(filePathName.isEmpty()){
            return;
        }else{

            QString sheetName = "Sheet1";

            QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
            if( !db.isValid())
                return;   //! type error

            QString dsn = "DRIVER={Microsoft Excel Driver (*.xls)};"
                    "DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=";
            dsn += ("\"" + filePathName + ".xls\"" + ";DBQ=" + filePathName + ".xls");
            db.setDatabaseName( dsn);

            // open connection
            if( !db.open())
                return;  //! db error

            QSqlQuery query(db);
            QString sSql;
            bool state;

            // drop the table if it's already exists
            // 如果表1存在的话，就删除
            sSql = QString("DROP TABLE [%1]").arg(sheetName);
            query.exec( sSql);


            //create the table (sheet in Excel file)
            sSql = QString("CREATE TABLE [%1] (").arg(sheetName);
            sSql += "编号 int, 校准前实际值 float, 校准前测量值 float, 校准前差值 float, 校准后实际值 float, 校准后测量值 float, 校准后差值 float";
            sSql += ")";
            state = query.prepare( sSql);
            if( !query.exec()) {
                QMessageBox::warning(this, "ODBC", "ODBC操作出错！", QMessageBox::Ok);
                goto CLOSE; //! create failed
            }

            for (int i = 0; i < model->rowCount(); i ++){
                sSql = QString("INSERT INTO [%1] ").arg( sheetName);
                sSql += "(编号, 校准前实际值, 校准前测量值, 校准前差值, 校准后实际值, 校准后测量值, 校准后差值) ";
                sSql += "VALUES(:num,:preActVal,:preMesVal,:preDiffVal,:lastActVal,:lastMesVal,:lastDiffVal)";
                state = query.prepare( sSql);
                query.bindValue(":num", i+1);
                getItemData(query,":preActVal", model, i, 0);
                getItemData(query,":preMesVal", model, i, 1);
                getItemData(query,":preDiffVal", model, i, 2);
                getItemData(query,":lastActVal", model, i, 3);
                getItemData(query,":lastMesVal", model, i, 4);
                getItemData(query,":lastDiffVal", model, i, 5);
                if( !query.exec()) {
                    QMessageBox::warning(this, "ODBC", "ODBC操作出错！", QMessageBox::Ok);
                    goto CLOSE; //! insert failed
                }
            }
    //close connection
     CLOSE:
                 db.close();

        }
        QString messageStr = "文件:"+fileName+".xls"+"保存成功！";
        QMessageBox::information(this, tr("提示"), messageStr, QMessageBox::Ok);
    }
}


void OneSensor::setMainTab(MainTab *mainTab)
{

    this->mainTab = mainTab;
}






