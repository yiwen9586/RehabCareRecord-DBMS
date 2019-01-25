#include "ass_1.h"
#include "ui_ass_1.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_ass_1;

ass_1::ass_1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ass_1)
{
    ui->setupUi(this);
    if(!createConnection())
      return;
}

bool ass_1::createConnection()
{
    db_ass_1 = QSqlDatabase::addDatabase("QODBC","excel");
    db_ass_1.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\疗效评估.xlsx");
        if (!db_ass_1.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_ass_1.lastError().text());
            return false;
        }
        return true;
}

ass_1::~ass_1()
{
    delete ui;
}

void ass_1::closeEvent (  QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_ass_1.connectionName());
    event->accept();
}

void ass_1::on_pushButton_clicked()
{
    QString sql;
    QString number;
    if(ui->Number->text().isEmpty())
        number="空";
    else
        number=ui->Number->text();
    sql="INSERT INTO [疗效评估$] VALUES ('"+number+"','"     //编号
                                          +ui->Name->text()+"','"  //姓名
                                          +ui->Zheng->text()+"','"  //症状
                                          +ui->Zhenduan->text()+"','" //伤病诊断
                                          +ui->Buwei->text()+"','" //治疗部位
                                          +ui->Xiangmu->text()+"',"  //项目及次数
                                          +ui->date1->text()+",'"  //日期1
                                          +ui->zhongzhang1->text()+"','"  //肿胀1
                                          +ui->guanjie1->text()+"','" //关节活动度1
                                          +ui->jili1->text()+"','"  //肌力1
                                          +ui->pain1->text()+"','"  //疼痛程度1
                                          +ui->other1->text()+"','"  //其他异常1
                                          +ui->beizhu1->text()+ "',0,0,0,0,0,0,0,0)";  //备注1


    QSqlQuery query(db_ass_1);
    if(query.exec(sql))
    {
         QMessageBox::about(NULL, "录入成功", "初次评估录入成功");
         ui->centralwidget->setEnabled(false);
    }

    else
         QMessageBox::critical(0,"录入失败",query.lastError().text()+"\n信息不完整请补全");
}
