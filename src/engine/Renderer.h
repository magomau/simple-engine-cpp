#pragma once

namespace simple_engine {

class Scene;
class Window;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(Window& window);
    void renderScene(Window& window, Scene& scene);
    void shutdown();

private:
    bool m_initialized;
};

} // namespace simple_engine
