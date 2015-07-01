#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T11:10:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkTesterGUI
TEMPLATE = app
RESOURCES = resources.qrc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    networktester.h

FORMS    += mainwindow.ui
LIBS += -lcurl
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
