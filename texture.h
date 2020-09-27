#pragma once
#include "glad/glad.h"
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
        void Draw(GLuint textureId);
    private:
        GLuint loadVBO();
        GLuint loadEBO();
        GLuint loadVAO(GLuint vbo, GLuint ebo);

        GLuint m_vboId = 0;
        GLuint m_eboId = 0;
        GLuint m_vaoId = 0;
        ProgramShader programShader;
    };
}
