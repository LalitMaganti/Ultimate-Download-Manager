#include "downloadfile.h"

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
    setArgs();
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
    if (started == false)
        setArgs();
    wp.restartWget(args);
}

void DownloadFile::setArgs()
{
    started = true;
    if (!(miscArgs.isEmpty()))
        args = miscArgs;
    args << url;
    if (resumable)
        args << "-c";
    QSettings settings;
    args << "-P" << settings.value("download/savelocation", QDir::homePath()).toString();
}
