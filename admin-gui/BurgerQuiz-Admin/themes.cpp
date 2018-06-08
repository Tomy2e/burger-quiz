#include "themes.h"

Themes::Themes()
{

}

QVector<Theme> Themes::fetchThemes()
{
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::Connection *con = DbConnection::getConnection();
        QVector<Theme> themes;

        stmt = con->createStatement();

        res = stmt->executeQuery("SELECT * FROM themes");

        while (res->next()) {
            Theme the_theme;
            the_theme.setId(res->getInt("id_theme"));
            the_theme.setLibelle(res->getString("libelle_theme"));
            the_theme.setPhoto(res->getString("photo_theme"));

            themes.push_back(the_theme);
        }

        return themes;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        QMessageBox msgBox;
        msgBox.setText("Une erreur SQL s'est produite !");
        msgBox.exec();

        QVector<Theme> emptyVec;
        return emptyVec;
      } catch(string e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(e));
        msgBox.exec();

        QVector<Theme> emptyVec;
        return emptyVec;
    }
}

void Themes::createTheme(Theme &theme)
{
    try {

        sql::PreparedStatement *pstmt;
        sql::Connection *con = DbConnection::getConnection();

        pstmt = con->prepareStatement("INSERT INTO themes(libelle_theme, photo_theme) VALUES (?, ?)");

        pstmt->setString(1, theme.getLibelle());
        pstmt->setString(2, theme.getPhoto());

        pstmt->executeUpdate();

        delete pstmt;

        // On récupère le last insert id

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT @@identity AS id");
        res->next();
        theme.setId(res->getInt("id"));

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
