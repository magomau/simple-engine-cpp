#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/vec3.hpp>

namespace simple_engine {

Camera::Camera()
    : position(0.0f, 0.0f)
    , halfHeight(1.0f) {
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    const float halfWidth = halfHeight * aspectRatio;
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
}

} // namespace simple_engine
