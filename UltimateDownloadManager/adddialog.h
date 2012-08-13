#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QUrl>
#include "downloadfile.h"
#include <QtNetwork/QNetworkReply>

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
    DownloadFile *fileGlobal = 0;
    bool start;
    void onNetworkReply(QNetworkReply *k);
    
private slots:
    void on_btnOK_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_btnCancel_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
