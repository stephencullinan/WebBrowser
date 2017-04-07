#ifndef FLUENTTABGROUP_H
#define FLUENTTABGROUP_H
#include <fluentbigbutton.h>
#include <textbox.h>
#include <QVector>
class FluentTabGroup : public Component
{
public:
    FluentTabGroup(QString tabGroupCaption, QVector<FluentBigButton> fluentBigButtons);
    FluentTabGroup(QString tabGroupCaption, QVector<TextBox> fluentTextBoxes);
    FluentTabGroup();
private:
    void createControl();
    QString tabGroupCaption;
    QVector<FluentBigButton> fluentBigButtons;
    QVector<TextBox> fluentTextBoxes;
};

#endif // FLUENTTABGROUP_H
