#pragma once

#include <SDL3/SDL_opengl.h>

#include "Scene.h"
#include "Shader.h"

namespace simple_engine {

class Window;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(Window& window);
    void render(Window& window, const Scene& scene);
    void shutdown();

private:
    Shader m_shader;
    bool m_initialized;
};

} // namespace simple_engine
