#ifndef BROWSERABOUT_H
#define BROWSERABOUT_H
#include <QObject>
#include <QWebEngineView>
class BrowserAbout : public QObject
{
    Q_OBJECT
public:
    explicit BrowserAbout(QWebEngineView *secondWebEngine, QWebEngineView *webEngine, QObject *parent = 0);
signals:
public slots:
    QString getAboutMenu();
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERABOUT_H
