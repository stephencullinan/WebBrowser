#ifndef LAYOUT_H
#define LAYOUT_H
#include "colorpicker.h"
#include "commandbutton.h"
#include "component.h"
#include "textbox.h"
#include "heading.h"
#include "listview.h"
#include "preloader.h"
#include "slider.h"
#include "switcher.h"
#include "tilesmall.h"
#include "table.h"
#include "tablesimplified.h"
#include "tile.h"
#include "tileselected.h"
#include "updatepanel.h"
#include <QMap>
#include <QVector>
#include <QString>
class Layout : public Component
{
public:
    Layout();
    Layout(QString id);
    void addTiles(QVector<Component> tiles);
    void addSmallTiles(QVector<TileSmall> tiles);
    void addLayouts(Layout firstLayout, Layout secondLayout);
    void addEmptyRows(int numberOfEmptyRows);
    void addControl(Component aControl, QVector<int> positions);
    void addControls(QVector<Component> controls, QVector<int> positions);
private:
    void createControl();
    QString id;
};

#endif // LAYOUT_H
