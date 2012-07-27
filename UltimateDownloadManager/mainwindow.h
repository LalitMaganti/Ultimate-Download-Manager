#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTabBar>
#include "downloadfile.h"
#include "adddialog.h"
#include "detailstab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void setProgress(WgetProgressObject *const cmdoutput);
    void setStatus(WgetProgressObject *const cmdoutput);
    void setLength(WgetProgressObject *const cmdoutput);
    void setItem(const QString status, int row, int index);
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_tableWidget_itemSelectionChanged();
    void on_tabWidgetMain_tabCloseRequested(int index);
    void on_tabWidgetMain_currentChanged(int index);
    void on_actionStop_triggered();
    void on_actionAdd_triggered();
    void on_actionQuit_triggered();
    void on_btnStartPause_clicked();

    void on_btnDelete_clicked();

private:
    Ui::MainWindow *ui;
    QList<DownloadFile*> listOfDownloads;
    int downloadsCount;
    void stopButtonChange(bool enable);
};

#endif // MAINWINDOW_H
