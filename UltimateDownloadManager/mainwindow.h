#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QDir>
#include <QMainWindow>
#include <QTableWidget>
#include <QTabBar>

#include "aboutdialog.h"
#include "adddialog.h"
#include "detailstab.h"
#include "downloadfile.h"
#include "redownloaddialog.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void setStatus(WgetProcess *cmdoutput);

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
    void on_btnRestart_clicked();
    void on_btnAdd_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    QList<DownloadFile*> listOfDownloads;
    int downloadsCount;
    int getTableWidgetRow();
};

#endif // MAINWINDOW_H