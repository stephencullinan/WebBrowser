#include "accordion.h"
#include "browseredittextreplacements.h"
#include "browserjavascriptfiles.h"
#include "browsersettings.h"
#include "commandbutton.h"
#include "layout.h"
#include "tablesimplified.h"
#include "textbox.h"
#include "updatepanel.h"
#include <QDebug>
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserEditTextReplacements::BrowserEditTextReplacements(QWebEngineView* secondWebEngineView,
                                                         QWebEngineView* webEngineView,
                                                         QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserEditTextReplacements::replaceTextMenu(bool textReplacementsOnly)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout applyTextReplacementsMenu = createLayout(textReplacementsOnly, true);
    QString replaceTextOnClickEvent = "";
    if(textReplacementsOnly)
        replaceTextOnClickEvent = "applyReplaceText(true);";
    else
        replaceTextOnClickEvent = "applyReplaceText(false);";
    CommandButton replaceTextButton("Apply", "Apply Your Setting", "checkmark", "success",
                                    replaceTextOnClickEvent);
    applyTextReplacementsMenu.addControl(replaceTextButton, QVector<int>({4, 4, 4}));
    Accordion replaceTextAccordion(QVector<QString>({"Replace Text"}),
                                   QVector<Layout>({applyTextReplacementsMenu}),
                                   QVector<QString>({"file-text"}));
    return replaceTextAccordion.toHTML();
}
Layout BrowserEditTextReplacements::createLayout(bool textReplacementsOnly, bool includeExistingSettings)
{
    Layout addNewSuggestionLayout;
    TextBox locateTextBox("The word to locate goes here", "file-text", "locateTextBox");
    addNewSuggestionLayout.addControl(locateTextBox, QVector<int>({0, 12, 0}));
    if(textReplacementsOnly)
    {
        TextBox replaceTextBox("The word to replace goes here", "file-text", "replaceTextBox");
        addNewSuggestionLayout.addControl(replaceTextBox, QVector<int>({0, 12, 0}));
    }
    else
    {
        ColorPicker replaceColourPicker("replaceColourPicker", "");
        addNewSuggestionLayout.addControl(replaceColourPicker, QVector<int>({0, 12, 0}));
    }
    CommandButton addNewSuggestionButton("Add", "Add Your Suggestion", "checkmark", "success",
                                         "getTextSuggestions();");
    addNewSuggestionLayout.addControl(addNewSuggestionButton, QVector<int>({2, 8, 2}));
    Layout existingSuggestionsLayout;
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> existingSettings;
    if(includeExistingSettings)
    {
        if(textReplacementsOnly)
            existingSettings = browserSettings.getExistingSettings("textReplacements");
        else
            existingSettings = browserSettings.getExistingSettings("textColourReplacements");
    }
    QVector<QString> possibleComponents;
    if(existingSettings.count() > 0 && existingSettings.at(0).count() > 1)
        possibleComponents = existingSettings.at(0).at(2).split(":").toVector();
    QVector<QVector<QString>> tableContents;
    QVector<QString> tableClickEvents;
    if(possibleComponents.count() >= 2)
    {
        QVector<QString> locateTerms = browserSettings.removeEmptyElements(
                                       possibleComponents.at(0).split(";").toVector());
        QVector<QString> replaceTerms = browserSettings.removeEmptyElements(
                                        possibleComponents.at(1).split(";").toVector());
        for(int counter = 0; counter < locateTerms.length() && counter < replaceTerms.length(); counter++)
        {
            QVector<QString> currentRow;
            currentRow.append(locateTerms.at(counter));
            currentRow.append(replaceTerms.at(counter));
            tableContents.append(currentRow);
            tableClickEvents.append("document.getElementById('existingSuggestionsTable_Row_" +
                                    QString::number(counter) + "').innerHTML = '';");
        }
    }
    TableSimplified existingSuggestionsTable("existingSuggestionsTable", QVector<QString>({"Locate", "Replace"}),
                                             tableContents, tableClickEvents);
    UpdatePanel existingSuggestionsPanel("existingSuggestionsPanel");
    existingSuggestionsPanel.addControl(existingSuggestionsTable);
    existingSuggestionsLayout.addControl(existingSuggestionsPanel, QVector<int>({0, 12, 0}));
    existingSuggestionsLayout.addEmptyRows(10);
    Layout applyTextReplacementsMenu;
    QString caption = "Text Replacements Are ";
    if(textReplacementsOnly == false)
        caption = "Text Colour Replacements Are ";
    TileSelected aSelectedTile("applyTextReplacementsSwitch", true,
                               caption + "Active For This Site",
                               caption + "Not Active For This Site", "file-text",
                               "applyTextReplacementsUpdatePanel");
    applyTextReplacementsMenu.addControl(aSelectedTile, QVector<int>({4, 4, 4}));
    UpdatePanel applyTextReplacementsUpdatePanel("applyTextReplacementsUpdatePanel");
    Layout suggestionsLayout;
    suggestionsLayout.addLayouts(addNewSuggestionLayout, existingSuggestionsLayout);
    applyTextReplacementsUpdatePanel.addControl(suggestionsLayout);
    applyTextReplacementsMenu.addControl(applyTextReplacementsUpdatePanel, QVector<int>({0, 12, 0}));
    return applyTextReplacementsMenu;
}

QString BrowserEditTextReplacements::replaceTextSuggestion(QString locateText, QString replaceText)
{
    QVector<QString> locateTextSuggestions = locateText.split(";").toVector();
    QVector<QString> replaceTextSuggestions = replaceText.split(";").toVector();
    QVector<QVector<QString>> textSuggestions({{}});
    QVector<QString> onTableTouchEvents;
    for(int counter = 0; counter < locateTextSuggestions.length() && counter < replaceTextSuggestions.length();
        counter++)
    {
        if(locateTextSuggestions.at(counter).length() > 0 && replaceTextSuggestions.at(counter).length() > 0)
        {
            textSuggestions.push_back(QVector<QString>({locateTextSuggestions.at(counter),
                                      replaceTextSuggestions.at(counter)}));
            onTableTouchEvents.append("document.getElementById('existingSuggestionsTable_Row_" +
                                      QString::number(counter) + "').innerHTML = '';");
        }
    }
    TableSimplified existingSuggestionsTable("existingSuggestionsTable", QVector<QString>({"Locate", "Replace"}),
                                             textSuggestions, onTableTouchEvents);
    return existingSuggestionsTable.toHTML();
}
void BrowserEditTextReplacements::applyReplaceText(QString locate, QString replace, bool textReplacementsOnly)
{
    BrowserSettings browserSettings(secondWebEngineView);
    QString textReplacements = "textReplacements";
    if(textReplacementsOnly == false)
        textReplacements = "textColourReplacements";
    QVector<QVector<QString>> existingSettings = browserSettings.getExistingSettings(textReplacements);
    if(locate.length() > 0 && replace.length() > 0)
    {
        browserSettings.writeNewSetting(existingSettings, textReplacements, locate + ":" + replace);
        executeReplaceText(locate, replace, textReplacementsOnly);
    }
    else
    {
        browserSettings.deleteExistingSetting(existingSettings);
        secondWebEngineView->reload();
    }
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
}
void BrowserEditTextReplacements::executeReplaceText(QString locate, QString replace, bool textReplacementsOnly)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addFindAndReplaceDOMText();
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QString> locateTerms = browserSettings.removeEmptyElements(locate.split(";").toVector());
    QVector<QString> replaceTerms = browserSettings.removeEmptyElements(replace.split(";").toVector());
    if(textReplacementsOnly == false)
    {
        QString styleInformation = "var style = document.createElement('style');";
        styleInformation.append("style.type = 'text/css';");
        styleInformation.append("style.innerHTML = '");
        for(int index = 0; index < locateTerms.length() && index < replaceTerms.length(); index++)
        {
            styleInformation.append(".textColourReplacement_" + QString::number(index) + "{ color: " +
                                    replaceTerms.at(index) + ";}");
        }
        styleInformation.append("';");
        styleInformation.append("document.getElementsByTagName('head')[0].appendChild(style);");
        secondWebEngineView->page()->runJavaScript(styleInformation);
    }
    for(int counter = 0; counter < locateTerms.length() && counter < replaceTerms.length(); counter++)
    {
        if(textReplacementsOnly)
        {
            QString replaceText = "var aBody = document.getElementsByTagName('body')[0];"
                                  "findAndReplaceDOMText(aBody, {preset: 'prose', find: '" +
                                  locateTerms.at(counter) + "', replace: '" + replaceTerms.at(counter) +
                                  "'});";
            secondWebEngineView->page()->runJavaScript(replaceText);
        }
        else
        {
            QString replaceText = "var aBody = document.getElementsByTagName('body')[0];";
            replaceText.append("findAndReplaceDOMText(aBody, {preset: 'prose', find: '");
            replaceText.append(locateTerms.at(counter) + "', wrap: 'em', wrapClass: '");
            replaceText.append("textColourReplacement_" + QString::number(counter) + "'});");
            secondWebEngineView->page()->runJavaScript(replaceText);
        }
    }
}
