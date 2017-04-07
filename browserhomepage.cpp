#include "accordion.h"
#include "browserhomepage.h"
#include "commandbutton.h"
#include "database.h"
#include "heading.h"
#include "layout.h"
#include "textbox.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserHomePage::BrowserHomePage(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                                 QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->database = new Database("Information");
}
void BrowserHomePage::loadHomePage()
{
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("title", "homePage");
    QVector<QString> columnTitles({"value"});
    QVector<QVector<QString>> tableSetting = database->getTableContents("setting", selectedParameters,
                                                                        columnTitles);
    if(tableSetting.count() > 0)
        secondWebEngineView->load(QUrl(tableSetting.at(0).at(0)));
}
QString BrowserHomePage::setHomePage()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aLayout;
    TextBox homePageTextBox("Please enter the address of your desired home page", "home", "homePageTextBox",
                            getHomePage());
    CommandButton saveHomePageButton("Save", "Save Your Home Page", "checkmark", "success",
                                     "saveUpdatedHomePage();");
    aLayout.addControl(homePageTextBox, QVector<int>({0, 12, 0}));
    aLayout.addControl(saveHomePageButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Your Home Page Address"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"home"}));
    return anAccordion.toHTML();
}
void BrowserHomePage::setHomePageToCurrentPage()
{
    updateHomePage(secondWebEngineView->url().toDisplayString());
}
QString BrowserHomePage::applyHomePageSetting(QString homePage)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    updateHomePage(homePage);
    Layout aLayout;
    Heading aHeading("Your home page has been updated to " + homePage);
    aLayout.addControl(aHeading, QVector<int>({0, 12, 0}));
    Accordion anAccordion(QVector<QString>({"Your Home Page Address"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"home"}));
    return anAccordion.toHTML();
}
void BrowserHomePage::updateHomePage(QString homePage)
{
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("title", "homePage");
    QMap<QString, QString> updatedContents;
    updatedContents.insert("value", homePage);
    database->updateRow("setting", selectedParameters, updatedContents);
}
QString BrowserHomePage::getHomePage()
{
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("title", "homePage");
    QVector<QVector<QString>> tableContents = database->getTableContents("setting", selectedParameters,
                                                                         QVector<QString>({"value"}));
    if(tableContents.count() > 0)
        return tableContents.at(0).at(0);
    return "";
}
