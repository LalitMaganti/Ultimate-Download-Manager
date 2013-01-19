#ifndef DOWNLOADTABWIDGET_H
#define DOWNLOADTABWIDGET_H

#include <QTabBar>
#include <QTabWidget>

class DownloadTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit DownloadTabWidget(QWidget *parent = 0) : QTabWidget(parent)
    {
    }

    void addTab(QWidget *parent, QString k) {
        QTabWidget::addTab(parent, k);
        if(count() == 1) {
            tabBar()->setTabButton(0, QTabBar::RightSide, 0);
        }
    }
};

#endif // DOWNLOADTABWIDGET_H