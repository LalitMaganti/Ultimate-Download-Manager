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
        for(DownloadFile *file: listOfDownloads)
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
     setItem(progressObject->status, progressObject->row, 2);
}

void MainWindow::setItem(const QString stringToWrite, int row, int index)
{
    delete ui->tableWidget->item(row, index);
    QTableWidgetItem *item = new QTableWidgetItem(stringToWrite);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    ui->tableWidget->setItem(row, index, item);
    ui->tableWidget->resizeColumnsToContents();
    if (stringToWrite == "Finished")
    {
        stopButtonChange(false);
        ui->btnDelete->setEnabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    const int row = ui->tableWidget->selectedItems()[0]->row();
    listOfDownloads[row]->stopProcess();
    ui->btnStartPause->setText("Pause");
    stopButtonChange(false);
    ui->btnDelete->setEnabled(true);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    const int rowNumber = item->row();
    DownloadFile *df = listOfDownloads[rowNumber];
    if (df->tabRow == -1)
    {
        DetailsTab *const newTab = new DetailsTab(listOfDownloads[rowNumber]);
        QString lbl = "Download " + QString::number((rowNumber + 1));
        ui->tabWidgetMain->addTab(newTab, lbl);
        df->tabRow = ui->tabWidgetMain->count();
        ui->tabWidgetMain->setCurrentIndex(df->tabRow);
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    const int row = ui->tableWidget->selectedItems()[0]->row();
    DownloadFile *df = listOfDownloads[row];
    if ((ui->tableWidget->selectedItems().count() > 0) && !(df->progressObject->status == "Finished") && !(df->progressObject->status == "Stopped"))
        stopButtonChange(true);
    else
        stopButtonChange(false);
}

void MainWindow::on_tabWidgetMain_tabCloseRequested(int index)
{
    delete ui->tabWidgetMain->widget(index);
}

void MainWindow::on_tabWidgetMain_currentChanged(int index)
{
    const int row = ui->tableWidget->selectedItems()[0]->row();
    DownloadFile *df = listOfDownloads[row];
    if (index == 0  && !(df->progressObject->status == "Finished") && !(df->progressObject->status == "Stopped"))
        stopButtonChange(true);
    else
    {
        stopButtonChange(false);
        ui->btnDelete->setEnabled(true);
    }
}

void MainWindow::on_actionStop_triggered()
{
    on_pushButton_2_clicked();
}

void MainWindow::stopButtonChange(bool enable)
{
    ui->pushButton_2->setEnabled(enable);
    ui->actionStop->setEnabled(enable);
    ui->btnStartPause->setEnabled(enable);
}

void MainWindow::on_actionAdd_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_btnStartPause_clicked()
{
    const int row = ui->tableWidget->selectedItems()[0]->row();
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
    const int row = ui->tableWidget->selectedItems()[0]->row();
    delete listOfDownloads[row];
    listOfDownloads.removeAt(row);
    ui->tableWidget->removeRow(row - 1);
    ui->tableWidget->setRowCount(0);
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
