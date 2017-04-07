#ifndef FLUENTMENU_H
#define FLUENTMENU_H
#include <QString>
#include "component.h"
#include "fluenttabpanel.h"
class FluentMenu : public Component
{
public:
    FluentMenu(QVector<QString> menuTitles, QVector<FluentTabPanel> fluentTabPanels, QString fluentMenuID,
               QString onClickEvent);
private:
    void createControl();
    QString fluentMenuID;
    QString onClickEvent;
    QVector<QString> menuTitles;
    QVector<FluentTabPanel> fluentTabPanels;
};

#endif // FLUENTMENU_H
