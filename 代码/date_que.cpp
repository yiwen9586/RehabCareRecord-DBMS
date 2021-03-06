#include "date_que.h"
#include "ui_date_que.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtGui>

QSqlDatabase db_date;

date_que::date_que(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::date_que)
{
    ui->setupUi(this);

    if(!createConnection())
      return;
}

date_que::~date_que()
{
    delete ui;
}

bool date_que::createConnection()
{

    db_date = QSqlDatabase::addDatabase("QODBC","excel");
    db_date.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\治疗记录.xlsx");
        if (!db_date.open())
        {
            qDebug()<<"connect error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_date.lastError().text());
            return false;
        }
        return true;
}

void date_que::closeEvent (  QCloseEvent *event  )
{
    QSqlDatabase::removeDatabase(db_date.connectionName());
    event->accept();
}


void date_que::on_pushButton_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();

    model->setColumnCount(8);

    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"类型");
    model->setHeaderData(3,Qt::Horizontal,"项目");
    model->setHeaderData(4,Qt::Horizontal,"诊断");
    model->setHeaderData(5,Qt::Horizontal,"部位");
    model->setHeaderData(6,Qt::Horizontal,"治疗项目");
    model->setHeaderData(7,Qt::Horizontal,"日期");


    QSqlQuery query(db_date);
    QString sql;
  /*  QStringList tables;
    tables<< "艺体" << "校男篮" << "摔跤" << "蹦床" << "足球" << "滑雪" << "大运会男篮" << "大运会女篮" << "国家冰壶" << "田径" << "网球";

    for(int i =0;i<tables.size();i++)
    {
        sql=sql+"select * from [" +tables.at(i)+"$] union all ";
    }
        sql = sql.left(sql.length()- 11);
*/
    sql="select * from [治疗记录$]";
   query.exec(sql);


   int i = 0;
   while(query.next())
   {

       QStringList dateList=query.value(query.record().indexOf("日期")).toString().split(",");
       if(dateList.contains(ui->comboBox->currentText()))
       {
           model->setItem(i,0,new QStandardItem(query.value(query.record().indexOf("编号")).toString()));
           model->setItem(i,1,new QStandardItem(query.value(query.record().indexOf("姓名")).toString()));
           model->setItem(i,2,new QStandardItem(query.value(query.record().indexOf("类型")).toString()));
           model->setItem(i,3,new QStandardItem(query.value(query.record().indexOf("项目")).toString()));
           model->setItem(i,4,new QStandardItem(query.value(query.record().indexOf("诊断")).toString()));
           model->setItem(i,5,new QStandardItem(query.value(query.record().indexOf("部位")).toString()));
           model->setItem(i,6,new QStandardItem(query.value(query.record().indexOf("治疗项目")).toString()));
           model->setItem(i,7,new QStandardItem(ui->comboBox->currentText()));

           i++;
       }

   }


    //view = new QTableView;
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;border: 0.3px solid #6c6c6c;}");
    ui->tableView->show();
}
