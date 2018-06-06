#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Déconnecté"));
    setWindowTitle("Connexion - BurgerQuizAdmin");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setWindowTitle("Accueil - BurgerQuizAdmin");

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
    setWindowTitle("Connexion - BurgerQuizAdmin");

    statusBar()->showMessage(tr("Déconnecté"));
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_8_clicked()
{
    setWindowTitle("Accueil - BurgerQuizAdmin");
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    setWindowTitle("Gestion des questions - BurgerQuizAdmin");
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

           if(questions[i].getActive() == 0)
           {
               newItem->setBackgroundColor(Qt::gray);
           }
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
    if(ui->listWidget->currentRow() != -1)
    {
        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        qDebug() << question.getId();
    }
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow != -1)
    {
        QVariant data = ui->listWidget->item(currentRow)->data(1);

        Question question = data.value<Question>();

        if(question.getActive() == 1)
        {
            ui->pushButton_11->setText("Désactiver");
        }
        else
        {
            ui->pushButton_11->setText("Activer");
        }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    if(ui->listWidget->currentRow() != -1)
    {
        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        if(question.getActive() == 1)
        {
            // On désactive
            question.disable();

            if(question.getActive() == 0)
            {
                // On met à jour l'objet question
                data.setValue(question);
                ui->listWidget->currentItem()->setData(1, data);

                ui->listWidget->currentItem()->setBackgroundColor(Qt::gray);
                ui->pushButton_11->setText("Activer");
            }
        }
        else
        {
            // On active
            question.enable();

            if(question.getActive() == 1)
            {
                // On met à jour l'objet question
                data.setValue(question);
                ui->listWidget->currentItem()->setData(1, data);

                ui->listWidget->currentItem()->setBackgroundColor(Qt::white);
                ui->pushButton_11->setText("Désactiver");
            }
        }
    }
}
