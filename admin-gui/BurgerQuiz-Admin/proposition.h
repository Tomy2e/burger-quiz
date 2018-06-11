#ifndef PROPOSITION_H
#define PROPOSITION_H

/*!
 * \file proposition.h
 * \brief Abstraction des propositions
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

#include "dbconnection.h"

using namespace std;

/*! \class Proposition
 * \brief classe representant une proposition
 *
 *  La classe permet aussi d'interagir directement avec la base de données (UPDATE et DELETE)
 */
class Proposition
{
public:
    Proposition();
    int getId();
    string getLibelleProposition();
    int getReponseProposition();
    int getActive();

    void setId(int id);
    void setLibelleProposition(string libelleProposition);
    void setReponseProposition(int reponseProposition);
    void setActive(int active);

    void disable();
    void remove();
    void updateLibelleProposition(string libelleProposition);
    void updateReponseProposition(int reponseProposition);
    void enable();

private:
    int id; /*!< ID de la proposition */
    string libelleProposition; /*!< Libellé de la proposition */
    int reponseProposition; /*!< Réponse à la proposition (1, 2 ou 3) */
    int active; /*!< Proposition active ou non (0 ou 1) */
};

#endif // PROPOSITION_H
