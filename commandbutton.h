#ifndef COMMANDBUTTON_H
#define COMMANDBUTTON_H
#include <QString>
#include "component.h"
class CommandButton : public Component
{
public:
    CommandButton(QString titleText, QString subText, QString icon, QString state, QString onClickEvent);
    CommandButton(QString titleText, QString subText, QString icon, QString state);
    CommandButton(QString titleText, QString subText, QString icon);
private:
    void createControl();
    QString onClickEvent;
    QString titleText;
    QString subText;
    QString icon;
    QString state;
};

#endif // COMMANDBUTTON_H
