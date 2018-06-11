#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \brief Fenêtre principale
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <QMainWindow>
#include <QDebug>
#include "dbconnection.h"
#include "questions.h"
#include "themes.h"
#include <QtWidgets>
#include "users.h"

Q_DECLARE_METATYPE(Question)
Q_DECLARE_METATYPE(Proposition)
Q_DECLARE_METATYPE(Theme)
Q_DECLARE_METATYPE(User)


namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 * \brief classe représentant la fenêtre principale
 *
 *  La classe gère toutes les interactions et l'affichage graphique
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /*!
     *  \brief Clic sur le bouton "Se connecter"
     */
    void on_pushButton_clicked();

    /*!
     *  \brief Clic sur le bouton "Se déconnecter"
     */
    void on_pushButton_7_clicked();

    /*!
     *  \brief Clic sur le bouton "Retour" dans la page Gestion des questions
     */
    void on_pushButton_8_clicked();

    /*!
     *  \brief Clic sur le bouton "Gestion des questions"
     */
    void on_pushButton_2_clicked();

    /*!
     *  \brief Clic sur le bouton "Supprimer" dans la page Gestion des questions
     */
    void on_pushButton_12_clicked();

    /*!
     *  \brief Sélection d'un élément dans la page Gestion des questions
     */
    void on_listWidget_currentRowChanged(int currentRow);

    /*!
     *  \brief Clic sur le bouton "Désactiver" dans la page Gestion des questions
     */
    void on_pushButton_11_clicked();

    /*!
     *  \brief Clic sur le bouton "Modif. Libellé 1" dans la page Gestion des questions
     */
    void on_pushButton_13_clicked();

    /*!
     *  \brief Clic sur le bouton "Modif. Libellé 2" dans la page Gestion des questions
     */
    void on_pushButton_14_clicked();

    /*!
     *  \brief Clic sur le bouton "Nouvelle question" dans la page Gestion des questions
     */
    void on_pushButton_16_clicked();

    /*!
     *  \brief Clic sur le bouton "voir propositions" dans la page Gestion des questions
     */
    void on_pushButton_10_clicked();

    /*!
     *  \brief Clic sur le bouton "Retour" dans la page Gestion des propositions
     */
    void on_pushButton_15_clicked();

    /*!
     *  \brief Clic sur le bouton "Modifier réponse" dans la page Gestion des propositions
     */
    void on_pushButton_18_clicked();

    /*!
     *  \brief Clic sur le bouton "Nouvelle proposition" dans la page Gestion des propositions
     */
    void on_pushButton_17_clicked();

    /*!
     *  \brief Clic sur le bouton "Désactiver" dans la page Gestion des propositions
     */
    void on_pushButton_19_clicked();

    /*!
     *  \brief Sélection d'un élément dans la page Gestion des propositions
     */
    void on_listWidget_2_currentRowChanged(int currentRow);

    /*!
     *  \brief Clic sur le bouton "Supprimer" dans la page Gestion des propositions
     */
    void on_pushButton_20_clicked();

    /*!
     *  \brief Clic sur le bouton "Gestion des thèmes"
     */
    void on_pushButton_4_clicked();

    /*!
     *  \brief Clic sur le bouton "Retour" dans la page Gestion des thèmes
     */
    void on_pushButton_21_clicked();

    /*!
     *  \brief Clic sur le bouton "Nouveau thème" dans la page Gestion des thèmes
     */
    void on_pushButton_22_clicked();

    /*!
     *  \brief Clic sur le bouton "Renommer" dans la page Gestion des thèmes
     */
    void on_pushButton_23_clicked();

    /*!
     *  \brief Clic sur le bouton "Changer photo" dans la page Gestion des thèmes
     */
    void on_pushButton_25_clicked();

    /*!
     *  \brief Clic sur le bouton "Supprimer" dans la page Gestion des thèmes
     */
    void on_pushButton_24_clicked();

    /*!
     *  \brief Clic sur le bouton "Sélectionner thèmes" dans la page Gestion des questions
     */
    void on_pushButton_9_clicked();

    /*!
     *  \brief Clic sur le bouton "Retour" dans la page de sélection des thèmes pour une question
     */
    void on_pushButton_26_clicked();

    /*!
     *  \brief Clic sur le bouton "Valider" dans la page de sélection des thèmes pour une question
     */
    void on_pushButton_27_clicked();

    /*!
     *  \brief Clic sur le bouton "Gestion des utilisateurs"
     */
    void on_pushButton_3_clicked();

    /*!
     *  \brief Clic sur le bouton "Retour" dans la page de gestion des utilisateurs
     */
    void on_pushButton_28_clicked();

    /*!
     *  \brief Clic sur le bouton "Nouvel utilisateur" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_29_clicked();

    /*!
     *  \brief Clic sur le bouton "Modifier MDP" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_30_clicked();

    /*!
     *  \brief Clic sur le bouton "Modifier âge" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_31_clicked();

    /*!
     *  \brief Clic sur le bouton "Modifier email" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_32_clicked();

    /*!
     *  \brief Clic sur le bouton "Modifier photo" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_33_clicked();

    /*!
     *  \brief Clic sur le bouton "Supprimer" dans la page de Gestion des utilisateurs
     */
    void on_pushButton_34_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
