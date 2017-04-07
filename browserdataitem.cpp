#include "browserdataitem.h"
#include "database.h"
#include <QDateTime>
#include <QDebug>
BrowserDataItem::BrowserDataItem(QObject *parent) : QObject(parent)
{

}
void BrowserDataItem::saveDataItemToSpecifiedTable(QString siteUrl, QString siteTitle, QString tableName)
{
    Database database("Information");
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("url", siteUrl);
    QVector<QString> columnTitles({"code"});
    int maximumSiteValue = 0;
    QVector<QVector<QString>> siteDetails = database.getTableContents("site", selectedParameters, columnTitles);
    if(siteDetails.count() == 0)
    {
        maximumSiteValue = database.getMaxValueOfColumn("site", "code");
        QVector<QString> newSiteDetails({QString::number(++maximumSiteValue), siteTitle, siteUrl});
        database.insertRow("site", newSiteDetails);
    }
    else
        maximumSiteValue = siteDetails.at(0).at(0).toInt();
    int maximumBookmarkValue = database.getMaxValueOfColumn(tableName, "code");
    QVector<QString> dataItemDetails({QString::number(++maximumBookmarkValue), QString::number(maximumSiteValue),
                                         QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")});
    database.insertRow(tableName, dataItemDetails);
}
void BrowserDataItem::saveDataItemToSpecifiedTableWithNoJoins(QString tableName, QVector<QString> tableRow)
{
    Database database("Information");
    int maximumTableValue = database.getMaxValueOfColumn(tableName, "code");
    tableRow.insert(0, QString::number(maximumTableValue + 1));
    database.insertRow(tableName, tableRow);
}
