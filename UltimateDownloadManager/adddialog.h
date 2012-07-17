#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "downloadfile.h"

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
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
