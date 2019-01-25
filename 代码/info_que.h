#ifndef INFO_QUE_H
#define INFO_QUE_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")


namespace Ui {
class info_que;
}

class info_que : public QMainWindow
{
    Q_OBJECT

public:
    explicit info_que(QWidget *parent = 0);
    ~info_que();
    bool createConnection();
    void closeEvent (QCloseEvent *event );

private slots:
    void on_pushButton_clicked();

private:
    Ui::info_que *ui;
};

#endif // INFO_QUE_H
