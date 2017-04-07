#ifndef BROWSERSETTINGS_H
#define BROWSERSETTINGS_H
#include "database.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QWebEngineView>
class BrowserSettings : public QObject
{
    Q_OBJECT
public:
    explicit BrowserSettings(QWebEngineView* secondWebEngineView, QObject *parent = 0);
    QVector<QVector<QString>> getExistingSettings(QString settingTitle);
    void deleteExistingSetting(QVector<QVector<QString>> tableContents);
    void writeNewSetting(QVector<QVector<QString>> tableContents, QString settingTitle, QString settingValue);
    QVector<QString> removeEmptyElements(QVector<QString> listWithEmptyElements);
signals:

public slots:
private:
    Database* database;
    QWebEngineView* secondWebEngineView;
};

#endif // BROWSERSETTINGS_H
