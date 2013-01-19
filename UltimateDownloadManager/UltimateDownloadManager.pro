#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T16:56:20
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = ultimatedownloadmanager
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           uicomponents/detailstab.cpp \
           dialogs/adddialog.cpp \
           dialogs/settings.cpp \
           dialogs/aboutdialog.cpp \
           dialogs/redownloaddialog.cpp \
           uicomponents/udmtablewidget.cpp

HEADERS  += mainwindow.h \
            mainwindow.h \
            uicomponents/detailstab.h \
            uicomponents/downloadtabwidget.h \
            dialogs/adddialog.h \
            dialogs/settings.h \
            dialogs/aboutdialog.h \
            dialogs/redownloaddialog.h \
            uicomponents/udmtablewidget.h \
            miscfunctions.h

FORMS    += mainwindow.ui \
            dialogs/adddialog.ui \
            dialogs/settings.ui \
            dialogs/aboutdialog.ui \
            dialogs/redownloaddialog.ui

windows:RC_FILE = images/icon.rc
!windows:QMAKE_CXXFLAGS += -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/release -lwgetinterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/debug -lwgetinterface

unix {
    LIBS += -L$$OUT_PWD/../WgetInterface/ -lwgetinterface
    target.path = /usr/bin
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../WgetInterface
DEPENDPATH += $$PWD/../WgetInterface
INCLUDEPATH += $$PWD/dialogs
DEPENDPATH += $$PWD/dialogs
INCLUDEPATH += $$PWD/uicomponents
DEPENDPATH += $$PWD/uicomponents

OTHER_FILES += \
    images/UDM.ico \
    images/UDM2.ico \
    images/UDM.png \
    images/UDM2.png \
    images/icon.rc
