#ifndef DETAILSTAB_H
#define DETAILSTAB_H

#include <QLabel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "downloadfile.h"

class DetailsTab : public QWidget
{
    Q_OBJECT
public:
    explicit DetailsTab(DownloadFile *df);
    ~DetailsTab();

    DownloadFile *downloadFile = nullptr;
    void setupUi();

private slots:
    void outputCommand(WgetProcess *const cmdoutput);

private:
    void deleteUi();
    QTextEdit *txtOutput = nullptr;
    QGridLayout *mainLayout = nullptr;
};

#endif // DETAILSTAB_H