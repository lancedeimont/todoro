#include "frmpreferences.h"
#include "ui_frmpreferences.h"

FrmPreferences::FrmPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPreferences)
{
    ui->setupUi(this);
}

FrmPreferences::~FrmPreferences()
{
    delete ui;
}
