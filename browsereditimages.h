#ifndef BROWSEREDITIMAGES_H
#define BROWSEREDITIMAGES_H
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserEditImages : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditImages(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView, QObject *parent = 0);

signals:

public slots:
    void removeImageFiles(bool currentState, QString imageExtension, QString imageTitle);
    void applyEditImageSettings(bool removePNGFiles, bool removeJPEGFiles, bool removeGIFFiles);
    QString getEditImagesMenu();
    void executeRemovalOfImageFiles(QString imageExtension);
    Layout createLayout(bool removePNGFiles, bool removeJPEGFiles, bool removeGIFFiles);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSEREDITIMAGES_H
