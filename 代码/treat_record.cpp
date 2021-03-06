#include "treat_record.h"
#include "ui_treat_record.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_treat;


Treat_Record::Treat_Record(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Treat_Record)
{
    ui->setupUi(this);

    if(!createConnection())
      return;

    QSqlQuery query_commo1(db_treat);
    query_commo1.exec("SELECT 部位 FROM [设置$] ");
    while (query_commo1.next())
    {
          ui->part->addItem(query_commo1.value(0).toString());
    }


    QSqlQuery query_commo2(db_treat);
    query_commo2.exec("SELECT 治疗项目 FROM [设置$] ");
    while (query_commo2.next())
    {
          ui->treatitem->addItem(query_commo2.value(0).toString());
    }

    QSqlQuery query_commo3(db_treat);
    query_commo3.exec("SELECT 项目 FROM [项目$] ");
    while (query_commo3.next())
    {
          ui->item->addItem(query_commo3.value(0).toString());
    }
}

Treat_Record::~Treat_Record()
{
    delete ui;
}

bool Treat_Record::createConnection()
{
    db_treat = QSqlDatabase::addDatabase("QODBC","excel");
    db_treat.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\治疗记录.xlsx");
        if (!db_treat.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_treat.lastError().text());
            return false;
        }
        return true;
}

void Treat_Record::closeEvent (QCloseEvent *event  )
{
   QSqlDatabase::removeDatabase(db_treat.connectionName());
    event->accept();
}

void Treat_Record::on_pushButton_clicked()
{
    QString sql;
    QString number;
    if(ui->number->text().isEmpty())
        number="空";
    else
        number=ui->number->text();

    qDebug()<<number;
    sql="INSERT INTO [治疗记录$] VALUES ('"+number+"','"     //编号
                                          +ui->name->text()+"','"  //姓名
                                          +ui->cate->currentText()+"','"  //类型
                                          +ui->item->currentText()+"','"  //项目
                                          +ui->diagnose->toPlainText()+"','"  //诊断
                                          +ui->part->currentText()+"','"  //部位
                                          +ui->treatitem->currentText()+"','"  //治疗项目
                                          +ui->date->text()+ "')";   //日期

    QSqlQuery query(db_treat);

    if(query.exec(sql))
        {
         QMessageBox::about(NULL, "录入成功", "治疗记录录入成功");
         ui->centralwidget->setEnabled(false);
         }
    else
         QMessageBox::critical(0,"录入失败",query.lastError().text()+"\n信息不完整请补全");
}
