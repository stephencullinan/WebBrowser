#ifndef BROWSERTABLEAU_H
#define BROWSERTABLEAU_H
#include "database.h"
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserTableau : public QObject
{
    Q_OBJECT
public:
    explicit BrowserTableau(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                            QObject *parent = 0);
signals:
public slots:
    QString createTableau();
    QString sortItems(QString orderByCondition, int numberOfItems);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    Database* database;
    Layout createTiles(QString orderByCondition, int numberOfItems);
};

#endif // BROWSERTABLEAU_H
