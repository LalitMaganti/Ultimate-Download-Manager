#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T16:56:20
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = UltimateDownloadManager
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           adddialog.cpp \
           detailstab.cpp \
           settings.cpp \
           aboutdialog.cpp \
    redownloaddialog.cpp

HEADERS  += mainwindow.h \
            mainwindow.h \
            adddialog.h \
            detailstab.h \
            downloadtabwidget.h \
            settings.h \
            aboutdialog.h \
    redownloaddialog.h \
    miscstuff.h

FORMS    += mainwindow.ui \
            adddialog.ui \
            settings.ui \
            aboutdialog.ui \
    redownloaddialog.ui

!windows:QMAKE_CXXFLAGS += -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/release/ -lWgetInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../WgetInterface/debug/ -lWgetInterface
else:unix:!symbian: LIBS += -L$$OUT_PWD/../WgetInterface/ -lWgetInterface

INCLUDEPATH += $$PWD/../WgetInterface
DEPENDPATH += $$PWD/../WgetInterface

unix:!symbian {
    target.path = /usr/bin
    INSTALLS += target
}

OTHER_FILES += \
    Images/UDM.ico \
    Images/UDM2.ico \
    Images/UDM.png \
    Images/UDM2.png
