#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T16:54:13
#
#-------------------------------------------------

TARGET = WgetInterface
TEMPLATE = lib
CONFIG += staticlib

DEFINES += WGETINTERFACE_LIBRARY

SOURCES += downloadfile.cpp \
    wgetprocess.cpp

HEADERS += downloadfile.h \
    wgetprocess.h \
    wgetprogressobject.h

gcc:QMAKE_CXXFLAGS += -std=c++0x

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}
