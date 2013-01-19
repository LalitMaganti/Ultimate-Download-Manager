#ifndef MISCSTUFF_H
#define MISCSTUFF_H

#include <QMainWindow>
#include <QDir>
#include <QString>
#include <QSettings>

#include "downloadfile.h"
#include "ui_mainwindow.h"

class MiscFunctions : QObject {
    Q_OBJECT

public:
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
};

#endif // MISCSTUFF_H
