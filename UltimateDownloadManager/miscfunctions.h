#ifndef MISCSTUFF_H
#define MISCSTUFF_H

#include <QMainWindow>
#include <QDir>
#include <QString>
#include <QSettings>

#include "downloadfile.h"
#include "ui_mainwindow.h"

class MiscFunctions
{
public:
    inline static void connectWgetAndMainWindow(const DownloadFile *wp, QMainWindow *mw, Ui::MainWindow *ui)
    {
        QObject::connect(wp, SIGNAL(lengthChanged(WgetProcess *const)), ui->tableWidget, SLOT(setFileSize(WgetProcess* const)));
        QObject::connect(wp, SIGNAL(statusChanged(WgetProcess *const)), mw, SLOT(setStatus(WgetProcess *const)));
        QObject::connect(wp, SIGNAL(progressChanged(WgetProcess *const)), ui->tableWidget, SLOT(setProgress(WgetProcess* const)));
        QObject::connect(wp, SIGNAL(speedChanged(WgetProcess* const)), ui->tableWidget, SLOT(setSpeed(WgetProcess* const)));
        QObject::connect(wp, SIGNAL(timeChanged(WgetProcess* const)), ui->tableWidget, SLOT(setTime(WgetProcess* const)));
        QObject::connect(wp, SIGNAL(outputChanged(WgetProcess*const)), ui->tableWidget, SLOT(setOutput(WgetProcess* const)));
    }

    inline static void stopButtonChange(bool enable, Ui::MainWindow *ui)
    {
        ui->pushButton_2->setEnabled(enable);
        ui->btnStartPause->setEnabled(enable);
        ui->btnDelete->setEnabled(!enable);
        ui->btnRestart->setEnabled(enable);
    }

    inline static QString getOutDirectory()
    {
        QSettings settings;
        settings.setPath(QSettings::IniFormat, QSettings::UserScope, "settings.ini");
        return QDir::toNativeSeparators(settings.value("download/savelocation", QDir::homePath()).toString());
    }
};

#endif // MISCSTUFF_H
