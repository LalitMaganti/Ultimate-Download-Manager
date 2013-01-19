#include "detailstab.h"

DetailsTab::DetailsTab(DownloadFile *df) : QWidget() {
    downloadFile = df;
    if (!(downloadFile->status == "Finished")) {
        connect(downloadFile, SIGNAL(lineRead(WgetProcess *const)), this, SLOT(outputCommand(WgetProcess *const)));
    }
    setupUi();
}

DetailsTab::~DetailsTab() {
    deleteUi();
    downloadFile->tabIndex = -1;
}

inline void DetailsTab::deleteUi() {
    delete txtOutput;
    delete mainLayout;
}

inline void DetailsTab::setupUi() {
    mainLayout = new QGridLayout;
    txtOutput = new QTextEdit;
    txtOutput->setReadOnly(true);
    txtOutput->setText(downloadFile->buffer);
    mainLayout->addWidget(txtOutput, 0, 0, 1, 5);
    setLayout(mainLayout);
}

void DetailsTab::outputCommand(WgetProcess *cmdoutput) {
    txtOutput->append(cmdoutput->rawLine);
}
