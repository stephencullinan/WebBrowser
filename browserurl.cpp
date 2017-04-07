#include "accordion.h"
#include "browserurl.h"
#include "commandbutton.h"
#include "layout.h"
#include "textbox.h"
#include <QObject>
#include <QString>
#include <QUrl>
#include <QWebEngineView>
BrowserURL::BrowserURL(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                       QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserURL::openURLPage()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aLayout;
    TextBox openURLTextBox("Please enter the URL of your page", "map2", "openURLTextBox");
    aLayout.addControl(openURLTextBox, QVector<int>({0, 12, 0}));
    CommandButton enterURLButton("Enter", "Enter Your URL", "map2", "success", "openSelectedURL();");
    aLayout.addControl(enterURLButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"The URL Of Your Page"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"map2"}));
    return anAccordion.toHTML();
}
void BrowserURL::openSelectedURL(QString selectedURL)
{
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
    secondWebEngineView->load(QUrl(selectedURL));
}
