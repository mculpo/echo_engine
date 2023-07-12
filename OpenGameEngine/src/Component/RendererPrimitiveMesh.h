#ifndef __RENDERERPRIMITEVEMESH_H__
#define __RENDERERPRIMITEVEMESH_H__

#include <Core/tspch.h>
#include <Component/Mesh.h>
#include <Component/Material.h>
#include <Renderer/Renderer.h>

namespace openge {
	class RendererPrimitiveMesh : public Renderer
	{
	public:
		void bind() override;
		void render() override;
	};
}

#endif // !__RENDERERPRIMITEVEMESH_H__


