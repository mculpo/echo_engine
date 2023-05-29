#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Entity.h"
namespace openge {
	class Entity;

	class Component {
	private:
		Entity& m_entity;
		std::uint64_t m_id;

	public:

		Component(Entity& entity, std::uint64_t id) : m_entity(entity), m_id(id) {}

		virtual ~Component() {}

		Entity& getEntity() {
			return m_entity;
		}
		Component& operator=(std::uint64_t id) {
			m_id = id;
			return *this;
		}

     

	};
}


#endif // __COMPONENT_H__
