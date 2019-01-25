#ifndef ASS_2_H
#define ASS_2_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")

namespace Ui {
class ass_2;
}

class ass_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ass_2(QWidget *parent = 0);
    ~ass_2();
    bool createConnection();
     void closeEvent (QCloseEvent *event  );


private slots:
     void on_pushButton_clicked();

     void on_save_btn_clicked();

private:
    Ui::ass_2 *ui;
};

#endif // ASS_2_H
