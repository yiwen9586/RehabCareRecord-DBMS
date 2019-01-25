#ifndef ASS_QUE_H
#define ASS_QUE_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")

namespace Ui {
class ass_que;
}

class ass_que : public QMainWindow
{
    Q_OBJECT

public:
    explicit ass_que(QWidget *parent = 0);
    ~ass_que();
    bool createConnection();
     void closeEvent (QCloseEvent *event  );

private slots:
     void on_pushButton_clicked();

private:
    Ui::ass_que *ui;
};

#endif // ASS_QUE_H
