#include "program_shader.h"

#include "utils.h"

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

ProgramShader::ProgramShader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
{
    Compile(vertexPath, fragmentPath);
}

void ProgramShader::Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    auto vertex = Utils::ReadFileVecChar(vertexPath);
    auto fragment = Utils::ReadFileVecChar(fragmentPath);

    if (!CompileShader(GL_VERTEX_SHADER, vertex.data(), m_vertexId))
    {
        assert(false);
    }

    if (!CompileShader(GL_FRAGMENT_SHADER, fragment.data(), m_fragmentId))
    {
        assert(false);
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, m_vertexId);
    glAttachShader(m_id, m_fragmentId);
    glLinkProgram(m_id);
    glDeleteShader(m_vertexId);
    glDeleteShader(m_fragmentId);

    GLint success;
    std::array<char, 512> infoLog;
    
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, static_cast<GLsizei>(infoLog.size()), nullptr,  infoLog.data());
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog.data() << std::endl;
    }
}

bool ProgramShader::CompileShader(GLenum type, const char* source, GLuint& id)
{
    int success;
    std::array<char, 512> infoLog;

    id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog.data() << std::endl;
        return false;
    };
    return true;
}
