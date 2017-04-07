#include "browsersettings.h"
#include "database.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserSettings::BrowserSettings(QWebEngineView* secondWebEngineView, QObject *parent) : QObject(parent)
{
    this->database = new Database("Information");
    this->secondWebEngineView = secondWebEngineView;
}
QVector<QVector<QString>> BrowserSettings::getExistingSettings(QString settingTitle)
{
    QVector<QString> tableNames({"sitesetting", "site"});
    QVector<QString> joinConditions({"sitesetting.site", "site.code"});
    QVector<QString> columnTitles({"sitesetting.code", "sitesetting.title", "sitesetting.value", "site.code",
                                   "site.title", "site.url"});
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("site.url", secondWebEngineView->url().toDisplayString());
    selectedParameters->insert("sitesetting.title", settingTitle);
    return database->getJoinedTableContents(tableNames, joinConditions, columnTitles, selectedParameters);
}
void BrowserSettings::deleteExistingSetting(QVector<QVector<QString>> tableContents)
{
    if(tableContents.count() > 0)
    {
        QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
        selectedParameters->insert("code", tableContents.at(0).at(0));
        database->deleteRow("sitesetting", selectedParameters);
    }
}
void BrowserSettings::writeNewSetting(QVector<QVector<QString>> tableContents, QString settingTitle,
                                      QString settingValue)
{
    if(tableContents.count() > 0)
    {
        QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
        selectedParameters->insert("code", tableContents.at(0).at(0));
        QMap<QString, QString> updatedParameters({{"value", settingValue}});
        database->updateRow("sitesetting", selectedParameters, updatedParameters);
    }
    else
    {
        int maximumValue = database->getMaxValueOfColumn("sitesetting", "code");
        QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
        selectedParameters->insert("url", secondWebEngineView->url().toDisplayString());
        QVector<QString> columnTitles({"code"});
        QVector<QVector<QString>> siteTableContents = database->getTableContents("site", selectedParameters,
                                                                                 columnTitles);
        if(siteTableContents.count() > 0)
        {
            QVector<QString> rowContents({QString::number(++maximumValue), siteTableContents.at(0).at(0),
                                         settingTitle, settingValue});
            database->insertRow("sitesetting", rowContents);
        }
    }
}
QVector<QString> BrowserSettings::removeEmptyElements(QVector<QString> listWithEmptyElements)
{
    for(int counter = 0; counter < listWithEmptyElements.length(); counter++)
        if(listWithEmptyElements.at(counter).length() == 0)
            listWithEmptyElements.removeAt(counter);
    return listWithEmptyElements;
}
