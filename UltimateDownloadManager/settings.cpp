#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(width(), height());
    QSettings settings;
    saveLocation = settings.value("download/savelocation", QDir::homePath()).toString();
    ui->lineEdit->setText(saveLocation);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_toolButton_clicked()
{
    QString tempSave = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(tempSave);
}
