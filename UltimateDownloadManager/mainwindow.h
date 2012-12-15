#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTabBar>
#include <QDir>
#include <QDesktopServices>

#include "downloadfile.h"
#include "dialogs/adddialog.h"
#include "uicomponents/detailstab.h"
#include "dialogs/settings.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/redownloaddialog.h"

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
    void processStatus(WgetProgressObject *wpo);
    void setStatus(WgetProgressObject *const cmdoutput);
    void on_btnRestart_clicked();
    void on_btnAdd_clicked();

private:
    Ui::MainWindow *ui;
    QList<DownloadFile*> listOfDownloads;
    int downloadsCount;
    void stopButtonChange(bool enable);
    int getTableWidgetRow();
};

#endif // MAINWINDOW_H
