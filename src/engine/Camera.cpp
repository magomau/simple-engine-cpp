#include "Camera.h"

#include <algorithm>
#include <cmath>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/vec3.hpp>

namespace simple_engine {

Camera::Camera()
    : position(0.0f, 0.0f)
    , targetPosition(0.0f, 0.0f)
    , halfHeight(1.0f) {
    m_followSharpness = 8.0f;
    m_hasFollowTarget = false;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    const float halfWidth = halfHeight * aspectRatio;
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
}

void Camera::update(float deltaTime) {
    if (!m_hasFollowTarget) {
        return;
    }

    const float clampedDeltaTime = std::max(deltaTime, 0.0f);
    const float interpolationFactor = 1.0f - std::exp(-m_followSharpness * clampedDeltaTime);
    position += (targetPosition - position) * interpolationFactor;
}

void Camera::setFollowTarget(const glm::vec2& target) {
    targetPosition = target;
    m_hasFollowTarget = true;
}

void Camera::clearFollowTarget() {
    m_hasFollowTarget = false;
    targetPosition = position;
}

void Camera::setFollowSharpness(float sharpness) {
    m_followSharpness = std::max(sharpness, 0.0f);
}

float Camera::getFollowSharpness() const {
    return m_followSharpness;
}

bool Camera::hasFollowTarget() const {
    return m_hasFollowTarget;
}

} // namespace simple_engine
