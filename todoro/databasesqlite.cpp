#include "databasesqlite.h"

databaseSqlite::databaseSqlite()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
}
bool databaseSqlite::createDatabase(QWidget * parent,QString *path)
{

    if (!path)
    {//show dialog and get a newPath
        qDebug()<<"no hay path"<<*path;
        QString newPath = QFileDialog::getSaveFileName(parent,
                QObject::tr("Create Database"), misc::filesPath(),
                "SQLite3 (*.sqlite3)", 0, QFileDialog::DontConfirmOverwrite);

        if (newPath.isEmpty())
            return false;
        path=&newPath;
    }

    //create a copy of the database in the *path
    QString oldDb = QSqlDatabase::database().databaseName();
    closeDatabase();

    if (QFile::exists(*path)) {
        QMessageBox::critical(0, QObject::tr("Database Error"), QObject::tr("Database exists already."));

        if (!oldDb.isEmpty())
            connectDatabase(oldDb);

        return false;
    }

    if(!QFile::copy(":/sqlite/todoro.db",*path))
    {
        QMessageBox::critical(parent,"Error",QString("Copying database to '%1'' failed").arg(*path));
        if (!oldDb.isEmpty())
            connectDatabase(oldDb);
        return false;
    }

    QFile::setPermissions(*path, QFile::ReadUser | QFile::WriteUser | QFile::WriteOwner | QFile::ReadOwner);

    if (!connectDatabase(*path)) {
        if (!oldDb.isEmpty())
            connectDatabase(oldDb);
        return false;
    }
    else {
        return true;
    }


}

bool databaseSqlite::openDatabase(QWidget *parent)
{
    QString oldPath = QFileInfo(QSqlDatabase::database().databaseName()).absolutePath();

    QString path = QFileDialog::getOpenFileName(parent,
            "Open Database",
            (oldPath.isEmpty()) ? misc::filesPath() : oldPath,
            "SQLite3 (*.sqlite3)");

    if (path.isEmpty())
        return false;

    QString oldDb = QSqlDatabase::database().databaseName();
    closeDatabase();

    if(!connectDatabase(path)) {
        if (!oldDb.isEmpty())
             return connectDatabase(oldDb);
         return false;
    }

    return true;
}

bool databaseSqlite::connectDatabase(const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().driverText());
        return false;
    }
    else
        qDebug() << "DB open";

    return true;
}

void databaseSqlite::closeDatabase()
{
    if (!QSqlDatabase::connectionNames().isEmpty()) {
        QSqlDatabase::database().close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
}
