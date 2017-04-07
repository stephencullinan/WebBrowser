#include "browserjavascriptfiles.h"
#include <QFile>
#include <QString>
#include <QWebEngineView>
BrowserJavaScriptFiles::BrowserJavaScriptFiles(QWebEngineView* secondWebEngineView, QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
}
void BrowserJavaScriptFiles::addJQuery()
{
    addFile("jquery-3.1.1.min.js");
}
void BrowserJavaScriptFiles::addFindAndReplaceDOMText()
{
    addFile("findAndReplaceDOMText.js");
}
void BrowserJavaScriptFiles::addFile(QString fileName)
{
    QFile aFile;
    aFile.setFileName(fileName);
    aFile.open(QIODevice::ReadOnly);
    QString fileText = aFile.readAll();
    if(fileName == "jquery-3.1.1.min.js")
        fileText.append("\nvar jQuery = {'jQuery' : jQuery.noConflict(true)};");
    aFile.close();
    secondWebEngineView->page()->runJavaScript(fileText);
}
