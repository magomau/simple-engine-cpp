#include "Application.h"

#include <SDL3/SDL.h>

namespace simple_engine {

void Application::processEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }
}

void Application::update() {
}

} // namespace simple_engine
