#include "layout.h"
#include "popover.h"
#include "textbox.h"
#include <QDebug>
#include <QString>
TextBox::TextBox(QString placeHolderText, QString icon, QString id, QString value)
{
    this->placeHolderText = placeHolderText;
    this->icon = icon;
    this->id = id;
    this->value = value;
    createControl();
}
TextBox::TextBox(QString placeHolderText, QString icon, QString id)
{
    this->placeHolderText = placeHolderText;
    this->icon = icon;
    this->id = id;
    this->value = "";
    createControl();
}
TextBox::TextBox(QString placeHolderText, QString icon)
{
    this->placeHolderText = placeHolderText;
    this->icon = icon;
    this->id = "";
    this->value = "";
    createControl();
}
TextBox::TextBox()
{
    this->placeHolderText = "";
    this->icon = "";
    this->id = "";
    this->value = "";
    createControl();
}
void TextBox::createControl()
{
    html.append("<div class=\"input-control modern text iconic full-size\" data-role=\"input\">");
    html.append("<input type=\"text\" id=\"" + id + "\" value=\"" + value + "\">");
    html.append("<span class=\"label\">" + placeHolderText + "</span>");
    html.append("<span class=\"informer\">" + placeHolderText + "</span>");
    html.append("<span class=\"placeholder\">" + placeHolderText + "</span>");
    html.append("<span class=\"icon mif-" + icon + "\"></span>");
    html.append("</div>");
    Layout errorMessageLayout;
    errorMessageLayout.addControl(Popover("", "top", id + "_ErrorMessage", "red", false), QVector<int>({2, 8, 2}));
    html.append(errorMessageLayout.toHTML());
}
