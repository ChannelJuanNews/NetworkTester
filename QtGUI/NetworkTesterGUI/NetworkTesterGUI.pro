#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T11:10:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = NetworkTesterGUI
TEMPLATE  = app
RESOURCES = resources.qrc

SOURCES   += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    networktester.h

FORMS    += mainwindow.ui

//LIBS += `mysql_config --cflags`
//LIBS += `mysql_config --libs`
//LIBS += -lmysqlcppconn
LIBS += -lcurl

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -stdlib=libc++

INCLUDEPATH += /usr/local/include/
//INCLUDEPATH += /usr/local/mysql/include
//INCLUDEPATH += /usr/local/include/cppconn
//INCLUDEPATH += /usr/local/mysql/lib

CONFIG += c++11
