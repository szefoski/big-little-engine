#pragma once
#include <glad/glad.h>

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "ogl_program_shader.h"

namespace lbe {
class OglObject3d {
 public:
  OglObject3d() = default;
  void Init();
  void Draw(GLuint texture_id, float x, float y, float z, float rotate_speed);

 private:
  GLuint SetupVBO();
  GLuint SetupVAO(GLuint vbo_id);

  GLuint vbo_id_ = 0;
  GLuint vao_id_ = 0;
  OglProgramShader program_shader_;
  glm::mat4 transform_matrix_ = glm::mat4(1.0f);
  GLint transform_matrix_location_ = 0;
  const glm::f32* kTransformMatrixPtr_ = glm::value_ptr(transform_matrix_);
};
}  // namespace lbe
