#ifndef WGETPROCESS_H
#define WGETPROCESS_H

#include <QDebug>
#include <QProcess>
#include <QTime>

class WgetProcess : public QProcess
{
    Q_OBJECT
public:
    WgetProcess();

    QString buffer;
    int row;

    // Changeable props
    int progressInt;
    QString speed;
    QString time;
    QString length;
    QString status;
    QString output;
    QString rawLine;

 protected:
    void startWget(QStringList args);
    void terminateWget();
    void pauseWget();
    void restartWget(QStringList args);

private:
    void processRawData(QString *line);
    void processLength(QString *line);
    void processProgress(QString *line);
    void processTime(QString *line);
    void processSpeed(QString *line);
    QString *processTime(QChar big, QChar small, QString *substring2);

    void writeprogressInt(int write);
    void writeSpeed(QString write);
    void writeTime(QString write);
    void writeLength(QString write);
    void writeStatus(QString write);
    void writeOutput(QString write);
    void writerawLine(QString write);

signals:
    void progressChanged(int wpo, int row);
    void statusChanged(WgetProcess *wpo);
    void speedChanged(QString wpo, int row);
    void timeChanged(QString wpo, int row);
    void lengthChanged(QString wpo, int row);
    void outputChanged(QString wpo, int row);
    void rawLineChanged(QString wpo, int row);

private slots:
    void readWgetLine();
    void processFinished(int code);

};
#endif // WGETPROCESS_H