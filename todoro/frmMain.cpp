#include "frmMain.h"
#include "ui_frmMain.h"

#include "qfile.h"
#include <stdio.h>
//TODO: todayP is used and modificated in some functions, it couldn't be happen since its value is obtained from DB
frmMain::frmMain(QWidget *parent) :
    //QWidget(parent,Qt::Dialog),
    QMainWindow(parent,Qt::Dialog),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    ui->pom1->setVisible(false);
    ui->pom2->setVisible(false);
    ui->pom3->setVisible(false);
    ui->pom4->setVisible(false);
    ui->pom5->setVisible(false);

    settings=new QSettings("mkProjs","todoro",this);

    loadProjects();

    clockState=STOP;
    currentState=UNSTARTED;
    minuts=25;
    seconds=0;
    nPomodoros=settings->value("pomodoros").toInt();//0;
    ui->laPomodoros->setText(QString::number(nPomodoros));
    updatePomodoros();
    timer = new QTimer(this);
    timrlong=15;
    timrshort=5;
    timwork=25;
    tmpTimestart=QDateTime::currentDateTime();

    trayIcon=new QSystemTrayIcon(this);
    //changeState();//actualizar tiempo
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    trayIcon->setIcon(QIcon(":images/caquiIcon.png"));


    //connect(trayIcon,SIGNAL(messageClicked()),this,SLOT(showMe()));
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(showMe(QSystemTrayIcon::ActivationReason)));
    menuCont=new QMenu(this);
    actNextStage= menuCont->addAction("start next stage");
    QAction *actSkip=menuCont->addAction("skip state");

    QAction *actShowme=menuCont->addAction("Show mainform");
    menuCont->addSeparator();
    QAction *actAbout=menuCont->addAction("About Todoro");
    menuCont->addSeparator();
    QAction *actExit= menuCont->addAction("Exit");

    connect(actExit,SIGNAL(triggered()),this,SLOT(exitCalled()));
    connect(actAbout,SIGNAL(triggered()),this,SLOT(showAboutTodoro()));
    connect(actSkip,SIGNAL(triggered()),this,SLOT(skipState()));

    connect(actShowme,SIGNAL(triggered()),this,SLOT(showMainform()));
    connect(actNextStage,SIGNAL(triggered()),this,SLOT(on_pbStart_clicked()));
    connect(ui->actionNew_Project,SIGNAL(triggered()),this,SLOT(createProject()));
    connect(ui->cbProjects,SIGNAL(currentIndexChanged(int)),this,SLOT(projectChanged(int)));


    trayIcon->setContextMenu(menuCont);
    trayIcon->show();


    clossing=false;
}

frmMain::~frmMain()
{
    delete ui;
}
void frmMain::skipState()
{
    if (currentState==WORK && (QMessageBox::information(this,"Canceling pomodoro",
        "Are you sure you want not to consider this pomodoro and start the next state?, this pomodoro wont be saved",
               QMessageBox::Yes, QMessageBox::No)==QMessageBox::No))
        return;

    changeState(false);
    upgradeIcon();
    updateLights();
}
void frmMain::showAboutTodoro()
{
    QMessageBox::about(this,"Todoro app","Copyright: Miguel Angel Galarreta Valverde,\n Sao Paulo - 2012");
}
void frmMain::exitWithoutConfirm()
{
    clossing=true;
    settings->sync();
    this->close();
}
void frmMain::exitCalled()
{
    if (QMessageBox::information(this,"leaving Todoro",
                                 "Are you sure you want to close Todoros app?",QMessageBox::Yes,
                                 QMessageBox::No)==QMessageBox::Yes)
    {
        clossing=true;
        settings->sync();
        this->close();

    }
}

void frmMain::showMe(QSystemTrayIcon::ActivationReason reason)
{
    //std::cout<<"asdf"<<endl;
    //this->showMaximized();
    //QMessageBox::information(0, tr("Systray"),
                                  //tr("Testing"));
    //ui->label_2->setText("aasdfaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    //this->hide();
    //this->show();
}

void frmMain::showMainform()
{
    //this->activateWindow();
    this->show();
    this->setFocus(Qt::ActiveWindowFocusReason);
    //this->show();
    this->activateWindow();
    this->raise();
}

void frmMain::on_action_Exit_triggered()
{
    clossing=true;
    this->settings->sync();
    close();   
}

void frmMain::setMainButtonText(QString text)
{
    ui->pbStart->setText(text);
    actNextStage->setText(text);
}

void frmMain::updateLights()
{
    int currentPos=(todayP)%5;
    QVector<QPushButton*> poms;
    poms.push_back(ui->pom1);
    poms.push_back(ui->pom2);
    poms.push_back(ui->pom3);
    poms.push_back(ui->pom4);
    poms.push_back(ui->pom5);

    for (int i=0;i<5;i++)
    {
        QPushButton *tmpBut=(QPushButton*)poms[i];

        if (i!=4) tmpBut->setIcon(QIcon(":/images/green.png"));
        if (currentPos>i || (currentPos==i && currentState==WORK))
            tmpBut->setVisible(true);
        else
            tmpBut->setVisible(false);
    }
    if (currentPos!=4 && currentState==WORK)
        ((QPushButton*)poms[currentPos])->setIcon(QIcon(":/images/orange.png"));

}
void frmMain::closeEvent(QCloseEvent * event)
{
    if (!clossing)
    {
        this->hide();
        event->ignore();
    }else
    {
        event->accept();
        exit(0);
    }
}
void frmMain::changeState(bool save)
{
    seconds=0;
    if (currentState==WORK)
    {
        if ((todayP+1)%5==0)
        {
            currentState=RELAX_LONG;
            ui->laActualState->setText("Long break");
            minuts=timrlong;
        }
        else
        {
            currentState=RELAX_SHORT;
            ui->laActualState->setText("Short break");
            minuts=timrshort;
        }

        if(save)
            savePomodoro();
        setMainButtonText("Break");
        todayP+=1;

        nPomodoros+=1;
        settings->setValue("pomodoros",nPomodoros);
        ui->laTodayPomodoros->setText(QString::number(todayP));
        ui->laPomodoros->setText(QString::number(nPomodoros));
    }else
    {
        if (currentState==RELAX_SHORT)
        {
            if(save)
                saveBreak(timrshort);
        }
        else if (currentState==RELAX_LONG)
        {
            if(save)
                saveBreak(timrlong);
        }

        currentState=WORK;
        ui->laActualState->setText("Working");
        minuts=timwork;
        setMainButtonText("Pomodoro");
    }

    updateLights();
    updatePomodoros();
    /*//test
    minuts=0;
    seconds=6;
    //end test*/

    timer->stop();

}

void frmMain::upgradeIcon()
{

    //trayIcon->showMessage("title", "body", QSystemTrayIcon::MessageIcon());
    QPixmap* pixmap=new QPixmap(32,32);
    QColor* color;
    //QColor* fontColor=new QColor(Qt::black);
    switch(currentState)
    {
    case RELAX_SHORT: color=new QColor(20,240,20); break;//green
    case RELAX_LONG: color=new QColor(20,80,240); break;//blue
    case WORK: color=new QColor(240,10,10); break;//red
    default: break;
    }

    if (clockState==PAUSE)
    {
        color=new QColor(240,240,10);//yellow
        //fontColor=new QColor(Qt::white);
    }

    if (clockState==STOP)
    {
        trayIcon->setIcon(QIcon(":images/caquiIcon.png"));
    }else //either, if it is running or it is paused
    {
        pixmap->fill(color->toRgb());

        //draw text
        QString text;
        if (minuts==0) text=QString::number(seconds);
        else text=QString::number(minuts);

        QPainter *painter=new QPainter(pixmap);
        QFont *fuente=new QFont();
        fuente->setPixelSize(20);

        painter->setFont(*fuente);
        QRadialGradient gradiente(pixmap->rect().center(),30);
        gradiente.setColorAt(0,*color);
        gradiente.setColorAt(1,QColor(Qt::black));

        QBrush brush(gradiente);
        painter->fillRect(pixmap->rect(),brush);       
        painter->drawText(pixmap->rect(),text,QTextOption(Qt::AlignCenter));

        QIcon* icon=new QIcon(*pixmap);
        trayIcon->setIcon(*icon);

    }
}

void frmMain::updateTime()
{
    if (seconds==0)
    {
        seconds=60;
        if (minuts>0)
        {
            minuts-=1;
        }
        else
        {
            seconds=0;
            clockState=PAUSE;
            setMainButtonText("Continue");
            changeState();
            trayIcon->showMessage("State ended","you ended the actual process, make click in the continue button in the context menu");
        }
        upgradeIcon();
    }
    else
    {
        seconds-=1;
        if (minuts==0)
            upgradeIcon();
    }
    ui->laCurrentTime->setText(QString::number(minuts)+":"+QString::number(seconds));
}

void frmMain::on_pbStart_clicked()
{
    if (clockState==STOP)
    {
        changeState();
        tmpTimestart=QDateTime::currentDateTime();
    }
    if (clockState==STOP || clockState==PAUSE)
    {
        clockState=RUN;
        timer->start(1000);
        setMainButtonText("Pause");
    }   else
    {
        clockState=PAUSE;
        timer->stop();
        setMainButtonText("Continue");
    }
    upgradeIcon();
}

void frmMain::createProject()
{
    bool ok;
    QString name=QInputDialog::getText(this,"New project","Insert the name of the new project",QLineEdit::Normal,"",&ok);
    if (ok)
    {
        QSqlQuery q;
        q.prepare("INSERT INTO tproject VALUES(NULL, :name)");
        q.bindValue(":name",name);
        q.exec();
        loadProjects();
    }
}

void frmMain::loadProjects()
{
    QSqlQueryModel  *q=new QSqlQueryModel(this);
    q->setQuery("SELECT id,name FROM tproject;");
    while(q->canFetchMore())
        q->fetchMore();

    qDebug()<<"rows "<<q->rowCount();

    ui->cbProjects->setModel(q);
    ui->cbProjects->setModelColumn(1);
    ui->cbProjects->setCurrentIndex(0);
}

void frmMain::savePomodoro()
{
    QAbstractItemModel *model=ui->cbProjects->model();

    QSqlQuery q;
    q.prepare("INSERT INTO tpomodoro VALUES(NULL, :project, :description, :startTime, :endTime)");
    q.bindValue(":project",model->data(model->index(ui->cbProjects->currentIndex(),0)).toInt());
    bool ok;
    QString description=QInputDialog::getText(this,"Pomodoro","What did you do in this time?",QLineEdit::Normal,"",&ok);
    if (ok)
        q.bindValue(":description",description);
    else
        q.bindValue(":description"," ");
    q.bindValue(":startTime",tmpTimestart);
    q.bindValue(":endTime",QDateTime::currentDateTime());
    q.exec();
}
void frmMain::saveBreak(int mints)
{
    QAbstractItemModel *model=ui->cbProjects->model();

    QSqlQuery q;
    q.prepare("INSERT INTO tbreak VALUES(NULL, :project, :startTime, :endTime, :origMinuts)");
    q.bindValue(":project",model->data(model->index(ui->cbProjects->currentIndex(),0)).toInt());
    q.bindValue(":startTime",tmpTimestart);
    q.bindValue(":endTime",QDateTime::currentDateTime());
    q.bindValue(":origMinuts",mints);
    q.exec();
}
void frmMain::updatePomodoros()
{
    QSqlQuery  q;
    q.exec("SELECT count(*) FROM tpomodoro WHERE date(endTime)=date('now');");
    q.next();
    todayP=q.value(0).toInt();
    ui->laTodayPomodoros->setText(QString::number(todayP));

    QSqlQuery  q4;
    q4.exec("SELECT count(*) FROM tpomodoro;");
    q4.next();
    nPomodoros=q4.value(0).toInt();
    ui->laPomodoros->setText(QString::number(nPomodoros));

    QAbstractItemModel *model=ui->cbProjects->model();
    QSqlQuery q2("SELECT count(*) FROM tpomodoro WHERE project=:project;");
    int nproject=model->data(model->index(ui->cbProjects->currentIndex(),0)).toInt();
    q2.bindValue(":project",nproject);
    q2.exec();
    q2.next();
    ui->laPomodorosProject->setText(q2.value(0).toString());

    QSqlQuery q3("SELECT count(*) FROM tpomodoro WHERE project=:project and date(endTime)=date('now');");
    q3.bindValue(":project",nproject);
    q3.exec();
    q3.next();
    ui->laTodayPomodorosProject->setText(q3.value(0).toString());
}
void frmMain::projectChanged(int index)
{
    updatePomodoros();
}
