#ifndef FRMOPTIONS_H
#define FRMOPTIONS_H

#include <QDialog>

namespace Ui {
class frmOptions;
}

class frmOptions : public QDialog
{
    Q_OBJECT

public:
    explicit frmOptions(QWidget *parent = 0);
    ~frmOptions();

private:
    Ui::frmOptions *ui;
};

#endif // FRMOPTIONS_H
