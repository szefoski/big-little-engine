#pragma once
#include <filesystem>
#include <vector>

namespace Utils {
std::vector<char> ReadFileVecChar(const std::filesystem::path &kPath);
}
