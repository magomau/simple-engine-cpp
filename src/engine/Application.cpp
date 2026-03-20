#include "Application.h"

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

#include <SDL3/SDL.h>

namespace simple_engine {

Application::Application()
    : m_moveSpeed(1.5f) {
}

void Application::processEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        m_input.processEvent(event);
    }
}

void Application::update(float deltaTime) {
    glm::vec2 direction(0.0f, 0.0f);

    if (m_input.isKeyPressed(SDL_SCANCODE_W)) {
        direction.y += 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_S)) {
        direction.y -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_A)) {
        direction.x -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_D)) {
        direction.x += 1.0f;
    }

    if (glm::length(direction) > 0.0f) {
        direction = glm::normalize(direction);
        RenderObject* playerObject = m_scene.getPrimaryObject();
        if (playerObject != nullptr) {
            playerObject->transform.position += direction * (m_moveSpeed * deltaTime);
        }
    }

    m_scene.update(deltaTime);
}

const Scene& Application::getScene() const {
    return m_scene;
}

} // namespace simple_engine
