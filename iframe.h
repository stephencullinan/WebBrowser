#ifndef IFRAME_H
#define IFRAME_H
#include "component.h"
#include <QString>
class IFrame : public Component
{
public:
    IFrame(QString url, QString id);
private:
    void addControl();
    QString url;
    QString id;
};

#endif // IFRAME_H
