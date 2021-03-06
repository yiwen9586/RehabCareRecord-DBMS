#include "ass_que.h"
#include "ui_ass_que.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_ass;

ass_que::ass_que(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ass_que)
{
    ui->setupUi(this);
    if(!createConnection())
      return;
}

ass_que::~ass_que()
{
    delete ui;
}



bool ass_que::createConnection()
{
    db_ass = QSqlDatabase::addDatabase("QODBC","excel");
    db_ass.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\疗效评估.xlsx");
        if (!db_ass.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_ass.lastError().text());
            return false;
        }
        return true;
}


void ass_que::closeEvent (  QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_ass.connectionName());
    event->accept();
}

void ass_que::on_pushButton_clicked()
{
    QSqlQuery query(db_ass);
    QString sql;
    sql = "SELECT * FROM [疗效评估$] WHERE 姓名='"+ui->lineEdit_name->text().trimmed()+"'"+"and 治疗部位='"+ui->lineEdit_part->text().trimmed()+"'";
    query.exec(sql);
    if(query.first())
    {
      ui->Number->setText(query.value(query.record().indexOf("编号")).toString());
      ui->Name->setText(query.value(query.record().indexOf("姓名")).toString());
      ui->zhengzhuang->setText(query.value(query.record().indexOf("症状")).toString());
      ui->zhenduan->setText(query.value(query.record().indexOf("伤病诊断")).toString());
      ui->buwei->setText(query.value(query.record().indexOf("治疗部位")).toString());
      ui->cishu->setText(query.value(query.record().indexOf("项目及次数")).toString());
      ui->date1->setText(query.value(query.record().indexOf("日期1")).toString());
      ui->zhongzhang1->setText(query.value(query.record().indexOf("肿胀1")).toString());
      ui->guanjie1->setText(query.value(query.record().indexOf("关节活动度1")).toString());
      ui->jili1->setText(query.value(query.record().indexOf("肌力1")).toString());
      ui->pain1->setText(query.value(query.record().indexOf("疼痛程度1")).toString());
      ui->other1->setText(query.value(query.record().indexOf("其他异常1")).toString());
      ui->beizhu1->setText(query.value(query.record().indexOf("备注1")).toString());
      ui->date1_2->setText(query.value(query.record().indexOf("日期2")).toString());
      ui->zhongzhang1_2->setText(query.value(query.record().indexOf("肿胀2")).toString());
      ui->guanjie1_2->setText(query.value(query.record().indexOf("关节活动度2")).toString());
      ui->jili1_2->setText(query.value(query.record().indexOf("肌力2")).toString());
      ui->pain1_2->setText(query.value(query.record().indexOf("疼痛程度2")).toString());
      ui->other1_2->setText(query.value(query.record().indexOf("其他异常2")).toString());
      ui->beizhu1_2->setText(query.value(query.record().indexOf("备注2")).toString());
      ui->liaoxiao->setText(query.value(query.record().indexOf("疗效")).toString());

    }
    else
      QMessageBox::critical(0,"","未找到该用户信息");
}
