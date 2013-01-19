#include "udmtablewidget.h"

UDMTableWidget::UDMTableWidget(QWidget *parent) : QTableWidget(parent)
{
}

int UDMTableWidget::getRow(QTableWidgetItem *item) {
    return item->row();
}

void UDMTableWidget::processStatus(WgetProcess *wpo) {
    int row = wpo->row;
    if (wpo->status == "Finished") {
        if (wpo->length == "Processing") {
            setItem("See log for more info", row, FileSize);
            setItem("Unknown", row, Speed);
            setItem("Download finished", row, Time);
        } else if(wpo->length == "0 second(s)") {
            setItem("Download finished", row, Time);
        }
        setItem("100%", row, Progress);
    } else if(wpo->status == "Failed") {
        setItem("See log for more info", row, FileSize);
        setItem("Unknown", row, Progress);
        setItem("Unknown", row, Speed);
        setItem("Download failed", row, Time);
    }
    resizeColumnsToContents();

    setStatus(wpo->status, row);
}

void UDMTableWidget::noInitialStart(DownloadFile *df) {
    setProgress(df->progressInt, df->row);
    setFileSize(df->length, df->row);
    setSpeed(df->speed, df->row);
    setTime(df->time, df->row);
}

void UDMTableWidget::setupNewItem(WgetProcess *wp, QString url) {
    connect(wp, &WgetProcess::lengthChanged, this, &UDMTableWidget::setFileSize);
    connect(wp, &WgetProcess::progressChanged, this, &UDMTableWidget::setProgress);
    connect(wp, &WgetProcess::speedChanged, this, &UDMTableWidget::setSpeed);
    connect(wp, &WgetProcess::timeChanged, this, &UDMTableWidget::setTime);
    connect(wp, &WgetProcess::outputChanged, this, &UDMTableWidget::setOutput);

    setItem(url, wp->row, URL);
    setCellWidget(wp->row, Progress, new QProgressBar());
}

inline void UDMTableWidget::setItem(const int progress, int row) {
    ((QProgressBar*)(cellWidget(row, Progress)))->setValue(progress);
}

inline void UDMTableWidget::setItem(const QString stringToWrite, int row, int index) {
    if (item(row, index) == 0x0) {
        QTableWidgetItem *item = new QTableWidgetItem(stringToWrite);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        QTableWidget::setItem(row, index, item);
        resizeColumnsToContents();
    } else {
        item(row, index)->setText(stringToWrite);
    }
}

void UDMTableWidget::setStatus(QString d, int row) {
    setItem(d, row, Status);
}

void UDMTableWidget::setFileSize(QString cmdoutput, int row) {
    setItem(cmdoutput, row, FileSize);
}

void UDMTableWidget::setProgress(int cmdoutput, int row) {
    setItem(cmdoutput, row);
}

void UDMTableWidget::setSpeed(QString cmdoutput, int row) {
    setItem(cmdoutput, row, Speed);
}

void UDMTableWidget::setTime(QString cmdoutput, int row) {
    setItem(cmdoutput, row, Time);
}

void UDMTableWidget::setOutput(QString cmdoutput, int row) {
    setItem(cmdoutput, row, Output);
}