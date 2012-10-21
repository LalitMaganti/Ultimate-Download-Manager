#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QClipboard>
#include <QFileDialog>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>


#include "downloadfile.h"
#include "miscstuff.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
    
public:
    AddDialog();
    ~AddDialog();
    QString url;
    DownloadFile *fileGlobal;
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
    Ui::AddDialog *ui;
    QString tempUrl;
};

#endif // ADDDIALOG_H
