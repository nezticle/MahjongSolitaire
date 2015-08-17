#include "mahjongboardarea.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>

#include <Qt3DRenderer/QCuboidMesh>

#include "diffusealphamaterial.h"

MahjongBoardArea::MahjongBoardArea(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_size(1.0f, 1.0f, 1.0f)
{
    //Translation
    Qt3D::QTransform *transformComponent = new Qt3D::QTransform(this);
    m_translation = new Qt3D::QTranslateTransform;
    transformComponent->addTransform(m_translation);
    addComponent(transformComponent);

    //Adjust the transform to be half the heith of the bounding box
    m_translation->setDz((m_size.z() / 2.0));

    //Debug Bounding Box Mesh
    m_mesh = new Qt3D::QCuboidMesh(this);
    m_mesh->setXExtent(m_size.x());
    m_mesh->setYExtent(m_size.y());
    m_mesh->setZExtent(m_size.z());
    addComponent(m_mesh);

    //Debug Bounding Box Material (wireframe)
    DiffuseAlphaMaterial *material = new DiffuseAlphaMaterial(this);
    material->setDiffuse(QColor(255, 0, 0, 50));
    addComponent(material);
}

QVector3D MahjongBoardArea::baseCenter() const
{
    return m_baseCenter;
}

QVector3D MahjongBoardArea::size() const
{
    return m_size;
}

void MahjongBoardArea::setBaseCenter(QVector3D baseCenter)
{
    if (m_baseCenter == baseCenter)
        return;

    m_baseCenter = baseCenter;
    emit baseCenterChanged(baseCenter);
}

void MahjongBoardArea::setSize(QVector3D size)
{
    if (m_size == size)
        return;

    m_size = size;
    m_translation->setDz((m_size.z() / 2.0));
    m_mesh->setXExtent(m_size.x());
    m_mesh->setYExtent(m_size.y());
    m_mesh->setZExtent(m_size.z());
    emit sizeChanged(size);
}

