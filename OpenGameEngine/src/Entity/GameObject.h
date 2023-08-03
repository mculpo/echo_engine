

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <Core/tspch.h>
#include <Entity/Entity.h>
#include <Component/Transform.h>
#include <Component/Renderer.h>

namespace openge {

    class GameObject : public Entity {
      
    public:
        GameObject();
        GameObject(std::uint64_t id, const std::string& name, const std::string& tag);
        ~GameObject();

        void setRenderer(ref<Renderer> renderer);
        void setTransform(ref<Transform> transform);

        ref<Renderer> getRenderer();
        ref<Transform> getTransform();

    private:
        ref<Renderer> m_renderer;
        ref<Transform> m_transform;
    };

}

#endif // __GAME_OBJECT_H__
