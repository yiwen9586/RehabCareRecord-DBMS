#include "ass_2.h"
#include "ui_ass_2.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_ass_2;


ass_2::ass_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ass_2)
{
    ui->setupUi(this);
    ui->groupBox_3->setEnabled(false);
    ui->save_btn->setEnabled(false);
    if(!createConnection())
      return;
}

bool ass_2::createConnection()
{
    db_ass_2 = QSqlDatabase::addDatabase("QODBC","excel");
    db_ass_2.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\疗效评估.xlsx");
        if (!db_ass_2.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_ass_2.lastError().text());
            return false;
        }
        return true;
}


ass_2::~ass_2()
{
    delete ui;
}

void ass_2::on_pushButton_clicked()
{
    QSqlQuery query(db_ass_2);
    QString sql;
    sql = "SELECT * FROM [疗效评估$] WHERE 姓名='"+ui->lineEdit_name->text().trimmed()+"'"+"and 治疗部位='"+ui->lineEdit_part->text().trimmed()+"'";
    query.exec(sql);
    if(query.first())
    {
        if(query.value(query.record().indexOf("日期2")).toString()=="0")
        {
            ui->Number_2->setText(query.value(query.record().indexOf("编号")).toString());
            ui->Name_2->setText(query.value(query.record().indexOf("姓名")).toString());
            ui->zhengzhuang_2->setText(query.value(query.record().indexOf("症状")).toString());
            ui->zhenduan_2->setText(query.value(query.record().indexOf("伤病诊断")).toString());
            ui->buwei_2->setText(query.value(query.record().indexOf("治疗部位")).toString());
            ui->cishu_2->setText(query.value(query.record().indexOf("项目及次数")).toString());
            ui->date1_3->setText(query.value(query.record().indexOf("日期1")).toString());
            ui->zhongzhang1_3->setText(query.value(query.record().indexOf("肿胀1")).toString());
            ui->guanjie1_3->setText(query.value(query.record().indexOf("关节活动度1")).toString());
            ui->jili1_3->setText(query.value(query.record().indexOf("肌力1")).toString());
            ui->pain1_3->setText(query.value(query.record().indexOf("疼痛程度1")).toString());
            ui->other1_3->setText(query.value(query.record().indexOf("其他异常1")).toString());
            ui->beizhu1_3->setText(query.value(query.record().indexOf("备注1")).toString());

            ui->groupBox_3->setEnabled(true);
            ui->save_btn->setEnabled(true);
         }

        else
            QMessageBox::critical(0,"","该条记录已存在再次评估信息，请退出查询");

    }
    else
      QMessageBox::critical(0,"","未找到该用户信息");
}


void ass_2::closeEvent (  QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_ass_2.connectionName());
    event->accept();
}

void ass_2::on_save_btn_clicked()
{
    QSqlQuery query(db_ass_2);
    QString sql;
    sql = "UPDATE [疗效评估$] SET 日期2='"+ui->date2->text()
                             +"',肿胀2='"+ui->zhongzhang2->text()
                             +"',关节活动度2='"+ui->guanjie2->text()
                             +"',肌力2='"+ui->jili2->text()
                             +"',疼痛程度2='"+ui->pain2->text()
                             +"',其他异常2='"+ui->other2->text()
                             +"',备注2='"+ui->beizhu2->text()
                             +"',疗效='"+ui->liaoxiao2->text()
                             +"' WHERE 姓名='"+ui->lineEdit_name->text().trimmed()+"'"+"and 治疗部位='"+ui->lineEdit_part->text().trimmed()+"'";
    if(query.exec(sql))
    {
         QMessageBox::about(NULL, "更新成功", "再次评估信息录入成功");
         ui->centralwidget->setEnabled(false);
    }

    else
         QMessageBox::critical(0,"更新失败",query.lastError().text()+"\n信息不完整请补全");
}
