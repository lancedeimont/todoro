#include "cconection.h"

cConection::cConection()
{
    conectionString="";
    //db=QSqlDatabase::addDatabase("QMYSQL");
    //db.setDatabaseName("todorodb");

    //if (!db.open())
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("acidalia");
    db.setDatabaseName("customdb");
    db.setUserName("mojito");
    db.setPassword("J0a1m8");
    bool ok = db.open();*/
}
int cConection::startDB()
{
    //return db.open();
    return 0;
}
