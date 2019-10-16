#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T10:15:46
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictserver
TEMPLATE = app


SOURCES += main.cpp \
    tcpserver.cpp \
    tcpsocket.cpp

HEADERS  += \
    tcpserver.h \
    tcpsocket.h
