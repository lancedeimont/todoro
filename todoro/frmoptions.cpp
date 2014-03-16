#include "frmoptions.h"
#include "ui_frmoptions.h"

frmOptions::frmOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmOptions)
{
    ui->setupUi(this);
}

frmOptions::~frmOptions()
{
    delete ui;
}
