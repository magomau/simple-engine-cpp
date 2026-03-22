#include "engine/Engine.h"
#include "game/Game.h"

int main() {
    simple_engine::Engine engine;
    simple_game::Game game;

    if (!engine.init()) {
        return 1;
    }

    engine.run(game);
    engine.shutdown();

    return 0;
}
