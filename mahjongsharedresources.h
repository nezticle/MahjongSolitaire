#ifndef MAHJONGSHAREDRESOURCES_H
#define MAHJONGSHAREDRESOURCES_H

#include <QtCore/QObject>
#include <QtCore/QMap>

namespace Qt3D {
    class QMaterial;
    class QMesh;
}

class MahjongSharedResources
{
public:
    static MahjongSharedResources &instance();

    Qt3D::QMaterial *materialForTileface(const QString &tileface);
    Qt3D::QMaterial *tileMaterial();
    Qt3D::QMaterial *tileSelectedMaterial();
    Qt3D::QMesh *tileMesh();
    Qt3D::QMesh *tilefaceMesh();

private:
    MahjongSharedResources();
    MahjongSharedResources(MahjongSharedResources const&);
    void operator =(MahjongSharedResources const&);

    void initSharedResources();
    Qt3D::QMaterial *generateMaterial(const QString &textureName);

    QMap<QString,Qt3D::QMaterial*> m_tileFaceMaterials;
    Qt3D::QMaterial *m_tileMaterial;
    Qt3D::QMaterial *m_tileSelectedMaterial;
    Qt3D::QMesh *m_tileMesh;
    Qt3D::QMesh *m_tilefaceMesh;

};

#endif // MAHJONGSHAREDRESOURCES_H
