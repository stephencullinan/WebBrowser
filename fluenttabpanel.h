#ifndef FLUENTTABPANEL_H
#define FLUENTTABPANEL_H
#include <QString>
#include <QVector>
#include "component.h"
#include "fluenttabgroup.h"
class FluentTabPanel : public Component
{
public:
    FluentTabPanel(QString fluentTabPanelID, QVector<FluentTabGroup> fluentTabGroups, QString style);
    FluentTabPanel(QString fluentTabPanelID, QVector<FluentTabGroup> fluentTabGroups);
    FluentTabPanel();
private:
    QString fluentTabPanelID;
    QVector<FluentTabGroup> fluentTabGroups;
    QString style;
    void createControl();
};

#endif // FLUENTTABPANEL_H
