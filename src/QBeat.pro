#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T14:07:48
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBeat
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    filehandler.cpp \
    songinfo.cpp \
    sheet.cpp \
    bar.cpp \
    beat.cpp \
    fallletter.cpp \
    explosion.cpp \
    skinmanager.cpp

HEADERS  += widget.h \
    filehandler.h \
    songinfo.h \
    sheet.h \
    bar.h \
    beat.h \
    fallletter.h \
    explosion.h \
    mmath.h \
    skinmanager.h

FORMS    += widget.ui

RESOURCES +=
