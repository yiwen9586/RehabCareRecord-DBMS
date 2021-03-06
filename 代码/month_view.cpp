#include "month_view.h"
#include "ui_month_view.h"
#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>
#include <QtGui>


QSqlDatabase db_month;

month_view::month_view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::month_view)
{
    ui->setupUi(this);

    if(!createConnection())
      return;


}

month_view::~month_view()
{
    delete ui;
}

bool month_view::createConnection()
{
    db_month = QSqlDatabase::addDatabase("QODBC","excel");
    db_month.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:/康复大厅/治疗记录.xlsx");
        if (!db_month.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_month.lastError().text());
            return false;
        }
        return true;
}


void month_view::closeEvent (QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_month.connectionName());
     event->accept();
}

void month_view::on_pushButton_clicked()
{
    QSqlQuery query(db_month);
    QString sql;
    QStringList tables,solutions;

    QSqlQuery query_1(db_month);
    query_1.exec("SELECT 项目 FROM [项目$] ");
    while (query_1.next())
    {
          tables.append(query_1.value(0).toString());
    }


    QSqlQuery query_2(db_month);
    query_2.exec("SELECT 治疗项目 FROM [设置$] ");
    while (query_2.next())
    {
          solutions.append(query_2.value(0).toString());
    }

    int m = tables.size();


    for (int i =0;i<m;i++)//对于一种项目
    {
        int sum_count=0;
        int count[30]={0};

      for (int j=0;j<30;j++)//对于一种治疗方案
      {
          query.exec("select 日期 from [治疗记录$] where 项目='"+tables.at(i)+"' and 治疗项目='"+solutions.at(j)+"'");
         while(query.next())
         {
            QStringList dateList=query.value(0).toString().split(",");
            count[j]+=dateList.size();
         }
         sum_count+=count[j];

      }

      sql="INSERT INTO [总结$] VALUES('"+tables.at(i)+"',";

      for (int k=0;k<30;k++)
      {
          sql+=QString::number(count[k])+",";
      }

      sql=sql+QString::number(sum_count)+")";

      qDebug()<<sql;
      query.exec(sql);

    }
     QMessageBox::about(NULL, "生成成功", "月度总结成功！请关闭此页面后到“治疗记录.xlsx”中的“总结”sheet中查看！");



}

void month_view::on_pushButton_2_clicked()
{
    model =new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM [总结$]" ,db_month);


    //view = new QTableView;
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;border: 0.3px solid #6c6c6c;}");
    ui->tableView->show();

}
