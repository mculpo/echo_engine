#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Component.h"

namespace openge {

    class Component;

    class Entity
    {
    private:
        std::uint64_t m_id;
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;

    public:
        Entity()
            : m_id(0) {}

        Entity(std::uint64_t id)
            : m_id(id) {}

        ~Entity() {}

        template<typename ComponentType, typename... Args>
        void addComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::type_index componentTypeIndex(typeid(ComponentType));
            if (m_components.count(componentTypeIndex) == 0)
            {
                std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);
                m_components[componentTypeIndex] = component;
            }
            else
            {
                // ComponentType already exists, you may want to handle this case accordingly
            }
        }

        template<typename ComponentType>
        std::shared_ptr<ComponentType> getComponent()
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
