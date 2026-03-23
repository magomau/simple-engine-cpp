#include "PauseState.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>
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

    for (UIButton& button : m_buttons) {
        button.resetInteraction();
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
    if (m_scene) {
        for (UIButton& button : m_buttons) {
            button.update(game, input, *m_scene);
        }

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
    m_buttons.clear();

    m_checkerTexture = std::make_shared<simple_engine::Texture>();
    const std::string texturePath = std::string(SIMPLE_ENGINE_ASSET_ROOT) + "/checker.ppm";
    if (!m_checkerTexture->loadFromFile(texturePath)) {
        m_checkerTexture.reset();
    }

    simple_engine::Transform backgroundTransform;
    backgroundTransform.position = glm::vec2(0.0f, 0.0f);
    backgroundTransform.scale = glm::vec2(8.0f, 4.5f);
    m_scene->createSprite(m_checkerTexture, backgroundTransform, glm::vec4(0.05f, 0.06f, 0.10f, 1.0f));

    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(300.0f, 140.0f), glm::vec2(680.0f, 180.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.12f, 0.14f, 0.18f, 0.94f), 1000));
    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(340.0f, 182.0f), glm::vec2(600.0f, 40.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.92f, 0.52f, 0.18f, 0.96f), 1001));
    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(380.0f, 250.0f), glm::vec2(520.0f, 22.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.35f, 0.76f, 0.48f, 0.95f), 1002));

    m_buttons.emplace_back(m_checkerTexture, glm::vec2(390.0f, 322.0f), glm::vec2(220.0f, 52.0f), [](Game& currentGame) {
        currentGame.changeState(GameStateId::Gameplay);
    }, simple_engine::UIAnchor::TopLeft, 1010);
    m_buttons.emplace_back(m_checkerTexture, glm::vec2(390.0f, 392.0f), glm::vec2(220.0f, 52.0f), [](Game& currentGame) {
        currentGame.changeState(GameStateId::MainMenu);
    }, simple_engine::UIAnchor::TopLeft, 1011);

    m_buttons[0].setColors(glm::vec4(0.24f, 0.60f, 0.90f, 0.96f), glm::vec4(0.34f, 0.72f, 1.0f, 0.98f), glm::vec4(0.18f, 0.45f, 0.74f, 0.99f));
    m_buttons[1].setColors(glm::vec4(0.82f, 0.42f, 0.18f, 0.96f), glm::vec4(0.96f, 0.52f, 0.24f, 0.98f), glm::vec4(0.64f, 0.32f, 0.14f, 0.99f));

    for (UIButton& button : m_buttons) {
        button.initialize(*m_scene);
    }

    return true;
}

} // namespace simple_game
