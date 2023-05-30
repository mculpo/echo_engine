#include "Model.h"

namespace openge {
    Model::Model(std::uint64_t id, const std::string& name, const std::string& tag)
        : Entity(id), name(name), tag(tag)
    {
    }

    const std::string& Model::GetName() const
    {
        return name;
    }

    void Model::SetName(const std::string& name)
    {
        this->name = name;
    }

    const std::string& Model::GetTag() const
    {
        return tag;
    }

    void Model::SetTag(const std::string& tag)
    {
        this->tag = tag;
    }
}

