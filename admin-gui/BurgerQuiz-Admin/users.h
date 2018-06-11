#ifndef USERS_H
#define USERS_H

/*!
 * \file user.h
 * \brief Gestion des utilisateurs
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <QVector>
#include "user.h"
#include <QtWidgets>
#include "dbconnection.h"

/*! \class Users
 * \brief classe permettant d'ajouter et récupérer les utilisateurs
 *
 *  Cette classe gère le CREATE et le READ sur la table utilisateurs
 */
class Users
{
public:
    Users();

    /*!
     *  \brief Récupération des utilisateurs
     *
     *  Methode qui va chercher dans la base de données
     *  tous les utilisateurs
     *
     *  \return Un QVector contenant des utilisateurs
     */
    QVector<User> fetchUsers();

    /*!
     *  \brief Crée un nouvel utilisateur
     *
     *  Méthode qui permet d'ajouter un nouvel utilisateur
     *  à la base de données
     *
     *  \param user : le nouvel utilisateur, passé par référence
     */
    void createUser(User &user);
};

#endif // USERS_H
