#ifndef WGETPROCESS_H
#define WGETPROCESS_H

#include <QProcess>
#include <QDebug>
#include "wgetprogressobject.h"

class WgetProcess : public QProcess
{
    Q_OBJECT
public:
    WgetProcess();
    WgetProgressObject progressObject;
    void startWget(QStringList args);
    
signals:
    void lineRead(WgetProgressObject *wpo);
    void lengthChanged(WgetProgressObject *wpo);
    void wgetStatusChanged(QString status);

private slots:
    void readWgetLine();
    void processFinished(int code);

private:
    void processRawData(QString *line);
};

#endif // WGETPROCESS_H
