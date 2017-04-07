#ifndef BROWSERJAVASCRIPTFILES_H
#define BROWSERJAVASCRIPTFILES_H
#include <QObject>
#include <QWebEngineView>
class BrowserJavaScriptFiles : public QObject
{
    Q_OBJECT
public:
    explicit BrowserJavaScriptFiles(QWebEngineView* secondWebEngineView, QObject *parent = 0);
    void addJQuery();
    void addFindAndReplaceDOMText();
signals:
public slots:
private:
    QWebEngineView* secondWebEngineView;
    void addFile(QString fileName);
};

#endif // BROWSERJAVASCRIPTFILES_H
