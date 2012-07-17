#ifndef WGETPROCESS_H
#define WGETPROCESS_H

#include <QProcess>
#include <QDebug>
#include <QTime>
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
    QString processTime(QChar big, QChar small, QString *substring2);
};

#endif // WGETPROCESS_H
