#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#include <core/core.h>

#include <gl/VertexBufferObject.h>
#include <gl/VertexArrayObject.h>

#include <base/TextureCubeMap.h>
#include <base/Material.h>

#include <manager/ShapeVerticesManager.h>

namespace openge {
	class Skybox
	{
	public:
		Skybox(ref<Material> material);
		~Skybox();
		void setTextureCubeMap(ref<TextureCubeMap> textureCubeMap);
		void Draw();
	private:
		ref<VertexArrayObject> m_VAO;
		ref<VertexBufferObject> m_VBO;
		ref<TextureCubeMap> m_textureCubeMap;
		ref<Material> m_material;
	};
}
#endif // !__SKYBOX_H__



