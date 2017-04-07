#ifndef TILE_H
#define TILE_H
#include <QString>
#include "component.h"
class Tile : public Component
{
public:
    Tile(QString tileIcon, QString tileLabel, QString tileBadge, QString onClickEvent);
    Tile(QString tileIcon, QString tileLabel, QString onClickEvent);
    Tile();
private:
    void createControl();
    QString tileIcon;
    QString tileLabel;
    QString tileBadge;
    QString onClickEvent;
};

#endif // TILE_H
