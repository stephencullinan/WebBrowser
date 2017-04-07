#include "tile.h"
Tile::Tile(QString tileIcon, QString tileLabel, QString tileBadge, QString onClickEvent)
{
    this->tileIcon = tileIcon;
    this->tileLabel = tileLabel;
    this->tileBadge = tileBadge;
    this->onClickEvent = onClickEvent;
    createControl();
}
Tile::Tile(QString tileIcon, QString tileLabel, QString onClickEvent)
{
    this->tileIcon = tileIcon;
    this->tileLabel = tileLabel;
    this->onClickEvent = onClickEvent;
    this->tileBadge = "";
    createControl();
}
Tile::Tile()
{

}
void Tile::createControl()
{
    html.append("<div class=\"tile bg-cyan fg-white\" data-role=\"tile\" onclick=\"" + onClickEvent);
    html.append("\" style=\"width:100%;\">");
    html.append("<div class=\"tile-content iconic\">");
    html.append("<span class=\"icon mif-" + tileIcon + "\"></span>");
    if(tileBadge.length() > 0)
        html.append("<span class=\"tile-badge bg-darkRed\">" + tileBadge + "</span>");
    html.append("<span class=\"tile-label\">" + tileLabel + "</span>");
    html.append("</div>");
    html.append("</div>");
}
