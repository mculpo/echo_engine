#ifndef __RENDERERCUBE_H__
#define __RENDERERCUBE_H__

#include <core/core.h>
#include <base/Mesh.h>
#include <base/Material.h>
#include <component/Renderer.h>

namespace openge {
	class RendererCube : public Renderer
	{
	public:
		void bind() override;
		void render() override;
	};
}

#endif // !__RENDERERPRIMITEVEMESH_H__


