#include "fluentmenu.h"
#include "fluenttabpanel.h"
#include <QDebug>
#include <QString>
#include <QVector>
FluentMenu::FluentMenu(QVector<QString> menuTitles, QVector<FluentTabPanel> fluentTabPanels, QString fluentMenuID,
                       QString onClickEvent)
{
    this->menuTitles = menuTitles;
    this->fluentTabPanels = fluentTabPanels;
    this->fluentMenuID = fluentMenuID;
    this->onClickEvent = onClickEvent;
    createControl();
}
void FluentMenu::createControl()
{
    html.append("<div class=\"fluent-menu\" data-role=\"fluentmenu\" id=\"" + fluentMenuID + "\">");
    html.append("<ul class=\"tabs-holder\" id=\"" + fluentMenuID + "_Holder\">");
    if(menuTitles.count() > 0)
    {
        html.append("<li class=\"special\" onclick=\"" + onClickEvent + "\"><a href=\"#tabs_0\">");
        html.append(menuTitles.at(0));
        html.append("</a></li>");
    }
    for(int counter = 1; counter < menuTitles.count(); counter++)
    {
        html.append("<li class=\"active\" onclick=\"selectTabPanel('" + fluentMenuID + "_Content', " +
                    QString::number(counter - 1) + ");\"><a href=\"#tabs_");
        html.append(QString::number(counter));
        html.append("\">");
        html.append(menuTitles.at(counter));
        html.append("</a></li>");
    }
    html.append("</ul>");
    html.append("<div class=\"tabs-content\" id=\"" + fluentMenuID + "_Content\">");
    for(FluentTabPanel aFluentTabPanel : fluentTabPanels)
        html.append(aFluentTabPanel.toHTML());
    html.append("</div>");
    html.append("</div>");
}
