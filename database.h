#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QMap>
#include <QtSql/QSqlDatabase>
#include <QVector>
class Database
{
public:
    Database(QString databaseName);
    Database(QString databaseName, QString hostName, QString username, QString password);
    QVector<QVector<QString>> getTableContents(QString tableName, QMap<QString, QString>* selectedParameters,
                                               QVector<QString> columnTitles);
    QVector<QVector<QString>> getJoinedTableContents(QVector<QString> tableNames, QVector<QString> joinConditions,
                                                     QVector<QString> columnTitles,
                                                     QMap<QString, QString>* selectedParameters);
    QVector<QVector<QString>> getJoinedTableContents(QVector<QString> tableNames,
                                                     QVector<QString> joinConditions,
                                                     QVector<QString> columnTitles,
                                                     QVector<QString> groupConditions,
                                                     QVector<QString> orderConditions,
                                                     QMap<QString, QString> *selectedParameters);
    void insertRow(QString tableName, QVector<QString> rowContents);
    void updateRow(QString tableName, QMap<QString, QString>* selectedParameters,
                   QMap<QString, QString> updatedContents);
    int getMaxValueOfColumn(QString tableName, QString columnName);
    int getAverageValueOfColumn(QString tableName, QString columnName, QMap<QString, QString> *selectedParameters);
    void deleteRow(QString tableName, QMap<QString, QString>* selectedParameters);
    void open();
    void close();
private:
    QString databaseName;
    QString hostName;
    QString username;
    QString password;
    QSqlDatabase database;
    int getSelectedValueOfColumn(QString tableName, QString columnName, QString operation,
                                 QMap<QString, QString> *selectedParameters);
    QString addWhereClause(QString queryText, QMap<QString, QString>* selectedParameters);
};

#endif // DATABASE_H
