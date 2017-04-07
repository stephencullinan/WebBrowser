#include "database.h"
#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QVector>
#include <QMap>
Database::Database(QString databaseName)
{
    this->databaseName = databaseName;
}
Database::Database(QString databaseName, QString hostName, QString username, QString password)
{
    this->databaseName = databaseName;
    this->hostName = hostName;
    this->username = username;
    this->password = password;
    this->database = QSqlDatabase::addDatabase("QMYSQL");
    this->database.setDatabaseName(this->databaseName);
    this->database.setHostName(this->hostName);
    this->database.setUserName(this->username);
    this->database.setPassword(this->password);
}
void Database::open()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseName + ".db");
    database.open();
}
void Database::close()
{
    database.close();
    QSqlDatabase::removeDatabase("QSQLITE");
}
QVector<QVector<QString>> Database::getTableContents(QString tableName, QMap<QString, QString>* selectedParameters,
                                             QVector<QString> columnTitles)
{
    QVector<QVector<QString>> tableContents;
    open();
    QString queryText = "SELECT ";
    if(columnTitles.count() == 0)
        queryText += "* ";
    else
    {
        for(QString aColumnTitle : columnTitles)
            queryText += aColumnTitle + ", ";
        queryText = queryText.mid(0, queryText.length() - 2);
    }
    queryText += " FROM " + tableName;
    queryText = addWhereClause(queryText, selectedParameters);
    QSqlQuery* aSqlQuery = new QSqlQuery();
    aSqlQuery->exec(queryText);
    QSqlRecord aRecord = aSqlQuery->record();
    int numberOfColumns = aRecord.count();
    while(aSqlQuery->next())
    {
        QVector<QString> aTableRow;
        for(int counter = 0; counter < numberOfColumns; counter++)
            aTableRow.append(aSqlQuery->value(counter).toString());
        tableContents.append(aTableRow);
    }
    close();
    return tableContents;
}
QVector<QVector<QString>> Database::getJoinedTableContents(QVector<QString> tableNames,
                                                           QVector<QString> joinConditions,
                                                           QVector<QString> columnTitles,
                                                           QVector<QString> groupConditions,
                                                           QVector<QString> orderConditions,
                                                           QMap<QString, QString> *selectedParameters)
{
    QVector<QVector<QString>> tableContents;
    open();
    QString queryText = "SELECT ";
    if(columnTitles.count() == 0)
        queryText.append("*");
    else
    {
        for(QString aColumnTitle : columnTitles)
            queryText += aColumnTitle + ", ";
        queryText = queryText.mid(0, queryText.length() - 2);
    }
    queryText.append(" FROM " + tableNames.at(0));
    for(int counter = 0, index = 1; counter < joinConditions.count() && index < tableNames.count();
        counter = counter + 2, index++)
        queryText.append(" JOIN " + tableNames.at(index) + " ON " + joinConditions.at(counter) + " = " +
                         joinConditions.at(counter + 1));
    if(groupConditions.count() > 0)
    {
        queryText.append(" GROUP BY ");
        for(QString aGroupCondition: groupConditions)
            queryText += aGroupCondition + ", ";
        queryText = queryText.mid(0, queryText.length() - 2);
    }
    queryText = addWhereClause(queryText, selectedParameters);
    if(orderConditions.count() > 0)
    {
        queryText.append(" ORDER BY ");
        for(QString anOrderCondition : orderConditions)
            queryText += anOrderCondition + ", ";
        queryText = queryText.mid(0, queryText.length() - 2);
    }
    QSqlQuery aSqlQuery;
    aSqlQuery.exec(queryText);
    QSqlRecord aRecord = aSqlQuery.record();
    int numberOfColumns = aRecord.count();
    while(aSqlQuery.next())
    {
        QVector<QString> aTableRow;
        for(int counter = 0; counter < numberOfColumns; counter++)
            aTableRow.append(aSqlQuery.value(counter).toString());
        tableContents.append(aTableRow);
    }
    close();
    return tableContents;
}
QVector<QVector<QString>> Database::getJoinedTableContents(QVector<QString> tableNames,
                                                           QVector<QString> joinConditions,
                                                           QVector<QString> columnTitles,
                                                           QMap<QString, QString>* selectedParameters)
{
    return getJoinedTableContents(tableNames, joinConditions, columnTitles, QVector<QString>({}),
                                  QVector<QString>({}), selectedParameters);
}

int Database::getMaxValueOfColumn(QString tableName, QString columnName)
{
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    return getSelectedValueOfColumn(tableName, columnName, "MAX", selectedParameters);
}
int Database::getAverageValueOfColumn(QString tableName, QString columnName,
                                      QMap<QString, QString>* selectedParameters)
{
    return getSelectedValueOfColumn(tableName, columnName, "AVG", selectedParameters);
}
void Database::insertRow(QString tableName, QVector<QString> rowContents)
{
    open();
    QString queryText = "INSERT INTO " + tableName + " VALUES (";
    QSqlQuery* aSqlQuery = new QSqlQuery();
    int location = 0;
    for(QString aRowContent : rowContents)
    {
        aRowContent = aRowContent.replace("'", "");
        if((aRowContent).toDouble())
            queryText += aRowContent + ", ";
        else
            queryText += "'" + aRowContent + "', ";
        location++;
    }
    queryText = queryText.mid(0, queryText.length() - 2);
    queryText += ");";
    aSqlQuery->exec(queryText);
    close();
}
void Database::deleteRow(QString tableName, QMap<QString, QString>* selectedParameters)
{
    open();
    QString queryText = "DELETE FROM " + tableName;
    QSqlQuery* aSqlQuery = new QSqlQuery();
    queryText = addWhereClause(queryText, selectedParameters);
    aSqlQuery->exec(queryText);
    close();
}
void Database::updateRow(QString tableName, QMap<QString, QString>* selectedParameters,
                         QMap<QString, QString> updatedContents)
{
    open();
    QString queryText = "UPDATE " + tableName;
    QSqlQuery* aSqlQuery = new QSqlQuery();
    if(updatedContents.count() > 0)
    {
        queryText += " SET ";
        for(auto anUpdatedContent : updatedContents.keys())
        {
            if((updatedContents.value(anUpdatedContent)).toDouble())
                queryText += anUpdatedContent + " = " + updatedContents.value(anUpdatedContent) + ", ";
            else
                queryText += anUpdatedContent + " = '" + updatedContents.value(anUpdatedContent) + "', ";
        }
        queryText = queryText.mid(0, queryText.length() - 2);
    }
    queryText = addWhereClause(queryText, selectedParameters);
    aSqlQuery->prepare(queryText);
    aSqlQuery->exec();
    close();
}
int Database::getSelectedValueOfColumn(QString tableName, QString columnName, QString operation,
                                       QMap<QString, QString>* selectedParameters)
{
    int selectedValue = 0;
    open();
    QString queryText = "SELECT " + operation + " (" + columnName + ") FROM " + tableName;
    queryText = addWhereClause(queryText, selectedParameters);
    QSqlQuery aSqlQuery;
    aSqlQuery.exec(queryText);
    QSqlRecord aRecord = aSqlQuery.record();
    int numberOfColumns = aRecord.count();
    while(aSqlQuery.next())
        for(int counter = 0; counter < numberOfColumns; counter++)
            selectedValue = aSqlQuery.value(counter).toInt();
    close();
    return selectedValue;
}
QString Database::addWhereClause(QString queryText, QMap<QString, QString>* selectedParameters)
{
    if(selectedParameters->count() > 0)
    {
        queryText += " WHERE ";
        for(auto aSelectedParameter : selectedParameters->keys())
        {
            if((selectedParameters->value(aSelectedParameter)).toDouble())
                queryText += aSelectedParameter + " = " + selectedParameters->value(aSelectedParameter) + " AND ";
            else
                queryText += aSelectedParameter + " LIKE '" + selectedParameters->value(aSelectedParameter) +
                "' AND ";
        }
        queryText = queryText.mid(0, queryText.length() - 5);
    }
    return queryText;
}
