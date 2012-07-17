#include "downloadfile.h"

DownloadFile::DownloadFile(QString urlarg)
{
    url = urlarg;
}

WgetProcess* DownloadFile::getWgetProcess()
{
    return &wp;
}

void DownloadFile::download()
{
    QStringList args(url);
    if (resumable)
        args << "-c";
    wp.startWget(args);
    progressObject = &wp.progressObject;
}

void DownloadFile::stopProcess()
{
    wp.terminate();
}

