#include "detailstab.h"
#include <QLabel>
#include "QTableWidgetItem"

DetailsTab::DetailsTab(DownloadFile *df)
{
    downloadFile = df;
    setupUi();
    if (downloadFile->progressObject->status == "Finished")
    {
        setItem(downloadFile->progressObject->status);
        setItem(downloadFile->progressObject);
    }
    else
    {
        connect(downloadFile->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject *const)), this, SLOT(outputCommand(WgetProgressObject *const)));
        connect(downloadFile->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject *const)), this, SLOT(setItem(WgetProgressObject *const)));
        connect(downloadFile->getWgetProcess(), SIGNAL(wgetStatusChanged(const QString)), this, SLOT(setItem(const QString)));
    }
    downloadFile->tabOpen = true;
}

DetailsTab::~DetailsTab()
{
    disconnect(downloadFile->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject *const)), this, SLOT(outputCommand(WgetProgressObject *const)));
    disconnect(downloadFile->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject *const)), this, SLOT(setItem(WgetProgressObject *const)));
    disconnect(downloadFile->getWgetProcess(), SIGNAL(wgetStatusChanged(const QString)), this, SLOT(setItem(const QString)));
    downloadFile->tabOpen = false;
    deleteUi();
}

inline void DetailsTab::deleteUi()
{
    delete d;
    delete j;
    delete mainLayout;
}

inline void DetailsTab::setupUi()
{
    mainLayout = new QGridLayout;
    d = new QTextEdit;
    d->setReadOnly(true);
    d->setText(downloadFile->progressObject->buffer);
    mainLayout->addWidget(d, 0, 0, 1, 5);
    j = new QLabel("Details");
    mainLayout->addWidget(j, 1, 0, 1, 5);
    lblLength = new QLabel("Length: Processing");
    mainLayout->addWidget(lblLength, 2, 0);
    lblStatus = new QLabel("Status: Running");
    mainLayout->addWidget(lblStatus, 2, 1);
    setLayout(mainLayout);
}

void DetailsTab::outputCommand(WgetProgressObject *const cmdoutput)
{
    d->append(cmdoutput->rawLine);
}

void DetailsTab::setItem(WgetProgressObject *const cmdoutput)
{
     setItem(cmdoutput->length, 1);
}

void DetailsTab::setItem(const QString status, int index)
{
    if (index == 0)
        lblStatus->setText("Status: " + status);
    else
        lblLength->setText("Length: " + status);
}
