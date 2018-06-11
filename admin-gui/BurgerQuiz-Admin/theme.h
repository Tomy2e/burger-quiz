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
    Theme();

    int getId();
    string getLibelle();
    string getPhoto();

    void setId(int id);
    void setLibelle(string libelle);
    void setPhoto(string photo);

    void updateLibelle(string libelle);
    void updatePhoto(string photo);
    void remove();

private:
    int id; /*!< ID du thème */
    string libelle; /*!< Libellé du thème */
    string photo; /*!< Lien vers la photo du thème */
};

#endif // THEME_H
