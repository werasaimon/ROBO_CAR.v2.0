#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T02:00:03
#
#-------------------------------------------------

QT += core gui network sensors



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteManagerForAndroid
TEMPLATE = app


LIBS += -lSDL2

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

