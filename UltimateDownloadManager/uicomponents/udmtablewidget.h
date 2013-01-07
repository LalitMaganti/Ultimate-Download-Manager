#ifndef UDMTABLEWIDGET_H
#define UDMTABLEWIDGET_H

#include <QTableWidget>
#include <QProgressBar>
#include "wgetprocess.h"
#include "miscdeclarations.h"

class UDMTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    UDMTableWidget(QWidget *parent = 0){parent++;}
    int getRow(QTableWidgetItem *item);
    void processStatus(WgetProcess *cmdoutput);
    void setItem(const QString stringToWrite, int row, int index);

private:
    void setItem(const int progress, int row);

public slots:
    void setProgress(WgetProcess *const cmdoutput);
    void setFileSize(WgetProcess *const cmdoutput);
    void setSpeed(WgetProcess *const cmdoutput);
    void setTime(WgetProcess *const cmdoutput);
    void setOutput(WgetProcess *const cmdoutput);
};

#endif // UDMTABLEWIDGET_H
