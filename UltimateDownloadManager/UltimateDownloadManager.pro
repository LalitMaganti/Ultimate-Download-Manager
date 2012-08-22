#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T16:56:20
#
#-------------------------------------------------

QT       += core gui widgets dialogheader

TARGET = UltimateDownloadManager
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           dialogsource/adddialog.cpp \
           detailstab.cpp \
           dialogsource/settings.cpp \
           dialogsource/aboutdialog.cpp \
           dialogsource/redownloaddialog.cpp

HEADERS  += mainwindow.h \
            mainwindow.h \
            dialogheader/adddialog.h \
            detailstab.h \
            downloadtabwidget.h \
            dialogheader/settings.h \
            dialogheader/aboutdialog.h \
            dialogheader/redownloaddialog.h \
            miscstuff.h

FORMS    += mainwindow.ui \
            dialogui/adddialog.ui \
            dialogui/settings.ui \
            dialogui/aboutdialog.ui \
            dialogui/redownloaddialog.ui

!windows:QMAKE_CXXFLAGS += -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/release -lWgetInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/debug -lWgetInterface
else:unix:!symbian: LIBS += -L$$OUT_PWD/../WgetInterface/ -lWgetInterface


windows:RC_FILE = images/icon.rc

INCLUDEPATH += $$PWD/../WgetInterface
DEPENDPATH += $$PWD/../WgetInterface

unix:!symbian {
    target.path = /usr/bin
    INSTALLS += target
}

OTHER_FILES += \
    images/UDM.ico \
    images/UDM2.ico \
    images/UDM.png \
    images/UDM2.png \
    images/icon.rc
