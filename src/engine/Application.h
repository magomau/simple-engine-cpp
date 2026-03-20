#pragma once

namespace simple_engine {

class Application {
public:
    void processEvents(bool& running);
    void update();
};

} // namespace simple_engine
