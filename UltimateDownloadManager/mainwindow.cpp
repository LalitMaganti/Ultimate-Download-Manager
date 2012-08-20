#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetMain->tabBarPublic->tabButton(0, QTabBar::RightSide)->hide();
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
        connect(df->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject *const)), this, SLOT(setLength(WgetProgressObject* const)));
        connect(df->getWgetProcess(), SIGNAL(wgetStatusChanged(WgetProgressObject *const)), this, SLOT(setStatus(WgetProgressObject *const)));
        connect(df->getWgetProcess(), SIGNAL(progressChanged(WgetProgressObject *const)), this, SLOT(setProgress(WgetProgressObject* const)));
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
            ui->btnStartPause->setText("Start");
        }
    }
    ui->tabWidgetMain->setCurrentIndex(0);
}

void MainWindow::setProgress(WgetProgressObject *const progressObject)
{
    if (progressObject->progress == -1)
        setItem("Unknown", progressObject->row, 3);
    else
        setItem((QString::number(progressObject->progress) + "%"), progressObject->row, 3);
}

void MainWindow::setLength(WgetProgressObject *const progressObject)
{
    setItem(progressObject->length, progressObject->row, 1);
}

void MainWindow::setStatus(WgetProgressObject *const progressObject)
{
    WgetProgressObject *wpo = progressObject;
    if (wpo->status == "Finished")
    {
        if (wpo->length == "Processing")
        {
            wpo->length = "See log for more info";
            setLength(wpo);
        }
        wpo->progress = 100;
    }
    else
    {
        wpo->progress = -1;
        wpo->length = "See log for more info";
        setLength(wpo);
    }
    setProgress(wpo);
    setItem(progressObject->status, progressObject->row, 2);
}

void MainWindow::setItem(const QString stringToWrite, int row, int index)
{
    if (ui->tableWidget->item(row, index) == 0x0)
    {
        QTableWidgetItem *item = new QTableWidgetItem(stringToWrite);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tableWidget->setItem(row, index, item);
    }
    else
    {
        ui->tableWidget->item(row, index)->setText(stringToWrite);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_2_clicked()
{
    const int row = getTableWidgetRow();
    listOfDownloads[row]->stopProcess();
    ui->btnStartPause->setText("Pause");
    stopButtonChange(false);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    const int rowNumber = item->row();
    DownloadFile *df = listOfDownloads[rowNumber];
    if (df->tabIndex == -1)
    {
        DetailsTab *const newTab = new DetailsTab(listOfDownloads[rowNumber]);
        QString lbl = "Download " + QString::number((rowNumber + 1));
        ui->tabWidgetMain->addTab(newTab, lbl);
        df->tabIndex = ui->tabWidgetMain->count() - 1;
    }
    ui->tabWidgetMain->setCurrentIndex(df->tabIndex);
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    if (ui->tableWidget->selectedItems().count() > 0)
    {
        const int row = ui->tableWidget->currentRow();
        DownloadFile *df = listOfDownloads[row];
        bool enable = ((df->progressObject->status == "Finished") || (df->progressObject->status == "Stopped") || (df->progressObject->status == "Failed"));
        stopButtonChange(!enable);
    }
}

void MainWindow::on_tabWidgetMain_tabCloseRequested(int index)
{
    delete ui->tabWidgetMain->widget(index);
}

void MainWindow::stopButtonChange(bool enable)
{
    ui->pushButton_2->setEnabled(enable);
    ui->btnStartPause->setEnabled(enable);
    ui->btnDelete->setEnabled(!enable);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_btnStartPause_clicked()
{
    const int row = getTableWidgetRow();
    DownloadFile *selectedDownload = listOfDownloads[row];
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
        ui->tabWidgetMain->removeTab(tabLocation);
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
    if (!tabLocation == -1)
    {
        for(int i = tabLocation; i < ui->tabWidgetMain->count(); i++)
        {
            df = listOfDownloads[i];
            if (!(df->tabIndex == -1))
                --df->tabIndex;
        }
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

int MainWindow::getTableWidgetRow()
{
    int selectedTab = ui->tabWidgetMain->currentIndex();
    int row;
    if (selectedTab == 0)
        row = ui->tableWidget->currentRow();
    else
        row = ((DetailsTab*)ui->tabWidgetMain->currentWidget())->downloadFile->progressObject->row;
    return row;
}
