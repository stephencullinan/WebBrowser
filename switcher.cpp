#include "switcher.h"
#include <QString>
Switcher::Switcher(QString id, QString onClickEvent, bool checked = true)
{
    this->id = id;
    this->onClickEvent = onClickEvent;
    this->checked = checked;
    createControl();
}
void Switcher::createControl()
{
    html.append("<label class=\"switch\" id=\"" + id + "\" onclick=\"" + onClickEvent + "\">");
    if(checked)
        html.append("<input type=\"checkbox\" checked>");
    else
        html.append("<input type=\"checkbox\">");
    html.append("<span class=\"check\"></span>");
    html.append("</label>");
}
