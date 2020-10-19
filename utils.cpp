#include "utils.h"
#include <fstream>
#include <cassert>
#include <iostream>

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
    std::cout << "File doesn't exists: " << path << " (" << std::filesystem::absolute(path) << ")" << std::endl;
    assert(false);
    return std::vector<char>();
}
