#include "MeshRenderer.h"
#include <ecs/components/Transform.h>
#include <ecs/components/Camera.h>
#include <ecs/entity/GameObject.h>

openge::MeshRenderer::MeshRenderer() : Component()
{
}

openge::MeshRenderer::MeshRenderer(Entity* entity) : Component(entity, 0)
{
}

openge::MeshRenderer::MeshRenderer(Entity* entity, Material* material, Mesh* mesh)
	:Component(entity, 0), m_material(material), m_mesh(mesh)
{
}


openge::MeshRenderer::~MeshRenderer()
{
}

void openge::MeshRenderer::setup()
{
	m_mesh->setup();
	m_material->setup();
}

void openge::MeshRenderer::bind()
{
	m_material->bind();
	std::shared_ptr<Camera> camera = gameObjectFindByTag<GameObject>("MainCamera")->getComponent<Camera>();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = camera->getProjectionMatrix();
	m_material->getShader()->setUniformMatrix4fv("view", view);
	m_material->getShader()->setUniformMatrix4fv("projection", projection);
	//m_mesh->useVAO();
}

void openge::MeshRenderer::render()
{
	glm::mat4 model = getEntity()->getComponent<Transform>()->getModelMatrix();
	m_material->getShader()->setUniformMatrix4fv("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

std::shared_ptr<openge::Material> openge::MeshRenderer::setMaterial(std::shared_ptr<Material> material)
{
	return m_material = std::move(material);
}

void openge::MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = std::move(mesh);
}
