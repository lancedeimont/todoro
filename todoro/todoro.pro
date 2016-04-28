#-------------------------------------------------
#
# Project created by QtCreator 2012-09-23T18:35:33
#
#-------------------------------------------------

QT       += core gui sql multimedia widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = todoro
TEMPLATE = app


SOURCES += main.cpp\
    todorofrm.cpp \
    frmMain.cpp \
    centity.cpp \
    cconection.cpp \
    databasesqlite.cpp \
    misc.cpp \
    psubmit.cpp \
    frmoptions.cpp

HEADERS  += \
    frmMain.h \
    todorofrm.h \
    centity.h \
    cconection.h \
    databasesqlite.h \
    misc.h \
    psubmit.h \
    frmoptions.h

FORMS    += \
    frmMain.ui \
    todorofrm.ui \
    psubmit.ui \
    frmoptions.ui

RESOURCES += \
    resources/resources.qrc
