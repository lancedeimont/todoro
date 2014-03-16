#-------------------------------------------------
#
# Project created by QtCreator 2012-09-23T18:35:33
#
#-------------------------------------------------

QT       += core gui sql
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
    frmPreferences.cpp \
    frmoptions.cpp

HEADERS  += \
    frmMain.h \
    todorofrm.h \
    centity.h \
    cconection.h \
    databasesqlite.h \
    misc.h \
    psubmit.h \
    frmPreferences.h \
    frmoptions.h

FORMS    += \
    frmMain.ui \
    todorofrm.ui \
    psubmit.ui \
    frmPreferences.ui \
    frmpreferences.ui \
    frmoptions.ui

RESOURCES += \
    resources/resources.qrc
