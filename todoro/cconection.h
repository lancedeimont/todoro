#ifndef CCONECTION_H
#define CCONECTION_H
//#include <QtSql/QSqlDatabase>
#include <QString>
//#include <Q

class cConection
{
public:
    cConection();
    int startDB();
private:
    QString conectionString;
//    QSqlDatabase db;
};

#endif // CCONECTION_H
