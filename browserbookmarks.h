#ifndef BROWSERBOOKMARKS_H
#define BROWSERBOOKMARKS_H
#include "database.h"
#include <QObject>
#include <QWebEngineView>
class BrowserBookmarks : public QObject
{
    Q_OBJECT
public:
    explicit BrowserBookmarks(QWebEngineView* secondWebEngineView,
                              QWebEngineView *webEngineView, QObject *parent = 0);
signals:

public slots:
    QString createNewBookmark();
    QString saveCreatedBookmark(QString siteUrl, QString siteTitle);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    Database* database;
};

#endif // BROWSERBOOKMARKS_H
