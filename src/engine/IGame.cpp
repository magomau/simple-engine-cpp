#include "IGame.h"

namespace simple_engine {

void IGame::handleEvent(const SDL_Event& event) {
    (void)event;
}

void IGame::shutdown() {
}

} // namespace simple_engine
