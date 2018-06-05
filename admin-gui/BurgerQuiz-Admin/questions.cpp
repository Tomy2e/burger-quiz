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
