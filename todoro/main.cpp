#include <QApplication>
#include "frmMain.h"
#include "databasesqlite.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "misc.h"

int main(int argc, char *argv[])
{
    databaseSqlite *db=new databaseSqlite();
    QSettings settings("mkProjs","todoro");



    QApplication a(argc, argv);

    frmMain *w;
    a.setQuitOnLastWindowClosed(false);
    QString pathdb=settings.value("pathdb","").toString();
    qDebug()<<"path "<<pathdb;
    if (!QFile::exists(pathdb))
    {
        //pathdb=QStandardPaths::standardLocations(QStandardPaths::DataLocation).back();
        pathdb=misc::filesPath();
        QDir().mkpath(pathdb+QDir::separator()+ "todoro"+QDir::separator());

        pathdb= pathdb+QDir::separator()+"todoro"+QDir::separator()+"todoro.db";
        db->createDatabase(w,&pathdb);
    }else
    {
        db->closeDatabase();
        db->connectDatabase(pathdb);
    }

    settings.setValue("pathdb",pathdb);
    settings.sync();

    w=new frmMain();
    w->show();
    
    return a.exec();
}
