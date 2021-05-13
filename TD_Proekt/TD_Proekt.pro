QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    enemy.cpp \
    game.cpp \
    gameobject.cpp \
    image.cpp \
    main.cpp \
    tower.cpp \
    wavegenerator.cpp

HEADERS += \
    button.h \
    enemy.h \
    game.h \
    gameobject.h \
    image.h \
    tile.h \
    tower.h \
    wavegenerator.h \
    waypoint.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    bat_l.png \
    bat_r.png \
    red ghost left.png \
    red ghost right.png \
    white ghost left.png \
    white ghost right.png
