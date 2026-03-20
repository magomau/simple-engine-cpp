#pragma once

#include "Input.h"
#include "Scene.h"

namespace simple_engine {

class Application {
public:
    Application();

    void processEvents(bool& running);
    void update(float deltaTime);

    const Scene& getScene() const;

private:
    Input m_input;
    Scene m_scene;
    float m_moveSpeed;
};

} // namespace simple_engine
