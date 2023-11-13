#include <base/Texture.h>
namespace openge {
	Texture::Texture()
	{
	}
	Texture::Texture(unsigned int glTarget) : m_target(glTarget), m_paths(NULL)
	{
	}
	Texture::Texture(unsigned int glTarget, const std::vector<String> path) : m_target(glTarget) , m_paths(path)
	{
	}
	Texture::~Texture()
	{
	}
	void Texture::Bind()
	{
		glBindTexture(m_target, m_textureId);
	}
	void Texture::Unbind()
	{
		glBindTexture(m_target, 0);
	}
	std::vector<String> Texture::GetPaths() const
	{
		return m_paths;
	}
	unsigned int Texture::GetTarget() const
	{
		return m_target;
	}
	unsigned int Texture::GetId() const
	{
		return 0;
	}
}
