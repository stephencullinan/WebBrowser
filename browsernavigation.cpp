#include "browsernavigation.h"
#include <QWebEngineView>
BrowserNavigation::BrowserNavigation(QWebEngineView* secondWebEngineView,
                                     QWebEngineView* webEngineView,
                                     QObject *parent) : QObject(parent)
{
    this->webEngineView = webEngineView;
    this->secondWebEngineView = secondWebEngineView;
}
void BrowserNavigation::goBackward()
{
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
    secondWebEngineView->back();
}
void BrowserNavigation::goForward()
{
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
    secondWebEngineView->forward();
}
void BrowserNavigation::refresh()
{
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
    secondWebEngineView->reload();
}
void BrowserNavigation::halt()
{
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
    secondWebEngineView->stop();
}
void BrowserNavigation::displayBrowser()
{
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
}
