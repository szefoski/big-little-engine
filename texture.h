#pragma once
#include "glad/glad.h"
#include "third/stb_image/stb_image.h"
#include "program_shader.h"

#include <filesystem>
#include <vector>

namespace lbe
{
    class Texture
    {
    public:
        Texture() = default;
        void Prepare();
        void Draw();
    private:
        GLuint loadVBO();
        GLuint loadEBO();
        GLuint loadVAO(GLuint vbo, GLuint ebo);
        GLuint loadTexture(const std::filesystem::path& texturePath);

        GLuint m_vboId = 0;
        GLuint m_eboId = 0;
        GLuint m_vaoId = 0;
        GLuint m_textureId = 0;
        ProgramShader programShader;
    };
}
