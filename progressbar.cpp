#include "progressbar.h"
#include <QString>
ProgressBar::ProgressBar(int currentValue, QString backgroundColour)
{
    this->currentValue = currentValue;
    this->backgroundColour = backgroundColour;
    createControl();
}
ProgressBar::ProgressBar()
{
    this->currentValue = 100;
    this->backgroundColour = "ribbed-cyan";
    createControl();
}
void ProgressBar::createControl()
{
    html.append("<div class=\"progress large\" data-value=\"");
    html.append(QString::number(currentValue));
    html.append("\" data-color=\"");
    html.append(backgroundColour);
    html.append("\" data-role=\"progress\">");
    html.append("<div class=\"bar " + backgroundColour + "\" style=\"width: " +
                QString::number(currentValue) + "%;\"></div>");
    html.append("</div>");
}
