#ifndef DIFFUSEALPHAMATERIAL_H
#define DIFFUSEALPHAMATERIAL_H

#include <QtGui/QColor>

#include <Qt3DRenderer/QMaterial>

namespace Qt3D {
    class QEffect;
    class QTechnique;
    class QParameter;
    class QShaderProgram;
    class QRenderPass;
    class QParameterMapping;
}

class DiffuseAlphaMaterial : public Qt3D::QMaterial
{
    Q_OBJECT
    Q_PROPERTY(QColor diffuse READ diffuse WRITE setDiffuse NOTIFY diffuseChanged)

public:
    DiffuseAlphaMaterial(QNode *parent = 0);
    QColor diffuse() const;
public slots:
    void setDiffuse(QColor diffuse);
signals:
    void diffuseChanged(QColor diffuse);
private:
    QColor m_diffuse;

    Qt3D::QEffect *m_diffuseAlphaEffect;
    Qt3D::QParameter *m_diffuseParameter;
    Qt3D::QParameter *m_lightPositionParameter;
    Qt3D::QParameter *m_lightIntensityParameter;
    Qt3D::QTechnique *m_diffuseAlphaGL3Technique;
    Qt3D::QTechnique *m_diffuseAlphaGL2Technique;
    Qt3D::QTechnique *m_diffuseAlphaES2Technique;
    Qt3D::QRenderPass *m_diffuseAlphaGL3RenderPass;
    Qt3D::QRenderPass *m_diffuseAlphaGL2RenderPass;
    Qt3D::QRenderPass *m_diffuseAlphaES2RenderPass;
    Qt3D::QShaderProgram *m_diffuseAlphaGL3Shader;
    Qt3D::QShaderProgram *m_diffuseAlphaGL2ES2Shader;
};

#endif // DIFFUSEALPHAMATERIAL_H
