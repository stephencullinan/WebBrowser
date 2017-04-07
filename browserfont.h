#ifndef BROWSERFONT_H
#define BROWSERFONT_H
#include <QObject>
#include <QString>
#include <QWebEngineView>
class BrowserFont : public QObject
{
    Q_OBJECT
public:
    explicit BrowserFont(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);

signals:

public slots:
    QString createNewFont();
    QString saveCreatedFont(QString fontFace);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSERFONT_H
