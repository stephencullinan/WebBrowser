#include "tablesimplified.h"
#include <QString>
#include <QVector>
TableSimplified::TableSimplified(QString tableID, QVector<QString> tableTitles,
                                 QVector<QVector<QString>> tableContents, QVector<QString> tableClickEvents)
{
    this->tableID = tableID;
    this->tableTitles = tableTitles;
    this->tableContents = tableContents;
    this->tableClickEvents = tableClickEvents;
    createControl();
}
void TableSimplified::createControl()
{
    html.append("<table class=\"table striped hovered cell-hovered border bordered\" id=\"" + this->tableID + "\">");
    if(tableTitles.count() > 0)
    {
        html.append("<thead><tr>");
        for(QString aTableColumnTitle : tableTitles)
            html.append("<th>" + aTableColumnTitle + "</th>");
        html.append("</tr></thead>");
    }
    if(tableContents.count() > 0)
    {
        html.append("<tbody>");
        for(int counter = 0; counter < tableContents.length(); counter++)
        {
            if(tableClickEvents.length() > counter)
                html.append("<tr onclick=\"" + tableClickEvents.at(counter) + "\" id=\"" + tableID + "_Row_" +
                            QString::number(counter) + "\">");
            else
                html.append("<tr>");
            for(QString aTableRowContent : tableContents.at(counter))
            {
                html.append("<td>" + aTableRowContent + "</td>");
            }
            html.append("</tr>");
        }
        html.append("</tbody>");
    }
    html.append("</table>");
}
