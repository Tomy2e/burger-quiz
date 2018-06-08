#include "proposition.h"

Proposition::Proposition()
{
    this->id = 0;
}

int Proposition::getId()
{
    return this->id;
}

string Proposition::getLibelleProposition()
{
    return this->libelleProposition;
}

int Proposition::getReponseProposition()
{
    return this->reponseProposition;
}

int Proposition::getActive()
{
    return this->active;
}

void Proposition::setId(int id)
{
    this->id = id;
}

void Proposition::setLibelleProposition(string libelleProposition)
{
    this->libelleProposition = libelleProposition;
}

void Proposition::setReponseProposition(int reponseProposition)
{
    this->reponseProposition = reponseProposition;
}

void Proposition::setActive(int active)
{
    this->active = active;
}

void Proposition::disable()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE propositions SET active_proposition = ? WHERE id_proposition = ?");

        pstmt->setInt(1, 0);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->active = 0;

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

void Proposition::remove()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("DELETE FROM propositions WHERE id_proposition = ?");

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

void Proposition::updateLibelleProposition(string libelleProposition)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE propositions SET libelle_proposition = ? WHERE id_proposition = ?");

        pstmt->setString(1, libelleProposition);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setLibelleProposition(libelleProposition);

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

void Proposition::updateReponseProposition(int reponseProposition)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE propositions SET reponse_proposition = ? WHERE id_proposition = ?");

        pstmt->setInt(1, reponseProposition);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->setReponseProposition(reponseProposition);

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

void Proposition::enable()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE propositions SET active_proposition = ? WHERE id_proposition = ?");

        pstmt->setInt(1, 1);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->active = 1;

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
