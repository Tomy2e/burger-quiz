#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Déconnecté"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    DbConnection *db = new DbConnection;
    if(db->initializeConnection(ui->lineEdit_2->text().toStdString(), ui->lineEdit->text().toStdString(), ui->lineEdit_3->text().toStdString(), ui->lineEdit_4->text().toStdString()))
    {
            qDebug() << "Connexion réussie !";
            statusBar()->showMessage("Connecté en tant que " + ui->lineEdit->text());
            ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
           qDebug() << "Erreur de connexion !";
           QMessageBox msgBox;
           msgBox.setText("Impossible de se connecter, veuillez vérifier les paramètres fournis");
           msgBox.exec();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    statusBar()->showMessage(tr("Déconnecté"));
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    Questions questionsManager;

    QVector<Question> questions = questionsManager.fetchQuestions();

    //qDebug() << "questions";

    for(int i = 0; i < questions.length(); i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
           newItem->setText(QString::fromStdString(questions[i].getLibelle1() + ", " + questions[i].getLibelle2() + " ou les deux ?"));
           QVariant data;
           data.setValue(questions[i]);
           newItem->setData(1, data);
           //qDebug() << newItem->data(1).toString();
           ui->listWidget->insertItem(0, newItem);
    }

    /*QListWidgetItem *newItem = new QListWidgetItem;
       newItem->setText("bonjour");
       //newItem->setData(1, "Test");
       //qDebug() << newItem->data(1).toString();
       ui->listWidget->insertItem(0, newItem);*/

    //ui->listWidget->addItem();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_12_clicked()
{
    QVariant data = ui->listWidget->currentItem()->data(1);

    Question question = data.value<Question>();

    qDebug() << question.getId();
}
