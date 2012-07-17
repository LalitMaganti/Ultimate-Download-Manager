#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "wgetprocess.h"

class DownloadFile
{
public:
    DownloadFile(){tabOpen = false;}
    DownloadFile(QString url);
    //TODO: Should be removed
    WgetProcess* getWgetProcess();
    // in the future
    bool tabOpen;
    bool resumable;
    void download();
    void stopProcess();
    WgetProgressObject* progressObject;

private:
    WgetProcess wp;
    QString url;
};

#endif // DOWNLOADFILE_H
