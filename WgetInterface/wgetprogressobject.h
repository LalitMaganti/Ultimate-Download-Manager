#ifndef WGETPROGRESSOBJECT_H
#define WGETPROGRESSOBJECT_H

#include <QString>

class WgetProgressObject
{
public:
    WgetProgressObject(){}
    QString length;
    int progress;
    QString rawLine;
    QString buffer;
    QString status;
};

#endif // WGETPROGRESSOBJECT_H
