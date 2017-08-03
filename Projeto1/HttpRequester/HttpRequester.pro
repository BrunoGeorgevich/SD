QT += core network
QT -= gui

CONFIG += c++11

TARGET = HttpRequester
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    requester.cpp

HEADERS += \
    requester.h

DISTFILES += \
    Server/service.php
