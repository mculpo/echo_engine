#include "GameObject.h"

namespace openge {
    GameObject::GameObject() : Entity(0, "", "") {}
    GameObject::GameObject(std::uint64_t id, const std::string& name, const std::string& tag)
        : Entity(id, name, tag)
    {
    }
    GameObject::~GameObject()
    {
    }
    void GameObject::setRenderer(ref<Renderer> renderer) 
    {
        m_renderer = renderer;
    }
    void GameObject::setTransform(ref<Transform> transform) 
    {
        m_transform = transform;
    }
    ref<Renderer> GameObject::getRenderer()
    {
        return m_renderer;
    }
    ref<Transform> GameObject::getTransform()
    {
        return m_transform;
    }
}

