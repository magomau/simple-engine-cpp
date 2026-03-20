#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "GLFunctions.h"
#include "Scene.h"
#include "Shader.h"
#include "Window.h"
#include "core/Logger.h"

namespace simple_engine {

namespace {

constexpr const char* kVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 vTexCoord;

void main() {
    vTexCoord = aTexCoord;
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";

constexpr const char* kFragmentShaderSource = R"(
#version 330 core
in vec2 vTexCoord;
out vec4 fragmentColor;

uniform vec4 uTintColor;
uniform int uUseTexture;
uniform sampler2D uTexture0;

void main() {
    vec4 color = uTintColor;
    if (uUseTexture == 1) {
        color *= texture(uTexture0, vTexCoord);
    }
    fragmentColor = color;
}
)";

} // namespace

Renderer::Renderer()
    : m_initialized(false) {
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
    window.getDrawableSize(width, height);
    glViewport(0, 0, width, height);

    if (!m_shader.create(kVertexShaderSource, kFragmentShaderSource)) {
        return false;
    }

    m_initialized = true;
    Logger::info("Renderer initialized successfully.");
    return true;
}

void Renderer::renderScene(Window& window, const Scene& scene) {
    int width = 0;
    int height = 0;
    window.getDrawableSize(width, height);
    glViewport(0, 0, width, height);

    glClearColor(0.08f, 0.12f, 0.24f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_initialized) {
        const float aspectRatio = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0f;
        const glm::mat4 view = scene.getCamera().getViewMatrix();
        const glm::mat4 projection = scene.getCamera().getProjectionMatrix(aspectRatio);

        m_shader.bind();
        m_shader.setMatrix4("uView", view);
        m_shader.setMatrix4("uProjection", projection);
        m_shader.setInt("uTexture0", 0);

        for (const RenderObject& object : scene.getObjects()) {
            if (!object.mesh) {
                continue;
            }

            m_shader.setMatrix4("uModel", object.transform.getMatrix());
            m_shader.setVector4("uTintColor", object.tintColor);
            m_shader.setInt("uUseTexture", object.texture ? 1 : 0);

            if (object.texture) {
                object.texture->bind(0);
            } else {
                gl::ActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            object.mesh->draw();
        }
    }

    window.swapBuffers();
}

void Renderer::shutdown() {
    m_shader.destroy();
    m_initialized = false;
    Logger::info("Renderer shutdown complete.");
}

} // namespace simple_engine
