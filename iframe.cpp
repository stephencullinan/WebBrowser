#include "iframe.h"
#include <QString>
IFrame::IFrame(QString url, QString id)
{
    this->url = url;
    this->id = id;
    addControl();
}
void IFrame::addControl()
{
    html.append("<iframe src=\"" + url + "\" width=\"100%\" height=\"100%\" id=\"" + id + "\"></iframe>");
}
