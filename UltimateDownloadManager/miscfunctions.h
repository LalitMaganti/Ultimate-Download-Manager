#ifndef MISCSTUFF_H
#define MISCSTUFF_H

#include <QMainWindow>
#include <QDir>
#include <QString>
#include <QSettings>

#include "ui_mainwindow.h"

static const int majorVersion = 1;
static const int minorVersion = 0;
static const int buildVersion = 0;

inline static void stopButtonChange(bool enable, Ui::MainWindow *ui) {
    ui->pushButton_2->setEnabled(enable);
    ui->btnStartPause->setEnabled(enable);
    ui->btnDelete->setEnabled(!enable);
    ui->btnRestart->setEnabled(enable);
}

inline static QString getOutDirectory() {
    QSettings settings;
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, "settings.ini");
    return QDir::toNativeSeparators(settings.value("download/savelocation", QDir::homePath()).toString());
}

#endif // MISCSTUFF_H
