#include "stepper.h"
Stepper::Stepper(QString id, int numberOfSteps, int initialValue, bool stepsClickable)
{
    this->id = id;
    this->numberOfSteps = numberOfSteps;
    this->initialValue = initialValue;
    this->stepsClickable = stepsClickable;
    createControl();
}
void Stepper::createControl()
{
    html.append("<div class=\"stepper diamond\" data-role=\"stepper\" data-type=\"diamond\" data-steps=\"" +
                QString::number(numberOfSteps));
    html.append("\" data-start=\"" + QString::number(initialValue) + "\" id=\"" + id + "\">");
    html.append("<ul id=\"" + id + "_List\">");
    for(int counter = 1; counter <= numberOfSteps; counter++)
    {
        QString onClickEvent = "";
        if(stepsClickable)
            onClickEvent = "updateStepper('" + id + "', " + QString::number(counter) + ");";
        if(counter < initialValue)
            html.append("<li class=\"complete\" onclick=\"" + onClickEvent + "\"></li>");
        else if(counter == initialValue)
            html.append("<li class=\"current\" onclick=\"" + onClickEvent + "\"></li>");
        else
            html.append("<li onclick=\"" + onClickEvent + "\"></li>");
    }
    html.append("</ul>");
    html.append("</div>");
    html.append("<input type=\"hidden\" id=\"" + id + "_Input\" value=\"" + QString::number(initialValue)
                + "\"></input>");
}
