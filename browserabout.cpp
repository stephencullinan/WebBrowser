#include "accordion.h"
#include "browserabout.h"
#include "paragraph.h"
BrowserAbout::BrowserAbout(QWebEngineView* secondWebEngine, QWebEngineView* webEngine,
                           QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngine;
    this->webEngineView = webEngine;
}
QString BrowserAbout::getAboutMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aboutMenuLayout;
    Paragraph aboutMenuParagraph("This software utilises the front end framework titled Metro UI CSS", "About");
    aboutMenuLayout.addControl(aboutMenuParagraph, QVector<int>({0, 12, 0}));
    Accordion aboutMenuAccordion(QVector<QString>({"About"}), QVector<Layout>({aboutMenuLayout}),
                                 QVector<QString>({"html5"}));
    return aboutMenuAccordion.toHTML();
}
