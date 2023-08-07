#ifndef __MODEL_H__
#define __MODEL_H__
#include <core/core.h>

#include <base/Texture.h>
#include <base/Mesh.h>

namespace openge {
	class Model
	{
	public:
		std::vector<Mesh> m_meshs;
		String m_directory;

		Model(String const& path);
	private:
		void loadModel(String const& path);

        void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<unsigned int> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName, String stringName);
	};
}
#endif // !__MODEL_H__


