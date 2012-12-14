#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "wgetprocess.h"

class DownloadFile : public WgetProcess
{
public:
    // Methods
    DownloadFile(QString url);
    ~DownloadFile();
    void download();
    void stopProcess();
    void start();
    void pause();
    void restart();

    // Variables
    int tabIndex;
    bool resumable;
    bool started;
    QString outdir;
    QString fullPath;
    QString miscArgs;
    bool overwriteRestart;

private:
    QStringList args;
    QString url;
    void setArgs();
};

#endif // DOWNLOADFILE_H
