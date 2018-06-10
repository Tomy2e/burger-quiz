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

void MainWindow::on_pushButton_10_clicked()
{
    if(ui->listWidget->currentRow() != -1)
    {
        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        ui->stackedWidget->setCurrentIndex(3);

        ui->label_2->setText(QString::fromStdString(question.getLibelle1() + ", " + question.getLibelle2() + " ou les 2 ?"));

        QVector<Proposition> propositions = question.getPropositions();

        ui->listWidget_2->clear();

        for(int i = 0; i < propositions.length(); i++)
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(QString::fromStdString(propositions[i].getLibelleProposition()));
            QVariant data;
            data.setValue(propositions[i]);
            newItem->setData(1, data);

            if(propositions[i].getActive() == 0)
            {
               newItem->setBackgroundColor(Qt::gray);
            }

            ui->listWidget_2->insertItem(0, newItem);
        }

    }
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_18_clicked()
{
    if(ui->listWidget_2->currentRow() != -1)
    {
        QVariant data = ui->listWidget_2->currentItem()->data(1);

        Proposition proposition = data.value<Proposition>();

        QDialog * d = new QDialog();
        QVBoxLayout * vbox = new QVBoxLayout();
        QLabel * labelA = new QLabel("Réponse : ");
        QComboBox * comboBoxA = new QComboBox();
        comboBoxA->addItems(QStringList() << "Libellé 1" << "Libellé 2" << "Les 2");

        switch(proposition.getReponseProposition())
        {
            case 1:
            comboBoxA->setCurrentIndex(comboBoxA->findText("Libellé 1"));
            break;
            case 2:
            comboBoxA->setCurrentIndex(comboBoxA->findText("Libellé 2"));
            break;
            case 3:
            comboBoxA->setCurrentIndex(comboBoxA->findText("Les 2"));
            break;
        }

        QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                            | QDialogButtonBox::Cancel);

        QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

        vbox->addWidget(labelA);
        vbox->addWidget(comboBoxA);
        vbox->addWidget(buttonBox);

        d->setLayout(vbox);

        int result = d->exec();
        if(result == QDialog::Accepted)
        {

            int selected = comboBoxA->currentIndex() + 1;

            if(selected > 0 && selected < 4)
            {
                proposition.updateReponseProposition(selected);

                if(proposition.getReponseProposition() == selected)
                {
                    // successfully updated reponse
                    QVariant data;
                    data.setValue(proposition);
                    ui->listWidget_2->currentItem()->setData(1, data);
                }
            }
        }

    }

}

void MainWindow::on_pushButton_17_clicked()
{
    QDialog * d = new QDialog();
    QVBoxLayout * vbox = new QVBoxLayout();


    QLabel * labelA = new QLabel("Proposition : ");
    QLineEdit * lineEditA = new QLineEdit();

    QLabel * labelB = new QLabel("Réponse : ");
    QComboBox * comboBoxA = new QComboBox();
    comboBoxA->addItems(QStringList() << "Libellé 1" << "Libellé 2" << "Les 2");


    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(labelA);
    vbox->addWidget(lineEditA);
    vbox->addWidget(labelB);
    vbox->addWidget(comboBoxA);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(!lineEditA->text().isEmpty())
        {
            Proposition newProp;
            newProp.setActive(1);
            newProp.setLibelleProposition(lineEditA->text().toStdString());
            newProp.setReponseProposition(comboBoxA->currentIndex() + 1);

            QVariant data = ui->listWidget->currentItem()->data(1);

            Question question = data.value<Question>();

            question.ajouterProposition(newProp);

            if(newProp.getId() != 0)
            {
                // Successfuly added to the database
                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setText(QString::fromStdString(newProp.getLibelleProposition()));
                QVariant data;
                data.setValue(newProp);
                newItem->setData(1, data);
                ui->listWidget_2->insertItem(0, newItem);
            }
        }
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    if(ui->listWidget_2->currentRow() != -1)
    {
        QVariant data = ui->listWidget_2->currentItem()->data(1);

        Proposition proposition = data.value<Proposition>();

        if(proposition.getActive() == 1)
        {
            // On désactive
            proposition.disable();
            ui->pushButton_19->setText("Activer");
        }
        else
        {
            // On active
            proposition.enable();
            ui->pushButton_19->setText("Désactiver");
        }

        if(proposition.getActive() == 0)
        {
           ui->listWidget_2->currentItem()->setBackgroundColor(Qt::gray);
        }
        else
        {
           ui->listWidget_2->currentItem()->setBackgroundColor(Qt::white);
        }

        data.setValue(proposition);
        ui->listWidget_2->currentItem()->setData(1, data);
    }
}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
    if(currentRow != -1)
    {
        QVariant data = ui->listWidget_2->item(currentRow)->data(1);

        Proposition proposition = data.value<Proposition>();

        if(proposition.getActive() == 0)
        {
            ui->pushButton_19->setText("Activer");
        }
        else
        {
            ui->pushButton_19->setText("Désactiver");
        }
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    // Supprimer une proposition
    if(ui->listWidget_2->currentRow() != -1)
    {
        QVariant data = ui->listWidget_2->currentItem()->data(1);

        Proposition proposition = data.value<Proposition>();

        proposition.remove();

        delete ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    Themes themesMgr;

    QVector<Theme> themes = themesMgr.fetchThemes();


    ui->listWidget_3->clear();

    for(int i = 0; i < themes.length(); i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::fromStdString(themes[i].getLibelle()));
        QVariant data;
        data.setValue(themes[i]);
        newItem->setData(1, data);

        ui->listWidget_3->insertItem(0, newItem);
    }
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_22_clicked()
{
    QDialog * d = new QDialog();
    QVBoxLayout * vbox = new QVBoxLayout();


    QLabel * labelA = new QLabel("Libellé Thème : ");
    QLineEdit * lineEditA = new QLineEdit();

    QLabel * labelB = new QLabel("URL Photo : ");
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
        if(!lineEditA->text().isEmpty())
        {
            Theme newTheme;
            newTheme.setLibelle(lineEditA->text().toStdString());
            newTheme.setPhoto(lineEditB->text().toStdString());

            Themes themesMgr;
            themesMgr.createTheme(newTheme);

            if(newTheme.getId() != 0)
            {
                // Successfuly added to the database
                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setText(QString::fromStdString(newTheme.getLibelle()));
                QVariant data;
                data.setValue(newTheme);
                newItem->setData(1, data);
                ui->listWidget_3->insertItem(0, newItem);
            }


        }
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    if(ui->listWidget_3->currentRow() != -1)
    {
        QVariant data = ui->listWidget_3->currentItem()->data(1);

        Theme theme = data.value<Theme>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir Libellé Thème"),
                                             tr("Libellé:"), QLineEdit::Normal,
                                             QString::fromStdString(theme.getLibelle()), &ok);
        if (ok && !text.isEmpty())
        {
            theme.updateLibelle(text.toStdString());

            data.setValue(theme);
            ui->listWidget_3->currentItem()->setData(1, data);
            ui->listWidget_3->currentItem()->setText(QString::fromStdString(theme.getLibelle()));

        }

    }
}

void MainWindow::on_pushButton_25_clicked()
{
    if(ui->listWidget_3->currentRow() != -1)
    {
        QVariant data = ui->listWidget_3->currentItem()->data(1);

        Theme theme = data.value<Theme>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir photo"),
                                             tr("URL :"), QLineEdit::Normal,
                                             QString::fromStdString(theme.getPhoto()), &ok);
        if (ok && !text.isEmpty())
        {
            theme.updatePhoto(text.toStdString());

            data.setValue(theme);
            ui->listWidget_3->currentItem()->setData(1, data);
        }

    }
}

void MainWindow::on_pushButton_24_clicked()
{
    if(ui->listWidget_3->currentRow() != -1)
    {
        QVariant data = ui->listWidget_3->currentItem()->data(1);

        Theme theme = data.value<Theme>();

        theme.remove();

        delete ui->listWidget_3->takeItem(ui->listWidget_3->currentRow());

    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(ui->listWidget->currentRow() != -1)
    {

        QVariant data = ui->listWidget->currentItem()->data(1);

        Question question = data.value<Question>();

        ui->stackedWidget->setCurrentIndex(5);

        ui->label_7->setText(QString::fromStdString(question.getLibelle1() + ", " + question.getLibelle2() + " ou les 2 ?"));

        QVector<Theme> themes_associes = question.getThemes();

        Themes themesMgr;
        QVector<Theme> all_themes = themesMgr.fetchThemes();


        ui->listWidget_4->clear();

        for(int i = 0; i < all_themes.size(); i++)
        {
            // Source : http://www.qtcentre.org/threads/7032-QListWidget-with-check-box-s?p=37201#post37201

            QListWidgetItem* item = new QListWidgetItem();
            item->setText(QString::fromStdString(all_themes[i].getLibelle()));
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag

            item->setCheckState(Qt::Unchecked);

            for(int j = 0; j < themes_associes.size(); j++)
            {
                if(all_themes[i].getId() == themes_associes[j].getId())
                {
                    item->setCheckState(Qt::Checked);
                }
            }

            QVariant data;
            data.setValue(all_themes[i]);
            item->setData(1, data);

            ui->listWidget_4->insertItem(0, item);
        }

    }

}

void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_27_clicked()
{
    for(int i = 0; i < ui->listWidget_4->count(); i++)
    {
        QVariant dataTheme = ui->listWidget_4->item(i)->data(1);
        Theme theme = dataTheme.value<Theme>();

        QVariant dataQuestion = ui->listWidget->currentItem()->data(1);
        Question question = dataQuestion.value<Question>();

        if(ui->listWidget_4->item(i)->checkState() == Qt::Checked)
        {
            question.linkTheme(theme);
        }
        else
        {
            question.unlinkTheme(theme);
        }
    }

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);

    Users usersMgr;

    QVector<User> users = usersMgr.fetchUsers();


    ui->listWidget_5->clear();

    for(int i = 0; i < users.length(); i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::fromStdString(users[i].getUsername()));
        QVariant data;
        data.setValue(users[i]);
        newItem->setData(1, data);

        ui->listWidget_5->insertItem(0, newItem);
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_29_clicked()
{
    // Add new user
    QDialog * d = new QDialog();
    QVBoxLayout * vbox = new QVBoxLayout();


    QLabel * labelA = new QLabel("Nom d'utilisateur : ");
    QLineEdit * lineEditA = new QLineEdit();

    QLabel * labelB = new QLabel("Age : ");
    QSpinBox * spin = new QSpinBox();
    spin->setMinimum(13);
    spin->setMaximum(100);

    QLabel * labelC = new QLabel("Email : ");
    QLineEdit * lineEditC = new QLineEdit();

    QLabel * labelD = new QLabel("Mot de passe : ");
    QLineEdit * lineEditD = new QLineEdit();
    lineEditD->setEchoMode(QLineEdit::Password);


    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(labelA);
    vbox->addWidget(lineEditA);
    vbox->addWidget(labelB);
    vbox->addWidget(spin);
    vbox->addWidget(labelC);
    vbox->addWidget(lineEditC);
    vbox->addWidget(labelD);
    vbox->addWidget(lineEditD);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(!lineEditA->text().isEmpty())
        {
            User newUser;
            newUser.setUsername(lineEditA->text().toStdString());
            newUser.setAge(spin->value());
            newUser.setEmail(lineEditC->text().toStdString());
            newUser.setPassword(lineEditD->text().toStdString(), false);
            newUser.setPhoto("");

            Users usersMgr;
            usersMgr.createUser(newUser);

            if(newUser.getId() != 0)
            {
                // Successfuly added to the database
                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setText(QString::fromStdString(newUser.getUsername()));
                QVariant data;
                data.setValue(newUser);
                newItem->setData(1, data);
                ui->listWidget_5->insertItem(0, newItem);
            }
        }
    }
}

void MainWindow::on_pushButton_30_clicked()
{
    if(ui->listWidget_5->currentRow() != -1)
    {
        QVariant data = ui->listWidget_5->currentItem()->data(1);

        User user = data.value<User>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir MDP"),
                                             tr("Nouv. MDP :"), QLineEdit::Password,
                                             "", &ok);
        if (ok && !text.isEmpty())
        {
            user.updatePassword(text.toStdString());

            data.setValue(user);
            ui->listWidget_5->currentItem()->setData(1, data);
        }
    }
}

void MainWindow::on_pushButton_31_clicked()
{
    if(ui->listWidget_5->currentRow() != -1)
    {
        QVariant data = ui->listWidget_5->currentItem()->data(1);

        User user = data.value<User>();

        bool ok;

        int i = QInputDialog::getInt(NULL, tr("Définir âge"),
                                     tr("Âge :"), user.getAge(), 13, 100, 1, &ok);
        if (ok)
        {
            user.updateAge(i);

            data.setValue(user);
            ui->listWidget_5->currentItem()->setData(1, data);;
        }


    }
}

void MainWindow::on_pushButton_32_clicked()
{
    if(ui->listWidget_5->currentRow() != -1)
    {
        QVariant data = ui->listWidget_5->currentItem()->data(1);

        User user = data.value<User>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir Email"),
                                             tr("Nouv. MDP :"), QLineEdit::Normal,
                                             QString::fromStdString(user.getEmail()), &ok);
        if (ok)
        {
            user.updateEmail(text.toStdString());

            data.setValue(user);
            ui->listWidget_5->currentItem()->setData(1, data);
        }
    }
}

void MainWindow::on_pushButton_33_clicked()
{
    if(ui->listWidget_5->currentRow() != -1)
    {
        QVariant data = ui->listWidget_5->currentItem()->data(1);

        User user = data.value<User>();

        bool ok;

        QString text = QInputDialog::getText(this, tr("Définir photo"),
                                             tr("URL Nouv. photo :"), QLineEdit::Normal,
                                             QString::fromStdString(user.getPhoto()), &ok);
        if (ok && !text.isEmpty())
        {
            user.updatePhoto(text.toStdString());

            data.setValue(user);
            ui->listWidget_5->currentItem()->setData(1, data);
        }
    }
}

void MainWindow::on_pushButton_34_clicked()
{
    // Remove user

    if(ui->listWidget_5->currentRow() != -1)
    {
        QVariant data = ui->listWidget_5->currentItem()->data(1);

        User user = data.value<User>();

        user.remove();

        delete ui->listWidget_5->takeItem(ui->listWidget_5->currentRow());

    }
}
