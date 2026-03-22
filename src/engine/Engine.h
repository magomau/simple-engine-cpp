#pragma once

#include <memory>

namespace simple_engine {

class IGame;
class Renderer;
class Window;
class Input;

class Engine {
public:
    Engine();
    ~Engine();

    bool init();
    void run(IGame& game);
    void shutdown();

private:
    bool m_running;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Input> m_input;
};

} // namespace simple_engine
