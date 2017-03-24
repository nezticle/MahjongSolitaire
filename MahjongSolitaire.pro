QT += gui quick 3dcore 3drender 3dextras 3dinput

SOURCES += \
    main.cpp \
    mahjonggamescene.cpp \
    tableentity.cpp \
    mahjongtileentity.cpp \
    mahjongboardlayoutitem.cpp \
    mahjongboard.cpp \
    mahjongsharedresources.cpp \
    util/textureatlas.cpp \
    util/areaallocator.cpp \
    mahjongtilematerial.cpp

RESOURCES += \
    qml.qrc \
    assets.qrc

HEADERS += \
    mahjonggamescene.h \
    tableentity.h \
    mahjongtileentity.h \
    mahjongboardlayoutitem.h \
    mahjongboard.h \
    mahjongsharedresources.h \
    util/textureatlas.h \
    util/areaallocator.h \
    mahjongtilematerial.h
