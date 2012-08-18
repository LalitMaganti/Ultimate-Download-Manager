#include "downloadfile.h"

DownloadFile::DownloadFile(QString urlarg)
{
    tabIndex = -1;
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
        args.append(miscArgs);
    args << url;
    if (resumable)
        args << "-c";
    if (!outdir.isEmpty())
        args << "-P" << outdir;
    else
        args << "-O" << fullPath;
}
