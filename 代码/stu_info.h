#ifndef STU_INFO_H
#define STU_INFO_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")

namespace Ui {
class stu_info;
}

class stu_info : public QMainWindow
{
    Q_OBJECT

public:
    explicit stu_info(QWidget *parent = 0);
    ~stu_info();
    bool createConnection();
    void closeEvent (QCloseEvent *event  );


private slots:
    void on_pushButton_clicked();

private:
    Ui::stu_info *ui;
};

#endif // STU_INFO_H
