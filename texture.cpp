#include "texture.h"

namespace lbe
{
    void Texture::Prepare()
    {
        m_textureId = loadTexture("res/debug_image.png");
        m_vboId = loadVBO();
        m_eboId = loadEBO();
        m_vaoId = loadVAO(m_vboId, m_eboId);
        programShader.Compile("shaders/texture.vert", "shaders/texture.frag");
    }

    void Texture::Draw()
    {
        programShader.Activate();
        //glUniform4f(vertexColorUniform, 1.0f, 1.0f, 0.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glBindVertexArray(m_vaoId);
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

    GLuint Texture::loadTexture(const std::filesystem::path& texturePath)
    {
        const auto genericStringPath = texturePath.generic_string();
        const char* c_path = genericStringPath.c_str();
        int width, height, channels;
        unsigned char* data = stbi_load(c_path, &width, &height, &channels, 0);

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        return textureID;
    }
}
