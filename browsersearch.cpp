#include "accordion.h"
#include "browsersearch.h"
#include "commandbutton.h"
#include "layout.h"
#include "textbox.h"
#include <QObject>
#include <QString>
#include <QWebEngineView>
BrowserSearch::BrowserSearch(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                             QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserSearch::performSearchOnGoogle()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aLayout;
    TextBox googleSearchQueryTextBox("Please enter the search query", "google", "googleSearchQueryTextBox");
    aLayout.addControl(googleSearchQueryTextBox, QVector<int>({0, 12, 0}));
    CommandButton enterSearchQueryButton("Search", "Search For Your Specified Query", "google", "success",
                                         "openSelectedSearch();");
    aLayout.addControl(enterSearchQueryButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"The Search Query"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"google"}));
    return anAccordion.toHTML();
}
void BrowserSearch::performSelectedSearch(QString searchTerm)
{
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
    secondWebEngineView->load(QUrl("https://www.google.ie/search?q=" + searchTerm));
}

