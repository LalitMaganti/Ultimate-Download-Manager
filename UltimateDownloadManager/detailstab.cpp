#include "detailstab.h"
#include <QLabel>
#include "QTableWidgetItem"

DetailsTab::DetailsTab(QString buffer)
{
    mainLayout = new QGridLayout;
    d = new QTextEdit;
    d->setReadOnly(true);
    d->setText(buffer);
    mainLayout->addWidget(d, 0, 0, 1, 5);
    j = new QLabel("Details");
    mainLayout->addWidget(j, 1, 0, 1, 5);
    lblLength = new QLabel("Length: Processing");
    mainLayout->addWidget(lblLength, 2, 0);
    lblStatus = new QLabel("Status: Running");
    mainLayout->addWidget(lblStatus, 2, 1);
    setLayout(mainLayout);
}

DetailsTab::~DetailsTab()
{
    downloadFile->tabOpen = false;
    delete d;
    delete j;
    delete mainLayout;
}

void DetailsTab::outputCommand(WgetProgressObject *cmdoutput)
{
    d->append(cmdoutput->rawLine);
}

void DetailsTab::setItem(WgetProgressObject* cmdoutput)
{
     setItem(cmdoutput->length, 1);
}

void DetailsTab::setItem(QString status, int index)
{
    if (index == 0)
    {
        lblStatus->setText("Status: " + status);
    }
    else
    {
        lblLength->setText("Length: " + status);
    }
}
