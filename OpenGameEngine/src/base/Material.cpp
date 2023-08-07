#include <base/Material.h>
namespace openge {

	Material::Material()
	{
	}

	Material::Material(ref<Shader> shader) : m_shader (shader)
	{
	}

	Material::~Material()
	{
	}

    void openge::Material::setShader(ref<Shader> shader)
    {
		m_shader = shader;
    }

    ref<Shader> openge::Material::getShader() const
    {
		return m_shader;
    }
}