#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include <core/core.h>
namespace openge {

	class Texture
	{
	public:
		Texture();
		Texture(unsigned int glTarget);
		Texture(unsigned int glTarget, const std::vector<String> path);
		~Texture();

		virtual void Bind();
		virtual void Unbind();


		virtual std::vector<String> GetPaths() const;
		virtual unsigned int GetTarget() const;
		virtual unsigned int GetId() const;

	protected:
		unsigned int m_textureId;
		unsigned int m_target;
		std::vector<String> m_paths;
	};
}
#endif // !__TEXTURE_H__



