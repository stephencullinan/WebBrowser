#ifndef BROWSEREDITFONT_H
#define BROWSEREDITFONT_H
#include "layout.h"
#include <QObject>
#include <QString>
#include <QWebEngineView>
class BrowserEditFont : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditFont(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);
signals:

public slots:
    QString editFontMenu();
    void applyFontSettings(QString fontFace, int fontSize);
    void executeFontFace(QString fontFace);
    void executeFontSize(int fontSize);
    Layout createLayout(QString fontFace, QString fontSize);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSEREDITFONT_H
