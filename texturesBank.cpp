#include "texturesBank.h"
#include "third/stb_image/stb_image.h"

#include <cassert>

namespace lbe
{
    std::map<std::filesystem::path, GLuint> texturesBank::s_texturesMap;

    GLuint texturesBank::GetTexureId(const std::filesystem::path& texturePath)
    {
        assert(s_texturesMap.find(texturePath) != s_texturesMap.end());
        return s_texturesMap[texturePath];
    }

    GLuint texturesBank::LoadTexture(const std::filesystem::path& texturePath)
    {
        assert(s_texturesMap.find(texturePath) == s_texturesMap.end());

        const auto genericStringPath = texturePath.generic_string();
        const char* c_path = genericStringPath.c_str();
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(c_path, &width, &height, &channels, 0);
        assert(data != nullptr);

        GLuint textureID = 0;
        if (data != nullptr)
        {
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if (channels == 3)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);

            s_texturesMap[texturePath] = textureID;
        }
        return textureID;
    }
}
