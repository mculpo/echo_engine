#include "Renderer.h"

namespace openge {

	void Renderer::addMesh(ref<Mesh> mesh)
	{
		m_meshs.push_back(mesh);
	}

	void Renderer::setMeshs(std::vector<ref<Mesh>> mesh)
	{
		m_meshs = mesh;
	}

	void Renderer::setMaterial(ref<Material> material)
	{
		m_material = material;
	}

	void Renderer::setTransform(ref<Transform> transform)
	{
		m_transform = transform;
	}

	void Renderer::setMainCamera(ref<Camera> camera)
	{
		m_mainCamera = camera;
	}

	std::vector<ref<Mesh>> Renderer::getMeshs()
	{
		return m_meshs;
	}
	ref<Material> Renderer::getMaterial()
	{
		return m_material;
	}
}