#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T15:42:50
#
#-------------------------------------------------

QT       += core gui network webengine webenginewidgets sql webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Browser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    browser.cpp \
    database.cpp \
    htmlpage.cpp \
    fluentbigbutton.cpp \
    fluenttabgroup.cpp \
    fluenttabpanel.cpp \
    fluentmenu.cpp \
    table.cpp \
    iframe.cpp \
    component.cpp \
    textbox.cpp \
    commandbutton.cpp \
    layout.cpp \
    heading.cpp \
    accordion.cpp \
    progressbar.cpp \
    tile.cpp \
    listview.cpp \
    updatepanel.cpp \
    colorpicker.cpp \
    tilesmall.cpp \
    tablesimplified.cpp \
    switcher.cpp \
    browserbookmarks.cpp \
    browsertables.cpp \
    browsernavigation.cpp \
    browserhomepage.cpp \
    browserurl.cpp \
    browsersearch.cpp \
    browsertableau.cpp \
    browsersettings.cpp \
    browserjavascriptfiles.cpp \
    browsereditimages.cpp \
    browsereditbackground.cpp \
    browsereditlinkscolour.cpp \
    browseredittextreplacements.cpp \
    browserfeeds.cpp \
    preloader.cpp \
    slider.cpp \
    tileselected.cpp \
    browsereditfont.cpp \
    browsereditimagerotations.cpp \
    browserdataitem.cpp \
    browsersiteedits.cpp \
    tilelarge.cpp \
    browserfont.cpp \
    browsertheme.cpp \
    paragraph.cpp \
    stepper.cpp \
    popover.cpp \
    browserabout.cpp

HEADERS  += mainwindow.h \
    browser.h \
    database.h \
    htmlpage.h \
    fluentbigbutton.h \
    fluenttabgroup.h \
    fluenttabpanel.h \
    fluentmenu.h \
    table.h \
    iframe.h \
    component.h \
    textbox.h \
    commandbutton.h \
    layout.h \
    heading.h \
    accordion.h \
    progressbar.h \
    tile.h \
    listview.h \
    updatepanel.h \
    colorpicker.h \
    tilesmall.h \
    tablesimplified.h \
    switcher.h \
    browserbookmarks.h \
    browsertables.h \
    browsernavigation.h \
    browserhomepage.h \
    browserurl.h \
    browsersearch.h \
    browsertableau.h \
    browsersettings.h \
    browserjavascriptfiles.h \
    browsereditimages.h \
    browsereditbackground.h \
    browsereditlinkscolour.h \
    browseredittextreplacements.h \
    browserfeeds.h \
    preloader.h \
    slider.h \
    tileselected.h \
    browsereditfont.h \
    browsereditimagerotations.h \
    browserdataitem.h \
    browsersiteedits.h \
    tilelarge.h \
    browserfont.h \
    browsertheme.h \
    paragraph.h \
    stepper.h \
    popover.h \
    browserabout.h

DISTFILES += \
    ../build-Browser-Desktop_Qt_5_8_0_GCC_64bit-Release/js/Sample.js \
    ../build-Browser-Desktop_Qt_5_8_0_GCC_64bit-Release/js/findAndReplaceDOMText.js
