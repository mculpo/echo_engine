#ifndef __RENDERERMODELMESH_H__
#define __RENDERERMODELMESH_H__
#include <Core/tspch.h>
#include <Component/Mesh.h>
#include <Component/Material.h>
#include <Component/Renderer.h>

namespace openge {
	class RendererModelMesh : public Renderer
	{
	public:
		void bind() override;
		void render() override;
	};
}

#endif // !__RENDERERMODELMESH_H__

