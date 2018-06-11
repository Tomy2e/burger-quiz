#ifndef THEMES_H
#define THEMES_H

/*!
 * \file themes.h
 * \brief Récupération des thèmes et création de nouveaux thèmes
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include "dbconnection.h"
#include "theme.h"
#include <QVector>
#include <QtWidgets>

/*! \class Themes
 * \brief classe permettant d'ajouter et récupérer les thèmes
 *
 *  Cette classe gère le CREATE et le READ sur la table themes
 */
class Themes
{
public:
    Themes();

    /*!
     *  \brief Récupération des thèmes
     *
     *  Methode qui va chercher dans la base de données
     *  tous les thèmes
     *
     *  \return Un QVector contenant des thèmes
     */
    QVector<Theme> fetchThemes();

    /*!
     *  \brief Crée un nouveau thème
     *
     *  Méthode qui permet d'ajouter un nouveau thème
     *  à la base de données
     *
     *  \param theme : le nouveau thème, passé par référence
     */
    void createTheme(Theme &theme);
};

#endif // THEMES_H
