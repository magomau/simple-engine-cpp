#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <glm/mat4x4.hpp>

#include "GLFunctions.h"
#include "Material.h"
#include "Scene.h"
#include "Window.h"
#include "core/Logger.h"

namespace simple_engine {

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

        for (const std::shared_ptr<RenderObject>& object : scene.getObjects()) {
            if (!object || !object->mesh || !object->material || !object->material->isValid()) {
                continue;
            }

            object->material->apply(object->transform.getMatrix(), view, projection);
            object->mesh->draw();
        }
    }

    window.swapBuffers();
}

void Renderer::shutdown() {
    m_initialized = false;
    Logger::info("Renderer shutdown complete.");
}

} // namespace simple_engine
