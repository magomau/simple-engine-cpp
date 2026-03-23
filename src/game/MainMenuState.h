#pragma once

#include <memory>
#include <vector>

#include "GameState.h"
#include "UIButton.h"

namespace simple_engine {
class Scene;
class Texture;
}

namespace simple_game {

class MainMenuState : public GameState {
public:
    MainMenuState();

    bool enter(Game& game) override;
    void handleEvent(Game& game, const SDL_Event& event) override;
    void update(Game& game, const simple_engine::Input& input, float deltaTime) override;
    void render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) override;
    GameStateId getStateId() const override;

private:
    bool buildMenuScene();

    std::unique_ptr<simple_engine::Scene> m_scene;
    std::shared_ptr<simple_engine::Texture> m_checkerTexture;
    std::vector<UIButton> m_buttons;
};

} // namespace simple_game
