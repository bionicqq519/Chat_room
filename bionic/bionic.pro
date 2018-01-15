#-------------------------------------------------
#
# Project created by QtCreator 2010-11-23T22:24:18
#
#-------------------------------------------------

QT += widgets
QT       += core gui
QT += network
TARGET = bionic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    msn_chat.cpp \
    chat_used.cpp \
    exception.cpp \
    initial.cpp \
    parse.cpp \
    search.cpp \
    search_used.cpp \
    search_virtual.cpp \
    client.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    class.h \
    msn_chat.h \
    chat_used.h \
    exception.h \
    initial.h \
    parse.h \
    search.h \
    search_used.h \
    search_virtual.h \
    client.h \
    server.h

FORMS    += mainwindow.ui
