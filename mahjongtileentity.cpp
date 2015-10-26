#include "mahjongtileentity.h"

#include "mahjongboardlayoutitem.h"
#include "mahjongsharedresources.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QScaleTransform>

#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QDiffuseMapMaterial>

class MahjongTilefaceEntity : public Qt3DCore::QEntity
{
public:
    MahjongTilefaceEntity(MahjongTileEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_material(Q_NULLPTR)
    {
        //Transform
        Qt3DCore::QTransform *transformComponent = new Qt3DCore::QTransform(this);
        Qt3DCore::QTranslateTransform *translate = new Qt3DCore::QTranslateTransform;
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
    Qt3DRender::QMaterial *m_material;
};


float MahjongTileEntity::s_tileWidth = 0.074f;
float MahjongTileEntity::s_tileHeight = 0.10f;
float MahjongTileEntity::s_tileDepth = 0.03f;

MahjongTileEntity::MahjongTileEntity(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_boardPosition(Q_NULLPTR)
    , m_selected(false)
    , m_visible(false)
    , m_tileFace(new MahjongTilefaceEntity(this))
{
    //Transform
    Qt3DCore::QTransform *transformComponent = new Qt3DCore::QTransform(this);
    m_translate = new Qt3DCore::QTranslateTransform;
    m_scale = new Qt3DCore::QScaleTransform;
    transformComponent->addTransform(m_translate);
    transformComponent->addTransform(m_scale);
    addComponent(transformComponent);

    //Mesh
    addComponent(MahjongSharedResources::instance().tileMesh());

    //Material
    addComponent(MahjongSharedResources::instance().tileMaterial());

    setEnabled(false);
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
    setEnabled(m_visible);

    emit visibleChanged(visible);
}
