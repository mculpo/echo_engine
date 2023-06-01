#include "MeshRenderer.h"

namespace openge {
	void MeshRenderer::setup()
	{
		m_mesh->setup();
		m_material->setup();
	}

	void MeshRenderer::bind()
	{
		m_material->bind();
		std::shared_ptr<Camera> camera = gameObjectFindByTag<GameObject>("MainCamera")->getComponent<Camera>();
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		m_material->getShader()->setUniformMatrix4fv("view", view);
		m_material->getShader()->setUniformMatrix4fv("projection", projection);
		m_mesh->useVAO();
	}

	void MeshRenderer::render()
	{
		glm::mat4 model = getEntity()->getComponent<Transform>()->getModelMatrix();
		m_material->getShader()->setUniformMatrix4fv("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void MeshRenderer::setMaterial(std::shared_ptr<Material> material)
	{
		m_material = material;
	}

	void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
	{
		m_mesh = mesh;
	}
}
