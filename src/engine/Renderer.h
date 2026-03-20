#pragma once

#include "Shader.h"

namespace simple_engine {

class Scene;
class Window;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(Window& window);
    void renderScene(Window& window, const Scene& scene);
    void shutdown();

private:
    Shader m_shader;
    bool m_initialized;
};

} // namespace simple_engine
