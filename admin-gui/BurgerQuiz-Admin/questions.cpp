#include "questions.h"

Questions::Questions()
{
}

QVector<Question> Questions::fetchQuestions()
{
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::Connection *con = DbConnection::getConnection();
        QVector<Question> questions;

        stmt = con->createStatement();

        res = stmt->executeQuery("SELECT * FROM questions");

        while (res->next()) {
            Question the_question;
            the_question.setId(res->getInt("id_question"));
            the_question.setActive(res->getInt("active_question"));
            the_question.setLibelle1(res->getString("libelle1"));
            the_question.setLibelle2(res->getString("libelle2"));
            questions.push_back(the_question);
        }

        return questions;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        QMessageBox msgBox;
        msgBox.setText("Une erreur SQL s'est produite !");
        msgBox.exec();

        QVector<Question> emptyVec;
        return emptyVec;
      } catch(string e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(e));
        msgBox.exec();

        QVector<Question> emptyVec;
        return emptyVec;
    }
}

void Questions::createQuestion(Question &question)
{
    try {

        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("INSERT INTO questions(libelle1, libelle2, active_question) VALUES (?, ?, ?)");

        pstmt->setString(1, question.getLibelle1());
        pstmt->setString(2, question.getLibelle2());
        pstmt->setInt(3, question.getActive());

        pstmt->executeUpdate();

        delete pstmt;

        // On récupère le last insert id

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT @@identity AS id");
        res->next();
        question.setId(res->getInt("id"));

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
