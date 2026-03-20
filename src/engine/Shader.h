#pragma once

#include <SDL3/SDL_opengl.h>

#include <glm/mat4x4.hpp>

namespace simple_engine {

class Shader {
public:
    Shader();
    ~Shader();

    bool create(const char* vertexSource, const char* fragmentSource);
    void bind() const;
    void destroy();
    void setMatrix4(const char* uniformName, const glm::mat4& matrix) const;

private:
    GLuint m_program;

    bool compileShader(GLuint& shader, GLenum shaderType, const char* source);
    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

} // namespace simple_engine
