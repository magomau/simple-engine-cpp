#include "Input.h"

namespace simple_engine {

Input::Input()
    : m_keyStates{}
    , m_mouseButtonStates{}
    , m_mouseButtonPressed{}
    , m_mouseButtonReleased{}
    , m_mousePosition(0.0f, 0.0f) {
}

void Input::beginFrame() {
    m_mouseButtonPressed.fill(false);
    m_mouseButtonReleased.fill(false);
}

void Input::processEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
        if (event.key.scancode < SDL_SCANCODE_COUNT) {
            m_keyStates[event.key.scancode] = true;
        }
        return;
    }

    if (event.type == SDL_EVENT_KEY_UP) {
        if (event.key.scancode < SDL_SCANCODE_COUNT) {
            m_keyStates[event.key.scancode] = false;
        }
        return;
    }

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        m_mousePosition = glm::vec2(event.motion.x, event.motion.y);
        return;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        m_mousePosition = glm::vec2(event.button.x, event.button.y);
        if (event.button.button < m_mouseButtonStates.size()) {
            m_mouseButtonStates[event.button.button] = true;
            m_mouseButtonPressed[event.button.button] = true;
        }
        return;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        m_mousePosition = glm::vec2(event.button.x, event.button.y);
        if (event.button.button < m_mouseButtonStates.size()) {
            m_mouseButtonStates[event.button.button] = false;
            m_mouseButtonReleased[event.button.button] = true;
        }
    }
}

bool Input::isKeyPressed(SDL_Scancode scancode) const {
    if (scancode >= SDL_SCANCODE_COUNT) {
        return false;
    }

    return m_keyStates[scancode];
}

glm::vec2 Input::getMousePosition() const {
    return m_mousePosition;
}

bool Input::isMouseButtonDown(Uint8 button) const {
    if (button >= m_mouseButtonStates.size()) {
        return false;
    }

    return m_mouseButtonStates[button];
}

bool Input::wasMouseButtonPressed(Uint8 button) const {
    if (button >= m_mouseButtonPressed.size()) {
        return false;
    }

    return m_mouseButtonPressed[button];
}

bool Input::wasMouseButtonReleased(Uint8 button) const {
    if (button >= m_mouseButtonReleased.size()) {
        return false;
    }

    return m_mouseButtonReleased[button];
}

} // namespace simple_engine
