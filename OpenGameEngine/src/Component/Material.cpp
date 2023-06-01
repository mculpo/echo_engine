#include "Material.h"
namespace openge {
	// Mapeamento dos valores de texture unit para seus respectivos nomes
	std::unordered_map<int, int> textureUnitNames = {
		{0	,GL_TEXTURE0 },
		{1	,GL_TEXTURE1 },
		{2	,GL_TEXTURE2 },
		{3	,GL_TEXTURE3 },
		{4	,GL_TEXTURE4 },
		{5	,GL_TEXTURE5 },
		{6	,GL_TEXTURE6 },
		{7	,GL_TEXTURE7 },
		{8	,GL_TEXTURE8 },
		{9	,GL_TEXTURE9 },
		{10	,GL_TEXTURE10},
		{11	,GL_TEXTURE11},
		{12	,GL_TEXTURE12},
		{13	,GL_TEXTURE13},
		{14	,GL_TEXTURE14},
		{15	,GL_TEXTURE15},
		{16	,GL_TEXTURE16},
		{17	,GL_TEXTURE17},
		{18	,GL_TEXTURE18},
		{19	,GL_TEXTURE19},
		{20	,GL_TEXTURE20},
		{21	,GL_TEXTURE21},
		{22	,GL_TEXTURE22},
		{23	,GL_TEXTURE23},
		{24	,GL_TEXTURE24},
		{25	,GL_TEXTURE25},
		{26	,GL_TEXTURE26},
		{27	,GL_TEXTURE27},
		{28	,GL_TEXTURE28},
		{29	,GL_TEXTURE29},
		{30	,GL_TEXTURE30},
		{31	,GL_TEXTURE31}
	};


	Material::Material()
	{
	}

	Material::Material(std::shared_ptr<Shader> shader) : m_shader (shader)
	{
	}

	Material::~Material()
	{
	}

	void openge::Material::setTexture(const std::string& name, std::shared_ptr<Texture> texture)
    {
		m_textures[name] = std::move(texture);
    }

    Texture* openge::Material::getTexture() const
    {
        return nullptr;
    }

    void openge::Material::setShader(std::shared_ptr<Shader> shader)
    {
		m_shader = shader;
    }

    Shader* openge::Material::getShader() const
    {
		return m_shader.get();
    }

    void openge::Material::setup()
    {
		m_shader->Bind();
		for (const auto& pair : m_textures) {
			const std::string& textureName = pair.first;
			const Texture& texture = *(pair.second);

			char lastChar = textureName.back(); // Obter o último caractere do nome
			int textureUnit = lastChar - '0'; // Converter o caractere para um valor numérico

			// Set the uniform for the texture
			m_shader->setUniform1i(textureName, textureUnit - 1);
		}
    }

    void openge::Material::bind()
    {
		int textureUnit = 0;
		for (const auto& pair : m_textures) {
			const std::string& textureName = pair.first;
			Texture* texture = pair.second.get();

			auto it = textureUnitNames.find(textureUnit);
			if (it != textureUnitNames.end()) {
				glActiveTexture(it->second);
				texture->Bind();
			}
			else {
				std::cout << "Texture Unit not found." << std::endl;
			}

			textureUnit++;
		}
		m_shader->Bind();
    }
}