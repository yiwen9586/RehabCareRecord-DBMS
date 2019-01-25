#ifndef TREAT_RECORD_H
#define TREAT_RECORD_H

#include <QMainWindow>
#pragma execution_character_set("utf-8")

namespace Ui {
class Treat_Record;
}

class Treat_Record : public QMainWindow
{
    Q_OBJECT

public:
    explicit Treat_Record(QWidget *parent = 0);
    ~Treat_Record();
    bool createConnection();
    void closeEvent (QCloseEvent *event  );

private slots:
    void on_pushButton_clicked();

private:
    Ui::Treat_Record *ui;
};

#endif // TREAT_RECORD_H
