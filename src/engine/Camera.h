#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace simple_engine {

class Camera {
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    glm::vec2 position;
    float halfHeight;
};

} // namespace simple_engine
