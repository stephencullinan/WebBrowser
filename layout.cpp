#include "colorpicker.h"
#include "commandbutton.h"
#include "component.h"
#include "heading.h"
#include "layout.h"
#include "slider.h"
#include "switcher.h"
#include "tablesimplified.h"
#include "textbox.h"
#include "tile.h"
#include "tileselected.h"
#include "listview.h"
#include "updatepanel.h"
#include "preloader.h"
#include <QMap>
#include <QDebug>
#include <QString>
#include <QVector>
Layout::Layout(QString id)
{
    this->id = id;
    createControl();
}
Layout::Layout()
{
    this->id = "";
    createControl();
}
void Layout::createControl()
{
    if(id.length() == 0)
        html.append("<div class=\"grid condensed\">");
    else
        html.append("<div class=\"grid condensed\" id=\"" + id + "\">");
    html.append("</div>");
}
void Layout::addEmptyRows(int numberOfEmptyRows)
{
    html = html.mid(0, html.length() - 6);
    for(int counter = 0; counter < numberOfEmptyRows; counter++)
    {
        html.append("<div class=\"row cells12\">");
        html.append("<div class=\"cell colspan12\"></div>");
        html.append("</div>");
    }
    html.append("</div>");
}
void Layout::addControl(Component aControl, QVector<int> positions)
{
    html = html.mid(0, html.length() - 6);
    if(positions.count() >= 3)
    {
        html.append("<div class=\"row cells12\">");
        html.append("<div class=\"cell colspan" + QString::number(positions.at(0)) + "\"></div>");
        html.append("<div class=\"cell colspan" + QString::number(positions.at(1)) + "\">" +
                    aControl.toHTML() + "</div>");
        html.append("<div class=\"cell colspan" + QString::number(positions.at(2)) + "\"></div>");
        html.append("</div>");
    }
    html.append("</div>");
}
void Layout::addControls(QVector<Component> controls, QVector<int> positions)
{
    html = html.mid(0, html.length() - 6);
    if(positions.count() >= (controls.count() * 3))
    {
        html.append("<div class=\"row cells12\">");
        for(int counter = 0; counter < controls.count(); counter++)
        {
            Component currentControl = controls.at(counter);
            html.append("<div class=\"cell colspan" + QString::number(positions.at(counter * 3)) + "\"></div>");
            html.append("<div class=\"cell colspan" + QString::number(positions.at((counter * 3) + 1)) + "\">" +
                        currentControl.toHTML() + "</div>");
            html.append("<div class=\"cell colspan" + QString::number(positions.at((counter * 3) + 2)) +
                        "\"></div>");
        }
        html.append("</div>");
    }
    html.append("</div>");
}
void Layout::addTiles(QVector<Component> tiles)
{
    html = html.mid(0, html.length() - 6);
    for(int counter = 0; counter < tiles.count(); counter++)
    {
        if(counter % 3 == 0)
            html.append("<div class=\"row cells12\">");
        html.append("<div class=\"cell colspan" + QString::number(1) + "\"></div>");
        Component aTile = tiles.at(counter);
        html.append("<div class=\"cell colspan" + QString::number(3) + "\">" +
                    aTile.toHTML() + "</div>");
        if(counter % 3 == 2 || counter == tiles.count() - 1)
            html.append("</div>");
    }
    html.append("</div>");
}
void Layout::addSmallTiles(QVector<TileSmall> tiles)
{
    html = html.mid(0, html.length() - 6);
    for(int counter = 0; counter < tiles.count(); counter++)
    {
        if(counter % 6 == 0)
            html.append("<div class=\"row cells12\">");
        TileSmall aSmallTile = tiles.at(counter);
        html.append("<div class=\"cell colspan" + QString::number(2) + "\">" + aSmallTile.toHTML() + "</div>");
        if(counter % 6 == 5 || counter == tiles.count() - 1)
            html.append("</div>");
    }
    html.append("</div>");
}

void Layout::addLayouts(Layout firstLayout, Layout secondLayout)
{
    html = html.mid(0, html.length() - 6);
    html.append("<div class=\"row cells12\">");
    html.append("<div class=\"cell colspan6\">" + firstLayout.toHTML() + "</div>");
    html.append("<div class=\"cell colspan6\">" + secondLayout.toHTML() + "</div>");
    html.append("</div>");
}
