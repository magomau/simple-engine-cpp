#pragma once

#include <SDL3/SDL.h>

namespace simple_engine {

class Window {
public:
    Window();
    ~Window();

    bool create(const char* title, int width, int height);
    void destroy();
    void swapBuffers() const;
    void getDrawableSize(int& width, int& height) const;

    SDL_Window* getNativeHandle() const;
    SDL_GLContext getGLContext() const;

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};

} // namespace simple_engine
