#ifndef ACCORDION_H
#define ACCORDION_H
#include "component.h"
#include "layout.h"
#include <QString>
#include <QVector>
class Accordion : public Component
{
public:
    Accordion(QVector<QString> accordionTitles, QVector<Layout> accordionControls,
              QVector<QString> accordionIcons);
private:
    void createControl();
    QVector<QString> accordionTitles;
    QVector<Layout> accordionControls;
    QVector<QString> accordionIcons;
};

#endif // ACCORDION_H
