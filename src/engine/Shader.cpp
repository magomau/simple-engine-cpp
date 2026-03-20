#include "Shader.h"

#include <string>

#include <glm/gtc/type_ptr.hpp>

#include "GLFunctions.h"
#include "core/Logger.h"

namespace simple_engine {

Shader::Shader()
    : m_program(0) {
}

Shader::~Shader() {
    destroy();
}

bool Shader::create(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    if (!compileShader(vertexShader, GL_VERTEX_SHADER, vertexSource)) {
        return false;
    }

    if (!compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentSource)) {
        gl::DeleteShader(vertexShader);
        return false;
    }

    if (!linkProgram(vertexShader, fragmentShader)) {
        gl::DeleteShader(vertexShader);
        gl::DeleteShader(fragmentShader);
        return false;
    }

    gl::DeleteShader(vertexShader);
    gl::DeleteShader(fragmentShader);

    Logger::info("Shader program created successfully.");
    return true;
}

void Shader::bind() const {
    gl::UseProgram(m_program);
}

void Shader::destroy() {
    if (m_program != 0) {
        gl::DeleteProgram(m_program);
        m_program = 0;
        Logger::info("Shader program destroyed.");
    }
}

void Shader::setMatrix4(const char* uniformName, const glm::mat4& matrix) const {
    const GLint location = gl::GetUniformLocation(m_program, uniformName);
    if (location < 0) {
        std::string message = "Uniform not found: ";
        message += uniformName;
        Logger::error(message.c_str());
        return;
    }

    gl::UniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

bool Shader::compileShader(GLuint& shader, GLenum shaderType, const char* source) {
    shader = gl::CreateShader(shaderType);
    if (shader == 0) {
        Logger::error("Failed to create shader object.");
        return false;
    }

    gl::ShaderSource(shader, 1, &source, nullptr);
    gl::CompileShader(shader);

    GLint success = GL_FALSE;
    gl::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE) {
        return true;
    }

    GLint logLength = 0;
    gl::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    std::string message = "Shader compilation failed.";
    if (logLength > 0) {
        std::string infoLog(static_cast<std::size_t>(logLength), '\0');
        gl::GetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
        message += " ";
        message += infoLog;
    }

    Logger::error(message.c_str());
    gl::DeleteShader(shader);
    shader = 0;
    return false;
}

bool Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    m_program = gl::CreateProgram();
    if (m_program == 0) {
        Logger::error("Failed to create shader program.");
        return false;
    }

    gl::AttachShader(m_program, vertexShader);
    gl::AttachShader(m_program, fragmentShader);
    gl::LinkProgram(m_program);

    GLint success = GL_FALSE;
    gl::GetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (success == GL_TRUE) {
        return true;
    }

    GLint logLength = 0;
    gl::GetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

    std::string message = "Shader linking failed.";
    if (logLength > 0) {
        std::string infoLog(static_cast<std::size_t>(logLength), '\0');
        gl::GetProgramInfoLog(m_program, logLength, nullptr, infoLog.data());
        message += " ";
        message += infoLog;
    }

    Logger::error(message.c_str());
    gl::DeleteProgram(m_program);
    m_program = 0;
    return false;
}

} // namespace simple_engine
