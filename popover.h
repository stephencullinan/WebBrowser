#ifndef POPOVER_H
#define POPOVER_H
#include "component.h"
class Popover : public Component
{
public:
    Popover(QString textualContent, QString markerPosition);
    Popover(QString textualContent, QString markerPosition, QString id, QString backgroundColour, bool visible);
private:
    void createControl();
    QString textualContent;
    QString markerPosition;
    QString id;
    QString backgroundColour;
    bool visible;
};

#endif // POPOVER_H
