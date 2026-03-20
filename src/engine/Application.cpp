#include "Application.h"

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

#include <SDL3/SDL.h>

namespace simple_engine {

Application::Application()
    : m_moveSpeed(1.5f)
    , m_cameraSpeed(1.8f) {
}

void Application::processEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        m_input.processEvent(event);
    }

    glm::vec2 objectDirection(0.0f, 0.0f);
    glm::vec2 cameraDirection(0.0f, 0.0f);

    if (m_input.isKeyPressed(SDL_SCANCODE_W)) {
        objectDirection.y += 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_S)) {
        objectDirection.y -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_A)) {
        objectDirection.x -= 1.0f;
    }
    if (m_input.isKeyPressed(SDL_SCANCODE_D)) {
        objectDirection.x += 1.0f;
    }

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

    m_scene.setObjectInputDirection(objectDirection);
    m_scene.setCameraInputDirection(cameraDirection);
}

Scene& Application::getScene() {
    return m_scene;
}

const Scene& Application::getScene() const {
    return m_scene;
}

} // namespace simple_engine
