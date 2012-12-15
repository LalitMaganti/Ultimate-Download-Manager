#ifndef UDMTABLEWIDGET_H
#define UDMTABLEWIDGET_H

#include <QTableWidget>
#include <QProgressBar>
#include "wgetprogressobject.h"
#include "miscdeclarations.h"

class UDMTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    UDMTableWidget(QWidget *parent = 0){parent++;}
    int getRow(QTableWidgetItem *item);
    void processStatus(WgetProgressObject *cmdoutput);
    void setItem(const QString stringToWrite, int row, int index);

private:
    void setItem(const int progress, int row);

public slots:
    void setProgress(WgetProgressObject *const cmdoutput);
    void setFileSize(WgetProgressObject *const cmdoutput);
    void setSpeed(WgetProgressObject *const cmdoutput);
    void setTime(WgetProgressObject *const cmdoutput);
    void setOutput(WgetProgressObject *const cmdoutput);
};

#endif // UDMTABLEWIDGET_H
