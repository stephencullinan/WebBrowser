#include "tilelarge.h"
#include <QDebug>
TileLarge::TileLarge(QString onClickEvent, QVector<QString> tileContent, QVector<int> tileSizes, QString tileLabel)
{
    this->onClickEvent = onClickEvent;
    this->tileContent = tileContent;
    this->tileLabel = tileLabel;
    this->tileSizes = tileSizes;
    createControl();
}
void TileLarge::createControl()
{
    html.append("<div class=\"tile-large bg-cyan fg-white\" data-role=\"tile\" onclick=\"" + onClickEvent);
    html.append("\" style=\"width:100%;\">");
    html.append("<div class=\"tile-content\">");
    for(int counter = 0; counter < tileContent.length() && counter < tileSizes.length(); counter++)
    {
        html.append("<h" + QString::number(tileSizes.at(counter)) + " align=\"center\">" + tileContent.at(counter)
                    + "</h" + QString::number(tileSizes.at(counter)) + ">");
    }
    html.append("</div>");
    if(tileLabel.length() > 0)
    {
        html.append("<span class=\"tile-label\">" + tileLabel + "</span>");
    }
    html.append("</div>");
}
