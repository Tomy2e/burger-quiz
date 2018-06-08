#include "question.h"

Question::Question()
{
    this->id = 0;
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

void Question::remove()
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("DELETE FROM appartient_parties WHERE id_question = ?");

        pstmt->setInt(1, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        pstmt = con->prepareStatement("DELETE FROM appartient_themes WHERE id_question = ?");

        pstmt->setInt(1, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        pstmt = con->prepareStatement("DELETE FROM propositions WHERE id_question = ?");

        pstmt->setInt(1, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        pstmt = con->prepareStatement("DELETE FROM questions WHERE id_question = ?");

        pstmt->setInt(1, this->getId());

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

void Question::updateLibelle1(string libelle1)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE questions SET libelle1 = ? WHERE id_question = ?");

        pstmt->setString(1, libelle1);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->libelle1 = libelle1;

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

void Question::updateLibelle2(string libelle2)
{
    try {
        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("UPDATE questions SET libelle2 = ? WHERE id_question = ?");

        pstmt->setString(1, libelle2);
        pstmt->setInt(2, this->getId());

        pstmt->executeUpdate();

        delete pstmt;

        this->libelle2 = libelle2;

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

QVector<Proposition> Question::getPropositions()
{
    try {
        sql::ResultSet *res;
        sql::Connection *con = DbConnection::getConnection();
        sql::PreparedStatement *pstmt;
        QVector<Proposition> propositions;

        pstmt = con->prepareStatement("SELECT * FROM propositions WHERE id_question = ?");
        pstmt->setInt(1, this->id);

        res = pstmt->executeQuery();


        while (res->next()) {
            Proposition the_proposition;
            the_proposition.setId(res->getInt("id_proposition"));
            the_proposition.setActive(res->getInt("active_proposition"));
            the_proposition.setLibelleProposition(res->getString("libelle_proposition"));
            the_proposition.setReponseProposition(res->getInt("reponse_proposition"));

            propositions.push_back(the_proposition);
        }

        delete pstmt;
        delete res;

        return propositions;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        QMessageBox msgBox;
        msgBox.setText("Une erreur SQL s'est produite !");
        msgBox.exec();

        QVector<Proposition> emptyVec;
        return emptyVec;
      } catch(string e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(e));
        msgBox.exec();

        QVector<Proposition> emptyVec;
        return emptyVec;
    }
}

void Question::ajouterProposition(Proposition &proposition)
{
    try {

        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("INSERT INTO propositions(libelle_proposition, reponse_proposition, active_proposition, id_question) VALUES (?, ?, ?, ?)");

        pstmt->setString(1, proposition.getLibelleProposition());
        pstmt->setInt(2, proposition.getReponseProposition());
        pstmt->setInt(3, proposition.getActive());
        pstmt->setInt(4, this->id);

        pstmt->executeUpdate();

        delete pstmt;

        // On récupère le last insert id

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT @@identity AS id");
        res->next();
        proposition.setId(res->getInt("id"));

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
