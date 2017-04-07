#include "accordion.h"
#include "component.h"
#include <QString>
#include <QVector>
Accordion::Accordion(QVector<QString> accordionTitles, QVector<Layout> accordionControls,
                     QVector<QString> accordionIcons)
{
    this->accordionControls = accordionControls;
    this->accordionIcons = accordionIcons;
    this->accordionTitles = accordionTitles;
    createControl();
}
void Accordion::createControl()
{
    html.append("<div class=\"accordion large-heading\" data-role=\"accordion\">");
    for(int counter = 0; counter < accordionControls.count(); counter++)
    {
        html.append("<div class=\"frame active\">");
        html.append("<div class=\"heading\">" + accordionTitles.at(counter) + "<span class=\"mif-" +
                    accordionIcons.at(counter) + " icon\"></span></div>");
        html.append("<div class=\"content\">");
        Layout aLayout = accordionControls.at(counter);
        html.append(aLayout.toHTML());
        html.append("</div>");
        html.append("</div>");
    }
    html.append("</div>");
}
