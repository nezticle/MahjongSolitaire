#include "mahjongtile.h"

#include "mahjongboardlayoutitem.h"
#include "mahjongsharedresources.h"

#include "mahjongboard.h"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>

// XXX Debug
//#include <Qt3DExtras/QPhongMaterial>

float MahjongTile::s_tileWidth = 0.074f;
float MahjongTile::s_tileHeight = 0.10f;
float MahjongTile::s_tileDepth = 0.03f;

MahjongTile::MahjongTile(MahjongBoard *board)
    : Qt3DCore::QEntity(board)
    , m_board(board)
{
    // MahjongTiles don't have materials because they are
    // rendered (via instancing) by the MahjongBoard entity.
    // Rather MahjongTiles have a position and collider mesh
    // to handle input.

    // Transform
    m_transform = new Qt3DCore::QTransform(this);
    addComponent(m_transform);

    // Mesh
    addComponent(MahjongSharedResources::instance().tileColliderMesh(m_board));

//    // XXX Debug only!
//    auto phongShader = new Qt3DExtras::QPhongMaterial(this);
//    phongShader->setDiffuse(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
//    addComponent(phongShader);

    // Input
    auto objectPicker = new Qt3DRender::QObjectPicker(this);
    objectPicker->setHoverEnabled(false);
    objectPicker->setDragEnabled(false);
    connect(objectPicker, SIGNAL(clicked(Qt3DRender::QPickEvent*)), this, SLOT(processTouched(Qt3DRender::QPickEvent*)));
    addComponent(objectPicker);
}

bool MahjongTile::isSelected() const
{
    return m_selected;
}

QString MahjongTile::faceValue() const
{
    return m_faceValue;
}

QVector3D MahjongTile::translate() const
{
    return m_transform->translation();
}

//QVector3D MahjongTile::globalTranslate() const
//{
//    QVector3D translate = this->translate();
//    auto parentNode = this->parentEntity();
//    while (parentNode) {
//        // Look for translation node
//        for (auto component : parentNode->components()) {
//            auto transformComponent = qobject_cast<Qt3DCore::QTransform*>(component);
//            if (transformComponent) {
//                translate *= transformComponent->translation();
//                break;
//            }
//        }
//        parentNode = parentNode->parentEntity();
//    }
//    return translate;
//}

QVector3D MahjongTile::scale() const
{
    return m_transform->scale3D();
}

//QVector3D MahjongTile::globalScale() const
//{
//    QVector3D scale = this->scale();
//    auto parentNode = this->parentEntity();
//    while (parentNode) {
//        // Look for translation node
//        for (auto component : parentNode->components()) {
//            auto transformComponent = qobject_cast<Qt3DCore::QTransform*>(component);
//            if (transformComponent) {
//                scale *= transformComponent->scale3D();
//                break;
//            }
//        }
//        parentNode = parentNode->parentEntity();
//    }
//    return scale;
//}

MahjongTile::TileFace MahjongTile::face() const
{
    if (faceValue() == QStringLiteral("b1"))
        return TileFace::Bamboo1;
    if (faceValue() == QStringLiteral("b2"))
        return TileFace::Bamboo2;
    if (faceValue() == QStringLiteral("b3"))
        return TileFace::Bamboo3;
    if (faceValue() == QStringLiteral("b4"))
        return TileFace::Bamboo4;
    if (faceValue() == QStringLiteral("b5"))
        return TileFace::Bamboo5;
    if (faceValue() == QStringLiteral("b6"))
        return TileFace::Bamboo6;
    if (faceValue() == QStringLiteral("b7"))
        return TileFace::Bamboo7;
    if (faceValue() == QStringLiteral("b8"))
        return TileFace::Bamboo8;
    if (faceValue() == QStringLiteral("b9"))
        return TileFace::Bamboo9;
    if (faceValue() == QStringLiteral("n1"))
        return TileFace::Character1;
    if (faceValue() == QStringLiteral("n2"))
        return TileFace::Character2;
    if (faceValue() == QStringLiteral("n3"))
        return TileFace::Character3;
    if (faceValue() == QStringLiteral("n4"))
        return TileFace::Character4;
    if (faceValue() == QStringLiteral("n5"))
        return TileFace::Character5;
    if (faceValue() == QStringLiteral("n6"))
        return TileFace::Character6;
    if (faceValue() == QStringLiteral("n7"))
        return TileFace::Character7;
    if (faceValue() == QStringLiteral("n8"))
        return TileFace::Character8;
    if (faceValue() == QStringLiteral("n9"))
        return TileFace::Character9;
    if (faceValue() == QStringLiteral("d1"))
        return TileFace::Coin1;
    if (faceValue() == QStringLiteral("d2"))
        return TileFace::Coin2;
    if (faceValue() == QStringLiteral("d3"))
        return TileFace::Coin3;
    if (faceValue() == QStringLiteral("d4"))
        return TileFace::Coin4;
    if (faceValue() == QStringLiteral("d5"))
        return TileFace::Coin5;
    if (faceValue() == QStringLiteral("d6"))
        return TileFace::Coin6;
    if (faceValue() == QStringLiteral("d7"))
        return TileFace::Coin7;
    if (faceValue() == QStringLiteral("d8"))
        return TileFace::Coin8;
    if (faceValue() == QStringLiteral("d9"))
        return TileFace::Coin9;
    if (faceValue() == QStringLiteral("z1"))
        return TileFace::Dragon1;
    if (faceValue() == QStringLiteral("z2"))
        return TileFace::Dragon2;
    if (faceValue() == QStringLiteral("z3"))
        return TileFace::Dragon3;
    if (faceValue() == QStringLiteral("w1"))
        return TileFace::Wind1;
    if (faceValue() == QStringLiteral("w2"))
        return TileFace::Wind2;
    if (faceValue() == QStringLiteral("w3"))
        return TileFace::Wind3;
    if (faceValue() == QStringLiteral("w4"))
        return TileFace::Wind4;
    if (faceValue() == QStringLiteral("f1"))
        return TileFace::Flower1;
    if (faceValue() == QStringLiteral("f2"))
        return TileFace::Flower2;
    if (faceValue() == QStringLiteral("f3"))
        return TileFace::Flower2;
    if (faceValue() == QStringLiteral("f4"))
        return TileFace::Flower2;
    if (faceValue() == QStringLiteral("s1"))
        return TileFace::Season1;
    if (faceValue() == QStringLiteral("s2"))
        return TileFace::Season2;
    if (faceValue() == QStringLiteral("s3"))
        return TileFace::Season3;
    if (faceValue() == QStringLiteral("s4"))
        return TileFace::Season4;

    return TileFace::Empty;
}

MahjongBoardLayoutItem *MahjongTile::boardPosition() const
{
    return m_boardPosition;
}

void MahjongTile::setBoardPosition(MahjongBoardLayoutItem *position)
{
    m_boardPosition = position;
}

float MahjongTile::tileWidth()
{
    return s_tileWidth;
}

float MahjongTile::tileHeight()
{
    return s_tileHeight;
}

float MahjongTile::tileDepth()
{
    return s_tileDepth;
}

void MahjongTile::setSelected(bool selected)
{
    if (m_selected == selected)
        return;
    m_selected = selected;

    emit selectedChanged(selected);
}

void MahjongTile::setFaceValue(const QString &value)
{
    if (m_faceValue == value)
        return;
    m_faceValue = value;
    emit faceValueChanged(value);
}

void MahjongTile::setTranslate(QVector3D translate)
{
    if (m_transform->translation() == translate)
        return;

    m_transform->setTranslation(translate);
    emit translateChanged(translate);
}

void MahjongTile::setScale(QVector3D scale)
{
    if (m_transform->scale3D() == scale)
        return;

    m_transform->setScale3D(scale);
    emit scaleChanged(scale);
}

void MahjongTile::processTouched(Qt3DRender::QPickEvent *event)
{
    // Inform that the tile has been touched
    m_board->checkTileTouched(this);
    event->setAccepted(true);
}
