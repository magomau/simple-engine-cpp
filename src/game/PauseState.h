#pragma once

#include <memory>

#include "GameState.h"

namespace simple_engine {
class Scene;
}

namespace simple_game {

class PauseState : public GameState {
public:
    PauseState();

    bool enter(Game& game) override;
    void handleEvent(Game& game, const SDL_Event& event) override;
    void update(Game& game, const simple_engine::Input& input, float deltaTime) override;
    void render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) override;
    GameStateId getStateId() const override;

private:
    bool buildPauseScene();

    std::unique_ptr<simple_engine::Scene> m_scene;
};

} // namespace simple_game
