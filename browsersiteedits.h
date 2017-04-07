#ifndef BROWSERSITEEDITS_H
#define BROWSERSITEEDITS_H

#include <QObject>
#include <QWebEngineView>
class BrowserSiteEdits : public QObject
{
    Q_OBJECT
public:
    explicit BrowserSiteEdits(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, int siteID,
                              QObject *parent = 0);

signals:

public slots:
private:
    int siteID;
    void applyEditsToSite();
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERSITEEDITS_H
