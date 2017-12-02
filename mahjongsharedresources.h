#ifndef MAHJONGSHAREDRESOURCES_H
#define MAHJONGSHAREDRESOURCES_H

#include <QtCore/QObject>
#include <QtCore/QMap>

namespace Qt3DCore {
    class QEntity;
}

namespace Qt3DRender {
    class QMaterial;
    class QMesh;
    class QAttribute;
}

class MahjongSharedResources
{
public:
    static MahjongSharedResources &instance();
    Qt3DRender::QMesh *tileColliderMesh(Qt3DCore::QEntity *parent);
    Qt3DRender::QMaterial *debugMaterial(Qt3DCore::QEntity *parent);
private:
    MahjongSharedResources();
    ~MahjongSharedResources();
    MahjongSharedResources(MahjongSharedResources const&);
    void operator =(MahjongSharedResources const&);

    void initSharedResources();

private:
    Qt3DCore::QEntity *m_dummyParent = nullptr;
    Qt3DRender::QMesh *m_tileColliderMesh = nullptr;
    Qt3DRender::QMaterial *m_debugMaterial = nullptr;

};



#endif // MAHJONGSHAREDRESOURCES_H
