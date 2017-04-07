#ifndef HTMLPAGE_H
#define HTMLPAGE_H
#include <QString>
class HTMLPage
{
public:
    HTMLPage();
    void createHeading();
    void createContent();
    QString getString();
    void writeToFile(QString fileName);
    void createMenuTitles(QString menuTitle, QVector<QString> menuTitles);
    void createMenuButtons();
private:
    QString htmlContent;
};


#endif // HTMLPAGE_H
