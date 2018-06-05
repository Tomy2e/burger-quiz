#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class DbConnection
{
public:
    DbConnection();
    bool initializeConnection(string serverAddr, string username, string password, string dbname);
    static sql::Connection * getConnection();

private:
    sql::Driver *driver;
    static sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
};

#endif // DBCONNECTION_H
