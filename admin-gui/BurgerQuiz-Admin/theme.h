#ifndef THEME_H
#define THEME_H

/*!
 * \file theme.h
 * \brief Abstraction des thèmes de questions
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <stdlib.h>
#include <iostream>
#include "dbconnection.h"
#include <QtWidgets>

using namespace std;

/*! \class Theme
 * \brief classe representant un thème
 *
 *  La classe permet aussi d'interagir directement avec la base de données (UPDATE et DELETE)
 */
class Theme
{
public:

    /*!
     *  \brief Constructeur
     *
     *  Définit par défaut l'ID du thème à 0
     *
     */
    Theme();

    /*!
     *  \brief Récupère l'ID du thème
     *
     *  \return Un nombre entier, unique par thème
     * si l'ID = 0, le thème n'a pas encore été ajouté dans la base de données
     */
    int getId();

    /*!
     *  \brief Récupère le libellé du thème
     *
     *  \return Une chaîne de caractères contenant le libellé du thème
     */
    string getLibelle();

    /*!
     *  \brief Récupère la photo du thème
     *
     *  \return Une chaîne de caractères contenant le lien HTTP
     * vers la photo du thème
     */
    string getPhoto();

    /*!
     *  \brief Définit l'ID du thème
     *
     *  \param id : doit correspondre à celui de la base de données ou
     * être égal à 0 si le thème n'est pas déjà dans la base de données
     */
    void setId(int id);

    /*!
     *  \brief Définit le libellé du thème
     *
     *  \param libelle : une chaîne de caractères au format alphanumérique
     */
    void setLibelle(string libelle);

    /*!
     *  \brief Définit la photo du thème
     *
     *  \param photo : une chaîne de caractères contenant le lien HTTP
     * vers la photo du thème
     */
    void setPhoto(string photo);

    /*!
     *  \brief Change le libellé du thème dans la BDD
     *
     *  \param libelle : le nouveau libellé
     */
    void updateLibelle(string libelle);

    /*!
     *  \brief Change la photo du thème dans la BDD
     *
     *  \param photo : la nouvelle photo
     */
    void updatePhoto(string photo);

    /*!
     *  \brief Supprime le thème dans la BDD
     *
     * Les liens thèmes-questions sont aussi supprimés
     *
     */
    void remove();

private:
    int id; /*!< ID du thème */
    string libelle; /*!< Libellé du thème */
    string photo; /*!< Lien vers la photo du thème */
};

#endif // THEME_H
