#ifndef WGETPROGRESSOBJECT_H
#define WGETPROGRESSOBJECT_H

#include <QString>
#include <QDateTime>

class WgetProgressObject
{
public:
    WgetProgressObject(){}
    int row, progressInt;
    QString length, time, rawLine, buffer, speed, status, output;
};

#endif // WGETPROGRESSOBJECT_H
