#ifndef BROWSEREDITBACKGROUND_H
#define BROWSEREDITBACKGROUND_H
#include "database.h"
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserEditBackground : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditBackground(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView,
                                   QObject* parent = 0);
signals:
public slots:
    void applyBackgroundColourSettings(QString colourTitle);
    QString applyBackgroundColourMenu();
    void executeBackgroundColour(QString colourTitle);
    Layout createLayout(QString existingSelectedColour);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
    Database* database;
};

#endif // BROWSEREDITBACKGROUND_H
