#ifndef MISCSTUFF_H
#define MISCSTUFF_H

#include <QMainWindow>
#include <QDir>
#include <QString>

#include "wgetprocess.h"
#include "ui_mainwindow.h"

static const int majorVersion = 0;
static const int minorVersion = 8;
static const int buildVersion = 6;
static const QString homedir = QDir::toNativeSeparators(QDir::homePath());

class MiscFunctions
{
public:
    inline static void connectWgetAndMainWindow(const WgetProcess *wp, QMainWindow *mw)
    {
        QObject::connect(wp, SIGNAL(lengthChanged(WgetProgressObject *const)), mw, SLOT(setLength(WgetProgressObject* const)));
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
};

#endif // MISCSTUFF_H
