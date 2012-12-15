#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

#include "miscdeclarations.h"
#include "miscfunctions.h"
#include "ui_settings.h"

namespace Ui {
class Settings;
}

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
    Ui::Settings *ui;
    QString saveLocation;
};

#endif // SETTINGS_H
