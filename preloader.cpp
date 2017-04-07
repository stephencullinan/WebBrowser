#include "preloader.h"
#include <QString>
PreLoader::PreLoader()
{
    createControl();
}
void PreLoader::createControl()
{
    html.append("<div data-role=\"preloader\" data-type=\"cycle\" data-style=\"color\" style=\"margin: auto\"");
    html.append(" class=\"preloader-cycle color-style\">");
    html.append("<div class=\"cycle\">");
    html.append("</div>");
    html.append("</div>");
}
