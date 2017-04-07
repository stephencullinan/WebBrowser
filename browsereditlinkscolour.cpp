#include "accordion.h"
#include "browsereditlinkscolour.h"
#include "browserjavascriptfiles.h"
#include "commandbutton.h"
#include "layout.h"
#include "slider.h"
#include "switcher.h"
#include "tileselected.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserEditLinksColour::BrowserEditLinksColour(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                                               QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserEditLinksColour::applyLinksColourMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QString existingSelectedColour;
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> existingSetting = browserSettings.getExistingSettings("linksColour");
    if(existingSetting.count() > 0)
        existingSelectedColour = existingSetting.at(0).at(2);
    Layout applyLinksColourMenu = createLayout(existingSelectedColour);
    CommandButton applyLinksCommandButton("Apply", "Apply Your Selected Setting", "checkmark", "success",
                                          "applyLinksColourSettings();");
    applyLinksColourMenu.addControl(applyLinksCommandButton, QVector<int>({3, 6, 3}));
    Accordion applyLinksColourAccordion(QVector<QString>({"Apply Links Colour"}),
                                        QVector<Layout>({applyLinksColourMenu}),
                                        QVector<QString>({"palette"}));
    return applyLinksColourAccordion.toHTML();
}
Layout BrowserEditLinksColour::createLayout(QString existingSelectedColour)
{
    Layout applyLinksColourMenu;
    TileSelected aSelectedTile("applyLinksColourSwitch", true, "Highlight Links Is Active For This Site",
                               "Highlight Links Is Not Active For This Site", "palette",
                               "applyLinksColourPickerUpdatePanel");
    applyLinksColourMenu.addControl(aSelectedTile, QVector<int>({4, 4, 4}));
    UpdatePanel applyLinksColourPickerUpdatePanel("applyLinksColourPickerUpdatePanel");
    applyLinksColourPickerUpdatePanel.addControl(ColorPicker("applyLinksColourPicker", existingSelectedColour));
    applyLinksColourMenu.addControl(applyLinksColourPickerUpdatePanel, QVector<int>({3, 6, 3}));
    applyLinksColourMenu.addEmptyRows(2);
    return applyLinksColourMenu;
}

void BrowserEditLinksColour::applyLinksColourSettings(QString colourTitle)
{
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> tableContents = browserSettings.getExistingSettings("linksColour");
    if(colourTitle.length() > 0)
    {
        executeLinksColour(colourTitle);
        browserSettings.writeNewSetting(tableContents, "linksColour", colourTitle);
    }
    else
    {
        browserSettings.deleteExistingSetting(tableContents);
        secondWebEngineView->reload();
    }
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
}
void BrowserEditLinksColour::executeLinksColour(QString colourTitle)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addJQuery();
    QString highlightLinks = "jQuery.jQuery('a').each( function () { jQuery.jQuery(this).css"
                             "('background-color', '" + colourTitle + "') } ); undefined";
    secondWebEngineView->page()->runJavaScript(highlightLinks);
}
