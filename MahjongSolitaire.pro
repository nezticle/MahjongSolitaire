QT += gui quick 3dcore 3drender 3dextras 3dinput

SOURCES += \
    main.cpp \
    mahjonggamescene.cpp \
    tableentity.cpp \
    mahjongboardlayoutitem.cpp \
    mahjongboard.cpp \
    mahjongsharedresources.cpp \
    mahjongtile.cpp \
    mahjongtilematerial.cpp

RESOURCES += \
    qml.qrc \
    assets.qrc

HEADERS += \
    mahjonggamescene.h \
    tableentity.h \
    mahjongboardlayoutitem.h \
    mahjongboard.h \
    mahjongsharedresources.h \
    mahjongtile.h \
    mahjongtilematerial.h
