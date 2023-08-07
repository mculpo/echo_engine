#include <component/RendererModelMesh.h>
namespace openge {
    void RendererModelMesh::bind()
    {
        Matrix4 view = m_mainCamera->getViewMatrix();
        Matrix4 projection = m_mainCamera->getProjectionMatrix();
        Matrix4 model = m_transform->getModelMatrix();

        m_material->getShader()->setUniformMatrix4fv("view", view);
        m_material->getShader()->setUniformMatrix4fv("projection", projection);
        m_material->getShader()->setUniformMatrix4fv("model", model);
    }

    void RendererModelMesh::render()
    {
        for (const auto& mesh : m_meshs) {
            mesh.bindTexture(m_material);
            mesh.useVAO();
            glDrawElements(
                GL_TRIANGLES,
                static_cast<unsigned int>(mesh.GetIndices().size()),
                GL_UNSIGNED_INT,
                0
            );
            mesh.unbindVAO();
            glActiveTexture(GL_TEXTURE0);
        }
    }
}
