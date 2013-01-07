#ifndef WGETPROCESS_H
#define WGETPROCESS_H

#include <QProcess>
#include <QDebug>
#include <QTime>

class WgetProcess : public QProcess
{
    Q_PROPERTY(int progressInt READ progressInt NOTIFY progressChanged)
    Q_PROPERTY(QString speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    Q_PROPERTY(QString length READ length NOTIFY lengthChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString output READ output NOTIFY outputChanged)
    Q_PROPERTY(QString rawLine READ rawLine NOTIFY lineRead)

    Q_OBJECT

public:
    WgetProcess();

    int progressInt();
    QString speed();
    QString time();
    QString length();
    QString status();
    QString output();
    QString rawLine();

    void writeprogressInt(int write);
    void writespeed(QString write);
    void writetime(QString write);
    void writelength(QString write);
    void writestatus(QString write);
    void writeoutput(QString write);
    void writerawLine(QString write);

    int row;
    QString buffer;

 protected:
    void startWget(const QStringList args);
    void terminateWget();
    void pauseWget();
    void restartWget(const QStringList args);

    // Vars
    int m_progressInt;
    QString m_speed;
    QString m_time;
    QString m_length;
    QString m_status;
    QString m_output;
    QString m_rawLine;

private:
    void processRawData(QString *const line);
    void processLength(QString *const line);
    void processProgress(QString *const line);
    void processTime(QString *const line);
    QString *processTime(const QChar big, const QChar small, QString *const substring2);
    void processSpeed(QString *const line);

signals:
    void progressChanged(WgetProcess *const wpo);
    void speedChanged(WgetProcess *const wpo);
    void timeChanged(WgetProcess *const wpo);
    void lengthChanged(WgetProcess *const wpo);
    void statusChanged(WgetProcess *const wpo);
    void outputChanged(WgetProcess *const wpo);
    void lineRead(WgetProcess *const wpo);

private slots:
    void readWgetLine();
    void processFinished(int code);
};
#endif // WGETPROCESS_H
