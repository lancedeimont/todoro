#include "frmoptions.h"
#include "ui_frmoptions.h"
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

frmOptions::frmOptions(QSettings *msettings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmOptions)
{
    ui->setupUi(this);
    this->settings = msettings;
}

frmOptions::~frmOptions()
{
    delete ui;
}

void frmOptions::on_btnBackup_clicked()
{
    QString pathdb=settings->value("pathdb","").toString();
    qDebug()<<"original "<<pathdb;
    int n=1;
    QString filename = QFileInfo(pathdb).fileName();
    QString filedir=QFileInfo(pathdb).path();
    databaseSqlite *db=new databaseSqlite();

    QString backupName = filedir+QDir::separator()+filename+"_"+QString::number(n);
    while(QFileInfo::exists(backupName))
    {
        n++;
        backupName = filedir+QDir::separator()+filename+"_"+QString::number(n);
    }

    db->copyDatabase(pathdb,backupName);
    qDebug()<<"namefile"<< filename<< "  dir "<<filedir<< "   backupname "<<backupName;

}

void frmOptions::on_btnRemoveDatabase_clicked()
{
    QString pathdb=settings->value("pathdb","").toString();
    databaseSqlite *db=new databaseSqlite();
    db->removeDatabase(pathdb);
    QMessageBox *msg=new QMessageBox(this);
    msg->setText("Database was removed from "+pathdb+ ", it is needed to RESTART the app to aply changes");
    msg->show();
            //show("Database was removed from "+pathdb);

}
