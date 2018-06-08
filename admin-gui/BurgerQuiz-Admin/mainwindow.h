#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dbconnection.h"
#include "questions.h"
#include "themes.h"
#include <QtWidgets>

Q_DECLARE_METATYPE(Question)
Q_DECLARE_METATYPE(Proposition)
Q_DECLARE_METATYPE(Theme)


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_12_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_listWidget_2_currentRowChanged(int currentRow);

    void on_pushButton_20_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_24_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
