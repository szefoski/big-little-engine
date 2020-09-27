#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <map>
#include <string>

namespace lbe
{
    class texturesBank
    {
    public:
        static GLuint GetTexureId(const std::filesystem::path& texturePath);
        static GLuint LoadTexture(const std::filesystem::path& texturePath);
    private:
        static std::map<std::filesystem::path, GLuint> s_texturesMap;
    };
}

