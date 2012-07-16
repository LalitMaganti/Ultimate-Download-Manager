#ifndef DETAILSTAB_H
#define DETAILSTAB_H

#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include "wgetprogressobject.h"

class DetailsTab : public QWidget
{
    Q_OBJECT
public:
    DetailsTab(QString buffer, QWidget *parent = 0);
    ~DetailsTab();
private slots:
    void outputCommand(WgetProgressObject *cmdoutput);
private:
    QTextEdit *d;
    QVBoxLayout *mainLayout;
};

#endif // DETAILSTAB_H
