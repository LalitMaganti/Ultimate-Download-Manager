#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTabBar>
#include <QDir>
#include <QDesktopServices>
#include <QProgressBar>

#include "downloadfile.h"
#include "dialogheader/adddialog.h"
#include "detailstab.h"
#include "dialogheader/settings.h"
#include "dialogheader/aboutdialog.h"
#include "miscstuff.h"
#include "dialogheader/redownloaddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_2_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_tableWidget_itemSelectionChanged();
    void on_tabWidgetMain_tabCloseRequested(int index);
    void on_actionQuit_triggered();
    void on_btnStartPause_clicked();
    void on_btnDelete_clicked();
    void on_actionSettings_triggered();
    void on_actionOpen_Download_Directory_triggered();
    void on_actionAbout_triggered();
    void setProgress(WgetProgressObject *const cmdoutput);
    void setStatus(WgetProgressObject *const cmdoutput);
    void setFileSize(WgetProgressObject *const cmdoutput);
    void setSpeed(WgetProgressObject *const cmdoutput);
    void setTime(WgetProgressObject *const cmdoutput);
    void setOutput(WgetProgressObject *const cmdoutput);
    void on_btnRestart_clicked();
    void on_btnAdd_clicked();

private:
    void setItem(const QString status, int row, int index);
    void setItem(const int status, int row);
    Ui::MainWindow *ui;
    QList<DownloadFile*> listOfDownloads;
    int downloadsCount;
    void stopButtonChange(bool enable);
    int getTableWidgetRow();
    int getTableWidgetRow(QTableWidgetItem *item);
    void processStatus(WgetProgressObject *wpo);
};

#endif // MAINWINDOW_H
