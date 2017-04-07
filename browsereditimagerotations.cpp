#include "browsereditimagerotations.h"
#include "browserjavascriptfiles.h"
#include "browsersettings.h"
#include "layout.h"
#include "tileselected.h"
#include "updatepanel.h"
#include <QWebEngineView>
BrowserEditImageRotations::BrowserEditImageRotations(QWebEngineView* secondWebEngineView,
                                                     QWebEngineView* webEngineView,
                                                     QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserEditImageRotations::editImageRotationsMenu()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout editImageRotationsMenuLayout;
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> imageRotationsDegreesSettings =
    browserSettings.getExistingSettings("imagesRotationDegrees");
    QVector<QVector<QString>> imageRotationsTimeSettings = browserSettings.getExistingSettings("imagesRotationTime");
    if(imageRotationsDegreesSettings.count() > 0 && imageRotationsTimeSettings.count() > 0)
        editImageRotationsMenuLayout = createLayout(imageRotationsDegreesSettings.at(0).at(2),
                                                    imageRotationsTimeSettings.at(0).at(2));
    else
        editImageRotationsMenuLayout = createLayout("", "");
    CommandButton editImageRotationsSubmitButton("Apply", "Apply Your Settings", "checkmark", "success",
                                                 "applyEditImageRotations();");
    editImageRotationsMenuLayout.addControl(editImageRotationsSubmitButton, QVector<int>({4, 4, 4}));
    return editImageRotationsMenuLayout.toHTML();
}
Layout BrowserEditImageRotations::createLayout(QString imagesRotationsDegree, QString imagesRotationsTime)
{
    Layout editImageRotationsMenuLayout;
    TileSelected editImageRotationsMenuSelectedTile("editImageRotationsMenuSelectedTile", true,
                                                    "Image Rotation Settings Are Active For This Site",
                                                    "Image Rotation Settings Are Not Active For This Site",
                                                    "images", "editImageRotationsUpdatePanel");
    editImageRotationsMenuLayout.addControl(editImageRotationsMenuSelectedTile, QVector<int>({4, 4, 4}));
    UpdatePanel editImageRotationsUpdatePanel("editImageRotationsUpdatePanel");
    Layout editImageRotationsLayout;
    TextBox editImageRotationsDegreesTextBox("Please enter the preferred rotation of the images", "images",
                                             "editImageRotationsDegreesTextBox", imagesRotationsDegree);
    editImageRotationsLayout.addControl(editImageRotationsDegreesTextBox, QVector<int>({0, 12, 0}));
    TextBox editImageTransitionTextBox("Please enter the preferred period of transition of the images",
                                       "images", "editImageTransitionTextBox", imagesRotationsTime);
    editImageRotationsLayout.addControl(editImageTransitionTextBox, QVector<int>({0, 12, 0}));
    editImageRotationsUpdatePanel.addControl(editImageRotationsLayout);
    editImageRotationsMenuLayout.addControl(editImageRotationsUpdatePanel, QVector<int>({0, 12, 0}));
    return editImageRotationsMenuLayout;
}

void BrowserEditImageRotations::applyImageRotationSettings(int imageRotationsDegrees, int imageRotationsTime)
{
    BrowserSettings browserSettings(secondWebEngineView);
    QVector<QVector<QString>> imageRotationDegreesSettings =
    browserSettings.getExistingSettings("imagesRotationDegrees");
    QVector<QVector<QString>> imageRotationTimeSettings = browserSettings.getExistingSettings("imagesRotationTime");
    if(imageRotationsDegrees > -1 && imageRotationsDegrees < 361 && imageRotationsTime > -1)
    {
        executeImageRotations(imageRotationsDegrees, imageRotationsTime);
        browserSettings.writeNewSetting(imageRotationDegreesSettings, "imagesRotationDegrees",
                                        QString::number(imageRotationsDegrees));
        browserSettings.writeNewSetting(imageRotationTimeSettings, "imagesRotationTime",
                                        QString::number(imageRotationsTime));
    }
    else
    {
        browserSettings.deleteExistingSetting(imageRotationDegreesSettings);
        browserSettings.deleteExistingSetting(imageRotationTimeSettings);
        secondWebEngineView->reload();
    }
    webEngineView->setFixedHeight(160);
    secondWebEngineView->setVisible(true);
}
void BrowserEditImageRotations::executeImageRotations(int imageRotationsDegrees, int imageRotationsTime)
{
    BrowserJavaScriptFiles javaScriptFiles(secondWebEngineView);
    javaScriptFiles.addJQuery();
    QString setImageRotations = "jQuery.jQuery('img').each( function () { ";
    setImageRotations.append("jQuery.jQuery(this).css('-webkit-transition', '-webkit-transform " +
                             QString::number(imageRotationsTime) + "s');");
    setImageRotations.append("jQuery.jQuery(this).css('-webkit-transform', 'rotate(" +
                             QString::number(imageRotationsDegrees) + "deg)')}); undefined");
    secondWebEngineView->page()->runJavaScript(setImageRotations);
}
