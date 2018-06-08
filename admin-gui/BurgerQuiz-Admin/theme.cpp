#include "theme.h"

Theme::Theme()
{
    this->id = 0;
}

int Theme::getId()
{
    return this->id;
}

string Theme::getLibelle()
{
    return this->libelle;
}

string Theme::getPhoto()
{
    return this->photo;
}

void Theme::setId(int id)
{
    this->id = id;
}

void Theme::setLibelle(string libelle)
{
    this->libelle = libelle;
}

void Theme::setPhoto(string photo)
{
    this->photo = photo;
}

void Theme::updateLibelle(string libelle)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE themes SET libelle_theme = ? WHERE id_theme = ?");

        pstmt->setString(1, libelle);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setLibelle(libelle);

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

void Theme::updatePhoto(string photo)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE themes SET photo_theme = ? WHERE id_theme = ?");

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

void Theme::remove()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("DELETE FROM appartient_themes WHERE id_theme = ?");

        pstmt->setInt(1, this->getId());
        pstmt->executeUpdate();

        delete pstmt;

        pstmt = con->prepareStatement("DELETE FROM themes WHERE id_theme = ?");

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
