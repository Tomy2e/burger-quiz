#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T17:23:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BurgerQuiz-Admin
TEMPLATE = app

LIBS += -lmysqlcppconn

SOURCES += main.cpp\
        mainwindow.cpp \
    dbconnection.cpp \
    questions.cpp \
    question.cpp \
    proposition.cpp \
    theme.cpp \
    themes.cpp \
    user.cpp \
    users.cpp

HEADERS  += mainwindow.h \
    dbconnection.h \
    questions.h \
    question.h \
    proposition.h \
    theme.h \
    themes.h \
    user.h \
    users.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
