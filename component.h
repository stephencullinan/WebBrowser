#ifndef COMPONENT_H
#define COMPONENT_H
#include <QString>
class Component
{
public:
    Component();
    QString toHTML();
protected:
    QString html;
};

#endif // COMPONENT_H
