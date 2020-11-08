#include "lbe/ogl_object_3d.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace lbe {
void OglObject3d::Init() {
  vbo_id_ = SetupVBO();
  vao_id_ = SetupVAO(vbo_id_);
  program_shader_.Compile("res/shaders/object3d.vert",
                          "res/shaders/object3d.frag");
  program_shader_.Activate();
  transform_matrix_location_ =
      glGetUniformLocation(program_shader_.GetId(), "transform");
}

void OglObject3d::Draw(GLuint texture_id, float x, float y, float z,
                       float rotate_speed) {
  // trans = glm::translate(trans, glm::vec3(1.0f, 0.5f, 0.0f));
  // trans_matrix_ = glm::rotate(trans_matrix_, glm::radians(-0.025f),
  // glm::vec3(0.0, 0.0, 1.0)); trans = glm::scale
  glm::mat4 model = glm::mat4(1.0f);
  // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f,
  // 0.0f)); model = glm::rotate(model, (float)glfwGetTime() *
  // glm::radians(50.0f), glm::vec3(0.6f, 0.3f, 0.3f));
  model = glm::translate(model, glm::vec3(x, y, z));
  model = glm::rotate(model, (float)glfwGetTime() * glm::radians(rotate_speed),
                      glm::vec3(0.6f, 0.3f, 0.3f));
  glm::mat4 view = glm::mat4(1.0f);
  // note that we're translating the scene in the reverse direction of where we
  // want to move
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
  const auto kProjection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  program_shader_.Activate();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glBindVertexArray(vao_id_);

  const auto kModelLoc = glGetUniformLocation(program_shader_.GetId(), "model");
  glUniformMatrix4fv(kModelLoc, 1, GL_FALSE, glm::value_ptr(model));
  const auto kViewLoc = glGetUniformLocation(program_shader_.GetId(), "view");
  glUniformMatrix4fv(kViewLoc, 1, GL_FALSE, glm::value_ptr(view));
  const auto kProjectionLoc =
      glGetUniformLocation(program_shader_.GetId(), "projection");
  glUniformMatrix4fv(kProjectionLoc, 1, GL_FALSE, glm::value_ptr(kProjection));

  glDrawArrays(GL_TRIANGLES, 0, 36);
}

GLuint OglObject3d::SetupVBO() {
  // clang-format off
  const std::vector<GLfloat> kVertices = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  // clang-format on

  GLuint vbo_id;
  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER,
               kVertices.size() * sizeof(decltype(kVertices)::value_type),
               kVertices.data(), GL_STATIC_DRAW);

  return vbo_id;
}

GLuint OglObject3d::SetupVAO(GLuint vbo_id) {
  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);

  glBindVertexArray(vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return vao_id;
}

}  // namespace lbe
