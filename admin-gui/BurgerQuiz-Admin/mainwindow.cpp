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

        question.remove();

        delete ui->listWidget->takeItem(ui->listWidget->currentRow());
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

void MainWindow::on_pushButton_13_clicked()
{
    if(ui->listWidget->currentRow() != -1)
    {
        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir Libellé 1"),
                                             tr("Libellé 1:"), QLineEdit::Normal,
                                             QString::fromStdString(question.getLibelle1()), &ok);
        if (ok && !text.isEmpty())
        {

            question.updateLibelle1(text.toStdString());

            data.setValue(question);
            ui->listWidget->currentItem()->setData(1, data);
            ui->listWidget->currentItem()->setText(QString::fromStdString(question.getLibelle1() + ", " + question.getLibelle2() + " ou les deux ?"));
        }

    }

}

void MainWindow::on_pushButton_14_clicked()
{
    if(ui->listWidget->currentRow() != -1)
    {
        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir Libellé 2"),
                                             tr("Libellé 2:"), QLineEdit::Normal,
                                             QString::fromStdString(question.getLibelle2()), &ok);
        if (ok && !text.isEmpty())
        {

            question.updateLibelle2(text.toStdString());

            data.setValue(question);
            ui->listWidget->currentItem()->setData(1, data);
            ui->listWidget->currentItem()->setText(QString::fromStdString(question.getLibelle1() + ", " + question.getLibelle2() + " ou les deux ?"));

        }

    }
}

void MainWindow::on_pushButton_16_clicked()
{
    // Exemple repris sur : https://stackoverflow.com/a/29132723

    QDialog * d = new QDialog();
    QVBoxLayout * vbox = new QVBoxLayout();

    QLabel * labelA = new QLabel("Libellé1 :");
    QLineEdit * lineEditA = new QLineEdit();

    QLabel * labelB = new QLabel("Libellé 2 :");
    QLineEdit * lineEditB = new QLineEdit();

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(labelA);
    vbox->addWidget(lineEditA);
    vbox->addWidget(labelB);
    vbox->addWidget(lineEditB);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(!lineEditA->text().isEmpty() && !lineEditB->text().isEmpty())
        {
            Question newQuestion;
            newQuestion.setActive(1);
            newQuestion.setLibelle1(lineEditA->text().toStdString());
            newQuestion.setLibelle2(lineEditB->text().toStdString());

            Questions qManager;
            qManager.createQuestion(newQuestion);

            // Si la question a bien été ajoutée, son ID est différent de 0 suite au passage par référence précédent
            if(newQuestion.getId() != 0)
            {
                QListWidgetItem *newItem = new QListWidgetItem;
                   newItem->setText(QString::fromStdString(newQuestion.getLibelle1() + ", " + newQuestion.getLibelle2() + " ou les deux ?"));
                   QVariant data;
                   data.setValue(newQuestion);
                   newItem->setData(1, data);

                   if(newQuestion.getActive() == 0)
                   {
                       newItem->setBackgroundColor(Qt::gray);
                   }

                   ui->listWidget->insertItem(0, newItem);
            }
        }
    }
}
