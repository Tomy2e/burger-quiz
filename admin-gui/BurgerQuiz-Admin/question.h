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
    Question();
    int getId();
    int getActive();
    string getLibelle1();
    string getLibelle2();

    void setId(int id);
    void setActive(int active);
    void setLibelle1(string libelle1);
    void setLibelle2(string libelle2);

    void updateLibelle1(string libelle1);
    void updateLibelle2(string libelle2);

    void enable();
    void disable();
    void remove();

    QVector<Proposition> getPropositions();

    QVector<Theme> getThemes();

    void linkTheme(Theme theme);
    void unlinkTheme(Theme theme);

    void ajouterProposition(Proposition &proposition);

private:
    int id; /*!< ID de la question */
    string libelle1; /*!< Libellé 1 de la question */
    string libelle2; /*!< Libellé 2 de la question */
    int active; /*!< Question active ou non (0 ou 1) */
};

#endif // QUESTION_H
