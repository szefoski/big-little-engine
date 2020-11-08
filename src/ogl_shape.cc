#include "lbe/ogl_shape.h"

namespace lbe {
void OglShape::Prepare() {
  vbo_id_ = LoadVBO();
  ebo_id_ = LoadEBO();
  vao_id_ = LoadVAO(vbo_id_, ebo_id_);
  program_shader_.Compile("res/shaders/simple.vert", "res/shaders/simple.frag");
}

void OglShape::Draw() {
  program_shader_.Activate();
  // glUniform4f(vertexColorUniform, 1.0f, 1.0f, 0.0f, 1.0f);
  glBindVertexArray(vao_id_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GLuint OglShape::LoadVBO() {
  // clang-format off
  const std::vector<GLfloat> kVertices = {
       0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
  };
  // clang-format on

  GLuint vbo_id_;
  glGenBuffers(1, &vbo_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
  glBufferData(GL_ARRAY_BUFFER,
               kVertices.size() * sizeof(decltype(kVertices)::value_type),
               kVertices.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vbo_id_;
}

GLuint OglShape::LoadEBO() {
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

GLuint OglShape::LoadVAO(GLuint vbo_id, GLuint ebo_id) {
  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);

  glBindVertexArray(vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);

  // vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return vao_id;
}
}  // namespace lbe
