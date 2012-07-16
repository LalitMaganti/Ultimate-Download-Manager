#include "detailstab.h"

DetailsTab::DetailsTab(QString buffer, QWidget *parent)
{
    mainLayout = new QVBoxLayout;
    d = new QTextEdit;
    d->setText(buffer);
    mainLayout->addWidget(d);
    setLayout(mainLayout);
}

DetailsTab::~DetailsTab()
{
    delete d;
    delete mainLayout;
}

void DetailsTab::outputCommand(WgetProgressObject *cmdoutput)
{
    d->append(cmdoutput->rawLine);
}
