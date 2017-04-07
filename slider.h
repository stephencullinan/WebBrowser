#ifndef SLIDER_H
#define SLIDER_H
#include "component.h"

class Slider : public Component
{
public:
    Slider(int maximumValue, int minimumValue);
    Slider();
private:
    void createControl();
    int maximumValue;
    int minimumValue;
};

#endif // SLIDER_H
