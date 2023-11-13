#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__
#include <core/core.h>
namespace openge {
    class FileSystem {
    public:
        // Método estático que recebe uma string e retorna o caminho completo
        static String path(const String& input) {
            std::filesystem::path fullPath = std::filesystem::current_path() / input;
            return fullPath.string();
        }
    };
}
#endif // !__FILESYSTEM_H__