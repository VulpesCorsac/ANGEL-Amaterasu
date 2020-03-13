#-------------------------------------------------
#
# Project created by QtCreator 2019-09-06T17:07:45
#
#-------------------------------------------------

QT      += core gui testlib

QT.testlib.CONFIG -= console
CONFIG -= console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Amaterasu
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG  += c++11

SOURCES += main.cpp \
           Amaterasu.cpp

HEADERS += Amaterasu.h

FORMS   += Amaterasu.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
