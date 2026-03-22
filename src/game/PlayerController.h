#pragma once

#include <glm/vec2.hpp>

namespace simple_engine {
class Input;
class RenderObject;
class Scene;
}

namespace simple_game {

class PlayerController {
public:
    PlayerController();

    void update(const simple_engine::Input& input, simple_engine::Scene& scene, simple_engine::RenderObject& player, float deltaTime);
    void setMoveSpeed(float moveSpeed);
    void setCollisionScale(float collisionScale);

    float getMoveSpeed() const;
    float getCollisionScale() const;

private:
    glm::vec2 getInputDirection(const simple_engine::Input& input) const;

    float m_moveSpeed;
    float m_collisionScale;
};

} // namespace simple_game
