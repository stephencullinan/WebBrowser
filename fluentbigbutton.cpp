#include "fluentbigbutton.h"
FluentBigButton::FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent, QString id,
                                 QString backgroundColour)
{
    this->buttonIcon = buttonIcon;
    this->buttonCaption = buttonCaption;
    this->onClickEvent = onClickEvent;
    this->id = id;
    this->backgroundColour = backgroundColour;
    createControl();
}
FluentBigButton::FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent, QString id)
{
    this->buttonIcon = buttonIcon;
    this->buttonCaption = buttonCaption;
    this->onClickEvent = onClickEvent;
    this->id = id;
    this->backgroundColour = "";
    createControl();
}
FluentBigButton::FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent)
{
    this->buttonIcon = buttonIcon;
    this->buttonCaption = buttonCaption;
    this->onClickEvent = onClickEvent;
    this->id = "";
    this->backgroundColour = "";
    createControl();
}
FluentBigButton::FluentBigButton(QString buttonIcon, QString buttonCaption)
{
    this->buttonIcon = buttonIcon;
    this->buttonCaption = buttonCaption;
    this->onClickEvent = "";
    this->id = "";
    this->backgroundColour = "";
    createControl();
}
FluentBigButton::FluentBigButton()
{

}
void FluentBigButton::createControl()
{
    html.append("<button class=\"fluent-big-button " + backgroundColour + "\" onclick=\"" + onClickEvent + "\" id=\"" + id + "\">");
    html.append("<span class=\"icon mif-" + buttonIcon + "\"></span>");
    html.append(buttonCaption);
    html.append("</button>");
}
