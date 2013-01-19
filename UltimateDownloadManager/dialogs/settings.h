#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

#include "miscfunctions.h"
#include "ui_settings.h"

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    
private slots:
    void on_toolButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::Settings *ui = nullptr;
    QString saveLocation;
};

#endif // SETTINGS_H