#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T18:36:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoClientUdp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videoclient.cpp

HEADERS  += mainwindow.h \
    videoclient.h

FORMS    += mainwindow.ui
