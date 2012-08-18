#ifndef DOWNLOADTABWIDGET_H
#define DOWNLOADTABWIDGET_H

#include <QTabWidget>

class DownloadTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    DownloadTabWidget(QWidget *parent = 0){tabBarPublic = tabBar();parent++;}
    QTabBar *tabBarPublic;
};

#endif // DOWNLOADTABWIDGET_H
