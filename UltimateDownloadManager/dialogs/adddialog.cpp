#include "adddialog.h"

AddDialog::AddDialog() : QDialog(), ui(new Ui::AddDialog) {
    ui->setupUi(this);
    this->setFixedSize(width(), height());
    QClipboard *k = QApplication::clipboard();
    tempUrl = k->text();

    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QNetworkReply *reply = nam->head(QNetworkRequest(tempUrl));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyFinished(QNetworkReply::NetworkError)));

    ui->lineEdit->setText(tempUrl);
    ui->btnOK->setEnabled(true);

    ui->txtSave->setText(getOutDirectory());
}

void AddDialog::replyFinished(QNetworkReply::NetworkError network) {
    if (network != 0)     {
        ui->lineEdit->setText("");
        ui->btnOK->setEnabled(false);
    }
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::on_btnOK_clicked() {
    url = ui->lineEdit->text();
    fileGlobal = new DownloadFile(url);
    fileGlobal->resumable = ui->checkBox->isChecked();
    fileGlobal->miscArgs = ui->lineEdit_2->text();
    start = ui->chkStart->isChecked();
    if (ui->chkName->isChecked()) {
        fileGlobal->outDir = ui->txtSave->text();
    } else {
        fileGlobal->fullPath = ui->txtSave->text() + QDir::separator() + ui->txtName->text();
    }
    this->accept();
}

void AddDialog::on_lineEdit_textChanged(const QString &arg1) {
    ui->btnOK->setEnabled(QUrl(arg1).isValid());
}

void AddDialog::on_btnCancel_clicked() {
    this->reject();
}

void AddDialog::on_checkBox_2_clicked() {
    bool enable = !(ui->checkBox_2->isChecked());
    ui->btnSave->setEnabled(enable);
    ui->txtSave->setEnabled(enable);
    ui->lblSave->setEnabled(enable);
    if(!enable) {
        ui->txtSave->setText(::getOutDirectory());
    }
}

void AddDialog::on_btnSave_clicked() {
    QString tempSave = QFileDialog::getExistingDirectory(this, "Open Directory", ui->txtSave->text(), QFileDialog::ShowDirsOnly);
    if (!(tempSave == "")) {
        ui->txtSave->setText(tempSave);
    }
}

void AddDialog::on_chkName_clicked() {
    bool enable = !(ui->chkName->isChecked());
    ui->txtName->setEnabled(enable);
    ui->lblName->setEnabled(enable);
    ui->btnOK->setEnabled(!enable);
}

void AddDialog::on_txtName_textChanged(const QString &arg1) {
    ui->btnOK->setEnabled(!arg1.isEmpty());
}
