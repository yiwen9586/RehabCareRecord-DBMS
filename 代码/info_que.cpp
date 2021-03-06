#include "info_que.h"
#include "ui_info_que.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_que;

info_que::info_que(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::info_que)
{
    ui->setupUi(this);

    if(!createConnection())
      return;
}

info_que::~info_que()
{
    delete ui;

}

bool info_que::createConnection()
{
    db_que = QSqlDatabase::addDatabase("QODBC","excel");
    db_que.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\基本信息.xlsx");
        if (!db_que.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_que.lastError().text());
            return false;
        }
        return true;
}

void info_que::on_pushButton_clicked()
{
    QSqlQuery query(db_que);
    QString sql;
    sql = "SELECT * FROM [个人信息$] WHERE 姓名='"+ui->lineEdit->text().trimmed()+"'";
    query.exec(sql);
    if(query.first())
    {
      ui->Number->setText(query.value(query.record().indexOf("编号")).toString());
      ui->Name->setText(query.value(query.record().indexOf("姓名")).toString());
      ui->Age->setText(query.value(query.record().indexOf("年龄")).toString());
      ui->Sex->setText(query.value(query.record().indexOf("性别")).toString());
      ui->Tall->setText(query.value(query.record().indexOf("身高")).toString());
      ui->Weight->setText(query.value(query.record().indexOf("体重")).toString());
      ui->BirthDate->setText(query.value(query.record().indexOf("出生年月")).toString());
      ui->Tel->setText(query.value(query.record().indexOf("联系电话")).toString());
      ui->Category->setText(query.value(query.record().indexOf("类别")).toString());

    }
    else
      QMessageBox::critical(0,"","未找到该用户信息");
}

void info_que::closeEvent (QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_que.connectionName());
     event->accept();
}
