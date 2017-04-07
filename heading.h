#ifndef HEADING_H
#define HEADING_H
#include "component.h"
#include <QString>
class Heading : public Component
{
public:
    Heading(QString headingTitle, QString headingContent, int headingSize);
    Heading(QString headingTitle, QString headingContent);
    Heading(QString headingTitle);
    void createControl();
private:
    QString headingTitle;
    QString headingContent;
    int headingSize;
};
#endif // HEADING_H
