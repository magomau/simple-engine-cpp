#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <array>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GLFunctions.h"
#include "Window.h"
#include "core/Logger.h"

namespace simple_engine {

namespace {

constexpr const char* kVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";

constexpr const char* kFragmentShaderSource = R"(
#version 330 core
out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(0.95, 0.55, 0.20, 1.0);
}
)";

} // namespace

Renderer::Renderer()
    : m_vertexArrayObject(0)
    , m_vertexBufferObject(0)
    , m_initialized(false) {
}

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::init(Window& window) {
    if (!window.getNativeHandle() || !window.getGLContext()) {
        Logger::error("Renderer initialization requires a valid window and OpenGL context.");
        return false;
    }

    if (!gl::loadOpenGLFunctions()) {
        return false;
    }

    int width = 0;
    int height = 0;
    SDL_GetWindowSize(window.getNativeHandle(), &width, &height);
    glViewport(0, 0, width, height);

    if (!m_shader.create(kVertexShaderSource, kFragmentShaderSource)) {
        return false;
    }

    if (!createTriangle()) {
        return false;
    }

    m_initialized = true;
    Logger::info("Renderer initialized successfully.");
    return true;
}

void Renderer::render(Window& window, const glm::vec2& trianglePosition) {
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(window.getNativeHandle(), &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.08f, 0.12f, 0.24f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_initialized) {
        const float aspectRatio = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
        const float timeSeconds = static_cast<float>(SDL_GetTicks()) / 1000.0f;

        const glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(trianglePosition, 0.0f));
        const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), timeSeconds, glm::vec3(0.0f, 0.0f, 1.0f));
        const glm::mat4 model = translation * rotation;
        const glm::mat4 view = glm::mat4(1.0f);
        const glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        m_shader.bind();
        m_shader.setMatrix4("uModel", model);
        m_shader.setMatrix4("uView", view);
        m_shader.setMatrix4("uProjection", projection);

        gl::BindVertexArray(m_vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        gl::BindVertexArray(0);
    }

    window.swapBuffers();
}

void Renderer::shutdown() {
    if (m_vertexBufferObject != 0) {
        gl::DeleteBuffers(1, &m_vertexBufferObject);
        m_vertexBufferObject = 0;
        Logger::info("Vertex buffer destroyed.");
    }

    if (m_vertexArrayObject != 0) {
        gl::DeleteVertexArrays(1, &m_vertexArrayObject);
        m_vertexArrayObject = 0;
        Logger::info("Vertex array destroyed.");
    }

    m_shader.destroy();
    m_initialized = false;
    Logger::info("Renderer shutdown complete.");
}

bool Renderer::createTriangle() {
    constexpr std::array<float, 9> vertices = {
         0.0f,  0.6f, 0.0f,
        -0.6f, -0.45f, 0.0f,
         0.6f, -0.45f, 0.0f,
    };

    gl::GenVertexArrays(1, &m_vertexArrayObject);
    gl::GenBuffers(1, &m_vertexBufferObject);

    if (m_vertexArrayObject == 0 || m_vertexBufferObject == 0) {
        Logger::error("Failed to create OpenGL buffers for triangle geometry.");
        return false;
    }

    gl::BindVertexArray(m_vertexArrayObject);
    gl::BindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    gl::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    gl::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    gl::EnableVertexAttribArray(0);
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

    Logger::info("Triangle geometry created successfully.");
    return true;
}

} // namespace simple_engine
