#include <component/Renderer.h>

namespace openge {

	void Renderer::AddMesh(Mesh mesh)
	{
		m_meshs.push_back(mesh);
	}

	void Renderer::SetMeshs(std::vector<Mesh> mesh)
	{
		m_meshs = mesh;
	}

	void Renderer::SetMaterial(ref<Material> material)
	{
		m_material = material;
	}

	void Renderer::SetTransform(ref<Transform> transform)
	{
		m_transform = transform;
	}

	void Renderer::SetMainCamera(ref<Camera> camera)
	{
		m_mainCamera = camera;
	}

	std::vector<Mesh> Renderer::GetMeshs()
	{
		return m_meshs;
	}
	ref<Material> Renderer::GetMaterial()
	{
		return m_material;
	}
}
