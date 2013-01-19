#ifndef UDMTABLEWIDGET_H
#define UDMTABLEWIDGET_H

#include <QProgressBar>
#include <QTableWidget>

#include "downloadfile.h"

class UDMTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit UDMTableWidget(QWidget *parent = 0);

    void noInitialStart(DownloadFile *df);
    void setupNewItem(WgetProcess *wp, QString url);

    int getRow(QTableWidgetItem *item);

    void processStatus(WgetProcess *cmdoutput);
    void setStatus(QString d, int row);

private:
    void setItem(int progress, int row);
    void setItem(QString stringToWrite, int row, int index);
    enum tableRow
    {
        URL = 0,
        FileSize = 1,
        Status = 2,
        Progress = 3,
        Speed = 4,
        Time = 5,
        Output = 6
    };

public slots:
    void setProgress(int cmdoutput, int row);
    void setFileSize(QString cmdoutput, int row);
    void setSpeed(QString cmdoutput, int row);
    void setTime(QString cmdoutput, int row);
    void setOutput(QString cmdoutput, int row);
};

#endif // UDMTABLEWIDGET_H