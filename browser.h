#ifndef BROWSER_H
#define BROWSER_H
#include "database.h"
#include <QJsonArray>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QTableWidget>
#include <QWebEngineView>
class Browser : public QMainWindow
{
    Q_OBJECT
public:
    explicit Browser(QWidget* parent = 0);
    void addBrowser();
    QMenuBar* createMenu();
    QWidget* getParentWidget();
    QMainWindow* getParentWindow();
    void openHomePage();
signals:
public slots:
    void updateProgressBar(int currentProgress);
    void loadFinished();
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    QWidget* parentWidget;
    QProgressBar* progressBar;
    Database* database;
};
#endif // BROWSER_H
