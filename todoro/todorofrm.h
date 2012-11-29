#ifndef TODOROFRM_H
#define TODOROFRM_H

#include <QMainWindow>

namespace Ui {
class todoroFrm;
}

class todoroFrm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit todoroFrm(QWidget *parent = 0);
    ~todoroFrm();
    
private:
    Ui::todoroFrm *ui;
};

#endif // TODOROFRM_H
