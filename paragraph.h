#ifndef PARAGRAPH_H
#define PARAGRAPH_H
#include "component.h"
class Paragraph : public Component
{
public:
    Paragraph(QString textualContent, QString title);
private:
    void createControl();
    QString textualContent;
    QString title;
};

#endif // PARAGRAPH_H
