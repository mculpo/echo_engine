#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include <core/core.h>

#include <base/Texture.h>
#include <base/Shader.h>

namespace openge {
    class Texture;
    class Shader;

    class Material {
    public:
        Material();
        Material(ref<Shader> shader);
        ~Material();

        void SetInstanced(bool instanced);
        void setShader(ref < Shader> shader);
        void SetAmountInstancedObject(unsigned int amount);

        ref<Shader> getShader() const;
        bool GetInstanced();
        unsigned int GetAmountInstancedObject();
    private:
        ref<Shader> m_shader;
        bool m_isInstanced;
        unsigned int m_amountInstancedObject;
    };
}
#endif

