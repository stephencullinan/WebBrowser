#ifndef BROWSERHOMEPAGE_H
#define BROWSERHOMEPAGE_H
#include "database.h"
#include <QObject>
#include <QString>
#include <QWebEngineView>
class BrowserHomePage : public QObject
{
    Q_OBJECT
public:
    explicit BrowserHomePage(QWebEngineView *secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);
signals:
public slots:
    void loadHomePage();
    QString setHomePage();
    QString applyHomePageSetting(QString homePage);
    void setHomePageToCurrentPage();
    QString getHomePage();
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    Database* database;
    void updateHomePage(QString homePage);
};

#endif // BROWSERHOMEPAGE_H
