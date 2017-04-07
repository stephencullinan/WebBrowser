#include "commandbutton.h"
#include <QString>
CommandButton::CommandButton(QString titleText, QString subText, QString icon, QString state, QString onClickEvent)
{
    this->titleText = titleText;
    this->subText = subText;
    this->icon = icon;
    this->state = state;
    this->onClickEvent = onClickEvent;
    createControl();
}
CommandButton::CommandButton(QString titleText, QString subText, QString icon, QString state)
{
    this->titleText = titleText;
    this->subText = subText;
    this->icon = icon;
    this->state = state;
    this->onClickEvent = onClickEvent;
    createControl();
}
CommandButton::CommandButton(QString titleText, QString subText, QString icon)
{
    this->titleText = titleText;
    this->subText = subText;
    this->icon = icon;
    this->state = "success";
    this->onClickEvent = onClickEvent;
    createControl();
}
void CommandButton::createControl()
{
    html.append("<button class=\"command-button " + state + "\" style=\"width:100%;\" onclick=\"" + onClickEvent +
                "\">");
    html.append("<span class=\"icon mif-" + icon + "\"></span>");
    html.append(titleText);
    html.append("<small>" + subText + "</small>");
    html.append("</button>");
}
