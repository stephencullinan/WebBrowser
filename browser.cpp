#include <QCheckBox>
#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFontDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QProgressBar>
#include <QPushButton>
#include <QSize>
#include <QTableWidget>
#include <QWebChannel>
#include <QWebEngineView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "browser.h"
#include "htmlpage.h"
#include "textbox.h"
#include "table.h"
#include "iframe.h"
#include "commandbutton.h"
#include "layout.h"
#include "listview.h"
#include "heading.h"
#include "accordion.h"
#include "fluentbigbutton.h"
#include "fluenttabgroup.h"
#include "fluenttabpanel.h"
#include "updatepanel.h"
#include "colorpicker.h"
#include "tablesimplified.h"
#include "browserabout.h"
#include "browserbookmarks.h"
#include "browsertables.h"
#include "browsernavigation.h"
#include "browserhomepage.h"
#include "browserurl.h"
#include "browsersearch.h"
#include "browsertableau.h"
#include "browsereditfont.h"
#include "browsereditimages.h"
#include "browsereditimagerotations.h"
#include "browsereditbackground.h"
#include "browsereditlinkscolour.h"
#include "browseredittextreplacements.h"
#include "browserfeeds.h"
#include "browserfont.h"
#include "browsersiteedits.h"
#include "browsertheme.h"
Browser::Browser(QWidget* parent) : QMainWindow(parent)
{
    this->parentWidget = parent;
    this->database = new Database("Information");
    QGridLayout* aLayout = new QGridLayout(this->parentWidget);
    this->parentWidget->setLayout(aLayout);
    this->webEngineView = new QWebEngineView();
    this->secondWebEngineView = new QWebEngineView();
    this->progressBar = new QProgressBar();
    this->progressBar->setValue(0);
    connect(this->secondWebEngineView, SIGNAL(loadProgress(int)), SLOT(updateProgressBar(int)));
    connect(this->secondWebEngineView, SIGNAL(loadFinished(bool)), SLOT(loadFinished()));
    webEngineView->setFixedHeight(160);
    this->parentWidget->layout()->addWidget(webEngineView);
    this->parentWidget->layout()->addWidget(this->secondWebEngineView);
    this->parentWidget->layout()->addWidget(this->progressBar);
    this->webEngineView->setVisible(true);
    this->progressBar->setVisible(false);
    openHomePage();
}
QWidget* Browser::getParentWidget()
{
    return this->parentWidget;
}
QMainWindow* Browser::getParentWindow()
{
    return this;
}
void Browser::openHomePage()
{
    HTMLPage* aHtmlPage = new HTMLPage();
    aHtmlPage->createHeading();
    aHtmlPage->createMenuButtons();
    aHtmlPage->writeToFile("index.html");
    QWebChannel* aWebChannel = new QWebChannel(webEngineView->page());
    webEngineView->page()->setWebChannel(aWebChannel);
    QObject* anObject = new BrowserBookmarks(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("bookmarks", anObject);
    anObject = new BrowserTables(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("tables", anObject);
    anObject = new BrowserNavigation(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("navigation", anObject);
    anObject = new BrowserHomePage(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("home", anObject);
    anObject = new BrowserURL(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("URL", anObject);
    anObject = new BrowserSearch(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("search", anObject);
    anObject = new BrowserTableau(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("tableau", anObject);
    anObject = new BrowserEditImages(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("editimages", anObject);
    anObject = new BrowserEditBackground(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("editbackground", anObject);
    anObject = new BrowserEditLinksColour(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("editlinkscolour", anObject);
    anObject = new BrowserEditTextReplacements(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("edittextreplacements", anObject);
    anObject = new BrowserFeeds(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("feeds", anObject);
    anObject = new BrowserEditFont(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("editfont", anObject);
    anObject = new BrowserEditImageRotations(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("editimagerotations", anObject);
    anObject = new BrowserFont(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("font", anObject);
    anObject = new BrowserTheme(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("theme", anObject);
    anObject = new BrowserAbout(secondWebEngineView, webEngineView);
    aWebChannel->registerObject("about", anObject);
    QDir aDirectory;
    this->webEngineView->load(QUrl("file:///" + aDirectory.currentPath() + "/index.html"));
    BrowserHomePage aHomePage(secondWebEngineView, webEngineView);
    this->secondWebEngineView->load(QUrl(aHomePage.getHomePage()));
}
void Browser::loadFinished()
{
    setWindowTitle(secondWebEngineView->title());
    int maximumValueFromSiteTable = 0;
    QMap<QString, QString>* parametersForSiteTable = new QMap<QString, QString>();
    parametersForSiteTable->insert("url", secondWebEngineView->url().toDisplayString());
    QVector<QString> columnTitlesForSiteTable;
    columnTitlesForSiteTable.push_back("code");
    QVector<QVector<QString>> existingSiteDetails = database->getTableContents("site", parametersForSiteTable,
                                                                                    columnTitlesForSiteTable);
    if(existingSiteDetails.count() == 0)
    {
        QVector<QString> informationForSiteTable;
        maximumValueFromSiteTable = database->getMaxValueOfColumn("site", "code");
        informationForSiteTable.push_back(QString::number(++maximumValueFromSiteTable));
        informationForSiteTable.push_back(this->secondWebEngineView->title());
        informationForSiteTable.push_back(this->secondWebEngineView->url().toDisplayString());
        database->insertRow("site", informationForSiteTable);
    }
    else
        maximumValueFromSiteTable = (existingSiteDetails.at(0).at(0)).toInt();
    QVector<QString> informationForHistoryTable;
    int maximumValueFromHistoryTable = database->getMaxValueOfColumn("history", "code");
    informationForHistoryTable.push_back(QString::number(++maximumValueFromHistoryTable));
    informationForHistoryTable.push_back(QString::number(maximumValueFromSiteTable));
    informationForHistoryTable.push_back(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    database->insertRow("history", informationForHistoryTable);
    BrowserSiteEdits siteEdits(secondWebEngineView, webEngineView, maximumValueFromSiteTable);
    secondWebEngineView->setVisible(true);
}
void Browser::updateProgressBar(int currentProgress)
{
    progressBar->setVisible(true);
    progressBar->setValue(currentProgress);
    if(currentProgress == 100)
        progressBar->setVisible(false);
}
