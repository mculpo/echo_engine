#ifndef __MATERIALMANAGER_H__
#define __MATERIALMANAGER_H__

#include <core/core.h>
#include <base/Material.h>

namespace openge {

    class MaterialManager {
    public:
        static void AddMaterial(const String& name, const ref<Material> material) {
            materials[name] = material;
        }

        static ref<Material> GetMaterial(const String& name) {
            auto it = materials.find(name);
            if (it != materials.end()) {
                return it->second;
            }
            return nullptr;
        }

        static void ClearMaterials() {
            materials.clear();
        }

    private:
        static std::unordered_map<String, ref<Material>> materials;
    };

    std::unordered_map<String, ref<Material>> MaterialManager::materials;
}


#endif // !__MATERIALMANAGER_H__

