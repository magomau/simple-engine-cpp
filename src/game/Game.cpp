#include "Game.h"

#include "GameState.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "engine/GLFunctions.h"
#include "engine/Input.h"
#include "core/Logger.h"

namespace simple_game {

Game::Game()
    : m_activeState(nullptr) {
}

Game::~Game() = default;

bool Game::init() {
    simple_engine::Logger::info("Game::init started.");

    if (!simple_engine::gl::isOpenGLLoaded()) {
        simple_engine::Logger::error("Game::init called before OpenGL functions were loaded.");
        return false;
    }

    m_mainMenuState = std::make_unique<MainMenuState>();
    m_gameplayState = std::make_unique<GameplayState>();
    m_pauseState = std::make_unique<PauseState>();

    if (!changeState(GameStateId::MainMenu)) {
        simple_engine::Logger::error("Failed to enter initial MainMenuState.");
        return false;
    }

    simple_engine::Logger::info("Game::init completed after OpenGL initialization and state setup.");
    return true;
}

void Game::handleEvent(const SDL_Event& event) {
    if (m_activeState) {
        m_activeState->handleEvent(*this, event);
    }
}

void Game::update(const simple_engine::Input& input, float deltaTime) {
    if (!m_activeState) {
        return;
    }

    m_activeState->update(*this, input, deltaTime);
}

void Game::render(simple_engine::Renderer& renderer, simple_engine::Window& window) {
    if (!m_activeState) {
        return;
    }

    m_activeState->render(*this, renderer, window);
}

void Game::shutdown() {
    if (m_activeState) {
        m_activeState->exit(*this);
        m_activeState = nullptr;
    }

    m_pauseState.reset();
    m_gameplayState.reset();
    m_mainMenuState.reset();
    simple_engine::Logger::info("Game states shut down.");
}

bool Game::changeState(GameStateId nextState) {
    GameState* nextStateInstance = getStateInstance(nextState);
    if (!nextStateInstance) {
        simple_engine::Logger::error("Requested game state is not available.");
        return false;
    }

    if (m_activeState == nextStateInstance) {
        return true;
    }

    if (m_activeState) {
        m_activeState->exit(*this);
    }

    if (!nextStateInstance->enter(*this)) {
        simple_engine::Logger::error("Failed to enter requested game state.");
        return false;
    }

    m_activeState = nextStateInstance;
    simple_engine::Logger::info("Game state transition completed.");
    return true;
}

GameplayState* Game::getGameplayState() const {
    return m_gameplayState.get();
}

GameState* Game::getStateInstance(GameStateId stateId) {
    switch (stateId) {
    case GameStateId::MainMenu:
        return m_mainMenuState.get();
    case GameStateId::Gameplay:
        return m_gameplayState.get();
    case GameStateId::Pause:
        return m_pauseState.get();
    default:
        return nullptr;
    }
}

} // namespace simple_game
