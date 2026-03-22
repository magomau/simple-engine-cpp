#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace simple_engine {

class Camera {
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    void update(float deltaTime);
    void setFollowTarget(const glm::vec2& target);
    void clearFollowTarget();
    void setFollowSharpness(float sharpness);
    void setDeadZone(const glm::vec2& size);
    glm::vec2 getDeadZone() const;
    void setBounds(const glm::vec2& minBounds, const glm::vec2& maxBounds);
    void clearBounds();
    bool hasBounds() const;
    float getFollowSharpness() const;
    bool hasFollowTarget() const;

    glm::vec2 position;
    glm::vec2 targetPosition;
    float halfHeight;

private:
    glm::vec2 clampToBounds(const glm::vec2& value) const;

    float m_followSharpness;
    glm::vec2 m_deadZoneHalfSize;
    glm::vec2 m_boundsMin;
    glm::vec2 m_boundsMax;
    float m_lastAspectRatio;
    bool m_hasFollowTarget;
    bool m_hasBounds;
};

} // namespace simple_engine
