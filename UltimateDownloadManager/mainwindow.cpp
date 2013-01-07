#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::setStatus(WgetProcess *const progressObject)
{
    processStatus(progressObject);
    ui->tableWidget->setItem(progressObject->status(), progressObject->row, Status);
}

inline void MainWindow::processStatus(WgetProcess *wpo)
{
    ui->tableWidget->processStatus(wpo);
    MiscFunctions::stopButtonChange(false, ui);
}

void MainWindow::on_pushButton_2_clicked()
{
    listOfDownloads[getTableWidgetRow()]->stopProcess();
    ui->btnStartPause->setText("Pause");
    MiscFunctions::stopButtonChange(false, ui);
    ui->btnRestart->setEnabled(false);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    int rowNumber = ui->tableWidget->getRow(item);
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
        DownloadFile *wpo = listOfDownloads[getTableWidgetRow()];
        QString status = wpo->status();
        bool enable = ((status == "Finished") || (status == "Stopped") || (status == "Failed"));
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
    if (selectedDownload->status() == "Running")
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
    delete df;
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
    listOfDownloads.removeAt(row);
    for(int i = row; i < listOfDownloads.count(); i++)
    {
        df = listOfDownloads[i];
        if (!(df->tabIndex == -1))
            ui->tabWidgetMain->setTabText(df->tabIndex, "Download " + QString::number(df->row));
        --df->row;
    }
    ui->btnRestart->setEnabled(false);
    ui->btnDelete->setEnabled(false);
}

void MainWindow::on_actionSettings_triggered()
{
    Settings settingsdialog;
    settingsdialog.exec();
}

void MainWindow::on_actionOpen_Download_Directory_triggered()
{
    QDesktopServices::openUrl(QUrl("file:///" + MiscFunctions::getOutDirectory()));
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
        return  ((DetailsTab*)ui->tabWidgetMain->currentWidget())->downloadFile->row;
}

void MainWindow::on_btnRestart_clicked()
{
    RedownloadDialog rd(listOfDownloads[getTableWidgetRow()]);
    rd.exec();
    listOfDownloads[getTableWidgetRow()]->restart();
}

void MainWindow::on_btnAdd_clicked()
{
    AddDialog add;
    int result = add.exec();
    DownloadFile *df = add.fileGlobal;
    if ((result == QDialog::Accepted) && !(add.url == ""))
    {
        listOfDownloads.append(df);
        downloadsCount = listOfDownloads.count();
        MiscFunctions::connectWgetAndMainWindow(df, this, ui);
        ui->tableWidget->setRowCount(downloadsCount);
        df->row = (ui->tableWidget->rowCount() - 1);
        ui->tableWidget->setItem(add.url, df->row, URL);
        QProgressBar *pgbar = new QProgressBar();
        ui->tableWidget->setCellWidget(df->row, Progress, pgbar);
        if (add.start)
            df->download();
        else
        {
            setStatus(df);
            ui->tableWidget->setProgress(df);
            ui->tableWidget->setFileSize(df);
            ui->tableWidget->setSpeed(df);
            ui->tableWidget->setTime(df);
            ui->btnStartPause->setText("Start");
        }
    }
    ui->tabWidgetMain->setCurrentIndex(0);
}
