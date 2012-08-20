#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetMain->tabBarPublic->tabButton(0, QTabBar::RightSide)->hide();
    ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    for(int tabIndex = 1; tabIndex < ui->tabWidgetMain->count(); tabIndex++)
        delete ui->tabWidgetMain->widget(tabIndex);
    if (downloadsCount != 0)
    {
#ifndef QT_ARCH_WINDOWS
        for(DownloadFile *file: listOfDownloads)
#else
        for each(DownloadFile *file in listOfDownloads)
#endif
                delete file;
    }
    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    {
        for(int row = 0; row < ui->tableWidget->rowCount(); row++)
            delete ui->tableWidget->item(row, column);
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog add;
    int result = add.exec();
    DownloadFile *const df = add.fileGlobal;
    if ((result == QDialog::Accepted) && !(add.url == ""))
    {
        listOfDownloads.append(df);
        downloadsCount = listOfDownloads.count();
        MiscFunctions::connectWgetAndMainWindow(df->getWgetProcess(), this);
        ui->tableWidget->setRowCount(downloadsCount);
        df->progressObject->row = (ui->tableWidget->rowCount() - 1);
        setItem(add.url, df->progressObject->row, 0);
        if (add.start)
            df->download();
        else
        {
            setStatus(df->progressObject);
            setProgress(df->progressObject);
            setLength(df->progressObject);
            setSpeed(df->progressObject);
            setTime(df->progressObject);
            ui->btnStartPause->setText("Start");
        }
    }
    ui->tabWidgetMain->setCurrentIndex(0);
}

void MainWindow::setLength(WgetProgressObject *const progressObject)
{
    setItem(progressObject->length, progressObject->row, 1);
}

void MainWindow::setStatus(WgetProgressObject *const progressObject)
{
    processStatus(progressObject);
    setItem(progressObject->status, progressObject->row, 2);
}

void MainWindow::setProgress(WgetProgressObject *const progressObject)
{
    setItem(progressObject->progress, progressObject->row, 3);
}

void MainWindow::setSpeed(WgetProgressObject *const progressObject)
{
    setItem(progressObject->speed, progressObject->row, 4);
}

void MainWindow::setTime(WgetProgressObject *const progressObject)
{
    setItem(progressObject->time, progressObject->row, 5);
}

inline void MainWindow::processStatus(WgetProgressObject *wpo)
{
    int row = wpo->row;
    if (wpo->status == "Finished")
    {
        if (wpo->length == "Processing")
        {
            setItem("See log for more info", row, 1);
            setItem("Download finished", row, 5);
        }
        if(wpo->length == "0s second(s)")
        setItem("100%",row, 3);
        MiscFunctions::stopButtonChange(false, ui);
    }
    else if(wpo->status == "Failed")
    {
        setItem("See log for more info", row, 1);
        setItem("Unknown", row, 3);
        setItem("Unknown", row, 4);
        setItem("Download failed", row, 5);
        MiscFunctions::stopButtonChange(false, ui);
    }
    ui->tableWidget->resizeColumnsToContents();
}

inline void MainWindow::setItem(const QString stringToWrite, int row, int index)
{
    if (ui->tableWidget->item(row, index) == 0x0)
    {
        QTableWidgetItem *item = new QTableWidgetItem(stringToWrite);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tableWidget->setItem(row, index, item);
        ui->tableWidget->resizeColumnsToContents();
    }
    else
        ui->tableWidget->item(row, index)->setText(stringToWrite);
}

void MainWindow::on_pushButton_2_clicked()
{
    listOfDownloads[getTableWidgetRow()]->stopProcess();
    ui->btnStartPause->setText("Pause");
    MiscFunctions::stopButtonChange(false, ui);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    const int rowNumber = getTableWidgetRow();
    DownloadFile *df = listOfDownloads[rowNumber];
    if (df->tabIndex == -1)
    {
        DetailsTab *const newTab = new DetailsTab(listOfDownloads[rowNumber]);
        ui->tabWidgetMain->addTab(newTab, "Download " + QString::number(rowNumber + 1));
        df->tabIndex = ui->tabWidgetMain->count() - 1;
    }
    ui->tabWidgetMain->setCurrentIndex(df->tabIndex);
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    if (ui->tableWidget->selectedItems().count() > 0)
    {
        WgetProgressObject *wpo = listOfDownloads[getTableWidgetRow()]->progressObject;
        bool enable = ((wpo->status == "Finished") || (wpo->status == "Stopped") || (wpo->status == "Failed"));
        MiscFunctions::stopButtonChange(!enable, ui);
    }
}

void MainWindow::on_tabWidgetMain_tabCloseRequested(int index)
{
    delete ui->tabWidgetMain->widget(index);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_btnStartPause_clicked()
{
    DownloadFile *selectedDownload = listOfDownloads[getTableWidgetRow()];
    if (selectedDownload->progressObject->status == "Running")
    {
        selectedDownload->pause();
        ui->btnStartPause->setText("Start");
    }
    else
    {
        selectedDownload->start();
        ui->btnStartPause->setText("Pause");
    }
}

void MainWindow::on_btnDelete_clicked()
{
    const int row = getTableWidgetRow();
    DownloadFile *df = listOfDownloads[row];
    const int tabLocation = df->tabIndex;
    if (!(tabLocation == -1))
    {
        ui->tabWidgetMain->removeTab(tabLocation);
        for(int i = tabLocation; i < ui->tabWidgetMain->count(); i++)
        {
            df = listOfDownloads[i];
            if (!(df->tabIndex == -1))
                --df->tabIndex;
        }
    }
    ui->tableWidget->removeRow(row);
    delete df;
    listOfDownloads.removeAt(row);
    for(int i = row; i < listOfDownloads.count(); i++)
    {
        df = listOfDownloads[i];
        if (!(df->tabIndex == -1))
            ui->tabWidgetMain->tabBarPublic->setTabText(df->tabIndex, "Download " + QString::number(df->progressObject->row));
        --df->progressObject->row;
    }
    if (ui->tableWidget->rowCount() == 0)
        ui->btnDelete->setEnabled(false);
}

void MainWindow::on_actionSettings_triggered()
{
    Settings settingsdialog;
    settingsdialog.exec();
}

void MainWindow::on_actionOpen_Download_Directory_triggered()
{
    QSettings settings;
    QString path = QDir::toNativeSeparators(settings.value("download/savelocation", QDir::homePath()).toString());
    QDesktopServices::openUrl(QUrl("file:///" + path));
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about;
    about.exec();
}

inline int MainWindow::getTableWidgetRow()
{
    int selectedTab = ui->tabWidgetMain->currentIndex();
    if (selectedTab == 0)
        return  ui->tableWidget->currentRow();
    else
        return  ((DetailsTab*)ui->tabWidgetMain->currentWidget())->downloadFile->progressObject->row;
}
