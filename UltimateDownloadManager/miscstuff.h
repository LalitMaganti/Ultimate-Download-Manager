#ifndef MISCSTUFF_H
#define MISCSTUFF_H

#include <QMainWindow>
#include <QDir>
#include <QString>
#include <QSettings>

#include "downloadfile.h"
#include "ui_mainwindow.h"

static const int majorVersion = 0;
static const int minorVersion = 8;
static const int buildVersion = 10;

enum tableRow
{
    URL = 0,
    FileSize = 1,
    Status = 2,
    Progress = 3,
    Speed = 4,
    Time = 5,
    Output = 6
};

class MiscFunctions
{
public:
    inline static void connectWgetAndMainWindow(const DownloadFile *wp, QMainWindow *mw)
    {
        QObject::connect(wp, SIGNAL(lengthChanged(WgetProgressObject *const)), mw, SLOT(setFileSize(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(wgetStatusChanged(WgetProgressObject *const)), mw, SLOT(setStatus(WgetProgressObject *const)));
        QObject::connect(wp, SIGNAL(progressChanged(WgetProgressObject *const)), mw, SLOT(setProgress(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(speedChanged(WgetProgressObject* const)), mw, SLOT(setSpeed(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(timeChanged(WgetProgressObject* const)), mw, SLOT(setTime(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(outputChanged(WgetProgressObject*const)), mw, SLOT(setOutput(WgetProgressObject* const)));
    }
    inline static void stopButtonChange(bool enable, Ui::MainWindow *ui)
    {
        ui->pushButton_2->setEnabled(enable);
        ui->btnStartPause->setEnabled(enable);
        ui->btnDelete->setEnabled(!enable);
        ui->btnRestart->setEnabled(!enable);
    }
    inline static QString getOutDirectory()
    {
        QSettings settings;
        settings.setPath(QSettings::IniFormat, QSettings::UserScope, "settings.ini");
        return QDir::toNativeSeparators(settings.value("download/savelocation", QDir::homePath()).toString());
    }
};

#endif // MISCSTUFF_H
