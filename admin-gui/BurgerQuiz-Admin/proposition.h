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
    /*!
     *  \brief Constructeur
     *
     *  Définit par défaut l'ID de la proposition à 0
     *
     */
    Proposition();

    /*!
     *  \brief Récupère l'ID de la proposition
     *
     *  \return Un nombre entier, unique par proposition
     * si l'ID = 0, la proposition n'a pas encore été ajoutée dans la base de données
     */
    int getId();

    /*!
     *  \brief Récupère le libellé de la proposition
     *
     *  \return Une chaine de caractères contenant le libellé de la proposition
     */
    string getLibelleProposition();

    /*!
     *  \brief Récupère la réponse de la proposition
     *
     *  \return Un nombre entier (1 = libellé 1, 2 = libellé 2, 3 = les deux)
     */
    int getReponseProposition();

    /*!
     *  \brief Récupère l'état de la proposition
     *
     *  \return Un nombre entier (1 = activé, 2 = désactivé)
     */
    int getActive();

    /*!
     *  \brief Définit l'ID de la proposition
     *
     *  \param id : doit correspondre à celui de la base de données ou
     * être égal à 0 si la proposition n'est pas déjà dans la base de données
     */
    void setId(int id);

    /*!
     *  \brief Définit le libellé de la proposition
     *
     *  \param libelleProposition : Une chaine de caractères contenant le libellé de la proposition
     */
    void setLibelleProposition(string libelleProposition);

    /*!
     *  \brief Définit la réponse de la proposition
     *
     *  \param reponseProposition : Un nombre entier (1 = libellé 1, 2 = libellé 2, 3 = les deux)
     */
    void setReponseProposition(int reponseProposition);

    /*!
     *  \brief Définit l'état de la proposition
     *
     *  \param active : doit être égal à 0 ou 1
     */
    void setActive(int active);

    /*!
     *  \brief Désactiver la proposition dans la base de données
     */
    void disable();

    /*!
     *  \brief Supprime la proposition dans la base de données
     */
    void remove();

    /*!
     *  \brief Met à jour le libellé de la proposition dans la BDD
     *
     *  \param libelleProposition : Une chaine de caractères contenant le libellé de la proposition
     */
    void updateLibelleProposition(string libelleProposition);

    /*!
     *  \brief Met à jour la réponse de la proposition dans la BDD
     *
     *  \param reponseProposition : Un nombre entier (1 = libellé 1, 2 = libellé 2, 3 = les deux)
     */
    void updateReponseProposition(int reponseProposition);

    /*!
     *  \brief Active la proposition dans la base de données
     */
    void enable();

private:
    int id; /*!< ID de la proposition */
    string libelleProposition; /*!< Libellé de la proposition */
    int reponseProposition; /*!< Réponse à la proposition (1, 2 ou 3) */
    int active; /*!< Proposition active ou non (0 ou 1) */
};

#endif // PROPOSITION_H
