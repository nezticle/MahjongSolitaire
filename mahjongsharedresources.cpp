#include "mahjongsharedresources.h"

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QAttribute>

// For Debuging
#include <Qt3DExtras/QPhongMaterial>

MahjongSharedResources &MahjongSharedResources::instance()
{
    static MahjongSharedResources instance;
    return instance;
}

Qt3DRender::QMesh *MahjongSharedResources::tileColliderMesh(Qt3DCore::QEntity *parent)
{
    if (m_tileColliderMesh->parentNode() != parent)
        m_tileColliderMesh->setParent(parent);
    return m_tileColliderMesh;
}

MahjongSharedResources::MahjongSharedResources()
{
    initSharedResources();
}

MahjongSharedResources::~MahjongSharedResources()
{
    delete m_dummyParent;
}

void MahjongSharedResources::initSharedResources()
{
    // Dummy parent makes sure that shared items are not
    // deleted when their parents are deleted
    m_dummyParent = new Qt3DCore::QEntity;

    m_tileColliderMesh = new Qt3DRender::QMesh();
    m_tileColliderMesh->setSource(QUrl("qrc:/models/MahjongTile_colider.obj"));

    auto phongShader = new Qt3DExtras::QPhongMaterial();
    phongShader->setDiffuse(QColor(Qt::red));
    m_debugMaterial = phongShader;

//    m_tileFaceMaterials.insert("b1", generateMaterial("bamboo1"));
//    m_tileFaceMaterials.insert("b2", generateMaterial("bamboo2"));
//    m_tileFaceMaterials.insert("b3", generateMaterial("bamboo3"));
//    m_tileFaceMaterials.insert("b4", generateMaterial("bamboo4"));
//    m_tileFaceMaterials.insert("b5", generateMaterial("bamboo5"));
//    m_tileFaceMaterials.insert("b6", generateMaterial("bamboo6"));
//    m_tileFaceMaterials.insert("b7", generateMaterial("bamboo7"));
//    m_tileFaceMaterials.insert("b8", generateMaterial("bamboo8"));
//    m_tileFaceMaterials.insert("b9", generateMaterial("bamboo9"));
//    m_tileFaceMaterials.insert("n1", generateMaterial("character1"));
//    m_tileFaceMaterials.insert("n2", generateMaterial("character2"));
//    m_tileFaceMaterials.insert("n3", generateMaterial("character3"));
//    m_tileFaceMaterials.insert("n4", generateMaterial("character4"));
//    m_tileFaceMaterials.insert("n5", generateMaterial("character5"));
//    m_tileFaceMaterials.insert("n6", generateMaterial("character6"));
//    m_tileFaceMaterials.insert("n7", generateMaterial("character7"));
//    m_tileFaceMaterials.insert("n8", generateMaterial("character8"));
//    m_tileFaceMaterials.insert("n9", generateMaterial("character9"));
//    m_tileFaceMaterials.insert("d1", generateMaterial("coin1"));
//    m_tileFaceMaterials.insert("d2", generateMaterial("coin2"));
//    m_tileFaceMaterials.insert("d3", generateMaterial("coin3"));
//    m_tileFaceMaterials.insert("d4", generateMaterial("coin4"));
//    m_tileFaceMaterials.insert("d5", generateMaterial("coin5"));
//    m_tileFaceMaterials.insert("d6", generateMaterial("coin6"));
//    m_tileFaceMaterials.insert("d7", generateMaterial("coin7"));
//    m_tileFaceMaterials.insert("d8", generateMaterial("coin8"));
//    m_tileFaceMaterials.insert("d9", generateMaterial("coin9"));
//    m_tileFaceMaterials.insert("z1", generateMaterial("dragon1"));
//    m_tileFaceMaterials.insert("z2", generateMaterial("dragon2"));
//    m_tileFaceMaterials.insert("z3", generateMaterial("dragon3"));
//    m_tileFaceMaterials.insert("w1", generateMaterial("wind1"));
//    m_tileFaceMaterials.insert("w2", generateMaterial("wind2"));
//    m_tileFaceMaterials.insert("w3", generateMaterial("wind3"));
//    m_tileFaceMaterials.insert("w4", generateMaterial("wind4"));
//    m_tileFaceMaterials.insert("f1", generateMaterial("flower1"));
//    m_tileFaceMaterials.insert("f2", generateMaterial("flower2"));
//    m_tileFaceMaterials.insert("f3", generateMaterial("flower3"));
//    m_tileFaceMaterials.insert("f4", generateMaterial("flower4"));
//    m_tileFaceMaterials.insert("s1", generateMaterial("season1"));
//    m_tileFaceMaterials.insert("s2", generateMaterial("season2"));
//    m_tileFaceMaterials.insert("s3", generateMaterial("season3"));
//    m_tileFaceMaterials.insert("s4", generateMaterial("season4"));
}

Qt3DRender::QMaterial *MahjongSharedResources::debugMaterial(Qt3DCore::QEntity *parent)
{
    if (m_debugMaterial->parentNode() != parent)
        m_debugMaterial->setParent(parent);
    return m_debugMaterial;
}
