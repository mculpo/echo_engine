#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>

template<typename T>
class Component {
public:
	std::uint64_t m_id;
	T m_data;

	Component() : m_id(0) {}
	Component(std::uint64_t id, const T& value) : m_id(id), m_data(value) {}
	~Component() {}

	Component& operator=(const T& value) {
		m_data = value;
		return *this;
	}
};

#endif // __COMPONENT_H__
