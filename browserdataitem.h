#ifndef BROWSERDATAITEM_H
#define BROWSERDATAITEM_H

#include <QObject>

class BrowserDataItem : public QObject
{
    Q_OBJECT
public:
    explicit BrowserDataItem(QObject *parent = 0);

signals:

public slots:
    void saveDataItemToSpecifiedTable(QString siteUrl, QString siteTitle, QString tableName);
    void saveDataItemToSpecifiedTableWithNoJoins(QString tableName, QVector<QString> tableRow);
};

#endif // BROWSERDATAITEM_H
