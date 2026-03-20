#pragma once

#include <array>

#include <SDL3/SDL.h>

namespace simple_engine {

class Input {
public:
    Input();

    void processEvent(const SDL_Event& event);
    bool isKeyPressed(SDL_Scancode scancode) const;

private:
    std::array<bool, SDL_SCANCODE_COUNT> m_keyStates;
};

} // namespace simple_engine
