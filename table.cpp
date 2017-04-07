#include "table.h"
#include <QString>
#include <QVector>
Table::Table(QString tableID, QVector<QString> tableTitles, QVector<QVector<QString>> tableRows,
             QVector<QString> tableClickEvents)
{
    this->tableID = tableID;
    this->tableTitles = tableTitles;
    this->tableRows = tableRows;
    this->tableClickEvents = tableClickEvents;
    createControl();
}
Table::Table(QString tableID, QVector<QString> tableTitles, QVector<QVector<QString>> tableRows)
{
    this->tableID = tableID;
    this->tableTitles = tableTitles;
    this->tableRows = tableRows;
    createControl();
}
void Table::createControl()
{
    html.append("<table id=\"" + tableID + "\" class=\"dataTable striped border bordered\" data-role=\"datatable\"");
    html.append("data-searching=\"true\">");
    if(tableTitles.count() > 0)
    {
        html.append("<thead>");
        html.append("<tr>");
        for(QString aTableTitle : tableTitles)
        {
            html.append("<th>");
            html.append(aTableTitle);
            html.append("</th>");
        }
        html.append("</tr>");
        html.append("</thead>");
    }
    if(tableRows.count() > 0)
    {
        html.append("<tbody>");
        int counter = 0;
        for(QVector<QString> aTableRow : tableRows)
        {
            if(tableClickEvents.count() == 0)
                html.append("<tr>");
            else
                html.append("<tr onclick=\"" + tableClickEvents.at(counter++) + "\">");
            for(QString aTableCell : aTableRow)
            {
                html.append("<td>");
                html.append(aTableCell);
                html.append("</td>");
            }
            html.append("</tr>");
        }
        html.append("</tbody>");
    }
    html.append("</table>");
}
