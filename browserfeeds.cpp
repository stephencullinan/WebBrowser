#include "accordion.h"
#include "browserdataitem.h"
#include "browserfeeds.h"
#include "browsertables.h"
#include "heading.h"
#include "layout.h"
#include "preloader.h"
#include "tile.h"
#include "tilelarge.h"
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QVector>
#include <QXmlStreamReader>
BrowserFeeds::BrowserFeeds(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                           QObject *parent) : QObject(parent)
{
    this->webEngineView = webEngineView;
    this->secondWebEngineView = secondWebEngineView;
}
QString BrowserFeeds::createNewFeed()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    TextBox feedTitleTextBox("Please enter the title of your feed", "feed3", "feedTitleTextBox");
    TextBox feedUrlTextBox("Please enter the url of your feed", "feed3", "feedUrlTextBox");
    CommandButton createNewFeedButton("Add", "Add A Feed", "checkmark", "success", "saveCreatedFeed();");
    Layout createNewFeedLayout;
    createNewFeedLayout.addControl(feedTitleTextBox, QVector<int>({0, 12, 0}));
    createNewFeedLayout.addControl(feedUrlTextBox, QVector<int>({0, 12, 0}));
    createNewFeedLayout.addControl(createNewFeedButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Add A Feed"}), QVector<Layout>({createNewFeedLayout}),
                          QVector<QString>({"feed3"}));
    return anAccordion.toHTML();
}
QString BrowserFeeds::saveCreatedFeed(QString feedUrl, QString feedTitle)
{
    BrowserDataItem aDataItem;
    aDataItem.saveDataItemToSpecifiedTable(feedUrl, feedTitle, "feed");
    BrowserTables aTable(secondWebEngineView, webEngineView);
    return aTable.createFormattedHTMLTable("feed", "Feeds");
}
QString BrowserFeeds::viewFeedsAsTiles()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    BrowserTables aTable(secondWebEngineView, webEngineView);
    QVector<QVector<QString>> feedContents = aTable.extractDataFromSpecifiedTable("feed");
    QVector<Component> availableTiles;
    for(QVector<QString> aFeed : feedContents)
        availableTiles.append(Tile("feed3", aFeed.at(1), "viewFeeds('" + aFeed.at(2) + "');"));
    Layout availableFeedsLayout;
    availableFeedsLayout.addTiles(availableTiles);
    Accordion availableFeedsAccordion(QVector<QString>({"Available Feeds"}),
                                      QVector<Layout>({availableFeedsLayout}),
                                      QVector<QString>({"feed3"}));
    return availableFeedsAccordion.toHTML();
}
QString BrowserFeeds::downloadFeeds(QString url)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QNetworkAccessManager* accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(retrieveFeeds(QNetworkReply*)));
    accessManager->get(QNetworkRequest(QUrl(url)));
    Layout preloaderLayout;
    PreLoader aPreLoader;
    preloaderLayout.addControl(aPreLoader, QVector<int>({5, 2, 5}));
    Accordion aPreLoaderAccordion(QVector<QString>({"Retrieving The Latest Feeds From " + url}),
                                  QVector<Layout>({preloaderLayout}), QVector<QString>({"feed3"}));
    return aPreLoaderAccordion.toHTML();
}
void BrowserFeeds::retrieveFeeds(QNetworkReply* aNetworkReply)
{
    QString fileContents = QString::fromStdString(aNetworkReply->readAll().toStdString());
    QVector<QString> extractedItems = extractElementFromTag(fileContents, "item");
    Layout feedsLayout;
    QVector<Component> createdTiles;
    for(QString anExtractedItem : extractedItems)
    {
        QVector<QString> tags({"title", "link", "description", "pubDate"});
        QMap<QString, QString> extractedItemAttributes = extractElementsFromTag(anExtractedItem, tags);
        createdTiles.append(TileLarge("openURL('" + extractedItemAttributes.value("link") + "');",
                                      QVector<QString>({extractedItemAttributes.value("title"),
                                                       extractedItemAttributes.value("description"),
                                                       extractedItemAttributes.value("pubDate")}),
                                      QVector<int>({3, 4, 5}),
                                      ""));
    }
    feedsLayout.addTiles(createdTiles);
    if(createdTiles.count() == 0)
        feedsLayout.addControl(Heading("There are no feed items available for the selected feed"),
                               QVector<int>({0, 12, 0}));
    Accordion* anAccordion = new Accordion(QVector<QString>({"Feeds"}), QVector<Layout>({feedsLayout}),
                                           QVector<QString>({"feed3"}));
    this->feedsAccordion = anAccordion;
    webEngineView->page()->runJavaScript("getFeedsAccordion();");
}
QString BrowserFeeds::getFeedsAccordion()
{
    return feedsAccordion->toHTML();
}
QVector<QString> BrowserFeeds::extractElementFromTag(QString fileText, QString tag)
{
    QVector<QString> extractedElements;
    QString existingFileContents = fileText;
    while(existingFileContents.indexOf("<" + tag + ">") > -1)
    {
        existingFileContents = existingFileContents.mid(existingFileContents.indexOf("<" + tag + ">") +
                                                    (tag.length() + 2));
        extractedElements.append(existingFileContents.mid(0, existingFileContents.indexOf("</" + tag + ">")));
    }
    return extractedElements;
}
QMap<QString, QString> BrowserFeeds::extractElementsFromTag(QString tagText, QVector<QString> requiredTags)
{
    QMap<QString, QString> extractedElements;
    for(QString aRequiredTag : requiredTags)
    {
        QString selectedText = tagText.mid(tagText.indexOf("<" + aRequiredTag + ">") +
                                           (aRequiredTag.length() + 2));
        extractedElements.insert(aRequiredTag,
                                 removeCDataTag(
                                     selectedText.mid(0, selectedText.indexOf("</" + aRequiredTag + ">"))));
    }
    return extractedElements;
}
QString BrowserFeeds::removeCDataTag(QString input)
{
    if(input.indexOf("<![CDATA[") > -1)
    {
        input = input.mid(9);
        input = input.mid(0, input.indexOf("]]>"));
    }
    return input;
}
