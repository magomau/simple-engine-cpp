#include "engine/Engine.h"

int main() {
    simple_engine::Engine engine;

    if (!engine.init()) {
        return 1;
    }

    engine.run();
    engine.shutdown();

    return 0;
}
