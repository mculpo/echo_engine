#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <Entity/Entity.h>
#include <Entity/EntityManager.h>

namespace openge {
	class Entity;

	class Component {
	private:
		std::shared_ptr<Entity> m_entity;
		unsigned int m_id;

	public:
		Component() : m_entity(nullptr), m_id(0) {}
		Component(std::shared_ptr<Entity> entity) : m_entity(entity), m_id(0) {}
		Component(std::shared_ptr<Entity> entity, unsigned int id) : m_entity(entity), m_id(id) {}
		~Component() {}

		void setEntity(std::shared_ptr<Entity> entity) {m_entity = entity;}

		void setId(unsigned int id) {m_id = id;}

		std::shared_ptr<Entity> getEntity() {return m_entity;}
		unsigned int getId() const {return m_id;}

		template<typename EntityType>
		std::shared_ptr<EntityType> gameObjectFindByTag(const std::string& tag) {
			return EntityManager::getInstance().findEntityByTag<EntityType>(tag);
		}
	};
}


#endif // __COMPONENT_H__
