#ifndef QUESTION_H
#define QUESTION_H

/*!
 * \file question.h
 * \brief Abstraction des questions
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <stdlib.h>
#include <iostream>
#include <QMessageBox>

#include "dbconnection.h"
#include "proposition.h"
#include "theme.h"

using namespace std;

/*! \class Question
 * \brief classe representant une question
 *
 *  La classe permet aussi d'interagir directement avec la base de données (UPDATE et DELETE)
 */
class Question
{
public:

    /*!
     *  \brief Constructeur
     *
     *  Définit par défaut l'ID de la question à 0
     *
     */
    Question();

    /*!
     *  \brief Récupère l'ID de la question
     *
     *  \return Un nombre entier, unique par question
     * si l'ID = 0, la question n'a pas encore été ajoutée dans la base de données
     */
    int getId();

    /*!
     *  \brief Récupère l'état de la question
     *
     *  \return Un nombre entier, 1 si la question est activée, 0 sinon
     */
    int getActive();

    /*!
     *  \brief Récupère le libellé 1 de la question
     *
     *  \return Une chaîne de caractères contenant le libellé 1
     */
    string getLibelle1();

    /*!
     *  \brief Récupère le libellé 2 de la question
     *
     *  \return Une chaîne de caractères contenant le libellé 2
     */
    string getLibelle2();

    /*!
     *  \brief Définit l'ID de la question
     *
     *  \param id : doit correspondre à celui de la base de données ou
     * être égal à 0 si la question n'est pas déjà dans la base de données
     */
    void setId(int id);

    /*!
     *  \brief Définit l'état de la question
     *
     *  \param active : doit être égal à 0 ou 1
     */
    void setActive(int active);

    /*!
     *  \brief Définit le libellé 1 de la question
     *
     *  \param libelle1 : première partie de la question
     */
    void setLibelle1(string libelle1);

    /*!
     *  \brief Définit le libellé 2 de la question
     *
     *  \param libelle2 : seconde partie de la question
     */
    void setLibelle2(string libelle2);

    /*!
     *  \brief Change le libellé 1 de la question dans la BDD
     *
     *  \param libelle1 : le nouveau libellé 1
     */
    void updateLibelle1(string libelle1);

    /*!
     *  \brief Change le libellé 2 de la question dans la BDD
     *
     *  \param libelle2 : le nouveau libellé 1
     */
    void updateLibelle2(string libelle2);

    /*!
     *  \brief Active la question dans la BDD
     */
    void enable();

    /*!
     *  \brief Désactive la question dans la BDD
     */
    void disable();

    /*!
     *  \brief Supprime la question dans la BDD
     */
    void remove();


    /*!
     *  \brief Récupération des propositions de la question
     *
     *  Methode qui va chercher dans la base de données
     *  les propositions associées à la question
     *
     *  \return Un QVector contenant des propositions
     */
    QVector<Proposition> getPropositions();


    /*!
     *  \brief Récupération des thèmes liés à la question
     *
     *  Methode qui va chercher dans la base de données
     *  les thèmes qui ont été associés à la question
     *
     *  \return Un QVector contenant des thèmes
     */
    QVector<Theme> getThemes();

    /*!
     *  \brief Fait le lien entre la question actuelle et un thème dans la BDD
     *
     *  \param theme : le thème à associer à la question
     */
    void linkTheme(Theme theme);

    /*!
     *  \brief Supprime le lien entre la question actuelle et un thème dans la BDD
     *
     *  \param theme : le thème à dissocier de la question
     */
    void unlinkTheme(Theme theme);

    /*!
     *  \brief Ajoute ue proposition à la question actuelle dans la BDD
     *
     *  \param proposition : la proposition à ajouter
     */
    void ajouterProposition(Proposition &proposition);

private:
    int id; /*!< ID de la question */
    string libelle1; /*!< Libellé 1 de la question */
    string libelle2; /*!< Libellé 2 de la question */
    int active; /*!< Question active ou non (0 ou 1) */
};

#endif // QUESTION_H
