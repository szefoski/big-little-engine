#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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
        ProgramShader m_programShader;
        glm::mat4 m_transMatrix = glm::mat4(1.0f);
        GLint m_transMatrixLoc = 0;
        glm::f32* m_tranMatrixPtr = glm::value_ptr(m_transMatrix);
    };
}
