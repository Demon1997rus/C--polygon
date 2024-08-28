#include "functions.h"

#include <sys/stat.h>

namespace rdi {
// POSIX
std::string searchConfig(const std::string &name, bool *ok)
{
    static std::array<std::string, 2> directories = {"../testirovka_noqt/data/", "../data/"};
    for (const std::string &directory : directories) {
        struct stat buffer;
        const std::string configPath = directory + name;
        if (stat(configPath.c_str(), &buffer) == 0) {
            if (ok) {
                *ok = true;
            }
            return configPath;
        }
    }
    if (ok) {
        *ok = false;
    }
    return std::string();
}

} // namespace rdi
