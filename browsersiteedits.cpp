#include "browsereditbackground.h"
#include "browsereditfont.h"
#include "browsereditimages.h"
#include "browsereditimagerotations.h"
#include "browsereditlinkscolour.h"
#include "browseredittextreplacements.h"
#include "browsersiteedits.h"
#include "database.h"
#include <QWebEngineView>
BrowserSiteEdits::BrowserSiteEdits(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView, int siteID,
                                   QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->siteID = siteID;
    applyEditsToSite();
}
void BrowserSiteEdits::applyEditsToSite()
{
    Database database("Information");
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("site", QString::number(siteID));
    QVector<QString> columnTitles({"title", "value"});
    QVector<QVector<QString>> availableEdits = database.getTableContents("sitesetting", selectedParameters,
                                                                          columnTitles);
    QVector<QVector<QString>> matchingThemes = database.getTableContents("themesite", selectedParameters,
                                                                         QVector<QString>({"theme"}));
    for(QVector<QString> aMatchingTheme : matchingThemes)
    {
        selectedParameters->clear();
        selectedParameters->insert("theme", aMatchingTheme.at(0));
        QVector<QVector<QString>> currentThemeSettings = database.getTableContents("themesetting",
                                                                                   selectedParameters,
                                                                                   QVector<QString>({"title",
                                                                                                     "value"}));
        for(QVector<QString> aCurrentThemeSetting: currentThemeSettings)
            availableEdits.append(aCurrentThemeSetting);
    }
    QMap<QString, QString> imagesRotationParameters;
    for(QVector<QString> anAvailableEdit : availableEdits)
    {
        if(anAvailableEdit.at(0) == "linksColour")
        {
            BrowserEditLinksColour anEditLinksColour(secondWebEngineView, webEngineView);
            anEditLinksColour.executeLinksColour(anAvailableEdit.at(1));
        }
        else if(anAvailableEdit.at(0) == "backgroundColour")
        {
            BrowserEditBackground anEditBackground(secondWebEngineView, webEngineView);
            anEditBackground.executeBackgroundColour(anAvailableEdit.at(1));
        }
        else if(anAvailableEdit.at(0) == "fontFace")
        {
            BrowserEditFont anEditFont(secondWebEngineView, webEngineView);
            anEditFont.executeFontFace(anAvailableEdit.at(1));
        }
        else if(anAvailableEdit.at(0) == "fontSize")
        {
            BrowserEditFont anEditFont(secondWebEngineView, webEngineView);
            anEditFont.executeFontSize(anAvailableEdit.at(1).toInt());
        }
        else if(anAvailableEdit.at(0) == "textReplacements")
        {
            QVector<QString> components = anAvailableEdit.at(1).split(":").toVector();
            BrowserEditTextReplacements anEditTextReplacement(secondWebEngineView, webEngineView);
            anEditTextReplacement.executeReplaceText(components.at(0), components.at(1), true);
        }
        else if(anAvailableEdit.at(0) == "textColourReplacements")
        {
            QVector<QString> components = anAvailableEdit.at(1).split(":").toVector();
            BrowserEditTextReplacements anEditTextReplacement(secondWebEngineView, webEngineView);
            anEditTextReplacement.executeReplaceText(components.at(0), components.at(1), false);
        }
        else if(anAvailableEdit.at(0) == "removePNGFiles" || anAvailableEdit.at(0) == "removeJPEGFiles" ||
                anAvailableEdit.at(0) == "removeGIFFiles")
        {
            BrowserEditImages anEditImage(secondWebEngineView, webEngineView);
            anEditImage.executeRemovalOfImageFiles(anAvailableEdit.at(1));
        }
        else if(anAvailableEdit.at(0) == "imagesRotationDegrees")
            imagesRotationParameters.insert("imagesRotationDegrees", anAvailableEdit.at(1));
        else if(anAvailableEdit.at(0) == "imagesRotationTime")
            imagesRotationParameters.insert("imagesRotationTime", anAvailableEdit.at(1));
    }
    if(imagesRotationParameters.contains("imagesRotationDegrees") &&
       imagesRotationParameters.contains("imagesRotationTime"))
    {
        BrowserEditImageRotations anEditImageRotation(secondWebEngineView, webEngineView);
        anEditImageRotation.executeImageRotations(imagesRotationParameters.value("imagesRotationDegrees").toInt(),
                                                  imagesRotationParameters.value("imagesRotationTime").toInt());
    }
}
