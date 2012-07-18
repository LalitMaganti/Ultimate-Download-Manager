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
    {
        delete ui->tabWidgetMain->widget(tabIndex);
    }
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->tableWidget->columnCount(); column++)
        {
            delete ui->tableWidget->item(row, column);
        }
    }
    if (downloadsCount != 0)
    {
        for(DownloadFile *file: listOfDownloads)
        {
            delete file;
        }
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog *const add = new AddDialog();
    int d = add->exec();
    DownloadFile *const df = add->fileGlobal;
    if ((d = QDialog::Accepted && !(add->url == "") && !(add->url == NULL)))
    {
        listOfDownloads.append(df);
        downloadsCount = listOfDownloads.count();
        connect(df->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject *const)), this, SLOT(setItem(WgetProgressObject* const)));
        connect(df->getWgetProcess(), SIGNAL(wgetStatusChanged(QString)), this, SLOT(setItem(const QString)));
        connect(df->getWgetProcess(), SIGNAL(progressChanged(WgetProgressObject *const)), this, SLOT(setProgress(WgetProgressObject* const)));
        connect(df->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject *const)), this, SLOT(setProgress(WgetProgressObject* const)));
        ui->tableWidget->setRowCount(downloadsCount);
        setItem(add->url, 0);
        df->download();
    }
    delete add;
}

void MainWindow::setProgress(WgetProgressObject *const progressObject)
{
    if (progressObject->progress == -1)
        setItem("Unknown", 3);
    else
        setItem((QString::number(progressObject->progress) + "%"), 3);
}

void MainWindow::setItem(WgetProgressObject *const progressObject)
{
     setItem(progressObject->length, 1);
}

void MainWindow::setItem(const QString stringTowWrite, int index)
{
    delete ui->tableWidget->item(downloadsCount - 1, index);
    QTableWidgetItem *item = new QTableWidgetItem(stringTowWrite);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->tableWidget->setItem(downloadsCount - 1, index, item);
    ui->tableWidget->resizeColumnsToContents();
    if (stringTowWrite == "Finished")
        stopButtonChange(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    listOfDownloads[ui->tableWidget->selectedItems()[0]->row()]->stopProcess();
    stopButtonChange(false);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    const int rowNumber = item->row();
    if (!(listOfDownloads[rowNumber]->tabOpen))
    {
        DetailsTab *const newTab = new DetailsTab(listOfDownloads[rowNumber]);
        QString lbl = "Download " + QString::number((rowNumber + 1));
        ui->tabWidgetMain->addTab(newTab, lbl);
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    DownloadFile *df = listOfDownloads[ui->tableWidget->selectedItems()[0]->row()];
    if ((ui->tableWidget->selectedItems().count() > 0) && !(df->progressObject->status == "Finished"))
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
    DownloadFile *df = listOfDownloads[ui->tableWidget->selectedItems()[0]->row()];
    if (index == 0  && !(df->progressObject->status == "Finished"))
        stopButtonChange(true);
    else
        stopButtonChange(false);
}

void MainWindow::on_actionStop_triggered()
{
    on_pushButton_2_clicked();
}

void MainWindow::stopButtonChange(bool enable)
{
    ui->pushButton_2->setEnabled(enable);
    ui->actionStop->setEnabled(enable);
}

void MainWindow::on_actionAdd_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
