QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #actions.cpp \
    ciede2000.cpp \
    filehelper.cpp \
    friendlyrgb.cpp \
    geomath.cpp \
    main.cpp \
    mainpresenter.cpp \
    mainwindow.cpp \
    #model.cpp \
 \    #updates.cpp
    settings.cpp

HEADERS += \
    #actions.h \
    ciede2000.h \
    filehelper.h \
    friendlyrgb.h \
    geomath.h \
    global.h \
    imainview.h \
    mainpresenter.h \
    mainviewmodel.h \
    mainwindow.h \
    #model.h \
 \    #updates.h
    settings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
