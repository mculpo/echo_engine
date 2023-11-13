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

	void Material::SetInstanced(bool instanced)
	{
		m_isInstanced = instanced;
	}

	void openge::Material::setShader(ref<Shader> shader)
    {
		m_shader = shader;
    }

	void Material::SetAmountInstancedObject(unsigned int amount)
	{
		m_amountInstancedObject = amount;
	}

    ref<Shader> openge::Material::getShader() const
    {
		return m_shader;
    }
	bool Material::GetInstanced()
	{
		return m_isInstanced;
	}
	unsigned int Material::GetAmountInstancedObject()
	{
		return m_amountInstancedObject;
	}
}