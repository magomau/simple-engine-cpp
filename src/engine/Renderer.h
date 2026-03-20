#pragma once

#include <SDL3/SDL_opengl.h>

#include <glm/vec2.hpp>

#include "Shader.h"

namespace simple_engine {

class Window;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(Window& window);
    void render(Window& window, const glm::vec2& trianglePosition);
    void shutdown();

private:
    Shader m_shader;
    GLuint m_vertexArrayObject;
    GLuint m_vertexBufferObject;
    bool m_initialized;

    bool createTriangle();
};

} // namespace simple_engine
