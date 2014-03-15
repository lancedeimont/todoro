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
    ~pSubmit();

private:
    Ui::pSubmit *ui;
};

#endif // PSUBMIT_H
