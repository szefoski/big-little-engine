#include "lbe/ogl_texture_mvp.h"

#include <GLFW/glfw3.h>

#include "lbe/ogl_textures_bank.h"

namespace lbe {
void OglTextureMVP::Prepare() {
  vbo_id_ = loadVBO();
  ebo_id_ = loadEBO();
  vao_id_ = loadVAO(vbo_id_, ebo_id_);
  program_shader_.Compile("res/shaders/perspectiveTexture.vert",
                          "res/shaders/perspectiveTexture.frag");
  program_shader_.Activate();
  trans_matrix_loc_ = glGetUniformLocation(program_shader_.GetId(), "transform");
}

void OglTextureMVP::Draw(const GLuint kTextureId) {
  // trans = glm::translate(trans, glm::vec3(1.0f, 0.5f, 0.0f));
  // trans_matrix_ = glm::rotate(trans_matrix_, glm::radians(-0.025f),
  // glm::vec3(0.0, 0.0, 1.0)); trans = glm::scale
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 view = glm::mat4(1.0f);
  // note that we're translating the scene in the reverse direction of where we
  // want to move
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projection;
  projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
                      glm::vec3(0.6f, 0.3f, 0.3f));

  program_shader_.Activate();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, kTextureId);
  glBindVertexArray(vao_id_);

  int modelLoc = glGetUniformLocation(program_shader_.GetId(), "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  int viewLoc = glGetUniformLocation(program_shader_.GetId(), "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  int projectionLoc =
      glGetUniformLocation(program_shader_.GetId(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GLuint OglTextureMVP::loadVBO() {
  const std::vector<GLfloat> vertices = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };

  GLuint vboId;
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(decltype(vertices)::value_type),
               vertices.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vboId;
}

GLuint OglTextureMVP::loadEBO() {
  // clang-format off
  const std::vector<GLuint> kIndices = {
      0, 1, 3,
      1, 2, 3
  };
  // clang-format on
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               kIndices.size() * sizeof(decltype(kIndices)::value_type),
               kIndices.data(), GL_STATIC_DRAW);

  return ebo;
}

GLuint OglTextureMVP::loadVAO(const GLuint kVboId, const GLuint kEboId) {
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
