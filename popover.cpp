#include "popover.h"

Popover::Popover(QString textualContent, QString markerPosition)
{
    this->textualContent = textualContent;
    this->markerPosition = markerPosition;
    this->id = "";
    this->backgroundColour = "cyan";
    this->visible = true;
    createControl();
}
Popover::Popover(QString textualContent, QString markerPosition, QString id, QString backgroundColour, bool visible)
{
    this->textualContent = textualContent;
    this->markerPosition = markerPosition;
    this->id = id;
    this->backgroundColour = backgroundColour;
    this->visible = visible;
    createControl();
}
void Popover::createControl()
{
    html.append("<div class=\"popover marker-on-" + markerPosition + " bg-" + backgroundColour + "\" id=\"" + id);
    html.append("\"");
    if(visible == false)
        html.append("style = \"display:none;\"");
    html.append(">");
    html.append("<div class=\"fg-white\" align=\"center\">" + textualContent + "</div>");
    html.append("</div>");
}
