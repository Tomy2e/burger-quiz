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

    QVector<Question> fetchQuestions();
    void createQuestion(Question &question);
};

#endif // QUESTIONS_H
