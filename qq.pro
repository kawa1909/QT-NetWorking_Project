#-------------------------------------------------
#
# Project created by QtCreator 2023-04-20T18:01:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qq
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    login.cpp

HEADERS  += widget.h \
    login.h

FORMS    += widget.ui \
    login.ui

RESOURCES += \
    res.qrc
CONFIG+=c++11
