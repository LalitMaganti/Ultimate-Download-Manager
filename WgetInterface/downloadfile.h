#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "wgetprocess.h"
#include <QSettings>
#include <QDir>

class DownloadFile : public WgetProcess
{
public:
    DownloadFile(){}
    DownloadFile(QString url);
    ~DownloadFile();
    //TODO: Should be removed
    WgetProcess* getWgetProcess(){return &wp;}
    // in the future
    int tabRow = -1;
    bool resumable;
    bool started;
    QStringList miscArgs;
    void download();
    void stopProcess();
    void start();
    void pause();
    WgetProgressObject* progressObject = 0;

private:
    QStringList args;
    WgetProcess wp;
    QString url;
};

#endif // DOWNLOADFILE_H
