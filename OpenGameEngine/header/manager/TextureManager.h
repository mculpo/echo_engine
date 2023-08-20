#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__
#include <core/core.h>
#include <core/Singleton.h>
#include <base/Texture.h>

namespace openge {
	class TextureManager : public Singleton<TextureManager> {
	public:
		void Add(ref<Texture> texture, unsigned int& index_texture) {
			m_textures[m_index] = texture;
			index_texture = m_index;
			m_index++;
		}

		void GetTextureByPath(const std::string& texture, unsigned int& index_texture) const {
			index_texture = -1;
			for (const auto& texture_pair : m_textures) {
				if (std::strcmp(texture_pair.second->GetPath().data(), texture.c_str()) == 0 ) {
					index_texture = texture_pair.first;
					return;
				}
			}
		}

		ref<Texture> GetTextureByIndex(const unsigned int index) {
			auto it = m_textures.find(index);
			if (it != m_textures.end()) {
				return it->second;
			}
			else {
				return nullptr;
			}
		}

	private:
		std::map<unsigned int, ref<Texture>> m_textures;
		unsigned int m_index = 0;

	};
}
#endif // !__TEXTUREMANAGER_H__

