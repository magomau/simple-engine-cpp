#pragma once

#include <memory>

#include "GameState.h"
#include "PlayerController.h"

namespace simple_game {

class GameScene;

class GameplayState : public GameState {
public:
    GameplayState();

    bool enter(Game& game) override;
    void exit(Game& game) override;
    void handleEvent(Game& game, const SDL_Event& event) override;
    void update(Game& game, const simple_engine::Input& input, float deltaTime) override;
    void render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) override;
    GameStateId getStateId() const override;

    GameScene* getScene() const;
    void reset();

private:
    std::unique_ptr<GameScene> m_scene;
    PlayerController m_playerController;
};

} // namespace simple_game
