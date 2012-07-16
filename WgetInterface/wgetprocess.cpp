#include "wgetprocess.h"

WgetProcess::WgetProcess()
{
    setReadChannel(QProcess::StandardError);
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readWgetLine()));
    connect(this, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
}

void WgetProcess::startWget(QStringList args)
{
    progressObject.status = "Running";
    progressObject.length = "Processing";
    emit(lengthChanged(&progressObject));
    emit(wgetStatusChanged("Running"));
    start("wget", args);
}

void WgetProcess::readWgetLine()
{
    if(canReadLine())
    {
        QString line = readLine();
        progressObject.rawLine = line;
        progressObject.buffer += line;
        processRawData(&line);
        emit lineRead(&progressObject);
    }
}

void WgetProcess::processRawData(QString *line)
{
    if(line->contains("Length: "))
    {
        if (line->contains("unspecified"))
        {
            progressObject.length = "Unknown - HTML file?";
        }
        else
        {
            QString substring1 = line->right(line->length() - line->indexOf("(") - 1);
            substring1 = substring1.left(substring1.indexOf(")"));
            progressObject.length = substring1;
        }
    }
    else if(line->contains("%"))
    {
        QString substring1 = line->left(line->lastIndexOf('.'));
        substring1 = substring1.right(substring1.length() - substring1.lastIndexOf('.'));
        substring1 = substring1.left(substring1.lastIndexOf('%'));
        substring1 = substring1.remove('.').trimmed();
        progressObject.progress = substring1.toULongLong();
    }
    emit(lengthChanged(&progressObject));
}

void WgetProcess::processFinished(int code)
{
    QString status;
    if (code == 0)
        status = "Finished";
    else
        status = "Failed";

    progressObject.status = status;
    emit(wgetStatusChanged(status));
}
