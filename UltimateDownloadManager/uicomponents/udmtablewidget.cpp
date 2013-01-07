#include "uicomponents/udmtablewidget.h"

int UDMTableWidget::getRow(QTableWidgetItem *item)
{
    return item->row();
}

inline void UDMTableWidget::setItem(const int progress, int row)
{
    ((QProgressBar*)(cellWidget(row, Progress)))->setValue(progress);
}

inline void UDMTableWidget::setItem(const QString stringToWrite, int row, int index)
{
    if (item(row, index) == 0x0)
    {
        QTableWidgetItem *item = new QTableWidgetItem(stringToWrite);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        QTableWidget::setItem(row, index, item);
        resizeColumnsToContents();
    }
    else
        item(row, index)->setText(stringToWrite);
}

void UDMTableWidget::setFileSize(WgetProcess *const progressObject)
{
    setItem(progressObject->length(), progressObject->row, FileSize);
}

void UDMTableWidget::setProgress(WgetProcess *const progressObject)
{
    setItem(progressObject->progressInt(), progressObject->row);
}

void UDMTableWidget::setSpeed(WgetProcess *const progressObject)
{
    setItem(progressObject->speed(), progressObject->row, Speed);
}

void UDMTableWidget::setTime(WgetProcess *const progressObject)
{
    setItem(progressObject->time(), progressObject->row, Time);
}

void UDMTableWidget::setOutput(WgetProcess *const progressObject)
{
    setItem(progressObject->output(), progressObject->row, Output);
}

void UDMTableWidget::processStatus(WgetProcess *wpo)
{
    int row = wpo->row;
    if (wpo->status() == "Finished")
    {
        if (wpo->length() == "Processing")
        {
            setItem("See log for more info", row, FileSize);
            setItem("Unknown", row, Speed);
            setItem("Download finished", row, Time);
        }
        else if(wpo->length() == "0 second(s)")
            setItem("Download finished", row, Time);
        setItem("100%", row, Progress);
    }
    else if(wpo->status() == "Failed")
    {
        setItem("See log for more info", row, FileSize);
        setItem("Unknown", row, Progress);
        setItem("Unknown", row, Speed);
        setItem("Download failed", row, Time);
    }
    resizeColumnsToContents();
}
