#include "psubmit.h"
#include "ui_psubmit.h"

int currentStars=3;

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

void pSubmit::setStateStar(QPushButton *button, bool activated)
{
    if (activated)
    {
        button->setIcon(QIcon(":images/star.png"));
    }else
    {
        button->setIcon(QIcon(":images/stargray.png"));
    }
}

void pSubmit::redrawStars(int n)
{
    QVector<QPushButton*> stars;
    stars << ui->star1 << ui->star2 << ui->star3 << ui->star4 << ui->star5;
    for (int i=0; i<5; i++)
    {
        setStateStar(stars.at(i), i < n);
    }
}

void pSubmit::on_star3_clicked()
{
    redrawStars(3);
    currentStars=3;
}

void pSubmit::on_star1_clicked()
{
    redrawStars(1);
    currentStars=1;
}

void pSubmit::on_star4_clicked()
{
    redrawStars(4);
    currentStars=4;
}

void pSubmit::on_star5_clicked()
{
    redrawStars(5);
    currentStars=5;
}

void pSubmit::on_star2_clicked()
{
    redrawStars(2);
    currentStars=2;
}

int pSubmit::getStarsNumber()
{
    return currentStars;
}

QString pSubmit::getMessage()
{
    return ui->txtMade->text();
}

void pSubmit::on_btnSave_clicked()
{
    this->close();
}
