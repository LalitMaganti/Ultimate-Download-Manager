#include "downloadfile.h"
#include <QDir>

DownloadFile::DownloadFile(QString urlarg)
{
    url = urlarg;
    started = false;
    progressObject = &wp.progressObject;
}

DownloadFile::~DownloadFile()
{
    if (!(progressObject->status == "Finished"))
        stopProcess();
}

void DownloadFile::download()
{
    started = true;
    QStringList args(url);
    if (resumable)
        args << "-c";
    args << "-P" << QDir::homePath();
    wp.startWget(args);
}

void DownloadFile::stopProcess()
{
    wp.terminateWget();
}

void DownloadFile::pause()
{
    wp.pauseWget();
}

void DownloadFile::start()
{
    QStringList args(url);
    if (resumable)
        args << "-c";
    args << "-P" << QDir::homePath();
    wp.restartWget(args);
}
