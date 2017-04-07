#ifndef STEPPER_H
#define STEPPER_H
#include "component.h"
class Stepper : public Component
{
public:
    Stepper(QString id, int numberOfSteps, int initialValue, bool stepsClickable);
private:
    QString id;
    int numberOfSteps;
    int initialValue;
    bool stepsClickable;
    void createControl();
};

#endif // STEPPER_H
