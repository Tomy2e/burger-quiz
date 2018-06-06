#include "question.h"

Question::Question()
{

}


int Question::getId()
{
    return this->id;
}

int Question::getActive()
{
    return this->active;
}

string Question::getLibelle1()
{
    return this->libelle1;
}

string Question::getLibelle2()
{
    return this->libelle2;
}

void Question::setId(int id)
{
    this->id = id;
}

void Question::setActive(int active)
{
    this->active = active;
}

void Question::setLibelle1(string libelle1)
{
    this->libelle1 = libelle1;
}

void Question::setLibelle2(string libelle2)
{
    this->libelle2 = libelle2;
}

void Question::enable()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE questions SET active_question = ? WHERE id_question = ?");

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

void Question::disable()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE questions SET active_question = ? WHERE id_question = ?");

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

