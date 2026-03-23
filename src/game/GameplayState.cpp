#include "GameplayState.h"

#include <memory>

#include <SDL3/SDL_scancode.h>

#include "Game.h"
#include "GameScene.h"
#include "engine/Input.h"
#include "engine/RenderObject.h"
#include "core/Logger.h"

namespace simple_game {

GameplayState::GameplayState() = default;

bool GameplayState::enter(Game& game) {
    (void)game;

    if (!m_scene) {
        simple_engine::Logger::info("Entering GameplayState and building gameplay scene.");
        m_scene = std::make_unique<GameScene>();
        if (!m_scene->build()) {
            simple_engine::Logger::error("GameplayState failed to build GameScene.");
            m_scene.reset();
            return false;
        }
    } else {
        simple_engine::Logger::info("Resuming existing GameplayState.");
    }

    return true;
}

void GameplayState::exit(Game& game) {
    (void)game;
}

void GameplayState::handleEvent(Game& game, const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat && event.key.scancode == SDL_SCANCODE_ESCAPE) {
        game.changeState(GameStateId::Pause);
    }
}

void GameplayState::update(Game& game, const simple_engine::Input& input, float deltaTime) {
    (void)game;

    if (!m_scene) {
        return;
    }

    simple_engine::RenderObject* player = m_scene->getPlayer();
    if (player != nullptr) {
        m_playerController.update(input, *m_scene, *player, deltaTime);
    }

    m_scene->update(deltaTime);
}

void GameplayState::render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) {
    (void)game;

    if (!m_scene) {
        return;
    }

    m_scene->render(renderer, window);
}

GameStateId GameplayState::getStateId() const {
    return GameStateId::Gameplay;
}

GameScene* GameplayState::getScene() const {
    return m_scene.get();
}

void GameplayState::reset() {
    if (m_scene) {
        simple_engine::Logger::info("Resetting GameplayState scene.");
        m_scene.reset();
    }
}

} // namespace simple_game
