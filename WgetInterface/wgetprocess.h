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
    void startWget(const QStringList args);
    void terminateWget();
    
signals:
    void progressChanged(WgetProgressObject *const wpo);
    void lineRead(WgetProgressObject *const wpo);
    void lengthChanged(WgetProgressObject *const wpo);
    void wgetStatusChanged(const QString status);

private slots:
    void readWgetLine();
    void processFinished(int code);

private:
    void processRawData(QString *const line);
    void processLength(QString *const line);
    void processProgress(QString *const line);
    void processTime(QString *const line);
    QString processTime(const QChar big, const QChar small, QString *const substring2);
};

#endif // WGETPROCESS_H
