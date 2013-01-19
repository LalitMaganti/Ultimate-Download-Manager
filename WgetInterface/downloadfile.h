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

    int tabIndex;
    bool resumable, started, overwriteRestart;
    QString outDir, fullPath, miscArgs;

private:
    QStringList args;
    QString url;
    void setArgs();
};

#endif // DOWNLOADFILE_H