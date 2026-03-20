#include "Input.h"

namespace simple_engine {

Input::Input()
    : m_keyStates{} {
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
    }
}

bool Input::isKeyPressed(SDL_Scancode scancode) const {
    if (scancode >= SDL_SCANCODE_COUNT) {
        return false;
    }

    return m_keyStates[scancode];
}

} // namespace simple_engine
