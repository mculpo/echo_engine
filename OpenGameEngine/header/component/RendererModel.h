#ifndef __RENDERERMODELMESH_H__
#define __RENDERERMODELMESH_H__

#include <core/core.h>
#include <base/Mesh.h>
#include <base/Material.h>
#include <component/Renderer.h>

namespace openge {
	class RendererModel : public Renderer
	{
	public:
		void bind() override;
		void render() override;
	};
}

#endif // !__RENDERERMODELMESH_H__

