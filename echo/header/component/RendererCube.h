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
		void Bind() override;
		void Render() override;
	};
}

#endif // !__RENDERERPRIMITEVEMESH_H__


