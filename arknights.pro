QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./source/agent/agent.cpp \
    ./source/agent/agentatkarea.cpp \
    ./source/agent/placeagent.cpp \
    ./source/agent/agentcard.cpp \
    ./source/agent/exusiai.cpp \
    ./source/agent/eyjafjalla.cpp\
    ./source/agent/melantha.cpp \
    ./source/agent/skadi.cpp \
    ./source/agent/silverash.cpp \
    ./source/map/coster.cpp \
    ./source/map/fightmainwindow.cpp \
    ./source/map/fightmap.cpp \
    ./source/map/mapblock.cpp \
    ./source/map/hp.cpp \
    ./source/mainwindow/jumpbutton.cpp \
    ./source/mainwindow/mainwindow.cpp \
    ./source/enemy/enemy.cpp \
    ./source/enemy/defence4.cpp \
    ./source/enemy/ghost.cpp \
    ./source/enemy/skii.cpp \
    ./source/enemy/soldier.cpp \
    ./source/enemy/uav.cpp \
    ./source/enemy/warlock.cpp \
    main.cpp

HEADERS += \
    ./header/common.h \
    ./header/agent/agent.h \
    ./header/agent/agentatkarea.h \
    ./header/agent/agentcard.h \
    ./header/agent/placeagent.h \
    ./header/agent/exusiai.h \
    ./header/agent/eyjafjalla.h \
    ./header/agent/melantha.h \
    ./header/agent/skadi.h \
    ./header/agent/silverash.h \
    ./header/map/coster.h \
    ./header/map/fightmainwindow.h \
    ./header/map/fightmap.h \
    ./header/map/hp.h \
    ./header/map/mapblock.h \
    ./header/mainwindow/jumpbutton.h \
    ./header/mainwindow/mainwindow.h \
    ./header/enemy/enemy.h \
    ./header/enemy/defence4.h \
    ./header/enemy/ghost.h \
    ./header/enemy/skii.h \
    ./header/enemy/soldier.h \
    ./header/enemy/uav.h \
    ./header/enemy/warlock.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Source.qrc
