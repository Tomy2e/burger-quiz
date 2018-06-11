#ifndef USER_H
#define USER_H

/*!
 * \file user.h
 * \brief Abstraction des utilisateurs
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */

#include <stdlib.h>
#include <iostream>
#include <QtWidgets>
#include "dbconnection.h"

using namespace std;

/*! \class User
 * \brief classe representant un utilisateur
 *
 *  La classe permet aussi d'interagir directement avec la base de données (UPDATE et DELETE)
 */
class User
{
public:

    /*!
     *  \brief Constructeur
     *
     *  Définit par défaut l'ID utilisateur à 0
     *
     */
    User();

    /*!
     *  \brief Récupère l'ID utilisateur
     *
     *  \return Un nombre entier, unique par utilisateur
     * si l'ID = 0, l'utilisateur n'a pas encore été ajouté dans la base de données
     */
    int getId();

    /*!
     *  \brief Récupère le nom d'utilisateur
     *
     *  \return Une chaîne de caractères contenant nom d'utilisateur
     */
    string getUsername();

    /*!
     *  \brief Récupère le mot de passe
     *
     *  \return Une chaîne de caractères contenant le mot de passe
     * hashé avec l'algorithme Bcrypt
     */
    string getPassword();

    /*!
     *  \brief Récupère l'âge
     *
     *  \return Un entier avec l'âge de l'utilisateur
     */
    int getAge();

    /*!
     *  \brief Récupère l'email de l'utilisateur
     *
     *  \return Une chaîne de caractères qui contient l'email
     */
    string getEmail();

    /*!
     *  \brief Récupère la photo de profil
     *
     *  \return Une chaîne de caractères contenant l'adresse
     * de la photo de profil
     */
    string getPhoto();

    /*!
     *  \brief Définit l'ID de l'utilisateur
     *
     *  \param id : doit correspondre à celui de la base de données ou
     * être égal à 0 si l'utilisateur n'est pas déjà dans la base de données
     */
    void setId(int id);

    /*!
     *  \brief Définit le nom d'utilisateur de l'utilisateur
     *
     *  \param username : chaîne de caractère alphanumérique
     */
    void setUsername(string username);

    /*!
     *  \brief Définit le mot de passe de l'utilisateur
     *
     *  \param password : le mot de passe
     *  \param hashed : indique si le mot de passe est déjà hashé ou non
     */
    void setPassword(string password, bool hashed = true);

    /*!
     *  \brief Définit l'âge de l'utilisateur
     *
     *  \param age : nombre entier, de préférence entre 13 et 100
     */
    void setAge(int age);

    /*!
     *  \brief Définit l'adresse mail de l'utilisateur
     *
     *  \param email : chaîne de caractère contenant un email
     */
    void setEmail(string email);

    /*!
     *  \brief Définit la photo l'utilisateur
     *
     *  \param photo : chaîne de caractère avec un lien HTTP vers
     * la photo de profil
     */
    void setPhoto(string photo);

    /*!
     *  \brief Change le mot de passe de l'utilisateur dans la BDD
     *
     *  \param password : le nouveau mot de passe
     */
    void updatePassword(string password);

    /*!
     *  \brief Change l'âge de l'utilisateur dans la BDD
     *
     *  \param age : le nouvel âge de l'utilisateur
     */
    void updateAge(int age);

    /*!
     *  \brief Change l'adresse mail de l'utilisateur dans la BDD
     *
     *  \param email : la nouvelle adresse mail
     */
    void updateEmail(string email);

    /*!
     *  \brief Change la photo de l'utilisateur dans la BDD
     *
     *  \param photo : la nouvelle photo
     */
    void updatePhoto(string photo);


    /*!
     *  \brief Supprime l'utilisateur dans la BDD
     *
     * Cela supprime également toutes les données
     * associées à l'utilisateur
     *
     */
    void remove();

private:
    int id; /*!< ID de l'utilisateur */
    string username; /*!< Nom d'utilisateur */
    string password; /*!< Mot de passe (normalement hashé) */
    int age; /*!< Age de l'utilisateur */
    string email; /*!< Email de l'utilisateur */
    string photo; /*!< Lien vers la photo de l'utilisateur */
};

#endif // USER_H
