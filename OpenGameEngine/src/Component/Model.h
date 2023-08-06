#ifndef __MODEL_H__
#define __MODEL_H__
#include <Core/tspch.h>
#include <Component/Material.h>
#include <Component/Mesh.h>
namespace openge {
	class Model
	{
	public:
		std::vector<Texture> m_textures_loaded;
		std::vector<Mesh> m_meshs;
		String m_directory;

		Model(String const& path);
	private:
		void loadModel(String const& path);

        void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName, String stringName);
	};
}
#endif // !__MODEL_H__


