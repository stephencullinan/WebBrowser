#ifndef BROWSEREDITTEXTREPLACEMENTS_H
#define BROWSEREDITTEXTREPLACEMENTS_H
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserEditTextReplacements : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditTextReplacements(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView,
                                         QObject *parent = 0);
signals:

public slots:
    QString replaceTextMenu(bool textReplacementsOnly);
    QString replaceTextSuggestion(QString locateText, QString replaceText);
    void applyReplaceText(QString locate, QString replace, bool textReplacementsOnly);
    void executeReplaceText(QString locate, QString replace, bool textReplacementsOnly);
    Layout createLayout(bool textReplacementsOnly, bool includeExistingSettings);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSEREDITTEXTREPLACEMENTS_H
