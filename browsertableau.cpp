#include "accordion.h"
#include "browsertableau.h"
#include "database.h"
#include "layout.h"
#include "tile.h"
#include <QMap>
#include <QString>
#include <QVector>
#include <QWebEngineView>
BrowserTableau::BrowserTableau(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                               QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
    this->database = new Database("Information");
}
QString BrowserTableau::createTableau()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    Layout tableauLayout;
    ListView tableauSortingListView("tableauSortingListView", "count(history.date) desc", "Sort Tiles");
    tableauSortingListView.addItem("Order By Item Viewed Descending", "Descending Order", "Sort Option", true,
                                   "count(history.date) desc", "sortTableauItems();");
    tableauSortingListView.addItem("Order By Item Viewed Ascending", "Ascending Order", "Sort Option", false,
                                   "count(history.date) asc", "sortTableauItems();");
    tableauSortingListView.addItem("Order By Site Title Descending", "Descending Order", "Sort Option", false,
                                   "site.title desc", "sortTableauItems();");
    tableauSortingListView.addItem("Order By Site Title Ascending", "Ascending Order", "Sort Option", false,
                                   "site.title asc", "sortTableauItems();");
    ListView tableauNumberOfItemsListView("tableauNumberOfItemsListView", "-1", "Number Of Tiles To Be Displayed");
    tableauNumberOfItemsListView.addItem("View 10 Tiles", "10 Tiles", "Display Option", false,
                                         "10", "sortTableauItems();");
    tableauNumberOfItemsListView.addItem("View 50 Tiles", "50 Tiles", "Display Option", false,
                                         "50", "sortTableauItems();");
    tableauNumberOfItemsListView.addItem("View 100 Tiles", "100 Tiles", "Display Option", false,
                                         "100", "sortTableauItems();");
    tableauNumberOfItemsListView.addItem("View All Tiles", "All Tiles", "Display Option", true,
                                         "-1", "sortTableauItems();");
    tableauLayout.addControls(QVector<Component>({tableauSortingListView, tableauNumberOfItemsListView}),
                              QVector<int>({1, 4, 1, 1, 4, 1}));
    UpdatePanel tableauUpdatePanel("tableauUpdatePanel");
    tableauUpdatePanel.addControl(createTiles("count(history.date) desc", -1));
    tableauLayout.addControl(tableauUpdatePanel, QVector<int>({0, 12, 0}));
    Accordion tableauAccordion(QVector<QString>({"Tableau"}), QVector<Layout>({tableauLayout}),
                               QVector<QString>({"html5"}));
    return tableauAccordion.toHTML();
}
QString BrowserTableau::sortItems(QString orderByCondition, int numberOfItems)
{
    return createTiles(orderByCondition, numberOfItems).toHTML();
}

Layout BrowserTableau::createTiles(QString orderByCondition, int numberOfItems)
{
    QVector<QString> tableTitles({"history", "site"});
    QVector<QString> joinConditions({"history.site", "site.code"});
    QVector<QString> columnTitles({"count(history.date)", "site.title", "site.url"});
    QVector<QString> groupByConditions({"site.url"});
    QVector<QString> orderByConditions({orderByCondition});
    QMap<QString, QString>* selectedParameters = new QMap<QString, QString>();
    QVector<QVector<QString>> rowContents = database->getJoinedTableContents(tableTitles, joinConditions,
                                                                             columnTitles, groupByConditions,
                                                                             orderByConditions, selectedParameters);
    QVector<Component> createdTiles({});
    QVector<QVector<QString>> formattedRows;
    int counter = 1;
    if(numberOfItems == -1)
        numberOfItems = rowContents.count();
    for(QVector<QString> selectedRow : rowContents)
    {
        if(counter <= numberOfItems)
        {
            QString tileTitle = selectedRow.at(1);
            if(tileTitle.length() == 0)
                tileTitle = selectedRow.at(2);
            Tile aTile("html5", tileTitle, selectedRow.at(0), "openURL('" + selectedRow.at(2) + "');");
            createdTiles.push_back(aTile);
        }
        counter++;
    }
    Layout aLayout;
    aLayout.addTiles(createdTiles);
    return aLayout;
}
