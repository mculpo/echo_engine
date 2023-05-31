#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include <ecs/entity/Entity.h>
#include <ecs/singleton/Singleton.h>
#include <unordered_map>
#include <string>
#include <memory>

namespace openge {

    class Entity;

    class EntityManager : public Singleton<EntityManager> {
    private:
        std::unordered_map<std::string, std::shared_ptr<Entity>> m_entities;

    public:
        EntityManager() {};
        ~EntityManager() {};

        template<typename ComponentType, typename... Args>
        void addEntity(Args&&... args) {
            static_assert(std::is_base_of<Entity, ComponentType>::value, "ComponentType must derive from Component<T>.");

            std::shared_ptr<ComponentType> _entity = std::make_shared<ComponentType>(std::forward<Args>(args)...);
            std::shared_ptr<Entity> __entity = std::static_pointer_cast<Entity>(_entity);
            m_entities[__entity->getTag()] = _entity;
        }

        void removeEntity(const std::string& tag) {
            m_entities.erase(tag);
        }

        template<typename EntityType>
        std::shared_ptr<EntityType> findEntityByTag(const std::string& tag) {
            auto it = m_entities.find(tag);
            if (it != m_entities.end()) {
                std::shared_ptr<Entity> entity = it->second;
                return std::static_pointer_cast<EntityType>(entity);
            }
            return nullptr;
        }
    };

} // namespace openge

#endif

