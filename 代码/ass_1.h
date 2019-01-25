#ifndef ASS_1_H
#define ASS_1_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")

namespace Ui {
class ass_1;
}

class ass_1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ass_1(QWidget *parent = 0);
    ~ass_1();
    bool createConnection();
     void closeEvent (QCloseEvent *event  );

private slots:
    void on_pushButton_clicked();

private:
    Ui::ass_1 *ui;
};

#endif // ASS_1_H
