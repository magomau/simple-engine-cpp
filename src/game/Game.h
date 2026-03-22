#pragma once

#include <memory>

#include "PlayerController.h"
#include "engine/IGame.h"

namespace simple_game {

class GameScene;

class Game : public simple_engine::IGame {
public:
    Game();
    ~Game() override;

    bool init() override;
    void update(const simple_engine::Input& input, float deltaTime) override;
    void render(simple_engine::Renderer& renderer, simple_engine::Window& window) override;
    void shutdown() override;

private:
    std::unique_ptr<GameScene> m_scene;
    PlayerController m_playerController;
};

} // namespace simple_game
