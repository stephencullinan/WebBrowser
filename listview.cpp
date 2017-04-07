#include "listview.h"
#include <QString>
ListView::ListView(QString listViewID, QString listViewSelectedValue, QString listGroupTitle)
{
    this->listViewID = listViewID;
    this->listViewSelectedValue = listViewSelectedValue;
    this->listGroupTitle = listGroupTitle;
    this->listViewCounter = 0;
    createControl();
}
void ListView::createControl()
{
    html.append("<input type=\"hidden\" id=\"" + listViewID + "_Input\" value=\"" + listViewSelectedValue + "\">");
    html.append("<div class=\"listview-outlook\" data-role=\"listview\" id=\"" + listViewID + "\">");
    html.append("<div class=\"list-group\">");
    html.append("<span class=\"list-group-toggle\">" + listGroupTitle + "</span>");
    html.append("</div>");
    html.append("</div>");
}
void ListView::addItem(QString listTitle, QString listSubTitle, QString listRemark, bool activeItem,
                       QString itemValue)
{
    addItem(listTitle, listSubTitle, listRemark, activeItem, itemValue, "");
}

void ListView::addItem(QString listTitle, QString listSubTitle, QString listRemark, bool activeItem,
                       QString itemValue, QString onClickEvent)
{
    html = html.mid(0, html.length() - 12);
    html.append("<div class=\"list-group-content\">");
    if(activeItem)
        html.append("<a class=\"list active marked\" href=\"#\" onclick=\"listItemSelected(" +
                    QString::number(listViewCounter) + ", '" + itemValue + "', '" + listViewID + "');" +
                    onClickEvent + "\">");
    else
        html.append("<a class=\"list marked\" href=\"#\" onclick=\"listItemSelected(" +
                    QString::number(listViewCounter) + ", '" + itemValue + "', '" + listViewID + "');" +
                    onClickEvent + "\">");
    html.append("<div class=\"list-content\">");
    html.append("<span class=\"list-title\">" + listTitle + "</span>");
    html.append("<span class=\"list-subtitle\">" + listSubTitle + "</span>");
    html.append("<span class=\"list-remark\">" + listRemark + "</span>");
    html.append("</div>");
    html.append("</a>");
    html.append("</div>");
    html.append("</div>");
    html.append("</div>");
    listViewCounter++;
}
