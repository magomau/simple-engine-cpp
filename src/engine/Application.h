#pragma once

#include "Input.h"
#include "PlayerController.h"
#include "Scene.h"

namespace simple_engine {

class Application {
public:
    Application();

    void processEvents(bool& running);
    void update(float deltaTime);
    Scene& getScene();
    const Scene& getScene() const;

private:
    Input m_input;
    PlayerController m_playerController;
    Scene m_scene;
    float m_cameraSpeed;
};

} // namespace simple_engine
