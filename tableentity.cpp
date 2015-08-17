#include "tableentity.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QRotateTransform>
#include <Qt3dCore/QScaleTransform>

#include <Qt3DRenderer/QDiffuseSpecularMapMaterial>
#include <Qt3DRenderer/QTextureImage>
#include <Qt3DRenderer/QAbstractTextureProvider>
#include <Qt3DRenderer/QMesh>

TableEntity::TableEntity(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
{
    //Mesh
    m_mesh = new Qt3D::QMesh(this);
    m_mesh->setSource(QUrl("qrc:/XYPlane.obj"));
    addComponent(m_mesh);

    //Material
    Qt3D::QTextureImage *diffuseTexture = new Qt3D::QTextureImage;
    diffuseTexture->setSource(QUrl("qrc:/wicker_diffuse.png"));
    Qt3D::QTextureImage *specularTexture = new Qt3D::QTextureImage;
    specularTexture->setSource(QUrl("qrc:/wicker_specular.png"));

    Qt3D::QDiffuseSpecularMapMaterial *material = new Qt3D::QDiffuseSpecularMapMaterial(this);
    material->diffuse()->addTextureImage(diffuseTexture);
    material->diffuse()->setGenerateMipMaps(false);
    material->diffuse()->setMagnificationFilter(Qt3D::QAbstractTextureProvider::Linear);
    material->specular()->addTextureImage(specularTexture);
    material->specular()->setGenerateMipMaps(false);
    material->specular()->setMagnificationFilter(Qt3D::QAbstractTextureProvider::Linear);
    material->setShininess(0.5f);
    addComponent(material);

    //Transform
    Qt3D::QTransform *transform = new Qt3D::QTransform(this);
    m_translate = new Qt3D::QTranslateTransform;
    transform->addTransform(m_translate);
    m_rotationX = new Qt3D::QRotateTransform;
    m_rotationX->setAxis(QVector3D(1.0f, 0.0f, 0.0f));
    transform->addTransform(m_rotationX);
    m_rotationY = new Qt3D::QRotateTransform;
    m_rotationY->setAxis(QVector3D(0.0f, 1.0f, 0.0f));
    transform->addTransform(m_rotationY);
    m_rotationZ = new Qt3D::QRotateTransform;
    m_rotationZ->setAxis(QVector3D(0.0f, 0.0f, 1.0f));
    transform->addTransform(m_rotationZ);
    m_scale = new Qt3D::QScaleTransform;
    transform->addTransform(m_scale);
    addComponent(transform);
}

float TableEntity::x() const
{
    return m_translate->dx();
}

float TableEntity::y() const
{
    return m_translate->dy();
}

float TableEntity::z() const
{
    return m_translate->dz();
}

float TableEntity::rotationX() const
{
    return m_rotationX->angleDeg();
}

float TableEntity::rotationY() const
{
    return m_rotationY->angleDeg();
}

float TableEntity::rotationZ() const
{
    return m_rotationZ->angleDeg();
}

float TableEntity::scale() const
{
    return m_scale->scale();
}

void TableEntity::setX(float x)
{
    if (m_translate->dx() == x)
        return;

    m_translate->setDx(x);
    emit xChanged(x);
}

void TableEntity::setY(float y)
{
    if (m_translate->dy() == y)
        return;

    m_translate->setDy(y);
    emit yChanged(y);
}

void TableEntity::setZ(float z)
{
    if (m_translate->dz() == z)
        return;

    m_translate->setDz(z);
    emit zChanged(z);
}

void TableEntity::setRotationX(float rotationX)
{
    if (m_rotationX->angleDeg() == rotationX)
        return;

    m_rotationX->setAngleDeg(rotationX);
    emit rotationXChanged(rotationX);
}

void TableEntity::setRotationY(float rotationY)
{
    if (m_rotationY->angleDeg() == rotationY)
        return;

    m_rotationY->setAngleDeg(rotationY);
    emit rotationYChanged(rotationY);
}

void TableEntity::setRotationZ(float rotationZ)
{
    if (m_rotationZ->angleDeg() == rotationZ)
        return;

    m_rotationZ->setAngleDeg(rotationZ);
    emit rotationZChanged(rotationZ);
}

void TableEntity::setScale(float scale)
{
    if (m_scale->scale() == scale)
        return;

    m_scale->setScale(scale);

    emit scaleChanged(scale);
}
