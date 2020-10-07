#include "texture.h"

#include "texturesBank.h"

namespace lbe
{
    void Texture::Prepare()
    {
        m_vboId = loadVBO();
        m_eboId = loadEBO();
        m_vaoId = loadVAO(m_vboId, m_eboId);
        m_programShader.Compile("shaders/textureMatrix.vert", "shaders/textureMatrix.frag");
        m_programShader.Activate();
        m_transMatrixLoc = glGetUniformLocation(m_programShader.GetId(), "transform");
    }

    void Texture::Draw(GLuint textureId)
    {
        //trans = glm::translate(trans, glm::vec3(1.0f, 0.5f, 0.0f));
        m_transMatrix = glm::rotate(m_transMatrix, glm::radians(-0.025f), glm::vec3(0.0, 0.0, 1.0));
        //trans = glm::scale
        m_programShader.Activate();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindVertexArray(m_vaoId);
        glUniformMatrix4fv(m_transMatrixLoc, 1, GL_FALSE, m_tranMatrixPtr);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    GLuint Texture::loadVBO()
    {
        const std::vector<GLfloat> vertices = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        GLuint vboId;
        glGenBuffers(1, &vboId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vboId;
    }

    GLuint Texture::loadEBO()
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

    GLuint Texture::loadVAO(GLuint vbo, GLuint ebo)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        //vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        return vao;
    }
}
