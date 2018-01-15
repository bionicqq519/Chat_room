#-------------------------------------------------
#
# Project created by QtCreator 2010-12-23T19:14:55
#
#-------------------------------------------------

QT       += testlib
QT += network
TARGET = tst_bionic_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_bionic_test.cpp \
    ../search_virtual.cpp \
    ../search_used.cpp \
    ../search.cpp \
    ../parse.cpp \
    ../msn_chat.cpp \
    ../initial.cpp \
    ../exception.cpp \
    ../chat_used.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../search_virtual.h \
    ../search_used.h \
    ../search.h \
    ../parse.h \
    ../msn_chat.h \
    ../initial.h \
    ../exception.h \
    ../chat_used.h \
    ../class.h
