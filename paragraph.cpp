#include "paragraph.h"
Paragraph::Paragraph(QString textualContent, QString title)
{
    this->textualContent = textualContent;
    this->title = title;
    createControl();
}
void Paragraph::createControl()
{
    html.append("<div class=\"example\" data-text=\"" + title + "\">");
    html.append("<h1 align=\"center\">" + title + "</h1>");
    html.append("<p>" + textualContent + "</p>");
    html.append("</div>");
}
