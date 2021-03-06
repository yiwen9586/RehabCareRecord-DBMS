#include "stu_info.h"
#include "ui_stu_info.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

QSqlDatabase db_stu;

stu_info::stu_info(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stu_info)
{
    ui->setupUi(this);


    if(!createConnection())
      return;

    QSqlQuery query_commo(db_stu);
    query_commo.exec("SELECT 项目 FROM [项目$] ");
    while (query_commo.next())
    {
          ui->stu_5->addItem(query_commo.value(0).toString());
          ui->spr_2->addItem(query_commo.value(0).toString());
    }


     ui->age->setPlaceholderText("请输入数字");
     ui->stu_4->setPlaceholderText("请输入数字");
     ui->spr_4->setPlaceholderText("请输入数字");



}

stu_info::~stu_info()
{
    delete ui;
}

void stu_info::on_pushButton_clicked()
{
    QString sex;

    if(ui->sex_male->isChecked())
        sex="男";
    else if(ui->sex_female->isChecked())
        sex="女";

    QString categ;
    if(ui->categ_stu->isChecked())
        categ="学生+"+ui->stu_1->text()+"+"+ui->stu_3->text()+"+"+ui->stu_5->currentText()+"+"+ui->stu_4->text();//学生+院系+年级+专项+运动年限
    else if(ui->categ_tch->isChecked())
        categ="教师+"+ui->tch_1->text()+"+"+ui->tch_2->text();//教师+部门+教研室
    else if(ui->categ_spr->isChecked())
        categ="运动员+"+ui->spr_1->currentText()+"+"+ui->spr_2->currentText()+"+"+ui->spr_3->currentText()+"+"+ui->spr_4->text();//运动员+所属单位+专项+等级+运动年限
    else if(ui->categ_oth->isChecked())
        categ="其他+"+ui->oth_1->text()+ui->oth_2->text();//其他+职业+运动爱好


    QString sql;
    sql="INSERT INTO [个人信息$] VALUES ('"+ui->num->text()+"','"     //编号
                                          +ui->name->text()+"',"  //姓名
                                          +ui->age->text()+",'"  //年龄
                                          +sex                   +"','"  //性别
                                          +ui->birth_year->text()+"年"+ui->birth_month->currentText()+"月','"  //出生年月
                                          +ui->tall->text()+"','"  //身高
                                          +ui->weight->text()+"','"  //体重
                                          +ui->tel->text()+"','"  //联系电话
                                          +categ+"')" ; //类别

    QSqlQuery query(db_stu);
    if(query.exec(sql))
    {
         QMessageBox::about(NULL, "录入成功", "个人信息录入成功");
         ui->centralwidget->setEnabled(false);
    }

    else
         QMessageBox::critical(0,"录入失败",query.lastError().text()+"\n信息不完整请补全");
}

bool stu_info::createConnection()
{
    db_stu = QSqlDatabase::addDatabase("QODBC","excel");
    db_stu.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\基本信息.xlsx");
        if (!db_stu.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_stu.lastError().text());
            return false;
        }
        return true;
}

void stu_info::closeEvent (QCloseEvent *event  )
{
   QSqlDatabase::removeDatabase(db_stu.connectionName());
    event->accept();
}

