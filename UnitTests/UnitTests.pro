#-------------------------------------------------
#
# Project created by QtCreator 2012-08-20T12:28:19
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unitteststest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unitteststest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../WgetInterface
DEPENDPATH += $$PWD/../WgetInterface

INCLUDEPATH += $$PWD/../UltimateDownloadManager
DEPENDPATH += $$PWD/../UltimateDownloadManager

!windows:QMAKE_CXXFLAGS += -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/release/ -lWgetInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/debug/ -lWgetInterface
else:unix:!symbian: LIBS += -L$$OUT_PWD/../WgetInterface/ -lWgetInterface
