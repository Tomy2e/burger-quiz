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
    bool initializeConnection(string serverAddr, string username, string password, string dbname);
    static sql::Connection * getConnection();

private:
    sql::Driver *driver; /*!< Instance du driver */
    static sql::Connection *con; /*!< Pointeur vers la connexion MySQL */
};

#endif // DBCONNECTION_H
