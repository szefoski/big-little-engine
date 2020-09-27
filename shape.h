#pragma once
#include "glad/glad.h"
#include "program_shader.h"

#include <vector>
namespace lbe
{
    class Shape
    {
    public:
        void Prepare();
        void Draw();

    protected:
        GLuint loadVBO();
        GLuint loadEBO();
        GLuint loadVAO(GLuint vbo, GLuint ebo);

        GLuint m_vboId = 0;
        GLuint m_eboId = 0;
        GLuint m_vaoId = 0;
        ProgramShader programShader;
    };
}
