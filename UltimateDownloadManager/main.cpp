#include <QApplication>
#include "mainwindow.h"
#include <QColumnView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
