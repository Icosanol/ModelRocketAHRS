#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T18:52:22
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialDownloader
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    serialdevice.cpp \
    serialexception.cpp

HEADERS  += MainWindow.h \
    serialdevice.h \
    serialexception.h

FORMS    += MainWindow.ui
