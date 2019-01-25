#include "reason_solution.h"
#include "ui_reason_solution.h"
#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>
#include <QtGui>


QSqlDatabase db_rs;

Reason_Solution::Reason_Solution(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reason_Solution)
{

    ui->setupUi(this);

    if(!createConnection())
      return;

    QSqlQuery query_commo1(db_rs);
    query_commo1.exec("SELECT 部位 FROM [设置$] ");
    while (query_commo1.next())
    {
          ui->comboBox->addItem(query_commo1.value(0).toString());
    }


    QSqlQuery query_commo2(db_rs);
    query_commo2.exec("SELECT 治疗项目 FROM [设置$] ");
    while (query_commo2.next())
    {
          ui->comboBox_2->addItem(query_commo2.value(0).toString());
    }
}

Reason_Solution::~Reason_Solution()
{
    delete ui;
}



void Reason_Solution::on_pushButton_clicked()
{

    QString sql;
 /*   QStringList tables;
    tables<< "艺体" << "校男篮" << "摔跤" << "蹦床" << "足球" << "滑雪" << "大运会男篮" << "大运会女篮" << "国家冰壶" << "田径" << "网球";

    for(int i =0;i<tables.size();i++)
    {
        sql=sql+"select * from [" +tables.at(i)+"$] where (病因='"+ ui->comboBox->currentText() +"') and (治疗方案='"+ ui->comboBox_2->currentText() + "') " + " union all ";
    }
        sql = sql.left(sql.length()- 11);
*/
    sql= "select * from [治疗记录$] where (部位='"+ ui->comboBox->currentText() +"') and (治疗项目='"+ ui->comboBox_2->currentText() + "') ";
    model =new QSqlQueryModel(this);
    model->setQuery(sql ,db_rs);


    //view = new QTableView;
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setStretchLastSection(true);
    ui->view->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;border: 0.3px solid #6c6c6c;}");
    ui->view->show();
}

bool Reason_Solution::createConnection()
{
    db_rs = QSqlDatabase::addDatabase("QODBC","excel");
    db_rs.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};READONLY=FALSE;DBQ=D:\\\\康复大厅\\\\治疗记录.xlsx");

        if (!db_rs.open())
        {
            qDebug()<<"connect data error";
            QMessageBox::critical(0,QObject::tr("Database Error"),db_rs.lastError().text());
            return false;
        }
        return true;
}


void Reason_Solution::closeEvent (QCloseEvent *event )
{
     QSqlDatabase::removeDatabase(db_rs.connectionName());
      event->accept();
}
