#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile file("D:/康复大厅/image/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
   // a.setStyleSheet(styleSheet);
   // w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);
    w.setWindowTitle("康复大厅数据管理系统");
    w.show();

    return a.exec();
}
