#pragma once
#include <glad/glad.h>

#include <filesystem>
#include <map>
#include <string>

namespace lbe {
class OglTexturesBank {
 public:
  static GLuint GetTexureId(const std::filesystem::path& kTexturePath);
  static GLuint LoadTexture(const std::filesystem::path& kTexturePath);

 private:
  static std::map<std::filesystem::path, GLuint> textures_map_;
};
}  // namespace lbe
