#include <component/RendererCube.h>
namespace openge {
    void RendererCube::Bind()
    {
        Matrix4 view = m_mainCamera->getViewMatrix();
        Matrix4 projection = m_mainCamera->getProjectionMatrix();
        Matrix4 model = m_transform->getModelMatrix();

        m_material->getShader()->setUniformMatrix4fv("view", view);
        m_material->getShader()->setUniformMatrix4fv("projection", projection);
        m_material->getShader()->setUniformMatrix4fv("model", model);
    }
    void RendererCube::Render()
    {
        for (const auto& mesh: m_meshs) {
            mesh.bindTexture(m_material);
            mesh.useVAO();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}
