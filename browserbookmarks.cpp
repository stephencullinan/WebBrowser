#include "browserbookmarks.h"
#include "browserdataitem.h"
#include "browsertables.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QWebChannel>
#include <QWebEngineView>
#include "heading.h"
#include "textbox.h"
#include "commandbutton.h"
#include "layout.h"
#include "accordion.h"
#include "database.h"
BrowserBookmarks::BrowserBookmarks(QWebEngineView* secondWebEngineView,
                                   QWebEngineView* webEngineView,
                                   QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->database = new Database("Information");
}
QString BrowserBookmarks::createNewBookmark()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    TextBox siteTitleTextBox("Please enter the title of your site", "bookmark", "siteTitleTextBox");
    TextBox siteUrlTextBox("Please enter the url of your site", "bookmark", "siteUrlTextBox");
    CommandButton createNewBookmarkButton("Add", "Add A Bookmark", "checkmark", "success", "saveBookmark();");
    Layout createNewBookmarkLayout;
    createNewBookmarkLayout.addControl(siteTitleTextBox, QVector<int>({0, 12, 0}));
    createNewBookmarkLayout.addControl(siteUrlTextBox, QVector<int>({0, 12, 0}));
    createNewBookmarkLayout.addControl(createNewBookmarkButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Add A Bookmark"}), QVector<Layout>({createNewBookmarkLayout}),
                          QVector<QString>({"bookmark"}));
    return anAccordion.toHTML();
}
QString BrowserBookmarks::saveCreatedBookmark(QString siteUrl, QString siteTitle)
{
    BrowserDataItem dataItem;
    dataItem.saveDataItemToSpecifiedTable(siteUrl, siteTitle, "bookmark");
    BrowserTables aTable(secondWebEngineView, webEngineView);
    return aTable.createFormattedHTMLTable("bookmark", "Bookmarks");
}
