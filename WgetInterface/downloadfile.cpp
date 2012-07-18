#include "downloadfile.h"

DownloadFile::DownloadFile(QString urlarg)
{
    url = urlarg;
}

DownloadFile::~DownloadFile()
{
    if (!(progressObject->status == "Finished"))
        stopProcess();
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
    wp.terminateWget();
}
