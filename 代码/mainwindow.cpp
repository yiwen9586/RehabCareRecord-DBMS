#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reason_solution.h"
#include "stu_info.h"
#include "info_que.h"
#include "date_que.h"
#include "month_view.h"
#include "treat_record.h"
#include "ass_que.h"
#include "ass_1.h"
#include "ass_2.h"
#include <QMessageBox>
#include <QtGui>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      QImage *img=new QImage;
      img->load("D:/康复大厅/image/logo1.jpg");
    //  img->scaled(191,141,Qt::KeepAspectRatio);
      ui->logo->setPixmap(QPixmap::fromImage(*img));
      QImage *img2=new QImage;
      img2->load("D:/康复大厅/image/logo2.jpg");
      ui->logo_2->setPixmap(QPixmap::fromImage(*img2));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    Reason_Solution *m = new Reason_Solution;
    m->setWindowTitle("部位及治疗项目查询");
    m->show();

}

void MainWindow::on_pushButton_clicked()
{
    stu_info *m = new stu_info;
    m->setWindowTitle("个人信息录入");
    m->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    info_que *m = new info_que;
    m->setWindowTitle("个人信息查询");
    m->show();

}

void MainWindow::on_pushButton_4_clicked()
{
    date_que *m = new date_que;
    m->setWindowTitle("根据日期查询");
    m->show();
}



void MainWindow::on_pushButton_6_clicked()
{
    Treat_Record *m = new Treat_Record;
    m->setWindowTitle("治疗记录录入");
    m->show();
}

void MainWindow::on_pushButton_10_clicked()
{
    ass_que *m = new ass_que;
    m->setWindowTitle("疗效评估查询");
    m->show();
}


void MainWindow::closeEvent (QCloseEvent *event )
{

    QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("退出程序"),
            QString(tr("警告：是否结束操作退出康复大厅?")),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            event->ignore();  //忽略退出信号，程序继续运行
        }
        else if (button == QMessageBox::Yes) {
            event->accept();  //接受退出信号，程序退出

        }
}






void MainWindow::on_pushButton_8_clicked()
{
    ass_2 *m = new ass_2;
    m->setWindowTitle("疗效评估再次录入");
    m->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    ass_1 *m = new ass_1;
    m->setWindowTitle("疗效评估初次录入");
    m->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    month_view *m = new month_view;
    m->setWindowTitle("月度总结");
    m->show();
}
