#include "dbconnection.h"

sql::Connection* DbConnection::con = NULL;

DbConnection::DbConnection()
{

}

bool DbConnection::initializeConnection(string serverAddr, string username, string password, string dbname)
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://"+ serverAddr +":3306", username, password);
        /* Connect to the MySQL test database */
        con->setSchema(dbname);

        return true;
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        return false;
      }
}

sql::Connection * DbConnection::getConnection()
{
    if(con == NULL)
    {
        throw new string("The database is not initialized!");
    }

    if(!con->isValid())
    {
        con->reconnect();
    }

    return con;
}
