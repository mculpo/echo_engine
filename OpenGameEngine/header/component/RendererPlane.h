#ifndef __RENDERERPLANE_H__
#define __RENDERERPLANE_H__

#include <core/core.h>
#include <base/Mesh.h>
#include <base/Material.h>
#include <component/Renderer.h>

namespace openge {
	class RendererPlane : public Renderer {
	public:
		void Bind() override;
		void Render() override;
	};
}
#endif // !__RENDERERPLANE_H__

