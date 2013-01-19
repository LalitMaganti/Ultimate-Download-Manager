#include "wgetprocess.h"

WgetProcess::WgetProcess() : QProcess() {
    setReadChannel(QProcess::StandardError);
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readWgetLine()));
    connect(this, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    writeprogressInt(0);
    writeStatus("Pending");
    writeLength("Pending");
    writeSpeed("Pending");
    writeTime("Pending");
    writeOutput("Pending");
    buffer = "Download not started";
}

void WgetProcess::startWget(QStringList args) {
    writeStatus("Running");
    writeLength("Processing");
    writeSpeed("Processing");
    writeTime("Processing");
    writeOutput("Processing");
    buffer = "";
    start("wget", args);
}

void WgetProcess::readWgetLine() {
    if(canReadLine()) {
        QString line = readLine();
        writerawLine(line);
        buffer += line;
        processRawData(&line);
    }
}

inline void WgetProcess::processLength(QString *line) {
    if (line->contains("unspecified")) {
        writeLength("Unknown - HTML file?");
        //SHOULD BE -1 - IMPLEMENT ERROR CATCH IN FUTURE
        writeprogressInt(100);
        writeSpeed("Unknown");
        writeTime("Unknown");
    } else {
        QString substring1 = line->right(line->length() - line->indexOf("(") - 1);
        substring1 = substring1.left(substring1.indexOf(")"));
        writeLength(substring1);
    }
}

inline void WgetProcess::processProgress(QString *line) {
    QString substring1 = line->left(line->lastIndexOf('%'));
    int substring2 = substring1.right(substring1.length() - substring1.lastIndexOf('.')).remove('.').trimmed().toInt();
    if (!(progressInt == substring2)) {
        writeprogressInt(substring2);
    }
}

void WgetProcess::processRawData(QString *line) {
    if(line->contains("Length: ")) {
        processLength(line);
    } else if(line->contains("Saving to:")) {
        writeOutput(line->right(line->length() - line->indexOf('`')).remove('\'').remove('`'));
    } else if(line->contains('%') && line->contains(". .") && (!(length == "Unknown - HTML file?"))) {
        processProgress(line);
        processTime(line);
        processSpeed(line);
    }
}

inline void WgetProcess::processTime(QString *line) {
    QString substring1, substring2;
    if(line->contains("100%")) {
        substring1 = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        substring2 = substring1.left(substring1.indexOf(" "));
        substring2 = substring2.right(substring2.length() - substring2.indexOf("=")).remove("=");
    } else {
        substring2 = line->right(line->length() - line->lastIndexOf('%')).remove('%').trimmed();
        substring2 = substring2.remove(0, 5).trimmed();
    }
    QString final;
    QString *time;
    if (substring2.contains('d')) {
        time = processTime('d', 'h', &substring2);
        final = time[0] + " day(s) " + time[1] + " hour(s)";
    } else if (substring2.contains('h')) {
        time = processTime('h', 'm', &substring2);
        final = time[0] + " hour(s) " + time[1] + " minute(s)";
    } else if (substring2.contains('m')) {
        time = processTime('m', 's', &substring2);
        final = time[0] + " minute(s) " + time[1] + " second(s)";
    } else {
        final = substring2.remove('s') + " second(s)";
    }
    writeTime(final);
}

QString* WgetProcess::processTime(QChar big, QChar small, QString *substring2) {
    QString *time = new QString[2];
    time[0] = substring2->left(substring2->indexOf(big));
    time[1] = substring2->right(substring2->length() - substring2->indexOf(big) - 1).remove(small);
    if ((big == 'h') && (time[0].toInt() > 24)) {
        time[0] = QString::number(time[0].toInt() - 24);
        time[0] += "1";
    }
    return time;
}

inline void WgetProcess::processSpeed(QString *line) {
    QString substring, speed;
    if(line->contains("100%")) {
        substring = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        speed = substring.left(substring.indexOf(" "));
        speed = speed.left(speed.indexOf("="));
    } else {
        substring = line->right(line->length() - line->lastIndexOf('%')).trimmed().remove("%").trimmed();
        speed = substring.left(substring.indexOf(" "));
    }
    if (!(speed == speed)) {
        writeSpeed(speed);
    }
}

void WgetProcess::terminateWget() {
    writeStatus("Stopped");
    if (!(status == "Paused")) {
        terminate();
    }
}

void WgetProcess::pauseWget() {
    writeStatus("Paused");
    terminate();
}

void WgetProcess::restartWget(QStringList args) {
    startWget(args);
}

void WgetProcess::processFinished(int code) {
    if (!(status == "Paused" || status == "Stopped")) {
        if (code == 0) {
            writeStatus("Finished");
        } else {
            writeStatus("Failed");
        }
    }
}

inline void WgetProcess::writeprogressInt(int write) {
    progressInt = write;
    emit(progressChanged(write, row));
}

inline void WgetProcess::writeSpeed(QString write) {
    speed = write;
    emit(speedChanged(write, row));
}

inline void WgetProcess::writeTime(QString write) {
    time = write;
    emit(timeChanged(write, row));
}

inline void WgetProcess::writeLength(QString write) {
    length = write;
    emit(lengthChanged(write, row));
}

inline void WgetProcess::writeStatus(QString write) {
    status = write;
    emit(statusChanged(this));
}

inline void WgetProcess::writeOutput(QString write) {
    output = write;
    emit(outputChanged(write, row));
}

inline void WgetProcess::writerawLine(QString write) {
    rawLine = write;
    emit(rawLineChanged(write, row));
}
