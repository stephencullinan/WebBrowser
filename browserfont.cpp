#include "accordion.h"
#include "browserdataitem.h"
#include "browserfont.h"
#include "browsertables.h"
#include "commandbutton.h"
#include "layout.h"
#include "textbox.h"
BrowserFont::BrowserFont(QWebEngineView* secondWebEngineView, QWebEngineView* webEngineView,
                         QObject *parent) : QObject(parent)
{
    this->secondWebEngineView = secondWebEngineView;
    this->webEngineView = webEngineView;
}
QString BrowserFont::createNewFont()
{
    secondWebEngineView->setVisible(false);
    webEngineView->setFixedHeight(760);
    TextBox fontFaceTextBox("Please enter the title of the font", "fonticons", "fontFaceTextBox");
    CommandButton createNewFontButton("Add", "Add A Font", "checkmark", "success", "saveFont();");
    Layout createNewFontLayout;
    createNewFontLayout.addControl(fontFaceTextBox, QVector<int>({0, 12, 0}));
    createNewFontLayout.addControl(createNewFontButton, QVector<int>({4, 4, 4}));
    Accordion anAccordion(QVector<QString>({"Add A Font"}), QVector<Layout>({createNewFontLayout}),
                          QVector<QString>({"fonticons"}));
    return anAccordion.toHTML();
}
QString BrowserFont::saveCreatedFont(QString fontFace)
{
    BrowserDataItem dataItem;
    QVector<QString> newFontAttributes({fontFace});
    dataItem.saveDataItemToSpecifiedTableWithNoJoins("font", newFontAttributes);
    BrowserTables aTable(secondWebEngineView, webEngineView);
    return aTable.createHTMLTable("font");
}
