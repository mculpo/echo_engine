#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <ecs/entity/Entity.h>
#include <ecs/entity/EntityManager.h>
namespace openge {
	class Entity;

	class Component {
	private:
		Entity* m_entity;
		std::uint64_t m_id;

	public:
		Component() : m_entity(nullptr), m_id(0) {};
		Component(std::uint64_t id) : m_entity(nullptr), m_id(id) {}
		Component(Entity* entity, std::uint64_t id) : m_entity(entity), m_id(id) {}

		virtual ~Component() {}
		void setEntity(Entity* entity) {
			m_entity = entity;
		}

		Entity* getEntity() const {
			return m_entity; // Retorna o ponteiro subjacente
		}

		Component& operator=(std::uint64_t id) {
			m_id = id;
			return *this;
		}

		template<typename EntityType>
		std::shared_ptr<EntityType> gameObjectFindByTag(const std::string& tag) {
			return EntityManager::getInstance().findEntityByTag<EntityType>(tag);
		}

	};
}


#endif // __COMPONENT_H__
