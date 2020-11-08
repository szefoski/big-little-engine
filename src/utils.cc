#include "lbe/utils.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <fstream>
#include <iostream>

std::vector<char> Utils::ReadFileVecChar(const std::filesystem::path& kPath) {
  if (std::filesystem::exists(kPath)) {
    std::ifstream file_stream(kPath, std::ios::in);
    const auto kSize = std::filesystem::file_size(kPath);
    std::vector<char> content(kSize + 1);
    file_stream.read(content.data(), kSize);
    file_stream.close();
    content[kSize] = 0;
    return content;
  }
  spdlog::critical("File doesn't exists: {} {}", kPath.u8string(),
                   std::filesystem::absolute(kPath).u8string());
  assert(false);
  return std::vector<char>();
}
