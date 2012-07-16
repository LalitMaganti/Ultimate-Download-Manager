#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (listOfDownloads.count() != 0)
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
        listOfDownloads.append(df);
        WgetProcess *wp = df->getWgetProcess();
        connect(wp, SIGNAL(lengthChanged(WgetProgressObject*)), this, SLOT(setItem(WgetProgressObject*)));
        connect(wp, SIGNAL(wgetStatusChanged(QString)), this, SLOT(setItem(QString)));
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
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
    ui->tableWidget->setItem(listOfDownloads.count() - 1, index, item);
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_2_clicked()
{
    listOfDownloads[ui->tableWidget->selectedItems()[0]->row()]->getWgetProcess()->kill();
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    DownloadFile *file = listOfDownloads[item->row()];
    DetailsTab *newTab = new DetailsTab(file->getWgetProcess()->progressObject.buffer);
    if (!(file->getWgetProcess()->progressObject.status == "Finished"))
        connect(file->getWgetProcess(), SIGNAL(lineRead(WgetProgressObject*)), newTab, SLOT(outputCommand(WgetProgressObject*)));
    ui->tabWidgetMain->addTab(newTab, "Download " + item->row());
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    if (ui->tableWidget->selectedItems().count() > 0)
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}
