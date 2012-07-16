#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetMain->tabBar()->tabButton(0, QTabBar::RightSide)->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (downloadsCount != 0)
    {
        for(DownloadFile *file: listOfDownloads)
        {
            file->getWgetProcess()->kill();
            delete file;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog add;
    int d = add.exec();
    if ((d = QDialog::Accepted && !(add.url == "") && !(add.url == NULL)))
    {
        DownloadFile *df = new DownloadFile(add.url);
        df->tabOpen = false;
        listOfDownloads.append(df);
        downloadsCount = listOfDownloads.count();
        connect(df->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject*)), this, SLOT(setItem(WgetProgressObject*)));
        connect(df->getWgetProcess(), SIGNAL(wgetStatusChanged(QString)), this, SLOT(setItem(QString)));
        ui->tableWidget->setRowCount(downloadsCount);
        setItem(add.url, 0);
        df->download();
    }
}

void MainWindow::setItem(WgetProgressObject* cmdoutput)
{
     setItem(cmdoutput->length, 1);
}

void MainWindow::setItem(QString status, int index)
{
    QTableWidgetItem *item = new QTableWidgetItem(status);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->tableWidget->setItem(downloadsCount - 1, index, item);
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_2_clicked()
{
    listOfDownloads[ui->tableWidget->selectedItems()[0]->row()]->getWgetProcess()->kill();
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    DownloadFile *file = listOfDownloads[item->row()];
    if (file->tabOpen == false)
    {
        file->tabOpen = true;
        DetailsTab *newTab = new DetailsTab(file->getWgetProcess()->progressObject.buffer);
        if (!(file->getWgetProcess()->progressObject.status == "Finished"))
        {
            connect(file->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject*)), newTab, SLOT(outputCommand(WgetProgressObject*)));
            connect(file->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject*)), newTab, SLOT(setItem(WgetProgressObject*)));
            connect(file->getWgetProcess(), SIGNAL(wgetStatusChanged(QString)), newTab, SLOT(setItem(QString)));
        }
        QString lbl = "Download " + QString::number(item->row() + 1);
        newTab->downloadFile = file;
        ui->tabWidgetMain->addTab(newTab, lbl);
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    if (ui->tableWidget->selectedItems().count() > 0)
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_tabWidgetMain_tabCloseRequested(int index)
{
    delete ui->tabWidgetMain->widget(index);
}
