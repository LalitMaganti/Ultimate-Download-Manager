#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if QT_VERSION >= 0x050000
    // Only available in QT5
    ui->tabWidgetMain->setTabsClosable(true);
    ui->tabWidgetMain->tabBar()->tabButton(0, QTabBar::RightSide)->hide();
#endif
}

MainWindow::~MainWindow()
{
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
            if (!(file->progressObject->status == "Finished"))
                file->stopProcess();
            delete file;
        }
    }
    for(int tabIndex = 1; tabIndex < ui->tabWidgetMain->count(); tabIndex++)
    {
        delete ui->tabWidgetMain->widget(tabIndex);
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog *add = new AddDialog();
    int d = add->exec();
    DownloadFile *df = add->fileGlobal;
    if ((d = QDialog::Accepted && !(add->url == "") && !(add->url == NULL)))
    {
        listOfDownloads.append(df);
        downloadsCount = listOfDownloads.count();
        connect(df->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject*)), this, SLOT(setItem(WgetProgressObject*)));
        connect(df->getWgetProcess(), SIGNAL(wgetStatusChanged(QString)), this, SLOT(setItem(QString)));
        connect(df->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject*)), this, SLOT(setProgress(WgetProgressObject*)));
        ui->tableWidget->setRowCount(downloadsCount);
        setItem(add->url, 0);
        df->download();
    }
    delete add;
}

void MainWindow::setProgress(WgetProgressObject* cmdoutput)
{
    if (cmdoutput->progress == -1)
        setItem("Unknown", 3);
    else
        setItem((QString::number(cmdoutput->progress) + "%"), 3);
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
    listOfDownloads[ui->tableWidget->selectedItems()[0]->row()]->stopProcess();
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    int rowNumber = item->row();
    DownloadFile *file = listOfDownloads[rowNumber];
    if (!(file->tabOpen))
    {
        file->tabOpen = true;
        DetailsTab *newTab = new DetailsTab(file->progressObject->buffer);
        if (!(file->progressObject->status == "Finished"))
        {
            connect(file->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject*)), newTab, SLOT(outputCommand(WgetProgressObject*)));
            connect(file->getWgetProcess(), SIGNAL(lengthChanged(WgetProgressObject*)), newTab, SLOT(setItem(WgetProgressObject*)));
            connect(file->getWgetProcess(), SIGNAL(wgetStatusChanged(QString)), newTab, SLOT(setItem(QString)));
        }
        else
        {
            setItem(file->progressObject->status);
            setItem(file->progressObject);
        }
        QString lbl = "Download " + QString::number((rowNumber + 1));
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

void MainWindow::on_tabWidgetMain_currentChanged(int index)
{
    if (index == 0)
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}
