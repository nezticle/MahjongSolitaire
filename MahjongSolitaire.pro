QT += gui quick 3dcore 3drenderer 3dcollision

SOURCES += \
    main.cpp \
    mahjonggamescene.cpp \
    tableentity.cpp \
    mahjongtileentity.cpp \
    mahjongboardlayoutitem.cpp \
    mahjongboard.cpp \
    mahjongsharedresources.cpp

RESOURCES += \
    qml.qrc \
    assets.qrc

HEADERS += \
    mahjonggamescene.h \
    tableentity.h \
    mahjongtileentity.h \
    mahjongboardlayoutitem.h \
    mahjongboard.h \
    mahjongsharedresources.h
