#include <base/Skybox.h>
namespace openge {

	Skybox::Skybox(ref<Material> material, std::vector<String> pathTexture, ref<Camera> mainCamera) 
		: m_material(material), m_path_textures(pathTexture), m_mainCamera(mainCamera)
	{
		Setup();
	}
	Skybox::~Skybox()
	{
	}
	void Skybox::Setup()
	{
		std::vector<Vector3> vertex = ShapeVerticesManager::getInstance().getSkyboxVertices();
		setVAO(createRef<VertexArrayObject>());
		setVBO(createRef<VertexBufferObject>(vertex.data(), vertex.size() * sizeof(Vertex), GL_STATIC_DRAW));
		m_vao->AddLayout(3, VP_FLOAT);
		m_vao->runLayout();

		m_textureCubeMap = createRef<TextureCubeMap>(m_path_textures);
	}
	void Skybox::Draw()
	{
		m_material->getShader()->Bind();
		glDepthFunc(GL_LEQUAL);// change depth function so depth test passes when values are equal to depth buffer's content

		// skybox-cube
		m_vao->Bind(); 
		BindTexture();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		m_vao->Unbind();
		glDepthFunc(GL_LESS); // set depth function back to default

	}
	void Skybox::Bind()
	{
		m_vao->Bind();
	}
	void Skybox::BindTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureCubeMap->GetId());
	}
	void Skybox::Unbind()
	{
		m_vao->Unbind();
	}
	void Skybox::setVAO(ref<VertexArrayObject> vao)
	{
		m_vao = std::move(vao);
	}
	void Skybox::setVBO(ref<VertexBufferObject> vbo)
	{
		m_vbo = std::move(vbo);
	}
	void Skybox::setMaterial(ref<Material> material)
	{
		m_material = material;
	}
	void Skybox::setMainCamera(ref<Camera> camera)
	{
		m_mainCamera = camera;
	}
}