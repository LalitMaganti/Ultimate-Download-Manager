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
    args << "-c";
    wp.startWget(args);
}

