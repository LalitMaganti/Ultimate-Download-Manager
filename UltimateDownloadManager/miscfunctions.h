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
        QObject::connect(wp, SIGNAL(lengthChanged(WgetProgressObject *const)), ui->tableWidget, SLOT(setFileSize(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(wgetStatusChanged(WgetProgressObject *const)), mw, SLOT(setStatus(WgetProgressObject *const)));
        QObject::connect(wp, SIGNAL(progressChanged(WgetProgressObject *const)), ui->tableWidget, SLOT(setProgress(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(speedChanged(WgetProgressObject* const)), ui->tableWidget, SLOT(setSpeed(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(timeChanged(WgetProgressObject* const)), ui->tableWidget, SLOT(setTime(WgetProgressObject* const)));
        QObject::connect(wp, SIGNAL(outputChanged(WgetProgressObject*const)), ui->tableWidget, SLOT(setOutput(WgetProgressObject* const)));
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
