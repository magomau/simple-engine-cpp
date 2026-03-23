#pragma once

#include <array>

#include <glm/vec2.hpp>

#include <SDL3/SDL.h>

namespace simple_engine {

class Input {
public:
    Input();

    void beginFrame();
    void processEvent(const SDL_Event& event);
    bool isKeyPressed(SDL_Scancode scancode) const;
    glm::vec2 getMousePosition() const;
    bool isMouseButtonDown(Uint8 button) const;
    bool wasMouseButtonPressed(Uint8 button) const;
    bool wasMouseButtonReleased(Uint8 button) const;

private:
    std::array<bool, SDL_SCANCODE_COUNT> m_keyStates;
    std::array<bool, 8> m_mouseButtonStates;
    std::array<bool, 8> m_mouseButtonPressed;
    std::array<bool, 8> m_mouseButtonReleased;
    glm::vec2 m_mousePosition;
};

} // namespace simple_engine
