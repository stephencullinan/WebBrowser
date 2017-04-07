#include "accordion.h"
#include "browsereditbackground.h"
#include "browserjavascriptfiles.h"
#include "browsersettings.h"
#include "colorpicker.h"
#include "commandbutton.h"
#include "database.h"
#include "tileselected.h"
#include "layout.h"
#include <QString>
#include <QVector>
BrowserEditBackground::BrowserEditBackground(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                                             QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->database = new Database("Information");
}
QString BrowserEditBackground::applyBackgroundColourMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QString existingSelectedColour;
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> existingSetting = browserSettings.getExistingSettings("backgroundColour");
    if(existingSetting.count() > 0)
        existingSelectedColour = existingSetting.at(0).at(2);
    Layout applyBackgroundColourMenu = createLayout(existingSelectedColour);
    CommandButton applyBackgroundCommandButton("Apply", "Apply Your Selected Colour", "checkmark", "success",
                                               "applyBackgroundColourSettings();");
    applyBackgroundColourMenu.addControl(applyBackgroundCommandButton, QVector<int>({3, 6, 3}));
    Accordion applyBackgroundColourAccordion(QVector<QString>({"Apply Background Colour"}),
                                             QVector<Layout>({applyBackgroundColourMenu}),
                                             QVector<QString>({"palette"}));
    return applyBackgroundColourAccordion.toHTML();
}
Layout BrowserEditBackground::createLayout(QString existingSelectedColour)
{
    Layout applyBackgroundColourMenu;
    TileSelected aSelectedTile("applyBackgroundColourSwitch", true, "Background Colour Is Active For This Site",
                               "Background Colour Is Not Active For This Site", "palette",
                               "applyBackgroundColourPickerUpdatePanel");
    applyBackgroundColourMenu.addControl(aSelectedTile, QVector<int>({4, 4, 4}));
    UpdatePanel applyBackgroundColourPickerUpdatePanel("applyBackgroundColourPickerUpdatePanel");
    applyBackgroundColourPickerUpdatePanel.addControl(ColorPicker("applyBackgroundColourPicker",
                                                                       existingSelectedColour));
    applyBackgroundColourMenu.addControl(applyBackgroundColourPickerUpdatePanel, QVector<int>({3, 6, 3}));
    applyBackgroundColourMenu.addEmptyRows(2);
    return applyBackgroundColourMenu;
}
void BrowserEditBackground::applyBackgroundColourSettings(QString colourTitle)
{
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> tableContents = browserSettings.getExistingSettings("backgroundColour");
    if(colourTitle.length() > 0)
    {
        executeBackgroundColour(colourTitle);
        browserSettings.writeNewSetting(tableContents, "backgroundColour", colourTitle);
    }
    else
    {
        browserSettings.deleteExistingSetting(tableContents);
        secondWebEngineView->reload();
    }
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
}
void BrowserEditBackground::executeBackgroundColour(QString colourTitle)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addJQuery();
    secondWebEngineView->page()->runJavaScript("jQuery.jQuery('body').css('background-color', '"
                                               + colourTitle + "');");
}
