#include "RendererPrimitiveMesh.h"
namespace openge {
    void RendererPrimitiveMesh::bind()
    {
        ref<Camera> camera = gameObjectFindByTag<GameObject>("MainCamera")->getComponent<Camera>();
        Matrix4 view = camera->getViewMatrix();
        Matrix4 projection = camera->getProjectionMatrix();
        ref<Transform> transform = getEntity()->getComponent<Transform>();
        Matrix4 model = transform->getModelMatrix();

        m_material->getShader()->setUniformMatrix4fv("view", view);
        m_material->getShader()->setUniformMatrix4fv("projection", projection);
        m_material->getShader()->setUniformMatrix4fv("model", model);
    }
    void RendererPrimitiveMesh::render()
    {
        for (const auto& mesh: m_meshs) {
            mesh->bindTexture(m_material);
            mesh->useVAO();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}
