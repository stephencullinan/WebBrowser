#ifndef BROWSERFEEDS_H
#define BROWSERFEEDS_H
#include "accordion.h"
#include <QMap>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QWebEngineView>
#include <QVector>
class BrowserFeeds : public QObject
{
    Q_OBJECT
public:
    explicit BrowserFeeds(QWebEngineView *secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);

signals:

public slots:
    QString downloadFeeds(QString url);
    void retrieveFeeds(QNetworkReply* aNetworkReply);
    QString getFeedsAccordion();
    QString createNewFeed();
    QString saveCreatedFeed(QString feedUrl, QString feedTitle);
    QString viewFeedsAsTiles();
private:
    QVector<QString> extractElementFromTag(QString fileText, QString tag);
    QMap<QString, QString> extractElementsFromTag(QString tagText, QVector<QString> requiredTags);
    QString removeCDataTag(QString input);
    QWebEngineView* webEngineView;
    QWebEngineView* secondWebEngineView;
    Accordion* feedsAccordion;
};

#endif // BROWSERFEEDS_H
