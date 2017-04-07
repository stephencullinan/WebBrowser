#ifndef BROWSERNAVIGATION_H
#define BROWSERNAVIGATION_H
#include "database.h"
#include <QObject>
#include <QWebEngineView>
class BrowserNavigation : public QObject
{
    Q_OBJECT
public:
    explicit BrowserNavigation(QWebEngineView* secondWebEngineView,
                               QWebEngineView *webEngineView, QObject *parent = 0);
signals:
public slots:
    void goBackward();
    void goForward();
    void refresh();
    void halt();
    void displayBrowser();
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERNAVIGATION_H
