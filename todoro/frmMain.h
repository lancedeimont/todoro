#ifndef FRMMAIN_H
#define FRMMAIN_H
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QPainter>
#include <vector>
#include <QWidget>
#include <QMessageBox>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QInputDialog>
#include <QSettings>
#include <QMediaPlayer>
#include "misc.h"

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow//QWidget//
{
    Q_OBJECT
enum estados{
        WORK,RELAX_SHORT,RELAX_LONG,UNSTARTED
    };
enum clockStates{
    PAUSE,STOP,RUN
    };
public:
    explicit frmMain(QSettings *settings, QWidget *parent = 0);
    estados currentState;
    clockStates clockState;
    ~frmMain();

private slots:
    void on_action_Exit_triggered();
    void updateTime();
    void on_pbStart_clicked();
    void showMe(QSystemTrayIcon::ActivationReason reason);
    void showMainform();
    void exitCalled();
    void showAboutTodoro();
    void createProject();
    void projectChanged(int index);
    void exitWithoutConfirm();
    void skipState();

    void on_action_Preferences_triggered();

private:
    void closeEvent(QCloseEvent * event);
    void changeState(bool save=1);
    void activateCountTime();
    void updateLights();
    void writeCurrentState();
    void readCurrentState();
    void upgradeIcon();
    void setMainButtonText(QString text);
    void loadProjects();
    void savePomodoro();
    void saveBreak(int mints);
    void updatePomodoros();

    QTimer *timer;
    QMenu *menuCont;
    QAction *actNextStage;
    Ui::frmMain *ui;
    QSystemTrayIcon *trayIcon;
    QSettings *settings;
    QDateTime tmpTimestart;
    int minuts;
    int seconds;
    int todayP;
    int nPomodoros;
//const:
    int timrlong;
    int timrshort;
    int timwork;

    int mode = 0; //0 to normal, 1 test(all times are 0)

    bool clossing;
    void makeAlertEndState();
};
#endif // FRMMAIN_H
