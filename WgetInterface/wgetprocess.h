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
    void pauseWget();
    void restartWget(const QStringList args);

    void processRawData(QString *const line);
    void processLength(QString *const line);
    void processProgress(QString *const line);
    void processTime(QString *const line);
    QString *processTime(const QChar big, const QChar small, QString *const substring2);
    void processSpeed(QString *const line);

signals:
    void speedChanged(WgetProgressObject *const wpo);
    void timeChanged(WgetProgressObject *const wpo);
    void progressChanged(WgetProgressObject *const wpo);
    void lineRead(WgetProgressObject *const wpo);
    void lengthChanged(WgetProgressObject *const wpo);
    void wgetStatusChanged(WgetProgressObject *const wpo);

private slots:
    void readWgetLine();
    void processFinished(int code);
};
#endif // WGETPROCESS_H
