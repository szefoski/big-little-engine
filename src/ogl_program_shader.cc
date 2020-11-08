#include "lbe/ogl_program_shader.h"

#include <array>
#include <cassert>
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h"
#include <vector>

#include "lbe/utils.h"

namespace lbe {

OglProgramShader::OglProgramShader(
    const std::filesystem::path& kVertexSrcPath,
    const std::filesystem::path& kFragmentSrcPath) {
  Compile(kVertexSrcPath, kFragmentSrcPath);
}

void OglProgramShader::Compile(const std::filesystem::path& kVertexPath,
                               const std::filesystem::path& kFragmentPath) {
  const auto kVertexSrc = Utils::ReadFileVecChar(kVertexPath);
  const auto kFragmentSrc = Utils::ReadFileVecChar(kFragmentPath);

  spdlog::error("Shader compilation error NOT: {}", kVertexPath);

  if (!CompileShader(GL_VERTEX_SHADER, kVertexSrc.data(), vertex_id_)) {
    spdlog::error("Shader compilation error: {}", kVertexPath);
    assert(false);
  }

  if (!CompileShader(GL_FRAGMENT_SHADER, kFragmentSrc.data(), fragment_id_)) {
    spdlog::error("Shader compilation error: {}", kFragmentPath);
    assert(false);
  }

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_id_);
  glAttachShader(program_id_, fragment_id_);
  glLinkProgram(program_id_);
  glDeleteShader(vertex_id_);
  glDeleteShader(fragment_id_);

  GLint success_status;

  glGetProgramiv(program_id_, GL_LINK_STATUS, &success_status);
  if (!success_status) {
    std::array<char, 512> info_log;
    glGetProgramInfoLog(program_id_, static_cast<GLsizei>(info_log.size()),
                        nullptr, info_log.data());
    spdlog::error("ERROR::SHADER::PROGRAM::LINKING_FAILED:\n{}", info_log.data());
  }
}

bool OglProgramShader::CompileShader(const GLenum kType, const char* kSource,
                                     GLuint& id) {
  int success;
  std::array<char, 512> info_log;

  id = glCreateShader(kType);
  glShaderSource(id, 1, &kSource, nullptr);
  glCompileShader(id);

  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id, static_cast<GLsizei>(info_log.size()), nullptr,
                       info_log.data());
    /*std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
              << info_log.data() << std::endl;*/
    return false;
  };
  return true;
}
}  // namespace lbe
