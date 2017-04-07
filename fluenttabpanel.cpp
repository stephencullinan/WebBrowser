#include "fluenttabpanel.h"
#include "fluenttabgroup.h"
#include <QString>
#include <QVector>
FluentTabPanel::FluentTabPanel(QString fluentTabPanelID, QVector<FluentTabGroup> fluentTabGroups, QString style)
{
    this->fluentTabPanelID = fluentTabPanelID;
    this->fluentTabGroups = fluentTabGroups;
    this->style = style;
    createControl();
}
FluentTabPanel::FluentTabPanel(QString fluentTabPanelID, QVector<FluentTabGroup> fluentTabGroups)
{
    this->fluentTabPanelID = fluentTabPanelID;
    this->fluentTabGroups = fluentTabGroups;
    this->style = "display:none;";
    createControl();
}
FluentTabPanel::FluentTabPanel()
{

}
void FluentTabPanel::createControl()
{
    html.append("<div class=\"tab-panel\" id=\"" + fluentTabPanelID + "\" style=\"" + style + "\">");
    for(FluentTabGroup aFluentTabGroup : fluentTabGroups)
        html.append(aFluentTabGroup.toHTML());
    html.append("</div>");
}
