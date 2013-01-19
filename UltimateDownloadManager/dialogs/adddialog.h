#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QClipboard>
#include <QDialog>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include "downloadfile.h"
#include "miscfunctions.h"
#include "ui_adddialog.h"

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddDialog();
    ~AddDialog();
    QString url;
    DownloadFile *fileGlobal = nullptr;
    bool start;

private slots:
    void on_btnOK_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_btnCancel_clicked();
    void on_checkBox_2_clicked();
    void on_btnSave_clicked();
    void on_chkName_clicked();
    void on_txtName_textChanged(const QString &arg1);
    void replyFinished(QNetworkReply::NetworkError network);

private:
    Ui::AddDialog *ui = nullptr;
    QString tempUrl;
};

#endif // ADDDIALOG_H