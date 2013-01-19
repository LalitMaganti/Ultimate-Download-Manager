#include "settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(width(), height());
    saveLocation = ::getOutDirectory();
    ui->lineEdit->setText(saveLocation);
}

Settings::~Settings() {
    delete ui;
}

void Settings::on_toolButton_clicked() {
    QString tempSave = QFileDialog::getExistingDirectory(this, "Open Directory", saveLocation, QFileDialog::ShowDirsOnly);
    if (!(tempSave == "")) {
        ui->lineEdit->setText(tempSave);
        saveLocation = ui->lineEdit->text();
    }
}

void Settings::on_buttonBox_accepted() {
    QSettings settings;
    settings.setPath(QSettings::IniFormat, QSettings::UserScope, "settings.ini");
    settings.setValue("download/savelocation", saveLocation);
    settings.sync();
}
