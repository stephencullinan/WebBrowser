#include "heading.h"
#include <QString>

Heading::Heading(QString headingTitle, QString headingContent, int headingSize)
{
    this->headingTitle = headingTitle;
    this->headingContent = headingContent;
    this->headingSize = headingSize;
    createControl();
}
Heading::Heading(QString headingTitle, QString headingContent)
{
    this->headingTitle = headingTitle;
    this->headingContent = headingContent;
    this->headingSize = 1;
    createControl();
}
Heading::Heading(QString headingTitle)
{
    this->headingTitle = headingTitle;
    this->headingContent = "";
    this->headingSize = 1;
    createControl();
}
void Heading::createControl()
{
    html.append("<h" + QString::number(headingSize) + " class=\"align-center\">" + headingTitle + "<small>" +
                headingContent + "</small></h" + QString::number(headingSize) + ">");
}
