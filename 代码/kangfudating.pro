#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T15:26:32
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kangfudating
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    date_que.cpp \
    info_que.cpp \
    month_view.cpp \
    reason_solution.cpp \
    stu_info.cpp \
    treat_record.cpp \
    ass_que.cpp \
    ass_2.cpp \
    ass_1.cpp

HEADERS  += mainwindow.h \
    date_que.h \
    info_que.h \
    month_view.h \
    reason_solution.h \
    stu_info.h \
    treat_record.h \
    ass_que.h \
    ass_2.h \
    ass_1.h

FORMS    += mainwindow.ui \
    date_que.ui \
    info_que.ui \
    month_view.ui \
    reason_solution.ui \
    stu_info.ui \
    treat_record.ui \
    ass_que.ui \
    ass_2.ui \
    ass_1.ui

RC_FILE= myapp.rc
