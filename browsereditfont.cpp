#include "browsereditfont.h"
#include "browserjavascriptfiles.h"
#include "browsersettings.h"
#include "commandbutton.h"
#include "layout.h"
#include "listview.h"
#include "textbox.h"
#include "tileselected.h"
#include "updatepanel.h"
#include <QWebEngineView>
BrowserEditFont::BrowserEditFont(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                                 QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserEditFont::editFontMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> fontFaceSettings = browserSettings.getExistingSettings("fontFace");
    QVector<QVector<QString>> fontSizeSettings = browserSettings.getExistingSettings("fontSize");
    QString fontFace = "";
    QString fontSize = "";
    if(fontFaceSettings.count() > 0)
        fontFace = fontFaceSettings.at(0).at(2);
    if(fontSizeSettings.count() > 0)
        fontSize = fontSizeSettings.at(0).at(2);
    Layout editFontMenuMainLayout = createLayout(fontFace, fontSize);
    CommandButton editFontMenuApplyButton("Apply", "Apply Your Settings", "checkmark", "success",
                                          "applyEditFont();");
    editFontMenuMainLayout.addControl(editFontMenuApplyButton, QVector<int>({4, 4, 4}));
    return editFontMenuMainLayout.toHTML();
}
Layout BrowserEditFont::createLayout(QString fontFace, QString fontSize)
{
    Layout editFontMenuMainLayout;
    TileSelected editFontMenuSelectedTile("editFontMenuSelectedTile", true,
                                          "Font Settings Are Active For This Site",
                                          "Font Settings Are Not Active For This Site", "fonticons",
                                          "editFontMenuUpdatePanel");
    editFontMenuMainLayout.addControl(editFontMenuSelectedTile, QVector<int>({4, 4, 4}));
    Layout editFontMenuLayout;
    ListView availableFontsListView("availableFontsListView", "", "Available Fonts");
    if(fontFace.length() > 0)
        ListView availableFontsListView("availableFontsListView", fontFace, "Available Fonts");
    Database aDatabase("Information");
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    QVector<QString> columnTitles({"font"});
    QVector<QVector<QString>> fontTableContents = aDatabase.getTableContents("font", selectedParameters,
                                                                             columnTitles);
    for(QVector<QString> aFont : fontTableContents)
    {
        if(aFont.at(0) == fontFace)
            availableFontsListView.addItem(aFont.at(0), "Font", "Setting", true, aFont.at(0));
        else
            availableFontsListView.addItem(aFont.at(0), "Font", "Setting", false, aFont.at(0));
    }
    editFontMenuLayout.addControl(availableFontsListView, QVector<int>({3, 6, 3}));
    if(fontSize.length() > 0)
    {
        TextBox fontSizeTextBox("Please enter the size of the font", "fonticons", "fontSizeTextBox",
                                fontSize);
        editFontMenuLayout.addControl(fontSizeTextBox, QVector<int>({0, 12, 0}));
    }
    else
    {
        TextBox fontSizeTextBox("Please enter the size of the font", "fonticons", "fontSizeTextBox");
        editFontMenuLayout.addControl(fontSizeTextBox, QVector<int>({0, 12, 0}));
    }
    UpdatePanel editFontMenuUpdatePanel("editFontMenuUpdatePanel");
    editFontMenuUpdatePanel.addControl(editFontMenuLayout);
    editFontMenuMainLayout.addControl(editFontMenuUpdatePanel, QVector<int>({0, 12, 0}));
    return editFontMenuMainLayout;
}

void BrowserEditFont::applyFontSettings(QString fontFace, int fontSize)
{
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> fontFaceSettings = browserSettings.getExistingSettings("fontFace");
    QVector<QVector<QString>> fontSizeSettings = browserSettings.getExistingSettings("fontSize");
    if(fontFace.length() > 0 && fontSize > -1)
    {
        executeFontFace(fontFace);
        executeFontSize(fontSize);
        browserSettings.writeNewSetting(fontFaceSettings, "fontFace", fontFace);
        browserSettings.writeNewSetting(fontSizeSettings, "fontSize", QString::number(fontSize));
    }
    else
    {
        browserSettings.deleteExistingSetting(fontFaceSettings);
        browserSettings.deleteExistingSetting(fontSizeSettings);
        secondWebEngineView->reload();
    }
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
}
void BrowserEditFont::executeFontFace(QString fontFace)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addJQuery();
    QString setFontFace = "jQuery.jQuery('body').css('font-family', '" + fontFace + "');";
    secondWebEngineView->page()->runJavaScript(setFontFace);
}
void BrowserEditFont::executeFontSize(int fontSize)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addJQuery();
    QString setFontSize = "jQuery.jQuery('body').css('font-size', '" + QString::number(fontSize) + ".px');";
    secondWebEngineView->page()->runJavaScript(setFontSize);
}
