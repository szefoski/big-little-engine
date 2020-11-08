#include "lbe/ogl_textures_bank.h"

#include <stb_image.h>

#include <cassert>

namespace lbe {
std::map<std::filesystem::path, GLuint> OglTexturesBank::textures_map_;

GLuint OglTexturesBank::GetTexureId(const std::filesystem::path& kTexturePath) {
  assert(textures_map_.find(kTexturePath) != textures_map_.end());
  return textures_map_[kTexturePath];
}

GLuint OglTexturesBank::LoadTexture(const std::filesystem::path& kTexturePath) {
  assert(textures_map_.find(kTexturePath) == textures_map_.end());

  const auto kGenericStringPath = kTexturePath.generic_string();
  const char* kCPath = kGenericStringPath.c_str();
  int width, height, channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(kCPath, &width, &height, &channels, 0);
  assert(data != nullptr);

  GLuint texture_id = 0;
  if (data != nullptr) {
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (channels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    textures_map_[kTexturePath] = texture_id;
  }
  return texture_id;
}
}  // namespace lbe
