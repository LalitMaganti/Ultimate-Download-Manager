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
    DetailsTab(DownloadFile *df);
    ~DetailsTab();
    DownloadFile *downloadFile;
    void setupUi();
private slots:
    void outputCommand( WgetProgressObject *const cmdoutput);
private:
    void deleteUi();
    QTextEdit *d;
    QGridLayout *mainLayout;
};

#endif // DETAILSTAB_H
