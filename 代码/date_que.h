#ifndef DATE_QUE_H
#define DATE_QUE_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")


namespace Ui {
class date_que;
}

class date_que : public QMainWindow
{
    Q_OBJECT

public:
    explicit date_que(QWidget *parent = 0);
    ~date_que();
    bool createConnection();
     void closeEvent (QCloseEvent *event  );


private slots:
    void on_pushButton_clicked();

private:
    Ui::date_que *ui;

};

#endif // DATE_QUE_H
