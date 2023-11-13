#include <component/RendererCube.h>
namespace openge {
    void RendererCube::Bind()
    {
        Matrix4 model = m_transform->getModelMatrix();
        m_material->getShader()->setUniformMatrix4fv("model", model);
    }

    void RendererCube::Render()
    {
        if (m_material->GetInstanced()) {
            for (const auto& mesh : m_meshs) {
                mesh->bindTexture(m_material);
                mesh->useVAO();
                glDrawArraysInstanced(GL_TRIANGLES, 0, 36, m_material->GetAmountInstancedObject());
            }
        }
        else {
            for (const auto& mesh : m_meshs) {
                mesh->bindTexture(m_material);
                mesh->useVAO();
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}
