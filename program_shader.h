#pragma once
#include <glad/glad.h>

#include <filesystem>
#include <string>

namespace lbe
{
    class ProgramShader
    {
    public:
        ProgramShader() = default;
        ProgramShader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        void Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        void Activate() const
        {
            glUseProgram(m_id);
        }
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
    protected:
        GLuint m_id = 0;
        GLuint m_vertexId = 0;
        GLuint m_fragmentId = 0;

        static bool CompileShader(GLenum type, const char* source, GLuint& id);
    };
}
