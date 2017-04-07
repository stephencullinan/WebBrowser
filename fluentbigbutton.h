#ifndef FLUENTBIGBUTTON_H
#define FLUENTBIGBUTTON_H
#include "component.h"
#include <QString>

class FluentBigButton : public Component
{
public:
    FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent, QString id,
                    QString backgroundColour);
    FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent, QString id);
    FluentBigButton(QString buttonIcon, QString buttonCaption, QString onClickEvent);
    FluentBigButton(QString buttonIcon, QString buttonCaption);
    FluentBigButton();
private:
    QString backgroundColour;
    QString buttonIcon;
    QString buttonCaption;
    QString id;
    QString onClickEvent;
    void createControl();
};

#endif // FLUENTBIGBUTTON_H
