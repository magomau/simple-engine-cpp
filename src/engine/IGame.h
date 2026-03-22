#pragma once

#include <SDL3/SDL_events.h>

namespace simple_engine {

class Input;
class Renderer;
class Window;

class IGame {
public:
    virtual ~IGame() = default;

    virtual bool init() = 0;
    virtual void handleEvent(const SDL_Event& event);
    virtual void update(const Input& input, float deltaTime) = 0;
    virtual void render(Renderer& renderer, Window& window) = 0;
    virtual void shutdown();
};

} // namespace simple_engine
