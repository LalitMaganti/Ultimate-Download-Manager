#ifndef WGETPROGRESSOBJECT_H
#define WGETPROGRESSOBJECT_H

#include <QString>
#include <QDateTime>

class WgetProgressObject
{
public:
    WgetProgressObject(){}
    QString length;
    QString progress;
    QString time;
    QString rawLine;
    QString buffer;
    QString status;
    int row;
    QString speed;
};

#endif // WGETPROGRESSOBJECT_H
