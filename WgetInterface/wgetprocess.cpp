#include "wgetprocess.h"

WgetProcess::WgetProcess()
{
    setReadChannel(QProcess::StandardError);
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readWgetLine()));
    connect(this, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    progressObject.progress = "0%";
    progressObject.status = "Pending";
    progressObject.length = "Pending";
    progressObject.speed = "Pending";
    progressObject.time = "Pending";
    progressObject.output = "Pending";
    progressObject.buffer = "Download not started";
}

void WgetProcess::startWget(QStringList args)
{
    progressObject.status = "Running";
    progressObject.length = "Processing";
    progressObject.speed = "Processing";
    progressObject.time = "Processing";
    progressObject.output = "Processing";
    progressObject.buffer = "";
    emit(lengthChanged(&progressObject));
    emit(wgetStatusChanged(&progressObject));
    emit(speedChanged(&progressObject));
    emit(timeChanged(&progressObject));
    emit(progressChanged(&progressObject));
    emit(outputChanged(&progressObject));
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

inline void WgetProcess::processLength(QString *const line)
{
    if (line->contains("unspecified"))
    {
        progressObject.length = "Unknown - HTML file?";
        progressObject.progress = "Unknown";
        progressObject.speed = "Unknown";
        progressObject.time = "Unknown";
        emit(progressChanged(&progressObject));
        emit(speedChanged(&progressObject));
        emit(timeChanged(&progressObject));
    }
    else
    {
        QString substring1 = line->right(line->length() - line->indexOf("(") - 1);
        substring1 = substring1.left(substring1.indexOf(")"));
        progressObject.length = substring1;
    }
    emit(lengthChanged(&progressObject));
}

inline void WgetProcess::processProgress(QString *const line)
{

    QString substring1 = line->left(line->lastIndexOf('%'));
    substring1 = substring1.right(substring1.length() - substring1.lastIndexOf('.')).remove('.').trimmed() + "%";
    if (!(progressObject.progress == substring1))
    {
        progressObject.progress = substring1;
        emit(progressChanged(&progressObject));
    }
}

void WgetProcess::processRawData(QString *const line)
{
    if(line->contains("Length: "))
    {
        processLength(line);
    }
    else if(line->contains("Saving to:"))
    {
        progressObject.output = line->right(line->length() - line->indexOf('`')).remove('\'').remove('`');
        emit(outputChanged(&progressObject));

    }
    else if(line->contains('%') && line->contains(". .") && (!(progressObject.length == "Unknown - HTML file?")))
    {
        processProgress(line);
        processTime(line);
        processSpeed(line);
    }
}

inline void WgetProcess::processTime(QString *const line)
{
    QString substring1;
    QString substring2;
    if(line->contains("100%"))
    {
        substring1 = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        substring2 = substring1.left(substring1.indexOf(" "));
        substring2 = substring2.right(substring2.length() - substring2.indexOf("=")).remove("=");
    }
    else
    {
        substring2 = line->right(line->length() - line->lastIndexOf('%')).remove('%').trimmed();
        substring2 = substring2.remove(0, 5).trimmed();
    }
        progressObject.time = "";
        QString *final = &progressObject.time;
        QString *time;
        if (substring2.contains('d'))
        {
            time = processTime('d', 'h', &substring2);
            *final = time[0] + " day(s) " + time[1] + " hour(s)";
        }
        else if (substring2.contains('h'))
        {
            time = processTime('h', 'm', &substring2);
            *final = time[0] + " hour(s) " + time[1] + " minute(s)";
        }
        else if (substring2.contains('m'))
        {
            time = processTime('m', 's', &substring2);
            *final = time[0] + " minute(s) " + time[1] + " second(s)";
        }
        else
            *final = substring2.remove('s') + " second(s)";
    emit(timeChanged(&progressObject));
}

QString* WgetProcess::processTime(const QChar big, const QChar small, QString *const substring2)
{

    QString *time = new QString[2];
    time[0] = substring2->left(substring2->indexOf(big));
    time[1] = substring2->right(substring2->length() - substring2->indexOf(big) - 1).remove(small);
    if ((big == 'h') && (time[0].toInt() > 24))
    {
        time[0] = QString::number(time[0].toInt() - 24);
        time[0] += "1";
    }
    return time;
}

inline void WgetProcess::processSpeed(QString *const line)
{
    QString substring1;
    QString substring2;
    if(line->contains("100%"))
    {
        substring1 = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        substring2 = substring1.left(substring1.indexOf(" "));
        substring2 = substring2.left(substring2.indexOf("="));
    }
    else
    {
        substring1 = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        substring2 = substring1.left(substring1.indexOf(" "));
    }
    if (!(progressObject.speed == substring2))
    {
        progressObject.speed = substring2;
        emit(speedChanged(&progressObject));
    }
}

void WgetProcess::terminateWget()
{
    if (!(progressObject.status == "Paused"))
    {
        progressObject.status = "Stopped";
        terminate();
    }
    else
    {
        progressObject.status = "Stopped";
        emit(wgetStatusChanged(&progressObject));
    }
}

void WgetProcess::pauseWget()
{
    progressObject.status = "Paused";
    terminate();
}

void WgetProcess::restartWget(const QStringList args)
{
    startWget(args);
}

void WgetProcess::processFinished(int code)
{
    if (!(progressObject.status == "Paused" || progressObject.status == "Stopped"))
    {
        if (code == 0)
            progressObject.status = "Finished";
        else
            progressObject.status = "Failed";
        emit(wgetStatusChanged(&progressObject));
    }
}
