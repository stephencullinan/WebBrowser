function selectTabPanel(tabPanelID, selectedTabPanel)
{
    var aTabPanel = document.getElementById(tabPanelID);
    for(var counter = 0; counter < aTabPanel.children.length; counter++)
        aTabPanel.children[counter].style = "display:none;";
    aTabPanel.children[selectedTabPanel].style = "display:block;";
    $('body').animate({scrollTop:0}, 'fast');
}
function viewTable(tableTitle, formattedTableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
       var tables = channel.objects.tables;
       tables.createFormattedHTMLTable(tableTitle, formattedTableTitle, function(receivedObject)
       {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#table_' + formattedTableTitle).dataTable();
       });
    });
}
function deleteRowFromTable(tableTitle, formattedTableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.createFormattedHTMLTableForDeletions(tableTitle, formattedTableTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#table_' + formattedTableTitle).dataTable();
        });
    });
}
function deleteSelectedRowFromTable(tableTitle, formattedTableTitle, columnTitles, columnValues)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.displayDeleteNotification(tableTitle, formattedTableTitle, columnTitles, columnValues,
                                         function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function deleteConfirmation(tableTitle, formattedTableTitle, columnValues)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.deleteSelectedRow(tableTitle, formattedTableTitle, columnValues, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#table_' + formattedTableTitle).dataTable();
        });
    });
}
function expungeTable(tableTitle, formattedTableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.displayExpungeNotification(tableTitle, formattedTableTitle, function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function viewTableWithNoJoins(tableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.createHTMLTable(tableTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#table_' + tableTitle).dataTable();
        });
    });
}
function deleteTableWithNoJoins(tableTitle, formattedTableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.createHTMLTableForDeletions(tableTitle, formattedTableTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#table_' + formattedTableTitle).dataTable();
        });
    });
}
function expungeConfirmation(tableTitle, formattedTableTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tables = channel.objects.tables;
        tables.deleteAllRows(tableTitle, formattedTableTitle, function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function goBackward()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var navigation = channel.objects.navigation;
        navigation.goBackward(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function goForward()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var navigation = channel.objects.navigation;
        navigation.goForward(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function openHomePage()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var home = channel.objects.home;
        home.loadHomePage(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function reload()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var navigation = channel.objects.navigation;
        navigation.refresh(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function stop()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var navigation = channel.objects.navigation;
        navigation.halt(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function displayBrowser()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var navigation = channel.objects.navigation;
        navigation.displayBrowser(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function addBookmark()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var bookmarks = channel.objects.bookmarks;
        bookmarks.createNewBookmark(function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function saveBookmark()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var bookmarks = channel.objects.bookmarks;
        var siteTitleTextBox = document.getElementById("siteTitleTextBox").value;
        var siteUrlTextBox = document.getElementById("siteUrlTextBox").value;
        removeErrorMessages(["siteTitleTextBox", "siteUrlTextBox"]);
        var errorFound = false;
        if(siteTitleTextBox.length < 2)
        {
            addErrorMessage("siteTitleTextBox", "A valid site title should have at least 2 characters");
            errorFound = true;
        }
        if(siteUrlTextBox.length < 2)
        {
            addErrorMessage("siteUrlTextBox", "A valid site url should have at least 2 characters");
            errorFound = true;
        }
        if(isValidURL(siteUrlTextBox) === false)
        {
            addErrorMessage("siteUrlTextBox", "This is not a valid url");
            errorFound = true;
        }
        if(errorFound === false)
        {
            bookmarks.saveCreatedBookmark(siteUrlTextBox, siteTitleTextBox, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = receivedObject;
                $('#table_Bookmarks').dataTable();
            });
        }
    });
}
function addFont()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var font = channel.objects.font;
        font.createNewFont(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function saveFont()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var font = channel.objects.font;
        var fontFaceTextBox = document.getElementById('fontFaceTextBox').value;
        var errorFound = false;
        removeErrorMessages(['fontFaceTextBox']);
        if(fontFaceTextBox.length < 2)
        {
            errorFound = true;
            addErrorMessage('fontFaceTextBox', 'A valid font should have at least 2 characters');
        }
        if(errorFound === false)
        {
            font.saveCreatedFont(fontFaceTextBox, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = receivedObject;
                $('#table_font').dataTable();
            });
        }
    });
}
function addThemeStepOne()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.createNewThemeStepOne(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepTwo()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var themeTitleTextBox = document.getElementById('themeTitleTextBox').value;
        var themeDescriptionTextBox = document.getElementById('themeDescriptionTextBox').value;
        var themeAuthorTextBox = document.getElementById('themeAuthorTextBox').value;
        var errorLocated = false;
        removeErrorMessages(['themeTitleTextBox', 'themeDescriptionTextBox', 'themeAuthorTextBox']);
        if(themeTitleTextBox.length < 2)
        {
            errorLocated = true;
            addErrorMessage('themeTitleTextBox', 'A valid theme title should have at least 2 characters');
        }
        if(themeDescriptionTextBox.length < 2)
        {
            errorLocated = true;
            addErrorMessage('themeDescriptionTextBox',
                            'A valid theme description should have at least 2 characters');
        }
        if(themeAuthorTextBox.length < 2)
        {
            errorLocated = true;
            addErrorMessage('themeAuthorTextBox',
                            "A valid theme author should have at least 2 characters");
        }
        if(errorLocated === false)
        {
            var parameters = extractValues(['themeTitleTextBox', 'themeDescriptionTextBox', 'themeAuthorTextBox']);
            theme.createNewThemeStepTwo(parameters, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = receivedObject;
            });
        }
    });
}
function addThemeStepThree()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var linksColour = document.getElementById('applyLinksColourPicker_Input').value;
        if(document.getElementById('applyLinksColourSwitch_Input').value === "off")
            linksColour = "";
        theme.createNewThemeStepThree(linksColour, function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepFour()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var backgroundColour = document.getElementById('applyBackgroundColourPicker_Input').value;
        if(document.getElementById('applyBackgroundColourSwitch_Input').value === "off")
            backgroundColour = "";
        theme.createNewThemeStepFour(backgroundColour, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepFive()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var fontFace = document.getElementById('availableFontsListView_Input').value;
        var fontSize = document.getElementById('fontSizeTextBox').value;
        if(document.getElementById('editFontMenuSelectedTile_Input').value === "off")
        {
            fontFace = "";
            fontSize = "";
        }
        theme.createNewThemeStepFive(fontFace, fontSize, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepSix()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var textReplacements = retrieveDataFromTable().split(":");
        theme.createNewThemeStepSix(textReplacements[0], textReplacements[1], function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepSeven()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var textReplacements = retrieveDataFromTable().split(":");
        theme.createNewThemeStepSeven(textReplacements[0], textReplacements[1], function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepEight()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var degrees = document.getElementById('editImageRotationsDegreesTextBox').value;
        var transition = document.getElementById('editImageTransitionTextBox').value;
        if(document.getElementById('editImageRotationsMenuSelectedTile_Input').value === "off")
        {
            degrees = "";
            transition = "";
        }
        theme.createNewThemeStepEight(degrees, transition, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function addThemeStepNine()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var removePNGFilesTile = convertValueFromSelectedTileToBoolean('removePNGFilesTile');
        var removeJPEGFilesTile = convertValueFromSelectedTileToBoolean('removeJPEGFilesTile');
        var removeGIFFilesTile = convertValueFromSelectedTileToBoolean('removeGIFFilesTile');
        theme.createNewThemeStepNine(removePNGFilesTile, removeJPEGFilesTile, removeGIFFilesTile,
                                     function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function viewAvailableThemes(viewingOnly)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.viewAvailableThemes(viewingOnly, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function viewTheme(themeID)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.viewDetailedDescriptionPageForTheme(themeID, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
            $('#ThemeSites_' + themeID).dataTable();
            $('#ThemeSettings_' + themeID).dataTable();
            initialiseSteppers();
        });
    });
}
function deleteTheme(themeID, themeTitle)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.deleteExistingTheme(themeID, themeTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function deleteThemeConfirmation(themeID)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.deleteExistingThemeConfirmation(themeID, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyTheme(themeID)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var applyThemeSetting = convertValueFromSelectedTileToBoolean("themeTileSelected");
        theme.applyThemeToSite(applyThemeSetting, function(receivedObject)
        {
            document.getElementById('sitesUpdatePanel').innerHTML = receivedObject;
            $('#ThemeSites_' + themeID).dataTable();
        });
    });
}
function sortTableauItems()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tableau = channel.objects.tableau;
        var tableauSortingOption = document.getElementById('tableauSortingListView_Input').value;
        var tableauNumberOfItemsOption = document.getElementById('tableauNumberOfItemsListView_Input').value;
        tableau.sortItems(tableauSortingOption, tableauNumberOfItemsOption, function(receivedObject)
        {
            document.getElementById('tableauUpdatePanel').innerHTML = receivedObject;
        });
    });
}
function addNewReview()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        theme.addNewReview(function(receivedObject)
        {
            document.getElementById('submitReviewUpdatePanel').innerHTML = receivedObject;
            initialiseStepper("reviewRating");
        });
    });
}
function saveNewReview()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var theme = channel.objects.theme;
        var reviewRating = document.getElementById('reviewRating_Input').value;
        var reviewDescription = document.getElementById('reviewDescriptionTextBox').value;
        var reviewFirstName = document.getElementById('reviewFirstNameTextBox').value;
        var reviewLastName = document.getElementById('reviewLastNameTextBox').value;
        var errorLocated = false;
        removeErrorMessages(['reviewDescriptionTextBox', 'reviewFirstNameTextBox', 'reviewLastNameTextBox']);
        if(reviewDescription.length < 2)
        {
            errorLocated = true;
            addErrorMessage('reviewDescriptionTextBox',
                            'A valid review description should contain at least 2 characters');
        }
        if(reviewFirstName.length < 2)
        {
            errorLocated = true;
            addErrorMessage('reviewFirstNameTextBox', 'A valid first name should contain at least 2 characters');
        }
        if(reviewLastName.length < 2)
        {
            errorLocated = true;
            addErrorMessage('reviewLastNameTextBox', 'A valid last name should contain at least 2 characters');
        }
        if(errorLocated === false)
        {
            theme.saveNewReview(reviewRating, reviewDescription, reviewFirstName, reviewLastName,
                                function(receivedObject)
            {
                document.getElementById('reviewsUpdatePanel').innerHTML = receivedObject;
                initialiseSteppers();
            })
        }
    });
}
function updateHomePage()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var home = channel.objects.home;
        home.setHomePage(function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function updateHomePageToCurrentPage()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var home = channel.objects.home;
        home.setHomePageToCurrentPage(function(receivedObject)
        {

        });
    });
}
function saveUpdatedHomePage()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var home = channel.objects.home;
        var homePageTextBox = document.getElementById("homePageTextBox").value;
        removeErrorMessages(['homePageTextBox']);
        var errorFound = false;
        if(homePageTextBox.length < 2)
        {
            errorFound = true;
            addErrorMessage('homePageTextBox', 'A valid home page should have at least 2 characters');
        }
        if(isValidURL(homePageTextBox) === false)
        {
            errorFound = true;
            addErrorMessage('homePageTextBox', 'This is not a valid url');
        }
        if(errorFound === false)
        {
            home.applyHomePageSetting(homePageTextBox, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = receivedObject;
            });
        }
    });
}
function enterURL()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var URL = channel.objects.URL;
        URL.openURLPage(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function performSearch()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var search = channel.objects.search;
        search.performSearchOnGoogle(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function openSelectedURL()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var URL = channel.objects.URL;
        var openURLTextBox = document.getElementById('openURLTextBox').value;
        var errorFound = false;
        removeErrorMessages(['openURLTextBox']);
        if(openURLTextBox.length < 2)
        {
            errorFound = true;
            addErrorMessage('openURLTextBox', 'A valid url should have at least 2 characters');
        }
        if(isValidURL(openURLTextBox) === false)
        {
            errorFound = true;
            addErrorMessage('openURLTextBox', 'This is not a valid url');
        }
        if(errorFound === false)
        {
            URL.openSelectedURL(openURLTextBox, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = '';
            });
        }
    });
}
function openURL(url)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var URL = channel.objects.URL;
        URL.openSelectedURL(url, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function replaceTextMenu(textReplacementsOnly)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var edittextreplacements = channel.objects.edittextreplacements;
        edittextreplacements.replaceTextMenu(textReplacementsOnly, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function getTextSuggestions()
{
    var locateText = document.getElementById('locateTextBox').value + ";";
    var replaceText;
    if(document.getElementById('replaceTextBox'))
        replaceText = document.getElementById('replaceTextBox').value + ";";
    if(document.getElementById('replaceColourPicker_Input'))
        replaceText = document.getElementById('replaceColourPicker_Input').value + ";";
    if(locateText.length > 1 && replaceText.length > 1)
    {
        var suggestionsTable = document.getElementById('existingSuggestionsTable');
        if(suggestionsTable.children.length >= 2)
        {
            var tableRows = suggestionsTable.children[1];
            for(var counter = 0; counter < tableRows.children.length; counter++)
            {
                if(tableRows.children[counter].children.length >= 2)
                {
                    locateText += tableRows.children[counter].children[0].innerHTML + ";";
                    replaceText += tableRows.children[counter].children[1].innerHTML + ";";
                }
            }
        }
        var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
        {
            var edittextreplacements = channel.objects.edittextreplacements;
            edittextreplacements.replaceTextSuggestion(locateText, replaceText, function(receivedObject)
            {
                document.getElementById('existingSuggestionsPanel').innerHTML = receivedObject;
                document.getElementById('locateTextBox').value = '';
                document.getElementById('replaceTextBox').value = '';
            });
        });
    }
    if(locateText.length === 1)
        displayNotification('Locate Text Must Be Longer Than 0 Characters');
    if(replaceText.length === 1)
        displayNotification('Replace Text Must Be Longer Than 0 Characters');
}
function applyReplaceText(textReplacementsOnly)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var edittextreplacements = channel.objects.edittextreplacements;
        var splitString = retrieveDataFromTable().split(":");
        edittextreplacements.applyReplaceText(splitString[0], splitString[1], textReplacementsOnly,
                                              function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function retrieveDataFromTable()
{
    var locateText = '';
    var replaceText = '';
    var suggestionsTable = document.getElementById('existingSuggestionsTable');
    if(suggestionsTable.children.length >= 2)
    {
        var tableRows = suggestionsTable.children[1];
        for(var counter = 0; counter < tableRows.children.length; counter++)
        {
            if(tableRows.children[counter].children.length >= 2)
            {
                locateText += tableRows.children[counter].children[0].innerHTML + ";";
                replaceText += tableRows.children[counter].children[1].innerHTML + ";";
            }
        }
    }
    if(document.getElementById('applyTextReplacementsSwitch_Input').value === 'off')
    {
       locateText = "";
        replaceText = "";
    }
    return locateText + ":" + replaceText;
}
function changeTextColour()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var help = channel.objects.help;
        help.replaceTextWithSelectedColour(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyBackgroundColourMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editbackground = channel.objects.editbackground;
        editbackground.applyBackgroundColourMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyBackgroundColourSettings()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editbackground = channel.objects.editbackground;
        var colourTitle = document.getElementById('applyBackgroundColourPicker_Input').value;
        if(document.getElementById('applyBackgroundColourSwitch_Input').value === "off")
            colourTitle = "";
        editbackground.applyBackgroundColourSettings(colourTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function applyLinksColourMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editlinkscolour = channel.objects.editlinkscolour;
        editlinkscolour.applyLinksColourMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyLinksColourSettings()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editlinkscolour = channel.objects.editlinkscolour;
        var colourTitle = document.getElementById('applyLinksColourPicker_Input').value;
        if(document.getElementById('applyLinksColourSwitch_Input').value === "off")
            colourTitle = "";
        editlinkscolour.applyLinksColourSettings(colourTitle, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        })
    });
}
function openSelectedSearch()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var search = channel.objects.search;
        var googleSearchQueryTextBox = document.getElementById('googleSearchQueryTextBox').value;
        var errorFound = false;
        if(googleSearchQueryTextBox.length < 2)
        {
            errorFound = true;
            addErrorMessage('googleSearchQueryTextBox', 'A valid search query should have at least 2 characters');
        }
        if(errorFound === false)
        {
            search.performSelectedSearch(googleSearchQueryTextBox, function(channel)
            {
                document.getElementById('mainPanel').innerHTML = '';
            });
        }
    });
}
function removeSelectedImages(currentState, imageExtension, removeImageExtension)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editimages = channel.objects.editimages;
        editimages.removeImageFiles(currentState, imageExtension, removeImageExtension, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function highlightLinks(currentState)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var help = channel.objects.help;
        help.highlightLinks(currentState, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function createTableau()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var tableau = channel.objects.tableau;
        tableau.createTableau(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function viewAvailableFeeds()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var feeds = channel.objects.feeds;
        feeds.viewFeedsAsTiles(function(receivedObject)
        {
           document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function viewFeeds(url)
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var feeds = channel.objects.feeds;
        feeds.downloadFeeds(url, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function getFeedsAccordion()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var feeds = channel.objects.feeds;
        feeds.getFeedsAccordion(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function createNewFeed()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var feeds = channel.objects.feeds;
        feeds.createNewFeed(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function saveCreatedFeed()
{
    var feedTitleTextBox = document.getElementById('feedTitleTextBox').value;
    var feedUrlTextBox = document.getElementById('feedUrlTextBox').value;
    var errorFound = false;
    removeErrorMessages(['feedTitleTextBox', 'feedUrlTextBox']);
    if(feedTitleTextBox.length < 2)
    {
        errorFound = true;
        addErrorMessage('feedTitleTextBox', 'A valid title of a feed should have at least 2 characters');
    }
    if(feedUrlTextBox.length < 2)
    {
        errorFound = true;
        addErrorMessage('feedUrlTextBox', 'A valid url of a feed should have at least 2 characters');
    }
    if(isValidURL(feedUrlTextBox) === false)
    {
        errorFound = true;
        addErrorMessage('feedUrlTextBox', 'This is not a valid url');
    }
    if(errorFound === false)
    {
        var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
        {
            var feeds = channel.objects.feeds;
            feeds.saveCreatedFeed(feedUrlTextBox, feedTitleTextBox, function(receivedObject)
            {
                document.getElementById('mainPanel').innerHTML = receivedObject;
                $('#table_Feeds').dataTable();
            });
        });
    }
}
function getEditFontMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editfont = channel.objects.editfont;
        editfont.editFontMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyEditFont()
{
    var fontFace = document.getElementById('availableFontsListView_Input').value;
    var fontSize = document.getElementById('fontSizeTextBox').value;
    if(document.getElementById('editFontMenuSelectedTile_Input').value === 'off')
    {
        fontFace = '';
        fontSize = -1;
    }
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editfont = channel.objects.editfont;
        editfont.applyFontSettings(fontFace, fontSize, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function getEditImageRotationsMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editimagerotations = channel.objects.editimagerotations;
        editimagerotations.editImageRotationsMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyEditImageRotations()
{
    var imageRotations = document.getElementById('editImageRotationsDegreesTextBox').value;
    var transitionTime = document.getElementById('editImageTransitionTextBox').value;
    if(document.getElementById('editImageRotationsMenuSelectedTile_Input').value === 'off')
    {
        imageRotations = -1;
        transitionTime = -1;
    }
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editimagerotations = channel.objects.editimagerotations;
        editimagerotations.applyImageRotationSettings(imageRotations, transitionTime, function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = '';
        });
    });
}
function getEditImagesMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editimages = channel.objects.editimages;
        editimages.getEditImagesMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function applyEditImageSettings()
{
    var removePNGFilesTile = convertValueFromSelectedTileToBoolean('removePNGFilesTile');
    var removeJPEGFilesTile = convertValueFromSelectedTileToBoolean('removeJPEGFilesTile');
    var removeGIFFilesTile = convertValueFromSelectedTileToBoolean('removeGIFFilesTile');
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var editimages = channel.objects.editimages;
        editimages.applyEditImageSettings(removePNGFilesTile, removeJPEGFilesTile, removeGIFFilesTile,
                                          function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = "";
        });
    });
}
function getAboutMenu()
{
    var aWebChannel = new QWebChannel(qt.webChannelTransport, function(channel)
    {
        var about = channel.objects.about;
        about.getAboutMenu(function(receivedObject)
        {
            document.getElementById('mainPanel').innerHTML = receivedObject;
        });
    });
}
function extractValues(controlIDs)
{
    var parameters = [];
    for(var counter = 0; counter < controlIDs.length; counter++)
        parameters[counter] = document.getElementById(controlIDs[counter]).value;
    return parameters;
}
function selectColour(controlID, selectedColour, selectedColourTitle)
{
    var selectedControl = document.getElementById(controlID);
    var position = 0;
    for(var counter = 0; counter < selectedControl.children.length; counter++)
    {
        for(var index = 0; index < selectedControl.children[counter].children.length; index++)
        {
            var className = selectedControl.children[counter].children[index].children[0].className;
            if(className.indexOf("element-selected") >= 0)
            {
                className = className.substring(0, className.length - 16);
                selectedControl.children[counter].children[index].children[0].className = className;
            }
            if(selectedColour === position)
            {
                className = className + " element-selected";
                selectedControl.children[counter].children[index].children[0].className = className;
            }
            position++;
        }
    }
    document.getElementById(controlID + "_Input").value = selectedColourTitle;
}
function tileSelected(id, onText, offText, panelID)
{
    var selectedTile = document.getElementById(id);
    if(selectedTile.className.indexOf("element-selected") > -1)
    {
        selectedTile.className = selectedTile.className.substring(0,
                                 selectedTile.className.indexOf("element-selected"));
        document.getElementById(id + "_Input").value = "off";
        document.getElementById(id + "_Label").innerText = offText;
        if(panelID && document.getElementById(panelID))
            $('#' + panelID).hide();
    }
    else
    {
        selectedTile.className = selectedTile.className + " element-selected";
        document.getElementById(id + "_Input").value = "on";
        document.getElementById(id + "_Label").innerText = onText;
        if(panelID && document.getElementById(panelID))
            $('#' + panelID).show();
    }
}
function convertValueFromSelectedTileToBoolean(id)
{
    var selectedTileElementValue = document.getElementById(id + "_Input").value;
    if(selectedTileElementValue === "on")
        return true;
    return false;
}
function listItemSelected(selectedListItemPosition, selectedListItemValue, selectedListItemID)
{
    var listItemComponent = document.getElementById(selectedListItemID);
    if(listItemComponent.children.length > 0)
    {
        listItemComponent = listItemComponent.children[0];
        if(listItemComponent.children.length > 0)
        {
            for(var counter = 1; counter < listItemComponent.children.length; counter++)
            {
                var currentChild = listItemComponent.children[counter];
                if(currentChild.children.length > 0)
                {
                    currentChild.children[0].className = "list marked";
                    if((counter - 1) === selectedListItemPosition)
                        currentChild.children[0].className = "list active marked";
                }
            }
        }
    }
    if(document.getElementById(selectedListItemID + "_Input"))
        document.getElementById(selectedListItemID + "_Input").value = selectedListItemValue;
}
function initialiseSteppers()
{
    var steppers = document.getElementsByClassName("stepper diamond");
    for(var counter = 0; counter < steppers.length; counter++)
        initialiseStepper(steppers[counter].id);
}
function initialiseStepper(stepperID)
{
    var width = window.outerWidth;
    var stepper = document.getElementById(stepperID + '_List');
    for(var counter = 0; counter < stepper.children.length; counter++)
    {
        stepper.children[counter].style = "left: " +
        parseInt(((counter + 1) / stepper.children.length) * width * .92) + "px;";
    }
}
function updateStepper(stepperID, selectedStep)
{
    var stepper = document.getElementById(stepperID + '_List');
    for(var counter = 0; counter < stepper.children.length; counter++)
    {
        stepper.children[counter].className = "";
        if((counter + 1) < selectedStep)
            stepper.children[counter].className = "complete";
        else if((counter + 1) === selectedStep)
        {
            stepper.children[counter].className = "current";
            document.getElementById(stepperID + "_Input").value = counter + 1;
        }
    }
}
function removeErrorMessages(textBoxIDs)
{
    for(var counter = 0; counter < textBoxIDs.length; counter++)
    {
        document.getElementById(textBoxIDs[counter] + '_ErrorMessage').style = "display:none;";
    }
}
function addErrorMessage(id, errorMessage)
{
    var errorMessagePopover = document.getElementById(id + '_ErrorMessage');
    if(errorMessagePopover.children.length > 0)
    {
        errorMessagePopover.children[0].innerHTML = errorMessage;
        $('#' + id + "_ErrorMessage").show();
    }
}
//jQuery Validation PlugIn Regex
function isValidURL(url)
{
    return /^(https?|s?ftp):\/\/(((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:)*@)?(((\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5]))|((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?)(:\d*)?)(\/((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)+(\/(([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)*)*)?)?(\?((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|[\uE000-\uF8FF]|\/|\?)*)?(#((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|\/|\?)*)?$/i.test(url);
}
