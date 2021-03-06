#ifndef FRMPREFERENCES_H
#define FRMPREFERENCES_H

#include <QDialog>

namespace Ui {
class FrmPreferences;
}

class FrmPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPreferences(QWidget *parent = 0);
    ~FrmPreferences();

private slots:
    void on_btnRemoveDatabase_clicked();

private:
    Ui::FrmPreferences *ui;
};

#endif // FRMPREFERENCES_H
