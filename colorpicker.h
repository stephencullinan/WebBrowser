#ifndef COLORPICKER_H
#define COLORPICKER_H
#include <QString>
#include "component.h"
class ColorPicker : public Component
{
public:
    ColorPicker(QString id, QString existingColour);
private:
    void createControl();
    QString existingColour;
    QString id;
};

#endif // COLORPICKER_H
