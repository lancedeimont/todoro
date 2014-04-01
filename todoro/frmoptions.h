#ifndef FRMOPTIONS_H
#define FRMOPTIONS_H

#include <QDialog>
#include <QFile>
#include <QSettings>
#include "databasesqlite.h"
#include <QFileInfo>

namespace Ui {
class frmOptions;
}

class frmOptions : public QDialog
{
    Q_OBJECT

public:
    explicit frmOptions(QSettings *settings, QWidget *parent = 0);
    ~frmOptions();

private slots:
    void on_btnBackup_clicked();

    void on_btnRemoveDatabase_clicked();

private:
    Ui::frmOptions *ui;
    QSettings *settings;
};

#endif // FRMOPTIONS_H
