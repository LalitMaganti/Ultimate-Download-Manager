#include "detailstab.h"
#include <QLabel>
#include "QTableWidgetItem"

DetailsTab::DetailsTab(DownloadFile *df)
{
    downloadFile = df;
    setupUi();
    if (!(downloadFile->progressObject->status == "Finished"))
    {
        connect(downloadFile->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject *const)), this, SLOT(outputCommand(WgetProgressObject *const)));
    }
}

DetailsTab::~DetailsTab()
{
    downloadFile->tabRow = -1;
    deleteUi();
}

inline void DetailsTab::deleteUi()
{
    delete d;
    delete mainLayout;
}

inline void DetailsTab::setupUi()
{
    mainLayout = new QGridLayout;
    d = new QTextEdit;
    d->setReadOnly(true);
    d->setText(downloadFile->progressObject->buffer);
    mainLayout->addWidget(d, 0, 0, 1, 5);
    setLayout(mainLayout);
}

void DetailsTab::outputCommand(WgetProgressObject *const cmdoutput)
{
    d->append(cmdoutput->rawLine);
}
