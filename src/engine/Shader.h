#pragma once

#include <SDL3/SDL_opengl.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace simple_engine {

class Shader {
public:
    Shader();
    ~Shader();

    bool create(const char* vertexSource, const char* fragmentSource);
    void bind() const;
    void destroy();
    void setMatrix4(const char* uniformName, const glm::mat4& matrix) const;
    void setInt(const char* uniformName, int value) const;
    void setVector2(const char* uniformName, const glm::vec2& value) const;
    void setVector4(const char* uniformName, const glm::vec4& value) const;

private:
    GLuint m_program;

    bool compileShader(GLuint& shader, GLenum shaderType, const char* source);
    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

} // namespace simple_engine
