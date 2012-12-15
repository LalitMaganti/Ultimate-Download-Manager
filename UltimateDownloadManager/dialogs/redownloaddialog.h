#ifndef REDOWNLOADDIALOG_H
#define REDOWNLOADDIALOG_H

#include <QDialog>

#include "downloadfile.h"
#include "ui_redownloaddialog.h"

namespace Ui {
class RedownloadDialog;
}

class RedownloadDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RedownloadDialog(DownloadFile *previousOutput, QWidget *parent = 0);
    ~RedownloadDialog();
    
private slots:
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::RedownloadDialog *ui;
    DownloadFile *df;
};

#endif // REDOWNLOADDIALOG_H
