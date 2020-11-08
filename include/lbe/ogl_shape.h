#pragma once
#include <glad/glad.h>

#include <vector>

#include "ogl_program_shader.h"
namespace lbe {
class OglShape {
 public:
  void Prepare();
  void Draw();

 protected:
  GLuint LoadVBO();
  GLuint LoadEBO();
  GLuint LoadVAO(GLuint vbo_id, GLuint ebo_id);

  GLuint vbo_id_ = 0;
  GLuint ebo_id_ = 0;
  GLuint vao_id_ = 0;
  OglProgramShader program_shader_;
};
}  // namespace lbe
