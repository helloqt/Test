#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:23:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BranQt4
TEMPLATE = app

SOURCES += code/main/main.cpp \
    code/main/mainwindow.cpp \
    code/optionPage/optionPage.cpp \
    code/optionPage/setWifi/setWifiPage.cpp \
    code/optionFrame.cpp 

HEADERS  += code/main/mainwindow.h \
    code/optionPage/optionPage.h \
    code/optionPage/setWifi/setWifiPage.h \
	code/optionFrame.h 


FORMS    += ui/landscape/mainwindow.ui \
    ui/landscape/setWifiPage.ui \
    ui/landscape/optionPage.ui 

INCLUDEPATH += code/ \
    code/optionPage \
    code/optionPage/setWifi 
	
RESOURCES += \
    BranQt.qrc \ 






