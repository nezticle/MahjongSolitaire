QT += gui quick 3dcore 3drenderer

SOURCES += \
    main.cpp \
    mahjonggamescene.cpp \
    tableentity.cpp \
    mahjongtileentity.cpp \
    mahjongboardlayoutitem.cpp \
    mahjongboardarea.cpp \
    diffusealphamaterial.cpp

RESOURCES += \
    qml.qrc \
    assets.qrc \
    shaders.qrc

HEADERS += \
    mahjonggamescene.h \
    tableentity.h \
    mahjongtileentity.h \
    mahjongboardlayoutitem.h \
    mahjongboardarea.h \
    diffusealphamaterial.h
