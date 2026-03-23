#include "PauseState.h"

#include <memory>
#include <string>

#include <SDL3/SDL_scancode.h>

#include <glm/vec4.hpp>

#include "Game.h"
#include "engine/Scene.h"
#include "engine/Sprite.h"
#include "engine/Texture.h"
#include "engine/UIElement.h"
#include "core/Logger.h"

namespace simple_game {

PauseState::PauseState() = default;

bool PauseState::enter(Game& game) {
    (void)game;

    if (!m_scene) {
        return buildPauseScene();
    }

    simple_engine::Logger::info("Entering PauseState.");
    return true;
}

void PauseState::handleEvent(Game& game, const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN || event.key.repeat) {
        return;
    }

    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
        game.changeState(GameStateId::Gameplay);
        return;
    }

    if (event.key.scancode == SDL_SCANCODE_M) {
        game.changeState(GameStateId::MainMenu);
    }
}

void PauseState::update(Game& game, const simple_engine::Input& input, float deltaTime) {
    (void)game;
    (void)input;

    if (m_scene) {
        m_scene->update(deltaTime);
    }
}

void PauseState::render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) {
    (void)game;

    if (m_scene) {
        m_scene->render(renderer, window);
    }
}

GameStateId PauseState::getStateId() const {
    return GameStateId::Pause;
}

bool PauseState::buildPauseScene() {
    simple_engine::Logger::info("Building PauseState scene.");

    m_scene = std::make_unique<simple_engine::Scene>();

    std::shared_ptr<simple_engine::Texture> checkerTexture = std::make_shared<simple_engine::Texture>();
    const std::string texturePath = std::string(SIMPLE_ENGINE_ASSET_ROOT) + "/checker.ppm";
    if (!checkerTexture->loadFromFile(texturePath)) {
        checkerTexture.reset();
    }

    simple_engine::Transform backgroundTransform;
    backgroundTransform.position = glm::vec2(0.0f, 0.0f);
    backgroundTransform.scale = glm::vec2(8.0f, 4.5f);
    m_scene->createSprite(checkerTexture, backgroundTransform, glm::vec4(0.05f, 0.06f, 0.10f, 1.0f));

    m_scene->addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(300.0f, 140.0f), glm::vec2(680.0f, 180.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.12f, 0.14f, 0.18f, 0.94f), 1000));
    m_scene->addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(340.0f, 182.0f), glm::vec2(600.0f, 40.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.92f, 0.52f, 0.18f, 0.96f), 1001));
    m_scene->addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(380.0f, 250.0f), glm::vec2(520.0f, 22.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.35f, 0.76f, 0.48f, 0.95f), 1002));

    return true;
}

} // namespace simple_game
