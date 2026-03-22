#pragma once

#include <glm/vec2.hpp>

namespace simple_engine {

class Input;
class Scene;

class PlayerController {
public:
    PlayerController();

    void update(const Input& input, Scene& scene, float deltaTime);
    void setMoveSpeed(float moveSpeed);
    void setCollisionScale(float collisionScale);

    float getMoveSpeed() const;
    float getCollisionScale() const;

private:
    glm::vec2 getInputDirection(const Input& input) const;

    float m_moveSpeed;
    float m_collisionScale;
};

} // namespace simple_engine
