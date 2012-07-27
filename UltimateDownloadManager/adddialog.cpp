#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog() : QDialog(), ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(width(), height());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
{
    url = ui->lineEdit->text();
    fileGlobal = new DownloadFile(url);
    fileGlobal->resumable = ui->checkBox->isChecked();
    start = ui->chkStart->isChecked();
}
