#ifndef REASON_SOLUTION_H
#define REASON_SOLUTION_H

#include <QMainWindow>
#include <QSqlQueryModel>

#pragma execution_character_set("utf-8")

namespace Ui {
class Reason_Solution;
}

class Reason_Solution : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reason_Solution(QWidget *parent = 0);
    ~Reason_Solution();
    bool createConnection();
    void closeEvent (QCloseEvent *event  );



private slots:
    void on_pushButton_clicked();

private:
    Ui::Reason_Solution *ui;

private:
    QSqlQueryModel *model;
};

#endif // REASON_SOLUTION_H
