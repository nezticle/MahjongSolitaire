#include "mahjongtileentity.h"

#include "mahjongboardlayoutitem.h"
#include "mahjongsharedresources.h"

#include <Qt3DCore/QTransform>

#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QDiffuseMapMaterial>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
//#include <Qt3DRender/QBoundingVolumeDebug>

class MahjongTilefaceEntity : public Qt3DCore::QEntity
{
public:
    MahjongTilefaceEntity(MahjongTileEntity *parent)
        : Qt3DCore::QEntity(parent)
        , m_material(Q_NULLPTR)
    {
        //Transform
        Qt3DCore::QTransform *transform = new Qt3DCore::QTransform(this);
        transform->setTranslation(QVector3D(0.0f, 0.0f, MahjongTileEntity::tileDepth() * 0.5f + 0.0001f));
        addComponent(transform);

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
    m_transform = new Qt3DCore::QTransform(this);
    addComponent(m_transform);

    //Mesh
    addComponent(MahjongSharedResources::instance().tileMesh());

    //Material
    addComponent(MahjongSharedResources::instance().tileMaterial());

    //Input
    Qt3DRender::QObjectPicker *objectPicker = new Qt3DRender::QObjectPicker(this);
    objectPicker->setHoverEnabled(false);
    connect(objectPicker, SIGNAL(clicked(Qt3DRender::QPickEvent*)), this, SLOT(processTouched(Qt3DRender::QPickEvent*)));
    addComponent(objectPicker);

//    Qt3DRender::QBoundingVolumeDebug *bvDebug = new Qt3DRender::QBoundingVolumeDebug(this);
//    bvDebug->setRecursive(false);
//    addComponent(bvDebug);

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
    return m_transform->translation();
}

QVector3D MahjongTileEntity::scale() const
{
    return m_transform->scale3D();
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
    if (m_transform->translation() == translate)
        return;

    m_transform->setTranslation(translate);
    emit translateChanged(translate);
}

void MahjongTileEntity::setScale(QVector3D scale)
{
    if (m_transform->scale3D() == scale)
        return;

    m_transform->setScale3D(scale);
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

void MahjongTileEntity::processTouched(Qt3DRender::QPickEvent *event)
{
    //Ignore pick events if the entity is disabled
    if (!isEnabled()) {
        event->setAccepted(false);
        return;
    }

    //inform that the tile has been touched
    qDebug() << "tile touched";
    event->setAccepted(true);
}
