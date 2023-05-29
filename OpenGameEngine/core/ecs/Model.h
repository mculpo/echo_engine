#ifndef __MODEL_H__
#define __MODEL_H__

#include "Entity.h"
#include <string>

namespace openge {

    class Model : public Entity {
    private:
        std::string name;
        std::string tag;

    public:
        Model(std::uint64_t id, const std::string& name, const std::string& tag);

        const std::string& GetName() const;
        void SetName(const std::string& name);

        const std::string& GetTag() const;
        void SetTag(const std::string& tag);
    };
}

#endif // __MODEL_H__
