#include "slider.h"
#include <QString>
Slider::Slider(int maximumValue, int minimumValue)
{
    this->maximumValue = maximumValue;
    this->minimumValue = minimumValue;
    createControl();
}
Slider::Slider()
{
    this->maximumValue = 1;
    this->minimumValue = 0;
    createControl();
}
void Slider::createControl()
{
    html.append("<div class=\"slider\" data-role=\"slider\" data-max-value=\"" + QString::number(maximumValue));
    html.append("\" data-min-value=\"" + QString::number(minimumValue) + "\">");
    html.append("<div class=\"slider-backside\">");
    html.append("</div>");
    html.append("<div class=\"complete\">");
    html.append("</div>");
    html.append("<div class=\"buffer\">");
    html.append("</div>");
    html.append("<a class=\"marker\">");
    html.append("</a>");
    html.append("</div>");
}
