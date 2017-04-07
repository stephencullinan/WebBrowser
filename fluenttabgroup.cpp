#include "fluenttabgroup.h"
#include <QString>
#include <QVector>
#include "fluentbigbutton.h"

FluentTabGroup::FluentTabGroup(QString tabGroupCaption, QVector<FluentBigButton> fluentBigButtons)
{
    this->tabGroupCaption = tabGroupCaption;
    this->fluentBigButtons = fluentBigButtons;
    createControl();
}
FluentTabGroup::FluentTabGroup(QString tabGroupCaption, QVector<TextBox> fluentTextBoxes)
{
    this->tabGroupCaption = tabGroupCaption;
    this->fluentTextBoxes = fluentTextBoxes;
    createControl();
}
FluentTabGroup::FluentTabGroup()
{

}
void FluentTabGroup::createControl()
{
    html.append("<div class=\"tab-panel-group\">");
    html.append("<div class=\"tab-group-content\">");
    for(FluentBigButton aButton : fluentBigButtons)
        html.append(aButton.toHTML());
    for(TextBox aTextBox : fluentTextBoxes)
        html.append(aTextBox.toHTML());
    html.append("</div>");
    html.append("<div class=\"tab-group-caption\">");
    html.append(tabGroupCaption);
    html.append("</div>");
    html.append("</div>");
}
