#include "downloadfile.h"

DownloadFile::DownloadFile(QString urlarg)
{
    tabIndex = -1;
    url = urlarg;
    started = false;
}

DownloadFile::~DownloadFile()
{
    if (!(progressObject.status == "Finished"))
        stopProcess();
}

void DownloadFile::download()
{
    setArgs();
    startWget(args);
}

void DownloadFile::stopProcess()
{
    terminateWget();
}

void DownloadFile::pause()
{
    pauseWget();
}

void DownloadFile::restart()
{
    bool oldresumable = resumable;
    resumable = false;
    setArgs();
    restartWget(args);
    resumable = oldresumable;
}

void DownloadFile::start()
{
    if (started == false)
        setArgs();
    restartWget(args);
}

void DownloadFile::setArgs()
{
    args.clear();
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
