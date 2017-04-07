#ifndef BROWSERTHEME_H
#define BROWSERTHEME_H
#include "layout.h"
#include <QObject>
#include <QJsonArray>
#include <QWebEngineView>
class BrowserTheme : public QObject
{
    Q_OBJECT
public:
    explicit BrowserTheme(QWebEngineView *secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);

signals:

public slots:
    QString createNewThemeStepOne();
    QString createNewThemeStepTwo(QJsonArray parameters);
    QString createNewThemeStepThree(QString linksColour);
    QString createNewThemeStepFour(QString backgroundColour);
    QString createNewThemeStepFive(QString fontFace, QString fontSize);
    QString createNewThemeStepSix(QString originalText, QString replaceText);
    QString createNewThemeStepSeven(QString originalText, QString replaceText);
    QString createNewThemeStepEight(QString imagesRotationDegrees, QString imagesRotationTimes);
    QString createNewThemeStepNine(bool removePNGFiles, bool removeJPEGFiles, bool removeGIFFiles);
    QString viewAvailableThemes(bool viewingOnly);
    QString deleteExistingTheme(int themeID, QString themeTitle);
    QString deleteExistingThemeConfirmation(int themeID);
    QString viewDetailedDescriptionPageForTheme(int themeID);
    QString addNewReview();
    QString saveNewReview(int reviewRating, QString reviewDescription, QString firstName, QString lastName);
    QString applyThemeToSite(bool applyThemeToSite);
private:
    QVector<QString> convertJSONArrayToVector(QJsonArray aJSONArray);
    void insertThemeSetting(QString themeSettingTitle, QString themeSettingValue);
    int retrieveCurrentSiteID();
    Layout createReviews();
    Layout createSitesLayout();
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    int themeID;
};

#endif // BROWSERTHEME_H
