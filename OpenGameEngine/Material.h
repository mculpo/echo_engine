#include <ecs/components/shader/Shader.h>
#include <ecs/components/texture/Texture.h>
#include <map>
#ifndef __MATERIAL_H__
#define __MATERIAL_H__
namespace openge {
    class Texture;
    class Shader;

    class Material {
    public:
        Material();
        Material(std::shared_ptr<Shader> shader);
        ~Material();

        void setTexture(const std::string& name, std::shared_ptr<Texture> texture);
        Texture* getTexture() const;

        void setShader(std::shared_ptr < Shader> shader);
        Shader* getShader() const;

        void setup();
        void bind();
    private:
        // Propriedades adicionais
        std::string m_name;
        std::shared_ptr<Shader> m_shader;
        std::map<std::string, std::shared_ptr<Texture>> m_textures;
    };
}
#endif

