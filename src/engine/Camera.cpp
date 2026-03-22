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
    m_deadZoneHalfSize = glm::vec2(0.0f, 0.0f);
    m_boundsMin = glm::vec2(0.0f, 0.0f);
    m_boundsMax = glm::vec2(0.0f, 0.0f);
    m_lastAspectRatio = 16.0f / 9.0f;
    m_hasFollowTarget = false;
    m_hasBounds = false;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    const_cast<Camera*>(this)->m_lastAspectRatio = std::max(aspectRatio, 0.0001f);
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
    position = clampToBounds(position);
}

void Camera::setFollowTarget(const glm::vec2& target) {
    glm::vec2 nextTarget = targetPosition;

    if (!m_hasFollowTarget) {
        nextTarget = target;
    } else {
        if (target.x < nextTarget.x - m_deadZoneHalfSize.x) {
            nextTarget.x = target.x + m_deadZoneHalfSize.x;
        } else if (target.x > nextTarget.x + m_deadZoneHalfSize.x) {
            nextTarget.x = target.x - m_deadZoneHalfSize.x;
        }

        if (target.y < nextTarget.y - m_deadZoneHalfSize.y) {
            nextTarget.y = target.y + m_deadZoneHalfSize.y;
        } else if (target.y > nextTarget.y + m_deadZoneHalfSize.y) {
            nextTarget.y = target.y - m_deadZoneHalfSize.y;
        }
    }

    targetPosition = clampToBounds(nextTarget);
    m_hasFollowTarget = true;
}

void Camera::clearFollowTarget() {
    m_hasFollowTarget = false;
    targetPosition = position;
}

void Camera::setFollowSharpness(float sharpness) {
    m_followSharpness = std::max(sharpness, 0.0f);
}

void Camera::setDeadZone(const glm::vec2& size) {
    m_deadZoneHalfSize = glm::max(size * 0.5f, glm::vec2(0.0f, 0.0f));
}

glm::vec2 Camera::getDeadZone() const {
    return m_deadZoneHalfSize * 2.0f;
}

void Camera::setBounds(const glm::vec2& minBounds, const glm::vec2& maxBounds) {
    m_boundsMin = minBounds;
    m_boundsMax = maxBounds;
    m_hasBounds = true;
    targetPosition = clampToBounds(targetPosition);
    position = clampToBounds(position);
}

void Camera::clearBounds() {
    m_hasBounds = false;
}

bool Camera::hasBounds() const {
    return m_hasBounds;
}

float Camera::getFollowSharpness() const {
    return m_followSharpness;
}

bool Camera::hasFollowTarget() const {
    return m_hasFollowTarget;
}

glm::vec2 Camera::clampToBounds(const glm::vec2& value) const {
    if (!m_hasBounds) {
        return value;
    }

    const float halfWidth = halfHeight * m_lastAspectRatio;
    const float minX = m_boundsMin.x + halfWidth;
    const float maxX = m_boundsMax.x - halfWidth;
    const float minY = m_boundsMin.y + halfHeight;
    const float maxY = m_boundsMax.y - halfHeight;

    glm::vec2 clamped = value;

    if (minX > maxX) {
        clamped.x = (m_boundsMin.x + m_boundsMax.x) * 0.5f;
    } else {
        clamped.x = std::clamp(clamped.x, minX, maxX);
    }

    if (minY > maxY) {
        clamped.y = (m_boundsMin.y + m_boundsMax.y) * 0.5f;
    } else {
        clamped.y = std::clamp(clamped.y, minY, maxY);
    }

    return clamped;
}

} // namespace simple_engine
