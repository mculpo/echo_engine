#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>
namespace openge {
	template<typename T>
	class Component {
	public:
		std::uint64_t m_id;

		Component() : m_id(0) {}
		Component(std::uint64_t id) : m_id(id) {}
		~Component() {}

		Component& operator=(std::uint64_t id) {
			m_id = id;
			return *this;
		}
	};
}
#endif // __COMPONENT_H__
