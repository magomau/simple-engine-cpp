#include "Game.h"

#include "GameScene.h"
#include "engine/GLFunctions.h"
#include "engine/Input.h"
#include "engine/RenderObject.h"
#include "core/Logger.h"

namespace simple_game {

Game::Game() = default;
Game::~Game() = default;

bool Game::init() {
    simple_engine::Logger::info("Game::init started.");

    if (!simple_engine::gl::isOpenGLLoaded()) {
        simple_engine::Logger::error("Game::init called before OpenGL functions were loaded.");
        return false;
    }

    m_scene = std::make_unique<GameScene>();
    if (!m_scene->build()) {
        simple_engine::Logger::error("Failed to build GameScene.");
        m_scene.reset();
        return false;
    }

    simple_engine::Logger::info("Game::init completed after OpenGL initialization.");
    return true;
}

void Game::update(const simple_engine::Input& input, float deltaTime) {
    if (!m_scene) {
        return;
    }

    simple_engine::RenderObject* player = m_scene->getPlayer();
    if (player != nullptr) {
        m_playerController.update(input, *m_scene, *player, deltaTime);
    }

    m_scene->update(deltaTime);
}

void Game::render(simple_engine::Renderer& renderer, simple_engine::Window& window) {
    if (!m_scene) {
        return;
    }

    m_scene->render(renderer, window);
}

void Game::shutdown() {
    if (m_scene) {
        simple_engine::Logger::info("Shutting down game scene.");
        m_scene.reset();
    }
}

} // namespace simple_game
