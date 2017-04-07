#include "colorpicker.h"
#include "tilesmall.h"
#include "layout.h"
#include <QVector>
#include <QString>
ColorPicker::ColorPicker(QString id, QString existingColour)
{
    this->id = id;
    this->existingColour = existingColour;
    createControl();
}
void ColorPicker::createControl()
{
    QVector<QString> colours({"black", "white", "lime", "green", "emerald", "teal", "blue", "cyan", "cobalt",
                              "indigo", "violet", "pink", "magenta", "crimson", "red", "orange", "amber", "yellow",
                             "brown", "olive", "steel", "mauve", "taupe", "gray", "dark", "darker"});
    QVector<TileSmall> tiles({});
    int counter = 0;
    for(QString aColour : colours)
    {
        bool selectedTile = false;
        if(aColour == existingColour)
            selectedTile = true;
        tiles.push_back(TileSmall(aColour, "selectColour('" + id + "', " + QString::number(counter++) +
                                  ", '" + aColour + "');", selectedTile));
    }
    Layout aLayout(id);
    aLayout.addSmallTiles(tiles);
    html.append(aLayout.toHTML());
    html.append("<input type=\"hidden\" id=\"" + id + "_Input\" value=\"" + existingColour + "\"></input>");
}
