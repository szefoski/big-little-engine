#include "textureMVP.h"

#include "texturesBank.h"
#include <GLFW/glfw3.h>

namespace lbe
{
    void TextureMVP::Prepare()
    {
        m_vboId = loadVBO();
        m_eboId = loadEBO();
        m_vaoId = loadVAO(m_vboId, m_eboId);
        m_programShader.Compile("shaders/perspectiveTexture.vert", "shaders/perspectiveTexture.frag");
        m_programShader.Activate();
        m_transMatrixLoc = glGetUniformLocation(m_programShader.GetId(), "transform");
    }

    void TextureMVP::Draw(GLuint textureId)
    {
        //trans = glm::translate(trans, glm::vec3(1.0f, 0.5f, 0.0f));
        //m_transMatrix = glm::rotate(m_transMatrix, glm::radians(-0.025f), glm::vec3(0.0, 0.0, 1.0));
        //trans = glm::scale
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.6f, 0.3f, 0.3f));


        m_programShader.Activate();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindVertexArray(m_vaoId);
        
        int modelLoc = glGetUniformLocation(m_programShader.GetId(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(m_programShader.GetId(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(m_programShader.GetId(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    GLuint TextureMVP::loadVBO()
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

    GLuint TextureMVP::loadEBO()
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

    GLuint TextureMVP::loadVAO(GLuint vbo, GLuint ebo)
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
