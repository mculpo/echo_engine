#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include <entity/Entity.h>
#include <core/Singleton.h>
#include <core/core.h>

namespace openge {

	class Entity;

	class EntityManager : public Singleton<EntityManager> {
	private:
		std::unordered_map<int, ref<Entity>> m_entities;
		ref<Entity> m_mainCamera;

	public:
		EntityManager() {};
		~EntityManager() {};

		void setMainCamera(ref<Entity> camera) {
			m_mainCamera = camera;
		}

		template<typename EntityType>
		ref<EntityType> getMainCamera() {
			return std::static_pointer_cast<EntityType>(m_mainCamera);
		}

		template<typename EntityType>
		void addEntity(ref<EntityType> entity) {
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Entity.");

			ref<Entity> _entity = std::static_pointer_cast<Entity>(entity);
			m_entities[m_entities.size() + 1] = _entity;
		}

		template<typename EntityType>
		std::vector<ref<EntityType>> findGameObjects()
		{
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Component<T>.");

			std::vector<ref<EntityType>> entities;

			for (const std::pair<const std::string, std::reference_wrapper<Entity>>& entity : m_entities)
			{
				ref<EntityType> _ent = std::static_pointer_cast<EntityType>(entity.second);
				if (_ent)
				{
					entities.push_back(_ent);
				}
			}

			return entities;
		}

		template<typename EntityType>
		std::vector<ref<EntityType>> findGameObjectsByTag(const std::string& tag)
		{
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must derive from Entity.");
			std::vector<ref<EntityType>> entities;

			for (const auto& entity : m_entities) {
				if (entity.second->getTag() == tag) {
					ref<EntityType> _entity = std::static_pointer_cast<EntityType>(entity.second);
					if (_entity) {
						entities.push_back(_entity);
					}
				}
			}
			return entities;
		}

		void removeEntity(const int tag) {
			m_entities.erase(tag);
		}

		template<typename EntityType>
		ref<EntityType> findEntityByTag(const std::string& tag) {

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

