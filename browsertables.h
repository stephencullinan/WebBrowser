#ifndef BROWSERTABLES_H
#define BROWSERTABLES_H
#include "database.h"
#include <QJsonArray>
#include <QObject>
#include <QString>
#include <QWebEngineView>
class BrowserTables : public QObject
{
    Q_OBJECT
public:
    explicit BrowserTables(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);
signals:
public slots:
    QString createFormattedHTMLTable(QString tableTitle, QString formattedTableTitle);
    QString createFormattedHTMLTableForDeletions(QString tableTitle, QString formattedTableTitle);
    QString displayDeleteNotification(QString tableName, QString formattedTableName,
                                      QJsonArray columnTitles, QJsonArray rowValues);
    QString displayExpungeNotification(QString tableName, QString formattedTableName);
    QString deleteSelectedRow(QString tableName, QString formattedTableName, QJsonArray rowValues);
    QString deleteAllRows(QString tableName, QString formattedTableName);
    QVector<QVector<QString>> extractDataFromSpecifiedTable(QString tableTitle);
    QString createHTMLTable(QString tableTitle);
    QString createHTMLTableForDeletions(QString tableTitle, QString formattedTableTitle);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    Database* database;
    QVector<QString> convertJSONArrayToVector(QJsonArray anArray);
    QString convertVectorToJavaScriptArray(QVector<QString> aVector);
};

#endif // BROWSERTABLES_H
