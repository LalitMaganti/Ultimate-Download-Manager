#include "redownloaddialog.h"

RedownloadDialog::RedownloadDialog(DownloadFile *dfa, QWidget *parent) : QDialog(parent), ui(new Ui::RedownloadDialog) {
    ui->setupUi(this);
    df = dfa;
    QString previousOutput = dfa->output;
    previousOutput = previousOutput.remove('\n');
    ui->txtSame->setText(previousOutput);
    QString ext = previousOutput.right(previousOutput.lastIndexOf("."));
    int i = ext.toInt();
    if(!i == 0) {
        QString withoutend =  previousOutput.left(previousOutput.lastIndexOf(".")).remove(".");
        ui->txtNew->setText(withoutend + "." + QString::number(i + 1));
    } else {
        ui->txtNew->setText(previousOutput + ".1");
    }
}

RedownloadDialog::~RedownloadDialog() {
    delete ui;
}

void RedownloadDialog::on_radioButton_2_clicked() {
    ui->txtSame->setEnabled(true);
    ui->txtNew->setEnabled(false);
}

void RedownloadDialog::on_radioButton_clicked() {
    ui->txtSame->setEnabled(false);
    ui->txtNew->setEnabled(true);
}

void RedownloadDialog::on_buttonBox_accepted() {
    df->overwriteRestart = ui->rdoOverwrite->isChecked();
    df->restart();
}
