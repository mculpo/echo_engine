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
		ref<Camera> camera = gameObjectFindByTag<GameObject>("MainCamera")->getComponent<Camera>();
		Matrix4 view = camera->getViewMatrix();
		Matrix4 projection = camera->getProjectionMatrix();
		m_material->getShader()->setUniformMatrix4fv("view", view);
		m_material->getShader()->setUniformMatrix4fv("projection", projection);
		m_mesh->useVAO();
	}

	void Renderer::render()
	{
		ref<Transform> transform = getEntity()->getComponent<Transform>();
		Matrix4 model = transform->getModelMatrix();
		Matrix3 transpose = transform->getTransposeMatrix();
		m_material->getShader()->setUniformMatrix4fv("model", model);
		m_material->getShader()->setUniformMatrix3fv("modelTranspose", transpose);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void Renderer::setMaterial(ref<Material> material)
	{
		m_material = material;
	}

	void Renderer::setMesh(ref<Mesh> mesh)
	{
		m_mesh = mesh;
	}
	ref<Material> Renderer::getMaterial()
	{
		return m_material;
	}
	ref<Mesh> Renderer::getMesh()
	{
		return m_mesh;
	}
}
