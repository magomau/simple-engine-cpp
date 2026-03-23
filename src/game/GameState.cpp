#include "GameState.h"

namespace simple_game {

void GameState::exit(Game& game) {
    (void)game;
}

void GameState::handleEvent(Game& game, const SDL_Event& event) {
    (void)game;
    (void)event;
}

} // namespace simple_game
