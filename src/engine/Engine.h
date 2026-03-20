#pragma once

#include <memory>

namespace simple_engine {

class Application;
class Renderer;
class Window;

class Engine {
public:
    Engine();
    ~Engine();

    bool init();
    void run();
    void shutdown();

private:
    bool m_running;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Application> m_application;
    std::unique_ptr<Renderer> m_renderer;
};

} // namespace simple_engine
