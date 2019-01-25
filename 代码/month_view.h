#ifndef MONTH_VIEW_H
#define MONTH_VIEW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#pragma execution_character_set("utf-8")

namespace Ui {
class month_view;
}

class month_view : public QMainWindow
{
    Q_OBJECT

public:
    explicit month_view(QWidget *parent = 0);
    ~month_view();
      void closeEvent (QCloseEvent *event  );
     bool createConnection();

private slots:
     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

private:
    Ui::month_view *ui;
    QSqlQueryModel *model;
};

#endif // MONTH_VIEW_H
