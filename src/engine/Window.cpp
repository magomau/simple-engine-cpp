#include "Window.h"

#include <SDL3/SDL_opengl.h>

#include "core/Logger.h"

namespace simple_engine {

Window::Window()
    : m_window(nullptr)
    , m_glContext(nullptr) {
}

Window::~Window() {
    destroy();
}

bool Window::create(const char* title, int width, int height) {
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) ||
        !SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) ||
        !SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) ||
        !SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
        Logger::error(SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        Logger::error(SDL_GetError());
        return false;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        Logger::error(SDL_GetError());
        destroy();
        return false;
    }

    if (!SDL_GL_MakeCurrent(m_window, m_glContext)) {
        Logger::error(SDL_GetError());
        destroy();
        return false;
    }

    if (!SDL_GL_SetSwapInterval(1)) {
        Logger::error(SDL_GetError());
        destroy();
        return false;
    }

    Logger::info("Window and OpenGL context created successfully.");
    return true;
}

void Window::destroy() {
    if (m_glContext) {
        SDL_GL_DestroyContext(m_glContext);
        m_glContext = nullptr;
        Logger::info("OpenGL context destroyed.");
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        Logger::info("Window destroyed.");
    }
}

void Window::swapBuffers() const {
    if (m_window) {
        SDL_GL_SwapWindow(m_window);
    }
}

SDL_Window* Window::getNativeHandle() const {
    return m_window;
}

SDL_GLContext Window::getGLContext() const {
    return m_glContext;
}

} // namespace simple_engine
