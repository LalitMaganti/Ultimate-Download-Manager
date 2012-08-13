#include "adddialog.h"
#include "ui_adddialog.h"
#include <QClipboard>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

AddDialog::AddDialog() : QDialog(), ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(width(), height());
    QClipboard *k = QApplication::clipboard();
    QString kf = k->text();
    if (QUrl(kf).isValid())
    {
        ui->lineEdit->setText(k->text());
        ui->btnOK->setEnabled(true);
    }
}

AddDialog::~AddDialog()
{
    delete ui;
}
void AddDialog::on_btnOK_clicked()
{
    url = ui->lineEdit->text();
    fileGlobal = new DownloadFile(url);
    fileGlobal->resumable = ui->checkBox->isChecked();
    if (!(ui->lineEdit_2->text().isEmpty()))
        fileGlobal->miscArgs = ui->lineEdit_2->text().split(" ");
    start = ui->chkStart->isChecked();
    this->accept();
}

void AddDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if (QUrl(arg1).isValid())
        ui->btnOK->setEnabled(true);
    else
        ui->btnOK->setEnabled(false);
}

void AddDialog::on_btnCancel_clicked()
{
    this->reject();
}
