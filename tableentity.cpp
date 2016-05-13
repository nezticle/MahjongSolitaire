#include "tableentity.h"

#include <Qt3DCore/QTransform>

#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPlaneMesh>

TableEntity::TableEntity(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
{
    // Mesh
    Qt3DExtras::QPlaneMesh *mesh = new Qt3DExtras::QPlaneMesh(this);
    mesh->setHeight(1.0f);
    mesh->setWidth(1.0f);
    mesh->setMeshResolution(QSize(2, 2));

    addComponent(mesh);

    // Material
    Qt3DExtras::QPhongMaterial *phongMaterial = new Qt3DExtras::QPhongMaterial(this);
    phongMaterial->setDiffuse(QColor(70, 150, 56));
    phongMaterial->setShininess(10.f);
    addComponent(phongMaterial);

    // Transform
    m_transform = new Qt3DCore::QTransform(this);

    // Transform the mesh to be XxY instead of XxZ
    m_transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 90.0f));

    addComponent(m_transform);
}

float TableEntity::x() const
{
    return m_transform->translation().x();
}

float TableEntity::y() const
{
    return m_transform->translation().y();
}

float TableEntity::z() const
{
    return m_transform->translation().z();
}

float TableEntity::rotationX() const
{
    return m_transform->rotation().toEulerAngles().x();
}

float TableEntity::rotationY() const
{
    return m_transform->rotation().toEulerAngles().y();
}

float TableEntity::rotationZ() const
{
    return m_transform->rotation().toEulerAngles().z();
}

float TableEntity::scale() const
{
    return m_transform->scale();
}

void TableEntity::setX(float x)
{
    if (m_transform->translation().x() == x)
        return;

    QVector3D translation = m_transform->translation();
    translation.setX(x);

    m_transform->setTranslation(translation);
    emit xChanged(x);
}

void TableEntity::setY(float y)
{
    if (m_transform->translation().y() == y)
        return;

    QVector3D translation = m_transform->translation();
    translation.setY(y);

    m_transform->setTranslation(translation);
    emit yChanged(y);
}

void TableEntity::setZ(float z)
{
    if (m_transform->translation().z() == z)
        return;

    QVector3D translation = m_transform->translation();
    translation.setZ(z);

    m_transform->setTranslation(translation);
    emit zChanged(z);
}

void TableEntity::setRotationX(float rotationX)
{
    if (m_transform->rotation().toEulerAngles().x() == rotationX)
        return;

    QVector3D eulerAngles = m_transform->rotation().toEulerAngles();
    eulerAngles.setX(rotationX);

    m_transform->setRotation(QQuaternion::fromEulerAngles(eulerAngles));
    emit rotationXChanged(rotationX);
}

void TableEntity::setRotationY(float rotationY)
{
    if (m_transform->rotation().toEulerAngles().y() == rotationY)
        return;

    QVector3D eulerAngles = m_transform->rotation().toEulerAngles();
    eulerAngles.setY(rotationY);

    m_transform->setRotation(QQuaternion::fromEulerAngles(eulerAngles));
    emit rotationYChanged(rotationY);
}

void TableEntity::setRotationZ(float rotationZ)
{
    if (m_transform->rotation().toEulerAngles().z() == rotationZ)
        return;

    QVector3D eulerAngles = m_transform->rotation().toEulerAngles();
    eulerAngles.setZ(rotationZ);

    m_transform->setRotation(QQuaternion::fromEulerAngles(eulerAngles));
    emit rotationZChanged(rotationZ);
}

void TableEntity::setScale(float scale)
{
    if (m_transform->scale() == scale)
        return;

    m_transform->setScale(scale);
    emit scaleChanged(scale);
}
