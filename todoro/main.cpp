#include <QtGui/QApplication>
#include "frmMain.h"
#include "databasesqlite.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>

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
        pathdb=QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        QDir().mkpath(pathdb+"todoro/");

        pathdb= pathdb+"todoro/todoro.db";
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
