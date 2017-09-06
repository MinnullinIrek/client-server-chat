QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = fuck
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    sqlite3.c

HEADERS += \
    server.h \
    sqlite3.h \
    sqlite3ext.h
