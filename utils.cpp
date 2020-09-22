#include "utils.h"
#include <fstream>
#include <cassert>

std::vector<char> Utils::ReadFileVecChar(const std::filesystem::path& path)
{
    if (std::filesystem::exists(path))
    {
        std::ifstream f(path, std::ios::in);
        const auto size = std::filesystem::file_size(path);
        std::vector<char> content(size);
        f.read(content.data(), size);
        f.close();
        return content;
    }
    assert(false);
    return std::vector<char>();
}
