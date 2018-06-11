#ifndef QUESTIONS_H
#define QUESTIONS_H

/*!
 * \file questions.h
 * \brief Permet de récupérer les questions existantes et d'ajouter une question
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include "question.h"
#include "dbconnection.h"
#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include "proposition.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

/*! \class Questions
 * \brief classe permettant d'ajouter et récupérer les questions
 *
 *  Cette classe gère le CREATE et le READ sur la table questions
 */
class Questions
{
public:
    Questions();

    /*!
     *  \brief Récupération des questions
     *
     *  Methode qui va chercher dans la base de données
     *  toutes les questions
     *
     *  \return Un QVector contenant des questions
     */
    QVector<Question> fetchQuestions();

    /*!
     *  \brief Crée une nouvelle question
     *
     *  Méthode qui permet d'ajouter une nouvelle question
     *  à la base de données
     *
     *  \param question : la nouvelle question, passée par référence
     */
    void createQuestion(Question &question);
};

#endif // QUESTIONS_H
