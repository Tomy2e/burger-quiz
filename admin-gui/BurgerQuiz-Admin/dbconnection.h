#ifndef DBCONNECTION_H
#define DBCONNECTION_H

/*!
 * \file dbconnection.h
 * \brief Gestion du pointeur de connexion à la base de données
 * \author Tomy G. & Gwenolé LF.
 * \version 0.1
 */


#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

/*! \class DbConnection
 * \brief classe contenant le pointeur de connexion à la base de données
 *
 *  La classe gère l'initialisation et la récupération du pointeur
 */

class DbConnection
{
public:
    DbConnection();

    /*!
     *  \brief Initialise la connexion à la base de données
     *
     *  \param serverAddr : l'adresse du serveur MySQL (sans le port)
     *  \param username : le nom d'utilisateur MySQL
     *  \param password : le mot de passe MySQL
     *  \param dbname : le nom de la base de données MySQL
     *  \return true si la connexion s'est effectuée avec succès, sinon false
     */
    bool initializeConnection(string serverAddr, string username, string password, string dbname);

    /*!
     *  \brief Permet de réutiliser une connexion déjà existante
     *
     * \return le pointeur vers la connexion à la base de donnnées
     */
    static sql::Connection * getConnection();

private:
    sql::Driver *driver; /*!< Instance du driver */
    static sql::Connection *con; /*!< Pointeur vers la connexion MySQL */
};

#endif // DBCONNECTION_H
