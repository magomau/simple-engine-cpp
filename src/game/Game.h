#pragma once

#include <memory>

#include "engine/IGame.h"

namespace simple_game {

enum class GameStateId;
class GameplayState;
class MainMenuState;
class PauseState;
class GameState;

class Game : public simple_engine::IGame {
public:
    Game();
    ~Game() override;

    bool init() override;
    void handleEvent(const SDL_Event& event) override;
    void update(const simple_engine::Input& input, float deltaTime) override;
    void render(simple_engine::Renderer& renderer, simple_engine::Window& window) override;
    void shutdown() override;

    bool changeState(GameStateId nextState);
    GameplayState* getGameplayState() const;

private:
    GameState* getStateInstance(GameStateId stateId);

    std::unique_ptr<MainMenuState> m_mainMenuState;
    std::unique_ptr<GameplayState> m_gameplayState;
    std::unique_ptr<PauseState> m_pauseState;
    GameState* m_activeState;
};

} // namespace simple_game
