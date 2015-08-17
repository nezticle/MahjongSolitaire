#include "mahjongtileentity.h"

#include "mahjongboardlayoutitem.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QRotateTransform>
#include <Qt3DCore/QScaleTransform>

#include <Qt3DRenderer/QMesh>
#include <Qt3DRenderer/QTextureImage>
#include <Qt3DRenderer/QDiffuseMapMaterial>

MahjongTileEntity::MahjongTileEntity(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_boardPosition(Q_NULLPTR)
    , m_selected(false)
    , m_visible(false)
{
    //Transform
    Qt3D::QTransform *transformComponent = new Qt3D::QTransform(this);
    m_translate = new Qt3D::QTranslateTransform;
    m_rotationX = new Qt3D::QRotateTransform;
    m_rotationX->setAxis(QVector3D(1.0f, 0.0f, 0.0f));
    m_rotationY = new Qt3D::QRotateTransform;
    m_rotationY->setAxis(QVector3D(0.0f, 1.0f, 1.0f));
    m_rotationZ = new Qt3D::QRotateTransform;
    m_rotationZ->setAxis(QVector3D(0.0f, 0.0f, 1.0f));
    m_scale = new Qt3D::QScaleTransform;
    transformComponent->addTransform(m_translate);
    transformComponent->addTransform(m_rotationX);
    transformComponent->addTransform(m_rotationY);
    transformComponent->addTransform(m_rotationZ);
    transformComponent->addTransform(m_scale);
    addComponent(transformComponent);

    //Mesh
    m_mesh = new Qt3D::QMesh(this);
    m_mesh->setSource(QUrl("qrc:/MahjongTile.obj"));
    addComponent(m_mesh);

    //Material
    Qt3D::QTextureImage *diffuseTexture = new Qt3D::QTextureImage;
    diffuseTexture->setSource(QUrl("qrc:/Tile_diffuse.png"));

    Qt3D::QDiffuseMapMaterial *material = new Qt3D::QDiffuseMapMaterial(this);
    material->diffuse()->addTextureImage(diffuseTexture);
    m_material = material;
    addComponent(m_material);
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

QVector3D MahjongTileEntity::rotation() const
{
    return QVector3D(m_rotationX->angleDeg(), m_rotationY->angleDeg(), m_rotationZ->angleDeg());
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

void MahjongTileEntity::setSelected(bool selected)
{
    if (m_selected == selected)
        return;
    m_selected = selected;
    emit selectedChanged(selected);
}

void MahjongTileEntity::setFaceValue(const QString &value)
{
    if (m_faceValue == value)
        return;
    m_faceValue = value;
    emit faceValueChanged(value);
}

void MahjongTileEntity::setTranslate(QVector3D translate)
{
    if (m_translate->translation() == translate)
        return;

    m_translate->setTranslation(translate);
    emit translateChanged(translate);
}

void MahjongTileEntity::setRotation(QVector3D rotation)
{
    if (QVector3D(m_rotationX->angleDeg(), m_rotationY->angleDeg(), m_rotationZ->angleDeg()) == rotation)
        return;

    m_rotationX->setAngleDeg(rotation.x());
    m_rotationY->setAngleDeg(rotation.y());
    m_rotationZ->setAngleDeg(rotation.z());
    emit rotationChanged(rotation);
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
