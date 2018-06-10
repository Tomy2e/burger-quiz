#include "user.h"

User::User()
{
    this->id = 0;
}

int User::getId()
{
    return this->id;
}

string User::getUsername()
{
    return this->username;
}

string User::getPassword()
{
    return this->password;
}

int User::getAge()
{
    return this->age;
}

string User::getEmail()
{
    return this->email;
}

string User::getPhoto()
{
    return this->photo;
}

void User::setId(int id)
{
    this->id = id;
}

void User::setUsername(string username)
{
    this->username = username;
}

void User::setPassword(string password, bool hashed)
{
    if(!hashed)
    {
        password = "nothashed:" + password;
    }

    this->password = password;
}

void User::setAge(int age)
{
    this->age = age;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPhoto(string photo)
{
    this->photo = photo;
}

void User::updatePassword(string password)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE utilisateurs SET password_utilisateur = ? WHERE id_utilisateur = ?");

        this->setPassword(password, false);

        pstmt->setString(1, this->getPassword());
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

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

void User::updateAge(int age)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE utilisateurs SET age_utilisateur = ? WHERE id_utilisateur = ?");

        pstmt->setInt(1, age);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setAge(age);

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

void User::updateEmail(string email)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE utilisateurs SET email_utilisateur = ? WHERE id_utilisateur = ?");

        pstmt->setString(1, email);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setEmail(email);

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

void User::updatePhoto(string photo)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE utilisateurs SET photo_utilisateur = ? WHERE id_utilisateur = ?");

        pstmt->setString(1, photo);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setPhoto(photo);

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

void User::remove()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("DELETE FROM possede_scores WHERE id_utilisateur = ?");

        pstmt->setInt(1, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        pstmt = con->prepareStatement("DELETE FROM utilisateurs WHERE id_utilisateur = ?");

        pstmt->setInt(1, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

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
