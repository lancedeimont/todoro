#ifndef PSUBMIT_H
#define PSUBMIT_H

#include <QDialog>

namespace Ui {
class pSubmit;
}

class pSubmit : public QDialog
{
    Q_OBJECT

public:
    explicit pSubmit(QWidget *parent = 0);
    int getStarsNumber();
    QString getMessage();
    ~pSubmit();

private slots:
    void on_star3_clicked();

    void on_star1_clicked();

    void on_star4_clicked();

    void on_star5_clicked();

    void on_star2_clicked();

    void on_btnSave_clicked();

private:
    Ui::pSubmit *ui;
    void redrawStars(int n);
    void setStateStar(QPushButton *button, bool avtivated);

};

#endif // PSUBMIT_H
