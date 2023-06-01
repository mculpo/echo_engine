#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include <Entity/Entity.h>
#include <Core/Singleton.h>
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


		template<typename EntityType>
		void addEntity(std::shared_ptr<EntityType> entity) {
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Entity.");

			std::shared_ptr<Entity> _entity = std::static_pointer_cast<Entity>(entity);
			std::string sizeString = std::to_string(m_entities.size());
			m_entities[_entity->getTag() + sizeString] = _entity;
		}

		template<typename EntityType>
		std::vector<std::shared_ptr<EntityType>> findGameObjects()
		{
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Component<T>.");

			std::vector<std::shared_ptr<EntityType>> entities;

			for (const auto& entity : m_entities)
			{
				std::shared_ptr<EntityType> _ent = std::static_pointer_cast<EntityType>(entity.second);
				if (_ent)
				{
					entities.push_back(_ent);
				}
			}

			return entities;
		}

		template<typename EntityType>
		std::vector<std::shared_ptr<EntityType>> findGameObjectsByTag(const std::string& tag)
		{
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Entity.");
			std::vector<std::shared_ptr<EntityType>> entities;

			for (const auto& entity : m_entities) {
				if (entity.second->getTag() == tag) {
					std::shared_ptr<EntityType> _entity = std::static_pointer_cast<EntityType>(entity.second);
					if (_entity) {
						entities.push_back(_entity);
					}
				}
			}
			return entities;
		}

		void removeEntity(const std::string& tag) {
			m_entities.erase(tag);
		}

		template<typename EntityType>
		std::shared_ptr<EntityType> findEntityByTag(const std::string& tag) {

			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Entity.");

			for (const auto& entity : m_entities) {
				if (entity.second->getTag() == tag) {
					return std::static_pointer_cast<EntityType>(entity.second);
				}
			}
			return nullptr;
		}
	};

} // namespace openge

#endif

