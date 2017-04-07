#include "accordion.h"
#include "browsertables.h"
#include "commandbutton.h"
#include "database.h"
#include "heading.h"
#include "layout.h"
#include "table.h"
#include <QJsonArray>
#include <QMap>
#include <QObject>
#include <QVector>
#include <QWebEngineView>
BrowserTables::BrowserTables(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                             QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->database = new Database("Information");
}
QString BrowserTables::createFormattedHTMLTable(QString tableTitle, QString formattedTableTitle)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QVector<QVector<QString>> tableContents = extractDataFromSpecifiedTable(tableTitle);
    QVector<QString> rowTitles({formattedTableTitle + " ID", "Site Title", "Site Url", "Date"});
    QVector<QString> rowClickEvents;
    if(tableTitle == "feed")
        for(QVector<QString> selectedRow : tableContents)
            rowClickEvents.push_back("viewFeeds('" + selectedRow.at(2) + "');");
    Table aTable("table_" + formattedTableTitle, rowTitles, tableContents, rowClickEvents);
    return aTable.toHTML();
}
QString BrowserTables::createHTMLTable(QString tableTitle)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    QVector<QString> columnTitles({"Code", "Font"});
    QVector<QVector<QString>> tableContents = database->getTableContents(tableTitle, selectedParameters,
                                                                         columnTitles);
    Table aTable("table_" + tableTitle, columnTitles, tableContents);
    return aTable.toHTML();
}
QVector<QVector<QString>> BrowserTables::extractDataFromSpecifiedTable(QString tableTitle)
{
    QVector<QString> tableTitles({tableTitle, "site"});
    QVector<QString> joinConditions({tableTitle + ".site", "site.code"});
    QVector<QString> columnTitles({tableTitle + ".code", "site.title", "site.url", tableTitle + ".date"});
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    QVector<QVector<QString>> tableContents = database->getJoinedTableContents(tableTitles, joinConditions,
                                                                               columnTitles, selectedParameters);
    return tableContents;
}
QString BrowserTables::createFormattedHTMLTableForDeletions(QString tableTitle, QString formattedTableTitle)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QVector<QVector<QString>> tableContents = extractDataFromSpecifiedTable(tableTitle);
    QVector<QString> rowTitles({formattedTableTitle + " ID", "Site Title", "Site Url", "Date"});
    QVector<QString> rowClickEvents;
    for(QVector<QString> selectedRow : tableContents)
        rowClickEvents.push_back("deleteSelectedRowFromTable('" + tableTitle + "', '" + formattedTableTitle +
                                 "', " + convertVectorToJavaScriptArray(rowTitles) + ", " +
                                 convertVectorToJavaScriptArray(selectedRow) + ");");
    Table aTable("table_" + formattedTableTitle, rowTitles, tableContents, rowClickEvents);
    return aTable.toHTML();
}
QString BrowserTables::createHTMLTableForDeletions(QString tableTitle, QString formattedTableTitle)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    QVector<QString> columnTitles({"Code", "Font"});
    QVector<QVector<QString>> tableContents = database->getTableContents(tableTitle, selectedParameters,
                                                                         columnTitles);
    QVector<QString> rowClickEvents;
    for(QVector<QString> selectedRow : tableContents)
        rowClickEvents.push_back("deleteSelectedRowFromTable('" + tableTitle + "', '" + formattedTableTitle +
                                 "', " + convertVectorToJavaScriptArray(columnTitles) + ", " +
                                 convertVectorToJavaScriptArray(selectedRow) + ");");
    Table aTable("table_" + formattedTableTitle, columnTitles, tableContents, rowClickEvents);
    return aTable.toHTML();
}
QString BrowserTables::displayDeleteNotification(QString tableName, QString formattedTableName,
                                                 QJsonArray columnTitles, QJsonArray rowValues)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aLayout;
    aLayout.addControl(Heading("Are you sure you wish to delete this row from " + formattedTableName + "?"),
                       QVector<int>({0, 12, 0}));
    QVector<QString> formattedColumnTitles = convertJSONArrayToVector(columnTitles);
    QVector<QString> formattedRowValues = convertJSONArrayToVector(rowValues);
    QVector<QVector<QString>> tableValues;
    tableValues.push_back(formattedRowValues);
    Table aTable("deleteTable", formattedColumnTitles, tableValues);
    aLayout.addControl(aTable, QVector<int>({0, 12, 0}));
    aLayout.addControl(CommandButton("Delete", "Delete This Row", "bin", "danger",
                                    "deleteConfirmation('" + tableName + "', '" + formattedTableName + "', " +
                                    convertVectorToJavaScriptArray(formattedRowValues) + ");"),
                                    QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Delete This Row"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"bin"}));
    return anAccordion.toHTML();
}
QString BrowserTables::displayExpungeNotification(QString tableName, QString formattedTableName)
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout aLayout;
    aLayout.addControl(Heading("Are you sure you wish to delete all information in the table titled "
                               + formattedTableName + "?"), QVector<int>({0, 12, 0}));
    aLayout.addControl(CommandButton("Delete", "Delete All Rows", "bin", "danger",
                      "expungeConfirmation('" + tableName + "', '" + formattedTableName + "');"),
                      QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Delete All Rows"}), QVector<Layout>({aLayout}),
                          QVector<QString>({"bin"}));
    return anAccordion.toHTML();
}
QString BrowserTables::deleteSelectedRow(QString tableName, QString formattedTableName, QJsonArray rowValues)
{
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    selectedParameters->insert("code", convertJSONArrayToVector(rowValues).at(0));
    database->deleteRow(tableName, selectedParameters);
    if(tableName == "font")
        return createHTMLTableForDeletions(tableName, formattedTableName);
    return createFormattedHTMLTableForDeletions(tableName, formattedTableName);
}
QString BrowserTables::deleteAllRows(QString tableName, QString formattedTableName)
{
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    database->deleteRow(tableName, selectedParameters);
    return createFormattedHTMLTable(tableName, formattedTableName);
}
QVector<QString> BrowserTables::convertJSONArrayToVector(QJsonArray anArray)
{
    QVector<QString> formattedArray;
    for(int counter = 0; counter < anArray.count(); counter++)
        formattedArray.push_back(anArray[counter].toString());
    return formattedArray;
}
QString BrowserTables::convertVectorToJavaScriptArray(QVector<QString> aVector)
{
    QString formattedOutput = "[";
    for(QString aVectorItem : aVector)
        formattedOutput += "'" + aVectorItem + "', ";
    return formattedOutput.mid(0, formattedOutput.length() - 2) + "]";
}
