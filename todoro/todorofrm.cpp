#include "todorofrm.h"
#include "ui_todorofrm.h"

todoroFrm::todoroFrm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::todoroFrm)
{
    ui->setupUi(this);
}

todoroFrm::~todoroFrm()
{
    delete ui;
}
