#pragma once
#include <glad/gl.h>

#include <filesystem>
#include <string>

namespace lbe {
class OglProgramShader {
 public:
  OglProgramShader() = default;
  OglProgramShader(const std::filesystem::path& kVertexSrcPath,
                   const std::filesystem::path& kFragmentSrcPath);
  void Compile(const std::filesystem::path& kVertexSrcPath,
               const std::filesystem::path& kFragmentSrcPath);
  void Activate() const { glUseProgram(program_id_); }
  void SetBool(const std::string& kName, const bool value) const;
  void SetInt(const std::string& kName, const int value) const;
  void SetFloat(const std::string& kName, const float value) const;
  GLuint GetId() const { return program_id_; }

 protected:
  GLuint program_id_ = 0;
  GLuint vertex_id_ = 0;
  GLuint fragment_id_ = 0;

  static bool CompileShader(const GLenum kType, const char* kSource,
                            GLuint& shader_id);
};
}  // namespace lbe
