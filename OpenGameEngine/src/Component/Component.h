#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <Core/tspch.h>
#include <Entity/Entity.h>
#include <Entity/EntityManager.h>

namespace openge {
	class Entity;

	class Component {
	private:
		ref<Entity> m_entity;
		unsigned int m_id;

	public:
		Component() : m_entity(nullptr), m_id(0) {}
		Component(ref<Entity> entity) : m_entity(entity), m_id(0) {}
		Component(ref<Entity> entity, unsigned int id) : m_entity(entity), m_id(id) {}
		~Component() {}

		void setEntity(ref<Entity> entity) {m_entity = entity;}

		void setId(unsigned int id) {m_id = id;}

		ref<Entity> getEntity() {return m_entity;}
		unsigned int getId() const {return m_id;}

		template<typename EntityType>
		ref<EntityType> gameObjectFindByTag(const std::string& tag) {
			return EntityManager::getInstance().findEntityByTag<EntityType>(tag);
		}
	};
}


#endif // __COMPONENT_H__
