#include "lbe/ogl_texture.h"

#include "lbe/ogl_textures_bank.h"

namespace lbe {
void OglTexture::Prepare() {
  vbo_id_ = loadVBO();
  ebo_id_ = loadEBO();
  vao_id_ = loadVAO(vbo_id_, ebo_id_);
  program_shader_.Compile("shaders/textureMatrix.vert",
                          "shaders/textureMatrix.frag");
  program_shader_.Activate();
  trans_matrix_loc_ = glGetUniformLocation(program_shader_.GetId(), "transform");
}

void OglTexture::Draw(const GLuint kTextureId) {
  // trans = glm::translate(trans, glm::vec3(1.0f, 0.5f, 0.0f));
  trans_matrix_ = glm::rotate(trans_matrix_, glm::radians(-0.025f),
                              glm::vec3(0.0, 0.0, 1.0));
  // trans = glm::scale
  program_shader_.Activate();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, kTextureId);
  glBindVertexArray(vao_id_);
  glUniformMatrix4fv(trans_matrix_loc_, 1, GL_FALSE, tran_matrix_ptr_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GLuint OglTexture::loadVBO() {
  const std::vector<GLfloat> vertices = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };

  GLuint vbo_id;
  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(decltype(vertices)::value_type),
               vertices.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vbo_id;
}

GLuint OglTexture::loadEBO() {
  // clang-format off
  const std::vector<GLuint> kIndices = {
      0, 1, 3,
      1, 2, 3
  };
  // clang-format on
  GLuint ebo_id;
  glGenBuffers(1, &ebo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               kIndices.size() * sizeof(decltype(kIndices)::value_type),
               kIndices.data(), GL_STATIC_DRAW);

  return ebo_id;
}

GLuint OglTexture::loadVAO(const GLuint kVboId, const GLuint kEboId) {
  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);

  glBindVertexArray(vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, kVboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEboId);

  // vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  return vao_id;
}
}  // namespace lbe
