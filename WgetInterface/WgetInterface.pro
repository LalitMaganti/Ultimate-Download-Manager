##-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T16:54:13
#
#-------------------------------------------------

TARGET = wgetinterface
TEMPLATE = lib

DEFINES += WGETINTERFACE_LIBRARY

SOURCES += downloadfile.cpp \
           wgetprocess.cpp

HEADERS += downloadfile.h \
           wgetprocess.h

!windows:QMAKE_CXXFLAGS += -std=c++0x
windows:CONFIG += static
else:CONFIG += static

unix {
    CONFIG(debug, debug|release):CONFIG += shared
    target.path = /usr/lib
    INSTALLS += target
}
