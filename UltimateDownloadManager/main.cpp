#include <QApplication>
#include <QColumnView>
#include <QMessageBox>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
#ifdef QT_ARCH_WINDOWS
    if(!QFile::exists("wget.exe")) {
        QMessageBox k;
        k.setText("wget not found in the same directory as the program!");
        k.show();
        return a.exec();
    }
#endif
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
