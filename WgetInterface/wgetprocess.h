#ifndef WGETPROCESS_H
#define WGETPROCESS_H

#include <QProcess>
#include <QDebug>
#include <QTime>

class WgetProcess : public QProcess
{
    Q_OBJECT

public:
    WgetProcess();

    QString buffer;
    int progressInt;
    QString speed;
    QString time;
    QString length;
    QString status;
    QString output;
    QString rawLine;
    int row;

 protected:
    void startWget(const QStringList args);
    void terminateWget();
    void pauseWget();
    void restartWget(const QStringList args);

private:
    void processRawData(QString *const line);
    void processLength(QString *const line);
    void processProgress(QString *const line);
    void processTime(QString *const line);
    void processSpeed(QString *const line);
    QString *processTime(const QChar big, const QChar small, QString *const substring2);

    void writeprogressInt(int write);
    void writeSpeed(QString write);
    void writeTime(QString write);
    void writeLength(QString write);
    void writeStatus(QString write);
    void writeOutput(QString write);
    void writerawLine(QString write);

signals:
    void progressChanged(int wpo, int row);
    void speedChanged(QString wpo, int row);
    void timeChanged(QString wpo, int row);
    void lengthChanged(QString wpo, int row);
    void statusChanged(WgetProcess *wpo);
    void outputChanged(QString wpo, int row);
    void rawLineChanged(QString wpo, int row);

private slots:
    void readWgetLine();
    void processFinished(int code);
};
#endif // WGETPROCESS_H
