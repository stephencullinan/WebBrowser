#ifndef BROWSEREDITLINKSCOLOUR_H
#define BROWSEREDITLINKSCOLOUR_H
#include "browsersettings.h"
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserEditLinksColour : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditLinksColour(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView,
                                    QObject *parent = 0);
signals:

public slots:
    QString applyLinksColourMenu();
    void applyLinksColourSettings(QString colourTitle);
    void executeLinksColour(QString colourTitle);
    Layout createLayout(QString existingSelectedColour);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSEREDITLINKSCOLOUR_H
