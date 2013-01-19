#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);
    ui->label_3->setText(QString("Version %1.%2.%3").arg(majorVersion).arg(minorVersion).arg(buildVersion));
}

AboutDialog::~AboutDialog() {
    delete ui;
}
