#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "component.h"
#include <QString>
class ProgressBar : public Component
{
public:
    ProgressBar(int currentValue, QString backgroundColour);
    ProgressBar();
private:
    void createControl();
    int currentValue;
    QString backgroundColour;
};

#endif // PROGRESSBAR_H
