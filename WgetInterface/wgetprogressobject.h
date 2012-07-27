#ifndef WGETPROGRESSOBJECT_H
#define WGETPROGRESSOBJECT_H

#include <QString>
#include <QDateTime>

class WgetProgressObject
{
public:
    WgetProgressObject(){}
    QString length;
    int progress;
    QDateTime time;
    QString rawLine;
    QString buffer;
    QString status;
    int row;
};

#endif // WGETPROGRESSOBJECT_H
