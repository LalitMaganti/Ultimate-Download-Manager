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
    else if(line->contains('%') && line->contains(". .") && (!(progressObject.length == "Unknown - HTML file?")))
    {
        QString substring1 = line->left(line->lastIndexOf('.'));
        substring1 = substring1.right(substring1.length() - substring1.lastIndexOf('.'));
        substring1 = substring1.left(substring1.lastIndexOf('%'));
        substring1 = substring1.remove('.').trimmed();
        progressObject.progress = substring1.toInt();
        QString substring2 = line->right(line->length() - line->lastIndexOf('.'));
        substring2 = substring2.remove(0, 4).trimmed();
        QDateTime time;
        if (substring2.contains('d'))
        {
            qDebug() << time.fromString(processTime('d', 'h', &substring2), "ddhh").toString("dd:hh:mm:ss");
        }
        else if (substring2.contains('h'))
        {
            qDebug() << time.fromString(processTime('h', 'm', &substring2), "dhhmm").toString("hh:mm:ss");
        }
        else if (substring2.contains('m'))
        {
            qDebug() << time.fromString(processTime('m', 's', &substring2), "mmss").toString("mm:ss");
        }
    }
}

QString WgetProcess::processTime(QChar big, QChar small, QString *substring2)
{
    QString bigstring = substring2->left(substring2->indexOf(big));
    QString smallstring = substring2->right(substring2->length() - substring2->indexOf(big) - 1).remove(small);
    if ((big == 'h') && (bigstring.toInt() > 24))
    {
        bigstring = QString::number(bigstring.toInt() - 24);
        bigstring += "1";
    }
    qDebug() << bigstring + smallstring;
    return (bigstring + smallstring);
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
