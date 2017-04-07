#ifndef LISTVIEW_H
#define LISTVIEW_H
#include "component.h"
#include <QString>
class ListView : public Component
{
public:
    ListView(QString listViewID, QString listViewSelectedValue, QString listGroupTitle);
    void addItem(QString listTitle, QString listSubTitle, QString listRemark,
                 bool activeItem, QString itemValue, QString onClickEvent);
    void addItem(QString listTitle, QString listSubTitle, QString listRemark,
                 bool activeItem, QString itemValue);
private:
    QString listViewID;
    QString listViewSelectedValue;
    QString listGroupTitle;
    int listViewCounter;
    void createControl();
};

#endif // LISTVIEW_H
