#ifndef TABLE_H
#define TABLE_H
#include "component.h"
#include <QString>
#include <QVector>
class Table : public Component
{
public:
    Table(QString tableID, QVector<QString> tableTitles, QVector<QVector<QString> > tableRows,
          QVector<QString> tableClickEvents);
    Table(QString tableID, QVector<QString> tableTitles, QVector<QVector<QString> > tableRows);
private:
    QVector<QVector<QString>> tableRows;
    QVector<QString> tableTitles;
    QVector<QString> tableClickEvents;
    QString tableID;
    void createControl();
};

#endif // TABLE_H
