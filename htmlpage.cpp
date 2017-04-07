#include "commandbutton.h"
#include "fluentbigbutton.h"
#include "fluenttabgroup.h"
#include "fluenttabpanel.h"
#include "fluentmenu.h"
#include "htmlpage.h"
#include "layout.h"
#include "table.h"
#include "textbox.h"
#include "progressbar.h"
#include <QString>
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>
#include <QVector>
HTMLPage::HTMLPage()
{
}
void HTMLPage::createHeading()
{
    htmlContent = "<!DOCTYPE html><html><head lang=\"en\"><title>Title</title>";
    htmlContent.append("<link href=\"css/metro.css\" rel=\"stylesheet\">");
    htmlContent.append("<link href=\"css/metro-icons.css\" rel=\"stylesheet\">");
    htmlContent.append("<link href=\"css/metro-responsive.css\" rel=\"stylesheet\">");
    htmlContent.append("<link href=\"css/metro-schemes.css\" rel=\"stylesheet\">");
    htmlContent.append("<script src=\"js/jquery-2.1.3.min.js\"><script>");
    htmlContent.append("<script src=\"js/metro.js\"></script>");
    htmlContent.append("<script src=\"js/jquery.dataTables.min.js\"></script>");
    htmlContent.append("<script src=\"qrc:///qtwebchannel/qwebchannel.js\"></script>");
    htmlContent.append("<script src=\"js/Sample.js\"></script>");
    this->htmlContent.append("</head>");
}
void HTMLPage::createMenuButtons()
{
    this->htmlContent.append("<body>");
    QVector<FluentTabPanel> menuPanels;
    QVector<FluentBigButton> navigationFirstMenuButtons;
    QVector<FluentBigButton> navigationThirdMenuButtons;
    QVector<FluentBigButton> navigationFourthMenuButtons;
    FluentBigButton backButton("arrow-left", "Back", "goBackward();");
    navigationFirstMenuButtons.append(backButton);
    FluentBigButton forwardButton("arrow-right", "Forward", "goForward();");
    navigationFirstMenuButtons.append(forwardButton);
    FluentBigButton reloadButton("checkmark", "Reload", "reload();");
    navigationThirdMenuButtons.append(reloadButton);
    FluentBigButton stopButton("cross", "Stop", "stop();");
    navigationThirdMenuButtons.append(stopButton);
    FluentBigButton homeButton("home", "Home", "openHomePage();");
    navigationThirdMenuButtons.append(homeButton);
    FluentBigButton tableauButton("html5", "View Tableau", "createTableau();");
    navigationThirdMenuButtons.append(tableauButton);
    FluentBigButton viewBrowserButton("compass2", "View Browser", "displayBrowser();");
    navigationThirdMenuButtons.append(viewBrowserButton);
    FluentBigButton navigateToUrlButton("checkmark", "Load URL", "enterURL();");
    FluentBigButton searchWithGoogleButton("google", "Search With Google", "performSearch();");
    navigationFourthMenuButtons.append(navigateToUrlButton);
    navigationFourthMenuButtons.append(searchWithGoogleButton);
    QVector<FluentTabGroup> navigationGroups;
    FluentTabGroup navigationFirstGroup("Navigation", navigationFirstMenuButtons);
    FluentTabGroup navigationThirdGroup("Navigation", navigationThirdMenuButtons);
    FluentTabGroup navigationFourthGroup("Search Address", navigationFourthMenuButtons);
    navigationGroups.append(navigationFirstGroup);
    navigationGroups.append(navigationThirdGroup);
    navigationGroups.append(navigationFourthGroup);
    FluentTabPanel navigationPanel("tabs_1", navigationGroups, "display:block;");
    menuPanels.append(navigationPanel);
    QVector<FluentBigButton> editMenuButtons;
    FluentBigButton highlightLinksButton("link", "Highlight Links", "applyLinksColourMenu();");
    editMenuButtons.append(highlightLinksButton);
    FluentBigButton backgroundColourButton("security", "Set Background Colour", "applyBackgroundColourMenu();");
    editMenuButtons.append(backgroundColourButton);
    FluentBigButton fontButton("fonticons", "Set Font Size And Face", "getEditFontMenu();");
    editMenuButtons.append(fontButton);
    FluentBigButton replaceTextButton("file-text", "Replace Text", "replaceTextMenu(true);");
    editMenuButtons.append(replaceTextButton);
    FluentBigButton replaceTextColourButton("palette", "Replace Text Colour", "replaceTextMenu(false);");
    editMenuButtons.append(replaceTextColourButton);
    FluentBigButton rotateImagesButton("images", "Rotate Images", "getEditImageRotationsMenu();");
    editMenuButtons.append(rotateImagesButton);
    FluentBigButton removeImagesButton("images", "Remove Images", "getEditImagesMenu();");
    editMenuButtons.append(removeImagesButton);
    QVector<FluentTabGroup> editGroups;
    FluentTabGroup editGroup("Edit Current Page", editMenuButtons);
    editGroups.append(editGroup);
    FluentTabPanel editPanel("tabs_2", editGroups);
    menuPanels.append(editPanel);
    QVector<FluentBigButton> historyMenuButtons;
    FluentBigButton viewHistoryButton("history", "View History", "viewTable('history', 'History');");
    historyMenuButtons.append(viewHistoryButton);
    FluentBigButton deleteHistoryButton("history", "Delete History", "deleteRowFromTable('history', 'History');");
    historyMenuButtons.append(deleteHistoryButton);
    FluentBigButton expungeHistoryButton("bin", "Expunge History", "expungeTable('history', 'History');");
    historyMenuButtons.append(expungeHistoryButton);
    QVector<FluentTabGroup> historyGroups;
    FluentTabGroup historyGroup("History", historyMenuButtons);
    historyGroups.append(historyGroup);
    FluentTabPanel historyPanel("tabs_3", historyGroups);
    menuPanels.append(historyPanel);
    QVector<FluentBigButton> bookmarksMenuButtons;
    FluentBigButton viewBookmarksButton("bookmarks", "View Bookmarks", "viewTable('bookmark', 'Bookmarks');");
    bookmarksMenuButtons.append(viewBookmarksButton);
    FluentBigButton addABookmarkButton("bookmarks", "Add A Bookmark", "addBookmark();");
    bookmarksMenuButtons.append(addABookmarkButton);
    FluentBigButton deleteABookmarkButton("bookmarks", "Delete A Bookmark",
                                          "deleteRowFromTable('bookmark', 'Bookmarks');");
    bookmarksMenuButtons.append(deleteABookmarkButton);
    FluentBigButton expungeBookmarksButton("bin", "Expunge Bookmarks", "expungeTable('bookmark', 'Bookmarks');");
    bookmarksMenuButtons.append(expungeBookmarksButton);
    QVector<FluentTabGroup> bookmarksGroups;
    FluentTabGroup bookmarksGroup("Bookmarks", bookmarksMenuButtons);
    bookmarksGroups.append(bookmarksGroup);
    FluentTabPanel bookmarksPanel("tabs_4", bookmarksGroups);
    menuPanels.append(bookmarksPanel);
    QVector<FluentBigButton> settingsMenuButtons;
    FluentBigButton setHomePageToCurrentPageButton("home", "Set Home Page To Current Page",
                                                   "updateHomePageToCurrentPage();");
    settingsMenuButtons.append(setHomePageToCurrentPageButton);
    FluentBigButton editHomePageButton("home", "Edit Home Page", "updateHomePage();");
    settingsMenuButtons.append(editHomePageButton);
    QVector<FluentTabGroup> settingsGroups;
    FluentTabGroup settingsGroup("Settings", settingsMenuButtons);
    settingsMenuButtons.clear();
    FluentBigButton viewFontsButton("fonticons", "View Fonts", "viewTableWithNoJoins('font');");
    settingsMenuButtons.append(viewFontsButton);
    FluentBigButton addAFontButton("plus", "Add A Font", "addFont();");
    settingsMenuButtons.append(addAFontButton);
    FluentBigButton deleteFontsButton("bin", "Delete A Font",
                                      "deleteTableWithNoJoins('font', 'Fonts');");
    settingsMenuButtons.append(deleteFontsButton);
    FluentBigButton expungeFontsButton("bin", "Expunge Fonts", "expungeTable('font', 'Fonts');");
    settingsMenuButtons.append(expungeFontsButton);
    FluentTabGroup fontSettingsGroup("Font Settings", settingsMenuButtons);
    settingsGroups.append(settingsGroup);
    settingsGroups.append(fontSettingsGroup);
    FluentTabPanel settingsPanel("tabs_5", settingsGroups);
    menuPanels.append(settingsPanel);
    QVector<FluentBigButton> feedsMenuButtons;
    FluentBigButton viewFeedsButton("feed3", "View Feeds As Tiles", "viewAvailableFeeds();");
    feedsMenuButtons.append(viewFeedsButton);
    FluentBigButton viewFeedsTableButton("feed3", "View Feeds As Table", "viewTable('feed', 'Feeds');");
    feedsMenuButtons.append(viewFeedsTableButton);
    FluentBigButton addAFeedButton("plus", "Add A Feed", "createNewFeed();");
    feedsMenuButtons.append(addAFeedButton);
    FluentBigButton deleteFeedButton("bin", "Delete Feed", "deleteRowFromTable('feed', 'Feeds');");
    feedsMenuButtons.append(deleteFeedButton);
    FluentBigButton expungeFeedButton("bin", "Expunge Feeds", "expungeTable('feed', 'Feeds');");
    feedsMenuButtons.append(expungeFeedButton);
    FluentTabGroup feedsGroup("Feeds", feedsMenuButtons);
    QVector<FluentTabGroup> feedsGroups;
    feedsGroups.append(feedsGroup);
    FluentTabPanel feedsPanel("tabs_6", feedsGroups);
    menuPanels.append(feedsPanel);
    QVector<FluentBigButton> themesMenuButtons;
    FluentBigButton createNewThemeButton("plus", "Add A Theme", "addThemeStepOne();");
    themesMenuButtons.append(createNewThemeButton);
    FluentBigButton viewExistingThemesButton("image", "View Existing Themes", "viewAvailableThemes(true);");
    themesMenuButtons.append(viewExistingThemesButton);
    FluentBigButton deleteExistingThemesButton("bin", "Delete A Theme", "viewAvailableThemes(false);");
    themesMenuButtons.append(deleteExistingThemesButton);
    FluentTabGroup themesGroup("Themes", themesMenuButtons);
    QVector<FluentTabGroup> themesGroups;
    themesGroups.append(themesGroup);
    FluentTabPanel themesPanel("tabs_7", themesGroups);
    menuPanels.append(themesPanel);
    QVector<QString> menuTitles({"About", "Navigation", "Edit", "History", "Bookmarks", "Settings", "Feeds",
                                 "Themes"});
    FluentMenu mainMenu(menuTitles, menuPanels, "mainMenu", "getAboutMenu();");
    htmlContent.append(mainMenu.toHTML());
    UpdatePanel mainPanel("mainPanel");
    htmlContent.append(mainPanel.toHTML());
    this->htmlContent.append("</body>");
    this->htmlContent.append("</html>");
}
QString HTMLPage::getString()
{
    return this->htmlContent;
}
void HTMLPage::writeToFile(QString fileName)
{
    QFile aFile(fileName);
    if(aFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&aFile);
        stream << this->htmlContent << endl;
    }
}
