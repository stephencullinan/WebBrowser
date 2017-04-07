#include "browser.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QtSql/QtSql>
#include <QWebEngineView>
#include <QLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget* aWidget = new QWidget();
    Browser* aBrowser = new Browser(aWidget);
    w.setCentralWidget(aBrowser->getParentWidget());
    w.showMaximized();
    return a.exec();
}
