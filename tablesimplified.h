#ifndef TABLESIMPLIFIED_H
#define TABLESIMPLIFIED_H
#include "component.h"
#include <QString>
#include <QVector>
class TableSimplified : public Component
{
public:
    TableSimplified(QString tableID, QVector<QString> tableTitles, QVector<QVector<QString>> tableContents,
                    QVector<QString> tableClickEvents);
private:
    void createControl();
    QString tableID;
    QVector<QString> tableTitles;
    QVector<QVector<QString>> tableContents;
    QVector<QString> tableClickEvents;
};

#endif // TABLESIMPLIFIED_H
