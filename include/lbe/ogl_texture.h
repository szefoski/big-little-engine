#pragma once
#include <glad/glad.h>

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "ogl_program_shader.h"

namespace lbe {
class OglTexture {
 public:
  OglTexture() = default;
  void Prepare();
  void Draw(const GLuint kTextureId);

 private:
  GLuint loadVBO();
  GLuint loadEBO();
  GLuint loadVAO(const GLuint kVboId, const GLuint kEboId);

  GLuint vbo_id_ = 0;
  GLuint ebo_id_ = 0;
  GLuint vao_id_ = 0;
  OglProgramShader program_shader_;
  glm::mat4 trans_matrix_ = glm::mat4(1.0f);
  GLint trans_matrix_loc_ = 0;
  glm::f32* tran_matrix_ptr_ = glm::value_ptr(trans_matrix_);
};
}  // namespace lbe
