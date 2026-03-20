#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "Camera.h"
#include "RenderObject.h"

namespace simple_engine {

class Renderer;
class Window;

class Scene {
public:
    Scene();

    void update(float deltaTime);
    void render(Renderer& renderer, Window& window) const;

    const std::vector<RenderObject>& getObjects() const;
    RenderObject* getPrimaryObject();
    const Camera& getCamera() const;
    Camera& getCamera();
    void setObjectInputDirection(const glm::vec2& direction);
    void setCameraInputDirection(const glm::vec2& direction);

private:
    std::vector<RenderObject> m_objects;
    Camera m_camera;
    glm::vec2 m_objectInputDirection;
    glm::vec2 m_cameraInputDirection;
    float m_objectMoveSpeed;
    float m_cameraMoveSpeed;
};

} // namespace simple_engine
