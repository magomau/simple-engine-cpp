#pragma once

#include "Input.h"
#include "Scene.h"

namespace simple_engine {

class Application {
public:
    Application();

    void processEvents(bool& running);
    Scene& getScene();
    const Scene& getScene() const;

private:
    Input m_input;
    Scene m_scene;
    float m_moveSpeed;
    float m_cameraSpeed;
};

} // namespace simple_engine
