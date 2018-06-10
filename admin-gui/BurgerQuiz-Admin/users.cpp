#include "users.h"

Users::Users()
{

}

QVector<User> Users::fetchUsers()
{
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::Connection *con = DbConnection::getConnection();
        QVector<User> users;

        stmt = con->createStatement();

        res = stmt->executeQuery("SELECT * FROM utilisateurs");

        while (res->next()) {
            User the_user;
            the_user.setId(res->getInt("id_utilisateur"));
            the_user.setUsername(res->getString("nom_utilisateur"));
            the_user.setPassword(res->getString("password_utilisateur"));
            the_user.setAge(res->getInt("age_utilisateur"));
            the_user.setEmail(res->getString("email_utilisateur"));
            the_user.setPhoto(res->getString("photo_utilisateur"));

            users.push_back(the_user);
        }

        return users;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        QMessageBox msgBox;
        msgBox.setText("Une erreur SQL s'est produite !");
        msgBox.exec();

        QVector<User> emptyVec;
        return emptyVec;
      } catch(string e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(e));
        msgBox.exec();

        QVector<User> emptyVec;
        return emptyVec;
    }
}

void Users::createUser(User &user)
{
    try {

        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("INSERT INTO utilisateurs(nom_utilisateur, password_utilisateur, age_utilisateur, email_utilisateur, photo_utilisateur) VALUES (?, ?, ?, ?, ?)");

        pstmt->setString(1, user.getUsername());
        pstmt->setString(2, user.getPassword());
        pstmt->setInt(3, user.getAge());
        pstmt->setString(4, user.getEmail());
        pstmt->setString(5, user.getPhoto());

        pstmt->executeUpdate();

        delete pstmt;

        // On récupère le last insert id

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT @@identity AS id");
        res->next();
        user.setId(res->getInt("id"));

        delete stmt;
        delete res;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        QMessageBox msgBox;
        msgBox.setText("Une erreur SQL s'est produite !");
        msgBox.exec();
    } catch(string e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(e));
        msgBox.exec();
    }
}
