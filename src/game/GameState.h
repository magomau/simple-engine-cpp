#pragma once

#include <SDL3/SDL_events.h>

namespace simple_engine {
class Input;
class Renderer;
class Window;
}

namespace simple_game {

class Game;

enum class GameStateId {
    MainMenu,
    Gameplay,
    Pause,
};

class GameState {
public:
    virtual ~GameState() = default;

    virtual bool enter(Game& game) = 0;
    virtual void exit(Game& game);
    virtual void handleEvent(Game& game, const SDL_Event& event);
    virtual void update(Game& game, const simple_engine::Input& input, float deltaTime) = 0;
    virtual void render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) = 0;
    virtual GameStateId getStateId() const = 0;
};

} // namespace simple_game
