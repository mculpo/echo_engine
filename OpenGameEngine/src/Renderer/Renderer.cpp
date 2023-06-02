#include "Renderer.h"

namespace openge {
	void Renderer::setup()
	{
		m_mesh->setup();
		m_material->setup();
	}

	void Renderer::bind()
	{
		m_material->bind();
		std::shared_ptr<Camera> camera = gameObjectFindByTag<GameObject>("MainCamera")->getComponent<Camera>();
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();
		m_material->getShader()->setUniformMatrix4fv("view", view);
		m_material->getShader()->setUniformMatrix4fv("projection", projection);
		m_mesh->useVAO();
	}

	void Renderer::render()
	{
		glm::mat4 model = getEntity()->getComponent<Transform>()->getModelMatrix();
		m_material->getShader()->setUniformMatrix4fv("model", model);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void Renderer::setMaterial(std::shared_ptr<Material> material)
	{
		m_material = material;
	}

	void Renderer::setMesh(std::shared_ptr<Mesh> mesh)
	{
		m_mesh = mesh;
	}
}
