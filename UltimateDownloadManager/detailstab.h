#ifndef DETAILSTAB_H
#define DETAILSTAB_H

#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include "wgetprogressobject.h"
#include "downloadfile.h"
class DetailsTab : public QWidget
{
    Q_OBJECT
public:
    DetailsTab(QString buffer);
    ~DetailsTab();
    DownloadFile *downloadFile;
private slots:
    void outputCommand(WgetProgressObject *cmdoutput);
public slots:
    void setItem(WgetProgressObject* cmdoutput);
    void setItem(QString status, int index = 0);
private:
    QTextEdit *d;
    QGridLayout *mainLayout;
    QLabel* j;
    QLabel* lblLength;
    QLabel* lblStatus;
};

#endif // DETAILSTAB_H
