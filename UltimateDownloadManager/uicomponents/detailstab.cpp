#include "detailstab.h"

DetailsTab::DetailsTab(DownloadFile *df)
{
    downloadFile = df;
    if (!(downloadFile->progressObject.status == "Finished"))
        connect(downloadFile, SIGNAL(lineRead(WgetProgressObject *const)), this, SLOT(outputCommand(WgetProgressObject *const)));
    setupUi();
}

DetailsTab::~DetailsTab()
{
    deleteUi();
    downloadFile->tabIndex = -1;
}

inline void DetailsTab::deleteUi()
{
    delete txtOutput;
    delete mainLayout;
}

inline void DetailsTab::setupUi()
{
    mainLayout = new QGridLayout;
    txtOutput = new QTextEdit;
    txtOutput->setReadOnly(true);
    txtOutput->setText(downloadFile->progressObject.buffer);
    mainLayout->addWidget(txtOutput, 0, 0, 1, 5);
    setLayout(mainLayout);
}

void DetailsTab::outputCommand(WgetProgressObject *const cmdoutput)
{
    txtOutput->append(cmdoutput->rawLine);
}
