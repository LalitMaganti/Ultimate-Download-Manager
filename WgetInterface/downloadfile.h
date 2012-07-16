#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "wgetprocess.h"

class DownloadFile
{
public:
    DownloadFile(){}
    DownloadFile(QString url);
    WgetProcess* getWgetProcess();
    void download();
private:
    WgetProcess wp;
    QString url;
};

#endif // DOWNLOADFILE_H
