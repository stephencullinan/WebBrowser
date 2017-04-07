#ifndef BROWSERSEARCH_H
#define BROWSERSEARCH_H
#include <QObject>
#include <QString>
#include <QWebEngineView>
class BrowserSearch : public QObject
{
    Q_OBJECT
public:
    explicit BrowserSearch(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);
signals:
public slots:
    QString performSearchOnGoogle();
    void performSelectedSearch(QString searchTerm);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERSEARCH_H
