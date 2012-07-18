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
    progressObject.progress = 0;
    emit(lengthChanged(&progressObject));
    emit(progressChanged(&progressObject));
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

void WgetProcess::processLength(QString *const line)
{
    if (line->contains("unspecified"))
    {
        progressObject.length = "Unknown - HTML file?";
        progressObject.progress = -1;
    }
    else
    {
        QString substring1 = line->right(line->length() - line->indexOf("(") - 1);
        substring1 = substring1.left(substring1.indexOf(")"));
        progressObject.length = substring1;
    }
    emit(lengthChanged(&progressObject));
}

void WgetProcess::processProgress(QString *const line)
{
    QString substring1 = line->left(line->lastIndexOf('%'));
    substring1 = substring1.right(substring1.length() - substring1.lastIndexOf('.')).remove('.').trimmed();
    if (!(progressObject.progress == substring1.toInt()))
    {
        progressObject.progress = substring1.toInt();
        emit(progressChanged(&progressObject));
    }
}

void WgetProcess::processRawData(QString *const line)
{
    if(line->contains("Length: "))
    {
        processLength(line);
    }
    else if(line->contains('%') && line->contains(". .") && (!(progressObject.length == "Unknown - HTML file?")))
    {
        processProgress(line);
        processTime(line);
    }
}

void WgetProcess::processTime(QString *const line)
{
    QString substring2 = line->right(line->length() - line->lastIndexOf('%')).remove('%').trimmed();
    substring2 = substring2.remove(0, 5).trimmed();
    QDateTime time;
    if (substring2.contains('d'))
    {
        progressObject.time = time.fromString(processTime('d', 'h', &substring2), "dh");
    }
    else if (substring2.contains('h'))
    {
        progressObject.time = time.fromString(processTime('h', 'm', &substring2), "dhm");
    }
    else if (substring2.contains('m'))
    {
        progressObject.time = time.fromString(processTime('m', 's', &substring2), "ms");
    }
}

inline QString WgetProcess::processTime(const QChar big, const QChar small, QString *const substring2)
{
    QString bigstring = substring2->left(substring2->indexOf(big));
    const QString smallstring = substring2->right(substring2->length() - substring2->indexOf(big) - 1).remove(small);
    if ((big == 'h') && (bigstring.toInt() > 24))
    {
        bigstring = QString::number(bigstring.toInt() - 24);
        bigstring += "1";
    }
    return (bigstring + smallstring);
}

void WgetProcess::terminateWget()
{
    terminate();
    progressObject.status = "Stopped";
    emit(wgetStatusChanged(progressObject.status));
}

void WgetProcess::processFinished(int code)
{
    if (code == 0)
        progressObject.status = "Finished";
    else
        progressObject.status = "Failed";
    emit(wgetStatusChanged(progressObject.status));
}
