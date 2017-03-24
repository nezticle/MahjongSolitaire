#include "mahjongsharedresources.h"

#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QAttribute>

MahjongSharedResources &MahjongSharedResources::instance()
{
    static MahjongSharedResources instance;
    return instance;
}

Qt3DRender::QMaterial *MahjongSharedResources::materialForTileface(const QString &tileface)
{
    return m_tileFaceMaterials[tileface];
}

Qt3DRender::QMaterial *MahjongSharedResources::tileMaterial()
{
    return m_tileMaterial;
}

Qt3DRender::QMaterial *MahjongSharedResources::tileSelectedMaterial()
{
    return m_tileSelectedMaterial;
}

Qt3DRender::QMesh *MahjongSharedResources::tileMesh()
{
    return m_tileMesh;
}

Qt3DRender::QMesh *MahjongSharedResources::tilefaceMesh()
{
    return m_tilefaceMesh;
}

MahjongSharedResources::MahjongSharedResources()
{
    initSharedResources();
}

void MahjongSharedResources::initSharedResources()
{
    //Tile Material
    m_tileMaterial = generateMaterial("Tile_diffuse");

    //Tile Selected Material
    m_tileSelectedMaterial = generateMaterial("TileSelected_diffuse");

    //Tile Mesh
    m_tileMesh = new Qt3DRender::QMesh();
    m_tileMesh->setSource(QUrl("qrc:/models/MahjongTile.obj"));

    //Tileface Mesh
    m_tilefaceMesh = new Qt3DRender::QMesh();
    m_tilefaceMesh->setSource(QUrl("qrc:/models/MahjongTileface.obj"));

    //Texture Atlas
    m_textureAtlas = new TextureAtlas();

    addImageToAtlas("qrc:/textures/bamboo1.png", "b1");
    addImageToAtlas("qrc:/textures/bamboo2.png", "b2");
    addImageToAtlas("qrc:/textures/bamboo3.png", "b3");
    addImageToAtlas("qrc:/textures/bamboo4.png", "b4");
    addImageToAtlas("qrc:/textures/bamboo5.png", "b5");
    addImageToAtlas("qrc:/textures/bamboo6.png", "b6");
    addImageToAtlas("qrc:/textures/bamboo7.png", "b7");
    addImageToAtlas("qrc:/textures/bamboo8.png", "b8");
    addImageToAtlas("qrc:/textures/bamboo9.png", "b9");
    addImageToAtlas("qrc:/textures/character1.png", "n1");
    addImageToAtlas("qrc:/textures/character2.png", "n2");
    addImageToAtlas("qrc:/textures/character3.png", "n3");
    addImageToAtlas("qrc:/textures/character4.png", "n4");
    addImageToAtlas("qrc:/textures/character5.png", "n5");
    addImageToAtlas("qrc:/textures/character6.png", "n6");
    addImageToAtlas("qrc:/textures/character7.png", "n7");
    addImageToAtlas("qrc:/textures/character8.png", "n8");
    addImageToAtlas("qrc:/textures/character9.png", "n9");
    addImageToAtlas("qrc:/textures/coin1.png", "d1");
    addImageToAtlas("qrc:/textures/coin2.png", "d2");
    addImageToAtlas("qrc:/textures/coin3.png", "d3");
    addImageToAtlas("qrc:/textures/coin4.png", "d4");
    addImageToAtlas("qrc:/textures/coin5.png", "d5");
    addImageToAtlas("qrc:/textures/coin6.png", "d6");
    addImageToAtlas("qrc:/textures/coin7.png", "d7");
    addImageToAtlas("qrc:/textures/coin8.png", "d8");
    addImageToAtlas("qrc:/textures/coin9.png", "d9");
    addImageToAtlas("qrc:/textures/dragon1.png", "z1");
    addImageToAtlas("qrc:/textures/dragon2.png", "z2");
    addImageToAtlas("qrc:/textures/dragon3.png", "z3");
    addImageToAtlas("qrc:/textures/wind1.png", "w1");
    addImageToAtlas("qrc:/textures/wind2.png", "w2");
    addImageToAtlas("qrc:/textures/wind3.png", "w3");
    addImageToAtlas("qrc:/textures/wind4.png", "w4");
    addImageToAtlas("qrc:/textures/flower1.png", "f1");
    addImageToAtlas("qrc:/textures/flower2.png", "f2");
    addImageToAtlas("qrc:/textures/flower3.png", "f3");
    addImageToAtlas("qrc:/textures/flower4.png", "f4");
    addImageToAtlas("qrc:/textures/season1.png", "s1");
    addImageToAtlas("qrc:/textures/season2.png", "s2");
    addImageToAtlas("qrc:/textures/season3.png", "s3");
    addImageToAtlas("qrc:/textures/season4.png", "s4");
    addImageToAtlas("qrc:/textures/Tile_diffuse.png", "tile");
    addImageToAtlas("qrc:/textures/TileSelected_diffuse.png", "selected");

    m_tileFaceMaterials.insert("b1", generateMaterial("bamboo1"));
    m_tileFaceMaterials.insert("b2", generateMaterial("bamboo2"));
    m_tileFaceMaterials.insert("b3", generateMaterial("bamboo3"));
    m_tileFaceMaterials.insert("b4", generateMaterial("bamboo4"));
    m_tileFaceMaterials.insert("b5", generateMaterial("bamboo5"));
    m_tileFaceMaterials.insert("b6", generateMaterial("bamboo6"));
    m_tileFaceMaterials.insert("b7", generateMaterial("bamboo7"));
    m_tileFaceMaterials.insert("b8", generateMaterial("bamboo8"));
    m_tileFaceMaterials.insert("b9", generateMaterial("bamboo9"));
    m_tileFaceMaterials.insert("n1", generateMaterial("character1"));
    m_tileFaceMaterials.insert("n2", generateMaterial("character2"));
    m_tileFaceMaterials.insert("n3", generateMaterial("character3"));
    m_tileFaceMaterials.insert("n4", generateMaterial("character4"));
    m_tileFaceMaterials.insert("n5", generateMaterial("character5"));
    m_tileFaceMaterials.insert("n6", generateMaterial("character6"));
    m_tileFaceMaterials.insert("n7", generateMaterial("character7"));
    m_tileFaceMaterials.insert("n8", generateMaterial("character8"));
    m_tileFaceMaterials.insert("n9", generateMaterial("character9"));
    m_tileFaceMaterials.insert("d1", generateMaterial("coin1"));
    m_tileFaceMaterials.insert("d2", generateMaterial("coin2"));
    m_tileFaceMaterials.insert("d3", generateMaterial("coin3"));
    m_tileFaceMaterials.insert("d4", generateMaterial("coin4"));
    m_tileFaceMaterials.insert("d5", generateMaterial("coin5"));
    m_tileFaceMaterials.insert("d6", generateMaterial("coin6"));
    m_tileFaceMaterials.insert("d7", generateMaterial("coin7"));
    m_tileFaceMaterials.insert("d8", generateMaterial("coin8"));
    m_tileFaceMaterials.insert("d9", generateMaterial("coin9"));
    m_tileFaceMaterials.insert("z1", generateMaterial("dragon1"));
    m_tileFaceMaterials.insert("z2", generateMaterial("dragon2"));
    m_tileFaceMaterials.insert("z3", generateMaterial("dragon3"));
    m_tileFaceMaterials.insert("w1", generateMaterial("wind1"));
    m_tileFaceMaterials.insert("w2", generateMaterial("wind2"));
    m_tileFaceMaterials.insert("w3", generateMaterial("wind3"));
    m_tileFaceMaterials.insert("w4", generateMaterial("wind4"));
    m_tileFaceMaterials.insert("f1", generateMaterial("flower1"));
    m_tileFaceMaterials.insert("f2", generateMaterial("flower2"));
    m_tileFaceMaterials.insert("f3", generateMaterial("flower3"));
    m_tileFaceMaterials.insert("f4", generateMaterial("flower4"));
    m_tileFaceMaterials.insert("s1", generateMaterial("season1"));
    m_tileFaceMaterials.insert("s2", generateMaterial("season2"));
    m_tileFaceMaterials.insert("s3", generateMaterial("season3"));
    m_tileFaceMaterials.insert("s4", generateMaterial("season4"));
}


Qt3DRender::QMaterial *MahjongSharedResources::generateMaterial(const QString &textureName)
{
    Qt3DExtras::QDiffuseMapMaterial *material = new Qt3DExtras::QDiffuseMapMaterial;
    Qt3DRender::QTextureImage *diffuseTexture = new Qt3DRender::QTextureImage;
    diffuseTexture->setSource(QUrl(QString("qrc:/textures/" + textureName + ".png")));
    material->diffuse()->addTextureImage(diffuseTexture);
    material->diffuse()->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    material->setAmbient(QColor(20, 20, 20));

    return material;
}

void MahjongSharedResources::addImageToAtlas(const QString &filename, const QString &id)
{
    m_texturesIds.insert(id, m_textureAtlas->addImage(QImage(filename), 1));
}

