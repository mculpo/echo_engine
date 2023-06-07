#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <Core/tspch.h>
#include "Component/Component.h"

namespace openge {

    class Component;
    class EntityManager;

    class Entity : public std::enable_shared_from_this<Entity> {
    protected:
        std::uint64_t m_id;
        std::unordered_map<std::type_index, ref<Component>> m_components;
        std::string m_name;
        std::string m_tag;

    public:
        Entity(std::uint64_t id, std::string name, std::string tag)
            : m_id(id), m_name(name), m_tag(tag) {}

        ~Entity() {}

        std::string getName() const {
            return m_name;
        }
        std::string getTag() const {
            return m_tag;
        }

        template<typename ComponentType>
        void addComponent(ref<ComponentType> component)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::type_index componentTypeIndex(typeid(ComponentType));
            if (m_components.count(componentTypeIndex) == 0)
            {
                component->setEntity(shared_from_this());
                ref<Component> baseComponent = std::static_pointer_cast<Component>(component);
                m_components[componentTypeIndex] = baseComponent;
            }
        }

        template<typename ComponentType>
        ref<ComponentType> getComponent()
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::type_index componentTypeIndex(typeid(ComponentType));
            auto it = m_components.find(componentTypeIndex);
            if (it != m_components.end())
            {
                return std::static_pointer_cast<ComponentType>(it->second);
            }
            return nullptr;
        }

        template<typename ComponentType>
        bool hasComponent()
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::type_index componentTypeIndex(typeid(ComponentType));
            return m_components.count(componentTypeIndex) > 0;
        }

        template<typename ComponentType>
        void removeComponent()
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::type_index componentTypeIndex(typeid(ComponentType));
            m_components.erase(componentTypeIndex);
        }
    };

} // namespace openge

#endif
