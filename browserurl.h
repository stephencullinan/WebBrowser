#ifndef BROWSERURL_H
#define BROWSERURL_H
#include <QObject>
#include <QWebEngineView>
class BrowserURL : public QObject
{
    Q_OBJECT
public:
    explicit BrowserURL(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);
signals:
public slots:
    QString openURLPage();
    void openSelectedURL(QString selectedURL);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERURL_H
