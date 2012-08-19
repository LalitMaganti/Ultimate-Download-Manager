#include <QApplication>
#include "mainwindow.h"
#include <QColumnView>
#include <QMessageBox>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef QT_ARCH_WINDOWS
    if(!QFile::exists("wget.exe"))
    {
        QMessageBox k;
        k.setText("Wget not found");
        k.show();
        return a.exec();
    }
#endif
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
