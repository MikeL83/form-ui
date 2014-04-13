#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T20:26:07
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FormUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logic.cpp

HEADERS  += mainwindow.h \
    logic.h

FORMS    += mainwindow.ui
