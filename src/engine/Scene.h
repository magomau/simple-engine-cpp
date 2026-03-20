#pragma once

#include <vector>

#include "Camera.h"
#include "RenderObject.h"

namespace simple_engine {

class Scene {
public:
    Scene();

    void update(float deltaTime);

    const std::vector<RenderObject>& getObjects() const;
    RenderObject* getPrimaryObject();
    const Camera& getCamera() const;
    Camera& getCamera();

private:
    std::vector<RenderObject> m_objects;
    Camera m_camera;
};

} // namespace simple_engine
