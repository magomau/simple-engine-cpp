#include "Application.h"

#include <glm/vec2.hpp>

#include <SDL3/SDL.h>

namespace simple_engine {

Application::Application()
    : m_cameraSpeed(1.8f) {
}

void Application::processEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        m_input.processEvent(event);
    }

    glm::vec2 cameraDirection(0.0f, 0.0f);

    if (m_input.isKeyPressed(SDL_SCANCODE_UP)) {
        cameraDirection.y += 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_DOWN)) {
        cameraDirection.y -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_LEFT)) {
        cameraDirection.x -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
        cameraDirection.x += 1.0f;
    }

    m_scene.setCameraInputDirection(cameraDirection);
}

void Application::update(float deltaTime) {
    m_playerController.update(m_input, m_scene, deltaTime);
    m_scene.update(deltaTime);
}

Scene& Application::getScene() {
    return m_scene;
}

const Scene& Application::getScene() const {
    return m_scene;
}

} // namespace simple_engine
