#include <base/Skybox.h>
namespace openge {
	Skybox::Skybox(ref<Material> material) 
		: m_material (material)
	{
		std::vector<Vector3> vertex = ShapeVerticesManager::getInstance().getSkyboxVertices();
		m_VAO = (createRef<VertexArrayObject>());
		m_VBO = (createRef<VertexBufferObject>(vertex.data(), vertex.size() * sizeof(Vertex), GL_STATIC_DRAW));
		m_VAO->AddLayout(3, VP_FLOAT); // aPos
		m_VAO->runLayout();
	}
	Skybox::~Skybox()
	{
	}
	void Skybox::setTextureCubeMap(ref<TextureCubeMap> textureCubeMap)
	{
		m_textureCubeMap = textureCubeMap;
	}
	void Skybox::Draw()
	{
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		m_material->getShader()->Bind();
		// skybox cube
		m_VAO->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureCubeMap->GetId());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		m_VAO->Unbind();
		glDepthFunc(GL_LESS); // set depth function back to default
	}
}
