#include "browsereditimages.h"
#include "browserjavascriptfiles.h"
#include "browsersettings.h"
#include "layout.h"
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserEditImages::BrowserEditImages(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                                     QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserEditImages::getEditImagesMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    BrowserSettings settings(secondWebEngineView);
    QVector<QVector<QString>> pngSettings = settings.getExistingSettings("removePNGFiles");
    QVector<QVector<QString>> jpegSettings = settings.getExistingSettings("removeJPEGFiles");
    QVector<QVector<QString>> gifSettings = settings.getExistingSettings("removeGIFFiles");
    bool removePNGFiles = false;
    if(pngSettings.count() > 0)
        removePNGFiles = true;
    bool removeJPEGFiles = false;
    if(jpegSettings.count() > 0)
        removeJPEGFiles = true;
    bool removeGIFFiles = false;
    if(gifSettings.count() > 0)
        removeGIFFiles = true;
    Layout editImagesMenuLayout = createLayout(removePNGFiles, removeJPEGFiles, removeGIFFiles);
    CommandButton editImagesMenuSubmitButton("Apply", "Apply Your Settings", "checkmark", "success",
                                             "applyEditImageSettings();");
    editImagesMenuLayout.addControl(editImagesMenuSubmitButton, QVector<int>({4, 4, 4}));
    return editImagesMenuLayout.toHTML();
}
Layout BrowserEditImages::createLayout(bool removePNGFiles, bool removeJPEGFiles, bool removeGIFFiles)
{
    Layout editImagesMenuLayout;
    TileSelected removePNGFilesTile("removePNGFilesTile", removePNGFiles, "PNG Files Are Removed For This Site",
                                    "PNG Files Are Not Removed For This Site", "images", "");
    TileSelected removeJPEGFilesTile("removeJPEGFilesTile", removeJPEGFiles, "JPEG Files Are Removed For This Site",
                                     "JPEG Files Are Not Removed For This Site", "images", "");
    TileSelected removeGIFFilesTile("removeGIFFilesTile", removeGIFFiles, "GIF Files Are Removed For This Site",
                                    "GIF Files Are Not Removed For This Site", "images", "");
    editImagesMenuLayout.addControl(removePNGFilesTile, QVector<int>({4, 4, 4}));
    editImagesMenuLayout.addEmptyRows(2);
    editImagesMenuLayout.addControl(removeJPEGFilesTile, QVector<int>({4, 4, 4}));
    editImagesMenuLayout.addEmptyRows(2);
    editImagesMenuLayout.addControl(removeGIFFilesTile, QVector<int>({4, 4, 4}));
    editImagesMenuLayout.addEmptyRows(2);
    return editImagesMenuLayout;
}
void BrowserEditImages::applyEditImageSettings(bool removePNGFiles, bool removeJPEGFiles, bool removeGIFFiles)
{
    removeImageFiles(removePNGFiles, "png", "removePNGFiles");
    removeImageFiles(removeJPEGFiles, "jpeg", "removeJPEGFiles");
    removeImageFiles(removeGIFFiles, "gif", "removeGIFFiles");
    secondWebEngineView->setVisible(true);
    webEngineView->setFixedHeight(160);
}
void BrowserEditImages::removeImageFiles(bool currentState, QString imageExtension, QString imageTitle)
{
    BrowserSettings settings(secondWebEngineView);
    QVector<QVector<QString>> tableContents = settings.getExistingSettings(imageTitle);
    if(currentState)
    {
        executeRemovalOfImageFiles(imageExtension);
        settings.writeNewSetting(tableContents, imageTitle, imageExtension);
    }
    else
    {
        settings.deleteExistingSetting(tableContents);
        secondWebEngineView->reload();
    }
}
void BrowserEditImages::executeRemovalOfImageFiles(QString imageExtension)
{
    BrowserJavaScriptFiles javascriptFiles(secondWebEngineView);
    javascriptFiles.addJQuery();
    secondWebEngineView->page()->runJavaScript("jQuery.jQuery('[src*=" + imageExtension + "]').remove();");
}
