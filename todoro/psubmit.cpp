#include "psubmit.h"
#include "ui_psubmit.h"

pSubmit::pSubmit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pSubmit)
{
    ui->setupUi(this);
}

pSubmit::~pSubmit()
{
    delete ui;
}
