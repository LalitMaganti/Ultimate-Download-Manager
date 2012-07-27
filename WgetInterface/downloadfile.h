#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "wgetprocess.h"

class DownloadFile : public WgetProcess
{
public:
    DownloadFile(){tabOpen = false;}
    DownloadFile(QString url);
    ~DownloadFile();
    //TODO: Should be removed
    WgetProcess* getWgetProcess(){return &wp;}
    // in the future
    bool tabOpen;
    bool resumable;
    bool started;
    void download();
    void stopProcess();
    void start();
    void pause();
    WgetProgressObject* progressObject = 0;

private:
    WgetProcess wp;
    QString url;
};

#endif // DOWNLOADFILE_H
