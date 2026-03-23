#include "MainMenuState.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

#include <glm/vec4.hpp>

#include "Game.h"
#include "GameplayState.h"
#include "engine/Scene.h"
#include "engine/Sprite.h"
#include "engine/Texture.h"
#include "engine/UIElement.h"
#include "core/Logger.h"

namespace simple_game {

MainMenuState::MainMenuState() = default;

bool MainMenuState::enter(Game& game) {
    if (GameplayState* gameplayState = game.getGameplayState()) {
        gameplayState->reset();
    }

    if (!m_scene) {
        return buildMenuScene();
    }

    for (UIButton& button : m_buttons) {
        button.resetInteraction();
    }

    simple_engine::Logger::info("Entering MainMenuState.");
    return true;
}

void MainMenuState::handleEvent(Game& game, const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN || event.key.repeat) {
        return;
    }

    if (event.key.scancode == SDL_SCANCODE_RETURN || event.key.scancode == SDL_SCANCODE_SPACE) {
        game.changeState(GameStateId::Gameplay);
    }
}

void MainMenuState::update(Game& game, const simple_engine::Input& input, float deltaTime) {
    if (m_scene) {
        for (UIButton& button : m_buttons) {
            button.update(game, input, *m_scene);
        }

        m_scene->update(deltaTime);
    }
}

void MainMenuState::render(Game& game, simple_engine::Renderer& renderer, simple_engine::Window& window) {
    (void)game;

    if (m_scene) {
        m_scene->render(renderer, window);
    }
}

GameStateId MainMenuState::getStateId() const {
    return GameStateId::MainMenu;
}

bool MainMenuState::buildMenuScene() {
    simple_engine::Logger::info("Building MainMenuState scene.");

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
    m_scene->createSprite(m_checkerTexture, backgroundTransform, glm::vec4(0.10f, 0.15f, 0.28f, 1.0f));

    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(240.0f, 110.0f), glm::vec2(800.0f, 220.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.12f, 0.16f, 0.24f, 0.92f), 1000));
    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(280.0f, 150.0f), glm::vec2(720.0f, 48.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.88f, 0.72f, 0.24f, 0.96f), 1001));
    m_scene->addUIElement(simple_engine::UIElement(m_checkerTexture, glm::vec2(320.0f, 230.0f), glm::vec2(640.0f, 24.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.24f, 0.62f, 0.92f, 0.95f), 1002));

    m_buttons.emplace_back(m_checkerTexture, glm::vec2(360.0f, 310.0f), glm::vec2(240.0f, 54.0f), [](Game& currentGame) {
        currentGame.changeState(GameStateId::Gameplay);
    }, simple_engine::UIAnchor::TopLeft, 1010);
    m_buttons.emplace_back(m_checkerTexture, glm::vec2(360.0f, 382.0f), glm::vec2(240.0f, 54.0f), [](Game& currentGame) {
        SDL_Event quitEvent{};
        quitEvent.type = SDL_EVENT_QUIT;
        SDL_PushEvent(&quitEvent);
        (void)currentGame;
    }, simple_engine::UIAnchor::TopLeft, 1011);

    m_buttons[0].setColors(glm::vec4(0.23f, 0.70f, 0.44f, 0.96f), glm::vec4(0.32f, 0.82f, 0.54f, 0.98f), glm::vec4(0.18f, 0.56f, 0.35f, 0.99f));
    m_buttons[1].setColors(glm::vec4(0.74f, 0.24f, 0.20f, 0.96f), glm::vec4(0.88f, 0.30f, 0.26f, 0.98f), glm::vec4(0.58f, 0.18f, 0.16f, 0.99f));

    for (UIButton& button : m_buttons) {
        button.initialize(*m_scene);
    }

    return true;
}

} // namespace simple_game
