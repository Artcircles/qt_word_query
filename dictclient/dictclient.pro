#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T09:00:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictclient
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    dictdialog.cpp

HEADERS  += logindialog.h \
    dictdialog.h

FORMS    += logindialog.ui \
    dictdialog.ui

RESOURCES += \
    dictlogin.qrc
