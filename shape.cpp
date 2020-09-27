#include "shape.h"
namespace lbe
{
    void Shape::Prepare()
    {
        m_vboId = loadVBO();
        m_eboId = loadEBO();
        m_vaoId = loadVAO(m_vboId, m_eboId);
        programShader.Compile("shaders/simple.vert", "shaders/simple.frag");
    }

    void Shape::Draw()
    {
        programShader.Activate();
        //glUniform4f(vertexColorUniform, 1.0f, 1.0f, 0.0f, 1.0f);
        glBindVertexArray(m_vaoId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    GLuint Shape::loadVBO()
    {
        const std::vector<GLfloat> vertices = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        };

        GLuint vboId;
        glGenBuffers(1, &vboId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vboId;
    }

    GLuint Shape::loadEBO()
    {
        const std::vector<GLuint> indices = {
            0, 1, 3,
            1, 2, 3
        };

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);

        return ebo;
    }

    GLuint Shape::loadVAO(GLuint vbo, GLuint ebo)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        //vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return vao;
    }
}
