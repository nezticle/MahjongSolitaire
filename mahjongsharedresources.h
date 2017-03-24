#ifndef MAHJONGSHAREDRESOURCES_H
#define MAHJONGSHAREDRESOURCES_H

#include <QtCore/QObject>
#include <QtCore/QMap>

#include "util/textureatlas.h"

namespace Qt3DRender {
    class QMaterial;
    class QMesh;
    class QAttribute;
}

class MahjongSharedResources
{
public:
    static MahjongSharedResources &instance();

    Qt3DRender::QMaterial *materialForTileface(const QString &tileface);
    Qt3DRender::QMaterial *tileMaterial();
    Qt3DRender::QMaterial *tileSelectedMaterial();
    Qt3DRender::QMesh *tileMesh();
    Qt3DRender::QMesh *tilefaceMesh();

private:
    MahjongSharedResources();
    MahjongSharedResources(MahjongSharedResources const&);
    void operator =(MahjongSharedResources const&);

    void initSharedResources();
    Qt3DRender::QMaterial *generateMaterial(const QString &textureName);
    void addImageToAtlas(const QString &filename, const QString &id);

    QMap<QString,Qt3DRender::QMaterial*> m_tileFaceMaterials;
    Qt3DRender::QMaterial *m_tileMaterial;
    Qt3DRender::QMaterial *m_tileSelectedMaterial;
    Qt3DRender::QMesh *m_tileMesh;
    Qt3DRender::QMesh *m_tilefaceMesh;
    TextureAtlas *m_textureAtlas;
    QHash<QString, TextureAtlas::TextureId> m_texturesIds;

};

#endif // MAHJONGSHAREDRESOURCES_H
