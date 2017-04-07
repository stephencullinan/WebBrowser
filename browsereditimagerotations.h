#ifndef BROWSEREDITIMAGEROTATIONS_H
#define BROWSEREDITIMAGEROTATIONS_H
#include "layout.h"
#include <QObject>
#include <QWebEngineView>
class BrowserEditImageRotations : public QObject
{
    Q_OBJECT
public:
    explicit BrowserEditImageRotations(QWebEngineView* secondWebEngineView, QWebEngineView *webEngineView,
                                       QObject *parent = 0);

signals:

public slots:
    QString editImageRotationsMenu();
    void applyImageRotationSettings(int imageRotationsDegrees, int imageRotationsTime);
    void executeImageRotations(int imageRotationsDegrees, int imageRotationsTime);
    Layout createLayout(QString imagesRotationsDegree, QString imagesRotationsTime);
private:
    QWebEngineView* secondWebEngineView;
    QWebEngineView* webEngineView;
};

#endif // BROWSEREDITIMAGEROTATIONS_H
