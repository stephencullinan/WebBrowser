#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <QString>
#include "component.h"
class TextBox : public Component
{
public:
    TextBox(QString placeHolderText, QString icon, QString id, QString value);
    TextBox(QString placeHolderText, QString icon, QString id);
    TextBox(QString placeHolderText, QString icon);
    TextBox();
private:
    void createControl();
    QString placeHolderText;
    QString icon;
    QString id;
    QString value;
};
#endif // TEXTBOX_H
