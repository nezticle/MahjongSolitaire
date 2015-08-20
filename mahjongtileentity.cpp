#include "mahjongtileentity.h"

#include "mahjongboardlayoutitem.h"
#include "mahjongsharedresources.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QScaleTransform>

#include <Qt3DRenderer/QMesh>
#include <Qt3DRenderer/QTextureImage>
#include <Qt3DRenderer/QDiffuseMapMaterial>

#include <Qt3DCollision/QBoxCollider>

class MahjongTilefaceEntity : public Qt3D::QEntity
{
public:
    MahjongTilefaceEntity(MahjongTileEntity *parent)
        : Qt3D::QEntity(parent)
        , m_material(Q_NULLPTR)
    {
        //Transform
        Qt3D::QTransform *transformComponent = new Qt3D::QTransform(this);
        Qt3D::QTranslateTransform *translate = new Qt3D::QTranslateTransform;
        transformComponent->addTransform(translate);
        translate->setDz(MahjongTileEntity::tileDepth() * 0.5 + 0.0001f);
        addComponent(transformComponent);

        //Mesh
        addComponent(MahjongSharedResources::instance().tilefaceMesh());
    }

    void setTileFace(const QString &tileface) {
        if (m_material != Q_NULLPTR) {
            removeComponent(m_material);
        }

        m_material = MahjongSharedResources::instance().materialForTileface(tileface);
        addComponent(m_material);
    }

private:
    Qt3D::QMaterial *m_material;
};


float MahjongTileEntity::s_tileWidth = 0.074f;
float MahjongTileEntity::s_tileHeight = 0.10f;
float MahjongTileEntity::s_tileDepth = 0.03f;

MahjongTileEntity::MahjongTileEntity(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_boardPosition(Q_NULLPTR)
    , m_selected(false)
    , m_visible(false)
    , m_tileFace(new MahjongTilefaceEntity(this))
{
    //Transform
    Qt3D::QTransform *transformComponent = new Qt3D::QTransform(this);
    m_translate = new Qt3D::QTranslateTransform;
    m_scale = new Qt3D::QScaleTransform;
    transformComponent->addTransform(m_translate);
    transformComponent->addTransform(m_scale);
    addComponent(transformComponent);

    //Mesh
    addComponent(MahjongSharedResources::instance().tileMesh());

    //Material
    addComponent(MahjongSharedResources::instance().tileMaterial());

    //Collider
    Qt3D::QBoxCollider *boxCollider = new Qt3D::QBoxCollider;
    boxCollider->setRadii(QVector3D(s_tileWidth / 2.0f,
                                    s_tileHeight / 2.0f,
                                    s_tileDepth / 2.0f));
    addComponent(boxCollider);
}

bool MahjongTileEntity::isSelected() const
{
    return m_selected;
}

QString MahjongTileEntity::faceValue() const
{
    return m_faceValue;
}

QVector3D MahjongTileEntity::translate() const
{
    return m_translate->translation();
}

QVector3D MahjongTileEntity::scale() const
{
    return m_scale->scale3D();
}

MahjongBoardLayoutItem *MahjongTileEntity::boardPosition() const
{
    return m_boardPosition;
}

void MahjongTileEntity::setBoardPosition(MahjongBoardLayoutItem *position)
{
    m_boardPosition = position;
}

bool MahjongTileEntity::visible() const
{
    return m_visible;
}

float MahjongTileEntity::tileWidth()
{
    return s_tileWidth;
}

float MahjongTileEntity::tileHeight()
{
    return s_tileHeight;
}

float MahjongTileEntity::tileDepth()
{
    return s_tileDepth;
}

void MahjongTileEntity::setSelected(bool selected)
{
    if (m_selected == selected)
        return;
    m_selected = selected;

    //Set correct material
    if (selected) {
        removeComponent(MahjongSharedResources::instance().tileMaterial());
        addComponent(MahjongSharedResources::instance().tileSelectedMaterial());
    } else {
        removeComponent(MahjongSharedResources::instance().tileSelectedMaterial());
        addComponent(MahjongSharedResources::instance().tileMaterial());
    }

    emit selectedChanged(selected);
}

void MahjongTileEntity::setFaceValue(const QString &value)
{
    if (m_faceValue == value)
        return;
    m_faceValue = value;
    m_tileFace->setTileFace(value);
    emit faceValueChanged(value);
}

void MahjongTileEntity::setTranslate(QVector3D translate)
{
    if (m_translate->translation() == translate)
        return;

    m_translate->setTranslation(translate);
    emit translateChanged(translate);
}

void MahjongTileEntity::setScale(QVector3D scale)
{
    if (m_scale->scale3D() == scale)
        return;

    m_scale->setScale3D(scale);
    emit scaleChanged(scale);
}

void MahjongTileEntity::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    emit visibleChanged(visible);
}
