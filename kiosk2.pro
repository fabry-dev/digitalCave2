#-------------------------------------------------
#
# Project created by QtCreator 2018-09-28T08:37:50
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia
QT += multimediawidgets
TARGET = kiosk2
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG += mpv

SOURCES += main.cpp \
    mpvwidget.cpp \
    alphaVideoPlayer.cpp \
    touchscreen.cpp \
    ledscreen.cpp \
    rotativebutton.cpp \
    horizontalbutton.cpp \
    udplistener.cpp \
    yearbuttons.cpp


HEADERS  += \
    mpvwidget.h \
    alphaVideoPlayer \
    alphaVideoPlayer.h \
    touchscreen.h \
    ledscreen.h \
    rotativebutton.h \
    horizontalbutton.h \
    udplistener.h \
    yearbuttons.h


FORMS    +=


LIBS+=
