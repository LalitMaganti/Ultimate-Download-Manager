#include "wgetprocess.h"

WgetProcess::WgetProcess()
{
    setReadChannel(QProcess::StandardError);
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readWgetLine()));
    connect(this, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    writeprogressInt(0);
    writestatus("Pending");
    writelength("Pending");
    writespeed("Pending");
    writetime("Pending");
    writeoutput("Pending");
    buffer = "Download not started";
}

void WgetProcess::startWget(QStringList args)
{
    m_status = "Running";
    m_length = "Processing";
    m_speed = "Processing";
    m_time = "Processing";
    m_output = "Processing";
    buffer = "";
    //emit(lengthChanged(this));
    //emit(statusChanged(this));
    //emit(speedChanged(this));
    //emit(timeChanged(this));
    //emit(progressChanged(this));
    //emit(outputChanged(this));
    start("wget", args);
}

void WgetProcess::readWgetLine()
{
    if(canReadLine())
    {
        QString line = readLine();
        m_rawLine = line;
        buffer += line;
        processRawData(&line);
        //emit lineRead(this);
    }
}

inline void WgetProcess::processLength(QString *const line)
{
    if (line->contains("unspecified"))
    {
        m_length = "Unknown - HTML file?";
        //SHOULD BE -1 - IMPLEMENT ERROR CATCH IN FUTURE
        m_progressInt = 100;
        m_speed = "Unknown";
        m_time = "Unknown";
        //emit(progressChanged(this));
        //emit(speedChanged(this));
        //emit(timeChanged(this));
    }
    else
    {
        QString substring1 = line->right(line->length() - line->indexOf("(") - 1);
        substring1 = substring1.left(substring1.indexOf(")"));
        m_length = substring1;
    }
    //emit(lengthChanged(this));
}

inline void WgetProcess::processProgress(QString *const line)
{

    QString substring1 = line->left(line->lastIndexOf('%'));
    int substring2 = substring1.right(substring1.length() - substring1.lastIndexOf('.')).remove('.').trimmed().toInt();
    if (!(m_progressInt == substring2))
    {
        m_progressInt = substring2;
        //emit(progressChanged(this));
    }
}

void WgetProcess::processRawData(QString *const line)
{
    if(line->contains("Length: "))
        processLength(line);
    else if(line->contains("Saving to:"))
    {
        m_output = line->right(line->length() - line->indexOf('`')).remove('\'').remove('`');
        //emit(outputChanged(this));

    }
    else if(line->contains('%') && line->contains(". .") && (!(m_length == "Unknown - HTML file?")))
    {
        processProgress(line);
        processTime(line);
        processSpeed(line);
    }
}

inline void WgetProcess::processTime(QString *const line)
{
    QString substring1, substring2;
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
        m_time = "";
        QString *final = &m_time;
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
    //emit(timeChanged(this));
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
    QString substring1, substring2;
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
    if (!(m_speed == substring2))
    {
        m_speed = substring2;
        //emit(speedChanged(this));
    }
}

void WgetProcess::terminateWget()
{
    if (!(m_status == "Paused"))
    {
        m_status = "Stopped";
        terminate();
    }
    else
    {
        m_status = "Stopped";
        //emit(statusChanged(this));
    }
}

void WgetProcess::pauseWget()
{
    m_status = "Paused";
    terminate();
}

void WgetProcess::restartWget(const QStringList args)
{
    startWget(args);
}

void WgetProcess::processFinished(int code)
{
    if (!(m_status == "Paused" || m_status == "Stopped"))
    {
        if (code == 0)
            m_status = "Finished";
        else
            m_status = "Failed";
        //emit(statusChanged(this));
    }
}

int WgetProcess::progressInt()
{
    return m_progressInt;
}

QString WgetProcess::speed()
{
    return m_speed;
}

QString WgetProcess::time()
{
    return m_time;
}

QString WgetProcess::length()
{
    return m_length;
}

QString WgetProcess::status()
{
    return m_status;
}

QString WgetProcess::output()
{
    return m_output;
}

QString WgetProcess::rawLine()
{
    return m_rawLine;
}

void WgetProcess::writeprogressInt(int write)
{
    m_progressInt = write;
}

void WgetProcess::writespeed(QString write)
{
    m_speed = write;
}

void WgetProcess::writetime(QString write)
{
    m_time = write;
}

void WgetProcess::writelength(QString write)
{
    m_length = write;
}

void WgetProcess::writestatus(QString write)
{
    m_status = write;
}

void WgetProcess::writeoutput(QString write)
{
    m_output = write;
}

void WgetProcess::writerawLine(QString write)
{
    m_rawLine = write;
}
