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
    float getFollowSharpness() const;
    bool hasFollowTarget() const;

    glm::vec2 position;
    glm::vec2 targetPosition;
    float halfHeight;

private:
    float m_followSharpness;
    bool m_hasFollowTarget;
};

} // namespace simple_engine
