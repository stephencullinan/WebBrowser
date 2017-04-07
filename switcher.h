#ifndef SWITCHER_H
#define SWITCHER_H
#include "component.h"
#include <QString>
class Switcher : public Component
{
public:
    Switcher(QString id, QString onClickEvent, bool checked);
private:
    QString id;
    QString onClickEvent;
    bool checked;
    void createControl();
};

#endif // SWITCHER_H
